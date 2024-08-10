// find:
#include "DragonSoul.h"

// paste below:
#ifdef __MISSION__
#include "mission_manager.h"
#endif

// find:
	sys_log(0, "LoadLocaleFile: DragonSoulTable: %s", szDragonSoulTableFileName);
	if (!DSManager::instance().ReadDragonSoulTableFile(szDragonSoulTableFileName))
	{
		sys_err("cannot load DragonSoulTable: %s", szDragonSoulTableFileName);
		//thecore_shutdown();
		//return;
	}	

// paste below:
#ifdef __MISSION__
	char szMissionTableFileName[FILE_NAME_LEN];
	snprintf(szMissionTableFileName, sizeof(szMissionTableFileName),
		"%s/mission_table.txt", LocaleService_GetBasePath().c_str());

	if (!CMissionManager::instance().ReadMissionTable(szMissionTableFileName))
	{
		sys_err("cannot load mission table: %s", szMissionTableFileName);
		thecore_shutdown();
		return;
	}
#endif
