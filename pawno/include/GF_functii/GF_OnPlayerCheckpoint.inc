/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_OnPlayerCheckpoint_included
	#endinput
#else
	#define GF_OnPlayerCheckpoint_included
#endif

stock ResetCheckpoints(playerid) {
	#if defined _stream_checkpoints
		if(checkpointNoAction[playerid] != INVALID_CHECKPOINT_ID)		DeleteCP(checkpointNoAction, playerid);
		if(checkpointLicenses[playerid] != INVALID_CHECKPOINT_ID)		DeleteRaceCP(checkpointLicenses, playerid);
		if(checkpointEnterBiz[playerid] != INVALID_CHECKPOINT_ID)		DeleteCP(checkpointEnterBiz, playerid);
		if(checkpointCaller[playerid] != INVALID_CHECKPOINT_ID)			DeleteCP(checkpointCaller, playerid);
		if(checkpointFarmer[playerid] != INVALID_CHECKPOINT_ID) {
			EndFarm(playerid);
			DeleteCP(checkpointFarmer, playerid);
		}
		if(checkpointSweeper[playerid] != INVALID_CHECKPOINT_ID)		DeleteCP(checkpointSweeper, playerid);
		if(checkpointDustman[playerid] != INVALID_CHECKPOINT_ID)		DeleteCP(checkpointDustman, playerid);
		if(checkpointTrashDust[playerid] != INVALID_CHECKPOINT_ID)		DeleteCP(checkpointTrashDust, playerid);
		if(checkpointTrucker[playerid] != INVALID_CHECKPOINT_ID)		DeleteCP(checkpointTrucker, playerid);
		if(checkpointHouse[playerid] != INVALID_CHECKPOINT_ID)			DeleteCP(checkpointHouse, playerid);
		if(checkpointSweeper2[playerid] != INVALID_CHECKPOINT_ID)		DeleteCP(checkpointSweeper2, playerid);
		if(checkpointFMARace[playerid] != INVALID_CHECKPOINT_ID)		DeleteCP(checkpointFMARace, playerid);
	#else
		if(CPid[playerid] != INVALID_CHECKPOINT_ID) DeleteCP(checkpointNoAction, playerid);
	#endif
	return true;
}

stock HaveVisibleCheckpoint(playerid) {
	#if defined _stream_checkpoints
		if(GetPlayerVisibleDynamicCP(playerid))
			return true;
	#else
		if(CPid[playerid] != INVALID_CHECKPOINT_ID)
			return true;
	#endif
	return false;
}

