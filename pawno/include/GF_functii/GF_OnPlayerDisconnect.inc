/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_OnPlayerDisconnect_included
	#endinput
#else
	#define GF_OnPlayerDisconnect_included
#endif

public OnPlayerDisconnect(playerid, reason) {
	new
		string[MAXO_TEXT];
	SavePlayerData(playerid);
	SpecPStateOnDiscon(playerid);
	DestroyDealerTDForPlayer(playerid);
	HidePlayerInformation(playerid);
	TextDrawDestroy(DigiHP[playerid]);
	TextDrawDestroy(DigiAP[playerid]);
	if(PlayerInfo[playerid][pFarmingTime] > 0) {
		PlayerInfo[playerid][pFarmingTime] = 0;
	}
	if(HireCar[playerid] != INVALID_PLAYER_ID) {
		SetVehicleToRespawn(HireCar[playerid]);
		HireCar[playerid] = INVALID_PLAYER_ID;
	}
	if(HaveAPersonalCar(playerid))
		DespawnVehicle(playerid);
	if(JOBVehicleTimer[playerid]) {
		for(new v; v < MAX_VEHICLES; v++) {
			if(IsAJOBVehicle(v)) {
				if(gLastDriver[v] == playerid) {
					SetVehicleToRespawn(v);
				}
			}
		}
		KillTimer(JOBVehicleTimer[playerid]);
		JOBVehicleTimer[playerid] = INVALID_VJOB_TIMER;
	}
	if(GetPlayerVehicleID(playerid)) {
		if(IsAJOBVehicle(GetPlayerVehicleID(playerid))) {
			SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		}
	}
	if(GotHit[playerid] != 0) {
	    if(GetChased[playerid] < 999) {
	        if(GetChased[playerid] != INVALID_PLAYER_ID) {
	        	SendClientMessage(GetChased[playerid], COLOR_YELLOW, "Your Hit has left the server.");
	            GoChase[GetChased[playerid]] = 999;
			}
	    }
	}
	if(TaxiST[playerid][InTaxi]) {
		if(TaxiST[playerid][DrivingTaxi] != INVALID_PLAYER_ID) {
			if(gPlayerLogged{TaxiST[playerid][DrivingTaxi]}) {
				new stringTrans[64], suma;
				suma = TaxiST[playerid][TaxiEarn];
				SafeGivePlayerMoney(playerid, -suma);
				SafeGivePlayerMoney(TaxiST[playerid][DrivingTaxi], suma);
				format(stringTrans, 64, "~w~Passenger left~n~~g~Earned $%d", suma);
				GameTextForPlayer(TaxiST[playerid][DrivingTaxi], stringTrans, 5000, 1);
				TaxiST[playerid][InTaxi] = 0;
				TaxiST[playerid][DrivingTaxi] = INVALID_PLAYER_ID;
				clear.string(stringTrans);
			}
		}
	}
	new cursa = RacePL[playerid][IdRace];
	if(cursa != INVALID_RACE_ID)  {
		if(Race[cursa][Started]) {
			if(Race[cursa][Chase]) {
				foreach(Player, i) {
					if(RacePL[i][IdRace] == cursa && i != playerid) {
						format(string,sizeof(string),"[{A60099}FMARace{FFFFFF}] %s"ALB" wons the race because the opponent disconnected.",PlayerName(i));
						SendFMARaceMessage(string);
						SafeGivePlayerMoney(i,Race[RacePL[i][IdRace]][Costs]*2);
						LeaveRace(i);
					}
				}
			}
		}
		LeaveRace(playerid);
	}
	return 1;
}

// End Of File ...
