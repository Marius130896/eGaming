/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_FactiuniSystem_included
	#endinput
#else
	#define GF_FactiuniSystem_included
#endif

stock LoadFactions() {
	mysql_tquery(connectionHandle, "SELECT * FROM factions", "LoadFactionsThread", "d", FACTIONS_THREAD_ID);
	return true;
}

function LoadFactionsThread() {
	rows = cache_num_rows();
	if(rows) {
		for(new i = 0; i < rows; i ++) {
			FactionInfo[i][fSQLID] = cache_get_row_int(i, 0);
			cache_get_row(i, 1, FactionInfo[i][fName], .max_len = MAX_FACTION_NAME);
			FactionInfo[i][fSpawnx] = cache_get_row_float(i, 2);
			FactionInfo[i][fSpawny] = cache_get_row_float(i, 3);
			FactionInfo[i][fSpawnz] = cache_get_row_float(i, 4);
			FactionInfo[i][fSpawnrot] = cache_get_row_float(i, 5);
			FactionInfo[i][fWeapon1] = cache_get_row_int(i, 6);
			FactionInfo[i][fAmmo1] = cache_get_row_int(i, 7);
			FactionInfo[i][fWeapon2] = cache_get_row_int(i, 8);
			FactionInfo[i][fAmmo2] = cache_get_row_int(i, 9);
			FactionInfo[i][fWeapon3] = cache_get_row_int(i, 10);
			FactionInfo[i][fAmmo3] = cache_get_row_int(i, 11);
			FactionInfo[i][fHQEnterx] = cache_get_row_float(i, 12);
			FactionInfo[i][fHQEntery] = cache_get_row_float(i, 13);
			FactionInfo[i][fHQEnterz] = cache_get_row_float(i, 14);
			FactionInfo[i][fHQExitx] = cache_get_row_float(i, 15);
			FactionInfo[i][fHQExity] = cache_get_row_float(i, 16);
			FactionInfo[i][fHQExitz] = cache_get_row_float(i, 17);
			FactionInfo[i][fInterior] = cache_get_row_int(i, 18);
			FactionInfo[i][fVirtualWorld] = cache_get_row_int(i, 19);
			cache_get_row(i, 20, FactionInfo[i][fText], .max_len = MAXO_TEXT);
			FactionInfo[i][fPickupModel] = cache_get_row_int(i, 21);
			cache_get_row(i, 22, FactionInfo[i][fRank0], .max_len = MAX_RANK_NAME);
			cache_get_row(i, 23, FactionInfo[i][fRank1], .max_len = MAX_RANK_NAME);
			cache_get_row(i, 24, FactionInfo[i][fRank2], .max_len = MAX_RANK_NAME);
			cache_get_row(i, 25, FactionInfo[i][fRank3], .max_len = MAX_RANK_NAME);
			cache_get_row(i, 26, FactionInfo[i][fRank4], .max_len = MAX_RANK_NAME);
			cache_get_row(i, 27, FactionInfo[i][fRank5], .max_len = MAX_RANK_NAME);
			cache_get_row(i, 28, FactionInfo[i][fRank6], .max_len = MAX_RANK_NAME);
			cache_get_row(i, 29, FactionInfo[i][fAnnounce], .max_len = MAXO_TEXT);
			FactionInfo[i][fSpawnx2] = cache_get_row_float(i, 30);
			FactionInfo[i][fSpawny2] = cache_get_row_float(i, 31);
			FactionInfo[i][fSpawnz2] = cache_get_row_float(i, 32);
			FactionInfo[i][fSpawnrot2] = cache_get_row_float(i, 33);
			FactionInfo[i][fTREnterx] = cache_get_row_float(i, 34);
			FactionInfo[i][fTREntery] = cache_get_row_float(i, 35);
			FactionInfo[i][fTREnterz] = cache_get_row_float(i, 36);
			FactionInfo[i][fTRExitx] = cache_get_row_float(i, 37);
			FactionInfo[i][fTRExity] = cache_get_row_float(i, 38);
			FactionInfo[i][fTRExitz] = cache_get_row_float(i, 39);
			FactionInfo[i][fTRInterior] = cache_get_row_int(i, 40);
			cache_get_row(i, 41, FactionInfo[i][fTextTR], .max_len = MAXO_TEXT);
			FactionInfo[i][fApplication] = cache_get_row_int(i, 42);
			FactionInfo[i][fFactionLevel] = cache_get_row_int(i, 43);
			cache_get_row(i, 44, FactionInfo[i][fFactionColor], .max_len = 6);

			#if defined _stream_pickups
				FactionInfo[i][fPickupHQ] = CreateDynamicPickup(FactionInfo[i][fPickupModel], 23, FactionInfo[i][fHQEnterx], FactionInfo[i][fHQEntery], FactionInfo[i][fHQEnterz]);
				FactionInfo[i][fPickupTR] = CreateDynamicPickup(FactionInfo[i][fPickupModel], 23, FactionInfo[i][fTREnterx], FactionInfo[i][fTREntery], FactionInfo[i][fTREnterz]);
			#else
				FactionInfo[i][fPickupHQ] = CreatePickup(FactionInfo[i][fPickupModel], 23, FactionInfo[i][fHQEnterx], FactionInfo[i][fHQEntery], FactionInfo[i][fHQEnterz]);
				FactionInfo[i][fPickupTR] = CreatePickup(FactionInfo[i][fPickupModel], 23, FactionInfo[i][fTREnterx], FactionInfo[i][fTREntery], FactionInfo[i][fTREnterz]);
			#endif
		}
		printf("LoadFactionsThread() - called (%d factions loaded).", rows);
	}
	return true;
}

