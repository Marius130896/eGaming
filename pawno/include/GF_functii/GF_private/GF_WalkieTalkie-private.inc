/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_WalkieTalkie_included
	#endinput
#else
	#define GF_WalkieTalkie_included
#endif

#define FREQ_PASS_LENGHT 5
#define NONE_FREQUENCE 0
#define NONE_WALKIETALKIE 1000000000

stock FrequenceMessage(freq, color, string[]) {
	foreach(Player, i) {
		if(gPlayerLogged{i}) {
			if(PlayerInfo[i][pFrequence] == freq) 
				SendClientMessage(i, color, string);
		}
	}
	return true;
}

COMMAND:wt(playerid, params[]) {
	if(PlayerInfo[playerid][pMute] > 1) 
		return SendClientMessage(playerid, COLOR_GRAD1, "You cannot send a frequence message, you have been silenced.");
	if(PlayerInfo[playerid][pFrequence] == NONE_WALKIETALKIE) 
		return SendClientMessage(playerid, COLOR_GRAD1, "You don't have a Walkie Talkie. Go to 24/7 to buy.");
	if(PlayerInfo[playerid][pFrequence] == NONE_FREQUENCE) 
		return SendClientMessage(playerid, COLOR_GRAD1, "You don't set a frequence, use /setfreq.");
	if(sscanf(params, "s[70]", params)) 
		return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/wt [Message]");
	if(strlen(params) > 70) 
		return SendClientMessage(playerid, 0xFFFF00AA, "[Anti-Spam] {FFFFFF}Line too long!");
	new string[MAXO_TEXT];
	format(string, MAXO_TEXT, "[WT-%d] %s: {FFFFFF}%s", PlayerInfo[playerid][pFrequence], PlayerName(playerid), params);
	FrequenceMessage(PlayerInfo[playerid][pFrequence], COLOR_ORANGE, string);
	clear.string(string);
	return 1;
}

COMMAND:connectfreq(playerid, params[]) {
	if(PlayerInfo[playerid][pFrequence] == NONE_WALKIETALKIE)
		return SendClientMessage(playerid, COLOR_GRAD1, "You don't have a Walkie Talkie. Go to 24/7 to buy.");
	new freqPass[FREQ_PASS_LENGHT], freqID;
	if(sscanf(params, "ds[5]", freqID, freqPass))
		return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/connectfreq [Frequence No] [Frequence Pass]");
	if(ISBetween(freqID, (NONE_FREQUENCE + 1), (NONE_WALKIETALKIE-1))) {
		if(freqID == PlayerInfo[playerid][pFrequence])
			return SendClientMessage(playerid, COLOR_GRAD1, "You are already connected at this frequence.");
		new string[MAXO_TEXT];
		mysql_format(connectionHandle, string, MAXO_TEXT, "SELECT * FROM Frequences WHERE FrequenceNo = %d AND FrequencePass = '%s' ", freqID, freqPass);
		mysql_tquery(connectionHandle, string, "ConnFrequence", "dd", playerid, freqID);
		clear.string(string);
	} else SendClientMessage(playerid, COLOR_GRAD1, "You entered an invalid value, please choose between 0 - 999.999.999");
	return true;
}

function ConnFrequence(playerid, freqID) {
	if(cache_num_rows())
		SetNewFrequence(playerid, freqID);
	else
		SendClientMessage(playerid, COLOR_GRAD1, "This password is wrong or this frequence didn't exist.");
	return true;
}

