/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_PayDaySystem_included
	#endinput
#else
	#define GF_PayDaySystem_included
#endif

function DiseasePayDay() {
	foreach(Player, i) {
		if(gPlayerLogged{i})
			PDayIncrement(i);
	}
	return true;
}

stock PDayIncrement(i) {
	new string[MAXO_TEXT];
	if(!IsPlayerPaused(i)) {
		PlayerInfo[i][pActiveCounter] ++;
		if(PlayerInfo[i][pActiveCounter] > 59) {
			PlayerInfo[i][pActiveTime] ++;
			PlayerInfo[i][pExp] ++;
			PlayerInfo[i][pActiveCounter] = 0;
			format(string, MAXO_TEXT2, "UPDATE players SET ActiveTime = %d, Respect = %d, ActiveCounter = %d WHERE ID = %d", PlayerInfo[i][pActiveTime], PlayerInfo[i][pExp], PlayerInfo[i][pActiveCounter], PlayerInfo[i][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			SendClientMessage(i, COLOR_GREEN, "You have received 1 bonus RP for your activity.");
		}
	}
	PlayerInfo[i][pPayDayTime] ++;
	format(string, MAXO_TEXT, "UPDATE players SET PayDayTime = %d WHERE ID = %d", PlayerInfo[i][pPayDayTime], PlayerInfo[i][pSQLID]);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	if(PlayerInfo[i][pPayDayTime] > 59) {
		PayDay(i);
		PlayerInfo[i][pPayDayTime] = 0;
		format(string, MAXO_TEXT, "UPDATE players SET PayDayTime = %d WHERE ID = %d", PlayerInfo[i][pPayDayTime], PlayerInfo[i][pSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	}
	clear.string(string);
	return true;
}

stock IncreasePayCheck(i) {
	if(!IsPlayerPaused(i)) {
		new level = PlayerInfo[i][pLevel];
		if (ISBetween(level, 0, 2))       PlayerInfo[i][pPayCheck] += 3;
		else if(ISBetween(level, 3, 4))   PlayerInfo[i][pPayCheck] += 5;
		else if(ISBetween(level, 5, 6))   PlayerInfo[i][pPayCheck] += 7;
		else if(ISBetween(level, 7, 8))   PlayerInfo[i][pPayCheck] += 9;
		else if(ISBetween(level, 9, 10))  PlayerInfo[i][pPayCheck] += 11;
		else if(ISBetween(level, 11, 12)) PlayerInfo[i][pPayCheck] += 13;
		else if(ISBetween(level, 13, 14)) PlayerInfo[i][pPayCheck] += 15;
		else if(ISBetween(level, 15, 16)) PlayerInfo[i][pPayCheck] += 17;
		else if(ISBetween(level, 17, 18)) PlayerInfo[i][pPayCheck] += 19;
		else if(ISBetween(level, 19, 20)) PlayerInfo[i][pPayCheck] += 21;
		else if(ISBetween(level, 21, 25)) PlayerInfo[i][pPayCheck] += 25;
		else if(ISBetween(level, 26, 30)) PlayerInfo[i][pPayCheck] += 30;
		else if(ISBetween(level, 31, 40)) PlayerInfo[i][pPayCheck] += 40;
		else if(ISBetween(level, 41, 50)) PlayerInfo[i][pPayCheck] += 55;
		else if(ISBetween(level, 51, 60)) PlayerInfo[i][pPayCheck] += 65;
		else if(ISBetween(level, 61, 70)) PlayerInfo[i][pPayCheck] += 75;
		else if(ISBetween(level, 71, 80)) PlayerInfo[i][pPayCheck] += 85;
		else PlayerInfo[i][pPayCheck] += 95;
	}
	return true;
}

stock PayDay(playerid) {
	new string[MAXO_TEXT], account, interest, rent = 0;
	new tmpintrate, TaxValue = 0;
	if(PlayerInfo[playerid][pLevel] != 0) {
		if(PlayerInfo[playerid][pPhousekey]) {
			rent = HouseInfo[PlayerInfo[playerid][pPhousekey]][hRentPrice];
			if(strcmp(PlayerName(playerid), HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], true) == 0) { rent = 0; }
			else if(rent > PlayerInfo[playerid][pCash]) {
				PlayerInfo[playerid][pPhousekey] = 0;
				SendClientMessage(playerid, COLOR_GRAD1, "* You have been evicted.");
				rent = 0;
				format(string, MAXO_TEXT, "UPDATE players SET Phousekey = 0 WHERE ID = %d", PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			}
			HouseInfo[PlayerInfo[playerid][pPhousekey]][hTakings] += rent;
			format(string, MAXO_TEXT, "UPDATE houses SET Takings = %d WHERE ID = %d", HouseInfo[PlayerInfo[playerid][pPhousekey]][hTakings], HouseInfo[PlayerInfo[playerid][pPhousekey]][hSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
		}
		TaxValue = (PlayerInfo[playerid][pLevel] * 100);
		PlayerInfo[playerid][pAccount] -= TaxValue;
		new ebill = (PlayerInfo[playerid][pAccount]/10000) * (PlayerInfo[playerid][pLevel]);
		SafeGivePlayerMoney(playerid, PlayerInfo[playerid][pPayCheck]);
		if(PlayerInfo[playerid][pAccount] != 0) {
			PlayerInfo[playerid][pAccount] -= ebill;
		}
		else
			ebill = 0;
		tmpintrate = 1;
		account = PlayerInfo[playerid][pAccount];
		interest = (PlayerInfo[playerid][pAccount]/1000) * tmpintrate;
		PlayerPlayMusic(playerid);
		PlayerInfo[playerid][pAccount] += interest;
		SendClientMessage(playerid, -1, "|___ BANK STATMENT ___|");
		format(string, MAXO_TEXT, "Paycheck: {FFFFFF}$%s {5F5F5F}Tax Money: {FFFFFF}-$%s", FormatNumber(PlayerInfo[playerid][pPayCheck], 0, '.'), FormatNumber(TaxValue, 0, '.'));
		SendClientMessage(playerid, 0x5F5F5FFF, string);
		if(PlayerInfo[playerid][pPhousekey] != 0 || PlayerInfo[playerid][pPbizkey] != 0) {
			format(string, MAXO_TEXT, "Electricity Bill: {FFFFFF}-$%s", FormatNumber(ebill, 0, '.'));
			SendClientMessage(playerid, 0x5F5F5FFF, string);
		}
		format(string, MAXO_TEXT, "Balance: {FFFFFF}$%s", FormatNumber(account, 0, '.'));
		SendClientMessage(playerid, 0x5F5F5FFF, string);
		format(string, MAXO_TEXT, "Interest Rate: {FFFFFF}0.%d {5F5F5F}percent", tmpintrate);
		SendClientMessage(playerid, 0x5F5F5FFF, string);
		format(string, MAXO_TEXT, "Interest Gained {FFFFFF}$%s", FormatNumber(interest, 0, '.'));
		SendClientMessage(playerid, 0x5F5F5FFF, string);
		SendClientMessage(playerid, 0x5F5F5FFF, "|--------------------------------------|");
		format(string, MAXO_TEXT, "New Balance: {FFFFFF}%s", FormatNumber(PlayerInfo[playerid][pAccount], 0, '.'));
		SendClientMessage(playerid, 0x5F5F5FFF, string);
		format(string, MAXO_TEXT, "Rent: {FFFFFF}-$%s", FormatNumber(rent, 0, '.'));
		SendClientMessage(playerid, 0x5F5F5FFF, string);
		GameTextForPlayer(playerid, "~y~PayDay~n~~w~Paycheck", 5000, 1);
		rent = 0;
		PlayerInfo[playerid][pPayCheck] = 0;
		PlayerInfo[playerid][pConnectTime] ++;
		PlayerInfo[playerid][pExp] ++;
		if(PlayerInfo[playerid][pGiftPoints] < 6) {
			PlayerInfo[playerid][pGiftPoints] ++;
		}
		CheckLastPDay(playerid);
		format(string, MAXO_TEXT2, "UPDATE players SET OnlineHours = %d, Respect = %d WHERE ID = %d", PlayerInfo[playerid][pConnectTime], PlayerInfo[playerid][pExp], PlayerInfo[playerid][pSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		format(string, MAXO_TEXT, "UPDATE players SET PayCheck = %d, GiftPoints = %d WHERE ID = %d", PlayerInfo[playerid][pPayCheck], PlayerInfo[playerid][pGiftPoints], PlayerInfo[playerid][pSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		clear.string(string);
	}
	return true;
}

COMMAND:pday(playerid, params[]) {
	new string[MAXO_TEXT];
	SendClientMessage(playerid, COLOR_GREEN, "_______________________________________________________________________");
	format(string, MAXO_TEXT, "xxx [ (SQLID: %d) %s - Level %d, %s ] xxx", PlayerInfo[playerid][pSQLID], PlayerName(playerid), PlayerInfo[playerid][pLevel], FactionInfo[PlayerInfo[playerid][pFactiune]][fName]);
	SendClientMessage(playerid, COLOR_LIGHTGREEN, string);
	format(string, MAXO_TEXT, "» NextPayDay: [%d] OnlineHours: [%d] ActiveHours: [%d]", (60 - PlayerInfo[playerid][pPayDayTime]), PlayerInfo[playerid][pConnectTime], PlayerInfo[playerid][pActiveTime]);
	SendClientMessage(playerid, COLOR_GRAD1, string);
	clear.string(string);
	SendClientMessage(playerid, COLOR_GREEN, "_______________________________________________________________________");
	return true;
}

// End Of File ...
