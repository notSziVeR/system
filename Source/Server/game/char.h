// find:
#include "char_manager.h"

// paste below:
#ifdef __MISSION__
#include "mission_manager.h"
class CMission;
#endif

// find:
		int				GetSyncHackCount() { return m_iSyncHackCount; }

// paste below:
#ifdef __MISSION__
	public:
		std::vector<LPMISSION> GetMission();
		LPMISSION GetMission(DWORD npc_vnum);
		void	SetMission(DWORD npc_vnum, LPMISSION mission);
		int		GetReturnedCount(DWORD npc_vnum);
		int		GetMissionIndex(DWORD npc_vnum);		
		int		GetMissionTime(DWORD npc_vnum);		
		void	SetReturnedCount(DWORD npc_vnum, BYTE count);
		void	SetMissionIndex(DWORD npc_vnum, BYTE count);
		void	SetMissionTime(DWORD npc_vnum, DWORD time);
	private:
		std::map<DWORD, LPMISSION> m_mapMission;
		bool m_bMissionInitialized = false;
#endif