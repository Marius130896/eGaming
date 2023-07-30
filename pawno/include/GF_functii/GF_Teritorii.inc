/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_Teritorii_included
	#endinput
#else
	#define GF_Teritorii_included
#endif

new nodmzone, nodmzone2;

#define COLOR_FLASHTURF 0xFF000080
#define COLOR_BORDER 0x00000060

#define MAX_ZONE_NAME 64
enum Zone {
	ZoneSQLID,
	ZoneName[MAX_ZONE_NAME],
	Float:ZoneMinX,
	Float:ZoneMinY,
	Float:ZoneMaxX,
	Float:ZoneMaxY
};
#define MAX_ZONE (34)
new ZoneInfo[MAX_ZONE][Zone];

#define INVALID_TURF_ID (-1)
#define MAX_TURF_NAME (25)
#define PLAYER_IN_TURF 			45			// numarul de secunde a unui player pe un teritoriu
enum Turf {
	TurfSQLID,
	TurfOwner,
	TurfName[MAX_TURF_NAME],
	Float:TurfMinX,
	Float:TurfMinY,
	Float:TurfMaxX,
	Float:TurfMaxY,
	border[4],
	/* Rival-Wars */
	TurfWarStarted,
	TurfWarPause,
	TurfAttacker,
	TurfColor
};
#define MAX_TURFS (34)
new TurfInfo[MAX_TURFS][Turf];

enum teamInfo {
	LastAttack,
	InWar,
	TeamScore,
	StartWarTime,
	AttackPause
};
new TeamInfo[MAX_FACTIONS][teamInfo];

#tryinclude <GF_functii/GF_private/GF_TeritoriiSystem-private>

#if !defined GF_TeritoriiSystem_included
	stock LoadTurf() {
		return true;
	}
	function InitTurfRivalWars() {
		return true;
	}
	function InitSpawnZone() {
		return true;
	}
	stock IsPlayerInArea(playerid, Float:minx2, Float:miny2, Float:maxx2, Float:maxy2) {
		return false;
	}
	stock GetPlayerTurfID(playerid) {
		return true;
	}
	function SetPlayerTurfName(playerid) {
		return true;
	}
#endif

COMMAND:turfs(playerid, params[]) {
	if(showTurfs{playerid})
		HideTurfs(playerid);
	else
		ShowTurfs(playerid);
	showTurfs{playerid} = !showTurfs{playerid};
	return 1;
}

stock ShowTurfs(playerid) {
	new fID = PlayerInfo[playerid][pFactiune];
	for(new t; t < MAX_TURFS; t++) {
		GangZoneShowForPlayer(playerid, TurfInfo[t][TurfSQLID], TurfInfo[t][TurfColor]);
		GangZoneShowForPlayer(playerid, TurfInfo[t][border][0], COLOR_BORDER);
		GangZoneShowForPlayer(playerid, TurfInfo[t][border][1], COLOR_BORDER);
		GangZoneShowForPlayer(playerid, TurfInfo[t][border][2], COLOR_BORDER);
		GangZoneShowForPlayer(playerid, TurfInfo[t][border][3], COLOR_BORDER);
		if(TurfInfo[t][TurfWarStarted] > 0) {
			if(TurfInfo[t][TurfOwner] == fID || TurfInfo[t][TurfAttacker] == fID)
				GangZoneFlashForPlayer(playerid, TurfInfo[t][TurfSQLID], COLOR_FLASHTURF);
		}
	}
	return true;
}

stock HideTurfs(playerid) {
	new fID = PlayerInfo[playerid][pFactiune];
	for(new t; t < MAX_TURFS; t++) {
		if(TurfInfo[t][TurfWarStarted] > 0) {
			if(TurfInfo[t][TurfOwner] == fID || TurfInfo[t][TurfAttacker] == fID)
				GangZoneStopFlashForPlayer(playerid, t);
		}
		GangZoneHideForPlayer(playerid, TurfInfo[t][TurfSQLID]);
		GangZoneHideForPlayer(playerid, TurfInfo[t][border][0]);
		GangZoneHideForPlayer(playerid, TurfInfo[t][border][1]);
		GangZoneHideForPlayer(playerid, TurfInfo[t][border][2]);
		GangZoneHideForPlayer(playerid, TurfInfo[t][border][3]);
	}
	return true;
}

// End Of File ...
