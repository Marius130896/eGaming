/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_MissionsDaily_included
	#endinput
#else
	#define GF_MissionsDaily_included
#endif

stock GetNeedProgress(playerid, caz) {
	return PlayerInfo[playerid][pNeedProgress][caz];
}

stock missionName(playerid, type, id) {
	new string[MAXO_TEXT];
	switch(type) {
		case MISSION_RENTCAR: format(string, MAXO_TEXT, "Rent a vehicle from Rent Car LS/SF/LV.");
		case MISSION_ANNOUNCE: format(string, MAXO_TEXT, "Place an announcement typing command /ad(vertisment)");
		case MISSION_PILLS: format(string, MAXO_TEXT, "Use a pill typing the command /usepills");
		case MISSION_DELIVERYPRODS: format(string, MAXO_TEXT, "Deliver products to %d businesses", PlayerInfo[playerid][pNeedProgress][id]);
		case MISSION_DELIVERYVEHS: format(string, MAXO_TEXT, "Deliver %d vehicles to Crane typing /dropcar", PlayerInfo[playerid][pNeedProgress][id]);
		case MISSION_SELLFLOUR: format(string, MAXO_TEXT, "Sell %d bags of flour typing /sellflour", PlayerInfo[playerid][pNeedProgress][id]);
		case MISSION_BUYGUN: format(string, MAXO_TEXT, "Buy a gun from Ammu-Nation SF/LS");
		case MISSION_BUYFOOD: format(string, MAXO_TEXT, "Buy food of %d times from Burger Shot", PlayerInfo[playerid][pNeedProgress][id]);
	}
	return string;
}

stock MissionProgress(playerid, type, id) {
	new progress, query[MAXO_TEXT];
	switch(type) {
		case MISSION_RENTCAR, MISSION_ANNOUNCE, MISSION_PILLS, MISSION_BUYGUN: progress = 1;
		case MISSION_DELIVERYPRODS, MISSION_BUYFOOD: progress = 2;
		case MISSION_DELIVERYVEHS: progress = 4;
		case MISSION_SELLFLOUR: progress = 2;
	}
	PlayerInfo[playerid][pNeedProgress][id] = progress;
	PlayerInfo[playerid][pProgress][id] = 0;
	format(query, MAXO_TEXT, "UPDATE players SET NeedProgress%d = %d WHERE ID = %d", id+1, progress, PlayerInfo[playerid][pSQLID]);
	mysql_tquery(connectionHandle, query, "NoReturnThread", "d", UPDATE_THREAD_ID);
	clear.string(query);
	return true;
}

stock GivePlayerMission(playerid) {
	new i = playerid, string[MAXO_TEXT];
	PlayerInfo[i][pDailyMission][0] = RandomEx(MISSION_RENTCAR, MISSION_BUYFOOD);
	PlayerInfo[i][pDailyMission][1] = RandomEx(MISSION_ANNOUNCE, MISSION_BUYGUN);
	if(PlayerInfo[i][pDailyMission][0] == PlayerInfo[i][pDailyMission][1]) PlayerInfo[i][pDailyMission][1] = 0;
	format(string, MAXO_TEXT, "UPDATE players SET DailyMission1 = %d WHERE ID = %d", PlayerInfo[playerid][pDailyMission][0], PlayerInfo[playerid][pSQLID]);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	format(string, MAXO_TEXT, "UPDATE players SET DailyMission2 = %d WHERE ID = %d", PlayerInfo[playerid][pDailyMission][1], PlayerInfo[playerid][pSQLID]);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	MissionProgress(i, PlayerInfo[i][pDailyMission][0], 0);
	MissionProgress(i, PlayerInfo[i][pDailyMission][1], 1);
	clear.string(string);
	return true;
}

