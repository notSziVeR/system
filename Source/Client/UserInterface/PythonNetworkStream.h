// find:
		void __BettingGuildWar_SetBettingMoney(UINT uBettingMoney);

// paste below:
#ifdef ENABLE_MISSION
	public:
		bool SendMissionPacket(BYTE subheader, DWORD npc_vnum, DWORD item_vnum);
	private:
		bool RecvMissionPacket();
#endif