// find:
			Set(HEADER_GC_DRAGON_SOUL_REFINE,		CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDragonSoulRefine), STATIC_SIZE_PACKET));

// paste below:
#ifdef ENABLE_MISSION
			Set(HEADER_GC_MISSION, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCMission), DYNAMIC_SIZE_PACKET));
#endif