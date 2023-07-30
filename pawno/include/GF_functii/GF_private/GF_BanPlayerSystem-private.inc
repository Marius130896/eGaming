/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_BanPlayerSystem_included
	#endinput
#else
	#define GF_BanPlayerSystem_included
#endif

enum KuramaBanEnum {
	banidSQLID,
	idinjoc,
	banmotiv[64],
	ipbanat[24],
	nickban[MAX_PLAYER_NAME]
};
new KuramaBanStruc[MAX_PLAYERS][KuramaBanEnum];

enum tc_method {
  tc_milliseconds,
  tc_seconds,
  tc_minutes
}

enum KuramaWarnEnum {
	warnid,
	idinjoc,
	warnnum,
	warnnick[MAX_PLAYER_NAME],
	warnmotiv[64],
	ipwarned[24]
};

new KuramaWarnStruc[MAX_PLAYERS][KuramaWarnEnum];

stock KuramaCheckBanned(playerid) {
	new query[MAXO_TEXT2];
	GameTextForPlayer(playerid, "~n~~r~"#server_name"~n~Checking ban status...", 5000, 4);
	format(query, sizeof(query), "SELECT `TimpExp`, `reason` FROM `bans` WHERE `Name` = '%s' AND `inactive` = 0 LIMIT 1", PlayerName(playerid));
	mysql_tquery(connectionHandle, query, "CheckBanned", "d", playerid);
	clear.string(query);
	return true;
}

stock strcpy2(dst[], src[]) {
	for (new i = 0; i < strlen(dst); i ++) {
		if(i < strlen(src)) dst[i] = src[i];
		else dst[i] = 0;
	}
}

stock mktime(hour,minute,second,day,month,year) {
	new timestamp2;

	timestamp2 = second + (minute * 60) + (hour * 3600);

	new days_of_month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	if ( ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0) ) {
		days_of_month[1] = 29; // Schaltjahr
	} else {
		days_of_month[1] = 28; // keins
	}

	new days_this_year = 0;
	days_this_year = --day;
	if(month > 1) { // No January Calculation, because its always the 0 past months
		for(new i=0; i<month-1;i++) {
			days_this_year += days_of_month[i];
		}
	}
	timestamp2 += days_this_year * 86400;

	for(new j=1970;j<year;j++) {
		timestamp2 += 31536000;
		if ( ((j % 4 == 0) && (j % 100 != 0)) || (j % 400 == 0) )  timestamp2 += 86400; // Schaltjahr + 1 Tag
	}

	return timestamp2;
}

function CheckBanned(extraid) {
	if(extraid != INVALID_PLAYER_ID) {
		if(cache_get_row_count()) {
			new momentan, timpban, result[40];
			getdate(gYears, gMonths, gDays);
			gettime(gHours, gMinutes, gSeconds);
			momentan = mktime(gHours, gMinutes, gSeconds, gDays, gMonths, gYears);
			timpban = cache_get_row_int(0, 4);
			cache_get_row(0, 6, result, .max_len = MAX_PLAYER_NAME+15);
			if(timpban > momentan) {
				new string2[160];
				format(string2, MAXO_TEXT, "xxx eG Guardian: You account is banned, Reason: %s. Will expire on %s. xxx", result, DateToTimestamp(timpban,3));
				SendClientMessage(extraid, COLOR_YELLOW, string2);
				format(string2, 160, "Motiv: %s\n\nBanul expira automat la:\n%s(ora serverului)\n\nPt. reclamatii: "#gamemode_forum"", result, DateToTimestamp(timpban,3));
				ShowPlayerDialog(extraid, DIALOGID_PLAYER_BANAT, DIALOG_STYLE_MSGBOX, "Login de pe Cont sau IP Banat!", string2, "Ok", "");
				KickDeelay(extraid);
				clear.string(string2);
			}
		}
	}
	return true;
}

function Unbanplayerip(playerid, ip[]) {
	new string[MAXO_TEXT];
	if(cache_num_rows()) {
		mysql_format(connectionHandle, string, sizeof(string), "UPDATE bans SET IP = '' WHERE ip = '%e'", ip);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		format(string, MAXO_TEXT, "AdmCmd: Admin %s has removed (offline) the ban from IP %s.", PlayerName(playerid), ip);
		ABroadCast(COLOR_YELLOW, string, 1);
		clear.string(string);
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "IP is not banned");
	}
	return true;
}

function Unbanplayer(playerid, name[]) {
	new string[MAXO_TEXT];
	if(cache_num_rows()) {
		mysql_format(connectionHandle, string, MAXO_TEXT, "UPDATE bans INNER JOIN players ON bans.player = players.ID SET Inactive = 1 WHERE players.Name = '%e'", name);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		format(string, MAXO_TEXT, "AdmCmd: Admin %s has removed (offline) the ban for %s's account.", PlayerName(playerid), name);
		ABroadCast(COLOR_YELLOW, string, 1);
		clear.string(string);
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "Name is not banned");
	}
	return true;
}