stock SendPlayerMessage(Float:radi, playerid, string[], color) {
	if(gPlayerLogged{playerid}) {
		foreach(Player, i) {
			if(gPlayerLogged{i}) {
				new Float:posx, Float:posy, Float:posz;
				GetPlayerPos(i, posx, posy, posz);
				if(GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid)) {
					if(IsPlayerInRangeOfPoint(playerid, radi, posx, posy, posz))
						SendClientMessage(i, color, string);
				}
			}
		}
	}
	return true;
}

COMMAND:radio(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(IsPlayerMDepartment(playerid)) {
		if(!sscanf(params, "s[75]", params)) {
			if(strlen(params) < 75) {
				if(PlayerInfo[playerid][pMute])
					return IsPlayerSilent();
				switch(PlayerInfo[playerid][pFactiune]) {
					case FACT_LSPD:
					{
						switch(PlayerInfo[playerid][pRank]) {
							case 1: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_LSPD][fRank1], PlayerName(playerid), params);
							case 2: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_LSPD][fRank2], PlayerName(playerid), params);
							case 3: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_LSPD][fRank3], PlayerName(playerid), params);
							case 4: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_LSPD][fRank4], PlayerName(playerid), params);
							case 5: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_LSPD][fRank5], PlayerName(playerid), params);
							case 6: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_LSPD][fRank6], PlayerName(playerid), params);
						}
						SendFamilyMessage(COLOR_RADIO, string, FACT_LSPD);
					}
					case FACT_FBI:
					{
						switch(PlayerInfo[playerid][pRank]) {
							case 1: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_FBI][fRank1], PlayerName(playerid), params);
							case 2: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_FBI][fRank2], PlayerName(playerid), params);
							case 3: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_FBI][fRank3], PlayerName(playerid), params);
							case 4: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_FBI][fRank4], PlayerName(playerid), params);
							case 5: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_FBI][fRank5], PlayerName(playerid), params);
							case 6: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_FBI][fRank6], PlayerName(playerid), params);
						}
						SendFamilyMessage(COLOR_RADIO, string, FACT_FBI);
					}
					case FACT_MEDIC:
					{
						switch(PlayerInfo[playerid][pRank]) {
							case 1: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_MEDIC][fRank1], PlayerName(playerid), params);
							case 2: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_MEDIC][fRank2], PlayerName(playerid), params);
							case 3: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_MEDIC][fRank3], PlayerName(playerid), params);
							case 4: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_MEDIC][fRank4], PlayerName(playerid), params);
							case 5: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_MEDIC][fRank5], PlayerName(playerid), params);
							case 6: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_MEDIC][fRank6], PlayerName(playerid), params);
						}
						SendFamilyMessage(COLOR_RADIO, string, FACT_MEDIC);
					}
				}
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/r(adio) [message]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG/Medic.");
	return true;
}

