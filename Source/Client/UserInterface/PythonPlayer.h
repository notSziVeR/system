// find:
		std::map<DWORD, DWORD> m_kMap_dwAffectIndexToSkillIndex;

// paste below:
#ifdef ENABLE_MISSION
	public:
		void					ApendMissionNPC(DWORD vnum) { 
									if (std::find(m_vecMissionNPC.begin(), m_vecMissionNPC.end(), vnum) == m_vecMissionNPC.end())
										m_vecMissionNPC.push_back(vnum);
								}
		std::vector<DWORD>		GetMissionNPC() { return m_vecMissionNPC; }
	private:
		std::vector<DWORD>		m_vecMissionNPC;
#endif