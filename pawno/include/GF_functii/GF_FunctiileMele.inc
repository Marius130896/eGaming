/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_FunctiileMele_included
	#endinput
#else
	#define GF_FunctiileMele_included
#endif

stock ResetGBVar(playerid) {
	GoBackInfo[playerid][gbInterior] = 0;
	GoBackInfo[playerid][gbVirtualWorld] = 0;
	GoBackInfo[playerid][gbHouseID] = 0;
	GoBackInfo[playerid][gbBizzID] = 0;
	GoBackInfo[playerid][gbHealth] = 0.0;
	GoBackInfo[playerid][gbArmour] = 0.0;
	GoBackInfo[playerid][gbWeapons][0] = 0;
	GoBackInfo[playerid][gbWeapons][1] = 0;
	GoBackInfo[playerid][gbWeapons][2] = 0;
	GoBackInfo[playerid][gbWeapons][3] = 0;
	GoBackInfo[playerid][gbWeapons][4] = 0;
	GoBackInfo[playerid][gbWeapons][5] = 0;
	GoBackInfo[playerid][gbUsed] = false;
	return true;
}

stock ResetSpectateVar(playerid) {
	Spectated[playerid][Status] = false;
	Spectated[playerid][Command] = false;
	Spectated[playerid][IDj] = INVALID_PLAYER_ID;
	Spectated[playerid][Type] = ADMIN_SPEC_TYPE_NONE;
	return true;
}

stock StorePlayerData(playerid) {
	if(!GoBackInfo[playerid][gbUsed] || !Spectated[playerid][Status])
		GoBackHint();
	new Float:gbH, Float:gbA;
	GetPlayerHealth(playerid, gbH);
	GetPlayerArmour(playerid, gbA);
	GetPlayerPos(playerid, GoBackInfo[playerid][gbPos][0], GoBackInfo[playerid][gbPos][1], GoBackInfo[playerid][gbPos][2]);
	GetPlayerFacingAngle(playerid, GoBackInfo[playerid][gbPos][3]);
	GoBackInfo[playerid][gbInterior] = GetPlayerInterior(playerid);
	GoBackInfo[playerid][gbVirtualWorld] = GetPlayerVirtualWorld(playerid);
	GoBackInfo[playerid][gbHouseID] = PlayerInfo[playerid][pInHouseID];
	GoBackInfo[playerid][gbBizzID] = PlayerInfo[playerid][pInBizzID];
	GoBackInfo[playerid][gbHealth] = gbH;
	GoBackInfo[playerid][gbArmour] = gbA;
	GoBackInfo[playerid][gbUsed] = true;
	return true;
}

stock SetPlayerBack(playerid) {
	new vID = GetPlayerVehicleID(playerid);
	SafeSetPlayerInterior(playerid, GoBackInfo[playerid][gbInterior]);
	SafeSetPlayerVirtualWorld(playerid, GoBackInfo[playerid][gbVirtualWorld]);
	PlayerInfo[playerid][pInBizzID] = GoBackInfo[playerid][gbBizzID];
	PlayerInfo[playerid][pInHouseID] = GoBackInfo[playerid][gbHouseID];
	SetPlayerHealth(playerid, GoBackInfo[playerid][gbHealth]);
	SetPlayerArmour(playerid, GoBackInfo[playerid][gbArmour]);
	if(Spectated[playerid][Status])
		SetSpawnInfo(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pSkin], GoBackInfo[playerid][gbPos][0], GoBackInfo[playerid][gbPos][1], GoBackInfo[playerid][gbPos][2], GoBackInfo[playerid][gbPos][3], FactionInfo[PlayerInfo[playerid][pFactiune]][fWeapon1], FactionInfo[PlayerInfo[playerid][pFactiune]][fAmmo1], FactionInfo[PlayerInfo[playerid][pFactiune]][fWeapon2], FactionInfo[PlayerInfo[playerid][pFactiune]][fAmmo2], FactionInfo[PlayerInfo[playerid][pFactiune]][fWeapon3], FactionInfo[PlayerInfo[playerid][pFactiune]][fAmmo3]);
	else
	{
		if(vID) {
			SetVehiclePos(vID, GoBackInfo[playerid][gbPos][0], GoBackInfo[playerid][gbPos][1], GoBackInfo[playerid][gbPos][2]);
			LinkVehicleToInterior(vID, GoBackInfo[playerid][gbInterior]);
			SetVehicleVirtualWorld(vID, GoBackInfo[playerid][gbVirtualWorld]);
			PutPlayerInVehicle(playerid, vID, 0);
		}
		else
			SafeSetPlayerPos(playerid, GoBackInfo[playerid][gbPos][0], GoBackInfo[playerid][gbPos][1], GoBackInfo[playerid][gbPos][2]),
			SafeSetPlayerFacingAngle(playerid, GoBackInfo[playerid][gbPos][3]);
	}
	GoBackInfo[playerid][gbUsed] = false;
	return true;
}

