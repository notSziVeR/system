// find:
#include "desc_client.h"

// paste below:
#ifdef __MISSION__
#include "mission_manager.h"
#endif


// find:
	DSManager dsManager;

// paste below:
#ifdef __MISSION__
	CMissionManager mission_manager;
#endif