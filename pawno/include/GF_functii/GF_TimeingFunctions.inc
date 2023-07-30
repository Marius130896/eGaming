/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/

#if defined GF_TimeingFunctions_included
	#endinput
#else
	#define GF_TimeingFunctions_included
#endif

function LoadTimersThread(timerid) {
	switch(timerid) {
		case 0: // other timer
		{
			SetTimer("OtherTimer", 1000, true);
			print("OtherTimer - called");
		}
		case 1: // Send Messages
		{
			SetTimer("SendMSG", 420000, true);
			print("SendMSG - called");			
		}
		case 2: // Disease PayDay
		{
			SetTimer("DiseasePayDay", 60000, true);
			print("DiseasePayDay - called");
		}
		case 3: // Disease Player Health
		{
			SetTimer("DiseasePlayerHealth", 30000, true);
			print("DiseasePlayerHealth - called");
		}
		case 4: // Aleator Contracts
		{
			SetTimer("AleatorContracts", 1800000, true);
			print("AleatorContracts - called");
		}
		case 5: // Check Gas
		{
			SetTimer("CheckGas", 15000, true);
			print("CheckGas - called");
		}
		case 6: // Show Menu In Business
		{
			SetTimer("ShowMenuInBusiness", 5000, false);
			print("ShowMenuInBusiness - called");
		}
		case 7: { // Server Unlocked
			ServerUnlocked = true;
			SendRconCommand("password 0");
		}
	}
	return true;
}

function FixHour(cHours) {
	cHours = timeshift + cHours;
	if (cHours < 0)
		cHours = cHours + 24;
	else if (cHours > 23)
		cHours = cHours - 24;
	shifthour = cHours;
	return true;
}

stock ShowPlayerDateTime(playerid) {
	TextDrawShowForPlayer(playerid, Logo);
	TextDrawShowForPlayer(playerid, TextdrawMonth);
	TextDrawShowForPlayer(playerid, TextdrawDay);
	TextDrawShowForPlayer(playerid, TextdrawHour);
}

function DiseasePlayerHealth() {
	foreach(Player, i) {
		new Float:viata;
		GetPlayerHealth(i, viata);
		SetPlayerHealth(i, viata - 0.3);
	}
	return true;
}