#if defined _stream_checkpoints
public OnPlayerEnterDynamicCP(playerid, checkpointid) {
#else
public OnPlayerEnterCheckpoint(playerid) {
	new checkpointid;
#endif
	new vID = GetPlayerVehicleID(playerid), string[MAXO_TEXT];
	if(CheckCP(checkpointid, checkpointFarmer, CP_FARMER) || CheckCP(checkpointid, checkpointSweeper, CP_SWEEPER) || CheckCP(checkpointid, checkpointDustman, CP_DUSTMAN) || CheckCP(checkpointid, checkpointTrucker, CP_TRUCKER || CheckCP(checkpointid, checkpointSweeper2, CP_SWEEPER2))) {
		if(GetTickCount() - AntiCheat[playerid][eGACSpeed] < 2000) {
			new Admins = 0;
			foreach(Player, i) {
				if(PlayerInfo[i][pAdmin] > 0)
					Admins ++;
			}
			if(Admins)
				format(string, MAXO_TEXT, "[CHEAT]: %s (%d) is suspected that can use Teleport Checkpoint Hack.", PlayerName(playerid), playerid),
				ABroadCast(COLOR_YELLOW, string, 1);
			else
				WarningPlayers(playerid, "Teleport CP");
			clear.string(string);
		}
		AntiCheat[playerid][eGACSpeed] = GetTickCount();
	}
	if(CheckCP(checkpointid, checkpointNoAction, CP_NO_ACTION)) {
		DeleteCP(checkpointNoAction, playerid);
	}
	else if(CheckCP(checkpointid, checkpointEnterBiz, CP_ENTER_BIZ)) {
		new
			idbiz = PlayerInfo[playerid][pInBizzID];
		switch(BizInfo[idbiz][bType]) {
			case BIZ_TYPE_GS: {
				TogglePlayerControllable(playerid, false);
				SafeSetPlayerFacingAngle(playerid, 268.6882);
				SetPlayerCameraPos(playerid, 316.9937, -130.5381, 1001.6083);
				SetPlayerCameraLookAt(playerid, 314.0421, -133.6974, 999.6016);
				ShowMenuForPlayer(MenuGunsAN, playerid);
			}
			case BIZ_TYPE_HOUSEUPG: {
				TogglePlayerControllable(playerid, false);
				ShowMenuForPlayer(HUMenu1, playerid);
			}
			case BIZ_TYPE_BURGERSHOT: {
				SetPlayerFacingAngle(playerid, 358.0966);
				SetPlayerCameraPos(playerid,379.4041,-70.1215,1003.1078);
				SetPlayerCameraLookAt(playerid,375.4483,-65.8456,1001.5078);
				TogglePlayerControllable(playerid, false);
				ShowMenuForPlayer(MenuBurger, playerid);
			}
			case BIZ_TYPE_24_7: {
				TogglePlayerControllable(playerid, false);
				ShowMenuForPlayer(MenuStore, playerid);
			}
		}
	}
	else if(CheckCP(checkpointid, checkpointCaller, CP_CALLER)) {
		ClientAccept[playerid] = INVALID_PLAYER_ID;
		DeleteCP(checkpointCaller, playerid);
	}
	if(!vID) {
		if(CheckCP(checkpointid, checkpointCaller, CP_CALLER)) {
			ClientAccept[playerid] = INVALID_PLAYER_ID;
			DeleteCP(checkpointCaller, playerid);
		}
		if(CheckCP(checkpointid, checkpointHouse, CP_HOUSE)) {
			new ID = PlayerInfo[playerid][pInHouseID];
			if(ID) {
				if(HouseInfo[ID][hHeal]) {
					new Float:temphealth;
					GetPlayerHealth(playerid, temphealth);
					if(temphealth < 100)
						SetPlayerHealth(playerid, 100.0), SendClientMessage(playerid, COLOR_WHITE, "You have been healed because of the house upgrade.");
				}
				if(HouseInfo[ID][hArmour]) {
					new Float:temparmour;
					GetPlayerArmour(playerid, temparmour);
					if(temparmour < 100.0 && IsPlayerCop(playerid))
						SetPlayerArmour(playerid, 100.0);
				}
				SafeResetPlayerInterior(playerid);
				DeleteCP(checkpointHouse, playerid);
				SafeSetPlayerPos(playerid, HouseInfo[ID][hEntrancex], HouseInfo[ID][hEntrancey], HouseInfo[ID][hEntrancez]);
				TextDrawHideForPlayer(playerid, propertytxt);
			}
		}
	}
	else
	{
		if(vID != INVALID_VEHICLE_ID) {
			if(CheckCP(checkpointid, checkpointFarmer, CP_FARMER)) {
			}
			else if(CheckCP(checkpointid, checkpointSweeper, CP_SWEEPER)) {
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
					if(CarInfo[vID][cType] == VEHICLE_TYPE_SWEEPER) {
						if(PlayerInfo[playerid][pCPSweeper] < MAX_CP_ROUTE_ONE) {
							PlayerInfo[playerid][pCPSweeper] ++;
							DeleteCP(checkpointSweeper, playerid);
							CreateCP(playerid,LocationRouteOneSweeper[PlayerInfo[playerid][pCPSweeper]][0],LocationRouteOneSweeper[PlayerInfo[playerid][pCPSweeper]][1],LocationRouteOneSweeper[PlayerInfo[playerid][pCPSweeper]][2],DEFAULT_CP_SIZE,checkpointSweeper,CP_SWEEPER);
							PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
							new Pret;
							switch(PlayerInfo[playerid][pSweeperSkill]) {
								case 0..96: { Pret = RandomEx(28, 32); SafeGivePlayerMoney(playerid, Pret); }
								case 97..288: { Pret = RandomEx(33, 36); SafeGivePlayerMoney(playerid, Pret); }
								case 289..672: { Pret = RandomEx(38, 42); SafeGivePlayerMoney(playerid, Pret); }
								case 673..1440: { Pret = RandomEx(43, 46); SafeGivePlayerMoney(playerid, Pret); }
								default: { Pret = RandomEx(48, 51); SafeGivePlayerMoney(playerid, Pret); }
							}
							format(string, MAX_PLAYER_NAME, "~w~+~g~$~w~%d", Pret);
							GameTextForPlayer(playerid, string, 2000, 1);
						}
						else
						{
							PlayerInfo[playerid][pCPSweeper] = -1;
							DeleteCP(checkpointSweeper, playerid);
							PlayerInfo[playerid][pCPSweeper] ++;
							PlayerInfo[playerid][pSweeperSkill] ++;
							format(string, MAXO_TEXT, "UPDATE players SET SweeperSkill = %d WHERE ID = %d", PlayerInfo[playerid][pSweeperSkill], PlayerInfo[playerid][pSQLID]);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							switch(PlayerInfo[playerid][pSweeperSkill]) {
								case 96: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations! Your Street Sweeper Skill is now Level 2.");
								case 288: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations! Your Street Sweeper Skill is now Level 3.");
								case 672: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations! Your Street Sweeper Skill is now Level 4.");
								case 1440: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations! Your Street Sweeper Skill is now Level 5.");
							}
							CreateCP(playerid,LocationRouteOneSweeper[0][0],LocationRouteOneSweeper[0][1],LocationRouteOneSweeper[0][2],DEFAULT_CP_SIZE,checkpointSweeper,CP_SWEEPER);
							SendClientMessage(playerid, COLOR_ORANGE, "INFO: You'll continue the route without to use the command /startsweep");
							SendClientMessage(playerid, COLOR_ORANGE, "INFO: You will receive the money at every checkpoint.");
						}
					} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in vehicle of service to continue the route.");
				}
				clear.string(string);
			}
			else if(CheckCP(checkpointid, checkpointSweeper2, CP_SWEEPER2)) {
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
					if(CarInfo[vID][cType] == VEHICLE_TYPE_SWEEPER) {
						if(PlayerInfo[playerid][pCPSweeper2] < MAX_CP_ROUTE_TWO) {
							PlayerInfo[playerid][pCPSweeper2] ++;
							DeleteCP(checkpointSweeper2, playerid);
							CreateCP(playerid,LocationRouteTwoSweeper[PlayerInfo[playerid][pCPSweeper2]][0],LocationRouteTwoSweeper[PlayerInfo[playerid][pCPSweeper2]][1],LocationRouteTwoSweeper[PlayerInfo[playerid][pCPSweeper2]][2],DEFAULT_CP_SIZE,checkpointSweeper2,CP_SWEEPER2);
							PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
							new Pret;
							switch(PlayerInfo[playerid][pSweeperSkill]) {
								case 0..96: { Pret = RandomEx(25, 28); SafeGivePlayerMoney(playerid, Pret); }
								case 97..288: { Pret = RandomEx(29, 32); SafeGivePlayerMoney(playerid, Pret); }
								case 289..672: { Pret = RandomEx(34, 37); SafeGivePlayerMoney(playerid, Pret); }
								case 673..1440: { Pret = RandomEx(38, 41); SafeGivePlayerMoney(playerid, Pret); }
								default: { Pret = RandomEx(42, 45); SafeGivePlayerMoney(playerid, Pret); }
							}
							format(string, MAX_PLAYER_NAME, "~w~+~g~$~w~%d", Pret);
							GameTextForPlayer(playerid, string, 2000, 1);
						}
						else
						{
							PlayerInfo[playerid][pCPSweeper2] = -1;
							DeleteCP(checkpointSweeper2, playerid);
							PlayerInfo[playerid][pCPSweeper2] ++;
							PlayerInfo[playerid][pSweeperSkill] ++;
							format(string, MAXO_TEXT, "UPDATE players SET SweeperSkill = %d WHERE ID = %d", PlayerInfo[playerid][pSweeperSkill], PlayerInfo[playerid][pSQLID]);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							switch(PlayerInfo[playerid][pSweeperSkill]) {
								case 96: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations! Your Street Sweeper Skill is now Level 2.");
								case 288: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations! Your Street Sweeper Skill is now Level 3.");
								case 672: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations! Your Street Sweeper Skill is now Level 4.");
								case 1440: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations! Your Street Sweeper Skill is now Level 5.");
							}
							CreateCP(playerid,LocationRouteTwoSweeper[0][0],LocationRouteTwoSweeper[0][1],LocationRouteTwoSweeper[0][2],DEFAULT_CP_SIZE,checkpointSweeper2,CP_SWEEPER2);
							SendClientMessage(playerid, COLOR_ORANGE, "INFO: You'll continue the route without to use the command /startsweep");
							SendClientMessage(playerid, COLOR_ORANGE, "INFO: You will receive the money at every checkpoint.");	
						}					
					} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in vehicle of service to continue the route.");
				}
				clear.string(string);
			}
			else if(CheckCP(checkpointid, checkpointDustman, CP_DUSTMAN)) {
				TogglePlayerControllable(playerid, false);
				SetTimerEx("UploadTrash", 5000, false, "u", playerid);
				SendClientMessage(playerid, COLOR_ORANGE, "INFO: Please wait 5 seconds, the trash will be uploaded in your vehicle...");
			}
			else if(CheckCP(playerid, checkpointCarJacker, CP_CARJACKER)) {
				PlayerInfo[playerid][pCarJackerSkill] ++;
				format(string, MAXO_TEXT, "UPDATE players SET CarJackerSkill = %d WHERE ID = %d", PlayerInfo[playerid][pCarJackerSkill], PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				new Rand;
				switch(PlayerInfo[playerid][pCarJackerSkill]) {
					case 0..16: Rand = RandomEx(3700, 3800), SafeGivePlayerMoney(playerid, Rand), PlayerInfo[playerid][pCarTime] = 15*60;
					case 17..56: Rand = RandomEx(3450, 3550), SafeGivePlayerMoney(playerid, Rand), PlayerInfo[playerid][pCarTime] = 12*60;
					case 57..152: Rand = RandomEx(2900, 3800), SafeGivePlayerMoney(playerid, Rand), PlayerInfo[playerid][pCarTime] = 10*60;
					case 153..240: Rand = RandomEx(2500, 3500), SafeGivePlayerMoney(playerid, Rand), PlayerInfo[playerid][pCarTime] = 8*60;
					default: Rand = RandomEx(2000, 3000), SafeGivePlayerMoney(playerid, Rand), PlayerInfo[playerid][pCarTime] = 6*60;
				}
				switch(PlayerInfo[playerid][pCarJackerSkill]) {
					case 17: SendClientMessage(playerid, COLOR_YELLOW, "* Your Car Jack Skill is now Level 2, you will earn more Money and quicker Reload Time.");
					case 57: SendClientMessage(playerid, COLOR_YELLOW, "* Your Car Jack Skill is now Level 3, you will earn more Money and quicker Reload Time.");
					case 153: SendClientMessage(playerid, COLOR_YELLOW, "* Your Car Jack Skill is now Level 4, you will earn more Money and quicker Reload Time.");
					case 241: SendClientMessage(playerid, COLOR_YELLOW, "* Your Car Jack Skill is now Level 5, you will earn more Money and quicker Reload Time.");
				}
				format(string, MAXO_TEXT, "* You sold a car for $%s, your reload time is %s minutes.", FormatNumber(Rand, 0, '.'), ConvertTime(PlayerInfo[playerid][pCarTime]));
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				DeleteCP(checkpointCarJacker, playerid);
				SetVehicleToRespawn(vID);
				new Float:slx, Float:sly, Float:slz;
				GetPlayerPos(playerid, slx, sly, slz);
				SetPlayerPos(playerid, slx, sly, slz+5);
				GameTextForPlayer(playerid, "~y~Sold the car", 2500, 1);
				for(new m; m < 2; m ++) {
					if(PlayerInfo[playerid][pDailyMission][m] == MISSION_DELIVERYVEHS)
						CheckMission(playerid, m);
				}
				clear.string(string);
			}
		}
	}
	return 1;
}

