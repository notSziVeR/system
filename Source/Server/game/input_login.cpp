// find:
    if (g_noticeBattleZone)
	{
		[...]
	}

// paste below:
#ifdef __MISSION__
	const auto vec_npc = CMissionManager::instance().GetNPCVector();
	BYTE vec_size = static_cast<BYTE>(vec_npc.size());

	TPacketGCMission header{};
	header.header = HEADER_GC_MISSION;
	header.subheader = MISSION_GC_SUBHEADER_SET_NPC;
	header.size = sizeof(TPacketGCMission) + sizeof(BYTE);

	TEMP_BUFFER buf;

	for (const auto npc_vnum : vec_npc)
	{
		buf.write(&npc_vnum, sizeof(DWORD));
		header.size += sizeof(DWORD);
	}

	const auto desc = ch->GetDesc();
	desc->BufferedPacket(&header, sizeof(TPacketGCMission));
	desc->Packet(&vec_size, sizeof(BYTE));
	desc->Packet(buf.read_peek(), buf.size());
#endif
