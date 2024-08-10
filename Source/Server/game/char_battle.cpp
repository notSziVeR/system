// find:
	if (true == IsMonster() && 2493 == GetMobTable().dwVnum)
	{
		if (pkKiller && pkKiller->GetGuild())
			CDragonLairManager::instance().OnDragonDead( this, pkKiller->GetGuild()->GetID() );
		else
			sys_err("DragonLair: Dragon killed by nobody");
	}

// paste below:
#ifdef __MISSION__
	if (pkKiller && pkKiller->IsPC())
	{
		if (IsMonster())
		{
			float chance = fnumber(0.0, 100.0);
			for (const auto mission : pkKiller->GetMission())
			{
				if (!mission)
					continue;

				if (chance < mission->drop_chance)
				{
					pkKiller->AutoGiveItem(mission->required_item.vnum);
				}
			}
		}
	}
#endif