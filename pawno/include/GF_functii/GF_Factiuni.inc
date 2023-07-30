/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_Factiuni_included
	#endinput
#else
	#define GF_Factiuni_included
#endif

#define MAX_FACTION_NAME (30)
#define MAX_RANK_NAME (30)
enum fInfo {
	fSQLID,
	fName[MAX_FACTION_NAME],
	Float:fSpawnx,
	Float:fSpawny,
	Float:fSpawnz,
	Float:fSpawnrot,
	fWeapon1,
	fAmmo1,
	fWeapon2,
	fAmmo2,
	fWeapon3,
	fAmmo3,
	Float:fHQEnterx,
	Float:fHQEntery,
	Float:fHQEnterz,
	Float:fHQExitx,
	Float:fHQExity,
	Float:fHQExitz,
	fInterior,
	fVirtualWorld,
	fText[MAXO_TEXT],
	fPickupModel,
	fPickupHQ,
	fPickupTR,
	fRank0[MAX_RANK_NAME],
	fRank1[MAX_RANK_NAME],
	fRank2[MAX_RANK_NAME],
	fRank3[MAX_RANK_NAME],
	fRank4[MAX_RANK_NAME],
	fRank5[MAX_RANK_NAME],
	fRank6[MAX_RANK_NAME],
	fAnnounce[MAXO_TEXT],
	Float:fSpawnx2,
	Float:fSpawny2,
	Float:fSpawnz2,
	Float:fSpawnrot2,
	Float:fTREnterx,
	Float:fTREntery,
	Float:fTREnterz,
	Float:fTRExitx,
	Float:fTRExity,
	Float:fTRExitz,
	fTRInterior,
	fTextTR[MAXO_TEXT],
	fApplication,
	fFactionLevel,
	fFactionColor[6]
};
#define MAX_FACTIONS (12)
new FactionInfo[MAX_FACTIONS][fInfo];

#tryinclude <GF_functii/GF_private/GF_FactiuniSystem-private>

#if !defined GF_FactiuniSystem_included
	stock LoadFactions() {
		return true;
	}
	function LoadFactionsThread() {
		return true;
	}
	stock SendPlayerMessage(Float:radi, playerid, string[], color) {
		return true;
	}
#endif

stock FactionsLog(playerid, string[]) {
	format(string, MAXO_TEXT2, "INSERT INTO faction_logs (Action, player) VALUES ('%s', '%d')", string, PlayerInfo[playerid][pSQLID]);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", ADDCHAT_THREAD_ID);
	clear.string(string);
	return true;
}

stock IsPlayerCop(playerid) {
	switch(PlayerInfo[playerid][pFactiune]) {
		case FACT_LSPD: return true;
		case FACT_FBI: return true;
	}
	return false;
}

stock IsPlayerMDepartment(playerid) {
	switch(PlayerInfo[playerid][pFactiune]) {
		case FACT_LSPD: return true;
		case FACT_FBI: return true;
		case FACT_MEDIC: return true;
	}
	return false;
}

stock IsPlayerMemberFaction(playerid) {
	switch(PlayerInfo[playerid][pFactiune]) {
		case FACT_LCN: return true;
		case FACT_YKZ: return true;
		case FACT_HITMAN: return true;
		case FACT_CNN: return true;
		case FACT_TAXI: return true;
		case FACT_BLOODS: return true;
		case FACT_CRIPS: return true;
		case FACT_FMA: return true;
	}
	return false;
}

stock IsPlayerGangster(playerid) {
	switch(PlayerInfo[playerid][pFactiune]) {
		case FACT_LCN: return true;
		case FACT_YKZ: return true;
		case FACT_BLOODS: return true;
		case FACT_CRIPS: return true;
	}
	return false;
}

stock SetPlayerFactionColor(playerid, factionid) {
	switch(factionid) {
		case FACT_CIVIL: return SetPlayerColor(playerid, COLOR_FACT_CIVIL);
		case FACT_LSPD: return  SetPlayerColor(playerid, COLOR_FACT_LSPD);
		case FACT_FBI: return SetPlayerColor(playerid, COLOR_FACT_FBI);
		case FACT_MEDIC: return SetPlayerColor(playerid, COLOR_FACT_MEDIC);
		case FACT_LCN: return SetPlayerColor(playerid, COLOR_FACT_LCN);
		case FACT_YKZ: return SetPlayerColor(playerid, COLOR_FACT_YKZ);
		case FACT_HITMAN: return SetPlayerColor(playerid, COLOR_FACT_HITMAN);
		case FACT_CNN: return SetPlayerColor(playerid, COLOR_FACT_CNN);
		case FACT_TAXI: return SetPlayerColor(playerid, COLOR_FACT_TAXI);
		case FACT_BLOODS: return SetPlayerColor(playerid, COLOR_FACT_BLOODS);
		case FACT_CRIPS: return SetPlayerColor(playerid, COLOR_FACT_CRIPS);
		case FACT_FMA: return SetPlayerColor(playerid, 0xA6009996);
	}
	return true;
}

stock FactionColor(factionid) {
	switch(factionid) {
		case FACT_CIVIL: return COLOR_WHITE;
		case FACT_LSPD: return COLOR_FACT_LSPD;
		case FACT_FBI: return COLOR_FACT_FBI;
		case FACT_MEDIC: return COLOR_FACT_MEDIC;
		case FACT_LCN: return COLOR_FACT_LCN;
		case FACT_YKZ: return COLOR_FACT_YKZ;
		case FACT_HITMAN: return COLOR_FACT_HITMAN;
		case FACT_CNN: return COLOR_FACT_CNN;
		case FACT_TAXI: return COLOR_FACT_TAXI;
		case FACT_BLOODS: return COLOR_FACT_BLOODS;
		case FACT_CRIPS: return COLOR_FACT_CRIPS;
		case FACT_FMA: return 0xA6009996;
	}
	return COLOR_FACT_CIVIL;
}


// End Of File ...