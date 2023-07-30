/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_ReferralSystem_included
	#endinput
#else
	#define GF_ReferralSystem_included
#endif

stock GetIDByName(name[ ]) {
	foreach(Player, i) {
		if(gPlayerLogged{i}) {
			if(!strcmp(PlayerName(i), name, true))
				return i;
		}
	}
    return INVALID_PLAYER_ID;
}

stock GetIDBySQLID(SQLID) {
	foreach(Player, i) {
		if(gPlayerLogged{i}) {
			if(SQLID == PlayerInfo[i][pSQLID])
				return i;
		}
	}
	return INVALID_PLAYER_ID;
}

function ValidReferral(extraid) {
	new string[MAXO_TEXT];
	rows = cache_num_rows();
	if(rows) {
		PlayerInfo[extraid][pReferralID] = cache_get_row_int(0, 0);
		format(string, MAXO_TEXT, " SERVER: So, you has been bring on server by Referral ID %d.", PlayerInfo[extraid][pReferralID]);
		SendClientMessage(extraid, -1, string);
		format(string, MAXO_TEXT, "UPDATE players SET ReferralID = %d WHERE ID = %d", PlayerInfo[extraid][pReferralID], PlayerInfo[extraid][pSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		ClearChatBox(extraid, 15);
		CreateCP(extraid,328.616,-1512.91,36.0391,1.5,checkpointNoAction,CP_NO_ACTION);
		TogglePlayerSpectating(extraid, false);
		TogglePlayerControllable(extraid, true);
		SetCameraBehindPlayer(extraid);
		SendClientMessage(extraid, COLOR_ORANGE, "Mergi la checkpointul rosu marcat pe minimap. Acolo vei sustine examenul pentru licenta de conducere.");
		PlayerInfo[extraid][pSkin] = 264;
		SetPlayerSkin(extraid, PlayerInfo[extraid][pSkin]);
		PlayerInfo[extraid][pTut] = 1;
		format(string, MAXO_TEXT, "UPDATE players SET Tut = 1 WHERE ID = %d", PlayerInfo[extraid][pSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		format(string, MAXO_TEXT2, "UPDATE players SET Skin = %d WHERE ID = %d", PlayerInfo[extraid][pSkin], PlayerInfo[extraid][pSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		SetPlayerSpawnInfo(extraid);
		new _rid;
		foreach(Player, i) {
			if(PlayerInfo[i][pSQLID] == PlayerInfo[extraid][pReferralID]) {
				_rid = i;
				break;
			}
		}
		if(_rid != INVALID_PLAYER_ID) {
			PlayerInfo[_rid][pExp] += 4;
			format(string, MAXO_TEXT, "Referral Bonus: "ALB"You received 4 Respect-Points because you recommended Referral ID %d.", PlayerInfo[extraid][pReferralID]);
			SendClientMessage(_rid, COLOR_YELLOW, string);
			GameTextForPlayer(_rid, "~g~Bonus!~n~~y~+4 ~w~Respect points.", 2500, 1);
		}
		format(string, MAXO_TEXT, "UPDATE players SET Respect = Respect + 4 WHERE ID = %d", PlayerInfo[extraid][pReferralID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		clear.string(string);
	} else ShowPlayerDialog(extraid, DIALOGID_REFERRAL_PLAYER, DIALOG_STYLE_INPUT, "Set your Referral", "This Referral ID is incorrect, please try again!\nIf you has beed bring on server by someone, type below, his Referral ID.\nIf you hasn't been bring by someone, press Skip button:", "Finish", "Skip");
	return true;
}

COMMAND:myreferrals(playerid, params[]) {
	new
		string[200];
	mysql_format(connectionHandle, string, sizeof(string), "SELECT Name, ReferralID, COALESCE(UNIX_TIMESTAMP(LastLogin), UNIX_TIMESTAMP(NOW())) FROM players WHERE ReferralID = %d", PlayerInfo[playerid][pSQLID]);
	mysql_tquery(connectionHandle, string, "ShowReferrals", "d", playerid);
	clear.string(string);
	return true;
}

function ShowReferrals(extraid) {
	rows = cache_num_rows();
	if(rows) {
		new string[MAXO_TEXT2], string2[528];
		strcat(string2, "Nr.\tName\tLast Login Date\n");
		for(new r; r < rows; r++) {
			new refConnect, refName[MAX_PLAYER_NAME];
			cache_get_row(r, 0, refName, .max_len = MAX_PLAYER_NAME);
			refConnect = cache_get_row_int(r, 2);
			format(string, MAXO_TEXT, "%d\t%s\t%s\n", r, refName, DateToTimestamp(refConnect, 1));
			strcat(string2, string);
		}
		ShowPlayerDialog(extraid, DIALOGID_NO_ACTION, DIALOG_STYLE_TABLIST_HEADERS, "My Referrals", string2, "Okay", "");
		clear.string(string);
		clear.string(string2);
	} else ShowPlayerDialog(extraid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "My Referrals", "You have bring 0 players.", "Okay", "");
	return true;
}

COMMAND:referralcollect(playerid, params[]) {
	new string[MAXO_TEXT];
	format(string, MAXO_TEXT, "Referral Bonus: "ALB"Bonus collected (Respect-Points: %d | Cash: $%s).", PlayerInfo[playerid][pReferralRespect], FormatNumber(PlayerInfo[playerid][pReferralCash], 0, ','));
	SendClientMessage(playerid, COLOR_YELLOW, string);
	if(PlayerInfo[playerid][pReferralRespect] > 0) {
		PlayerInfo[playerid][pExp] += PlayerInfo[playerid][pReferralRespect];
		PlayerInfo[playerid][pReferralRespect] = 0;
	}
	if(PlayerInfo[playerid][pReferralCash] > 0) {
		SafeGivePlayerMoney(playerid, PlayerInfo[playerid][pReferralCash]);
		PlayerInfo[playerid][pReferralCash] = 0;
	}
	mysql_format(connectionHandle, string, MAXO_TEXT2, "UPDATE players SET ReferralRespect = 0, ReferralCash = 0, Respect = %d WHERE ID = %d", PlayerInfo[playerid][pExp], PlayerInfo[playerid][pSQLID]);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	clear.string(string);
	return true;
}

function ReferralBonus(extraid, refID, refMoneys, refRespect) {
	rows = cache_num_rows();
	if(rows) {
		new
			string[MAXO_TEXT], refName[MAX_PLAYER_NAME],
			curMoneys, curRespect;
		cache_get_row(0, 1, refName, .max_len = MAX_PLAYER_NAME);
		curMoneys = cache_get_row_int(0, 81);
		curRespect = cache_get_row_int(0, 82);
		curMoneys += refMoneys;
		curRespect += refRespect;
		format(string, MAXO_TEXT, "UPDATE players SET ReferralCash = %d, ReferralRespect = %d WHERE ID = %d", curMoneys, curRespect, refID);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		new
			pID = GetIDByName(refName);
		if(pID != INVALID_PLAYER_ID) {
			PlayerInfo[pID][pReferralCash] += curMoneys;
			PlayerInfo[pID][pReferralRespect] += curRespect;
			format(string, MAXO_TEXT2, "Referral Bonus: "ALB"You received $%s and %d Respect-Points from %s, type /referralcollect.", FormatNumber(refMoneys, 0, ','), refRespect, PlayerName(extraid));
			SendClientMessage(pID, COLOR_YELLOW, string);
		}
		clear.string(string);
	}
	return true;
}

// End Of File ...