stock HBroadCast(color, const string[], level) {
	foreach(Player, i) {
		if(PlayerInfo[i][pHelper] >= level)
			SendClientMessage(i, color, string);
	}
	return true;
}

stock ABroadCast(color, const string[], level) {
	foreach(Player, i) {
		if(IsPlayerConnected(i)) {
			if(PlayerInfo[i][pAdmin] >= level) {
				SendClientMessage(i, color, string);
			}
		}
	}
	return true;
}

stock OOCNews(color, const string[]) {
	foreach(Player, i) {
		if(gPlayerLogged{i})
			SendClientMessage(i, color, string);
	}
	return true;
}

stock SendFamilyMessage(color, const string[], faction) {
	foreach(Player, i) {
		if(PlayerInfo[i][pFactiune] == faction)
			SendClientMessage(i, color, string);
	}
	return true;
}

stock LBroadCast(color, const string[]) {
	foreach(Player, i) {
		if(PlayerInfo[i][pLeader] > FACT_CIVIL)
			SendClientMessage(i, color, string);
	}
	return true;
}

stock LiveChat(color, const string[]) {
	foreach(new i : Player) {
		if(TogglePlayerLive{i})
			SendClientMessage(i, color, string);
	}
	return true;
}

stock PlayerName(playerid) {
	new
		numelejucatorului[MAX_PLAYER_NAME];
	GetPlayerName(playerid, numelejucatorului, MAX_PLAYER_NAME);
	return numelejucatorului;
}

stock KickDeelay(playerid) {
	SetTimerEx("KickDeelayFunc", 1000, false, "u", playerid);
	return true;
}

function KickDeelayFunc(playerid) {
	Kick(playerid);
	return true;
}

stock isNumeric(const string[]) {
	new
		length = strlen(string);
	if (length == 0) return false;
	for (new i = 0; i < length; i++) {
		if((string[i] > '9' || string[i] < '0' && string[i] != '-' && string[i] != '+') || (string[i] == '-' && i != 0) || (string[i] == '+' && i != 0)) return false;
	}
	if(length == 1 && (string[0] == '-' || string[0] == '+')) return false;
	return true;
}

stock SetPlayerMoney(playerid, cash) {
	ResetPlayerMoney(playerid);
	return GivePlayerMoney(playerid, cash);
}

#if !defined PInfo_MAX_STRING
	#define PInfo_MAX_STRING 700
#endif

stock ShowPlayerInformation(playerid, title[], text[])
{
	if(PInfo_Active[playerid] == 1)
	{
		TextDrawDestroy(PInfo_TXT[playerid]);
		PInfo_TXT[playerid] = INVALID_TEXTDRAW_ID;
	}
	new
		string[PInfo_MAX_STRING];
	format(string, PInfo_MAX_STRING, "~r~%s ~n~~n~~y~%s ~n~~n~~w~Press ~g~RETURN ~w~to close this message box.", title, text);
	PInfo_TXT[playerid] = TextDrawCreate(20.000000, 155.000000, string);
	TextDrawBackgroundColor(PInfo_TXT[playerid], 255);
	TextDrawFont(PInfo_TXT[playerid], 1);
	TextDrawLetterSize(PInfo_TXT[playerid], 0.270000, 1.000000);
	TextDrawColor(PInfo_TXT[playerid], -1);
	TextDrawSetOutline(PInfo_TXT[playerid], 0);
	TextDrawSetProportional(PInfo_TXT[playerid], 1);
	TextDrawSetShadow(PInfo_TXT[playerid], 1);
	TextDrawUseBox(PInfo_TXT[playerid], 1);
	TextDrawBoxColor(PInfo_TXT[playerid], 555819339);
	TextDrawTextSize(PInfo_TXT[playerid], 209.000000, 0.000000);
	TextDrawShowForPlayer(playerid, PInfo_TXT[playerid]);
	PInfo_Active[playerid] = 1;
	clear.string(string);
	return true;
}

stock HidePlayerInformation(playerid)
{
	if(!(PInfo_Active[playerid] == 1)) return false;
	TextDrawHideForPlayer(playerid, PInfo_TXT[playerid]);
	TextDrawDestroy(PInfo_TXT[playerid]);
	PInfo_Active[playerid] = 0;
	PInfo_TXT[playerid] = INVALID_TEXTDRAW_ID;
	return true;
}

#define MAX_STRING 255

stock right(source[], len) {
	new retval[MAX_STRING], srclen;
	srclen = strlen(source);
	strmid(retval, source, srclen - len, srclen, MAX_STRING);
	return retval;
}