COMMAND:r(playerid, params[]) {
	return cmd_radio(playerid, params);
}

COMMAND:departments(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(IsPlayerMDepartment(playerid)) {
		if(!sscanf(params, "s[75]", params)) {
			if(strlen(params) < 75) {
				if(PlayerInfo[playerid][pMute])
					return IsPlayerSilent();
				switch(PlayerInfo[playerid][pFactiune]) {
					case FACT_LSPD:
					{
						switch(PlayerInfo[playerid][pRank]) {
							case 1: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_LSPD][fRank1], PlayerName(playerid), params);
							case 2: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_LSPD][fRank2], PlayerName(playerid), params);
							case 3: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_LSPD][fRank3], PlayerName(playerid), params);
							case 4: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_LSPD][fRank4], PlayerName(playerid), params);
							case 5: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_LSPD][fRank5], PlayerName(playerid), params);
							case 6: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_LSPD][fRank6], PlayerName(playerid), params);
						}
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_LSPD);
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_FBI);
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_MEDIC);
					}
					case FACT_FBI:
					{
						switch(PlayerInfo[playerid][pRank]) {
							case 1: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_FBI][fRank1], PlayerName(playerid), params);
							case 2: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_FBI][fRank2], PlayerName(playerid), params);
							case 3: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_FBI][fRank3], PlayerName(playerid), params);
							case 4: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_FBI][fRank4], PlayerName(playerid), params);
							case 5: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_FBI][fRank5], PlayerName(playerid), params);
							case 6: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_FBI][fRank6], PlayerName(playerid), params);
						}
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_FBI);
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_LSPD);
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_MEDIC);
					}
					case FACT_MEDIC:
					{
						switch(PlayerInfo[playerid][pRank]) {
							case 1: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_MEDIC][fRank1], PlayerName(playerid), params);
							case 2: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_MEDIC][fRank2], PlayerName(playerid), params);
							case 3: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_MEDIC][fRank3], PlayerName(playerid), params);
							case 4: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_MEDIC][fRank4], PlayerName(playerid), params);
							case 5: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_MEDIC][fRank5], PlayerName(playerid), params);
							case 6: format(string, MAXO_TEXT, "*** (( %s %s: %s, over. )) ***", FactionInfo[FACT_MEDIC][fRank6], PlayerName(playerid), params);
						}
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_MEDIC);
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_FBI);
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_LSPD);
					}
				}
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/r(adio) [message]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG/Medic.");
	return true;
}

COMMAND:d(playerid, params[]) {
	return cmd_departments(playerid, params);
}

