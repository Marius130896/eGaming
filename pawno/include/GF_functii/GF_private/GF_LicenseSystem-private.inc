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

new
    TargetObject = INVALID_OBJECT_ID,
	InGunCount,
	Float:space[3],
	tinteGtest
;

new
	PInGunTest[MAX_PLAYERS char],
	inguntest, 
	timpGtest, 
	NrTinteGtest 
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

stock LoadWeaponSkill(playerid) {
	new string[MAXO_TEXT];
	format(string, MAXO_TEXT, "SELECT GunLicType FROM players_licenses WHERE PlayerID = %d", PlayerInfo[playerid][pSQLID]);
	mysql_tquery(connectionHandle, string, "LoadWSkillThd", "d", playerid);
	return true;
}

function LoadWSkillThd(extraid) {
	if(extraid != INVALID_PLAYER_ID) {
		if(cache_get_row_count()) {
			gDynPlayerInfo[extraid][pGunLicType] = cache_get_row_int(0, 2);
		} else gDynPlayerInfo[extraid][pGunLicType] = 0;
		CheckWeaponLicense(extraid);
	}
	return true;
}

stock CheckWeaponLicense(playerid) {
	new string[MAXO_TEXT];
	format(string, MAXO_TEXT, "SELECT GunLic FROM players WHERE ID = %d",PlayerInfo[playerid][pSQLID]);
	mysql_tquery(connectionHandle, string, "CheckWeapExpThd", "d", playerid);
	return true;
}

function CheckWeapExpThd(extraid) {
	if(extraid != INVALID_PLAYER_ID) {
		if(cache_num_rows()) {
			PlayerInfo[extraid][pGunLic] = cache_get_row_int(0, 82);
			SetPlayerWeaponSkill(extraid);
			if(ISBetween(PlayerInfo[extraid][pGunLic], 10 ,gettime())) {
				new string[MAXO_TEXT];
				gDynPlayerInfo[extraid][pGunLicType] = 0;
				format(string, sizeof(string), "INSERT INTO players_licenses (PlayerID,GunLicType) VALUES (%d,%d) ON DUPLICATE KEY UPDATE GunLicType = %d",PlayerInfo[extraid][pSQLID], gDynPlayerInfo[extraid][pGunLicType], gDynPlayerInfo[extraid][pGunLicType]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			}
		}
	}
    return true;
}

stock SetPlayerWeaponSkill(playerid) {
	new Experienta;
	if(PlayerInfo[playerid][pGunLic] > gLocalTimeStamp) {
		if(gDynPlayerInfo[playerid][pGunLicType] == 2) Experienta = 1200;
		else Experienta = 400;
	}
	else Experienta = 100;
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, Experienta);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, Experienta);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, Experienta);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, Experienta);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, Experienta);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, Experienta);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, Experienta);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, Experienta);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, Experienta);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, Experienta);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, Experienta);
	return true;
}

function Count(playerid) {
	if(InGunCount == 0) InGunCount = 1, GameTextForPlayer(playerid, "~p~3", 5000, 3),SetTimerEx("Count", 1001, 0, "i", playerid), PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
	else if(InGunCount == 1) InGunCount = 2, GameTextForPlayer(playerid, "~p~2", 5000, 3),SetTimerEx("Count", 1002, 0, "i", playerid), PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
	else if(InGunCount == 2) InGunCount = 3, GameTextForPlayer(playerid, "~p~1", 5000, 3),SetTimerEx("Count", 1003, 0, "i", playerid), PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
	else if(InGunCount == 3) InGunCount = 0, GameTextForPlayer(playerid, "~W~Begin", 5000, 3), StartGunTest(playerid),SetTimerEx("NumaratoareGun", 1004, 0, "i", playerid), TogglePlayerControllable(playerid, 1), PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
	return true;
}

