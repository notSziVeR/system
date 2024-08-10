// find:
	Set(HEADER_CG_STATE_CHECKER, sizeof(BYTE), "ServerStateCheck", false);

// paste below:
#ifdef __MISSION__
	Set(HEADER_CG_MISSION, sizeof(TPacketCGMission), "Mission", true);
#endif