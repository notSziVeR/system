// find:
		case HEADER_CG_DRAGON_SOUL_REFINE:
			{
				[...]
			}
			break;

// paste below:
#ifdef __MISSION__
		case HEADER_CG_MISSION:
			if ((iExtraLen = Mission(ch, c_pData, m_iBufferLeft)) < 0)
				return -1;
			break;
#endif

// add at the end of the file:
#ifdef __MISSION__
int CInputMain::Mission(LPCHARACTER ch, const char* data, size_t uiBytes)
{
	if (!ch || !ch->GetDesc())
		return -1;

	TPacketCGMission* p = (TPacketCGMission*)data;

	if (uiBytes < sizeof(TPacketCGMission))
		return -1;

	const char* c_pData = data + sizeof(TPacketCGMission);
	uiBytes -= sizeof(TPacketCGMission);

	switch (p->subheader)
	{
		case MISSION_CG_SUBHEADER_OPEN:
		{
			if (uiBytes < sizeof(DWORD))
				return -1;

			DWORD npc_vnum = *(DWORD*)c_pData;
			c_pData += sizeof(DWORD);
			uiBytes -= sizeof(DWORD);

			sys_log(0, "Mission: npc_vnum %d", npc_vnum);

			const auto mission = ch->GetMission(npc_vnum);
			if (!mission)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("MISSION INFO NOT FOUND"));
				return sizeof(DWORD);
			}

			TPacketGCMission header{};
			header.header = HEADER_GC_MISSION;
			header.subheader = MISSION_GC_SUBHEADER_SET_DATA;
			header.size = sizeof(TPacketGCMission) + sizeof(TPacketGCMissionInfo);

			TPacketGCMissionInfo packet{};
			packet.required_item.vnum = mission->required_item.vnum;
			packet.required_item.count = mission->required_item.count;
			packet.level = mission->level;
			packet.chance = mission->chance;
			packet.time = mission->time;
			packet.map_index = mission->map_index;

			packet.mob_count = mission->mob_vnum.size();
			packet.affect_count = mission->reward_affect.size();
			packet.item_count = mission->reward_item.size();

			TEMP_BUFFER buf;
			for (const auto mob_vnum : mission->mob_vnum)
			{
				buf.write(&mob_vnum, sizeof(DWORD));
				header.size += sizeof(DWORD);
			}
			
			for (auto& affect : mission->reward_affect)
			{
				TPacketGCMissionAffect it{};
				it.index = affect.index;
				it.value = affect.value;

				buf.write(&it, sizeof(TPacketGCMissionAffect));
				header.size += sizeof(TPacketGCMissionAffect);
			}
			
			for (auto& item : mission->reward_item)
			{
				TPacketGCMissionItem it{};
				it.vnum = item.vnum;
				it.count = item.count;

				buf.write(&it, sizeof(TPacketGCMissionItem));
				header.size += sizeof(TPacketGCMissionItem);
			}

			const auto desc = ch->GetDesc();

			desc->BufferedPacket(&header, sizeof(TPacketGCMission));
			desc->Packet(&packet, sizeof(TPacketGCMissionInfo));
			desc->Packet(buf.read_peek(), buf.size());

			auto returned = ch->GetReturnedCount(npc_vnum);

			TPacketGCMission header2;
			header2.header = HEADER_GC_MISSION;
			header2.subheader = MISSION_GC_SUBHEADER_UPDATE_STATUS;
			header2.size = sizeof(TPacketGCMission) + sizeof(TPacketGCMissionStatus);

			TPacketGCMissionStatus packet2;
			packet2.returned = static_cast<BYTE>(returned);
			packet2.time = ch->GetMissionTime(npc_vnum);

			desc->BufferedPacket(&header2, sizeof(TPacketGCMission));
			desc->Packet(&packet2, sizeof(TPacketGCMissionStatus));

			return sizeof(DWORD);
		}
			break;

		case MISSION_CG_SUBHEADER_RETURN:
		case MISSION_CG_SUBHEADER_RETURN_ALL:
		{
			if (uiBytes < sizeof(DWORD))
				return -1;

			DWORD npc_vnum = *(DWORD*)c_pData;
			c_pData += sizeof(DWORD);
			uiBytes -= sizeof(DWORD);

			if (uiBytes < sizeof(DWORD))
				return -1;

			DWORD elixir_vnum = *(DWORD*)c_pData;
			c_pData += sizeof(DWORD);
			uiBytes -= sizeof(DWORD);

			const auto mission = ch->GetMission(npc_vnum);
			if (!mission)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("MISSION INFO NOT FOUND"));
				return sizeof(DWORD) + sizeof(DWORD);
			}

			if (ch->GetLevel() < mission->level)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("MISSION LEVEL TOO LOW"));
				return sizeof(DWORD) + sizeof(DWORD);
			}

			const auto count = (p->subheader == MISSION_CG_SUBHEADER_RETURN_ALL) ? mission->required_item.count - ch->GetReturnedCount(npc_vnum) : 1;

			if (ch->CountSpecifyItem(mission->required_item.vnum) < count)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("MISSION NO ITEM"));
				return sizeof(DWORD) + sizeof(DWORD);
			}			
	
			int wait_time = ch->GetMissionTime(npc_vnum);
			if (wait_time > get_global_time())
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("MISSION WAIT"));
				return sizeof(DWORD) + sizeof(DWORD);
			}

			int elixir_count = 0;
			int chance_boost = 0;

			if (elixir_vnum == MISSION_ELIXIR_25 || elixir_vnum == MISSION_ELIXIR_50)
			{
				elixir_count = ch->CountSpecifyItem(elixir_vnum);
				switch (elixir_vnum)
				{
					case MISSION_ELIXIR_25:
						chance_boost = 25;
						break;
					case MISSION_ELIXIR_50:
						chance_boost = 50;
						break;
				}
			}

			auto returned = 0;
			int total_time = 0;
			const auto desc = ch->GetDesc();
			auto success = 0;

			for (int i = 0; i < count; i++)
			{
				returned = ch->GetReturnedCount(npc_vnum);
				total_time += mission->time;

				if (elixir_count)
				{
					elixir_count--;
					ch->RemoveSpecifyItem(elixir_vnum, 1);
				}
				else
				{
					chance_boost = 0;
				}

				const auto chance = fnumber(0, 100);
				if (chance < mission->chance + chance_boost)
				{
					returned++;
					success++;
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("MISSION RETURNED SUCCESSFULLY"));
					ch->SetReturnedCount(npc_vnum, returned);

					if (returned == mission->required_item.count)
					{
						for (auto& affect : mission->reward_affect)
							ch->AddAffect(AFFECT_COLLECT, affect.index, affect.value, 0, INFINITE_AFFECT_DURATION, 0, false);

						for (auto& item : mission->reward_item)
							const auto it = ch->AutoGiveItem(item.vnum, item.count, -1, false);

						// since we don't have apply texts here in game, let's send 
						TPacketGCMission header2;
						header2.header = HEADER_GC_MISSION;
						header2.subheader = MISSION_GC_SUBHEADER_REWARD;
						header2.size = sizeof(TPacketGCMission);
						
						desc->Packet(&header2, sizeof(TPacketGCMission));

						ch->SetReturnedCount(npc_vnum, 0);
						ch->SetMissionTime(npc_vnum, 0);
						
						auto index = ch->GetMissionIndex(npc_vnum);
						index++;
						ch->SetMissionIndex(npc_vnum, index);

						const auto new_mission = CMissionManager::instance().GetMission(npc_vnum, index);
						ch->SetMission(npc_vnum, new_mission);

						if (new_mission)
						{
							if (ch->GetLevel() >= new_mission->level)
								ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("MISSION YOU CAN START NOW"));
							else
								ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("MISSION AVAILABLE NEXT MISSION"));

							TPacketCGMission header{};
							header.header = HEADER_CG_MISSION;
							header.subheader = MISSION_CG_SUBHEADER_OPEN;
							
							char buffer[sizeof(TPacketCGMission) + sizeof(DWORD)];

							memcpy(buffer, &header, sizeof(TPacketCGMission));
							memcpy(buffer + sizeof(TPacketCGMission), &npc_vnum, sizeof(DWORD));

							Mission(ch, buffer, sizeof(buffer));
						}
						else
						{
							ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("MISSION NO MORE MISSIONS"));

							TPacketGCMission header2;
							header2.header = HEADER_GC_MISSION;
							header2.subheader = MISSION_GC_SUBHEADER_CLOSE;
							header2.size = sizeof(TPacketGCMission);

							desc->Packet(&header2, sizeof(TPacketGCMission));
						}

						break;
					}
				}
				else
				{
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("MISSION RETURNED WRONG"));
				}

				ch->RemoveSpecifyItem(mission->required_item.vnum, 1);
			}

			ch->SetMissionTime(npc_vnum, get_global_time() + total_time);
			if (count > 1)
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("MISSION RETURNED %d / %d"), success, count);

			TPacketGCMission header;
			header.header = HEADER_GC_MISSION;
			header.subheader = MISSION_GC_SUBHEADER_UPDATE_STATUS;
			header.size = sizeof(TPacketGCMission) + sizeof(TPacketGCMissionStatus);

			TPacketGCMissionStatus packet;
			packet.returned = static_cast<BYTE>(returned);
			packet.time = ch->GetMissionTime(npc_vnum);

			desc->BufferedPacket(&header, sizeof(TPacketGCMission));
			desc->Packet(&packet, sizeof(TPacketGCMissionStatus));

			return sizeof(DWORD) + sizeof(DWORD);
		}
			break;

		default:
			break;
	}

	return 0;
}
#endif
