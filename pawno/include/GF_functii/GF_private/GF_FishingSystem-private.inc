/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/

#if defined GF_FishingSystem_included
	#endinput
#else
	#define GF_FishingSystem_included
#endif

#define MAX_FISH_LOCATION 10
#define MAX_FISH_LOCATION2 5

#define TIME_FISHING 10000
#define TIME_LEAVE 5000
#define SLOT_CUFF 4

new FishTime[MAX_PLAYERS];
new bool:FirstAnimation[MAX_PLAYERS char];
new IsPlayerAtFishing[MAX_PLAYERS char];

stock ResetVarFishing(playerid) {
	FirstAnimation{playerid} = true;
	KillTimer(FishTime[playerid]);
	IsPlayerAtFishing{playerid} = false;
	return true;
}

new Float:FishLocation[][] = {
	{403.8266,-2088.7598,7.8359},
	{398.7553,-2088.7490,7.8359},
	{396.2197,-2088.6692,7.8359},
	{391.1094,-2088.7976,7.8359},
	{383.4157,-2088.7849,7.8359},
	{374.9598,-2088.7979,7.8359},
	{369.8107,-2088.7927,7.8359},
	{367.3637,-2088.7925,7.8359},
	{362.2244,-2088.7981,7.8359},
	{354.5382,-2088.7979,7.8359}
};

new Float:FishLocation2[][] = {
	{349.9670,-2072.4966,7.8359},
	{349.9450,-2067.3997,7.8359},
	{349.9207,-2064.6753,7.8359},
	{349.8975,-2059.6731,7.8359},
	{349.8625,-2052.1243,7.8359}
};

new FishNames[22][20] = {
	{"Amberjack"},
	{"Jacket"},
	{"Grouper"},
	{"Red Snapper"},
	{"Pants"},
	{"Trout"},
	{"Blue Marlin"},
	{"Can"},
	{"Mackeral"},
	{"Sea Bass"},
	{"Shoes"},
	{"Pike"},
	{"Sail Fish"},
	{"Garbage"},
	{"Tuna"},
	{"Eel"},
	{"Dolphin"},
	{"Shark"},
	{"Turtle"},
	{"Catfish"},
	{"Money Bag"},
	{"Swordfish"}
};

enum pFishing {
	pFish1[20],
	pFish2[20],
	pFish3[20],
	pFish4[20],
	pFish5[20],
	pWeight1,
	pWeight2,
	pWeight3,
	pWeight4,
	pWeight5,
	pFid1,
	pFid2,
	pFid3,
	pFid4,
	pFid5,
	pLastFish,
	pFishID,
	pLastWeight,
};
new Fishes[MAX_PLAYERS][pFishing];

stock IHaveFish(playerid) 
	return Fishes[playerid][pWeight1] > 0 || Fishes[playerid][pWeight2] > 0 || Fishes[playerid][pWeight3] > 0 || Fishes[playerid][pWeight4] > 0 || Fishes[playerid][pWeight5] > 0;

stock MaxFishes(playerid) 
	return Fishes[playerid][pWeight1] > 0 && Fishes[playerid][pWeight2] > 0 && Fishes[playerid][pWeight3] > 0 && Fishes[playerid][pWeight4] > 0 && Fishes[playerid][pWeight5] > 0;

stock ClearFishID(playerid, fish) {
	if(playerid != INVALID_PLAYER_ID) {
		switch (fish) {
			case 1: {
				strmid(Fishes[playerid][pFish1], "None", 0, 4);
				Fishes[playerid][pWeight1] = 0;
				Fishes[playerid][pFid1] = 0;
			}
			case 2: {
				strmid(Fishes[playerid][pFish2], "None", 0, 4);
				Fishes[playerid][pWeight2] = 0;
				Fishes[playerid][pFid2] = 0;
			}
			case 3: {
				strmid(Fishes[playerid][pFish3], "None", 0, 4);
				Fishes[playerid][pWeight3] = 0;
				Fishes[playerid][pFid3] = 0;
			}
			case 4: {
				strmid(Fishes[playerid][pFish4], "None", 0, 4);
				Fishes[playerid][pWeight4] = 0;
				Fishes[playerid][pFid4] = 0;
			}
			case 5: {
				strmid(Fishes[playerid][pFish5], "None", 0, 4);
				Fishes[playerid][pWeight5] = 0;
				Fishes[playerid][pFid5] = 0;
			}
		}
	}
	return true;
}

