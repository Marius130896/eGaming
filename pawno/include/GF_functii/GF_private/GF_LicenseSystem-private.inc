/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_LicenseSystem_included
	#endinput
#else
	#define GF_LicenseSystem_included
#endif

#pragma unused DriverTestTimer
#pragma unused DMVT

new
	DriverTestTimer[MAX_PLAYERS],
	DMVT[MAX_PLAYERS]
;

stock IsVehicleNoLicense(vehicleid) {
	switch(GetVehicleModel(vehicleid)) {
		case 462, 481, 509, 510: return true;
	}
	return false;
}

function DrivingTest2(playerid) {
	#if defined _stream_objects
		MoveDynamicObject(poartaDMV1, 320.7399,-1488.0225,21.8870, 1);
	#else
		MoveObject(poartaDMV1, 320.7399,-1488.0225,21.8870, 1);
	#endif
	SetTimer("CloseDMVGate1", 30000, false);
	CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,363.6036,-1468.5726,30.8122,329.5655,-1536.8867,32.9324,0);
}

function DrivingTest3(playerid) {
	CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,329.5655,-1536.8867,32.9324,343.8846,-1646.0770,32.7906,0);
}

function PlayerLeaveCarTest(playerid, vID) {
	if(DMVTimer{playerid}) {
		ClearChatBox(playerid, 5);
		PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
		PlayerPlayMusic(playerid);
		SetCameraBehindPlayer(playerid);
		SetVehicleToRespawn(vID);
	  	SendClientMessage(playerid, COLOR_LIGHTRED, "Atentie! "ALB"Ai fost declarat respins, la proba practica !");
		GameTextForPlayer(playerid, "~r~Respins!", 3000, 3);
	  	TakingLesson{playerid} = false;
		DMVTimer{playerid} = false;
		DeleteRaceCP(checkpointLicenses, playerid);
		switch(pTestType{playerid}) {
			case TEST_TYPE_CAR: SafeSetPlayerPos(playerid, 331.7640, -1515.6975, 35.8672);
			case TEST_TYPE_FLYING: SafeSetPlayerPos(playerid, 1521.0065, -2438.7390, 13.5547);
			case TEST_TYPE_SAILING: SafeSetPlayerPos(playerid, 154.1533, -1946.6228, 5.3903);
		}
		SafeSetPlayerVirtualWorld(playerid, 0);
		pTestType{playerid} = TEST_TYPE_NONE;
	}
	return true;
}

stock IsPlayerDeadInExam(playerid) {
	new vID = GetPlayerVehicleID(playerid);
	switch(pTestType{playerid}) {
		case TEST_TYPE_CAR: SafeSetPlayerPos(playerid, 331.7640, -1515.6975, 35.8672);
		case TEST_TYPE_FLYING: SafeSetPlayerPos(playerid, 1521.0065, -2438.7390, 13.5547);
		case TEST_TYPE_SAILING: SafeSetPlayerPos(playerid, 154.1533, -1946.6228, 5.3903);
	}
	if(pTestType{playerid} == TEST_TYPE_CAR) {
		TakingLesson{playerid} = false;
		pTestType{playerid} = TEST_TYPE_NONE;
		DeleteRaceCP(checkpointLicenses, playerid);
		GameTextForPlayer(playerid, "~r~Respins", 5000, 3);
		SetVehicleToRespawn(vID);
		SendClientMessage(playerid, COLOR_LIGHTRED, "Atentie! "ALB"Ai fost declarat respins, la proba practica !");
		SafeSetPlayerVirtualWorld(playerid, 0);
	}
	else if(pTestType{playerid} == TEST_TYPE_FLYING) {
		TakingLesson{playerid} = false;
		pTestType{playerid} = TEST_TYPE_NONE;
		DeleteRaceCP(checkpointLicenses, playerid);
		GameTextForPlayer(playerid, "~r~Respins", 5000, 3);
		SetVehicleToRespawn(vID);
		SendClientMessage(playerid, COLOR_LIGHTRED, "Atentie! "ALB"Ai fost declarat respins, la proba practica !");
		SafeSetPlayerVirtualWorld(playerid, 0);
	}
	else if(pTestType{playerid} == TEST_TYPE_SAILING) {
		TakingLesson{playerid} = false;
		pTestType{playerid} = TEST_TYPE_NONE;
		DeleteRaceCP(checkpointLicenses, playerid);
		GameTextForPlayer(playerid, "~r~Respins", 5000, 3);
		SetVehicleToRespawn(vID);
		SendClientMessage(playerid, COLOR_LIGHTRED, "Atentie! "ALB"Ai fost declarat respins, la proba practica !");
		SafeSetPlayerVirtualWorld(playerid, 0);
	}
	return true;
}


