/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_TeritoriiSystem_included
	#endinput
#else
	#define GF_TeritoriiSystem_included
#endif

stock LoadTurf() {
	mysql_tquery(connectionHandle, "SELECT *  FROM turfs_rivalwars", "InitTurfRivalWars", "d", TURFS_THREAD_ID);
	mysql_tquery(connectionHandle, "SELECT * FROM spawn_zone", "InitSpawnZone", "d", ZONE_THREAD_ID);
	return true;
}

function InitTurfRivalWars() {
	rows = cache_num_rows();
	if(rows) {
		for(new i = 1; i < MAX_TURFS; i ++) {
			new j = i - 1;
			TurfInfo[i][TurfOwner] = cache_get_row_int(j, 1);
			cache_get_row(j, 2, TurfInfo[i][TurfName], MAX_TURF_NAME);
			TurfInfo[i][TurfMinX] = cache_get_row_float(j, 3);
			TurfInfo[i][TurfMinY] = cache_get_row_float(j, 4);
			TurfInfo[i][TurfMaxX] = cache_get_row_float(j, 5);
			TurfInfo[i][TurfMaxY] = cache_get_row_float(j, 6);
			switch(TurfInfo[i][TurfOwner]) {
				case FACT_LCN, FACT_YKZ, FACT_BLOODS, FACT_CRIPS: {
					TurfInfo[i][TurfWarPause] = cache_get_row_int(j, 7);
					TurfInfo[i][TurfColor] = FactionColor(TurfInfo[i][TurfOwner]);
					TurfInfo[i][TurfSQLID] = GangZoneCreate(TurfInfo[i][TurfMinX], TurfInfo[i][TurfMinY], TurfInfo[i][TurfMaxX], TurfInfo[i][TurfMaxY]);
					TurfInfo[i][border][0] = GangZoneCreate(TurfInfo[i][TurfMinX]-2.0, TurfInfo[i][TurfMinY], TurfInfo[i][TurfMinX]+2.0, TurfInfo[i][TurfMaxY]);
					TurfInfo[i][border][1] = GangZoneCreate(TurfInfo[i][TurfMinX]-2.0, TurfInfo[i][TurfMaxY]-2.0, TurfInfo[i][TurfMaxX], TurfInfo[i][TurfMaxY]+2.0);
					TurfInfo[i][border][2] = GangZoneCreate(TurfInfo[i][TurfMaxX]-2.0, TurfInfo[i][TurfMinY], TurfInfo[i][TurfMaxX]+2.0, TurfInfo[i][TurfMaxY]);
					TurfInfo[i][border][3] = GangZoneCreate(TurfInfo[i][TurfMinX]-2.0, TurfInfo[i][TurfMinY]-2.0, TurfInfo[i][TurfMaxX], TurfInfo[i][TurfMinY]+2.0);
				}
			}
		}
		printf("InitTurfRivalWars() - called (%d turfs loaded).", rows);
	}
	return true;
}

function InitSpawnZone() {
	rows = cache_num_rows();
	if(rows) {
		for(new i = 0; i < rows; i ++) {
			cache_get_row(i, 1, ZoneInfo[i][ZoneName], .max_len = MAX_ZONE_NAME);
			ZoneInfo[i][ZoneMinX] = cache_get_row_float(i, 2);
			ZoneInfo[i][ZoneMinY] = cache_get_row_float(i, 3);
			ZoneInfo[i][ZoneMaxX] = cache_get_row_float(i, 4);
			ZoneInfo[i][ZoneMaxY] = cache_get_row_float(i, 5);
			ZoneInfo[i][ZoneSQLID] = GangZoneCreate(ZoneInfo[i][ZoneMinX], ZoneInfo[i][ZoneMinY], ZoneInfo[i][ZoneMaxX], ZoneInfo[i][ZoneMaxY]);
		}
		printf("InitSpawnZone() - called (%d zones loaded).", rows);
	}
	return true;
}

stock IsPlayerInArea(playerid, Float:minx2, Float:miny2, Float:maxx2, Float:maxy2) {
	new Float:xa, Float:ya, Float:za;
	GetPlayerPos(playerid, xa, ya, za);
	if (xa > minx2 && xa < maxx2 && ya > miny2 && ya < maxy2) return true;
	return false;
}

