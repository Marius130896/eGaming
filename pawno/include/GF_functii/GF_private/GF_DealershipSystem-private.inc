/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_DealershipSystem_included
	#endinput
#else
	#define GF_DealershipSystem_included
#endif

new
	PlayerText:dsChenarNegru[MAX_PLAYERS] 		= {PlayerText:INVALID_TEXT_DRAW,...},
	PlayerText:dsDenumireMasina[MAX_PLAYERS] 	= {PlayerText:INVALID_TEXT_DRAW,...},
	PlayerText:dsPretMasina[MAX_PLAYERS] 		= {PlayerText:INVALID_TEXT_DRAW,...},
	PlayerText:dsStocMasina[MAX_PLAYERS]		= {PlayerText:INVALID_TEXT_DRAW,...},
	PlayerText:dsInainteMasina[MAX_PLAYERS]		= {PlayerText:INVALID_TEXT_DRAW,...},
	PlayerText:dsInapoiMasina[MAX_PLAYERS]		= {PlayerText:INVALID_TEXT_DRAW,...},
	PlayerText:dsTestDriveMasina[MAX_PLAYERS]	= {PlayerText:INVALID_TEXT_DRAW,...},
	PlayerText:dsExitShop[MAX_PLAYERS]		= {PlayerText:INVALID_TEXT_DRAW,...},
	PlayerText:dsPreviewCar[MAX_PLAYERS]		= {PlayerText:INVALID_TEXT_DRAW,...},
	PlayerText:dsCumparareMasina[MAX_PLAYERS]	= {PlayerText:INVALID_TEXT_DRAW,...}
;

new
	parkrand;

new Float:ParkDSVeh[][4] = {
	{1630.2391,-1107.4390,23.5275,269.6891},
	{1630.3253,-1103.0308,23.5212,269.8122},
	{1630.4016,-1098.4706,23.5262,269.6807},
	{1630.3420,-1094.0437,23.5354,270.8030},
	{1630.2286,-1089.5927,23.5297,269.7821},
	{1630.2505,-1085.0754,23.5274,269.9847},
	{1620.3772,-1085.0669,23.5152,89.4779},
	{1620.5515,-1089.5403,23.5286,89.3054},
	{1620.3004,-1094.0116,23.5313,89.8355},
	{1620.1838,-1098.4990,23.5276,89.3908},
	{1620.1820,-1102.9921,23.5136,90.7438},
	{1619.9980,-1107.4092,23.5588,89.9003}
};

#define MAX_DS_CARS 120
enum dInfo {
	dSQLID,
	dType,
	dNume[32],
	dModel,
	dPrice,
	dStock
};
new DealershipInfo[MAX_DS_CARS][dInfo];
new dscars;
new ds_motoare;
new ds_low;
new ds_med;
new ds_high;
new pDSMasinaTestDrive[MAX_PLAYERS] = {INVALID_VEHICLE_ID,...};

stock LoadDealership() {
	mysql_tquery(connectionHandle, "SELECT * FROM vehicles_dealership", "LoadDealershipThd", "d", DEALERSHIP_THREAD_ID);
	return true;
}

function LoadDealershipThd() {
	rows = cache_get_row_count();
	ds_motoare = 0;
	ds_low = 0;
	ds_med = 0;
	ds_high = 0;
	if(rows > 0) {
		for(new d; d < rows; d++) {
			DealershipInfo[d][dSQLID] = cache_get_row_int(d, 0);
			DealershipInfo[d][dType] = cache_get_row_int(d, 1);
			cache_get_row(d, 2, DealershipInfo[d][dNume], .max_len = 32);
			DealershipInfo[d][dModel] = cache_get_row_int(d, 3);
			DealershipInfo[d][dPrice] = cache_get_row_int(d, 4);
			DealershipInfo[d][dStock] = cache_get_row_int(d, 5);
			switch(DealershipInfo[d][dType]) {
				case 0: ds_motoare++;
				case 1: ds_low++;
				case 2: ds_med++;
				case 3: ds_high++;
			}
		}
		dscars = rows;
		printf("LoadDealerShipThread() - called (%d vehicles loaded).", rows);
	}
	return true;
}

stock HaveAPersonalCar(playerid) {
	new
		HaveVehicle = INVALID_VEHICLE_ID;
	for(new v; v < MAX_VEHICLES; v++) {
		if(CarInfo[v][cType] == VEHICLE_TYPE_PERSONAL) {
			if(CarInfo[v][cOwnerSQLID] == PlayerInfo[playerid][pSQLID]) {
				HaveVehicle = v;
				break;
			}
		}
	}
	return HaveVehicle;
}