function Ban2(playerid,element,index) {
	new query[MAXO_TEXT2], banstr[MAXO_TEXT1], momentan, durata;
	getdate(gYears, gMonths, gDays);
	momentan = gettime(gHours, gMinutes, gSeconds);
	switch(index) {
		case 1: durata = mktime(gHours+element, gMinutes, gSeconds,gDays,gMonths,gYears), memcpy(banstr, "hours", 0, MAXO_TEXT1 * 4, MAXO_TEXT1 *4); // timp destinatie
		case 2: durata = mktime(gHours, gMinutes+element, gSeconds,gDays,gMonths,gYears), memcpy(banstr, "minutes", 0, MAXO_TEXT1 * 4, MAXO_TEXT1 *4); // timp destinatie
		case 3: durata = mktime(gHours, gMinutes, gSeconds+element,gDays,gMonths,gYears), memcpy(banstr, "seconds", 0, MAXO_TEXT1 * 4, MAXO_TEXT1 *4); // timp destinatie
		case 4: durata = mktime(gHours, gMinutes, gSeconds,gDays+element,gMonths,gYears), memcpy(banstr, "days", 0, MAXO_TEXT1 * 4, MAXO_TEXT1 *4); // timp destinatie
		case 5: durata = mktime(gHours, gMinutes, gSeconds,gDays,gMonths+element,gYears), memcpy(banstr, "months", 0, MAXO_TEXT1 * 4, MAXO_TEXT1 *4); // timp destinatie
		case 6: durata = mktime(gHours, gMinutes, gSeconds,gDays,gMonths,gYears+element), memcpy(banstr, "years", 0, MAXO_TEXT1 * 4, MAXO_TEXT1 *4); // timp destinatie
		default: return SendClientMessage(playerid,COLOR_LIGHTRED, "Eroare setare durata ban.");
	}
	mysql_format(connectionHandle, query, sizeof(query), "INSERT INTO bans (player,admin,TimpInit,TimpExp,ip,reason,Name) VALUES ('%d','%e','%d','%d','%s','%e','%e')",KuramaBanStruc[playerid][banidSQLID],PlayerName(playerid),momentan,durata,KuramaBanStruc[playerid][ipbanat],KuramaBanStruc[playerid][banmotiv],KuramaBanStruc[playerid][nickban]);
	mysql_tquery(connectionHandle, query, "NoReturnThread", "d", ADDBAN_THREAD_ID);
	if(IsPlayerConnected(KuramaBanStruc[playerid][idinjoc])) {
		if(strfind(KuramaBanStruc[playerid][banmotiv], "3Warn ->", true) == -1) {
			if(element == 10 && index == 6)
				format(query, MAXO_TEXT2, "AdmCmd: %s was been permanent banned by Admin %s, Reason: %s.", PlayerName(KuramaBanStruc[playerid][idinjoc]), PlayerName(playerid), KuramaBanStruc[playerid][banmotiv]);
			else
				format(query, MAXO_TEXT2, "AdmCmd: %s was been banned by Admin %s for %d %s, Reason: %s.", PlayerName(KuramaBanStruc[playerid][idinjoc]), PlayerName(playerid), element, banstr, KuramaBanStruc[playerid][banmotiv]);
			SendClientMessageToAll(COLOR_LIGHTRED, query);
			InsertSanctionInPanel(KuramaBanStruc[playerid][idinjoc], playerid, ACTION_BAN, query);
		}
		format(query, MAXO_TEXT2, "Banned!\n\nMotiv: %s\n\nPt. reclamatii: "#gamemode_forum"", KuramaBanStruc[playerid][banmotiv]);
		ShowPlayerDialog(KuramaBanStruc[playerid][idinjoc], DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "You have been Banned", query, "Ok", "Quit");
		KickDeelay(KuramaBanStruc[playerid][idinjoc]);
	}
	KuramaBanStruc[playerid][banidSQLID] = -1;
	KuramaBanStruc[playerid][idinjoc] = 999;
	strcpy2(KuramaBanStruc[playerid][banmotiv], "");
	strcpy2(KuramaBanStruc[playerid][ipbanat], "");
	strcpy2(KuramaBanStruc[playerid][nickban], "");
	clear.string(banstr);
	clear.string(query);
	return true;
}

function Ban3(idbanat,element,index,adminname[],motiv[]) {
	new query[MAXO_TEXT2], momentan, durata;
	getdate(gYears, gMonths, gDays);
	gettime(gHours, gMinutes, gSeconds);
	momentan = mktime(gHours, gMinutes, gSeconds,gDays,gMonths,gYears); // timp curent
	switch(index) {
		case 1: durata = mktime(gHours+element, gMinutes, gSeconds,gDays,gMonths,gYears); // timp destinatie
		case 2: durata = mktime(gHours, gMinutes+element, gSeconds,gDays,gMonths,gYears); // timp destinatie
		case 3: durata = mktime(gHours, gMinutes, gSeconds+element,gDays,gMonths,gYears); // timp destinatie
		case 4: durata = mktime(gHours, gMinutes, gSeconds,gDays+element,gMonths,gYears); // timp destinatie
		case 5: durata = mktime(gHours, gMinutes, gSeconds,gDays,gMonths+element,gYears); // timp destinatie
		case 6: durata = mktime(gHours, gMinutes, gSeconds,gDays,gMonths,gYears+element); // timp destinatie
		default: return true;
	}
	mysql_format(connectionHandle, query, MAXO_TEXT2, "INSERT INTO bans (player,admin,TimpInit,TimpExp,ip,reason) VALUES ('%d','%s','%d','%d','%s','%e')",PlayerInfo[idbanat][pSQLID],adminname,momentan,durata,PlayerIP[idbanat],motiv);
	mysql_tquery(connectionHandle, query, "NoReturnThread", "d", ADDBAN_THREAD_ID);
	format(query, MAXO_TEXT, "AdmCmd: %s was been banned by Admin %s, Reason: %s.", PlayerName(idbanat), adminname, motiv);
	SendClientMessageToAll(COLOR_LIGHTRED, query);
	format(query, MAXO_TEXT, "Banned!\n\nMotiv: %s\n\nPt. reclamatii: "#gamemode_forum"", motiv);
	ShowPlayerDialog(idbanat, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "You have been Banned", query, "Quit", "");
	KickDeelay(idbanat);

	KuramaBanStruc[idbanat][banidSQLID] = -1;
	KuramaBanStruc[idbanat][idinjoc] = 999;
	strcpy2(KuramaBanStruc[idbanat][banmotiv], "");
	strcpy2(KuramaBanStruc[idbanat][ipbanat], "");
	clear.string(query);
	return 1;
}

stock BanSysOnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	new string[MAXO_TEXT];
	if(dialogid == DIALOGID_QUESTION_BAN) {
		if(response) {
			switch(listitem) {
				case 0 : ShowPlayerDialog(playerid,DIALOGID_MINUTE_BAN,DIALOG_STYLE_INPUT,"Ai ales minute","Introdu valoarea.\n De ex daca introduci 5 in casuta\nbanul va fi de 5 minute","Ok","Anuleaza");
				case 1 : ShowPlayerDialog(playerid,DIALOGID_HOUR_BAN,DIALOG_STYLE_INPUT,"Ai ales Ore","Introdu valoarea.\n De ex daca introduci 5 in casuta\nbanul va fi de 5 ore","Ok","Anuleaza");
				case 2 : ShowPlayerDialog(playerid,DIALOGID_DAY_BAN,DIALOG_STYLE_INPUT,"Ai ales Zile","Introdu valoarea.\n De ex daca introduci 5 in casuta\nbanul va fi de 5 zile","Ok","Anuleaza");
				case 3 : ShowPlayerDialog(playerid,DIALOGID_MONTH_BAN,DIALOG_STYLE_INPUT,"Ai ales Luni","Introdu valoarea.\n De ex daca introduci 5 in casuta\nbanul va fi de 5 luni","Ok","Anuleaza");
				case 4 : ShowPlayerDialog(playerid,DIALOGID_YEAR_BAN,DIALOG_STYLE_INPUT,"Ai ales Ani","Introdu valoarea.\n De ex daca introduci 5 in casuta\nbanul va fi de 5 ani","Ok","Anuleaza");
				case 5 : ShowPlayerDialog(playerid,DIALOGID_PERM_BAN,DIALOG_STYLE_MSGBOX,"Ai ales Permanent","Sigur doresti sa-l banezi permanent?","Ok","Anuleaza");
			}
			return true;
		}
		else if(!response) {
			SendClientMessage(playerid, COLOR_GRAD1, "Banul a fost anulat.");
			return true;
		}
	}
	else if(dialogid == DIALOGID_MINUTE_BAN) {
		if (response)  {
			new tmpid = strval(inputtext);
			if(!isNumeric(inputtext)) return SendClientMessage(playerid, COLOR_GRAD1, "Eroare: Introduceti un numar!");
			if(KuramaBanStruc[playerid][idinjoc] != INVALID_PLAYER_ID)
				format(string, MAXO_TEXT2, "AdmCmd: %s (SQLID: %d) was been banned by Admin %s for %d minutes, Reason: %s", PlayerName(KuramaBanStruc[playerid][idinjoc]), KuramaBanStruc[playerid][banidSQLID], PlayerName(playerid), tmpid, KuramaBanStruc[playerid][banmotiv]);
			else
				format(string,sizeof(string),"AdmCmd: %s (SQLID %d) was been banned by Admin %s for %d minutes, Reason: %s", KuramaBanStruc[playerid][nickban], KuramaBanStruc[playerid][banidSQLID], PlayerName(playerid), tmpid, KuramaBanStruc[playerid][banmotiv]);
			ABroadCast(COLOR_YELLOW, string, 1);
			Ban2(playerid, tmpid, 2);
			clear.string(string);
			return 1;
		}
		else if(!response) {
			SendClientMessage(playerid, COLOR_GRAD1, "Banul a fost anulat.");
			return true;
		}
	}
	else if(dialogid == DIALOGID_HOUR_BAN) {
		if (response) {
			new tmpid = strval(inputtext);
			if(!isNumeric(inputtext)) return SendClientMessage(playerid, COLOR_GRAD1, "Eroare: Introduceti un numar!");
			if(KuramaBanStruc[playerid][idinjoc] != INVALID_PLAYER_ID)
				format(string, MAXO_TEXT2, "AdmCmd: %s (SQLID: %d) was been banned by Admin %s for %d hours, Reason: %s", PlayerName(KuramaBanStruc[playerid][idinjoc]), KuramaBanStruc[playerid][banidSQLID], PlayerName(playerid), tmpid, KuramaBanStruc[playerid][banmotiv]);
			else
				format(string,sizeof(string),"AdmCmd: %s (SQLID %d) was been banned by Admin %s for %d hours, Reason: %s", KuramaBanStruc[playerid][nickban], KuramaBanStruc[playerid][banidSQLID], PlayerName(playerid), tmpid, KuramaBanStruc[playerid][banmotiv]);
			ABroadCast(COLOR_YELLOW, string, 1);
			Ban2(playerid, tmpid, 1);
			clear.string(string);
			return true;
		}
		else if(!response) {
			SendClientMessage(playerid, COLOR_GRAD1, "Banul a fost anulat.");
			return true;
		}
	}
	else if(dialogid == DIALOGID_DAY_BAN) {
		if(response) {
			new tmpid = strval(inputtext);
			if(!isNumeric(inputtext)) return SendClientMessage(playerid, COLOR_GRAD1, "Eroare: Introduceti un numar!");
			if(KuramaBanStruc[playerid][idinjoc] != INVALID_PLAYER_ID)
				format(string, MAXO_TEXT2, "AdmCmd: %s (SQLID: %d) was been banned by Admin %s for %d days, Reason: %s", PlayerName(KuramaBanStruc[playerid][idinjoc]), KuramaBanStruc[playerid][banidSQLID], PlayerName(playerid), tmpid, KuramaBanStruc[playerid][banmotiv]);
			else
				format(string,sizeof(string),"AdmCmd: %s (SQLID %d) was been banned by Admin %s for %d days, Reason: %s", KuramaBanStruc[playerid][nickban], KuramaBanStruc[playerid][banidSQLID], PlayerName(playerid), tmpid, KuramaBanStruc[playerid][banmotiv]);
			ABroadCast(COLOR_YELLOW, string, 1);
			Ban2(playerid, tmpid, 4);
			clear.string(string);
			return true;
		}
		else if(!response) {
			SendClientMessage(playerid, COLOR_GRAD1, "Banul a fost anulat.");
			return true;
		}
	}
	else if(dialogid == DIALOGID_MONTH_BAN) {
		if(response) {
			new tmpid = strval(inputtext);
			if(!isNumeric(inputtext)) return SendClientMessage(playerid, COLOR_GRAD1, "Eroare: Introduceti un numar!");
			if(KuramaBanStruc[playerid][idinjoc] != INVALID_PLAYER_ID)
				format(string, MAXO_TEXT2, "AdmCmd: %s (SQLID: %d) was been banned by Admin %s for %d months, Reason: %s", PlayerName(KuramaBanStruc[playerid][idinjoc]), KuramaBanStruc[playerid][banidSQLID], PlayerName(playerid), tmpid, KuramaBanStruc[playerid][banmotiv]);
			else
				format(string,sizeof(string),"AdmCmd: %s (SQLID %d) was been banned by Admin %s for %d months, Reason: %s", KuramaBanStruc[playerid][nickban], KuramaBanStruc[playerid][banidSQLID], PlayerName(playerid), tmpid, KuramaBanStruc[playerid][banmotiv]);
			ABroadCast(COLOR_YELLOW, string, 1);
			Ban2(playerid, tmpid, 5);
			clear.string(string);
			return true;
		}
		else if(!response) {
			SendClientMessage(playerid, COLOR_GRAD1, "Banul a fost anulat.");
			return true;
		}
	}
	else if(dialogid == DIALOGID_YEAR_BAN) {
		if(response) {
			new tmpid = strval(inputtext);
			if(!isNumeric(inputtext)) return SendClientMessage(playerid, COLOR_GRAD1, "Eroare: Introduceti un numar!");
			if(KuramaBanStruc[playerid][idinjoc] != INVALID_PLAYER_ID)
				format(string, MAXO_TEXT2, "AdmCmd: %s (SQLID: %d) was been banned by Admin %s for %d years, Reason: %s", PlayerName(KuramaBanStruc[playerid][idinjoc]), KuramaBanStruc[playerid][banidSQLID], PlayerName(playerid), tmpid, KuramaBanStruc[playerid][banmotiv]);
			else
				format(string,sizeof(string),"AdmCmd: %s (SQLID %d) was been banned by Admin %s for %d years, Reason: %s", KuramaBanStruc[playerid][nickban], KuramaBanStruc[playerid][banidSQLID], PlayerName(playerid), tmpid, KuramaBanStruc[playerid][banmotiv]);
			ABroadCast(COLOR_YELLOW, string, 1);
			Ban2(playerid, tmpid, 6);
			clear.string(string);
			return true;
		}
		else if(!response) {
			SendClientMessage(playerid, COLOR_GRAD1, "Banul a fost anulat.");
			return true;
		}
	}
	else if(dialogid == DIALOGID_PERM_BAN) {
		if (response) {
			format(string, MAXO_TEXT2, "AdmCmd: %s (SQLID: %d) was been banned permanent by Admin %s, Reason: %s", PlayerName(KuramaBanStruc[playerid][idinjoc]), KuramaBanStruc[playerid][banidSQLID], PlayerName(playerid), KuramaBanStruc[playerid][banmotiv]);
			ABroadCast(COLOR_YELLOW, string, 1);
			Ban2(playerid, 10, 6);
			clear.string(string);
			return true;
		}
		else if(!response) {
			SendClientMessage(playerid, COLOR_GRAD1, "Banul a fost anulat.");
			return true;
		}
	}
	else if(dialogid == DIALOGID_PLAYER_BANAT) {
		ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX,"Login from banned account","Nu uita! Banul expira automat\nNu e nevoie sa faci o cerere unban.","Ok","");
		KickDeelay(playerid);
		return true;
	}
	else if(dialogid == DIALOGID_OFFBAN2) {
		if (response) {
			ShowPlayerDialog( playerid, DIALOGID_QUESTION_BAN, DIALOG_STYLE_LIST, "Selectati Durata ban", "Minute\nOre\nZile\nLuni\nAni\nPermanent", "Selecteaza", "Anulare" );
		} else if(!response) return true;
	}
	else if(dialogid == DIALOGID_OFFBAN1) {
		if (response) {
			KuramaCheckBannedNick(playerid,KuramaBanStruc[playerid][banidSQLID]);
		} else if(!response) return true;
	}
	else if(dialogid == DIALOGID_OFFWARN) {
		if (response) {
			KuramaCheckWarnedNick(playerid,KuramaWarnStruc[playerid][warnid]);
		}
		else
		{
			KuramaWarnStruc[playerid][warnid] = -1;
			KuramaWarnStruc[playerid][idinjoc] = -1;
			KuramaWarnStruc[playerid][warnnum] = 0;
			strcpy2(KuramaWarnStruc[playerid][warnnick], "");
			strcpy2(KuramaWarnStruc[playerid][ipwarned], "");
			return true;
		}
	}
	else if(dialogid == DIALOGID_OFFWARN2)
	{
		if (response)
			WarnOfflineAdd(playerid);
		else
		{
			KuramaWarnStruc[playerid][warnid] = -1;
			KuramaWarnStruc[playerid][idinjoc] = -1;
			KuramaWarnStruc[playerid][warnnum] = 0;
			strcpy2(KuramaWarnStruc[playerid][warnnick], "");
			strcpy2(KuramaWarnStruc[playerid][ipwarned], "");
			return true;
		}
	}
	return true;
}

