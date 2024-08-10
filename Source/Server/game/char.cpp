// add at the end of the file:
#ifdef __MISSION__
std::vector<LPMISSION> CHARACTER::GetMission()
{
	std::vector<LPMISSION> v;
	v.resize(m_mapMission.size());

	for (const auto mission : m_mapMission)
		v.push_back(mission.second);

	return v;
}

LPMISSION CHARACTER::GetMission(DWORD npc_vnum)
{
	if (!m_bMissionInitialized)
	{
		m_bMissionInitialized = true;

		const auto vec_npc = CMissionManager::instance().GetNPCVector();
		for (const auto npc_vnum : vec_npc)
		{
			const auto index = GetMissionIndex(npc_vnum);

			const auto mission = CMissionManager::instance().GetMission(npc_vnum, index);
			if (mission)
			{
				SetMission(npc_vnum, mission);
				sys_log(0, "mission index %d, item vnum %d, item count %d", mission->index, mission->required_item.vnum, mission->required_item.count);

			}
			else
			{
				sys_err("mission not found");
				M2_DELETE(mission);
			}
		}
	}

	const auto it = m_mapMission.find(npc_vnum);
	if (it != m_mapMission.end())
		return it->second;

	return nullptr;
}

void CHARACTER::SetMission(DWORD npc_vnum, LPMISSION mission)
{
	// prevent leaks
	auto it = GetMission(npc_vnum);
	if (it) M2_DELETE(it);

	m_mapMission[npc_vnum] = mission;
}

int CHARACTER::GetReturnedCount(DWORD npc_vnum)
{
	char qf[64];
	snprintf(qf, sizeof(qf), "__mission.returned_%d", npc_vnum);

	return GetQuestFlag(qf);
}

int CHARACTER::GetMissionIndex(DWORD npc_vnum)
{
	char qf[64];
	snprintf(qf, sizeof(qf), "__mission.index_%d", npc_vnum);

	return GetQuestFlag(qf);
}

int CHARACTER::GetMissionTime(DWORD npc_vnum)
{
	char qf[64];
	snprintf(qf, sizeof(qf), "__mission.time_%d", npc_vnum);

	return GetQuestFlag(qf);
}

void CHARACTER::SetReturnedCount(DWORD npc_vnum, BYTE count)
{
	char qf[64];
	snprintf(qf, sizeof(qf), "__mission.returned_%d", npc_vnum);

	SetQuestFlag(qf, count);
}

void CHARACTER::SetMissionIndex(DWORD npc_vnum, BYTE count)
{
	char qf[64];
	snprintf(qf, sizeof(qf), "__mission.index_%d", npc_vnum);

	SetQuestFlag(qf, count);
}

void CHARACTER::SetMissionTime(DWORD npc_vnum, DWORD time)
{
	char qf[64];
	snprintf(qf, sizeof(qf), "__mission.time_%d", npc_vnum);

	SetQuestFlag(qf, time);
}
#endif