stock GetPlayerTurfID(playerid) {
	for(new i = 0; i < MAX_TURFS; i ++) {
		if(IsPlayerInArea(playerid, TurfInfo[i][TurfMinX], TurfInfo[i][TurfMinY], TurfInfo[i][TurfMaxX], TurfInfo[i][TurfMaxY]))
			return i;
	}
	for(new i = 0; i < MAX_ZONE; i ++) {
		if(IsPlayerInArea(playerid, ZoneInfo[i][ZoneMinX], ZoneInfo[i][ZoneMinY], ZoneInfo[i][ZoneMaxX], ZoneInfo[i][ZoneMaxY]))
			return i;
	}
	return true;
}

function SetPlayerTurfName(playerid) {
	new string[MAXO_TEXT1], zoneid = GetPlayerTurfID(playerid);
	if(IsPlayerInArea(playerid, TurfInfo[zoneid][TurfMinX], TurfInfo[zoneid][TurfMinY], TurfInfo[zoneid][TurfMaxX], TurfInfo[zoneid][TurfMaxY])) {
		format(string, MAXO_TEXT1, "%s Turf.", TurfInfo[zoneid][TurfName]);
		TextDrawSetString(turftxt[playerid], string);
		TextDrawShowForPlayer(playerid, turftxt[playerid]);
	}
	else if(IsPlayerInArea(playerid, ZoneInfo[zoneid][ZoneMinX], ZoneInfo[zoneid][ZoneMinY], ZoneInfo[zoneid][ZoneMaxX], ZoneInfo[zoneid][ZoneMaxY])) {
		format(string, MAXO_TEXT1, "%s.", ZoneInfo[zoneid][ZoneName]);
		TextDrawSetString(turftxt[playerid], string);
		TextDrawShowForPlayer(playerid, turftxt[playerid]);
	}
	else
	{
		TextDrawSetString(turftxt[playerid], " ");
		TextDrawHideForPlayer(playerid, turftxt[playerid]);
	}
	clear.string(string);
	return true;
}

COMMAND:addturf(playerid, params[]) {
	new Float:turfpos[4], turfowner;
	if(IsPlayerFounder(playerid)) {
		if(!sscanf(params, "p<,>ffffd", turfpos[0], turfpos[1], turfpos[2], turfpos[3], turfowner)) {
			AddTurf(playerid, turfpos[0], turfpos[1], turfpos[2], turfpos[3], turfowner);
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/addturf [MixX] [MinY] MaxX] [MaxY] [TurfOwner]");
	} else NotAuthorized();
	return true;
}

stock AddTurf(playerid, Float:turfpos, Float:turfposy, Float:turfposz, Float:turfposa, owner) {
	new string[MAXO_TEXT2];
	format(string, MAXO_TEXT2, "INSERT INTO `turfs_rivalwars` (`TurfMinX`, `TurfMinY`, `TurfMaxX`, `TurfMaxY`, `TurfOwner`) VALUES ('%f', '%f', '%f', '%f', '%d')", turfpos, turfposy, turfposz, turfposa, owner);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", TURFS_THREAD_ID);
	SendClientMessage(playerid, COLOR_YELLOW, "[Turfs] {FFFFFF}Turf adaugat cu succes in baza de date.");
	clear.string(string);
	return true;
}

COMMAND:editnameturf(playerid, params[]) {
	new string[MAXO_TEXT], turf = GetPlayerTurfID(playerid);
	if(IsPlayerFounder(playerid)) {
		if(!sscanf(params, "p< >s[64]", params)) {
			if(strlen(params) > 1 || strlen(params) < 65) {
				if(IsPlayerInArea(playerid, TurfInfo[turf][TurfMinX], TurfInfo[turf][TurfMinY], TurfInfo[turf][TurfMaxX], TurfInfo[turf][TurfMaxY])) {
					strmid(TurfInfo[turf][TurfSQLID], params, 0, 1, MAXO_TEXT1);
					format(string, MAXO_TEXT, "UPDATE `turfs_rivalwars` SET `TurfName` = '%s' WHERE `SQLID` = '%d'", params, turf);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", TURFS_THREAD_ID);
					format(string, MAXO_TEXT, "AdmCmd: You has changed the TurfName (%s) for TurfSQLID %d.", params, turf);
					SendClientMessage(playerid, COLOR_LIGHTRED, string);
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "You must be on the turf, when use this command.");
			} else SendClientMessage(playerid, COLOR_YELLOW, "[Anti-Spam]: {FFFFFF}Line too long.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/editnameturf [name]");
	} else NotAuthorized();
	return true;
}

// End Of File ...