stock strmatch(const String1[], const String2[]) {
    if((strcmp(String1, String2, true, strlen(String2)) == 0) && (strlen(String2) == strlen(String1))) {
        return true;
    }
    else
    {
        return false;
    }
}

stock SafeResetPlayerInterior(playerid) {
	if(IsPlayerInInside(playerid)) {
		SafeSetPlayerInterior(playerid, 0);
		SafeSetPlayerVirtualWorld(playerid, 0);
		if(PlayerInfo[playerid][pInBizzID])
			PlayerInfo[playerid][pInBizzID] = 0;
		if(PlayerInfo[playerid][pInHouseID])
			PlayerInfo[playerid][pInHouseID] = 0;
		if(PlayerInfo[playerid][pInHQID])
			PlayerInfo[playerid][pInHQID] = FACT_CIVIL;
	}
	return true;
}


stock ClearChatBox(playerid, lines) {
	for(new i = 0; i < lines; i ++) {
		SendClientMessage(playerid, -1, " ");
	}
	return true;
}

stock SafeSetPlayerInterior(playerid, int) {
	SetPlayerInterior(playerid, int);
	PlayerInfo[playerid][pInterior] = int;
	return true;
}

stock SafeSetPlayerVirtualWorld(playerid, vid) {
	SetPlayerVirtualWorld(playerid, vid);
	PlayerInfo[playerid][pVirtualWorld] = vid;
	return true;
}

stock SafeSetPlayerPos(playerid, Float:X, Float:Y, Float:Z) {
	SetPlayerPos(playerid, X, Y, Z);
	return true;
}

stock SafeSetPlayerFacingAngle(playerid, Float:A) {
	SetPlayerFacingAngle(playerid, A);
	return true;
}

stock ConvertTime(secunde) {
   new
       string[16],
       minute = floatround(secunde / 60);
   secunde -= minute * 60;
   format(string, sizeof(string), "%d:%02d", minute, secunde);
   return string;
}

stock RandomEx(min, max) {
	return random(max - min) + min;
}

stock CheckName(playerid, name[]) {
	new
		count = 0,
		id = INVALID_PLAYER_ID,
		noap[MAX_PLAYER_NAME]; // n - name | o - of | a - all | p - players
	if(!isNumeric(name)) { // option 1 (string)
		foreach(Player, i) {
			if(!IsPlayerNPC(i)) {
				GetPlayerName(i, noap, sizeof(noap));
				if(strfind(noap, name, true) != -1) {
					count++;
					id = i;
				}
			}
		}
		if(count == 1) return PartialName[playerid][jucator_gasit] = id;
		else if(count > 1) {
		    SendClientMessage(playerid, COLOR_GRAD1, "Too many result,please be more specific.");
			return 0;
		}
		else {
			SendClientMessage(playerid, COLOR_GRAD1, "That player is not connected.");
			return 0;
		}
   	}
   	else { // option 2 (value)
   	    if(strval(name) != INVALID_PLAYER_ID) {
   	        if(IsPlayerConnected(strval(name))) {
				if(!IsPlayerNPC(strval(name))) {
					return PartialName[playerid][jucator_gasit] = strval(name);
				}
			}
   	        else {
   	            SendClientMessage(playerid, COLOR_GRAD2, "That player is not connected.");
				return 0;
			}
   	    }
   	    else {
   	        SendClientMessage(playerid, COLOR_GRAD1, "Invalid player.");
			return 0;
		}
   	}
	return 1;
}

stock SpecPStateOnDiscon(playerid) {
	foreach(Player,i) {
		if(Spectated[i][Type] != ADMIN_SPEC_TYPE_NONE) {
			if(Spectated[i][IDj] == playerid) SendClientMessage(playerid, COLOR_WHITE, "Your target has left server."), SpecStopSpec(i);
		}
	}
	return 1;
}

function SpecStreamUpdate(playerid, specplayerid, value) {
	SafeSetPlayerInterior(playerid, value);
	PlayerInfo[playerid][pVirtualWorld] = PlayerInfo[specplayerid][pVirtualWorld];
	SafeSetPlayerVirtualWorld(playerid, PlayerInfo[specplayerid][pVirtualWorld]);
	PlayerSpectatePlayer(playerid, specplayerid);
	return 1;
}

function CommandsLogs(string[]) {
	new entry[MAXO_TEXT2], File:hFile;
	format(entry, MAXO_TEXT2, "%s\r\n", string);
	hFile = fopen("Logs/Commands.log", io_append);
	fwrite(hFile, entry);
	fclose(hFile);
	clear.string(entry);
	return true;
}

stock IsInsideInterior(playerid) {
    return (PlayerInfo[playerid][pInterior] || PlayerInfo[playerid][pVirtualWorld]);
}

// End Of File ...
