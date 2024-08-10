// find:
			case HEADER_GC_DRAGON_SOUL_REFINE:
				ret = RecvDragonSoulRefine();
				break;

// paste below:
#ifdef ENABLE_MISSION
			case HEADER_GC_MISSION:
				ret = RecvMissionPacket();
				break;
#endif

// add at the end of the file:
#ifdef ENABLE_MISSION
bool CPythonNetworkStream::SendMissionPacket(BYTE subheader, DWORD npc_vnum, DWORD item_vnum)
{
	if (!__CanActMainInstance())
		return true;

	TPacketCGMission packet;
	packet.header = HEADER_CG_MISSION;
	packet.subheader = subheader;

	if (!Send(sizeof(TPacketCGMission), &packet))
		return false;

	if (!Send(sizeof(DWORD), &npc_vnum))
		return false;

	if (subheader == MISSION_CG_SUBHEADER_RETURN || subheader == MISSION_CG_SUBHEADER_RETURN_ALL)
		if (!Send(sizeof(DWORD), &item_vnum))
			return false;

	return SendSequence();
}

bool CPythonNetworkStream::RecvMissionPacket()
{
	TPacketGCMission packet;
	if (!Recv(sizeof(packet), &packet))
		return false;

	TraceError("RecvMissionPacket: subheader %d, size %d", packet.subheader, packet.size);

	switch (packet.subheader)
	{
		case MISSION_GC_SUBHEADER_SET_DATA:
		{
			TPacketGCMissionInfo info;
			if (!Recv(sizeof(TPacketGCMissionInfo), &info))
				return false;

			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_MissionSetData", Py_BuildValue("(iiifii)",
				info.required_item.vnum, info.required_item.count, info.level, info.chance, info.time, info.map_index));

			for (int i = 0; i < info.mob_count; i++)
			{
				DWORD mob_vnum;
				if (!Recv(sizeof(DWORD), &mob_vnum))
					return false;

				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_MissionAppendMob", Py_BuildValue("(i)", mob_vnum));
			}
		
			for (int i = 0; i < info.affect_count; i++)
			{
				TPacketGCMissionAffect affect;
				if (!Recv(sizeof(TPacketGCMissionAffect), &affect))
					return false;

				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_MissionAppendAffect", Py_BuildValue("(ii)",
					affect.index, affect.value));
			}
		
			for (int i = 0; i < info.item_count; i++)
			{
				TPacketGCMissionItem item;
				if (!Recv(sizeof(TPacketGCMissionItem), &item))
					return false;

				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_MissionAppendItem", Py_BuildValue("(ii)",
					item.vnum, item.count));
			}
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_MissionRefreshWindow", Py_BuildValue("()"));
			return true;
		}
		case MISSION_GC_SUBHEADER_SET_NPC:
		{
			BYTE npc_count;
			if (!Recv(sizeof(BYTE), &npc_count))
				return false;

			CPythonPlayer& rkPlayer = CPythonPlayer::Instance();

			for (int i = 0; i < npc_count; i++)
			{
				DWORD npc_vnum;
				if (!Recv(sizeof(DWORD), &npc_vnum))
					return false;

				rkPlayer.ApendMissionNPC(npc_vnum);
			}
			return true;
		}
		case MISSION_GC_SUBHEADER_UPDATE_STATUS:
		{
			TPacketGCMissionStatus status;
			if (!Recv(sizeof(TPacketGCMissionStatus), &status))
				return false;

			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_MissionRefreshStatus", Py_BuildValue("(ii)", status.returned, status.time));
			return true;
		}
		case MISSION_GC_SUBHEADER_CLOSE:
		{
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_MissionClose", Py_BuildValue("()"));
			return true;
		}
		case MISSION_GC_SUBHEADER_REWARD:
		{
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_MissionDisplayReward", Py_BuildValue("()"));
			return true;
		}
		default:
		{
			TraceError("RecvMissionPacket: unknown subheader %d", packet.subheader);
		}
	}

	return true;
}
#endif