COMMAND:setfreq(playerid, params[])  {
	new
		string[MAXO_TEXT],
		freq;
	if(PlayerInfo[playerid][pFrequence] == NONE_WALKIETALKIE)
		return SendClientMessage(playerid, COLOR_GRAD1, "You don't have a Walkie Talkie. Go to 24/7 to buy.");
	if(sscanf(params, "d", freq))
		return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/setfreq [Frequence]");
	if(ISBetween(freq, NONE_FREQUENCE, (NONE_WALKIETALKIE-1))) {
		if(freq == PlayerInfo[playerid][pFrequence]) 
			return SendClientMessage(playerid, COLOR_GRAD1, "You are already connected at this frequence.");
		if(PlayerInfo[playerid][pFreqNO] > NONE_FREQUENCE && PlayerInfo[playerid][pFreqNO] == freq || PlayerInfo[playerid][pAdmin] > 1337)
			SetNewFrequence(playerid, freq);
		else 
		{
			mysql_format(connectionHandle, string, MAXO_TEXT, "SELECT * FROM Frequences WHERE FrequenceNo = %d", freq);
			mysql_tquery(connectionHandle, string, "CheckFrequence", "dd", playerid, freq);
			clear.string(string);
		}
	}
	else
		SendClientMessage(playerid, COLOR_GRAD1, "You entered an invalid value, please choose between 0 - 999.999.999");
	return true;
}

function CheckFrequence(extraid, freq) {
	if(cache_num_rows()) {
		SendClientMessage(extraid, COLOR_GRAD1, "You can't connect at this frequence, you can't connect at it.");
		SendClientMessage(extraid, COLOR_GRAD1, "Type the command /connectfreq [Freq ID] [Freq Pass] to connect at this frequence.");
	}
	else
		SetNewFrequence(extraid, freq);
	return true;
}

stock SetNewFrequence(playerid, freq) {
	new
		string[MAXO_TEXT];
	if(freq != NONE_FREQUENCE && !PlayerInfo[playerid][pAdmin]) {
		format(string, sizeof(string), "W-T Info: %s joined to you channel.", PlayerName(playerid));
		FrequenceMessage(freq, -1, string);
	}
	PlayerInfo[playerid][pFrequence] = freq;
	format(string, sizeof(string), "Your frequence from Walkie-Talkie set to %d.", PlayerInfo[playerid][pFrequence]);
	SendClientMessage(playerid, COLOR_GRAD1, string);
	format(string, sizeof(string), "UPDATE players SET Frequence = %d WHERE ID = %d", PlayerInfo[playerid][pFrequence], PlayerInfo[playerid][pSQLID]);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	clear.string(string);
	return true;
}

COMMAND:mychannel(playerid, params[]) {
	if(PlayerInfo[playerid][pFrequence] == NONE_FREQUENCE)
		return SendClientMessage(playerid, COLOR_GRAD1, "You don't have set a frequnce, use /setfreq.");
	if(PlayerInfo[playerid][pFrequence] == NONE_WALKIETALKIE) 
	    return SendClientMessage(playerid, COLOR_GRAD1, "You don't have a Walkie Talkie. Go to 24/7 to buy.");
	new
		string[MAXO_TEXT];
	format(string, MAXO_TEXT, "|__________________ Channel %d members __________________|", PlayerInfo[playerid][pFrequence]);
	SendClientMessage(playerid, -1, string);
	foreach(Player, i) {
		if(!PlayerInfo[i][pAdmin]) {
			if(PlayerInfo[i][pFrequence] == PlayerInfo[playerid][pFrequence]) {
				format(string, MAXO_TEXT, "*** %s (ID: %d)", PlayerName(i), i);
				SendClientMessage(playerid, COLOR_GREY, string);
			}
		}
	}
	clear.string(string);
	return 1;
}