function CDPart(playerid) {
	new string[MAXO_TEXT1];
	PInGunTest{playerid} = 1;
	inguntest = 1;
	ResetPlayerWeapons(playerid);
	SetPlayerInterior(playerid, 1);
	SetCameraBehindPlayer(playerid);
	SetPlayerPos(playerid, 292.3133,-24.6635,1001.5156);
	SetPlayerFacingAngle(playerid, 359.0700);
	TogglePlayerControllable(playerid, 0);
	SetTimerEx("Count", 5000, 0, "i", playerid);
	format(string, MAXO_TEXT1, "~w~You have:~b~ %d ~w~ seconds to shoot %d targets.", timpGtest, NrTinteGtest);
	ShowPlayerInformation(playerid, "Shooting Test", string);
	SetPlayerHealth(playerid, 100);
	return true;
}

function StartGunTest(playerid) {
	if(TargetObject != INVALID_OBJECT_ID) return 1;
	new pick = random(2), pos = random(2);
#if defined _stream_objects
	if(pick == 0)TargetObject = CreateDynamicObject(2051, 283.54360961914, -9.9804744720459, 1002.3126831055,  0, 0, 0,-1, -1, -1);
	if(pick == 1)TargetObject = CreateDynamicObject(2051, 300.73095703125, -17.896602630615, 1001.8324584961, 0, 0, 0,-1, -1, -1);
	if(pick == 0 && pos == 0) MoveDynamicObject(TargetObject, 286.35388183594, -10.028178215027, 1002.3405151367, 1.0), space[0] = 0.5, space[1] = -1.2, space[2] = 1;
	if(pick == 0 && pos == 1) MoveDynamicObject(TargetObject, 291.95822143555, -10.16796207428, 1002.3361816406, 1.0), space[0] = 0.5, space[1] = -1.2, space[2] = 2;
	if(pick == 1 && pos == 0) MoveDynamicObject(TargetObject, 298.63711547852, -17.926261901855, 1001.8919677734, 1.0), space[0] = 0.5, space[1] = 0.2, space[2] = 1;
	if(pick == 1 && pos == 1) MoveDynamicObject(TargetObject, 294.79470825195, -17.730730056763, 1001.8419189453, 1.0), space[0] = 0.5, space[1] = 0.2, space[2] = 1;
	Streamer_UpdateEx(playerid, 294.79470825195, -17.730730056763, 1001.8419189453);
#else
	if(pick == 0)TargetObject = CreateObject(2051, 283.54360961914, -9.9804744720459, 1002.3126831055,  0, 0, 0);
	if(pick == 1)TargetObject = CreateObject(2051, 300.73095703125, -17.896602630615, 1001.8324584961, 0, 0, 0);
	if(pick == 0 && pos == 0) MoveObject(TargetObject, 286.35388183594, -10.028178215027, 1002.3405151367, 1.0), space[0] = 0.5, space[1] = -1.2, space[2] = 1;
	if(pick == 0 && pos == 1) MoveObject(TargetObject, 291.95822143555, -10.16796207428, 1002.3361816406, 1.0), space[0] = 0.5, space[1] = -1.2, space[2] = 2;
	if(pick == 1 && pos == 0) MoveObject(TargetObject, 298.63711547852, -17.926261901855, 1001.8919677734, 1.0), space[0] = 0.5, space[1] = 0.2, space[2] = 1;
	if(pick == 1 && pos == 1) MoveObject(TargetObject, 294.79470825195, -17.730730056763, 1001.8419189453, 1.0), space[0] = 0.5, space[1] = 0.2, space[2] = 1;
#endif
	if(gDynPlayerInfo[playerid][pGunLicType] == 0 && pick == 0) space[0] = 0.75;
	if(gDynPlayerInfo[playerid][pGunLicType] == 1) space[0] = 0.95;
	return true;
}