COMMAND:ban(playerid,params[]) {
	new giveplayerid;
	if(PlayerInfo[playerid][pAdmin]) {
		if(!sscanf(params, "s[24]s[64]", PartialName[playerid][nume_introdus], KuramaBanStruc[playerid][banmotiv])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			giveplayerid = PartialName[playerid][jucator_gasit];
			if(giveplayerid != INVALID_PLAYER_ID) {
				if(IsPlayerNPC(giveplayerid)) return SendClientMessage(playerid, COLOR_GRAD2, "Cannot Ban an NPC !");
				ShowPlayerDialog( playerid, DIALOGID_QUESTION_BAN,DIALOG_STYLE_LIST, "Selectati Durata ban", "Minute\nOre\nZile\nLuni\nAni\nPermanent", "Selecteaza", "Anulare");
				GetPlayerIp(giveplayerid, KuramaBanStruc[playerid][ipbanat], 25);
				KuramaBanStruc[playerid][idinjoc] = giveplayerid;
				KuramaBanStruc[playerid][banidSQLID] = PlayerInfo[giveplayerid][pSQLID];
				PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
			} else SendClientMessage(playerid, COLOR_GRAD1, "Can not find user - Unknown user");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/ban [playerid/PartOfName] [reason]");
	} else NotAuthorized();
	return true;
}

stock BanOfflineDB(playerid, numele[]) {
	new query[MAXO_TEXT1+29];
	mysql_format(connectionHandle, query, sizeof(query), "SELECT ID, Name, Level FROM players WHERE Name = '%e' LIMIT 1", numele);
	mysql_tquery(connectionHandle, query, "OffBanThd1", "d", playerid);
	clear.string(query);
	return 1;
}

COMMAND:offlineban(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] > 1) {
		if(!sscanf(params, "s[25]s[64]", KuramaBanStruc[playerid][nickban], KuramaBanStruc[playerid][banmotiv])) {
			BanOfflineDB(playerid, KuramaBanStruc[playerid][nickban]);
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/o(ffline)ban [name] [reason]");
	} else NotAuthorized();
	return true;
}

