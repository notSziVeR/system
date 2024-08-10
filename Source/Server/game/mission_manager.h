#pragma once

class CMission
{
public:
	using item = struct SItem
	{
		DWORD vnum;
		BYTE count;

		bool operator == (const struct SItem& item) const
		{
			return item.vnum == vnum && item.count == count;
		}

	};

	using affect = struct SAffect
	{
		DWORD index;
		DWORD value;

		bool operator == (const struct SAffect& item) const
		{
			return item.index == index && item.value == value;
		}
	};

	CMission()
	{
		index = 0;
		npc_vnum = 0;
		required_item = {};
		level = 0;
		chance = 0.0;
		drop_chance = 0.0;
		time = 0;
		map_index = 0;
		mob_vnum = {};
		reward_item = {};
		reward_affect = {};
	}

	BYTE index;
	DWORD npc_vnum;
	item required_item;
	BYTE level;
	float chance;
	float drop_chance;
	DWORD time;
	DWORD map_index;
	std::vector<DWORD> mob_vnum;
	std::vector<item> reward_item;
	std::vector<affect> reward_affect;

};

typedef class CMission* LPMISSION;

class CMissionManager : public singleton<CMissionManager>
{
public:
	CMissionManager();
	~CMissionManager();

	LPMISSION	GetMission(DWORD npc_vnum, BYTE index);
	
	bool ReadMissionTable(const char* c_pszFileName);
	std::vector<DWORD> GetNPCVector() const { return m_vec_missionNPC; }

	static bool iequals(const std::string& a, const std::string& b)
	{
		unsigned int sz = a.size();
		if (b.size() != sz)
			return false;
		for (unsigned int i = 0; i < sz; ++i)
			if (tolower(a[i]) != tolower(b[i]))
				return false;
		return true;
	}

private:
	std::vector<LPMISSION> m_vec_missionData;
	std::vector<DWORD> m_vec_missionNPC;
};