COMMAND:faction(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(IsPlayerMemberFaction(playerid)) {
		if(!sscanf(params, "s[75]", params)) {
			if(strlen(params) < 75) {
				if(PlayerInfo[playerid][pMute])
					return IsPlayerSilent();
				switch(PlayerInfo[playerid][pFactiune]) {
					case FACT_LCN:
					{
						switch(PlayerInfo[playerid][pRank]) {
							case 1: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_LCN][fRank1], PlayerName(playerid), params);
							case 2: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_LCN][fRank2], PlayerName(playerid), params);
							case 3: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_LCN][fRank3], PlayerName(playerid), params);
							case 4: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_LCN][fRank4], PlayerName(playerid), params);
							case 5: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_LCN][fRank5], PlayerName(playerid), params);
							case 6: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_LCN][fRank6], PlayerName(playerid), params);
						}
						SendFamilyMessage(COLOR_FAMILY, string, FACT_LCN);
					}
					case FACT_YKZ:
					{
						switch(PlayerInfo[playerid][pRank]) {
							case 1: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_YKZ][fRank1], PlayerName(playerid), params);
							case 2: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_YKZ][fRank2], PlayerName(playerid), params);
							case 3: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_YKZ][fRank3], PlayerName(playerid), params);
							case 4: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_YKZ][fRank4], PlayerName(playerid), params);
							case 5: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_YKZ][fRank5], PlayerName(playerid), params);
							case 6: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_YKZ][fRank6], PlayerName(playerid), params);
						}
						SendFamilyMessage(COLOR_FAMILY, string, FACT_YKZ);
					}
					case FACT_HITMAN:
					{
						switch(PlayerInfo[playerid][pRank]) {
							case 1: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_HITMAN][fRank1], PlayerName(playerid), params);
							case 2: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_HITMAN][fRank2], PlayerName(playerid), params);
							case 3: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_HITMAN][fRank3], PlayerName(playerid), params);
							case 4: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_HITMAN][fRank4], PlayerName(playerid), params);
							case 5: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_HITMAN][fRank5], PlayerName(playerid), params);
							case 6: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_HITMAN][fRank6], PlayerName(playerid), params);
						}
						SendFamilyMessage(COLOR_FAMILY, string, FACT_HITMAN);
					}
					case FACT_CNN:
					{
						switch(PlayerInfo[playerid][pRank]) {
							case 1: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_CNN][fRank1], PlayerName(playerid), params);
							case 2: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_CNN][fRank2], PlayerName(playerid), params);
							case 3: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_CNN][fRank3], PlayerName(playerid), params);
							case 4: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_CNN][fRank4], PlayerName(playerid), params);
							case 5: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_CNN][fRank5], PlayerName(playerid), params);
							case 6: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_CNN][fRank6], PlayerName(playerid), params);
						}
						SendFamilyMessage(COLOR_FAMILY, string, FACT_CNN);
					}
					case FACT_TAXI:
					{
						switch(PlayerInfo[playerid][pRank]) {
							case 1: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_TAXI][fRank1], PlayerName(playerid), params);
							case 2: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_TAXI][fRank2], PlayerName(playerid), params);
							case 3: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_TAXI][fRank3], PlayerName(playerid), params);
							case 4: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_TAXI][fRank4], PlayerName(playerid), params);
							case 5: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_TAXI][fRank5], PlayerName(playerid), params);
							case 6: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_TAXI][fRank6], PlayerName(playerid), params);
						}
						SendFamilyMessage(COLOR_FAMILY, string, FACT_TAXI);
					}
					case FACT_BLOODS:
					{
						switch(PlayerInfo[playerid][pRank]) {
							case 1: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_BLOODS][fRank1], PlayerName(playerid), params);
							case 2: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_BLOODS][fRank2], PlayerName(playerid), params);
							case 3: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_BLOODS][fRank3], PlayerName(playerid), params);
							case 4: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_BLOODS][fRank4], PlayerName(playerid), params);
							case 5: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_BLOODS][fRank5], PlayerName(playerid), params);
							case 6: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_BLOODS][fRank6], PlayerName(playerid), params);
						}
						SendFamilyMessage(COLOR_FAMILY, string, FACT_BLOODS);
					}
					case FACT_CRIPS:
					{
						switch(PlayerInfo[playerid][pRank]) {
							case 1: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_CRIPS][fRank1], PlayerName(playerid), params);
							case 2: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_CRIPS][fRank2], PlayerName(playerid), params);
							case 3: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_CRIPS][fRank3], PlayerName(playerid), params);
							case 4: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_CRIPS][fRank4], PlayerName(playerid), params);
							case 5: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_CRIPS][fRank5], PlayerName(playerid), params);
							case 6: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_CRIPS][fRank6], PlayerName(playerid), params);
						}
						SendFamilyMessage(COLOR_FAMILY, string, FACT_CRIPS);
					}
					case FACT_FMA:
					{
						switch(PlayerInfo[playerid][pRank]) {
							case 1: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_FMA][fRank1], PlayerName(playerid), params);
							case 2: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_FMA][fRank2], PlayerName(playerid), params);
							case 3: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_FMA][fRank3], PlayerName(playerid), params);
							case 4: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_FMA][fRank4], PlayerName(playerid), params);
							case 5: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_FMA][fRank5], PlayerName(playerid), params);
							case 6: format(string, MAXO_TEXT, "*** (( %s %s: %s. )) ***", FactionInfo[FACT_FMA][fRank6], PlayerName(playerid), params);
						}
						SendFamilyMessage(COLOR_FAMILY, string, FACT_FMA);
					}
				}
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/f(action) [message]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command.");
	return true;
}

COMMAND:f(playerid, params[]) {
	return cmd_faction(playerid, params);
}

// End Of File ...