stock ResetPlayerMission() {
	new query[MAXO_TEXT];
	mysql_tquery(connectionHandle, "UPDATE players SET DailyMission1 = -1, Progress = 0, DailyMission2 = -1, Progress2 = 0, NeedProgress1 = 0, NeedProgress2 = 0", "NoReturnThread", "d", UPDATE_THREAD_ID);
    foreach(Player, i) {
        if(IsPlayerConnected(i) && gPlayerLogged{i}) {
			PlayerInfo[i][pDailyMission][0] = RandomEx(MISSION_RENTCAR, MISSION_BUYFOOD);
			PlayerInfo[i][pDailyMission][1] = RandomEx(MISSION_ANNOUNCE, MISSION_BUYGUN);
			if(PlayerInfo[i][pDailyMission][0] == PlayerInfo[i][pDailyMission][1]) PlayerInfo[i][pDailyMission][1] = 0;
			format(query, MAXO_TEXT, "UPDATE players SET DailyMission1 = %d WHERE ID = %d", PlayerInfo[i][pDailyMission][0], PlayerInfo[i][pSQLID]);
			mysql_tquery(connectionHandle, query, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(query, MAXO_TEXT, "UPDATE players SET DailyMission2 = %d WHERE ID = %d", PlayerInfo[i][pDailyMission][1], PlayerInfo[i][pSQLID]);
			mysql_tquery(connectionHandle, query, "NoReturnThread", "d", UPDATE_THREAD_ID);
			MissionProgress(i, PlayerInfo[i][pDailyMission][0], 0);
			MissionProgress(i, PlayerInfo[i][pDailyMission][1], 1);
			SendClientMessage(i, COLOR_YELLOW, "* The missions of the day have been reset. Use /missions to see new missions.");
			clear.string(query);
        }
    }
	return true;
}

stock CheckMission(playerid, id) {
	new string[MAXO_TEXT], money = 10000 + (PlayerInfo[playerid][pLevel] * 1000) + random(2000);
	if(PlayerInfo[playerid][pDailyMission][id] != -1) {
		PlayerInfo[playerid][pProgress][id] ++;
		if(PlayerInfo[playerid][pProgress][id] == PlayerInfo[playerid][pNeedProgress][id]) {
			format(string, MAXO_TEXT2, "The mission '%s' has been completed.", missionName(playerid, PlayerInfo[playerid][pDailyMission][id], id));
			SendClientMessage(playerid, COLOR_GREEN, string);
			format(string, MAXO_TEXT, "You received $%s and 1 Respect-Point.", FormatNumber(money));
			SendClientMessage(playerid, COLOR_GREEN, string);
			PlayerInfo[playerid][pExp] ++;
			format(string, MAXO_TEXT, "UPDATE players SET Respect = %d WHERE ID = %d", PlayerInfo[playerid][pExp], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			SafeGivePlayerMoney(playerid, money);
			PlayerInfo[playerid][pProgress][id] ++;
		}
		else if(PlayerInfo[playerid][pProgress][id] < PlayerInfo[playerid][pNeedProgress][id]) {
			format(string, MAXO_TEXT2, "Progress for the mission '%s': %d/%d", missionName(playerid, PlayerInfo[playerid][pDailyMission][id], id), PlayerInfo[playerid][pProgress][id], PlayerInfo[playerid][pNeedProgress][id]);
			SendClientMessage(playerid, COLOR_YELLOW, string);
		}
	    if(id == 0) format(string, MAXO_TEXT, "UPDATE players SET Progress = %d WHERE ID = %d", PlayerInfo[playerid][pProgress][id], PlayerInfo[playerid][pSQLID]);
		else if(id == 1) format(string, MAXO_TEXT, "UPDATE players SET Progress2 = %d WHERE ID = %d", PlayerInfo[playerid][pProgress][id], PlayerInfo[playerid][pSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		clear.string(string);
	}
	return true;
}

stock CheckMissionStatus(playerid) {
	new string[MAXO_TEXT], status1[20], status2[20];
	if(PlayerInfo[playerid][pProgress][0] >= GetNeedProgress(playerid, 0)) format(status1, 20, "Mission completed.");
	else format(status1, 20, "%d/%d", PlayerInfo[playerid][pProgress][0], GetNeedProgress(playerid, 0));
	if(PlayerInfo[playerid][pProgress][1] >= GetNeedProgress(playerid, 1)) format(status2, 20, "Mission completed.");
	else format(status2, 20, "%d/%d", PlayerInfo[playerid][pProgress][1], GetNeedProgress(playerid, 1));
	format(string, MAXO_TEXT, "Mission 1: %s. (Progress: %s)", missionName(playerid, PlayerInfo[playerid][pDailyMission][0], 0), status1);
	SendClientMessage(playerid, COLOR_YELLOW, string);
	format(string, MAXO_TEXT, "Mission 2: %s. (Progress: %s)", missionName(playerid, PlayerInfo[playerid][pDailyMission][1], 1), status2);
	SendClientMessage(playerid, COLOR_YELLOW, string);
	clear.string(string);
	return true;
}

COMMAND:missions(playerid, params[]) {
	new string[MAXO_TEXT], status1[20], status2[20];
	if(PlayerInfo[playerid][pProgress][0] >= GetNeedProgress(playerid, 0)) format(status1, 20, "Mission completed.");
	else format(status1, 20, "%d/%d", PlayerInfo[playerid][pProgress][0], GetNeedProgress(playerid, 0));
	if(PlayerInfo[playerid][pProgress][1] >= GetNeedProgress(playerid, 1)) format(status2, 20, "Mission completed.");
	else format(status2, 20, "%d/%d", PlayerInfo[playerid][pProgress][1], GetNeedProgress(playerid, 1));
	format(string, MAXO_TEXT, "Mission 1: %s (Progress: %s)", missionName(playerid, PlayerInfo[playerid][pDailyMission][0], 0), status1);
	SendClientMessage(playerid, COLOR_YELLOW, string);
	format(string, MAXO_TEXT, "Mission 2: %s (Progress: %s)", missionName(playerid, PlayerInfo[playerid][pDailyMission][1], 1), status2);
	SendClientMessage(playerid, COLOR_YELLOW, string);
	clear.string(string);
	return true;
}

COMMAND:resetmissions(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] > 4) {
		ResetPlayerMission();
	} else NotAuthorized();
	return true;
}

#define LUNI 1
#define MARTI 2
#define MIERCURI 3
#define JOI	4
#define VINERI 5
#define SAMBATA	6
#define DUMINICA 7

stock GetDayName(day = 0, month = 0, year = 0) {
	if(day == 0 && month== 0 && year == 0)
		getdate(year, month, day);
	if(month < 3) {
		month += 12;
		year--;
	}
	return (((13*month+3)/5 + day + year + year/4 - year/100 + year/400) % 7)+1;
}

stock IsWeekendDays() {
	switch(GetDayName()) {
		case VINERI..DUMINICA: return true;
	}
	return false;
}

#define MAX_PDAYS 7

stock CheckLastPDay(playerid) {
	new string[MAXO_TEXT], bool: canTakeAward = false;
	getdate(gYears, gMonths, gDays);
	if(PlayerInfo[playerid][pLastTimeOfPD] == gMonths) {
	    if((gDays-PlayerInfo[playerid][pLastDayOfPD]) == 1) 
	        canTakeAward = true;
	    else
	        PlayerInfo[playerid][pTotalPD] = 0,
			canTakeAward = true;
	}
    else
    {
        if(gMonths == 5 || gMonths == 7 ||  gMonths == 10 || gMonths == 12) {
            if(gDays == 1 && PlayerInfo[playerid][pLastDayOfPD] == 30) 
                canTakeAward = true;
            else
                PlayerInfo[playerid][pTotalPD] = 0,
				canTakeAward = true;
        }
        else if(gMonths == 3) {
            if(gDays == 1 && PlayerInfo[playerid][pLastDayOfPD] == 28 || gDays == 1 && PlayerInfo[playerid][pLastDayOfPD] == 29) 
                canTakeAward = true;
            else
                PlayerInfo[playerid][pTotalPD] = 0,
				canTakeAward = true;
        }
        else
        {
            if(gDays == 1 && PlayerInfo[playerid][pLastDayOfPD] == 31) 
                canTakeAward = true;
            else
                PlayerInfo[playerid][pTotalPD] = 0,
				canTakeAward = true;
        }
    }
	if(canTakeAward) {
		new cashAward = (PlayerInfo[playerid][pTotalPD] + 1) * 10000;
		SafeGivePlayerMoney(playerid, cashAward);
		PlayerInfo[playerid][pTotalPD] = (PlayerInfo[playerid][pTotalPD] <= MAX_PDAYS) ? PlayerInfo[playerid][pTotalPD] + 1 : 0;
		PlayerInfo[playerid][pLastDayOfPD] = gDays;
		PlayerInfo[playerid][pLastTimeOfPD] = gMonths;
		format(string, MAXO_TEXT, "~g~$ ~y~%d", cashAward);
		GameTextForPlayer(playerid, string, 3000, 1);
		format(string, MAXO_TEXT, "Ai primit $%s bonus, te asteptam cu un nou bonus mai mare maine.", FormatNumber(cashAward, 0, '.'));
		SendClientMessage(playerid, COLOR_YELLOW, string);
		format(string, MAXO_TEXT, "UPDATE players SET TotalPD = %d, LastDayOfPD = %d, LastTimeOfPD = %d WHERE ID = %d", PlayerInfo[playerid][pTotalPD], PlayerInfo[playerid][pLastDayOfPD], PlayerInfo[playerid][pLastTimeOfPD], PlayerInfo[playerid][pSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	}
	clear.string(string);
	return true;
}

stock GivePlayerAwardGetGift(playerid) {
	new rand = RandomEx(0, 9), string[MAXO_TEXT];
	PlayerInfo[playerid][pGiftPoints] -= 5;
	format(string, MAXO_TEXT, "UPDATE players SET GiftPoints = %d WHERE ID = %d", PlayerInfo[playerid][pGiftPoints], PlayerInfo[playerid][pSQLID]);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	switch(rand) {
		case 0: { // 2x Level UP
			PlayerInfo[playerid][pLevel] += 2;
			SendClientMessage(playerid, COLOR_LIGHTGREEN, "*** GiftBox *** You won 2x Level Up at the Gift Box.");
			format(string, MAXO_TEXT, "UPDATE players SET Level = %d WHERE ID = %d", PlayerInfo[playerid][pLevel], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		}
		case 1: { // 25x Respect Points
			PlayerInfo[playerid][pExp] += 25;
			SendClientMessage(playerid, COLOR_LIGHTGREEN, "*** GiftBox *** You won 25x Respect Points at the Gift Box.");
			format(string, MAXO_TEXT, "UPDATE players SET Respect = %d WHERE ID = %d", PlayerInfo[playerid][pExp], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		}
		case 2: { // $70.000 - $80.000 Cash
			new randmoney = RandomEx(70000, 80000);
			SafeGivePlayerMoney(playerid, randmoney);
			ConsumingMoney[playerid] = 1;
			format(string, MAXO_TEXT, "*** GiftBox *** You won $%s cash at the Gift Box.", FormatNumber(randmoney, 0, '.'));
			SendClientMessage(playerid, COLOR_LIGHTGREEN, string);
		}
		case 3: { // 25x Gift Points
			PlayerInfo[playerid][pGiftPoints] += 25;
			SendClientMessage(playerid, COLOR_LIGHTGREEN, "*** GiftBox *** You won 25x Gift Points at the Gift Box.");
			format(string, MAXO_TEXT, "UPDATE players SET GiftPoints = %d WHERE ID = %d", PlayerInfo[playerid][pGiftPoints], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		}
		case 4: { // All Licenses Available 300 Hours
			PlayerInfo[playerid][pDrivingLicense] += 300;
			PlayerInfo[playerid][pFlyingLicense] += 300;
			PlayerInfo[playerid][pSailingLicense] += 300;
			SendClientMessage(playerid, COLOR_LIGHTGREEN, "*** GiftBox *** You won All Licenses for 300 Hours at the Gift Box.");
			format(string, MAXO_TEXT2, "UPDATE players SET DrivingLicense = %d, FlyingLicense = %d, SailingLicense = %d WHERE ID = %d", PlayerInfo[playerid][pDrivingLicense], PlayerInfo[playerid][pFlyingLicense], PlayerInfo[playerid][pSailingLicense], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		}
		case 5: { // 1x Skill Up for Farmer Job
			switch(PlayerInfo[playerid][pFarmerSkill]) {
				case 0..50: PlayerInfo[playerid][pFarmerSkill] = 51, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for the job Farmer, type /skills.");
				case 51..100: PlayerInfo[playerid][pFarmerSkill] = 101, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for the job Farmer, type /skills.");
				case 101..300: PlayerInfo[playerid][pFarmerSkill] = 301, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for the job Farmer, type /skills.");
				case 301..500: PlayerInfo[playerid][pFarmerSkill] = 501, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for the job Farmer, type /skills.");
				default: return SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** Your skill for the job of Farmer is maximum, type again /getgift."), true;
			}
			format(string, MAXO_TEXT, "UPDATE players SET FarmerSkill = %d WHERE ID = %d", PlayerInfo[playerid][pFarmerSkill], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		}
		case 6: { // 1x Skill Up for News Reporter
			switch(PlayerInfo[playerid][pNewsSkill]) {
				case 0..50: PlayerInfo[playerid][pNewsSkill] = 51, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for News Reporter Informer, type /skills.");
				case 51..100: PlayerInfo[playerid][pNewsSkill] = 101, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for News Reporter Informer, type /skills.");
				case 101..300: PlayerInfo[playerid][pNewsSkill] = 301, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for News Reporter Informer, type /skills.");
				case 301..500: PlayerInfo[playerid][pNewsSkill] = 501, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for News Reporter Informer, type /skills.");
				default: return SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** Your skill for News Reporter Informer is maximum, type again /getgift."), true;
			}
			format(string, MAXO_TEXT, "UPDATE players SET NewsSkill = %d WHERE ID = %d", PlayerInfo[playerid][pNewsSkill], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		}
		case 7: { // 1x Skill Up for DustMan Job
			switch(PlayerInfo[playerid][pDustSkill]) {
				case 0..50: PlayerInfo[playerid][pDustSkill] = 51, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for the job of Dustman, type /skills.");
				case 51..100: PlayerInfo[playerid][pDustSkill] = 101, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for the job of Dustman, type /skills.");
				case 101..300: PlayerInfo[playerid][pDustSkill] = 301, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for the job of Dustman, type /skills.");
				case 301..500: PlayerInfo[playerid][pDustSkill] = 501, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for the job of Dustman, type /skills.");
				default: return SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** Your skill for the job of Dustman is maximum, type again /getgift."), true;
			}
			format(string, MAXO_TEXT, "UPDATE players SET DustSkill = %d WHERE ID = %d", PlayerInfo[playerid][pDustSkill], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		}
		case 8: { // 1x Skill Up for Car Jacker Job
			switch(PlayerInfo[playerid][pCarJackerSkill]) {
				case 0..50: PlayerInfo[playerid][pCarJackerSkill] = 51, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for the job of Car Jacker, type /skills.");
				case 51..100: PlayerInfo[playerid][pCarJackerSkill] = 101, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for the job of Car Jacker, type /skills.");
				case 101..300: PlayerInfo[playerid][pCarJackerSkill] = 301, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for the job of Car Jacker, type /skills.");
				case 301..500: PlayerInfo[playerid][pCarJackerSkill] = 501, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for the job of Car Jacker, type /skills.");
				default: return SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** Your skill for the job of Car Jacker is maximum, type again /getgift."), true;
			}
			format(string, MAXO_TEXT, "UPDATE players SET CarJackerSkill = %d WHERE ID = %d", PlayerInfo[playerid][pCarJackerSkill], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		}
		case 9: { // 1x skill up for arms dealer job
			switch(PlayerInfo[playerid][pArmsDealerSkill]) {
				case 0..50: PlayerInfo[playerid][pArmsDealerSkill] = 51, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for the job of Arms Dealer, type /skills.");
				case 51..150: PlayerInfo[playerid][pArmsDealerSkill] = 101, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for the job of Arms Dealer, type /skills.");
				case 151..300: PlayerInfo[playerid][pArmsDealerSkill] = 301, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for the job of Arms Dealer, type /skills.");
				case 301..400: PlayerInfo[playerid][pArmsDealerSkill] = 501, SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** You won 1x Skill UP for the job of Arms Dealer, type /skills.");
				default: return SendClientMessage(playerid, COLOR_YELLOW, "*** GiftBox *** Your skill for the job ofArms Dealer is maximum, type again /getgift."), true;
			}
			format(string, MAXO_TEXT, "UPDATE players SET ArmsDealerSkill = %d WHERE ID = %d", PlayerInfo[playerid][pArmsDealerSkill], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		}
	}
	clear.string(string);
	return true;
}

COMMAND:getgift(playerid, params[]) {
	if(PlayerInfo[playerid][pGiftPoints] > 4) {
		if(IsPlayerInRangeOfPoint(playerid, 3.0, 510.9125, -1757.1626, 14.2118)) {
			GivePlayerAwardGetGift(playerid);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't in the place where you can to use this command.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have enough GiftPoints to use the command /getgift.");
	return true;
}

#define MAX_ENEMY_HITMAN    2		// two contracts
#define MIN_PRIZE_HITMAN 	15000 	// $15.000
#define MAX_PRIZE_HITMAN    30000 	// $30.000

new
	Iterator:PlayersContract<MAX_PLAYERS>;

stock ContractExceptions(playerid)
	return gPlayerLogged{playerid} && !PlayerInfo[playerid][pHeadValue] && PlayerInfo[playerid][pFactiune] != FACT_HITMAN && !IsPlayerCop(playerid);

stock MembersHitmanOnline() {
	foreach(Player, i) {
		if(PlayerInfo[i][pFactiune] == FACT_HITMAN) return true;
	}
	return false;
}

function AleatorContracts() {
	if(!MembersHitmanOnline()) return 0;
	new targetid[2], string[MAXO_TEXT];
	foreach (Player, playerid) {
		if (ContractExceptions(playerid) && !Iter_Contains(PlayersContract, playerid)) Iter_Add(PlayersContract, playerid);
	}
	if(Iter_Count(PlayersContract) > 1) {
		targetid[0] = Iter_Random(PlayersContract);
        targetid[1] = Iter_Random(PlayersContract);
		while(targetid[0] == targetid[1]) {
			targetid[0] = Iter_Random(PlayersContract);
			targetid[1] = Iter_Random(PlayersContract);
		}
		for(new hit; hit < MAX_ENEMY_HITMAN; hit++) {
			PlayerInfo[targetid[hit]][pHeadValue] = RandomEx(MIN_PRIZE_HITMAN, MAX_PRIZE_HITMAN);
		}
		format(string, MAXO_TEXT, "FactNews: The server has placed a contract on %s for $%s and %s for $%s.", PlayerName(targetid[0]), FormatNumber(PlayerInfo[targetid[0]][pHeadValue], 0, ','), PlayerName(targetid[1]), FormatNumber(PlayerInfo[targetid[1]][pHeadValue], 0, ','));
		SendFamilyMessage(COLOR_LIGHTRED, string, FACT_HITMAN);
		clear.string(string);
	}
	Iter_Clear(PlayersContract);
	HelperToAll();
	return true;
}

// End Of File ...