function OtherTimer() {
	new
		string[MAXO_TEXT], vID;
	foreach(new i : Player) {
		vID = GetPlayerVehicleID(i);
		if(gPlayerLogged{i}) {
			SetPlayerMoney(i, PlayerInfo[i][pCash]);
			SetPlayerScore(i, PlayerInfo[i][pLevel]);
			if(PlayerInfo[i][pDeelayNeedHelp] != 0) {
				PlayerInfo[i][pDeelayNeedHelp] --;
				if(PlayerInfo[i][pDeelayNeedHelp] == 0)
					PlayerInfo[i][pDeelayNeedHelp] = 0;
			}
			if(PlayerInfo[i][pMuteTime] != 0) {
				PlayerInfo[i][pMuteTime] --;
				if(PlayerInfo[i][pMuteTime] == 0) {
					PlayerInfo[i][pMuteTime] = 0;
					PlayerInfo[i][pMute] = 0;
				}
			}
			if(PlayerInfo[i][pJailTime] != 0) {
				PlayerInfo[i][pJailTime] --;
				if(PlayerInfo[i][pJailTime] == 0) {
					PlayerInfo[i][pJailTime] = 0;
					PlayerInfo[i][pJailed] = 0;
					SafeSetPlayerInterior(i, 0);
					SafeSetPlayerVirtualWorld(i, 0);
					SafeSetPlayerPos(i, 1545.6927, -1675.9683, 13.5609);
					format(string, MAXO_TEXT, "UPDATE players SET Jailed = %d WHERE ID = %d", PlayerInfo[i][pJailed], PlayerInfo[i][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					SendClientMessage(i, COLOR_GRAD1, "You have paid your debt to society.");
					GameTextForPlayer(i, "~g~Freedom~n~~w~Try to be a better citizen", 5000, 1);
				}
			}
			if(PlayerInfo[i][pUsePillsTime] != 0) {
				PlayerInfo[i][pUsePillsTime] --;
				if(PlayerInfo[i][pUsePillsTime] == 0)
					PlayerInfo[i][pUsePillsTime] = 0;
			}
			if(PlayerInfo[i][pReportTime] != 0) {
				PlayerInfo[i][pReportTime] --;
				if(PlayerInfo[i][pReportTime] == 0)
					PlayerInfo[i][pReportTime] = 0;
			}
			if(ClientAccept[i] != INVALID_PLAYER_ID) {
				new
					Float: Pos[3],
					pID = ClientAccept[i];
				GetPlayerPos(pID, Pos[0], Pos[1], Pos[2]);
				CreateCP(i,Pos[0],Pos[1],Pos[2],5.0,checkpointCaller,CP_CALLER);
			}
		    if(CellTime[i] > 0) {
				if (CellTime[i] == cchargetime) {
					CellTime[i] = 1;
					if(Mobile[Mobile[i]] == i) {
						CallCost[i] = CallCost[i]+callcost;
					}
				}
				CellTime[i] = CellTime[i] +1;
				if (Mobile[Mobile[i]] == 255 && CellTime[i] == 5) {
				    if(IsPlayerConnected(Mobile[i])) {
						format(string, sizeof(string), "* %s's phone rings.", PlayerName(Mobile[i]));
						RingTone[Mobile[i]] = 10;
						SendPlayerMessage(30.0, Mobile[i], string, COLOR_PURPLE);
					}
				}
			}
			if(CellTime[i] == 0 && CallCost[i] > 0) {
				format(string, MAXO_TEXT, "~w~The call cost~n~~r~$%d", CallCost[i]);
				SafeGivePlayerMoney(i, -CallCost[i]);
				GameTextForPlayer(i, string, 5000, 1);
				CallCost[i] = 0;
			}
			if(TaxiST[i][InTaxi] == 1) {
				new sofer;
				sofer = TaxiST[i][DrivingTaxi];
				if(sofer != INVALID_PLAYER_ID && TaxiST[sofer][TaxiDuty] == 1) {
					if(GetPlayerState(i) == PLAYER_STATE_PASSENGER) {
						new vehicleid, Float:speed_x, Float:speed_y, Float:speed_z, distanta, ValoareAdaugata;
						vehicleid = GetPlayerVehicleID(i);
						GetVehicleVelocity(vehicleid, speed_x, speed_y, speed_z);
						distanta = floatround((floatsqroot(((speed_x * speed_x) + (speed_y * speed_y)) + (speed_z * speed_z)) * 158.179)/7.2);
						ValoareAdaugata = TransportValue[sofer] * distanta/13;
						if(IsPlayerInVehicle(sofer, vehicleid) && GetPlayerState(sofer) == PLAYER_STATE_DRIVER) {
							if(PlayerInfo[i][pCash] > TaxiST[i][TaxiEarn]) {
								TaxiST[i][TaxiEarn] += ValoareAdaugata;
								format(string, MAXO_TEXT, "~y~Ride Cost~g~$%d", TaxiST[i][TaxiEarn]);
								GameTextForPlayer(i, string, 4000, 6);
								GameTextForPlayer(sofer, string, 4000, 6);
							}
							else
							{
								format(string, MAXO_TEXT, "%s left the taxi because he couldnt afford anymore time.", PlayerName(i));
								SendClientMessage(sofer, COLOR_WHITE, string);
								RemovePlayerFromVehicle(i);
								TaxiST[i][TaxiEarn] = TransportValue[sofer];
								TaxiST[i][InTaxi] = 0;
								TaxiST[i][DrivingTaxi] = INVALID_PLAYER_ID;
							}
						}
						else
						{
							RemovePlayerFromVehicle(i);
							TaxiST[i][TaxiEarn] = TransportValue[sofer];
							TaxiST[i][InTaxi] = 0;
							TaxiST[i][DrivingTaxi] = INVALID_PLAYER_ID;
						}
					}
					else
					{
						format(string, MAXO_TEXT, "* You paid %s $%s for the amount of fare you owned him.", PlayerName(sofer), FormatNumber(TaxiST[i][TaxiEarn], 0, '.' ));
						SendClientMessage(i, COLOR_WHITE, string);
						format(string, sizeof(string), "* You earned $%s from passenger %s.", FormatNumber(TaxiST[i][TaxiEarn], 0, '.' ), PlayerName(i));
						SendClientMessage(sofer, COLOR_WHITE, string);
						new tlabel[20];
						format(tlabel, 20, "~r~-%d~y~$", TaxiST[i][TaxiEarn]);
						GameTextForPlayer(i, tlabel, 1500, 1);
						format(tlabel, 20, "~b~+%d~y~$", TaxiST[i][TaxiEarn]);
						GameTextForPlayer(sofer, tlabel, 1500, 1);
						SafeGivePlayerMoney(sofer, TaxiST[i][TaxiEarn]);
						SafeGivePlayerMoney(i, -TaxiST[i][TaxiEarn]);
						TaxiST[i][TaxiEarn] = TransportValue[sofer];
						TaxiST[i][InTaxi] = 0;
						TaxiST[i][DrivingTaxi] = INVALID_PLAYER_ID;
					}
				}
				else
				{
					if(GetPlayerState(i) == PLAYER_STATE_PASSENGER) {
						SendClientMessage(i, COLOR_WHITE, "Taxi Driver, has left vehicle / That taxi has no driver.");
						RemovePlayerFromVehicle(i);
						TaxiST[i][TaxiEarn] = TransportValue[sofer];
						TaxiST[i][InTaxi] = 0;
						TaxiST[i][DrivingTaxi] = INVALID_PLAYER_ID;
					}
				}
			}
		}
		if(PlayerInfo[i][pCarTime] != 0) {
			PlayerInfo[i][pCarTime] --;
			if(PlayerInfo[i][pCarTime] == 0)
				PlayerInfo[i][pCarTime] = 0;
		}
		if(PlayerInfo[i][pTakeVehiclePause]) {
			PlayerInfo[i][pTakeVehiclePause] --;
			if(PlayerInfo[i][pTakeVehiclePause] == 0)
				PlayerInfo[i][pTakeVehiclePause] = 0;
		}
		if(PlayerInfo[i][pAdvertismentTime] != 0) {
			PlayerInfo[i][pAdvertismentTime] --;
			if(PlayerInfo[i][pAdvertismentTime] == 0)
				PlayerInfo[i][pAdvertismentTime] = 0;
		}
		if(PlayerInfo[i][pDrugsTime] != 0) {
			PlayerInfo[i][pDrugsTime] --;
			if(PlayerInfo[i][pDrugsTime] == 0)
				PlayerInfo[i][pDrugsTime] = 0;
		}
		if(PlayerStoned[i] >= 2) {
			PlayerStoned[i] ++;
			if(PlayerStoned[i] > 10) {
				PlayerStoned[i] = 2;
				new Float:angle;
				GetPlayerFacingAngle(i, angle);
				if(GetPlayerVehicleID(i) != INVALID_VEHICLE_ID)
					if(GetPlayerState(i) == PLAYER_STATE_DRIVER) {
						SetVehicleZAngle(GetPlayerVehicleID(i), angle + 25);
					}
					else
						SetPlayerFacingAngle(i, angle + 90);
				SetPlayerDrunkLevel(i, 2050);
			}
		}
		if(NewbieChatTimer[i] != 0) {
			NewbieChatTimer[i] --;
			if(NewbieChatTimer[i] == 0)
				NewbieChatTimer[i] = 0;
		}
		if(PlayerInfo[i][pDisableTime] != 0) {
			PlayerInfo[i][pDisableTime] --;
			if(PlayerInfo[i][pDisableTime] == 0) {
				PlayerInfo[i][pDisableTime] = 0;
				PlayerInfo[i][pDisable] = 0;
				format(string, MAXO_TEXT, "UPDATE players SET DisableTime = %d, Disable = %d WHERE ID = %d", PlayerInfo[i][pDisableTime], PlayerInfo[i][pDisable], PlayerInfo[i][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			}
		}
		//================================>%=============================
		// se contorizeaza doar daca playerul nu este afk
		if(!IsPlayerPaused(i)) {
			IncreasePayCheck(i);
			if(GetPlayerState(i) == PLAYER_STATE_DRIVER) {
				new Float:chealth, status[MAX_PLAYER_NAME];
				if(!IsVehicleBike(vID) && !IsVehicleBoat(vID) && !IsVehiclePlane(vID)) {
					new engine, lights, alarm, doors, bonnet, boot, objective;
					GetVehicleHealth(vID, chealth);
					GetVehicleParamsEx(vID, engine, lights, alarm, doors, bonnet, boot, objective);
					if(doors == VEHICLE_PARAMS_OFF) { status = "~r~~h~Locked~w~"; }
					else { status = "~g~~h~Unlocked~w~"; }
					if(CarInfo[vID][cType] == VEHICLE_TYPE_PERSONAL)
						format(string, 512, "~n~~n~~n~Speed: %d km/h~n~Fuel: %d%s~w~~n~Doors: %s~n~Kilometers: %.2f", GetVehicleSpeed(vID), Gas[vID], "%", status, CarInfo[vID][cKM]);
					else
						format(string, 512, "~n~~n~~n~Speed: %d km/h~n~Fuel: %d%s~w~~n~Doors: %s", GetVehicleSpeed(vID), Gas[vID], "%", status);
					PlayerTextDrawSetString(i, Speedo, string);
					PlayerTextDrawShow(i, Speedo);	
					VehHUpd(i, chealth);
				}
			}
			if(PlayerInfo[i][pFarmingTime] != 0) {
				if(IsPlayerInArea(i, -618.9274, -1646.58, -46.7115, -1261.211)) {
					if(GetVehicleSpeed(vID) > 24) {
						PlayerInfo[i][pFarmingTime] --;
						format(string, PInfo_MAX_STRING, "Trebuie sa mergi cu acest vehicul timp de ~r~%s minute ~y~cu o viteza > de 25 km/h pentru a indeplini misiunea de recoltare.", ConvertTime(PlayerInfo[i][pFarmingTime]));
						ShowPlayerInformation(i, "Farmer Job", string);
						if(PlayerInfo[i][pFarmingTime] == 0) {
							PlayerInfo[i][pFarmingTime] = 0;
							HidePlayerInformation(i);
							FarmCantitate[i] = 1;
							SendClientMessage(i, COLOR_ORANGE, "INFO: Fermierul ti-a oferit un sac cu grau drept rasplata pentru munca ta.");
							SendClientMessage(i, COLOR_ORANGE, "INFO: Mergi la checkpointul setat pe minimap, pentru a vinde sacul folosind /sellbag.");
							CreateCP(i,-87.9676,-29.1070,3.1172,3.0,checkpointNoAction,CP_NO_ACTION);
							SetVehicleToRespawn(vID);

							new vehicleID = INVALID_VEHICLE_ID;

							vehicleID = CreateVehicle(422, -410.0577, -1426.4757, 25.7152, 89.6585, -1, -1, 15);

							if(vehicleID != INVALID_VEHICLE_ID) {
								CarInfo[vehicleID][cModel] = 422;
								CarInfo[vehicleID][cType] = VEHICLE_TYPE_FARMER_B;
								gLastDriver[vehicleID] = i;
								CarInfo[vehicleID][cRespawnTime] = 15;
								CarInfo[vehicleID][cHealth] = 1000.0;
								CarInfo[vehicleID][cValue] = 0;
								CarInfo[vehicleID][cFactionID] = FACT_CIVIL;
								CarInfo[vehicleID][cRank] = 0;
								CarInfo[vehicleID][cBiz] = 0;
								CarInfo[vehicleID][cLastBroken] = gLocalTimeStamp+86400;
								CarInfo[vehicleID][cEngine] = false;
								CarInfo[vehicleID][cLock] = 0;
								new engine, lights, alarm, doors, bonnet, boot, objective;
								GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
								SetVehicleParamsEx(vehicleID, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
								Gas[vehicleID] = GasMax;
								StopCarRadio(vehicleID);
								SetVehicleNumberPlate(vehicleID, "eG 01 FRM");
								PutPlayerInVehicle(i, vehicleID, 0);
							}
						}
					} else format(string, PInfo_MAX_STRING, "Trebuie sa mergi cu acest vehicul timp de ~r~%s minute ~y~cu o viteza > de 25 km/h pentru a indeplini misiunea de recoltare.", ConvertTime(PlayerInfo[i][pFarmingTime])), ShowPlayerInformation(i, "Farmer Job", string);
				} else ShowPlayerInformation(i, "Farmer Job", "Ai parasit zona de lucru. Pentru a continua misiunea de recoltare, intoarce-te pe Farming Turf.");
			}
			if(PlayerInfo[i][pWantedDown]) {
				PlayerInfo[i][pWantedDown] --;
				if(!PlayerInfo[i][pWantedDown]) {
					PlayerInfo[i][pWlvl] --;
					SetPlayerWanted(i, INVALID_PLAYER_ID, PlayerInfo[i][pWlvl]);
					if(PlayerInfo[i][pWlvl])
						PlayerInfo[i][pWantedDown] = 60 * WANTED_DOWN_TIME;
				}
				UpdateWantedDown(i, PlayerInfo[i][pWantedDown]);
			}
		}
		if(gFindMCarTime[i] != 0) {
			gFindMCarTime[i] --;
			if(gFindMCarTime[i] == 0)
				gFindMCarTime[i] = 0;
		}
	}
	//==========================%<=======================
	// -- copyrighted
	for(new z = 0; z < MAX_TURFS; z ++) {
		if(TurfInfo[z][TurfWarStarted] > 0) {
			TurfInfo[z][TurfWarStarted] --;
			foreach(new i : Player) {
				if(gPlayerLogged{i}) {
					if(PlayerInfo[i][pFactiune] == TurfInfo[z][TurfOwner]) {
						format(string, MAXO_TEXT, "~y~Turf Name: ~r~%s~n~~y~Faction Score: ~r~%d~n~~y~Time Left: ~r~%s",
						TurfInfo[z][TurfName], TeamInfo[PlayerInfo[i][pFactiune]][TeamScore], ConvertTime(TurfInfo[z][TurfWarStarted]));
						ShowPlayerInformation(i, "Rival-War Statistics", string);
					}
					if(PlayerInfo[i][pFactiune] == TurfInfo[z][TurfAttacker]) {
						format(string, MAXO_TEXT, "~y~Turf Name: ~r~%s~n~~y~Faction Score: ~r~%d~n~~y~Time Left: ~r~%s",
						TurfInfo[z][TurfName], TeamInfo[PlayerInfo[i][pFactiune]][TeamScore], ConvertTime(TurfInfo[z][TurfWarStarted]));
						ShowPlayerInformation(i, "Rival-War Statistics", string);
					}
					if(TurfInfo[z][TurfWarStarted] == 0) {
						StopRivalWarsBetweenPlayers(z, TurfInfo[z][TurfAttacker], TurfInfo[z][TurfOwner]);
					}
				}
			}
		}
	}
	new tmphour, tmpminute, tmpsecond;
	gettime(tmphour, tmpminute, tmpsecond);
	FixHour(tmphour);
	tmphour = shifthour;
	if((tmphour > ghour) || (tmphour == 0 && ghour == 23)) {
		format(string, MAXO_TEXT1, "SERVER: The time is now %d:00 hours.", tmphour + 1);
		OOCNews(COLOR_WHITE, string);
		ghour = tmphour;
		if (realtime)
			SetWorldTime(tmphour);
	}

	#tryinclude <GF_functii/_private/GF_AntiCheatChecker-private>

	new ServerHour, ServerMinute, ServerSecond;
	new Year, Month, Day;

	gettime(ServerHour, ServerMinute, ServerSecond);
	getdate(Year, Month, Day);

	format(string, MAXO_TEXT1, "%02d:%02d", ServerHour, ServerMinute);
	TextDrawSetFormat(TextdrawHour, string);
	for(new i = 0; i < GetMaxPlayers(); i++) {
		SetPlayerTime(i, ServerHour, ServerMinute);
	}

	if(ServerHour == 6 && ServerMinute == 00 && ServerSecond == 00)
		ResetPlayerMission();
	if(IsWeekendDays()) 
		SendRconCommand("hostname [0.3.7] eGaming RPG Server: Happy Week!");
	else
		SendRconCommand("hostname [BETA] eGaming RP: Think different, think eGaming!");

	TextDrawSetFormat(TextdrawDay, "%02d", Day);
	TextDrawSetFormat(TextdrawMonth, "%02d", Month);

	switch(Month) {
		case IANUARIE: TextDrawSetString(TextdrawMonth, "Ianuarie");
		case FEBRUARIE: TextDrawSetString(TextdrawMonth, "Februarie");
		case MARTIE: TextDrawSetString(TextdrawMonth, "Martie");
		case APRILIE: TextDrawSetString(TextdrawMonth, "Aprilie");
		case MAI: TextDrawSetString(TextdrawMonth, "Mai");
		case IUNIE: TextDrawSetString(TextdrawMonth, "Iunie");
		case IULIE: TextDrawSetString(TextdrawMonth, "Iulie");
		case AUGUST: TextDrawSetString(TextdrawMonth, "August");
		case SEPTEMBRIE: TextDrawSetString(TextdrawMonth, "Septembrie");
		case OCTOMBRIE: TextDrawSetString(TextdrawMonth, "Octombrie");
		case NOIEMBRIE: TextDrawSetString(TextdrawMonth, "Noiembrie");
		case DECEMBRIE: TextDrawSetString(TextdrawMonth, "Decembrie");
	}
	if(ServerHour == 22)
		SetWorldTime(22);
	else
		SetWorldTime(ServerHour);
	clear.string(string);
	return true;
}


// End Of File ...