COMMAND:kickfreq(playerid, params[]) {
	if(PlayerInfo[playerid][pFreqNO] > NONE_FREQUENCE) {
		new
			pID;
		if(sscanf(params, "u", pID))
			return SendClientMessage(playerid, COLOR_GRAD1, "USAGE: /kickfreq [playerid/PartOfName]");
		if(pID != INVALID_PLAYER_ID) {
			if(pID == playerid)
				return SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command on yourself.");
			if(PlayerInfo[pID][pFrequence] == PlayerInfo[playerid][pFreqNO]) {
				new string[MAXO_TEXT];
				PlayerInfo[pID][pFrequence] = NONE_FREQUENCE;
				format(string, MAXO_TEXT, "* You kicked out %s from your frequence.", PlayerName(pID));
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				format(string, MAXO_TEXT, "* You have been kicked out from frequence %d by Owner %s.", PlayerInfo[playerid][pFreqNO], PlayerName(playerid));
				SendClientMessage(pID, COLOR_LIGHTBLUE, string);
				mysql_format(connectionHandle, string, MAXO_TEXT, "UPDATE players SET Frequence = %d WHERE ID = %d", PlayerInfo[pID][pFrequence], PlayerInfo[pID][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "This player is not on the frequency you hold.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid player.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You do not have any frequency to use this command.");
	return true;
}

COMMAND:changefreqpass(playerid, params[]) {
	if(PlayerInfo[playerid][pFreqNO] > NONE_FREQUENCE) {
		new string[MAXO_TEXT], newPass[FREQ_PASS_LENGHT];
		if(sscanf(params, "s[5]", newPass))
			return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/changefreqpass [New Password]");
		if(ISBetween(strlen(newPass), 1, FREQ_PASS_LENGHT)) {
			format(string, MAXO_TEXT, "* The new password from the frequence %d is: %s", PlayerInfo[playerid][pFreqNO], newPass);
			SendClientMessage(playerid, COLOR_YELLOW, string);
			mysql_format(connectionHandle, string, MAXO_TEXT, "UPDATE Frequences SET FrequencePass = '%s' WHERE FrequenceNo = %d", newPass, PlayerInfo[playerid][pFreqNO]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_GRAD1, "The password must contain between 1-5 characters.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have any frequency to change your password.");
	return true;
}

stock WalOnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	#pragma unused listitem
	new string[MAXO_TEXT];
	if(dialogid == DIALOGID_BUY_WALKIETALKIE) {
		if(response) {
			if(isNumeric(inputtext)) {
				if(ISBetween(strlen(inputtext), (NONE_FREQUENCE+1), (NONE_WALKIETALKIE-1))) {
					format(string, MAXO_TEXT, "SELECT * FROM Frequences WHERE FrequenceNo= '%d' OR FrequenceOwner = '%s'", inputtext, PlayerName(playerid));
					mysql_tquery(connectionHandle, string, "BuyFrequence", "ds", playerid, inputtext);
					clear.string(string);
				} else ShowPlayerDialog(playerid, DIALOGID_BUY_WALKIETALKIE, DIALOG_STYLE_INPUT, "Buy Walkie Talkie Menu", "Invalid frequence number!\nType below the frequency number you want to buy:", "Next", "Abort");
			} 
		} 
		else 
		{
			SendClientMessage(playerid, COLOR_GRAD1, "You aborted this action.");
			TogglePlayerControllable(playerid, true);
			SetCameraBehindPlayer(playerid);
		}
	}
	return true;
}

function BuyFrequence(playerid, freqID[]) {
	new string[MAXO_TEXT];
	rows = cache_num_rows();
	if(!rows) {
		PlayerInfo[playerid][pFreqNO] = strval(freqID);
		format(string, MAXO_TEXT, "INSERT INTO Frequences (FrequenceNo, FrequencePass, FrequenceOwner) VALUES ('%s', '00000', '%s')", freqID, PlayerName(playerid));
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		format(string, MAXO_TEXT, "UPDATE players SET FreqNO = %d WHERE ID = %d", PlayerInfo[playerid][pFreqNO], PlayerInfo[playerid][pSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		format(string, MAXO_TEXT, "* You bought frequency number '%d' with the password '00000' at price of $%s.", PlayerInfo[playerid][pFreqNO], FormatNumber(PretItemInfo[3][pretItem]));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Information: "ALB"If you want to change the password, type the command /changefreqpass");
		clear.string(string);
	} else ShowPlayerDialog(playerid, DIALOGID_BUY_WALKIETALKIE, DIALOG_STYLE_INPUT, "Buy Walkie Talkie Menu", "This frequency has already been bought!\nType below the frequency number you want to buy:", "Next", "Abort");
	return true;
}

// End Of File ...