COMMAND:oban(playerid, params[]) {
	return cmd_offlineban(playerid, params);
}

function OffBanThd1(extraid) {
	new string2[MAXO_TEXT], numeuser[MAX_PLAYER_NAME], niveluser;
	if(cache_get_row_count()) {
		KuramaBanStruc[extraid][banidSQLID] = cache_get_row_int(0, 0);
		cache_get_row(0, 1, numeuser); KuramaBanStruc[extraid][idinjoc] = ReturnUser(numeuser);
		niveluser = cache_get_row_int(0, 2);
		format(string2, MAXO_TEXT, "A fost gasit utilizatorul:\nNume: %s\nNivel: %d\nAcesta este utilizatorul pe care doriti sa-l banati ?", numeuser, niveluser);
		ShowPlayerDialog(extraid, DIALOGID_OFFBAN1, DIALOG_STYLE_MSGBOX, "Offline Banning", string2, "Da", "Anulare");
		clear.string(string2);
	} else ShowPlayerDialog(extraid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Offline Banning", "Nu a fost gasit niciun utilizator cu acest nume", "Ok", "");
	return true;
}

stock KuramaCheckBannedNick(playerid,sqlid)
{
	new query[MAXO_TEXT];
	format(query, MAXO_TEXT, "SELECT player, inactive FROM bans WHERE inactive = 0 AND player = %d", sqlid);
	mysql_tquery(connectionHandle, query, "OffBanThd2", "d", playerid);
	clear.string(query);
	return 1;
}

function OffBanThd2(extraid) {
	new string2[MAXO_TEXT];
	if(cache_get_row_count()) {
		new timpban = cache_get_row_int(0, 1);
		if(timpban < gLocalTimeStamp) {
			cache_get_row(0, 0, KuramaBanStruc[extraid][ipbanat], connectionHandle, 25);
			format(string2, MAXO_TEXT, "Ultimul ban gasit pentru acest utilizator\na expirat la data %s\n Continuarea procesul de adaugare ban?", DateToTimestamp(timpban,3));
			ShowPlayerDialog(extraid, DIALOGID_OFFBAN2, DIALOG_STYLE_MSGBOX, "Offline Banning", string2, "Continua", "Anulare");
		}
		else
		{
			KuramaBanStruc[extraid][banidSQLID] = -1;
			KuramaBanStruc[extraid][idinjoc] = 999;
			strcpy2(KuramaBanStruc[extraid][banmotiv], "");
			strcpy2(KuramaBanStruc[extraid][ipbanat], "");
			strcpy2(KuramaBanStruc[extraid][nickban], "");

			format(string2, MAXO_TEXT, "Nu pot adauga ban.\nUtilizatorul are deja un ban in curs\ncare expira la %s", DateToTimestamp(timpban,3));
			ShowPlayerDialog(extraid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Offline Banning", string2, "Ok","");
		}
		clear.string(string2);
	} else ShowPlayerDialog(extraid, DIALOGID_QUESTION_BAN, DIALOG_STYLE_LIST, "Selectati Durata ban", "Minute\nOre\nZile\nLuni\nAni\nPermanent", "Selecteaza", "Anulare" );
	return true;
}

COMMAND:warn(playerid,params[]) {
	if (PlayerInfo[playerid][pAdmin]) {
		new string[MAXO_TEXT], motiv[40], giveplayerid;
		if(!sscanf(params, "s[24]s[39]", PartialName[playerid][nume_introdus], motiv)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			giveplayerid = PartialName[playerid][jucator_gasit];
			if(giveplayerid != INVALID_PLAYER_ID) {
				if(!IsPlayerNPC(giveplayerid)) {
					PlayerInfo[giveplayerid][pWarnings] ++;
					if(PlayerInfo[giveplayerid][pWarnings] >= 3) {
						PlayerInfo[giveplayerid][pWarnings] = 0;
						format(string, MAXO_TEXT, "UPDATE players SET Warnings = %d WHERE ID = %d", PlayerInfo[giveplayerid][pWarnings], PlayerInfo[giveplayerid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						format(string, MAXO_TEXT, "AdmCmd: %s was been banned by Admin %s (had 3 Warnings), Reason: %s", PlayerName(giveplayerid), PlayerName(playerid), motiv);
						SendClientMessageToAll(COLOR_LIGHTRED, string);

						format(motiv, 40, "3Warn-> %s", motiv);
						memcpy(KuramaBanStruc[playerid][banmotiv], motiv, 0, MAX_PLAYER_NAME*4, MAX_PLAYER_NAME*4);
						memcpy(KuramaBanStruc[playerid][nickban], PlayerName(giveplayerid), 0, MAX_PLAYER_NAME*4, MAX_PLAYER_NAME*4);
						KuramaBanStruc[playerid][banidSQLID] = PlayerInfo[giveplayerid][pSQLID];
						KuramaBanStruc[playerid][idinjoc] = giveplayerid;
						GetPlayerIp(giveplayerid, KuramaBanStruc[playerid][ipbanat], 25);
						Ban2(playerid,3,4);
						return 1;
					}
					else
					{
						format(string, MAXO_TEXT, "AdmCmd: %s was warned by Admin %s, Reason: %s.", PlayerName(giveplayerid), PlayerName(playerid), motiv);
						ABroadCast(COLOR_LIGHTRED, string, 1);
						format(string, MAXO_TEXT, "* You was been warned by Admin %s, Reason: %s.", PlayerName(playerid), motiv);
						SendClientMessage(giveplayerid, COLOR_LIGHTRED, string);
					}
					format(string, MAXO_TEXT, "AdmCmd: %s was warned by Admin %s, Reason: %s.", PlayerName(giveplayerid), PlayerName(playerid), motiv);
					InsertSanctionInPanel(giveplayerid, playerid, ACTION_WARN, string);
					format(string, sizeof(string), "UPDATE players SET Warnings = %d WHERE ID = %d", PlayerInfo[giveplayerid][pWarnings], PlayerInfo[giveplayerid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				} else SendClientMessage(playerid, COLOR_GRAD1, "Cannot Warn an NPC !");
				PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "Can not find user - Unknown user.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/warn [playerid/PartOfName] [reason]");
	} else NotAuthorized();
	return true;
}

COMMAND:owarn(playerid,params[]) {
	if(PlayerInfo[playerid][pAdmin] > 1) {
		if(!sscanf(params, "s[20]s[64]", KuramaBanStruc[playerid][nickban], KuramaWarnStruc[playerid][warnmotiv])) {
			WarnOfflineDB(playerid,KuramaBanStruc[playerid][nickban]);
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/o(ffline)warn(ing) [name] [reason]");
	} else NotAuthorized();
	return true;
}

COMMAND:offlinewarning(playerid, params[]) {
	return cmd_owarn(playerid, params);
}

stock WarnOfflineDB(playerid, numele[]) {
	new query[MAXO_TEXT];
	mysql_format(connectionHandle, query, MAXO_TEXT, "SELECT u1.ID, u1.Name, u1.Level, u1.Warnings FROM players as u1 WHERE u1.Name = '%e' LIMIT 1", numele);
	mysql_tquery(connectionHandle, query, "OffWarnThd1", "d", playerid);
	clear.string(query);
	return 1;
}

function OffWarnThd1(extraid) {
	new string2[MAXO_TEXT], niveluser;
	if(cache_get_row_count()) {
		KuramaWarnStruc[extraid][warnid] = cache_get_row_int(0, 0);
		cache_get_row(0, 1, KuramaWarnStruc[extraid][warnnick], connectionHandle, MAX_PLAYER_NAME); KuramaWarnStruc[extraid][idinjoc] = ReturnUser(KuramaWarnStruc[extraid][warnnick]);
		niveluser = cache_get_row_int(0, 2);
		KuramaWarnStruc[extraid][warnnum] = cache_get_row_int(0, 3);
		format(string2, MAXO_TEXT, "A fost gasit utilizatorul: \nNume: %s\nNivel: %d \nWarnings: %d\nAcesta este utilizatorul care doriti sa primeasca warn ?", KuramaWarnStruc[extraid][warnnick], niveluser, KuramaWarnStruc[extraid][warnnum]);
		ShowPlayerDialog(extraid, DIALOGID_OFFWARN, DIALOG_STYLE_MSGBOX, "Offline Warning", string2, "Da", "Anulare");
		clear.string(string2);
	} else ShowPlayerDialog(extraid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Offline Warning", "Nu a fost gasit niciun utilizator cu acest nume", "Ok", "");
	return true;
}

function OffWarnThd2(extraid) {
	new string2[MAXO_TEXT];
	if(cache_get_row_count()) {
		new timpban = cache_get_row_int(0, 1);
		if(timpban < gLocalTimeStamp) {
			cache_get_row(0, 0, KuramaWarnStruc[extraid][ipwarned], connectionHandle, 25);
			format(string2, MAXO_TEXT, "Ultimul ban gasit pentru acest utilizator\na expirat la data %s\n Continuarea procesul adaugare warning?", DateToTimestamp(timpban,3));
			ShowPlayerDialog(extraid, DIALOGID_OFFWARN2, DIALOG_STYLE_MSGBOX, "Offline Warning", string2, "Continua", "Anulare");
		}
		else
		{
			KuramaWarnStruc[extraid][warnid] = -1;
			KuramaWarnStruc[extraid][idinjoc] = -1;
			KuramaWarnStruc[extraid][warnnum] = 0;
			strcpy2(KuramaWarnStruc[extraid][warnnick], "");
			strcpy2(KuramaWarnStruc[extraid][ipwarned], "");

			format(string2, MAXO_TEXT, "Nu pot adauga warning.\nUtilizatorul are deja un ban in curs\ncare expira la %s", DateToTimestamp(timpban,3));
			ShowPlayerDialog(extraid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Offline Warning", string2, "Ok", "Anulare");
		}
		clear.string(string2);
	} else ShowPlayerDialog(extraid, DIALOGID_OFFWARN2, DIALOG_STYLE_MSGBOX, "Offline Warning", "Jucatorul nu a avut banuri in trecut", "Continua", "Anulare");
	return true;
}

stock KuramaCheckWarnedNick(playerid, sqlid)
{
	new query[MAXO_TEXT+22];
	format(query, sizeof(query), "SELECT player, inactive FROM bans WHERE inactive = 0 AND player = %d LIMIT 1", sqlid);
	mysql_tquery(connectionHandle, query, "OffWarnThd2", "d", playerid);
	clear.string(query);
	return 1;
}

stock WarnOfflineAdd(playerid)
{
	if(IsPlayerConnected(KuramaWarnStruc[playerid][idinjoc])) {
		//-------  eliberare resurse
		KuramaWarnStruc[playerid][warnid] = -1;
		KuramaWarnStruc[playerid][idinjoc] = -1;
		KuramaWarnStruc[playerid][warnnum] = 0;
		strcpy2(KuramaWarnStruc[playerid][warnnick], "");
		strcpy2(KuramaWarnStruc[playerid][ipwarned], "");
		//-------
		SendClientMessage(playerid, COLOR_LIGHTRED, "Jucatorul este intrat pe server. Foloseste comanda /warn");
		return 1;
	}
	new string[MAXO_TEXT],
		motiv[MAXO_TEXT1];
	KuramaWarnStruc[playerid][warnnum]++;
	format(string,sizeof(string),"UPDATE `players` SET `Warnings` = '%d' WHERE `players`.`id` = %d",KuramaWarnStruc[playerid][warnnum],KuramaWarnStruc[playerid][warnid]);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	format(string,sizeof(string),"AdmCmd: %s was been warned by Admin %s, Reason: %s.",KuramaWarnStruc[playerid][warnnick],PlayerName(playerid),KuramaWarnStruc[playerid][warnmotiv]);
	ABroadCast(COLOR_YELLOW, string, 1);
	if(KuramaWarnStruc[playerid][warnnum] >= 3) {
		format(string,sizeof(string),"UPDATE `players` SET `Warnings` = '0' WHERE `players`.`ID` = %d",KuramaWarnStruc[playerid][warnid]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		format(motiv,sizeof(motiv),"3Warn-> %s",KuramaWarnStruc[playerid][warnmotiv]);
		memcpy(KuramaBanStruc[playerid][banmotiv], motiv, 0, MAX_PLAYER_NAME*4, MAX_PLAYER_NAME*4);
		KuramaBanStruc[playerid][banidSQLID] = KuramaWarnStruc[playerid][warnid];
		KuramaBanStruc[playerid][idinjoc] = KuramaWarnStruc[playerid][idinjoc];
		memcpy(KuramaBanStruc[playerid][ipbanat], KuramaWarnStruc[playerid][ipwarned], 0, MAX_PLAYER_NAME*4, MAX_PLAYER_NAME*4);
		Ban2(playerid,3,4);

		KuramaWarnStruc[playerid][warnid] = -1;
		KuramaWarnStruc[playerid][idinjoc] = -1;
		KuramaWarnStruc[playerid][warnnum] = 0;
		strcpy2(KuramaWarnStruc[playerid][warnnick], "");
		strcpy2(KuramaWarnStruc[playerid][ipwarned], "");
	}
	clear.string(string);
	return 1;
}

COMMAND:unbanip(playerid, params[]) {
    new ip[16], string[MAXO_TEXT];
	if(PlayerInfo[playerid][pAdmin] > 4) {
		if(!sscanf(params, "s[16]", ip)) {
			mysql_format(connectionHandle, string, sizeof(string), "SELECT ip FROM bans WHERE ip = '%e'", ip);
			mysql_tquery(connectionHandle, string, "Unbanplayerip", "ds", playerid, ip);
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/unbanip [ip]");
	} else NotAuthorized();
	return true;
}

COMMAND:unban(playerid, params[])  {
    new name[MAX_PLAYER_NAME], string[MAXO_TEXT+MAX_PLAYER_NAME];
	if(PlayerInfo[playerid][pAdmin] > 4) {
		if(!sscanf(params, "s[24]", name)) {
			mysql_format(connectionHandle, string, sizeof(string), "SELECT players.Name FROM players INNER JOIN bans ON players.ID = bans.player WHERE bans.inactive = 0 AND players.Name = '%e'", name);
			mysql_tquery(connectionHandle, string, "Unbanplayer", "ds", playerid, name);
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/unban [Name]");
	} else NotAuthorized();
	return true;
}

// End Of File ...