#if defined _stream_checkpoints
public OnPlayerLeaveDynamicCP(playerid, checkpointid)
#else
public OnPlayerLeaveCheckpoint(playerid)
#endif
{
	return 1;
}

#if defined _stream_checkpoints
public OnPlayerEnterDynamicRaceCP(playerid, checkpointid) {
#else
public OnPlayerEnterRaceCheckpoint(playerid) {
	new checkpointid;
#endif
	new
		string[MAXO_TEXT], vID = GetPlayerVehicleID(playerid);
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		if(CheckCP(checkpointid, checkpointLicenses, CP_LICENSES)) {
			if(pTestType{playerid} == TEST_TYPE_CAR) {
				if(CarInfo[vID][cType] == VEHICLE_TYPE_CARTEST) {
					if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 301.8990,-1485.2570,24.3287)) {
						SetPlayerHealth(playerid, 100.0);
						ClearChatBox(playerid, 5);
						SendClientMessage(playerid, -1, ""GALBEN"			- Urcarea in panta -");
						SendClientMessage(playerid, -1, "");
						SendClientMessage(playerid, -1, "» In urmatoarea proba, va trebui sa urci pe acea rampa, pana la urmatorul checkpoint.");
						SendClientMessage(playerid, COLOR_RED, "Atentie! "ALB"Daca in timp ce urci, lovesti masina de ziduri, vei fi declarat respins");
						SendClientMessage(playerid, -1, "... la aceasta proba. Fii atent!");
						PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						SetTimerEx("DrivingTest2", 3000, 0, "d", playerid);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 363.6036,-1468.5726,30.8122)) {
						new Float:health;
						if (vID != INVALID_VEHICLE_ID) GetVehicleHealth(vID, health);
						if(health >= 1000.0) {
							#if defined _stream_objects
								MoveDynamicObject(poartaDMV1, 320.7399,-1488.0225,25.1970, 1);
							#else
								MoveObject(poartaDMV1, 320.7399,-1488.0225,25.1970, 1);
							#endif
							ClearChatBox(playerid, 5);
							SendClientMessage(playerid, -1, ""GALBEN"			- Proba practica a acestui examen -");
							SendClientMessage(playerid, -1, "");
							SendClientMessage(playerid, -1, "» In urmatoarea proba, va trebui sa conduci prin oras.");
							SendClientMessage(playerid, -1, "» Urmareste ruta de checkpointuri marcate cu "ROSU"rosu"ALB".");
							SendClientMessage(playerid, COLOR_RED, "Atentie! "ALB"Daca nu este nici un checkpoint in campul vizual, ghideaza-te dupa minimap.");
							SendClientMessage(playerid, -1, "» Fii atent la viteza, pentru a tine vehiculul sub control.");
							PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
							DeleteRaceCP(checkpointLicenses, playerid);
							SetTimerEx("DrivingTest3", 100, 0, "d", playerid);
						}
						else
						{
							DeleteRaceCP(checkpointLicenses, playerid);
							RemovePlayerFromVehicle(playerid);
							GameTextForPlayer(playerid, "~r~ Respins", 5000, 3);
							ClearChatBox(playerid, 5);
							SendClientMessage(playerid, COLOR_LIGHTRED, "___________________________________");
							SendClientMessage(playerid, -1, "Ai picat testul pentru obtinerea permisului de conducere.");
							SendClientMessage(playerid, -1, "Data viitoare fii mai atent la indicatiile primite.");
							PlayerPlaySound(playerid, 1055, 0.0, 0.0, 0.0);
							SetVehicleToRespawn(vID);
							Gas[vID] = GasMax;
							TakingLesson{playerid} = false;
							pTestType{playerid} = TEST_TYPE_NONE;
							SafeSetPlayerPos(playerid, 331.7640, -1515.6975, 35.8672);
						}
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 329.5655,-1536.8867,32.9324)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,343.8846,-1646.0770,32.7906,809.3568,-1674.4735,13.1162,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 343.8846,-1646.0770,32.7906)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,809.3568,-1674.4735,13.1162,1291.8374,-1575.0763,13.0928,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 809.3568,-1674.4735,13.1162)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,1291.8374,-1575.0763,13.0928,1303.4083,-1854.6796,13.1187,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 1291.8374,-1575.0763,13.0928)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,1303.4083,-1854.6796,13.1187,1314.7368,-1839.7689,13.1166,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 1303.4083,-1854.6796,13.1187)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,1314.7368,-1839.7689,13.1166,1323.0358,-1731.2330,13.1145,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 1314.7368,-1839.7689,13.1166)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,1323.0358,-1731.2330,13.1145,1482.5431,-1731.9219,13.1171,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 1323.0358,-1731.2330,13.1145)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,1482.5431,-1731.9219,13.1171,1531.0907,-1674.5771,13.1161,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 1482.5431,-1731.9219,13.1171)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,1531.0907,-1674.5771,13.1161,1315.3633,-1563.7474,13.1184,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 1531.0907,-1674.5771,13.1161)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,1315.3633,-1563.7474,13.1184,1370.3503,-937.5458,33.9197,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 1315.3633,-1563.7474,13.1184)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,1370.3503,-937.5458,33.9197,128.2512,-1583.4326,10.2674,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 1370.3503,-937.5458,33.9197)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,128.2512,-1583.4326,10.2674,367.1543,-1775.6154,5.0646,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 128.2512,-1583.4326,10.2674)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,367.1543,-1775.6154,5.0646,472.7876,-1725.8472,10.5033,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 367.1543,-1775.6154,5.0646)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,472.7876,-1725.8472,10.5033,633.6907,-1709.1121,14.1220,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 472.7876,-1725.8472,10.5033)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,633.6907,-1709.1121,14.1220,612.8205,-1674.3411,15.6806,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 633.6907,-1709.1121,14.1220)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,612.8205,-1674.3411,15.6806,451.6092,-1634.6154,25.6162,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 612.8205,-1674.3411,15.6806)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,451.6092,-1634.6154,25.6162,413.4886,-1468.5250,30.3317,0);
						SendClientMessage(playerid, COLOR_FAMILY, "Testul practic se apropie de final.");
						SendClientMessage(playerid, COLOR_FAMILY, "Intoarce-te la sediul Driving Motor Vehicle ");
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 451.6092,-1634.6154,25.6162)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,413.4886,-1468.5250,30.3317,329.3841,-1517.9370,35.6002,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 413.4886,-1468.5250,30.3317)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,329.3841,-1517.9370,35.6002,309.7464,-1556.1841,31.6986,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 329.3841,-1517.9370,35.6002)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,309.7464,-1556.1841,31.6986,281.0324,-1548.1263,25.3595,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 309.7464,-1556.1841,31.6986)) 				{
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,281.0324,-1548.1263,25.3595,281.4239,-1531.0164,24.3286,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 281.0324,-1548.1263,25.3595)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,281.4239,-1531.0164,24.3286,281.4239,-1531.0164,24.3286,1);
						#if defined _stream_objects
							MoveDynamicObject(poartaDMV2, 283.5161,-1542.7693,21.9870, 1);
						#else
							MoveObject(poartaDMV2, 283.5161,-1542.7693,21.9870, 1);
						#endif
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 281.4239,-1531.0164,24.3286)) {
						#if defined _stream_objects
							MoveDynamicObject(poartaDMV2, 283.5161,-1542.7693,25.2140, 1);
						#else
							MoveObject(poartaDMV2, 283.5161,-1542.7693,25.2140, 1);
						#endif
						DeleteRaceCP(checkpointLicenses, playerid);
						SetPlayerHealth(playerid, 100.0);
						PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
						GameTextForPlayer(playerid, "~g~Admis", 5000, 3);
						ClearChatBox(playerid, 5);

						PlayerInfo[playerid][pCash] -= (PlayerInfo[playerid][pLevel]*2500);
						SetVehicleToRespawn(vID);
						Gas[vID] = GasMax;
						SafeSetPlayerPos(playerid, 331.4290, -1515.3436, 35.8672);
						SetCameraBehindPlayer(playerid);
						PlayerPlayMusic(playerid);
						TakingLesson{playerid} = false;
						pTestType{playerid} = TEST_TYPE_NONE;

						PlayerInfo[playerid][pDrivingLicense] = gettime()+ExpiraLicenta;
						#if defined _stream_objects
							MoveDynamicObject(poartaDMV2, 283.5161,-1542.7693,25.2140, 1);
						#else
							MoveObject(poartaDMV2, 283.5161,-1542.7693,25.2140, 1);
						#endif
						SendClientMessage(playerid, COLOR_GREEN, "________________________________________________");
						SendClientMessage(playerid, -1, "* Felicitari! Ai fost admis la examenul de conducere.");
						format(string, MAXO_TEXT, "* Ti-a fost inmanat permisul de conducere valabil pana la: "GALBEN"%s", DateToTimestamp(PlayerInfo[playerid][pDrivingLicense], 1));
						SendClientMessage(playerid, -1, string);
						format(string, MAXO_TEXT, "UPDATE players SET DrivingLicense = %d WHERE ID = %d", PlayerInfo[playerid][pDrivingLicense], PlayerInfo[playerid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						SafeSetPlayerVirtualWorld(playerid, 0);
						clear.string(string);
					}
				}
			}
			else if(pTestType{playerid} == TEST_TYPE_FLYING) {
				if(CarInfo[vID][cType] == VEHICLE_TYPE_FLYTEST) {
					if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 1485.8119, -2492.1541, 13.7311)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,1806.5820,-2493.8647,14.2595,2235.0701,-2718.4248,59.8103,4);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 1806.5820,-2493.8647,14.2595)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,2235.0701,-2718.4248,59.8103,2728.6077,-2816.4028,129.7854,3);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 2235.0701,-2718.4248,59.8103)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,2728.6077,-2816.4028,129.7854,3001.4404,-2572.4548,40.2982,3);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 2728.6077,-2816.4028,129.7854)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,3001.4404,-2572.4548,40.2982,2737.8586,-2022.2001,46.2179,3);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 3001.4404,-2572.4548,40.2982)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,2737.8586,-2022.2001,46.2179,2664.7454,-1895.5518,96.5807,3);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 2737.8586,-2022.2001,46.2179)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,2664.7454,-1895.5518,96.5807,698.2737,-588.4136,49.5590,3);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 2664.7454,-1895.5518,96.5807)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,698.2737,-588.4136,49.5590,-139.3617,45.0276,29.3195,3);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 698.2737,-588.4136,49.5590)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,-139.3617,45.0276,29.3195,-1195.1671,334.0156,87.9995,3);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, -139.3617,45.0276,29.3195)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,-1195.1671,334.0156,87.9995,-1493.1873,-88.8193,34.1767,3);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, -1195.1671,334.0156,87.9995)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,-1493.1873,-88.8193,34.1767,-22.6809,-1636.5306,114.9031,3);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, -1493.1873,-88.8193,34.1767)) {
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "Intoarce-te la aeroport!");
						GameTextForPlayer(playerid, "~b~ Intoarce-te la aeroport!", 15000, 3);
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,2010.3856,-2493.6411,14.2568,9000.0,4500.0,14.2568,4);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 2010.3856,-2493.6411,14.2568)) {
						DeleteRaceCP(checkpointLicenses, playerid);
						SetVehicleToRespawn(vID);
						GameTextForPlayer(playerid, "~g~Admis", 5000, 3);
						RemovePlayerFromVehicle(playerid);
						PlayerPlayMusic(playerid);
						Gas[vID] = GasMax;
						pTestType{playerid} = TEST_TYPE_NONE;
						PlayerInfo[playerid][pCash] -= (PlayerInfo[playerid][pLevel]*3000);
						SafeSetPlayerPos(playerid, 1521.0065, -2438.7390, 13.5547);
						ClearChatBox(playerid, 5);
						PlayerInfo[playerid][pFlyingLicense] = gettime()+ExpiraLicenta;
						format(string, MAXO_TEXT, "UPDATE players SET FlyingLicense = %d WHERE ID = %d", PlayerInfo[playerid][pFlyingLicense], PlayerInfo[playerid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						format(string, MAXO_TEXT, "UPDATE players SET Cash = %d WHERE ID = %d", PlayerInfo[playerid][pCash], PlayerInfo[playerid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "Felicitari! Ai fost admis la examenul de pilotaj.");
						format(string, MAXO_TEXT, "* Ti-a fost brevetul de zbor valabil pana la: "GALBEN"%s", DateToTimestamp(PlayerInfo[playerid][pFlyingLicense], 1));
						SendClientMessage(playerid, -1, string);
						SendClientMessage(playerid, COLOR_GRAD1, string);
						clear.string(string);
					}
				}
			}
			else if(pTestType{playerid} == TEST_TYPE_SAILING) {
				if(CarInfo[vID][cType] == VEHICLE_TYPE_BOATTEST) {
					if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 64.0870,-1861.9862,-0.3723)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,52.6557,-1522.2325,-0.4971,14.3312,-1332.9686,-0.5491,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 52.6557,-1522.2325,-0.4971)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,14.3312,-1332.9686,-0.5491,43.9599,-517.6404,-0.5737,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 14.3312,-1332.9686,-0.5491)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,43.9599,-517.6404,-0.5737,1869.7708,-74.7352,-0.4922,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 43.9599,-517.6404,-0.5737)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,1869.7708,-74.7352,-0.4922,2119.6782,92.4619,-0.1057,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 1869.7708,-74.7352,-0.4922)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,2119.6782,92.4619,-0.1057,2765.8096,580.1815,-0.5862,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 2119.6782,92.4619,-0.1057)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,2765.8096,580.1815,-0.5862,3581.6343,-3834.3601,-0.1511,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 2765.8096,580.1815,-0.5862)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,3581.6343,-3834.3601,-0.1511,397.9161,-2079.4922,-0.5332,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 3581.6343,-3834.3601,-0.1511)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,397.9161,-2079.4922,-0.5332,217.0749,-1952.8027,-0.4018,0);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 397.9161,-2079.4922,-0.5332)) {
						PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
						DeleteRaceCP(checkpointLicenses, playerid);
						CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,217.0749,-1952.8027,-0.4018,-9000,-4500,-0.4018,1);
					}
					else if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, 217.0749,-1952.8027,-0.4018)) {
						DeleteRaceCP(checkpointLicenses, playerid);
						SetVehicleToRespawn(vID);
						GameTextForPlayer(playerid, "~g~Admis", 5000, 3);
						RemovePlayerFromVehicle(playerid);
						Gas[vID] = GasMax;
						pTestType{playerid} = TEST_TYPE_NONE;
						PlayerInfo[playerid][pCash] -= (PlayerInfo[playerid][pLevel]*2000);
						SafeSetPlayerPos(playerid, 154.3131, -1941.2975, 3.7734);
						PlayerInfo[playerid][pSailingLicense] = gettime()+ExpiraLicenta;
						format(string, MAXO_TEXT, "UPDATE players SET SailingLicense = %d WHERE ID = %d", PlayerInfo[playerid][pSailingLicense], PlayerInfo[playerid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						format(string, MAXO_TEXT, "UPDATE players SET Cash = %d WHERE ID = %d", PlayerInfo[playerid][pCash], PlayerInfo[playerid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "Felicitari! Ai fost admis la examenul de navigat.");
						format(string, MAXO_TEXT, "* Ti-a fost licenta de navigat valabila pana la: "GALBEN"%s", DateToTimestamp(PlayerInfo[playerid][pSailingLicense], 1));
						SendClientMessage(playerid, -1, string);
						SendClientMessage(playerid, COLOR_GRAD1, string);
						clear.string(string);
					}
				}
			}
		}
		else if(CheckCP(checkpointid, checkpointFMARace, CP_FMA_RACE)) {
			if(RacePL[playerid][IdRace] != INVALID_RACE_ID) 
			{
				new
					c = RacePL[playerid][Checkpoint];
				if(!Race[RacePL[playerid][IdRace]][Started])
					return 1;
				//-- afisare info race
				new checkpointtype;
				if(Race[IDCursa][Air]) checkpointtype = RACE_CHECKPOINT_AIR;
				else checkpointtype = RACE_CHECKPOINT_NORMAL;
				if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) // in cazul in care intra in checkpoint fara sa fie sofer
				{
					format(string,sizeof(string),"[{A60099}FMARace{FFFFFF}] %s "ALB"entered in checkpoint on foot/passager.", PlayerName(playerid));
					SendFMARaceMessage(string);
					LeaveRace(playerid);
					return 1;
				}
				PlayerPlaySound(playerid,1138, 0.0, 0.0, 0.0);
				DeleteRaceCP(checkpointFMARace, playerid);
				if(RacePL[playerid][Checkpoint] == Race[IDCursa][CheckpointNr]) 
				{
					if(RacePL[playerid][RLap] == Race[IDCursa][Laps]) 
					{
						Race[IDCursa][Podium]++;
						switch (Race[IDCursa][Record])
						{
							case NO_RECORD_YET:
								NewRecordFMA(playerid);
							default:
							{
								if(RacePL[playerid][TimeRC] <= Race[IDCursa][Record]) 
									NewRecordFMA(playerid);
							}
						
						}
						if(Race[IDCursa][Chase]) 
						{
							foreach(Player, i) {
								if(RacePL[i][IdRace] == IDCursa && i!= playerid) 
								{
									if(RacePL[playerid][Points]>=RacePL[i][Points]) 
									{
										format(string,sizeof(string),"[{A60099}FMARace{FFFFFF}] %s"ALB" wons the chase race with {C14124}%d"ALB" points.",PlayerName(playerid),RacePL[playerid][Points]);
										SafeGivePlayerMoney(playerid,Race[IDCursa][Costs]*2);
									}
									else 
									{
										format(string,sizeof(string),"[{A60099}FMARace{FFFFFF}] %s"ALB" wons the chase race with {C14124}%d"ALB" points.",PlayerName(i),RacePL[i][Points]);
										SafeGivePlayerMoney(i,Race[IDCursa][Costs]*2);
									}
									SendFMARaceMessage(string);
									LeaveRace(i);
								}
							}
						}
						else 
						{
							format(string,sizeof(string),"[{A60099}FMARace{FFFFFF}] {446ED1}%s"ALB" finish the race. Position: {C14124}%d.",PlayerName(playerid),Race[IDCursa][Podium]);
							SendFMARaceMessage(string);
							new suma = floatround(Race[IDCursa][Costs]*Race[IDCursa][ParticipantsReady]*2/Race[IDCursa][Podium]),
								bonus = 50000,
								total = 0;
							// bonus
							if(strcmp(PlayerName(playerid), Race[IDCursa][RacePLRecord], true) == 0)
							{
								format(string, sizeof(string), "~y~Race Name: ~b~%s~n~~n~ ~y~Place ~g~%d~n~ ~y~Earned ~g~$~y~%s~n~ ~y~Bonus received ~g~$~y~%s",
									Race[IDCursa][Nome], Race[IDCursa][Podium], FormatNumber(suma, 0, ','), FormatNumber(bonus, 0, ','));
								total = suma + bonus;
							}
							else
							{
								format(string, sizeof(string), "~y~Race Name: ~b~%s~n~~n~ ~y~Place ~g~%d~n~ ~y~Earned ~g~$~y~%s",
									Race[IDCursa][Nome], Race[IDCursa][Podium], FormatNumber(suma, 0, ','));
								total = suma;
							}
							SafeGivePlayerMoney(playerid,total);
							ShowPlayerInformation(playerid, "Race Statistics", string);
						}
						LeaveRace(playerid);
						FinishRace(IDCursa);
						return 1;
					}
					else 
					{
						RacePL[playerid][RLap]++;
						CreateRaceCP(playerid,checkpointFMARace,CP_FMA_RACE,CheckpointRace[IDCursa][0][CXPos],CheckpointRace[IDCursa][0][CYPos],CheckpointRace[IDCursa][0][CZPos],CheckpointRace[IDCursa][1][CXPos],CheckpointRace[IDCursa][1][CYPos],CheckpointRace[IDCursa][1][CZPos],checkpointtype);
						RacePL[playerid][Checkpoint] = 0;
						if(Race[IDCursa][Laps] > 1 && Race[IDCursa][Chase] == 0) {
							format(string, sizeof(string), "~y~Race Name: ~b~%s~n~~n~ ~y~Laps ~g~%d ~y~of ~r~%d~n~ ~y~Checkpoint ~g~%d ~y~of ~r~%d",
								 Race[IDCursa][Nome], RacePL[playerid][RLap], Race[IDCursa][Laps], RacePL[playerid][Checkpoint], Race[IDCursa][CheckpointNr]);
							ShowPlayerInformation(playerid, "Race Statistics", string);
						}
						return 1;
					}
				}
				if(RacePL[playerid][Checkpoint] < Race[IDCursa][CheckpointNr]-1) 
				{
					RacePL[playerid][Checkpoint]++;
					c = RacePL[playerid][Checkpoint];
					CreateRaceCP(playerid,checkpointFMARace,CP_FMA_RACE,CheckpointRace[IDCursa][c][CXPos],CheckpointRace[IDCursa][c][CYPos],CheckpointRace[IDCursa][c][CZPos],CheckpointRace[IDCursa][c+1][CXPos],CheckpointRace[IDCursa][c+1][CYPos],CheckpointRace[IDCursa][c+1][CZPos],checkpointtype);
					return 1;
				}
				else if(RacePL[playerid][Checkpoint] == Race[IDCursa][CheckpointNr]-1) 
				{
					if(Race[IDCursa][Air]) checkpointtype = RACE_CHECKPOINT_FINAIR;
					else checkpointtype = RACE_CHECKPOINT_FINNORMAL;
					RacePL[playerid][Checkpoint]++;
					c = RacePL[playerid][Checkpoint];
					CreateRaceCP(playerid,checkpointFMARace,CP_FMA_RACE,CheckpointRace[IDCursa][c][CXPos],CheckpointRace[IDCursa][c][CYPos],CheckpointRace[IDCursa][c][CZPos],CheckpointRace[IDCursa][c+1][CXPos],CheckpointRace[IDCursa][c+1][CYPos],CheckpointRace[IDCursa][c+1][CZPos],checkpointtype);
					return 1;
				}
			}
		}
	}
	return 1;
}

#if defined _stream_checkpoints
public OnPlayerLeaveDynamicRaceCP(playerid, checkpointid) {
#else
public OnPlayerLeaveRaceCheckpoint(playerid) {
#endif
	return 1;
}

// End Of File ...