function ShootingCheck(playerid) {
	if(PInGunTest{playerid}) {
		new Float:x, Float:y, Float:z;
		if(GetPlayerWeapon(playerid) >= 1 && GetPlayerWeaponState(playerid) != WEAPONSTATE_RELOADING) {
			GetObjectPos(TargetObject, x, y, z);
			if(IsPlayerAimingAt(playerid, x, y+space[1], z-space[2], space[0])) {
				DestroyObject(TargetObject);
				TargetObject = INVALID_OBJECT_ID;
				tinteGtest++;
				StartGunTest(playerid);
				ShootDisInfo(playerid);
			}
		}
		if(tinteGtest >= NrTinteGtest) {
			new string[MAXO_TEXT], panala;
			panala = gettime();
			StopShootingTest(playerid);
			SendClientMessage(playerid, COLOR_LIGHTBLUE,"You passed the shooting test.");
			SendClientMessage(playerid, COLOR_LIGHTBLUE,"The extra paperwork costed you 10.000$.");
			SafeGivePlayerMoney(playerid,-10000);
			GameTextForPlayer(playerid, "~g~You passed the shooting test", 500, 1);
			gDynPlayerInfo[playerid][pGunLicType]++;
			if(gDynPlayerInfo[playerid][pGunLicType] > 2) gDynPlayerInfo[playerid][pGunLicType] = 2;
			PlayerInfo[playerid][pGunLic] = panala+ExpiraLicenta;
			format(string, sizeof(string), "UPDATE players SET GunLic = %d WHERE id = %d",panala+ExpiraLicenta,PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(string, sizeof(string), "INSERT INTO players_licenses (PlayerID,GunLicSP,GunLicType) VALUES (%d,%d,%d) ON DUPLICATE KEY UPDATE GunLicType = %d",PlayerInfo[playerid][pSQLID], panala, gDynPlayerInfo[playerid][pGunLicType], gDynPlayerInfo[playerid][pGunLicType]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			inguntest = 0;
			SetPlayerWeaponSkill(playerid);
		}
		else if(timpGtest <= 0) {
			StopShootingTest(playerid);
			SendClientMessage(playerid, COLOR_LIGHTBLUE,"You failed the shooting test");
			GameTextForPlayer(playerid, "~R~You failed the shooting test", 500, 1);
			inguntest = 0;
		}
	}
	return true;
}

function NumaratoareGun(playerid) {
	if(timpGtest > 0) {
		timpGtest--;
		SetTimerEx("NumaratoareGun", 1004, 0, "i", playerid);
		ShootDisInfo(playerid); 
	}
	return true;
}

stock ShootDisInfo(playerid) {
	new string[80];
	format(string, 80, "~w~You have: ~n~  ~b~%d~w~ seconds ~n~  ~r~%d/%d~w~ targets", timpGtest, tinteGtest, NrTinteGtest);
	ShowPlayerInformation(playerid, "Shooting Test", string);
	return true;
}

stock varShootfree() {
	inguntest = 0;
	timpGtest = 0;
	tinteGtest = 0;
	if(TargetObject != INVALID_OBJECT_ID) {
	#if defined _stream_objects
		DestroyDynamicObject(TargetObject);
	#else
		DestroyObject(TargetObject);
	#endif
		TargetObject = INVALID_OBJECT_ID;
	}
	return true;
}


function StopShootingTest(playerid) {
	PInGunTest{playerid} = 0;
	SetPlayerInterior(playerid, 7);
	SetPlayerPos(playerid, 312.5899,-140.4549,1004.0625);
	ResetPlayerWeapons(playerid);
	timpGtest = 0;
	tinteGtest = 0;
#if defined _stream_objects
	if(IsValidDynamicObject(TargetObject)) {
		DestroyDynamicObject(TargetObject);
		TargetObject = INVALID_OBJECT_ID;
		Streamer_UpdateEx(playerid, 312.5899,-140.4549,1004.0625);
	}
#else
	if(IsValidObject(TargetObject)) {
		DestroyObject(TargetObject);
		TargetObject = INVALID_OBJECT_ID;
	}
#endif
	inguntest = 0;
	if(gDynPlayerInfo[playerid][pGunLicType] == 1) SendClientMessage(playerid, COLOR_LIGHTBLUE, "You finished advanced shooting training."); 
	return true;
}

function GiveGunLicS(playerid, giveplayerid) {
	if(playerid != INVALID_PLAYER_ID) {
		new string[96];
		rows = cache_get_row_count();
		if(rows) {
			new SuspendatLa, curent;
			curent = gettime();
			SuspendatLa = cache_get_row_int(0, 0);
			if(SuspendatLa > curent)  {
				format(string,sizeof(string),"You can't receive a license. You are suspended until: {DBED15}%s", DateToTimestamp(SuspendatLa,1));
				SendClientMessage(giveplayerid, COLOR_GRAD1, string);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "That player's license has been suspended by a cop. He must wait longer!");
			}
		}
		else 
		{
			new PanaLa;
			PanaLa = gLocalTimeStamp + ExpiraLicenta; 
			PlayerInfo[giveplayerid][pGunLic] = PanaLa;
			gDynPlayerInfo[playerid][pGunLicType] = 1; 
			format(string, sizeof(string), "UPDATE players SET GunLic = %d WHERE ID = %d",PanaLa,PlayerInfo[giveplayerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(string, sizeof(string), "UPDATE players_licenses SET GunLicType = 1 WHERE PlayerID = %d",PlayerInfo[giveplayerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			SetPlayerWeaponSkill(giveplayerid);
		}
	}
	return true;
}

function ChGunLSuspThd(extraid) {
	if(extraid != INVALID_PLAYER_ID) {
		rows = cache_get_row_count();
		if(rows) {
			new SuspendatLa, curent;
			curent = gettime();
			SuspendatLa = cache_get_row_int(0, 3);
			if(SuspendatLa > curent) {
				new string[96];
				format(string,sizeof(string),"You can't receive a license. You are suspended until: {DBED15}%s"ALB"",DateToTimestamp(SuspendatLa,1));
				ShowPlayerDialog(extraid,DIALOGID_NO_ACTION,DIALOG_STYLE_MSGBOX,"Wepon testing denied", string,"Ok","");
			}
			else 
			{
				if(pTestType{extraid} == TEST_TYPE_NONE) ShowPlayerDialog(extraid, DIALOGID_CHOSE_WEAP, DIALOG_STYLE_LIST, "Choose the training level", "(Beginner) Pistol Training\n(Advanced) MachineGun Training\n", "Start Test", "Cancel");
				else SendClientMessage(extraid, COLOR_GREY, "You are already on the test!");
			}
		}
		else 
		{
			if(pTestType{extraid} == TEST_TYPE_NONE) ShowPlayerDialog(extraid, DIALOGID_CHOSE_WEAP, DIALOG_STYLE_LIST, "Choose the training level", "(Beginner) Pistol Training\n(Advanced) MachineGun Training\n", "Start Test", "Cancel");
			else SendClientMessage(extraid, COLOR_GREY, "You are already on the test!");
		}
	}
	return true;
}

function ChGunLBegThd(extraid) {
	if(extraid != INVALID_PLAYER_ID) {
		new string[MAXO_TEXT], curent;
		curent = gettime();
		rows = cache_get_row_count();
		if(rows)  {
			gDynPlayerInfo[extraid][pGunLicType] = cache_get_row_int(0, 2);
			if(gDynPlayerInfo[extraid][pGunLicType] >= 1) ShowPlayerDialog(extraid,DIALOGID_NO_ACTION,DIALOG_STYLE_MSGBOX,"Gun Training Denied","You have already done the Beginner Training.","Ok","");
			else 
			{
				if (ISBetween(PlayerInfo[extraid][pGunLic], 10, curent)) {
					format(string, sizeof(string),"Your license has expired. Do you want to renew your license? It will cost you $%s",FormatNumber( PlayerInfo[extraid][pLevel]*1000, 0, ',' ));
					ShowPlayerDialog(extraid, DIALOGID_LICENSE_ADDGUNBEG2, DIALOG_STYLE_MSGBOX, "License renewal", string, "Yes", "No");
				}
				else
				{
					gDynPlayerInfo[extraid][pGunLicType] = 0;
					timpGtest = 55;
					NrTinteGtest = 20;
					SafeGivePlayerMoney(extraid,-10000);
					GameTextForPlayer(extraid, "~W~Shoot 20 targets before your time is over", 5000, 1);
					CDPart(extraid);
					GivePlayerWeapon(extraid, WEAPON_COLT45, 9999);
				}
			}
		}
		else 
		{
			if (ISBetween(PlayerInfo[extraid][pGunLic], 10, curent)) {
				format(string, sizeof(string),"Your license has expired. Do you want to renew your license? It will cost you $%s",FormatNumber( PlayerInfo[extraid][pLevel]*2000, 0, ',' ));
				ShowPlayerDialog(extraid, DIALOGID_LICENSE_ADDGUNBEG2, DIALOG_STYLE_MSGBOX, "License renewal", string, "Yes", "No");
			}
			else
			{
				gDynPlayerInfo[extraid][pGunLicType] = 0;
				timpGtest = 55;
				NrTinteGtest = 20;
				SafeGivePlayerMoney(extraid,-10000);
				GameTextForPlayer(extraid, "~W~Shoot 20 targets before your time is over", 5000, 1);
				CDPart(extraid);
				GivePlayerWeapon(extraid, WEAPON_COLT45, 9999);
			}
		}
	}
	return true;
}

function ChGunLAdvThd(extraid) {
	if(extraid != INVALID_PLAYER_ID) {
		rows = cache_get_row_count();
		if(rows) {
			gDynPlayerInfo[extraid][pGunLicType] = cache_get_row_int(0, 2);
			if(gDynPlayerInfo[extraid][pGunLicType] == 0) ShowPlayerDialog(extraid,DIALOGID_NO_ACTION,DIALOG_STYLE_MSGBOX,"Gun Training Denied","You must train your Beginner skills first.","Ok","");
			else if(gDynPlayerInfo[extraid][pGunLicType] == 2) ShowPlayerDialog(extraid,DIALOGID_NO_ACTION,DIALOG_STYLE_MSGBOX,"Gun Training Denied","You have already done the Advanced Training.","Ok","");
			else 
			{
				if (gDynPlayerInfo[extraid][pGunLicType] == 3) {
					new string[MAXO_TEXT];
					format(string, sizeof(string),"Your license has expired. Do you want to renew your license? It will cost you $%s",FormatNumber( PlayerInfo[extraid][pLevel]*1500, 0, ',' ));
					ShowPlayerDialog(extraid, DIALOGID_LICENSE_ADDGUNADV2, DIALOG_STYLE_MSGBOX, "License renewal", string, "Yes", "No");
				}
				else
				{
					timpGtest = 70;
					NrTinteGtest = 45;
					SafeGivePlayerMoney(extraid,-10000);
					GameTextForPlayer(extraid, "~W~Shoot 30 targets before your time is over", 5000, 1);
					CDPart(extraid);
					GivePlayerWeapon(extraid, WEAPON_UZI, 9999);
				}
			}
		}
		else 
		{
			ShowPlayerDialog(extraid,DIALOGID_NO_ACTION,DIALOG_STYLE_MSGBOX,"Gun Training Denied","You must train your Beginner skills first.","Ok","");
		}
	}
	return true;
}

stock LicWeapOnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	#pragma unused inputtext
	new
		string[MAXO_TEXT];
	if(dialogid == DIALOGID_DMV_WEAP) {
		if (response) {
			if(PlayerInfo[playerid][pCash]< 10000) return ShowPlayerDialog(playerid,DIALOGID_NO_ACTION,DIALOG_STYLE_MSGBOX,"Shooting test failed","You don't have enough cash. $10.000 is needed if you get the test.","Ok","");
			if(inguntest == 1) ShowPlayerDialog(playerid,DIALOGID_NO_ACTION,DIALOG_STYLE_MSGBOX,"Shooting test failed","Someone else is training right now, please wait..","Ok","");
			else
			{
				format(string, sizeof(string), "SELECT GunLicSP FROM players_licenses WHERE PlayerID = %d",PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "ChGunLSuspThd", "d", playerid);
			}
		}
		else if(!response) return true;
	}
	if(dialogid == DIALOGID_CHOSE_WEAP) {
		if(response) {
			if(inguntest == 1) ShowPlayerDialog(playerid,DIALOGID_NO_ACTION,DIALOG_STYLE_MSGBOX,"Shooting test failed","Someone else is training right now, please wait..","Ok","");
			else
			{
				CheckWeaponLicense(playerid);
				switch(listitem) {
					case 0: {
						format(string, sizeof(string), "SELECT GunLicType FROM players_licenses WHERE PlayerID = %d",PlayerInfo[playerid][pSQLID]);
						mysql_tquery(connectionHandle, string, "ChGunLBegThd", "d", playerid);
					}
					case 1: {
						format(string, sizeof(string), "SELECT GunLicType FROM players_licenses WHERE PlayerID = %d",PlayerInfo[playerid][pSQLID]);
						mysql_tquery(connectionHandle, string, "ChGunLAdvThd", "d", playerid);
					}
				}
			}
		}
		else if(!response) return true;
	}
	else if(dialogid == DIALOGID_LICENSE_ADDGUNBEG2) {
		if (response) {
			if(PlayerInfo[playerid][pCash] > PlayerInfo[playerid][pLevel]*1000) {
				new tlabel[20], extras, panala;
				panala = gettime();
				extras = PlayerInfo[playerid][pLevel]*1000;
				SafeGivePlayerMoney(playerid,-extras);
				format(tlabel, sizeof(tlabel), "~r~-%d~y~$", extras);
				GameTextForPlayer(playerid, tlabel, 1500, 1);
				ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Licence renewal", "Renewal successful!", "Ok", "");
				gDynPlayerInfo[playerid][pGunLicType] = 3; 
				PlayerInfo[playerid][pGunLic] = panala+ExpiraLicenta;
				format(string, sizeof(string), "UPDATE players SET GunLic = %d WHERE ID = %d",panala+ExpiraLicenta,PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				format(string, sizeof(string), "INSERT INTO players_licenses (PlayerID,GunLicSP,GunLicType) VALUES (%d,%d,%d) ON DUPLICATE KEY UPDATE GunLicType = %d",PlayerInfo[playerid][pSQLID], panala, gDynPlayerInfo[playerid][pGunLicType], gDynPlayerInfo[playerid][pGunLicType]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				SetPlayerWeaponSkill(playerid);
			} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Licence renewal failed", "No action has been taken. You don't have enough money.", "Ok", "");
		}
		else if(!response) ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Licence renewal failed", "No action has been taken. You aborted the change.", "Ok", "");
	}
	else if(dialogid == DIALOGID_LICENSE_ADDGUNADV2) {
		if (response) {
			if(PlayerInfo[playerid][pCash] > PlayerInfo[playerid][pLevel]*1500) {
				new tlabel[20], extras, panala;
				panala = gettime();
				extras = PlayerInfo[playerid][pLevel]*1500;
				SafeGivePlayerMoney(playerid,-extras);
				format(tlabel, sizeof(tlabel), "~r~-%d~y~$", extras);
				GameTextForPlayer(playerid, tlabel, 1500, 1);
				ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Licence renewal", "Renewal successful!", "Ok", "");
				gDynPlayerInfo[playerid][pGunLicType] = 2; 
				PlayerInfo[playerid][pGunLic] = panala+ExpiraLicenta;
				format(string, sizeof(string), "UPDATE players SET GunLic = %d WHERE ID = %d",panala+ExpiraLicenta,PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				format(string, sizeof(string), "INSERT INTO players_licenses (PlayerID,GunLicSP,GunLicType) VALUES (%d,%d,%d) ON DUPLICATE KEY UPDATE GunLicType = %d",PlayerInfo[playerid][pSQLID], panala, gDynPlayerInfo[playerid][pGunLicType], gDynPlayerInfo[playerid][pGunLicType]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				SetPlayerWeaponSkill(playerid);
			} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Licence renewal failed", "No action has been taken. You don't have enough money.", "Ok", "");
		}
		else if(!response) ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Licence renewal failed", "No action has been taken. You aborted the change.", "Ok", "");
	}
	return true;
}

// End Of File ...