stock CreateDealerTDForPlayer(playerid) {
	dsChenarNegru[playerid] = CreatePlayerTextDraw(playerid, 607.000000, 269.470367, "usebox");
	PlayerTextDrawLetterSize(playerid, dsChenarNegru[playerid], 0.000000, 17.197738);
	PlayerTextDrawTextSize(playerid, dsChenarNegru[playerid], 477.333343, 0.000000);
	PlayerTextDrawAlignment(playerid, dsChenarNegru[playerid], 1);
	PlayerTextDrawColor(playerid, dsChenarNegru[playerid], 0);
	PlayerTextDrawUseBox(playerid, dsChenarNegru[playerid], true);
	PlayerTextDrawBoxColor(playerid, dsChenarNegru[playerid], 102);
	PlayerTextDrawSetShadow(playerid, dsChenarNegru[playerid], 0);
	PlayerTextDrawSetOutline(playerid, dsChenarNegru[playerid], 0);
	PlayerTextDrawFont(playerid, dsChenarNegru[playerid], 0);

	dsInainteMasina[playerid] = CreatePlayerTextDraw(playerid, 476.666625, 253.036972, "<");
	PlayerTextDrawLetterSize(playerid, dsInainteMasina[playerid], 0.449999, 1.600000);
	PlayerTextDrawAlignment(playerid, dsInainteMasina[playerid], 1);
	PlayerTextDrawColor(playerid, dsInainteMasina[playerid], -1);
	PlayerTextDrawSetShadow(playerid, dsInainteMasina[playerid], 0);
	PlayerTextDrawSetOutline(playerid, dsInainteMasina[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, dsInainteMasina[playerid], 51);
	PlayerTextDrawFont(playerid, dsInainteMasina[playerid], 1);
	PlayerTextDrawSetProportional(playerid, dsInainteMasina[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, dsInainteMasina[playerid], true);

	dsInapoiMasina[playerid] = CreatePlayerTextDraw(playerid, 596.000000, 254.696350, ">");
	PlayerTextDrawLetterSize(playerid, dsInapoiMasina[playerid], 0.449999, 1.600000);
	PlayerTextDrawAlignment(playerid, dsInapoiMasina[playerid], 1);
	PlayerTextDrawColor(playerid, dsInapoiMasina[playerid], -1);
	PlayerTextDrawSetShadow(playerid, dsInapoiMasina[playerid], 0);
	PlayerTextDrawSetOutline(playerid, dsInapoiMasina[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, dsInapoiMasina[playerid], 51);
	PlayerTextDrawFont(playerid, dsInapoiMasina[playerid], 1);
	PlayerTextDrawSetProportional(playerid, dsInapoiMasina[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, dsInapoiMasina[playerid], true);

	dsDenumireMasina[playerid] = CreatePlayerTextDraw(playerid, 481.666625, 275.851898, "Name:");
	PlayerTextDrawLetterSize(playerid, dsDenumireMasina[playerid], 0.265000, 1.247407);
	PlayerTextDrawAlignment(playerid, dsDenumireMasina[playerid], 1);
	PlayerTextDrawColor(playerid, dsDenumireMasina[playerid], -1);
	PlayerTextDrawSetShadow(playerid, dsDenumireMasina[playerid], 0);
	PlayerTextDrawSetOutline(playerid, dsDenumireMasina[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, dsDenumireMasina[playerid], 51);
	PlayerTextDrawFont(playerid, dsDenumireMasina[playerid], 1);
	PlayerTextDrawSetProportional(playerid, dsDenumireMasina[playerid], 1);

	dsPretMasina[playerid] = CreatePlayerTextDraw(playerid, 482.666595, 293.444488, "Price:");
	PlayerTextDrawLetterSize(playerid, dsPretMasina[playerid], 0.265000, 1.247407);
	PlayerTextDrawAlignment(playerid, dsPretMasina[playerid], 1);
	PlayerTextDrawColor(playerid, dsPretMasina[playerid], -1);
	PlayerTextDrawSetShadow(playerid, dsPretMasina[playerid], 0);
	PlayerTextDrawSetOutline(playerid, dsPretMasina[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, dsPretMasina[playerid], 51);
	PlayerTextDrawFont(playerid, dsPretMasina[playerid], 1);
	PlayerTextDrawSetProportional(playerid, dsPretMasina[playerid], 1);

	dsTestDriveMasina[playerid] = CreatePlayerTextDraw(playerid, 519.999877, 359.814880, "Test Drive");
	PlayerTextDrawLetterSize(playerid, dsTestDriveMasina[playerid], 0.265000, 1.247407);
	PlayerTextDrawAlignment(playerid, dsTestDriveMasina[playerid], 1);
	PlayerTextDrawColor(playerid, dsTestDriveMasina[playerid], -1);
	PlayerTextDrawSetShadow(playerid, dsTestDriveMasina[playerid], 0);
	PlayerTextDrawSetOutline(playerid, dsTestDriveMasina[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, dsTestDriveMasina[playerid], 51);
	PlayerTextDrawFont(playerid, dsTestDriveMasina[playerid], 1);
	PlayerTextDrawSetProportional(playerid, dsTestDriveMasina[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, dsTestDriveMasina[playerid], true);

	dsExitShop[playerid] = CreatePlayerTextDraw(playerid, 481.666564, 408.518646, "Exit Shop");
	PlayerTextDrawLetterSize(playerid, dsExitShop[playerid], 0.265000, 1.247407);
	PlayerTextDrawAlignment(playerid, dsExitShop[playerid], 1);
	PlayerTextDrawColor(playerid, dsExitShop[playerid], -1);
	PlayerTextDrawSetShadow(playerid, dsExitShop[playerid], 0);
	PlayerTextDrawSetOutline(playerid, dsExitShop[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, dsExitShop[playerid], 51);
	PlayerTextDrawFont(playerid, dsExitShop[playerid], 1);
	PlayerTextDrawSetProportional(playerid, dsExitShop[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, dsExitShop[playerid], true);

	dsCumparareMasina[playerid] = CreatePlayerTextDraw(playerid, 576.333374, 406.518585, "Buy");
	PlayerTextDrawLetterSize(playerid, dsCumparareMasina[playerid], 0.449999, 1.600000);
	PlayerTextDrawAlignment(playerid, dsCumparareMasina[playerid], 1);
	PlayerTextDrawColor(playerid, dsCumparareMasina[playerid], -1);
	PlayerTextDrawSetShadow(playerid, dsCumparareMasina[playerid], 0);
	PlayerTextDrawSetOutline(playerid, dsCumparareMasina[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, dsCumparareMasina[playerid], 51);
	PlayerTextDrawFont(playerid, dsCumparareMasina[playerid], 0);
	PlayerTextDrawSetProportional(playerid, dsCumparareMasina[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, dsCumparareMasina[playerid], true);

	dsStocMasina[playerid] = CreatePlayerTextDraw(playerid, 481.999908, 308.963012, "Stocks:");
	PlayerTextDrawLetterSize(playerid, dsStocMasina[playerid], 0.265000, 1.247407);
	PlayerTextDrawAlignment(playerid, dsStocMasina[playerid], 1);
	PlayerTextDrawColor(playerid, dsStocMasina[playerid], -1);
	PlayerTextDrawSetShadow(playerid, dsStocMasina[playerid], 0);
	PlayerTextDrawSetOutline(playerid, dsStocMasina[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, dsStocMasina[playerid], 51);
	PlayerTextDrawFont(playerid, dsStocMasina[playerid], 1);
	PlayerTextDrawSetProportional(playerid, dsStocMasina[playerid], 1);

	dsPreviewCar[playerid] = CreatePlayerTextDraw(playerid, 494.666687, 204.503692, "_");
	PlayerTextDrawFont(playerid, dsPreviewCar[playerid], TEXT_DRAW_FONT_MODEL_PREVIEW);
	PlayerTextDrawUseBox(playerid, dsPreviewCar[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, dsPreviewCar[playerid], 0xFFFFFF00);
	PlayerTextDrawTextSize(playerid, dsPreviewCar[playerid], 100.0, 100.0);
	PlayerTextDrawSetSelectable(playerid, dsPreviewCar[playerid], true);
	return true;
}

stock DestroyDealerTDForPlayer(playerid) {
	if(dsExitShop[playerid] != PlayerText:INVALID_TEXT_DRAW) {
		PlayerTextDrawHide(playerid, dsChenarNegru[playerid]);
		PlayerTextDrawHide(playerid, dsDenumireMasina[playerid]);
		PlayerTextDrawHide(playerid, dsPretMasina[playerid]);
		PlayerTextDrawHide(playerid, dsStocMasina[playerid]);
		PlayerTextDrawHide(playerid, dsInainteMasina[playerid]);
		PlayerTextDrawHide(playerid, dsInapoiMasina[playerid]);
		PlayerTextDrawHide(playerid, dsTestDriveMasina[playerid]);
		PlayerTextDrawHide(playerid, dsExitShop[playerid]);
		PlayerTextDrawHide(playerid, dsCumparareMasina[playerid]);
		PlayerTextDrawHide(playerid, dsPreviewCar[playerid]);

		PlayerTextDrawDestroy(playerid, dsChenarNegru[playerid]);
		PlayerTextDrawDestroy(playerid, dsDenumireMasina[playerid]);
		PlayerTextDrawDestroy(playerid, dsPretMasina[playerid]);
		PlayerTextDrawDestroy(playerid, dsStocMasina[playerid]);
		PlayerTextDrawDestroy(playerid, dsInainteMasina[playerid]);
		PlayerTextDrawDestroy(playerid, dsInapoiMasina[playerid]);
		PlayerTextDrawDestroy(playerid, dsTestDriveMasina[playerid]);
		PlayerTextDrawDestroy(playerid, dsExitShop[playerid]);
		PlayerTextDrawDestroy(playerid, dsCumparareMasina[playerid]);
		PlayerTextDrawDestroy(playerid, dsPreviewCar[playerid]);

		dsChenarNegru[playerid] = PlayerText:INVALID_TEXT_DRAW;
		dsDenumireMasina[playerid] = PlayerText:INVALID_TEXT_DRAW;
		dsPretMasina[playerid] = PlayerText:INVALID_TEXT_DRAW;
		dsStocMasina[playerid] = PlayerText:INVALID_TEXT_DRAW;
		dsInainteMasina[playerid] = PlayerText:INVALID_TEXT_DRAW;
		dsInapoiMasina[playerid] = PlayerText:INVALID_TEXT_DRAW;
		dsTestDriveMasina[playerid] = PlayerText:INVALID_TEXT_DRAW;
		dsExitShop[playerid]= PlayerText:INVALID_TEXT_DRAW;
		dsCumparareMasina[playerid] = PlayerText:INVALID_TEXT_DRAW;
		dsPreviewCar[playerid] = PlayerText:INVALID_TEXT_DRAW;

		CancelSelectTextDraw(playerid);
	}
	if(pDSMasinaTestDrive[playerid] != INVALID_VEHICLE_ID) {
		DestroyVehicle(pDSMasinaTestDrive[playerid]);
		pDSMasinaTestDrive[playerid] = INVALID_VEHICLE_ID;
	}
	return true;
}

stock ShowDSEnvironment(playerid) {
	PlayerInfo[playerid][pCursorDealer] = 0;
	CreateDealerTDForPlayer(playerid);
	UpdateDSEnvironment(playerid, PlayerInfo[playerid][pCursorDealer]);

	PlayerTextDrawShow(playerid, dsChenarNegru[playerid]);
	PlayerTextDrawShow(playerid, dsInainteMasina[playerid]);
	PlayerTextDrawShow(playerid, dsInapoiMasina[playerid]);
	PlayerTextDrawShow(playerid, dsTestDriveMasina[playerid]);
	PlayerTextDrawShow(playerid, dsExitShop[playerid]);
	PlayerTextDrawShow(playerid, dsCumparareMasina[playerid]);

	PlayerTextDrawShow(playerid, dsDenumireMasina[playerid]);
	PlayerTextDrawShow(playerid, dsStocMasina[playerid]);
	PlayerTextDrawShow(playerid, dsPretMasina[playerid]);
	PlayerTextDrawShow(playerid, dsPreviewCar[playerid]);

	SelectTextDraw(playerid, COLOR_LIGHTBLUE);

	TogglePlayerControllable(playerid, false);
	SafeSetPlayerVirtualWorld(playerid, playerid+1);
	SetPlayerCameraPos(playerid, 2132.1714, -1127.4611, 27.0237);
	SetPlayerCameraLookAt(playerid, 2132.0005, -1128.4456, 26.7787);
	SafeSetPlayerPos(playerid, 2123.3401, -1195.9111, 23.9385);
	return true;
}

stock HideDSEnvironment(playerid) {
	DestroyDealerTDForPlayer(playerid);

	SafeSetPlayerVirtualWorld(playerid, 0);
	SafeSetPlayerPos(playerid, 2127.4929, -1148.9103, 24.3025);

	TogglePlayerControllable(playerid, true);
	SetCameraBehindPlayer(playerid);
	return true;
}

stock UpdateDSEnvironment(playerid, indexDerulare) {
	new string[MAXO_TEXT1];
	if(pDSMasinaTestDrive[playerid] != INVALID_VEHICLE_ID) {
		DestroyVehicle(pDSMasinaTestDrive[playerid]);
		pDSMasinaTestDrive[playerid] = INVALID_VEHICLE_ID;
	}
	format(string, sizeof(string), "Name: ~y~%s", DealershipInfo[indexDerulare][dNume]);
	PlayerTextDrawSetString(playerid, dsDenumireMasina[playerid], string);

	format(string, sizeof(string), "Stocks: ~y~%d", DealershipInfo[indexDerulare][dStock]);
	PlayerTextDrawSetString(playerid, dsStocMasina[playerid], string);

	format(string, sizeof(string), "Price: ~y~%s $", FormatNumber( DealershipInfo[indexDerulare][dPrice], 0, '.' ));
	PlayerTextDrawSetString(playerid, dsPretMasina[playerid], string);

	PlayerTextDrawSetPreviewModel(playerid, dsPreviewCar[playerid], DealershipInfo[indexDerulare][dModel]);
	PlayerTextDrawSetPreviewVehCol(playerid, dsPreviewCar[playerid], 1, 1);
	PlayerTextDrawSetPreviewRot(playerid, dsPreviewCar[playerid], -10.0, 0.0, -20.0, 1.0);
	PlayerTextDrawShow(playerid, dsPreviewCar[playerid]);

	pDSMasinaTestDrive[playerid] = CreateVehicle(DealershipInfo[indexDerulare][dModel],2130.6353,-1134.1908,25.2273,330.0091,1,1,-1);
	SetVehicleVirtualWorld(pDSMasinaTestDrive[playerid],playerid+1);
	clear.string(string);
	return true;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid) {
	if(playertextid == dsExitShop[playerid]) {
		HideDSEnvironment(playerid);
		SendClientMessage(playerid, COLOR_WHITE, "You have exited from shop.");
		return 1;
	}
	else if(playertextid == dsInainteMasina[playerid]) {
		if(PlayerInfo[playerid][pCursorDealer] == 0) PlayerInfo[playerid][pCursorDealer] = dscars;
		PlayerInfo[playerid][pCursorDealer] --;
		UpdateDSEnvironment(playerid, PlayerInfo[playerid][pCursorDealer]);
		return 1;
	}
	else if(playertextid == dsInapoiMasina[playerid]) {
		if(ISBetween(PlayerInfo[playerid][pCursorDealer], 0, (dscars-2))) PlayerInfo[playerid][pCursorDealer] ++;
		else PlayerInfo[playerid][pCursorDealer] = 0;
		UpdateDSEnvironment(playerid, PlayerInfo[playerid][pCursorDealer]);
		return 1;
	}
	else if(playertextid == dsTestDriveMasina[playerid]) {
		if(DealershipInfo[PlayerInfo[playerid][pCursorDealer]][dStock] > 0) {
			HideDSEnvironment(playerid);
			SafeSetPlayerVirtualWorld(playerid, playerid+1);
			pDSMasinaTestDrive[playerid] = CreateVehicle(DealershipInfo[PlayerInfo[playerid][pCursorDealer]][dModel], 1715.3977, -663.6888, 42.9167, 355.9638, 1, 1, -1);
			SetVehicleVirtualWorld(pDSMasinaTestDrive[playerid], playerid+1);
			CarInfo[pDSMasinaTestDrive[playerid]][cLastBroken] = gLocalTimeStamp+86400;
			CarInfo[pDSMasinaTestDrive[playerid]][cHealth] = 1000.0;
			CarInfo[pDSMasinaTestDrive[playerid]][cEngine] = true;
			Gas[pDSMasinaTestDrive[playerid]] = GasMax;
			SafeSetPlayerPos(playerid, 1715.3977, -663.6888, 42.9167);
			PutPlayerInVehicle(playerid, pDSMasinaTestDrive[playerid], 0);
			StopCarRadio(pDSMasinaTestDrive[playerid]);
			new engine, lights, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(pDSMasinaTestDrive[playerid], engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(pDSMasinaTestDrive[playerid], VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);
			SendClientMessage(playerid, COLOR_WHITE, "You have 30 seconds to test the car, have fun.");
			timertestdrive = SetTimerEx("dsStopVehicleTest", 30000, false, "d", playerid);
		} else SendClientMessage(playerid, COLOR_GRAD1, "This model is not in stock to be tested.");
		return 1;
	}
	else if(playertextid == dsCumparareMasina[playerid]) {
		BuyVehicle(playerid, PlayerInfo[playerid][pCursorDealer]);
		return 1;
	}

	return 0;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid) {
	if(clickedid == Text:INVALID_TEXT_DRAW) {
		if(dsExitShop[playerid] != PlayerText:INVALID_TEXT_DRAW) {
			HideDSEnvironment(playerid);
		}
		return true;
	}
    return false;
}

function dsStopVehicleTest(playerid) {
	HideDSEnvironment(playerid);
	KillTimer(timertestdrive);
	SendClientMessage(playerid, COLOR_WHITE, "Your test drive time has expired.");
	return true;
}

stock BuyVehicle(playerid, DBvID) {
	if(PlayerInfo[playerid][pCarSlots] > 0) {
		if(PlayerInfo[playerid][pAccount] >= DealershipInfo[DBvID][dPrice]) {
			if(DealershipInfo[DBvID][dStock] > 0) {
				if(HaveAPersonalCar(playerid) == INVALID_VEHICLE_ID) {
					new
						string[300],
						vID;
					parkrand = random(sizeof(ParkDSVeh));
					vID = CreateVehicle(DealershipInfo[DBvID][dModel], ParkDSVeh[parkrand][0], ParkDSVeh[parkrand][1], ParkDSVeh[parkrand][2], ParkDSVeh[parkrand][3], 1, 1, -1);
					if(vID != INVALID_VEHICLE_ID) {
						CarInfo[vID][cModel] = DealershipInfo[DBvID][dModel];
						CarInfo[vID][cLocation][0] = ParkDSVeh[parkrand][0];
						CarInfo[vID][cLocation][1] = ParkDSVeh[parkrand][1];
						CarInfo[vID][cLocation][2] = ParkDSVeh[parkrand][2];
						CarInfo[vID][cAngle] = ParkDSVeh[parkrand][3];
						CarInfo[vID][cColor][0] = 1;
						CarInfo[vID][cColor][1] = 1;
						strmid(CarInfo[vID][cPlate], "eG Dealership", 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);
						strmid(CarInfo[vID][cOwner], PlayerName(playerid), 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);
						CarInfo[vID][cOwnerSQLID] = PlayerInfo[playerid][pSQLID];
						CarInfo[vID][cValue] = DealershipInfo[DBvID][dPrice];
						CarInfo[vID][cType] = VEHICLE_TYPE_PERSONAL;
						CarInfo[vID][cLastBroken] = gLocalTimeStamp + 86400;
						SetVehicleNumberPlate(vID, CarInfo[vID][cPlate]);
						format(string, sizeof(string), "%s's vehicle", CarInfo[vID][cOwner]);
						CarInfo[vID][cText] = Create3DTextLabel(string, COLOR_GRAD1, 0.0, 0.0, 0.0, 30.5, 0, 1);
						Attach3DTextLabelToVehicle(CarInfo[vID][cText], vID, 0.0, 0.0, 0.0);
						SetVehicleToRespawn(vID);
						format(string, MAXO_TEXT, "* {FFFFFF}Congratulations %s! You are now the owner of %s.", PlayerName(playerid), DealershipInfo[DBvID][dNume]);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						format(string, MAXO_TEXT, "%s bought %s at a price of $%s from Dealership.", PlayerName(playerid), DealershipInfo[DBvID][dNume], FormatNumber(DealershipInfo[DBvID][dPrice], 0, '.'));
						InsertLogInPanel(playerid, LOG_VEHICLES, string);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* {FFFFFF}HINT: For the avaible commands type /mycarhelp.");
						format(string, MAXO_TEXT, "* {FFFFFF}You've been charged with $%s for that.",FormatNumber(DealershipInfo[DBvID][dPrice], 0, '.'));
						SendClientMessage(playerid, COLOR_LIGHTBLUE,string);
						SendClientMessage(playerid, COLOR_LIGHTBLUE,"HINT: Your car is parket at Mulholland Intersection Parking. Use /findmycar to find it.");
						format(string, sizeof(string), "INSERT INTO vehicles_personal (Model, PosX, PosY, PosZ, Angle, Plate, Owner, OwnerSQLID, Price, LastBroken) VALUES ('%d', '%f', '%f', '%f', '%f', '%s', '%s', '%d', '%d', '%d')",
							CarInfo[vID][cModel],
							CarInfo[vID][cLocation][0],
							CarInfo[vID][cLocation][1],
							CarInfo[vID][cLocation][2],
							CarInfo[vID][cAngle],
							CarInfo[vID][cPlate],
							CarInfo[vID][cOwner],
							CarInfo[vID][cOwnerSQLID],
							CarInfo[vID][cValue],
							CarInfo[vID][cLastBroken]
						);
						mysql_tquery(connectionHandle, string, "SetCarSQLID", "d", vID);
						PlayerInfo[playerid][pAccount] -= DealershipInfo[DBvID][dPrice];
						PlayerInfo[playerid][pCarSlots] --;
						format(string, sizeof(string), "UPDATE players SET Account = %d, CarSlots = %d WHERE ID = %d", PlayerInfo[playerid][pAccount], PlayerInfo[playerid][pCarSlots], PlayerInfo[playerid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						DealershipInfo[DBvID][dStock] --;
						format(string, sizeof(string), "UPDATE vehicles_dealership SET Stock = %d WHERE Model = %d", DealershipInfo[DBvID][dStock], DealershipInfo[DBvID][dModel]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", DEALERSHIP_THREAD_ID);
						HideDSEnvironment(playerid);
						clear.string(string);
					}
				}
				else
					SendClientMessage(playerid, COLOR_GRAD1, "You have spawned a personal vehicle.");
			}
			else
				SendClientMessage(playerid, COLOR_GRAD1, "This model doesn't exist at Dealership.");
		}
		else
			SendClientMessage(playerid, COLOR_GRAD1, "You don't have enough money in your bank account.");
	}
	else
		SendClientMessage(playerid, COLOR_GRAD1, "You don't have any car slots available.");
	return 1;
}

function SetCarSQLID(vID) {
	CarInfo[vID][cSQLID] = cache_insert_id();
	return 1;
}

COMMAND:insertstock(playerid, params[]) {
	new string[MAXO_TEXT], model, type, stocks, price;
	if(PlayerInfo[playerid][pAdmin] > 5) {
		if(!sscanf(params, "dddd", model, type, stocks, price)) {
			if(ISBetween(model, 400, 612)) {
				if(ISBetween(type, 0, 3)) {
					if(stocks > 0) {
						if(price > 0) {
							format(string, MAXO_TEXT, "INSERT INTO vehicles_dealership (Type, Model, Name, Stock, Price) VALUES ('%d', '%d', '%s', '%d', '%d')", type, model, vehName[model-400], stocks, price);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", DEALERSHIP_THREAD_ID);
							LoadDealership();
							format(string, MAXO_TEXT, "AdmCmd: %s was added to the database at the price of $%s with stock of %d.", vehName[model-400], FormatNumber(price, 0, '.'), stocks);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							clear.string(string);
						} else SendClientMessage(playerid, COLOR_GRAD1, "The price must to be bigger than $0.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "The stock must to be bigger than 0.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid type vehicle.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid vehicle model.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/insertstock [model vehicle] [type vehicle] [stock] [price]"),
			SendClientMessage(playerid, COLOR_GRAD1, "Types of vehicles (numbers)"),
			SendClientMessage(playerid, COLOR_GRAD2, "0 - Motocycle"),
			SendClientMessage(playerid, COLOR_GRAD3, "1 - Low vehicle"),
			SendClientMessage(playerid, COLOR_GRAD4, "2 - Medium vehicle"),
			SendClientMessage(playerid, COLOR_GRAD4, "3 - High vehicle");
	} else NotAuthorized();
	return true;
}

COMMAND:updatestock(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] > 5) {
		new amount, model, string[MAXO_TEXT];
		if(!sscanf(params, "dd", model, amount)) {
			if(amount > 0) {
				if(ISBetween(model, 400, 612)) {
					format(string, MAXO_TEXT, "UPDATE vehicles_dealership SET Stock = %d WHERE Model = %d", amount, model);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", DEALERSHIP_THREAD_ID);
					LoadDealership();
					format(string, MAXO_TEXT, "AdmCmd: The stock was set at %d for the model %s (%d).", amount, vehName[model-400], model);
					SendClientMessage(playerid, COLOR_LIGHTRED, string);
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid model vehicle.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "The stock must to be bigger than 0.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/updatestock [model] [amount]");
	} else NotAuthorized();
	return true;
}

COMMAND:spawnmycar(playerid, params[]) {
	if(HaveAPersonalCar(playerid) != INVALID_VEHICLE_ID)
		return SendClientMessage(playerid, COLOR_GRAD1, "You already have a spawned vehicle, use /despawnmycar.");
	new
		SQLID, string[MAXO_TEXT];
	if(sscanf(params, "d", SQLID))
		return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/spawnmycar [Car SQLID]");
	format(string, sizeof(string), "SELECT * FROM vehicles_personal WHERE ID = %d AND OwnerSQLID = %d", SQLID, PlayerInfo[playerid][pSQLID]);
	mysql_tquery(connectionHandle, string, "SpawnVehicleThd", "dd", playerid, SQLID);
	clear.string(string);
	return true;
}

function SpawnVehicleThd(playerid, vSQLid) {
	rows = cache_num_rows();
	if(rows) {
		new
			string[MAXO_TEXT],
			VehicleModel, Float:VehiclePos[4], vID;
		VehicleModel = cache_get_row_int(0, 1); // Model
		VehiclePos[0] = cache_get_row_float(0, 2); // PosX
		VehiclePos[1] = cache_get_row_float(0, 3); // PosY
		VehiclePos[2] = cache_get_row_float(0, 4); // PosZ
		VehiclePos[3] = cache_get_row_float(0, 5); // Angle

		vID = CreateVehicle(VehicleModel, VehiclePos[0], VehiclePos[1], VehiclePos[2], VehiclePos[3], -1, -1, -1);

		if(vID != INVALID_VEHICLE_ID) {
			CarInfo[vID][cSQLID] = cache_get_row_int(0, 0); // SQL ID
			CarInfo[vID][cModel] = VehicleModel;
			CarInfo[vID][cLocation][0] = VehiclePos[0];
			CarInfo[vID][cLocation][1] = VehiclePos[1];
			CarInfo[vID][cLocation][2] = VehiclePos[2];
			CarInfo[vID][cAngle] = VehiclePos[3];
			cache_get_row(0, 6, CarInfo[vID][cPlate], .max_len = MAX_PLAYER_NAME); // Plate
			cache_get_row(0, 7, CarInfo[vID][cOwner], .max_len = MAX_PLAYER_NAME); // Owner Name
			CarInfo[vID][cOwnerSQLID] = cache_get_row_int(0, 8); // Owner SQL ID
			CarInfo[vID][cValue] = cache_get_row_int(0, 9); // Price
			CarInfo[vID][cType] = VEHICLE_TYPE_PERSONAL; // Type
			CarInfo[vID][cLastBroken] = cache_get_row_int(0, 10); // LastBroken
			CarInfo[vID][cPaintJob] = cache_get_row_int(0, 11);
			CarInfo[vID][cColor][0] = cache_get_row_int(0, 12);
			CarInfo[vID][cColor][1] = cache_get_row_int(0, 13);
			CarInfo[vID][cKM] = cache_get_row_float(0, 14);

			// now, we load the tunning parts
			new
				exhaust, frontbumper, rearbumper, roof, spoilers, sideskirt1,
				sideskirt2, wheels, hydraulics, nitro, hood, lamps, stereo, ventright, ventleft;

			spoilers = cache_get_row_int(0, 14);
			if(spoilers >= 1000)
				CarInfo[vID][cMods][0] = spoilers;
			hood = cache_get_row_int(0, 15);
			if(hood >= 1000)
				CarInfo[vID][cMods][1] = hood;
			roof = cache_get_row_int(0, 16);
			if(roof >= 1000)
				CarInfo[vID][cMods][2] = roof;
			sideskirt1 = cache_get_row_int(0, 17);
			if(sideskirt1 >= 1000)
				CarInfo[vID][cMods][3] = sideskirt1;
			lamps = cache_get_row_int(0, 18);
			if(lamps >= 1000)
				CarInfo[vID][cMods][4] = lamps;
			nitro = cache_get_row_int(0, 19);
			if(nitro >= 1000)
				CarInfo[vID][cMods][5] = nitro;
			exhaust = cache_get_row_int(0, 20);
			if(exhaust >= 1000)
				CarInfo[vID][cMods][6] = exhaust;
			wheels = cache_get_row_int(0, 21);
			if(wheels >= 1000)
				CarInfo[vID][cMods][7] = wheels;
			stereo = cache_get_row_int(0, 22);
			if(stereo >= 1000)
				CarInfo[vID][cMods][8] = stereo;
			hydraulics = cache_get_row_int(0, 23);
			if(hydraulics >= 1000)
				CarInfo[vID][cMods][9] = hydraulics;
			frontbumper = cache_get_row_int(0, 24);
			if(frontbumper >= 1000)
				CarInfo[vID][cMods][10] = frontbumper;
			rearbumper = cache_get_row_int(0, 25);
			if(rearbumper >= 1000)
				CarInfo[vID][cMods][11] = rearbumper;
			ventright = cache_get_row_int(0, 26);
			if(ventright >= 1000)
				CarInfo[vID][cMods][12] = ventright;
			ventleft = cache_get_row_int(0, 27);
			if(ventleft >= 1000)
				CarInfo[vID][cMods][13] = ventleft;
			sideskirt2 = cache_get_row_int(0, 28);
			if(sideskirt2 >= 1000)
				CarInfo[vID][cMods][14] = sideskirt2;
			CarInfo[vID][cLock] = cache_get_row_int(0, 29);
			format(string, sizeof(string), "%s's vehicle", CarInfo[vID][cOwner]);
			CarInfo[vID][cText] = Create3DTextLabel(string, COLOR_GRAD1, 0.0, 0.0, 0.0, 30.5, GetVehicleVirtualWorld(vID), 1);
			Attach3DTextLabelToVehicle(CarInfo[vID][cText], vID, 0.0, 0.0, 0.0);
			SetVehicleNumberPlate(vID, CarInfo[vID][cPlate]);
			SetVehicleToRespawn(vID);
			format(string, sizeof(string), "* You spawned your personal vehicle %s (%d) | Vehicle ID: %d", vehName[CarInfo[vID][cModel] - 400], CarInfo[vID][cModel], vID);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			clear.string(string);
		}
	}
	else
		SendClientMessage(playerid, COLOR_GRAD1, "You entered an invalid car SQLid, please use /mycars.");
	return 1;
}

COMMAND:mycars(playerid, params[]) {
	new
		query[MAXO_TEXT];
	format(query, sizeof(query), "SELECT * FROM vehicles_personal WHERE OwnerSQLID = %d", PlayerInfo[playerid][pSQLID]);
	mysql_tquery(connectionHandle, query, "CheckPlayerVehicles", "d", playerid);
	clear.string(query);
	return 1;
}

function CheckPlayerVehicles(playerid) {
	rows = cache_num_rows();
	if(rows) {
		new
			string[MAXO_TEXT],
			VehicleSQLID, VehicleModel, VehiclePrice, r = 0;
		format(string, sizeof(string), "|_________________ %s's vehicles _________________|", PlayerName(playerid));
		SendClientMessage(playerid, COLOR_GRAD1, string);
		while(r < rows) {
			VehicleSQLID = cache_get_row_int(r, 0);
			VehicleModel = cache_get_row_int(r, 1);
			VehiclePrice = cache_get_row_int(r, 9);
			format(string, sizeof(string), "Car SQLID: %d | Model: %s (%d) | Value: $%s", VehicleSQLID, vehName[VehicleModel - 400], VehicleModel, FormatNumber(VehiclePrice, 0, '.'));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			r++;
		}
		SendClientMessage(playerid, COLOR_GRAD1, "|___________________________________________________|");
		format(string, sizeof(string), "You have %d personal vehicles.", rows);
		SendClientMessage(playerid, COLOR_GRAD1, string);
		clear.string(string);
	}
	else
		SendClientMessage(playerid, COLOR_GRAD1, "You don't have a personal vehicle.");
	return 1;
}

COMMAND:despawnmycar(playerid, params[]) {
	new
		vID = HaveAPersonalCar(playerid), p = 0;
	if(vID == INVALID_VEHICLE_ID)
		return SendClientMessage(playerid, COLOR_GRAD1, "You don't have a spawned vehicle, use /spawnmycar.");
	foreach(Player, i) {
		if(GetPlayerVehicleID(playerid) == vID && i != playerid) {
			p++;
		}
	}
	if(p != 0)
		return SendClientMessage(playerid, COLOR_GRAD1, "There are players in your personal vehicle, you can't despawn it.");
	DespawnVehicle(playerid);
	return 1;
}

stock DespawnVehicle(playerid) {
	new
		vID = HaveAPersonalCar(playerid);
	if(DestroyVehicle(vID)) { // executat cu succes
		new
			string[MAXO_TEXT];
		// dealocam variabilele in GM -- cele mai importante de pe slotul ocupat de vehiculul jucatorului
		// la urmtorul vehicul spawnat, daca va primi acelasi ID, vor fi populate de functia 'SpawnVehicle'
		format(string, sizeof(string), "You despawned your personal vehicle (Model: %s | Model ID: %d)", vehName[CarInfo[vID][cModel] - 400], CarInfo[vID][cModel]);
		SendClientMessage(playerid, COLOR_YELLOW, string);
		foreach(Player, i) {
			if(GetPlayerVehicleID(playerid) == vID && i != playerid) {
				SendClientMessage(i, COLOR_GRAD1, "The owner of this vehicle has left the server or has destroyed his vehicle.");
			}
		}
		CarInfo[vID][cType] = VEHICLE_TYPE_GENERIC;
		CarInfo[vID][cOwnerSQLID] = 0;
		CarInfo[vID][cModel] = 0;
		memcpy(CarInfo[vID][cOwner], "", 0, MAX_PLAYER_NAME*4, MAX_PLAYER_NAME*4);
		Delete3DTextLabel(CarInfo[vID][cText]);
		CarInfo[vID][cLock] = 0;
		CarInfo[vID][cSQLID] = 0;
		CarInfo[vID][cPaintJob] = -1;
		CarInfo[vID][cColor][0] = -1;
		CarInfo[vID][cColor][1] = -1;
		for(new mod; mod < MAX_MODS; mod++) {
			new
				component = GetVehicleComponentInSlot(vID, mod);
			if(component >= 1000)
				RemoveVehicleComponent(vID, component);
			CarInfo[vID][cMods][mod] = 0;
		}
		clear.string(string);
	}
	return 1;
}

stock SwitchVehicleLock(vID, playerid) {
	if(CarInfo[vID][cLock] == 0)
		CarInfo[vID][cLock] = 1;
	else
		CarInfo[vID][cLock] = 0;
	if(CarInfo[vID][cType] == VEHICLE_TYPE_PERSONAL) {
		new
			string[MAXO_TEXT];
		format(string, MAXO_TEXT, "~w~Personal Vehicle %s", ((CarInfo[vID][cLock] == 0) ? ("~g~Unlocked") : ("~r~Locked")));
		GameTextForPlayer(playerid, string, 5000, 6);
		format(string, MAXO_TEXT, "%s %s.", PlayerName(playerid), ((CarInfo[vID][cLock] == 1) ? ("is locking his personal vehicle and puts the key in his pocket") : ("looks in his pocket for his car key. He finds the key and unlocks his personal vehicle")));
		SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
		format(string, sizeof(string), "UPDATE vehicles_personal SET Locked = %d WHERE ID = %d", CarInfo[vID][cLock], CarInfo[vID][cSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", DEALERSHIP_THREAD_ID);
		clear.string(string);
	}
	foreach(Player, i) {
		if(i != playerid) {
			SetVehicleParamsForPlayer(vID, i, 0, CarInfo[vID][cLock]);
		}
	}
	return 1;
}

COMMAND:parkmycar(playerid, params[]) {
	if(GetPlayerVehicleID(playerid) == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_GRAD1, "You must be in a vehicle to use this command.");
	if(HaveAPersonalCar(playerid) == INVALID_VEHICLE_ID)
		return SendClientMessage(playerid, COLOR_GRAD1, "You don't have a spawned vehicle.");
	new
		vID = GetPlayerVehicleID(playerid);
	if(PlayerInfo[playerid][pSQLID] == CarInfo[vID][cOwnerSQLID]) {
		new
			string[MAXO_TEXT];
		// preluam pozitiile vehiculului
		GetVehiclePos(vID, CarInfo[vID][cLPosition][0], CarInfo[vID][cLPosition][1], CarInfo[vID][cLPosition][2]);
		GetVehicleZAngle(vID, CarInfo[vID][cLPosition][3]);
		// apoi salvam pozitiile in baza de date
		format(string, MAXO_TEXT, "UPDATE vehicles_personal SET PosX = %f, PosY = %f, PosZ = %f, Angle = %f WHERE ID = %d", CarInfo[vID][cLPosition][0], CarInfo[vID][cLPosition][1], CarInfo[vID][cLPosition][2], CarInfo[vID][cLPosition][3], CarInfo[vID][cSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", DEALERSHIP_THREAD_ID);
		// informam jucatorul care a parcat masina
		format(string, MAXO_TEXT, "* NOTE: You've changed the spawn location for your personal vehicle %s (%d).", vehName[CarInfo[vID][cModel] - 400], CarInfo[vID][cModel]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
		// setam si stergem texul de pe vehicul
		memcpy(CarInfo[vID][cOwner], "", 0, MAX_PLAYER_NAME*4, MAX_PLAYER_NAME*4);
		Delete3DTextLabel(CarInfo[vID][cText]);
		// incep noile setari pentru parcarea vehiculului
		new NewCarID = vID;
		DestroyVehicle(vID);

		new noua_masina = CreateVehicle(CarInfo[NewCarID][cModel], CarInfo[NewCarID][cLPosition][0], CarInfo[NewCarID][cLPosition][1], CarInfo[NewCarID][cLPosition][2], CarInfo[NewCarID][cLPosition][3], CarInfo[NewCarID][cColor][0], CarInfo[NewCarID][cColor][1], -1);
		
		memcpy(CarInfo[vID][cOwner], PlayerName(playerid), 0, MAX_PLAYER_NAME * 4, MAX_PLAYER_NAME * 4);
		format(string, 35, "%s's vehicle", CarInfo[NewCarID][cOwner]);
		CarInfo[NewCarID][cText] = Create3DTextLabel(string, COLOR_GRAD1, 0.0, 0.0, 0.0, 30.5, GetVehicleVirtualWorld(NewCarID), 1);
		Attach3DTextLabelToVehicle(CarInfo[NewCarID][cText], noua_masina, 0.0, 0.0, 0.0);
		
		SetVehicleNumberPlate(noua_masina, CarInfo[NewCarID][cPlate]);
		SetVehicleToRespawn(noua_masina);
		clear.string(string);		
	}
	else
		SendClientMessage(playerid, COLOR_GRAD1, "This is not your personal vehicle.");
	return 1;
}

COMMAND:mycarhelp(playerid, params[]) {
	new string[MAXO_TEXT];
	format(string, MAXO_TEXT, "SELECT * FROM vehicles_personal WHERE OwnerSQLID = %d", PlayerInfo[playerid][pSQLID]);
	mysql_tquery(connectionHandle, string, "CheckMyVehicle", "d", playerid);
	clear.string(string);
	return true;
}

function CheckMyVehicle(playerid) {
	rows = cache_num_rows();
	if(rows) {
		ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Command available for your car", ""ALBASTRU2"* To find your car use: /findmycar;\n* To park your car use: /parkmycar;\n* To spawn your car use: /spawnmycar;\n* To despawn yor car use: /despawnmycar;\n* To sell your car at state use: /sellmycartostate;\n* To sell a player's car use: /sellmycarto;\n* To change the color for you car use: /changecolorformycar;\n* To change the number plate, use: /setplatemycar;", "Okay", "");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have any vehicle personal.");
	return true;
}

COMMAND:sellmycartostate(playerid, params[]) {
	new string[MAXO_TEXT], vID = HaveAPersonalCar(playerid);
	if(vID != INVALID_VEHICLE_ID) {
		if(GetPlayerVehicleID(playerid) == vID) {
			if(IsPlayerInRangeOfPoint(playerid, 30.0, 2131.9163, -1150.4362, 24.1587)) {
				new sellprice = CalculateSellPrice(CarInfo[vID][cValue]);
				PlayerInfo[playerid][pAccount] += sellprice;
				PlayerInfo[playerid][pCarSlots] ++;
				format(string, MAXO_TEXT2, "UPDATE players SET Account = %d, CarSlots = %d WHERE ID = %d", PlayerInfo[playerid][pAccount], PlayerInfo[playerid][pCarSlots], PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				format(string, MAXO_TEXT2, "DELETE FROM vehicles_personal WHERE ID = %d AND OwnerSQLID = %d LIMIT 1", CarInfo[vID][cSQLID], PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", DEALERSHIP_THREAD_ID);
				format(string, MAXO_TEXT, "* You have sold your car at state for the amount $%s (65 percent).", FormatNumber(sellprice, 0, '.'));
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				format(string, sizeof(string), "SELECT * FROM vehicles_dealership WHERE Model = %d", CarInfo[vID][cModel]);
				mysql_tquery(connectionHandle, string, "UpdateDSStocks", "");
				DespawnVehicle(playerid);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in the yard from dealership.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "This vehicle isn't your personal vehicle or you aren't in your vehicle.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "Your vehicle isn't spawned to sell it.");
	return true;
}

function UpdateDSStocks() {
	new
		string[MAXO_TEXT];
	rows = cache_num_rows();
	if(rows > 0) {
		new
			id = (cache_get_row_int(0, 0) - 1);
		DealershipInfo[id][dStock] ++;
		format(string, MAXO_TEXT, "UPDATE vehicles_dealership SET Stock = %d WHERE Model = %d", DealershipInfo[id][dStock], DealershipInfo[id][dModel]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", DEALERSHIP_THREAD_ID);
		clear.string(string);
	}
	return true;
}

stock CalculateSellPrice(PriceVehicle) {
	new Float:PriceCar;
	PriceCar = (65*PriceVehicle)/100;
	return floatround(PriceCar, floatround_round);
}

enum gInfo {
	bool: gSell,
	gPrice,
	gOwner,
	gBuyer
}
new
	gSellCarInfo[MAX_VEHICLES][gInfo];

COMMAND:sellmycarto(playerid, params[]) {
	new string[MAXO_TEXT], pID, Price, vID = HaveAPersonalCar(playerid);
	if(vID != INVALID_VEHICLE_ID) {
		if(sscanf(params, "s[24]d", PartialName[playerid][nume_introdus], Price))
			return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/sellmycarto [playerid/PartOfName] [Price]");
		CheckName(playerid, PartialName[playerid][nume_introdus]);
		pID = PartialName[playerid][jucator_gasit];
		if(pID != INVALID_PLAYER_ID) {
			if(GetDistanceBetweenPlayers(playerid, pID) < 10) {
				if(HaveAPersonalCar(pID) == INVALID_VEHICLE_ID) {
					if(PlayerInfo[pID][pCarSlots] > 0) {
						if(Price < 0)
							return SendClientMessage(playerid, COLOR_GRAD1, "Invalid value.");
						if(gSellCarInfo[vID][gSell] == true)
							return SendClientMessage(playerid, COLOR_GRAD1, "This vehicle is already for sale, wait 30 seconds.");
						if(pID == playerid)
							return SendClientMessage(playerid, COLOR_GRAD1, "You can't sell the personal car yourself.");
						gSellCarInfo[vID][gPrice] = Price;
						gSellCarInfo[vID][gOwner] = playerid;
						gSellCarInfo[vID][gBuyer] = pID;
						gSellCarInfo[vID][gSell] = true;
						format(string, MAXO_TEXT, "* You ofer your personal vehicle %s [Model: %d] to %s for $%s.", vehName[GetVehicleModel(vID) - 400], GetVehicleModel(vID), PlayerName(pID), FormatNumber(gSellCarInfo[vID][gPrice], 0, '.'));
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						format(string, MAXO_TEXT, "* %s offer his personal vehicle %s [Model: %d] for $%s, type /acceptsell to accept it.", PlayerName(playerid), vehName[GetVehicleModel(vID) - 400], GetVehicleModel(vID), FormatNumber(gSellCarInfo[vID][gPrice], 0, '.'));
						SendClientMessage(pID, COLOR_LIGHTBLUE, string);
						SetTimerEx("SellCarTimer", 30000, false, "d", vID);
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player doesn't have any car slots available.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "This player has a spawned personal vehicle.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "This player is too far away from you.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid playerid.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have a spawned personal vehicle.");
	return 1;
}

COMMAND:acceptsell(playerid, params[]) {
	new
		string[MAXO_TEXT],
		pID,
		p = 0;
	if(HaveAPersonalCar(playerid) == INVALID_VEHICLE_ID) {
		if(PlayerInfo[playerid][pCarSlots] > 0) {
			if(sscanf(params, "s[24]", PartialName[playerid][nume_introdus]))
				return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/acceptsell [playerid/PartOfName]");
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			pID = PartialName[playerid][jucator_gasit];
			if(pID != INVALID_PLAYER_ID) {
				if(GetDistanceBetweenPlayers(playerid, pID) < 10) {
					new
						vID = HaveAPersonalCar(pID);
					if(vID != INVALID_VEHICLE_ID) {
						if(gSellCarInfo[vID][gSell] == true && gSellCarInfo[vID][gBuyer] == playerid && gSellCarInfo[vID][gOwner] == pID) {
							if(PlayerInfo[playerid][pAccount] >= gSellCarInfo[vID][gPrice]) {
								foreach(Player, i) {
									if(GetPlayerVehicleID(i) == vID) {
										p++;
									}
									break;
								}
								if(p != 0)
									return SendClientMessage(playerid, COLOR_GRAD1, "There are players in this vehicle, can't buy it.");
								memcpy(CarInfo[vID][cOwner], PlayerName(playerid), 0, MAX_PLAYER_NAME * 4, MAX_PLAYER_NAME * 4);
								CarInfo[vID][cOwnerSQLID] = PlayerInfo[playerid][pSQLID];
								format(string, MAXO_TEXT, "%s's vehicle", CarInfo[vID][cOwner]);
								Update3DTextLabelText(CarInfo[vID][cText], COLOR_GRAD1, string);
								format(string, MAXO_TEXT, "UPDATE vehicles_personal SET Owner = '%s', OwnerSQLID = %d WHERE ID = %d", CarInfo[vID][cOwner], CarInfo[vID][cOwnerSQLID], CarInfo[vID][cSQLID]);
								mysql_tquery(connectionHandle, string, "NoReturnThread", "d", DEALERSHIP_THREAD_ID);

								PlayerInfo[playerid][pAccount] -= gSellCarInfo[vID][gPrice];
								PlayerInfo[pID][pAccount] += gSellCarInfo[vID][gPrice];
								PlayerInfo[playerid][pCarSlots] --;
								PlayerInfo[pID][pCarSlots] ++;
								format(string, MAXO_TEXT, "UPDATE players SET Account = %d, CarSlots = %d WHERE ID = %d", PlayerInfo[playerid][pAccount], PlayerInfo[playerid][pCarSlots], PlayerInfo[playerid][pSQLID]);
								mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
								format(string, sizeof(string), "UPDATE players SET Account = %d, CarSlots = %d WHERE id = %d", PlayerInfo[pID][pAccount], PlayerInfo[pID][pCarSlots], PlayerInfo[pID][pSQLID]);
								mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);

								format(string, MAXO_TEXT, "* You bought the personal vehicle from %s [Model: %s (%d)] for $%s.", PlayerName(pID), vehName[GetVehicleModel(vID) - 400], GetVehicleModel(vID), FormatNumber(gSellCarInfo[vID][gPrice], 0, '.'));
								SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
								format(string, sizeof(string), "* %s bought you personal vehicle %s [Model: %d] for $%s.", PlayerName(playerid), vehName[GetVehicleModel(vID) - 400], GetVehicleModel(vID), FormatNumber(gSellCarInfo[vID][gPrice], 0, '.'));
								SendClientMessage(pID, COLOR_LIGHTBLUE, string);
								ResetSellCarVar(vID);
								PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
								clear.string(string);
							} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have enough money to buy this car.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "This vehicle is not for sell.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player doesn't have a spawned personal vehicle.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "This player is not near you.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid / Unknown user.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have any available slots to buy a new car.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You already have a spawned personal vehicle, can't buy another.");
	return 1;
}

function SellCarTimer(vID) {
	if(gSellCarInfo[vID][gSell] == true) {
		ResetSellCarVar(vID);
	}
	return true;
}

stock ResetSellCarVar(vID) {
	gSellCarInfo[vID][gSell] = false;
	gSellCarInfo[vID][gPrice] = -1;
	gSellCarInfo[vID][gOwner] = INVALID_PLAYER_ID;
	gSellCarInfo[vID][gBuyer] = INVALID_PLAYER_ID;
	return true;
}

COMMAND:findmycar(playerid, params[]) {
	if(gPlayerLogged{playerid}) {
		if(IsPlayerInInside(playerid))
			return SendClientMessage(playerid, COLOR_GRAD1, "You can't use this function from inside a building/interior.");
		if(IsPlayerInAnyVehicle(playerid))
			return SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command from vehicle.");
		if(HaveAPersonalCar(playerid) == INVALID_VEHICLE_ID)
			return SendClientMessage(playerid, COLOR_GRAD1, "You don't have a spawned vehicle.");
		if(Spectated[playerid][Status])
			return SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command right now.");
		new string[MAXO_TEXT];
		if(gFindMCarTime[playerid]) {
			format(string, MAXO_TEXT, "Can't use this command, please try again later in %s.", ConvertTime(gFindMCarTime[playerid]));
			SendClientMessage(playerid, COLOR_GRAD1, string);
			clear.string(string);
			return 1;
		}
		else
		{
			new Float:Pos[3], vID = HaveAPersonalCar(playerid);
			vehiculcautat[vID] = playerid;
			StorePlayerData(playerid);
			VizualizeazaMasina(playerid, vID);
			GetVehiclePos(vID, Pos[0], Pos[1], Pos[2]);
			SetPlayerMapIcon(playerid, MAPICON_FINDCAR, Pos[0], Pos[1], Pos[2], 55, 0, MAPICON_GLOBAL_CHECKPOINT);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Your current car position has been shown as a car icon on the map.");
			SetTimerEx("StopVizMasina", 5000, false, "d", playerid);
			gFindMCarTime[playerid] = 2*60;
		}
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are dead, can't use this command.");
	return true;
}

stock VizualizeazaMasina(playerid, carid) {
	gFindMyCar{playerid} = true;
	TogglePlayerSpectating(playerid, true);
	PlayerSpectateVehicle(playerid, carid);
	return true;
}

function StopVizMasina(playerid) {
	TogglePlayerSpectating(playerid, false);
	SetPlayerBack(playerid);
	return 1;
}

stock EnterOnPersonalCar(playerid, vID) {
	new
		string[MAXO_TEXT];
	GetVehiclePos(vID, CarInfo[vID][cLocation][0], CarInfo[vID][cLocation][1], CarInfo[vID][cLocation][2]);
	if(CarInfo[vID][cOwnerSQLID] == PlayerInfo[playerid][pSQLID]) {
		format(string, MAXO_TEXT, "* This is your personal vehicle %s (%d), If you want to lock your personal vehicle, press key 'N'.", vehName[CarInfo[vID][cModel] - 400], CarInfo[vID][cModel]);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
		Update3DTextLabelText(CarInfo[vID][cText], COLOR_GRAD1, "");
		CalculateKM(playerid, vID);
		if(vehiculcautat[vID] == playerid) {
			RemovePlayerMapIcon(playerid, MAPICON_FINDCAR);
			vehiculcautat[vID] = INVALID_PLAYER_ID;
		}
		clear.string(string);
	}
	return true;
}

stock IsVehicleNoTunning(vehicleid) {
	if(vehicleid != INVALID_VEHICLE_ID) {
		switch(GetVehicleModel(vehicleid)) {
			case 481, 462, 471, 581, 461, 468, 463, 522, 509, 510, 586: return true;
		}
	}
	return false;
}

COMMAND:changecolorformycar(playerid, params[]) {
	new vID = GetPlayerVehicleID(playerid), string[MAXO_TEXT], color[2];
	if(HaveAPersonalCar(playerid) == vID) {
		if(!sscanf(params, "dd", color[0], color[1])) {
			if(IsPlayerInRangeOfPoint(playerid, 30.0, 2131.9163, -1150.4362, 24.1587)) {
				if(IsVehicleNoTunning(vID)) {
					CarInfo[vID][cColor][0] = color[0];
					CarInfo[vID][cColor][1] = color[1];
					ChangeVehicleColor(vID, color[0], color[1]);
					format(string, MAXO_TEXT, "UPDATE vehicles_personal SET Color1 = %d, Color2 = %d WHERE ID = %d", color[0], color[1], CarInfo[vID][cSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", DEALERSHIP_THREAD_ID);
					format(string, MAXO_TEXT, "* You changed the colors for your vehicle using the colors %d and %d.", color[0], color[1]);
					SendClientMessage(playerid, COLOR_LIGHTRED, string);
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command for this type of vehicle.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in the yard from dealership.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/changecolorformycar [color1] [color2]");
	} else NotAuthorized();
	return true;
}

COMMAND:setplatemycar(playerid, params[]) {
	new vID = GetPlayerVehicleID(playerid), string[MAXO_TEXT];
	if(HaveAPersonalCar(playerid) == vID) {
		if(!sscanf(params, "s[10]", params)) {
			if(ISBetween(strlen(params), 1, 9)) {
				if(IsVehicleWithEngine(vID)) {
					if(IsPlayerInRangeOfPoint(playerid, 30.0, 2131.9163, -1150.4362, 24.1587)) {
						memcpy(CarInfo[vID][cPlate], params, 0, MAX_PLAYER_NAME * 4, MAX_PLAYER_NAME * 4);
						SetVehicleNumberPlate(vID, params);
						format(string, MAXO_TEXT, "* The new number plate for your vehicle it's: '%s'.", params);
						SendClientMessage(playerid, COLOR_LIGHTRED, string);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "[NOTE]: The new number plate will be active, at the respawn of vehicle.");
						format(string, MAXO_TEXT, "UPDATE vehicles_personal SET Plate = '%s' WHERE ID = %d", params, CarInfo[vID][cSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", DEALERSHIP_THREAD_ID);
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in the yard from dealership.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "The number plate can't be changed for this type of vehicle.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "The lengh must be of minimum 1 until 9 characters.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/setplatemycar [number plate]");
	} else NotAuthorized();
	return true;
}

function CalculateKM(playerid, vID) {
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		if(CarInfo[vID][cType] == VEHICLE_TYPE_PERSONAL) {
			new Float: DistanceKM;
			DistanceKM = GetVehicleDistanceFromPoint(vID, CarInfo[vID][cLPosition][0], CarInfo[vID][cLPosition][1], CarInfo[vID][cLPosition][2]);
			CarInfo[vID][cKM] += DistanceKM / 1000;
			GetVehiclePos(vID, CarInfo[vID][cLPosition][0], CarInfo[vID][cLPosition][1], CarInfo[vID][cLPosition][2]);
			SetTimerEx("CalculateKM", 3000, false, "dd", playerid, vID);
		}
		
	} 
	else 
	{
		new  query[MAXO_TEXT];
		format(query, MAXO_TEXT, "UPDATE vehicles_personal SET KM = %f WHERE ID = %d", CarInfo[vID][cKM], CarInfo[vID][cSQLID]);
		mysql_tquery(connectionHandle, query, "NoReturnThread", "d", DEALERSHIP_THREAD_ID);
		clear.string(query);
	}
	return 1;
}

// End Of File ...