stock DMVOnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	#pragma unused inputtext
	#pragma unused listitem
	new string[MAXO_TEXT];
	switch(dialogid) {
		case DIALOGID_DMV_ACTION: {
			if(response) {
				if(Tutorial[playerid] && PlayerInfo[playerid][pDrivingLicense] == 0) {
					pTestType{playerid} = TEST_TYPE_CAR;
					TakingLesson{playerid} = true;
					SafeSetPlayerPos(playerid, 298.2368, -1496.2021, 24.9219);
					SafeSetPlayerFacingAngle(playerid, 231.7178);
					SafeSetPlayerVirtualWorld(playerid, DMV_VW);
					CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,301.8990,-1485.2570,24.3287,363.6036,-1468.5726,30.8122,0);
					ClearChatBox(playerid, 5);
					format(string, MAXO_TEXT, ""GALBEN"			Indicatii catre elevul %s!", PlayerName(playerid));
					SendClientMessage(playerid, -1, string);
					SendClientMessage(playerid, -1, "");
					SendClientMessage(playerid, -1, ""GALBEN"			- Parcarea vehiculului -");
					SendClientMessage(playerid, -1, "");
					SendClientMessage(playerid, -1, "» Urca-te in masina de test, apoi parcheaza in checkpointul "ROSU"rosu"ALB".");
					SendClientMessage(playerid, COLOR_RED, "Atentie! "ALB"Trebuie sa parchezi intre liniile albe, marcate pe asfalt, altfel vei fi");
					SendClientMessage(playerid, -1, "... declarat respins la aceasta proba. Fii atent!");
				}
				else
				{
					if(PlayerInfo[playerid][pDrivingLicense] == 0 && PlayerInfo[playerid][pTut] == 1) {
						PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
						ClearChatBox(playerid, 5);
						SafeGivePlayerMoney(playerid, -(PlayerInfo[playerid][pLevel]*2500));
						PlayerPlayMusic(playerid);
						PlayerInfo[playerid][pDrivingLicense] = gettime()+ExpiraLicenta;
						format(string, MAXO_TEXT, "UPDATE players SET DrivingLicense = %d WHERE ID = %d", PlayerInfo[playerid][pDrivingLicense], PlayerInfo[playerid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						SendClientMessage(playerid, COLOR_GREEN, "________________________________________________");
						SendClientMessage(playerid, -1, "* Felicitari! Ti-ai reinnoit permisul de conducere.");
						format(string, MAXO_TEXT, "* Ti-a fost inmanat permisul de conducere valabil pana la: "GALBEN"%s", DateToTimestamp(PlayerInfo[playerid][pDrivingLicense], 1));
						SendClientMessage(playerid, -1, string);
						clear.string(string);
					} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Driving Motor Vehicle", "This exam was beed cancelled.\nYou have already a driving license valid.", "Close", "");
				}
			} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Driving Motor Vehicle Info", "This exam was been cancelled.", "Close", "");
		}
		case DIALOGID_DMP_ACTION: {
			if(response) {
				if(PlayerInfo[playerid][pFlyingLicense] == 0) {
					ClearChatBox(playerid, 20);
					pTestType{playerid} = TEST_TYPE_FLYING;
					TakingLesson{playerid} = true;
					CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,1485.8119,-2492.1541,13.7311, 1638.2096,-2489.6609,40.9067,4);
					SendClientMessage(playerid, -1, ""GALBEN"Indicatii");
					SendClientMessage(playerid, -1, "");
					SendClientMessage(playerid, COLOR_RADIO, "Urca intr-un elicoper, si urmeaza ruta de checkpointuri;");
					SendClientMessage(playerid, COLOR_RADIO, "Daca checkpointurile nu sunt in raza campului vizual, ghideaza-te dupa minimap.");
					SendClientMessage(playerid, COLOR_RADIO, "Succes!");
				} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Driving Motor Plane", "This exam was beed cancelled.\nYou have already a flying license valid.", "Close", "");
			} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Driving Motor Plane Info", "This exam was been cancelled.", "Close", "");
		}
		case DIALOGID_DMB_ACTION: {
			if(response) {
				if(PlayerInfo[playerid][pSailingLicense] == 0) {
					ClearChatBox(playerid, 20);
					pTestType{playerid} = TEST_TYPE_SAILING;
					TakingLesson{playerid} = true;
					CreateRaceCP(playerid,checkpointLicenses,CP_LICENSES,64.0870,-1861.9862,-0.3723,8.1471,-1867.0076,-0.5757,1);
					SendClientMessage(playerid, -1, ""GALBEN"Indicatii");
					SendClientMessage(playerid, -1, "");
					SendClientMessage(playerid, COLOR_RADIO, "Urca intr-o barca, si urmeaza ruta de checkpointuri;");
					SendClientMessage(playerid, COLOR_RADIO, "Daca checkpointurile nu sunt in raza campului vizual, ghideaza-te dupa minimap.");
					SendClientMessage(playerid, COLOR_RADIO, "Succes!");
				} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Driving Motor Boat", "This exam was beed cancelled.\nYou have already a sailing license valid.", "Close", "");
			} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Driving Motor Boat Info", "This exam was been cancelled.", "Close", "");
		}
	}
	return true;
}

// End Of File ...
