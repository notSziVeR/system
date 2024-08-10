#include "stdafx.h"

#ifdef __MISSION__
#include "constants.h"
#include "text_file_loader.h"
#include "group_text_parse_tree.h"
#include "char.h"
#include "config.h"

#include "mission_manager.h"

CMissionManager::CMissionManager()
{

}

CMissionManager::~CMissionManager()
{

}

LPMISSION CMissionManager::GetMission(DWORD npc_vnum, BYTE index)
{
	for (const auto mission : m_vec_missionData)
	{
		bool second_condition = (index) ? mission->index == index : true;

		if (mission->npc_vnum == npc_vnum && second_condition)
		{
			auto new_mission = M2_NEW CMission(*mission);
			return new_mission;
		}
	}

	return nullptr;
}

bool CMissionManager::ReadMissionTable(const char* c_pszFileName)
{
	CGroupTextParseTreeLoader loader;
	if (!loader.Load(c_pszFileName))
	{
		sys_err("%s Load fail.", c_pszFileName);
		return false;
	}

	auto* pMissionGroup = loader.GetGroup("npc");
	if (nullptr == pMissionGroup)
	{
		sys_err("Group NPC is not exist.");
		return false;
	}

	sys_log(0, "Mission: loading missions for %d npcs", pMissionGroup->GetRowCount());

	for (auto i = 0; i < pMissionGroup->GetRowCount(); i++)
	{
		DWORD npc_vnum;
		std::string group_name;
		if (!pMissionGroup->GetValue(i, "npc", npc_vnum) || !pMissionGroup->GetValue(i, "group", group_name))
		{
			sys_err("Invalid row(%d). Group 'npc' rows must have 'npc', 'group' columns", i);
			return false;
		}
		std::transform(group_name.begin(), group_name.end(), group_name.begin(), static_cast<int(*)(int)>(std::tolower));

		if (std::find(m_vec_missionNPC.begin(), m_vec_missionNPC.end(), npc_vnum) == m_vec_missionNPC.end())
			m_vec_missionNPC.push_back(npc_vnum);

		auto* pNPCGroup = loader.GetGroup(group_name.c_str());
		if (!pNPCGroup)
		{
			sys_err("Group %s is not exist.", group_name.c_str());
			return false;
		}

		for (auto j = 0; j < pNPCGroup->GetRowCount(); j++)
		{
			sys_log(0, "Mission: loading %d missions for npc %d", pNPCGroup->GetRowCount(), npc_vnum);

			std::string mission_name;
			if (!pNPCGroup->GetValue(j, "name", mission_name))
			{
				sys_err("row(%d) of 'group %s' does not have 'name' column", j, pNPCGroup->GetNodeName().c_str());
				return false;
			}

			sys_log(0, "Mission: npc_vnum %d, group %s, index %d, name %s", npc_vnum, group_name.c_str(), j, mission_name.c_str());

			auto* pMissionGroup = loader.GetGroup(mission_name.c_str());
			if (!pMissionGroup)
			{
				sys_err("Group %s is not exist.", mission_name.c_str());
				return false;
			}

			const auto mission = M2_NEW CMission();

			if (!pMissionGroup->GetValue("item_vnum", 0, mission->required_item.vnum))
			{
				sys_err("Syntax error %s : no 'item_vnum', node %s", c_pszFileName, pMissionGroup->GetNodeName().c_str());
				return false;
			}
				
			if (!pMissionGroup->GetValue("item_count", 0, mission->required_item.count))
			{
				sys_err("Syntax error %s : no 'item_count', node %s", c_pszFileName, pMissionGroup->GetNodeName().c_str());
				return false;
			}				
				
			if (!pMissionGroup->GetValue("level", 0, mission->level))
			{
				sys_err("Syntax error %s : no 'level', node %s", c_pszFileName, pMissionGroup->GetNodeName().c_str());
				return false;
			}				
				
			if (!pMissionGroup->GetValue("chance", 0, mission->chance))
			{
				sys_err("Syntax error %s : no 'chance', node %s", c_pszFileName, pMissionGroup->GetNodeName().c_str());
				return false;
			}				
				
			if (!pMissionGroup->GetValue("drop_chance", 0, mission->drop_chance))
			{
				sys_err("Syntax error %s : no 'drop_chance', node %s", c_pszFileName, pMissionGroup->GetNodeName().c_str());
				return false;
			}				
				
			if (!pMissionGroup->GetValue("time", 0, mission->time))
			{
				sys_err("Syntax error %s : no 'time', node %s", c_pszFileName, pMissionGroup->GetNodeName().c_str());
				return false;
			}				
				
			if (!pMissionGroup->GetValue("map_index", 0, mission->map_index))
			{
				sys_err("Syntax error %s : no 'map_index', node %s", c_pszFileName, pMissionGroup->GetNodeName().c_str());
				return false;
			}
				
			if (mission->chance > 100.0 || mission->chance <= 0)
			{
				sys_err("Syntax error %s : 'chance' is supposed to be 1-100, node %s", c_pszFileName, pMissionGroup->GetNodeName().c_str());
				return false;
			}

			auto* pMobGroup = pMissionGroup->GetChildNode("mob");
			if (!pMobGroup)
			{
				sys_err("Group %s does not have 'group mob'.", pMissionGroup->GetNodeName().c_str());
				return false;
			}

			mission->index = j;
			mission->npc_vnum = npc_vnum;

			for (auto l = 0; l < pMobGroup->GetRowCount(); l++)
			{
				DWORD mob_vnum;
				if (!pMobGroup->GetValue(l, "vnum", mob_vnum))
				{
					sys_err("row(%d) of 'group mob' of 'group %s' does not have 'vnum' column", l, pMissionGroup->GetNodeName().c_str());
					return false;
				}

				if (std::find(mission->mob_vnum.begin(), mission->mob_vnum.end(), mob_vnum) == mission->mob_vnum.end())
					mission->mob_vnum.push_back(mob_vnum);

				sys_log(0, "        MOB: %d", mob_vnum);
			}

			auto* pRewardGroup = pMissionGroup->GetChildNode("reward");
			if (!pRewardGroup)
			{
				sys_err("Group %s does not have 'group reward'.", pMissionGroup->GetNodeName().c_str());
				return false;
			}

			for (auto l = 0; l < pRewardGroup->GetRowCount(); l++)
			{
				std::string type;
				std::string index;
				DWORD value;

				if (!pRewardGroup->GetValue(l, "type", type))
				{
					sys_err("row(%d) of 'group reward' of 'group %s' does not have 'type' column", l, pMissionGroup->GetNodeName().c_str());
					return false;
				}
					
				if (!pRewardGroup->GetValue(l, "index", index))
				{
					sys_err("row(%d) of 'group reward' of 'group %s' does not have 'index' column", l, pMissionGroup->GetNodeName().c_str());
					return false;
				}
					
				if (!pRewardGroup->GetValue(l, "value", value))
				{
					sys_err("row(%d) of 'group reward' of 'group %s' does not have 'value' column", l, pMissionGroup->GetNodeName().c_str());
					return false;
				}

				if (iequals(type, "Affect"))
				{
					CMission::affect item;
					if (0 == (item.index = FN_get_apply_type(index.c_str())))
					{
						sys_err("Invalid apply_type(%s)", index.c_str());
						return false;
					}
					item.value = value;

					if (std::find_if(mission->reward_affect.begin(), mission->reward_affect.end(),
						[&](const CMission::affect it)
						{ return it == item; }) == mission->reward_affect.end())
						mission->reward_affect.push_back(item);
				}
				else if (iequals(type, "Item"))
				{
					CMission::item item;
					item.vnum = atoi(index.c_str());
					item.count = value;

					if (std::find_if(mission->reward_item.begin(), mission->reward_item.end(),
						[&](const CMission::item it)
						{ return it == item; }) == mission->reward_item.end())
						mission->reward_item.push_back(item);

				}
				else
				{
					sys_err("row(%d) of 'group reward' of 'group %s' 'type' value can only be `Affect` or `Item`", l, pMissionGroup->GetNodeName().c_str());
					return false;
				}
				sys_log(0, "        %s %s %d", type.c_str(), index.c_str(), value);				
			}

			m_vec_missionData.push_back(mission);
		}
	}

	return true;
}
#endif