stock IsAtFishPlace(playerid) {
	if(playerid != INVALID_PLAYER_ID) {
		new f;
		for(f = 0; f < MAX_FISH_LOCATION; f++) {
			if(IsPlayerInRangeOfPoint(playerid, 1.0, FishLocation[f][0], FishLocation[f][1], FishLocation[f][2])) return 1;
		}
		for(f = 0; f < MAX_FISH_LOCATION2; f++) {
			if(IsPlayerInRangeOfPoint(playerid, 1.0, FishLocation2[f][0], FishLocation2[f][1], FishLocation2[f][2])) return 2;
		}
	}
	return false;
}

function FishTimer(playerid) {
	if(playerid != INVALID_PLAYER_ID) {
		if(IsPlayerAtFishing{playerid}) {
			new rand, string[MAXO_TEXT];
			RemovePlayerAttachedObject(playerid, SLOT_CUFF);
			HaveFishingBait[playerid] --;
			TogglePlayerControllable(playerid, 1);
			ApplyAnimation(playerid, "CARRY", "crry_prtial", 2.0, 0, 0, 0, 0, 0, 1);
			IsPlayerAtFishing{playerid} = false;
			rand = random(20);
			switch(rand) {
				case 1: return SendClientMessage(playerid, COLOR_GREY, "You caught a Jacket and threw it away !");
				case 2,4: return SendClientMessage(playerid, COLOR_GREY, "You caught a Pants and threw it away !");
				case 7: return SendClientMessage(playerid, COLOR_GREY, "You caught a Can and threw it away !");
				case 10: return SendClientMessage(playerid, COLOR_GREY, "You caught a pair of Shoes and threw it away !");
				case 13: return SendClientMessage(playerid, COLOR_GREY, "You caught some Garbage and threw it away !");
			}
			new fstring[MAX_PLAYER_NAME], Caught, Level = PlayerInfo[playerid][pFishSkill];
			switch(Level) {
				case 0..10: Caught = RandomEx(16, 20);
				case 11..50: Caught = RandomEx(39, 50);
				case 51..200: Caught = RandomEx(79, 100);
				case 201..400: Caught = RandomEx(129, 145);
				default: Caught = RandomEx(146, 181);
			}
			rand = random(sizeof(FishNames));
			switch(rand) {
				case 1: return SendClientMessage(playerid, COLOR_GREY, "You caught a Jacket and threw it away !");
				case 2,4: return SendClientMessage(playerid, COLOR_GREY, "You caught a Pants and threw it away !");
				case 7: return SendClientMessage(playerid, COLOR_GREY, "You caught a Can and threw it away !");
				case 10: return SendClientMessage(playerid, COLOR_GREY, "You caught a pair of Shoes and threw it away !");
				case 13: return SendClientMessage(playerid, COLOR_GREY, "You caught some Garbage and threw it away !");
				case 20: {
					new mrand = random(2000);
					format(string, sizeof(string), "* You caught a Money Bag, containing $%s.", mrand);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					SafeGivePlayerMoney(playerid, mrand);
					return true; // oprim
				}
			}
			if(!Fishes[playerid][pWeight1]) {
				PlayerInfo[playerid][pFishSkill] ++;
				format(fstring, sizeof(fstring), "%s", FishNames[rand]);
				strmid(Fishes[playerid][pFish1], fstring, 0, strlen(fstring), 255);
				Fishes[playerid][pWeight1] = Caught;
				format(string, sizeof(string), "* You have caught a %s, which weights %d Lbs.", Fishes[playerid][pFish1], Caught);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				Fishes[playerid][pLastWeight] = Caught;
				Fishes[playerid][pLastFish] = 1;
				Fishes[playerid][pFid1] = rand;
				Fishes[playerid][pFishID] = rand;
				if(Caught > PlayerInfo[playerid][pBiggestFish]) {
					format(string, sizeof(string), "* Your old record of %d Lbs has been passed, your new Biggest Fish is: %d Lbs.", PlayerInfo[playerid][pBiggestFish], Caught);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					PlayerInfo[playerid][pBiggestFish] = Caught;
					format(string, sizeof(string), "UPDATE players SET BiggestFish = %d WHERE ID = %d", Caught, PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				}
			}
			else if(!Fishes[playerid][pWeight2]) {
				PlayerInfo[playerid][pFishSkill] ++;
				format(fstring, sizeof(fstring), "%s", FishNames[rand]);
				strmid(Fishes[playerid][pFish2], fstring, 0, strlen(fstring), 255);
				Fishes[playerid][pWeight2] = Caught;
				format(string, sizeof(string), "* You have caught a %s, which weights %d Lbs.", Fishes[playerid][pFish2], Caught);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				Fishes[playerid][pLastWeight] = Caught;
				Fishes[playerid][pLastFish] = 2;
				Fishes[playerid][pFid2] = rand;
				Fishes[playerid][pFishID] = rand;
				if(Caught > PlayerInfo[playerid][pBiggestFish]) {
					format(string, sizeof(string), "* Your old record of %d Lbs has been passed, your new Biggest Fish is: %d Lbs.", PlayerInfo[playerid][pBiggestFish], Caught);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					PlayerInfo[playerid][pBiggestFish] = Caught;
					format(string, sizeof(string), "UPDATE players SET BiggestFish = %d WHERE ID = %d", Caught, PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				}
			}
			else if(!Fishes[playerid][pWeight3]) {
				PlayerInfo[playerid][pFishSkill] ++;
				format(fstring, sizeof(fstring), "%s", FishNames[rand]);
				strmid(Fishes[playerid][pFish3], fstring, 0, strlen(fstring), 255);
				Fishes[playerid][pWeight3] = Caught;
				format(string, sizeof(string), "* You have caught a %s, which weights %d Lbs.", Fishes[playerid][pFish3], Caught);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				Fishes[playerid][pLastWeight] = Caught;
				Fishes[playerid][pLastFish] = 3;
				Fishes[playerid][pFid3] = rand;
				Fishes[playerid][pFishID] = rand;
				if(Caught > PlayerInfo[playerid][pBiggestFish]) {
					format(string, sizeof(string), "* Your old record of %d Lbs has been passed, your new Biggest Fish is: %d Lbs.", PlayerInfo[playerid][pBiggestFish], Caught);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					PlayerInfo[playerid][pBiggestFish] = Caught;
					format(string, sizeof(string), "UPDATE players SET BiggestFish = %d WHERE ID = %d", Caught, PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				}
			}
			else if(!Fishes[playerid][pWeight4]) {
				PlayerInfo[playerid][pFishSkill] ++;
				format(fstring, sizeof(fstring), "%s", FishNames[rand]);
				strmid(Fishes[playerid][pFish4], fstring, 0, strlen(fstring), 255);
				Fishes[playerid][pWeight4] = Caught;
				format(string, sizeof(string), "* You have caught a %s, which weights %d Lbs.", Fishes[playerid][pFish4], Caught);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				Fishes[playerid][pLastWeight] = Caught;
				Fishes[playerid][pLastFish] = 4;
				Fishes[playerid][pFid4] = rand;
				Fishes[playerid][pFishID] = rand;
				if(Caught > PlayerInfo[playerid][pBiggestFish]) {
					format(string, sizeof(string), "* Your old record of %d Lbs has been passed, your new Biggest Fish is: %d Lbs.", PlayerInfo[playerid][pBiggestFish], Caught);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					PlayerInfo[playerid][pBiggestFish] = Caught;
					format(string, sizeof(string), "UPDATE players SET BiggestFish = %d WHERE ID = %d", Caught, PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				}
			}
			else if(!Fishes[playerid][pWeight5]) {
				PlayerInfo[playerid][pFishSkill] ++;
				format(fstring, sizeof(fstring), "%s", FishNames[rand]);
				strmid(Fishes[playerid][pFish5], fstring, 0, strlen(fstring), 255);
				Fishes[playerid][pWeight5] = Caught;
				format(string, sizeof(string), "* You have caught a %s, which weights %d Lbs.", Fishes[playerid][pFish5], Caught);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				Fishes[playerid][pLastWeight] = Caught;
				Fishes[playerid][pLastFish] = 5;
				Fishes[playerid][pFid5] = rand;
				Fishes[playerid][pFishID] = rand;
				if(Caught > PlayerInfo[playerid][pBiggestFish]) {
					format(string, sizeof(string), "* Your old record of %d Lbs has been passed, your new Biggest Fish is: %d Lbs.", PlayerInfo[playerid][pBiggestFish], Caught);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					PlayerInfo[playerid][pBiggestFish] = Caught;
					format(string, sizeof(string), "UPDATE players SET BiggestFish = %d WHERE ID = %d", Caught, PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				}
			}
			switch(PlayerInfo[playerid][pFishSkill]) {
				case 10: {
					SendClientMessage(playerid, COLOR_YELLOW, "* Your Fishing Skill is now Level 2, you can now catch Heavier Fishes.");
					format(string, sizeof(string), "UPDATE players SET FishSkill = %d WHERE ID = %d", PlayerInfo[playerid][pFishSkill] , PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					SafeGivePlayerMoney(playerid, 2000);
				}
				case 50:
				{
					SendClientMessage(playerid, COLOR_YELLOW, "* Your Fishing Skill is now Level 3, you can now catch Heavier Fishes.");
					format(string, sizeof(string), "UPDATE players SET FishSkill = %d WHERE ID = %d", PlayerInfo[playerid][pFishSkill] , PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					SafeGivePlayerMoney(playerid, 3000); 
				}
				case 200: 
				{
					SendClientMessage(playerid, COLOR_YELLOW, "* Your Fishing Skill is now Level 4, you can now catch Heavier Fishes.");
					format(string, sizeof(string), "UPDATE players SET FishSkill = %d WHERE ID = %d", PlayerInfo[playerid][pFishSkill] , PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					SafeGivePlayerMoney(playerid, 4000);
				}
				case 400:
				{
					SendClientMessage(playerid, COLOR_YELLOW, "* Your Fishing Skill is now Level 5, you can now catch Heavier Fishes.");
					format(string, sizeof(string), "UPDATE players SET FishSkill = %d WHERE ID = %d", PlayerInfo[playerid][pFishSkill] , PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					SafeGivePlayerMoney(playerid, 5000);
				}
			}
			clear.string(string);
		}
	}
	return true;
}

function AnimFixer(playerid, caz) {
	if(playerid != INVALID_PLAYER_ID) {
		switch(caz) {
			case 1: {
				if(IsAtFishPlace(playerid) || IsVehicleBoat(GetPlayerVehicleID(playerid))) {
					if(IsPlayerAtFishing{playerid}) {
						SetCameraBehindPlayer(playerid);
						ApplyAnimation(playerid,"SWORD","sword_block",50.0,0,1,0,1,1,1);
					}
				}
			}
			case 2: {
				if(PlayerInfo[playerid][pJailed] > 0) 
					ApplyAnimation(playerid, "BASEBALL", "Bat_1", 4.1, 1, 1, 0, 1, 0, 1);
			}
		}
	}
	return true;
}

COMMAND:fish(playerid, params[]) {
	if(MaxFishes(playerid)) 
		return SendClientMessage(playerid, COLOR_GRAD1, "You already caught 5 Fishes, sell them first !");
	if(IsPlayerInAnyVehicle(playerid))
		return SendClientMessage(playerid, COLOR_GRAD1, "You can't fishing when you are in a vehicle !");
    new Float:xx;
    new Float:yy;
    new Float:zz;
    GetPlayerPos(playerid, xx, yy, zz);
	if(IsAtFishPlace(playerid)) {
		if(!IsPlayerAtFishing{playerid}) {
			if(HaveFishingBait[playerid] > 0) {
				if(HaveFishingRog{playerid}) {
					new Float:Angle;
					GetPlayerFacingAngle(playerid, Angle);
					switch(IsAtFishPlace(playerid)) {
						case 1: { 
							if(ISBetween(Angle, 120, 220)) {
								if(ISBetween(xx, 350 , 410) && ISBetween(yy, -2088.5 , -2090.5)&& zz == 7.8359) {
									SetPlayerArmedWeapon(playerid, 0);
									ApplyAnimation(playerid,"SWORD","sword_block",50.0,0,1,0,1,1,1);
									IsPlayerAtFishing{playerid} = true;
									FishTime[playerid] = SetTimerEx("FishTimer", TIME_FISHING, false, "i", playerid);
									if(FirstAnimation{playerid})
										SetTimerEx("AnimFixer", 1000, false, "ii", playerid, 1);
									FirstAnimation{playerid} = false;
									SetPlayerAttachedObject(playerid, SLOT_CUFF,18632,6,0.079376,0.037070,0.007706,181.482910,0.000000,0.000000,1.000000,1.000000,1.000000);
									GameTextForPlayer(playerid, "nnnnnnnn~w~fishing in the ocean, waiting for ~g~results....", TIME_FISHING-1000, 3);
								} else SendClientMessage(playerid, COLOR_GRAD1, "You are not at a Fishing Place (Big Wheel Rods).");
							} else SendClientMessage(playerid, COLOR_GRAD1, "Throw into the ocean !");
						} 
						case 2: {
							if(ISBetween(Angle, 30, 130)) {
								if(ISBetween(xx, 350 , 410)&& ISBetween(yy, -2088.5 , -2090.5)&& zz == 7.8359) {
									SetPlayerArmedWeapon(playerid, 0);
									ApplyAnimation(playerid,"SWORD","sword_block",50.0,0,1,0,1,1,1);
									IsPlayerAtFishing{playerid} = true;
									FishTime[playerid] = SetTimerEx("FishTimer", TIME_FISHING, false, "i", playerid);
									if(FirstAnimation{playerid})
										SetTimerEx("AnimFixer", 1000, false, "ii", playerid, 1);
									FirstAnimation{playerid} = false;
									SetPlayerAttachedObject(playerid, SLOT_CUFF,18632,6,0.079376,0.037070,0.007706,181.482910,0.000000,0.000000,1.000000,1.000000,1.000000);
									GameTextForPlayer(playerid, "nnnnnnnn~w~fishing in the ocean, waiting for ~g~results....", TIME_FISHING-1000, 3);
								} else SendClientMessage(playerid, COLOR_GRAD1, "You are not at a Fishing Place (Big Wheel Rods).");
							} else SendClientMessage(playerid, COLOR_GRAD1, "Throw into the ocean !");
						}
					}
				} else SendClientMessage(playerid,COLOR_GRAD1, "You do not have any Fishing Rod on your hands !");
			} else SendClientMessage(playerid,COLOR_GRAD1, "You do not have any Baits left !");
		} else SendClientMessage(playerid,COLOR_GRAD1, "You are already Fishing !");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not at a Fishing Place (Big Wheel Rods).");
	return 1;
}

stock FishCost(playerid, fish) {
	if(playerid != INVALID_PLAYER_ID) {
		new cost = 1;
		switch (fish) {
			case 2,3,21: cost = 30+50;
			case 5: cost = 50+50;
			case 6: cost = 20+50;
			case 8:cost = 80+50;
			case 9,14: cost = 120+50;
			case 11,15: cost = 90+50;
			case 12,16,17: cost = 70+50;
			case 18: cost = 100+50;
			case 19: cost = 40+50;
		}
		return cost;
	}
	return false;
}

stock MoneyForMyFish(playerid) {
	new award, cost_fish, stats_fish[MAXO_TEXT], string[3072];
	cost_fish = FishCost(playerid, Fishes[playerid][pFid1]) * Fishes[playerid][pWeight1];
	award += cost_fish;
	format(stats_fish, sizeof(stats_fish), "Fish - %s - Cost - $%s\n", Fishes[playerid][pFish1], FormatNumber(cost_fish, 0, ','));
	strcat(string, stats_fish, sizeof(string));
	if(Fishes[playerid][pWeight2] > 0) {
		cost_fish = FishCost(playerid, Fishes[playerid][pFid2]) * Fishes[playerid][pWeight2];
		award += cost_fish;
		format(stats_fish, sizeof(stats_fish), "Fish - %s - Cost - $%s\n", Fishes[playerid][pFish2], FormatNumber(cost_fish, 0, ','));
		strcat(string, stats_fish, sizeof(string));
	}
	if(Fishes[playerid][pWeight3] > 0) {
		cost_fish = FishCost(playerid, Fishes[playerid][pFid3]) * Fishes[playerid][pWeight3];
		award += cost_fish;
		format(stats_fish, sizeof(stats_fish), "Fish - %s - Cost - $%s\n", Fishes[playerid][pFish3], FormatNumber(cost_fish, 0, ','));
		strcat(string, stats_fish, sizeof(string));
	}
	if(Fishes[playerid][pWeight4] > 0) {
		cost_fish = FishCost(playerid, Fishes[playerid][pFid4]) * Fishes[playerid][pWeight4];
		award += cost_fish;
		format(stats_fish, sizeof(stats_fish), "Fish - %s - Cost - $%s\n", Fishes[playerid][pFish4], FormatNumber(cost_fish, 0, ','));
		strcat(string, stats_fish, sizeof(string));
	}
	if(Fishes[playerid][pWeight5] > 0) {
		cost_fish = FishCost(playerid, Fishes[playerid][pFid5]) * Fishes[playerid][pWeight5];
		award += cost_fish;
		format(stats_fish, sizeof(stats_fish), "Fish - %s - Cost - $%s\n", Fishes[playerid][pFish5], FormatNumber(cost_fish, 0, ','));
		strcat(string, stats_fish, sizeof(string));
	}
	ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Fish Stats", string, "Close", "");
	clear.string(stats_fish);
	clear.string(string);
	return award;
}

COMMAND:sellfish(playerid,params[]) {
	new string[MAXO_TEXT], idbiz = PlayerInfo[playerid][pInBizzID];
	if (BizInfo[idbiz][bType] == BIZ_TYPE_BURGERSHOT) {
		if (!IHaveFish(playerid))
			return SendClientMessage(playerid, COLOR_GRAD1, "You don't have any fish !");
		new award_fish = MoneyForMyFish(playerid);
		SafeGivePlayerMoney(playerid, award_fish);

		format(string, sizeof(string), "* You have sold your fishes for $%s.", FormatNumber( award_fish, 0, ',' ));
		SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
		for(new i = 1; i < 6; i ++) 
			ClearFishID(playerid, i);
		Fishes[playerid][pLastFish] = 0;
		Fishes[playerid][pFishID] = 0;
		clear.string(string);
	} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in Burger Shot to sell your fish !");
	return 1;
}

// End Of File ...
