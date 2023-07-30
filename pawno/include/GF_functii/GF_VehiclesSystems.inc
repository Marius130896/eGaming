/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_VehiclesSystems_included
	#endinput
#else
	#define GF_VehiclesSystems_included
#endif

new
	vehiculcautat[MAX_VEHICLES],
	timertestdrive
;

enum cInfo {
	cSQLID,
	cModel,
	Float:cLocation[3],
	Float:cAngle,
	cColor[2],
	cRespawnTime,
	cType,
	cFactionID,
	cRank,
	cBiz,
	cJob,
	Float:cHealth,
	bool:cEngine,
	cLastBroken,
	bool:cStareBroken,
	Text3D:cText,
	cValue,
	cOwner[MAX_PLAYER_NAME],
	cLock,
	cPlate[MAX_PLAYER_NAME],
	cOwnerSQLID,
	cPaintJob,
	cMods[15],
	Float:cKM,
	Float:cLPosition[4]
};
new
	CarInfo[MAX_VEHICLES][cInfo],
	TotalVehicles = 0;
#define MAX_MODS 15

#tryinclude <GF_functii/GF_private/GF_VehiclesSystem-private>

stock HideCarTD(playerid) {
	TextDrawHideForPlayer(playerid,VehicleHPBar[0]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[1]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[2]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[3]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[4]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[5]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[6]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[7]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[8]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[9]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[10]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[11]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[12]);

	TextDrawHideForPlayer(playerid, Fuel[playerid]),
	TextDrawHideForPlayer(playerid, BlackBox),
	TextDrawHideForPlayer(playerid, Moving[playerid]);

	PlayerTextDrawHide(playerid, Speedo);
	return true;
}

stock VehHUpd(playerid, Float:vhp) {
	if(vhp != VHPBar[playerid])
		VehHealthBar(playerid, vhp);
	VHPBar[playerid] = vhp;
	return true;
}

stock VehHealthBar(playerid, Float:vhp) {
	TextDrawHideForPlayer(playerid,VehicleHPBar[0]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[1]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[2]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[3]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[4]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[5]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[6]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[7]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[8]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[9]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[10]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[11]);
	TextDrawHideForPlayer(playerid,VehicleHPBar[12]);
	if(vhp == INVALID_VEH_HP) return 1;
	else if (0.0 <= vhp <= 250.0) TextDrawShowForPlayer(playerid,VehicleHPBar[0]);
	else if(250.0 <= vhp <= 317.0) TextDrawShowForPlayer(playerid,VehicleHPBar[1]);
	else if(317.0 <= vhp <= 385.0) TextDrawShowForPlayer(playerid,VehicleHPBar[2]);
	else if(385.0 <= vhp <= 453.0) TextDrawShowForPlayer(playerid,VehicleHPBar[3]);
	else if(453.0 <= vhp <= 521.0) TextDrawShowForPlayer(playerid,VehicleHPBar[4]);
	else if(521.0 <= vhp <= 589.0) TextDrawShowForPlayer(playerid,VehicleHPBar[5]);
	else if(589.0 <= vhp <= 657.0) TextDrawShowForPlayer(playerid,VehicleHPBar[6]);
	else if(657.0 <= vhp <= 725.0) TextDrawShowForPlayer(playerid,VehicleHPBar[7]);
	else if(725.0 <= vhp <= 793.0) TextDrawShowForPlayer(playerid,VehicleHPBar[8]);
	else if(793.0 <= vhp <= 861.0) TextDrawShowForPlayer(playerid,VehicleHPBar[9]);
	else if(861.0 <= vhp <= 929.0) TextDrawShowForPlayer(playerid,VehicleHPBar[10]);
	else if(929.0 <= vhp <= 1001.0) TextDrawShowForPlayer(playerid,VehicleHPBar[11]);
	else if(1001.0 <= vhp <= 1000000.0) {
		TextDrawShowForPlayer(playerid,VehicleHPBar[12]);
		SetVehicleToRespawn(GetPlayerVehicleID(playerid));
		SendClientMessage(playerid, 0xFFFF00AA, "[AntiCrash]That car had an error and had to be respawned.");
	}
	else
		SendClientMessage(playerid, COLOR_GREEN, "Eroare: Nu am putut detecta damage-ul masinii...");
	return true;
}

function CheckGas() {
	new engine, lights, alarm, doors, bonnet, boot, objective;
	foreach(Player, i) {
		new
			vID = GetPlayerVehicleID(i);
		if(GetPlayerState(i) == PLAYER_STATE_DRIVER) {
			if(!IsVehicleBike(vID) && !IsVehicleBoat(vID) && !IsVehiclePlane(vID)) {
				if(Gas[vID] != 0) {
					GetVehicleParamsEx(vID, engine, lights, alarm, doors, bonnet, boot, objective);
					if(engine == VEHICLE_PARAMS_ON) {
						if(Gas[vID] <= 10)
							PlayerPlaySound(i, 1085, 0.0, 0.0, 0.0);
						Gas[vID] --;
					}
				}
				else
				{
					NoFuel[i] = 1;
					TogglePlayerControllable(i, false);
					GameTextForPlayer(i,"~w~~n~~n~~n~~n~~n~~n~~n~~n~No fuel in Vehicle~n~Press ENTER to leave the vehicle",15500,3);
				}
			}
		}
	}
	return true;
}

stock isLicensePlate(vehicleid) {
    switch(GetVehicleModel(vehicleid)) {
        case 406, 417, 425, 430, 432, 435, 441, 444, 446, 447, 449, 450,
        452, 453, 454, 457, 460, 464, 465, 468, 469, 471, 472, 473, 476,
        481, 484, 485, 486, 487, 488, 493, 494, 497, 501, 502, 503, 509,
        510, 511, 512, 513, 514, 515, 519, 520, 522, 528, 530, 531, 532,
        537, 538, 539, 548, 553, 563, 564, 568, 569, 570, 571, 572, 573,
        577, 583, 584, 590, 591, 592, 593, 594, 595, 601, 606, 607, 608,
        610, 611: return true;
    }
    return false;
}

stock IsVehiclePlane(vehicleid) {
	switch(GetVehicleModel(vehicleid)) {
		case 417, 425, 447, 460: return true;
		case 464, 465, 469, 476: return true;
		case 487, 488, 497, 501: return true;
		case 511, 512, 513, 519: return true;
		case 520, 548, 553, 563: return true;
		case 592, 593: return true;
	}
	return false;
}

stock IsVehicleBoat(vehicleid) {
	switch(GetVehicleModel(vehicleid)) {
		case 430, 446, 452, 453, 454: return true;
		case 472, 473, 484, 493, 595: return true;
	}
	return false;
}

stock IsVehicleBike(vehicleid) {
	switch(GetVehicleModel(vehicleid)) {
		case 481, 509, 510: return true;
	}
	return false;
}

stock NamePlateVehicle(vehicleid) {
	new
		plate[10];
	switch(vehicleid) {
		case FACT_CIVIL: plate = "CIV";
		case FACT_LSPD: plate = "POL";
		case FACT_FBI: plate = "FBI";
		case FACT_MEDIC: plate = "MED";
		case FACT_LCN: plate = "LCN";
		case FACT_YKZ: plate = "YKZ";
		case FACT_HITMAN: plate = "HIT";
		case FACT_CNN: plate = "NEW";
		case FACT_TAXI: plate = "TXC";
		case FACT_BLOODS: plate = "BSG";
		case FACT_CRIPS: plate = "CZG";
	}
	return plate;
}

stock IsAFactionVehicle(vID) {
	switch(CarInfo[vID][cType]) {
		case VEHICLE_TYPE_FACTION: return true;
	}
	return false;
}

stock IsADMVehicle(vID) {
	switch(CarInfo[vID][cType]) {
		case VEHICLE_TYPE_CARTEST: return true;
	}
	return false;
}

stock IsARentableVehicle(vID) {
	switch(CarInfo[vID][cType]) {
		case VEHICLE_TYPE_RENTCAR: return true;
	}
	return false;
}

stock EnterOnRentCar(playerid, newcar) {
	new
		carstring[MAXO_TEXT1];
	SendClientMessage(playerid, COLOR_LIGHTBLUE, "* "GRI3"Type /rentcar to rent this vehicle or press ENTER key to get out.");
	TogglePlayerControllable(playerid, false);
	format(carstring, MAXO_TEXT1, "~w~Vehicle Cost~n~~g~$~y~%s", FormatNumber(CarInfo[newcar][cValue], 0, '.'));
	GameTextForPlayer(playerid, carstring, 5000, 1);
	clear.string(carstring);
	return true;
}

stock IsVehicleWithEngine(vehicleid) {
	switch(GetVehicleModel(vehicleid)) {
		case 400..431: return true;
		case 433..434: return true;
		case 435..440: return true;
		case 442..448: return true;
		case 451..480: return true;
		case 482..500: return true;
		case 502..508: return true;
		case 511..563: return true;
		case 565..568: return true;
		case 570..583: return true;
		case 585..589: return true;
		case 592, 593, 609: return true;
		case 595..605: return true;
	}
	return false;
}

stock LockCar(carid) {
	CarInfo[carid][cLock] = 1;
	foreach (Player, i)
		SetVehicleParamsForPlayer(carid, i, 0, VEHICLE_PARAMS_OFF);
	return 1;
}

stock UnLockCar(carid) {
	CarInfo[carid][cLock] = 0;
	foreach (Player, i)
		SetVehicleParamsForPlayer(carid, i, 0, VEHICLE_PARAMS_ON);
	return 1;
}

function Fillup(playerid, vID, BizID) {
	new
		string[MAXO_TEXT],
		FillUp, Suma;
	FillUp = GasMax - Gas[vID];
	if(FillUp > 50)
		BizInfo[BizID][bProducts] -= 2;
	else
		BizInfo[BizID][bProducts] --;
	Gas[vID] += FillUp;
	Suma = FillUp*5;
	SafeGivePlayerMoney(playerid, -Suma);
	format(string, MAXO_TEXT, "* Vehicle filled up, for: $%s.", FormatNumber(Suma, 0, '.'));
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
	format(string, MAXO_TEXT, "~r~-~y~$%s", FormatNumber(Suma, 0, '.'));
	GameTextForPlayer(playerid, string, 5000, 1);
	BizInfo[BizID][bTakings] += Suma;
	format(string, MAXO_TEXT, "UPDATE bizz SET Takings = %d, Products = %d WHERE ID = %d", BizInfo[BizID][bTakings], BizInfo[BizID][bProducts], BizInfo[BizID][bSQLID]);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
	TogglePlayerControllable(playerid, true);
	clear.string(string);
	return 1;
}

stock Update3DtextRentCar(carid) {
	new rentedby = INVALID_PLAYER_ID;
	for(new i = 0; i < MAX_PLAYERS; i ++) {
		if(HireCar[i] == carid) {
			rentedby = i;
			break;
		}
	}
	new carstring[MAXO_TEXT];
	if(rentedby != INVALID_PLAYER_ID)
		format(carstring, MAXO_TEXT, "Rented by: %s", PlayerName(rentedby)), Update3DTextLabelText(CarInfo[carid][cText], COLOR_RENTED, carstring);
	else
	{
		new tipmasina = CarInfo[carid][cType];
		new valoare = CarInfo[carid][cValue];
		switch(tipmasina) {
			case VEHICLE_TYPE_RENTCAR: format(carstring, MAXO_TEXT, "Vehicle for rent!\nRent price: $%s\nType: /rentcar", FormatNumber(valoare, 0, '.'));
		}
		Update3DTextLabelText(CarInfo[carid][cText], COLOR_PROPERTY, carstring);
	}
	clear.string(carstring);
	return true;
}


stock IsValidComponent(vehicleid, componentid)
{
	new
		model = GetVehicleModel( vehicleid );

    switch( componentid )
	{
        case 1000:
        {
			switch( model )
			{
				case 589, 492, 516, 404, 547, 489, 505, 405, 421: return true;
			}
		}
        case 1001:
        {
			switch( model )
		  	{
     			case 496, 401, 518, 527, 415, 585, 546, 410, 603, 426, 436, 405,
				     580, 439, 550, 549, 420, 540, 529: return true;
     		}
        }
        case 1002:
        {
			switch( model )
		  	{
			  	case 496, 546, 517, 551, 418, 516, 404, 489, 505: return true;
			}
        }
        case 1003:
        {
			switch( model )
		  	{
				case 496, 401, 518, 415, 585, 517, 410, 551, 426, 436, 547, 439,
				     550, 549, 420, 491, 529: return true;
			}
        }
        case 1004:
        {
          	switch( model )
		  	{
			  	case 401, 589, 492, 546, 516, 600, 426, 489, 505, 550, 420, 540,
				     478: return true;
        	}
        }
        case 1005:
        {
          	switch( model )
		  	{
			  	case 401, 518, 589, 492, 551, 600, 426, 489, 505, 550, 420, 478:
			  		return true;
			}
		}
        case 1006:
        {
          	switch( model )
		  	{
			  	case 496, 401, 518, 589, 585, 492, 546, 551, 418, 603, 600, 426,
				     436, 489, 505, 580, 550, 540, 529, 477: return true;
        	}
        }
        case 1007, 1017:
        {
          	switch( model )
		  	{
			  	case 496, 422, 401, 518, 527, 415, 589, 585, 546, 517, 410, 516,
				     404, 603, 600, 436, 580, 439, 549, 540, 491, 529, 477:
			 		return true;
        	}
        }
        case 1011:
        {
          	switch( model )
		  	{
			  	case 496, 549, 529: return true;
			}
		}
        case 1012:
        {
          	switch( model )
		  	{
			  	case 549, 478, 529: return true;
			}
        }
        case 1013:
        {
          	switch( model )
		  	{
			  	case 422, 401, 518, 589, 585, 400, 410, 500, 404, 600, 436, 489,
				     505, 478, 439: return true;
			}
        }
        case 1014:
        {
          	switch( model )
		  	{
			  	case 527, 542, 405, 491, 421: return true;
			}
        }
        case 1015:
        {
          	switch( model )
		  	{
			  	case 527, 542, 516: return true;
			}
        }
        case 1016:
        {
          	switch( model )
		  	{
			  	case 589, 492, 517, 551, 418, 516, 404, 547, 489, 505, 421:
			  		return true;
			}
        }
        case 1018:

        {
          	switch( model )
		  	{
			  	case 518, 527, 415, 542, 589, 585, 546, 400, 517, 551, 516, 603,
				     600, 547, 489, 505, 405, 580, 550, 549, 540, 491, 421, 529,
					 477: return 1;
        	}
        }
        case 1019:
        {
          	switch( model )
		  	{
			  	case 496, 422, 401, 415, 542, 585, 546, 400, 517, 410, 551, 500,
				     516, 404, 603, 426, 436, 547, 489, 505, 405, 550, 549, 420,
					 540, 491, 421, 529, 477: return true;
        	}
        }
        case 1020:
        {
          	switch( model )
		  	{
			  	case 496, 422, 401, 518, 527, 542, 589, 585, 400, 517, 410, 551,
				     500, 418, 516, 404, 603, 600, 436, 547, 489, 505, 405, 580,
					 550, 549, 540, 491, 478, 421, 529, 477: return true;
        	}
        }
        case 1021:
        {
          	switch( model )
		  	{
			  	case 422, 527, 542, 400, 410, 551, 500, 418, 516, 404, 426, 436,
				     547, 405, 420, 491, 478, 421, 477: return true;
        	}
        }
        case 1022:
        {
          	switch( model )
		  	{
			  	case 600, 436, 478: return true;
			}
        }
        case 1023:
        {
          	switch( model )
		  	{
			  	case 496, 518, 415, 585, 546, 517, 410, 551, 603, 405, 580, 439,
				     550, 549, 540, 491, 421, 529: return true;
        	}
        }
        case 1024:
        {
          	switch( model )
		  	{
			  	case 589, 546, 400, 410, 500, 603, 489, 505, 540, 478:
			  		return true;
			}
        }
        case 1008..1010, 1025, 1073..1087, 1096..1098:
        {
            if( IsTransfenderVehicle( model ) || IsLocolowVehicle( model ) ||
			    IsWAAVehicle( model ))
				return true;
        }
        case 1190..1193, 1134..1137:
        {
             if( model == 576 ) return true;
        }
        case 1186..1189, 1129..1133, 1102:
        {
             if( model == 567 ) return true;
        }
        case 1181..1184, 1128, 1107..1108, 1103..1105:
        {
             if( model == 536 ) return true;
        }
        case 1185, 1178..1180, 1122..1127, 1106, 1100..1101:
        {
             if( model == 534 ) return true;
        }
        case 1174..1177, 1099, 1042..1044:
        {
             if( model == 575 ) return true;
        }
        case 1173, 1158..1162, 1065..1072:
        {
             if( model == 559 ) return true;
        }
        case 1171..1172, 1146..1149, 1034..1041:
        {
             if( model == 562 ) return true;
        }
        case 1169..1170, 1138..1141, 1026..1033:
        {
             if( model == 560 ) return true;
        }
        case 1163..1168, 1088..1095:
        {
             if( model == 558 ) return true;
        }
        case 1154..1157, 1055..1064:
        {
             if( model == 561 ) return true;
        }
        case 1150..1153, 1045..1054:
        {
             if( model == 565 ) return true;
        }
        case 1109..1121:
        {
             if( model == 535 ) return true;
        }
        case 1142..1145:
        {
            switch( model )
		  	{
			  	case 401, 518, 542, 589, 585, 546, 517, 603, 439, 550, 549, 540,
				     491: return true;
			}
        }
    }
    return false;

}

stock IsTransfenderVehicle(model)
{
	switch(model)
	{
	    case 400, 401, 402, 404, 405, 409, 410, 411, 415, 418, 419, 420, 421,
		     422, 424, 426, 429, 436, 438, 439, 442, 445, 451, 458, 466, 467, 474,
			 475, 477, 478, 479, 480, 489, 491, 492, 496, 500, 505, 506, 507,
			 516, 517, 518, 527, 526, 529, 533, 540, 541, 542, 545, 546, 547,
			 549, 550, 551, 555, 575, 579, 580, 585, 587, 589, 600, 602, 603:
 			return true;
	}
	return false;
}

stock IsLocolowVehicle(model)
{
    switch(model)
    {
		case 412, 534, 535, 536, 566, 567, 576: return true;
    }
    return false;
}

stock IsWAAVehicle(model)
{
    switch(model)
    {
		case 558, 559, 560, 561, 562, 565: return true;
    }
    return false;
}

stock GetVehicleMods(playerid, carid) {
	#pragma unused playerid
	if (carid) { // prevenire bug
		new exhaust, frontbumper, rearbumper, roof, spoilers, sideskirt1,
		sideskirt2, wheels, hydraulics, nitro, hood, lamps, stereo, ventright, ventleft;
		exhaust = GetVehicleComponentInSlot(carid, CARMODTYPE_EXHAUST);
		#pragma unused exhaust
		frontbumper = GetVehicleComponentInSlot(carid, CARMODTYPE_FRONT_BUMPER);
		#pragma unused frontbumper
		rearbumper = GetVehicleComponentInSlot(carid, CARMODTYPE_REAR_BUMPER);
		#pragma unused rearbumper
		roof = GetVehicleComponentInSlot(carid, CARMODTYPE_ROOF);
		#pragma unused roof
		spoilers = GetVehicleComponentInSlot(carid, CARMODTYPE_SPOILER);
		#pragma unused spoilers
		sideskirt1 = GetVehicleComponentInSlot(carid, CARMODTYPE_SIDESKIRT);
		#pragma unused sideskirt1
		sideskirt2 = GetVehicleComponentInSlot(carid, CARMODTYPE_SIDESKIRT);
		#pragma unused sideskirt2
		wheels = GetVehicleComponentInSlot(carid, CARMODTYPE_WHEELS);
		#pragma unused wheels
		hydraulics = GetVehicleComponentInSlot(carid, CARMODTYPE_HYDRAULICS);
		#pragma unused hydraulics
		nitro = GetVehicleComponentInSlot(carid, CARMODTYPE_NITRO);
		#pragma unused nitro
		hood = GetVehicleComponentInSlot(carid, CARMODTYPE_HOOD);
		#pragma unused hood
		lamps = GetVehicleComponentInSlot(carid, CARMODTYPE_LAMPS);
		#pragma unused lamps
		stereo = GetVehicleComponentInSlot(carid, CARMODTYPE_STEREO);
		#pragma unused stereo
		ventright = GetVehicleComponentInSlot(carid, CARMODTYPE_VENT_RIGHT);
		#pragma unused ventright
		ventleft = GetVehicleComponentInSlot(carid, CARMODTYPE_VENT_LEFT);
		#pragma unused ventleft

		if(CarInfo[carid][cType] == VEHICLE_TYPE_PERSONAL) {
			UpdateVehicleMods(carid);
		}
	}
	return true;
}

stock UpdateVehicleMods(carid) {
	if (carid) { // prevenire bug
		new exhaust, frontbumper, rearbumper, roof, spoilers, sideskirt1,
		sideskirt2, wheels, hydraulics, nitro, hood, lamps, stereo, ventright, ventleft;
		exhaust = GetVehicleComponentInSlot(carid, CARMODTYPE_EXHAUST);
		frontbumper = GetVehicleComponentInSlot(carid, CARMODTYPE_FRONT_BUMPER);
		rearbumper = GetVehicleComponentInSlot(carid, CARMODTYPE_REAR_BUMPER);
		roof = GetVehicleComponentInSlot(carid, CARMODTYPE_ROOF);
		spoilers = GetVehicleComponentInSlot(carid, CARMODTYPE_SPOILER);
		sideskirt1 = GetVehicleComponentInSlot(carid, CARMODTYPE_SIDESKIRT);
		sideskirt2 = GetVehicleComponentInSlot(carid, CARMODTYPE_SIDESKIRT);
		wheels = GetVehicleComponentInSlot(carid, CARMODTYPE_WHEELS);
		hydraulics = GetVehicleComponentInSlot(carid, CARMODTYPE_HYDRAULICS);
		nitro = GetVehicleComponentInSlot(carid, CARMODTYPE_NITRO);
		hood = GetVehicleComponentInSlot(carid, CARMODTYPE_HOOD);
		lamps = GetVehicleComponentInSlot(carid, CARMODTYPE_LAMPS);
		stereo = GetVehicleComponentInSlot(carid, CARMODTYPE_STEREO);
		ventright = GetVehicleComponentInSlot(carid, CARMODTYPE_VENT_RIGHT);
		ventleft = GetVehicleComponentInSlot(carid, CARMODTYPE_VENT_LEFT);
		if(spoilers >= 1000)    CarInfo[carid][cMods][0] = spoilers;
		if(hood >= 1000)        CarInfo[carid][cMods][1] = hood;
		if(roof >= 1000)        CarInfo[carid][cMods][2] = roof;
		if(sideskirt1 >= 1000)  CarInfo[carid][cMods][3] = sideskirt1;
		if(lamps >= 1000)       CarInfo[carid][cMods][4] = lamps;
		if(nitro >= 1000)       CarInfo[carid][cMods][5] = nitro;
		if(exhaust >= 1000)     CarInfo[carid][cMods][6] = exhaust;
		if(wheels >= 1000)      CarInfo[carid][cMods][7] = wheels;
		if(stereo >= 1000)      CarInfo[carid][cMods][8] = stereo;
		if(hydraulics >= 1000)  CarInfo[carid][cMods][9] = hydraulics;
		if(frontbumper >= 1000) CarInfo[carid][cMods][10] = frontbumper;
		if(rearbumper >= 1000)  CarInfo[carid][cMods][11] = rearbumper;
		if(ventright >= 1000)   CarInfo[carid][cMods][12] = ventright;
		if(ventleft >= 1000)    CarInfo[carid][cMods][13] = ventleft;
		if(sideskirt2 >= 1000)  CarInfo[carid][cMods][14] = sideskirt2;
		SaveVehMods(carid);
	}
	return 1;
}

stock SaveVehMods(vID) {
	if(vID != INVALID_VEHICLE_ID) {
		if(CarInfo[vID][cType] == VEHICLE_TYPE_PERSONAL) {
			new
				query[300];
			format(query, sizeof(query), "UPDATE vehicles_personal SET Spoilers = %d, Hood = %d, Roof = %d, Sideskirt1 = %d, Lamps = %d, Nitro = %d, Exhaust = %d, Wheels = %d, Stereo = %d, Hydraulics = %d, Frontbumper = %d, Rearbumper = %d, Ventright = %d, Ventleft = %d, Sideskirt2 = %d WHERE ID = %d",
			CarInfo[vID][cMods][0], // Spoilers
			CarInfo[vID][cMods][1], // Hood
			CarInfo[vID][cMods][2], // Roof
			CarInfo[vID][cMods][3], // Sideskirt1
			CarInfo[vID][cMods][4], // Lamps
			CarInfo[vID][cMods][5], // Nitro
			CarInfo[vID][cMods][6], // Exhaust
			CarInfo[vID][cMods][7], // Wheels
			CarInfo[vID][cMods][8], // Stereo
			CarInfo[vID][cMods][9], // Hydraulics
			CarInfo[vID][cMods][10], // Frontbumper
			CarInfo[vID][cMods][11], // Rearbumper
			CarInfo[vID][cMods][12], // Ventright
			CarInfo[vID][cMods][13], // Ventleft
			CarInfo[vID][cMods][14], // Sideskirt2
			CarInfo[vID][cSQLID]
			);
			mysql_tquery(connectionHandle, query, "NoReturnThread", "d", TUNNING_THREAD_ID);
			clear.string(query);
		}
	}
	return true;
}

stock LoadVehicleMods(vehicleid) {
	ChangeVehiclePaintjob(vehicleid, CarInfo[vehicleid][cPaintJob]);
	ChangeVehicleColor(vehicleid, CarInfo[vehicleid][cColor][0], CarInfo[vehicleid][cColor][1]);
	for(new m; m < MAX_MODS; m++) {
		if(CarInfo[vehicleid][cMods][m] >= 1000) {
			if(IsValidComponent(vehicleid, CarInfo[vehicleid][cMods][m]))
				AddVehicleComponent(vehicleid, CarInfo[vehicleid][cMods][m]);
		}
	}
	return true;
}

stock SetVehicleForPlayers(vID) {
	new string[MAXO_TEXT];
	if(vID != INVALID_VEHICLE_ID) {
		switch(CarInfo[vID][cType]) {
			case VEHICLE_TYPE_FACTION: {
				format(string, MAX_PLAYER_NAME, "eG %d %s", CarInfo[vID][cSQLID], NamePlateVehicle(CarInfo[vID][cFactionID]));
				SetVehicleNumberPlate(vID, string);
				SetVehicleToRespawn(vID);
			}
			case VEHICLE_TYPE_CARTEST: {
				format(string, MAX_PLAYER_NAME, "eG %02d DMV", CarInfo[vID][cSQLID]);
				SetVehicleNumberPlate(vID, string);
				SetVehicleToRespawn(vID);
				SetVehicleVirtualWorld(vID, DMV_VW);
			}
			case VEHICLE_TYPE_RENTCAR: {
				format(string, MAXO_TEXT, "Vehicle for rent!\nRent price: $%s\nType: /rentcar", FormatNumber(CarInfo[vID][cValue], 0, '.'));
				CarInfo[vID][cText] = Create3DTextLabel(string, COLOR_PROPERTY, 0.0, 0.0, 0.0, 30.5, GetVehicleVirtualWorld(vID), 1);
				Attach3DTextLabelToVehicle(CarInfo[vID][cText], vID, 0.0, 0.0, 0.0);
				format(string, MAX_PLAYER_NAME, "eG %02d RNT", CarInfo[vID][cSQLID]);
				SetVehicleNumberPlate(vID, string);
				SetVehicleToRespawn(vID);
			}
		}
	}
	clear.string(string);
	return true;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {
	if(IsPlayerNPC(playerid)) return 1;
	new
		string[96], Float:X, Float:Y, Float:Z;
	format(string, 96, "~g~%s", vehName[GetVehicleModel(vehicleid)-400]);
	GameTextForPlayer(playerid, string, 2000, 1);
	switch(CarInfo[vehicleid][cType]) {
		case VEHICLE_TYPE_CARTEST..VEHICLE_TYPE_BOATTEST: {
			if(!TakingLesson{playerid}) {
				GetPlayerPos(playerid, X, Y, Z);
				SafeSetPlayerPos(playerid, X, Y, Z);
			}
			else
			{
				if(DMVTimer{playerid}) {
					DMVTimer{playerid} = false;
					SendClientMessage(playerid, COLOR_GREY, "In regula. Acum ca ai revenit la timp in vehiculul de test, sa continuam examenul.");
				}
			}
		}
		case VEHICLE_TYPE_FACTION: {
			if(ISBetween(CarInfo[vehicleid][cFactionID], FACT_LSPD, MAX_FACTIONS-1) && !ispassenger) {
				if(PlayerInfo[playerid][pFactiune] == CarInfo[vehicleid][cFactionID]) {
					if(PlayerInfo[playerid][pRank] < CarInfo[vehicleid][cRank]) {
						GetPlayerPos(playerid, X, Y, Z);
						SafeSetPlayerPos(playerid, X, Y, Z);
						format(string, MAXO_TEXT, "You need Rank %d to drive this vehicle.", CarInfo[vehicleid][cRank]);
						SendClientMessage(playerid, COLOR_GRAD1, string);						
					}
				}
				else
				{
					GetPlayerPos(playerid, X, Y, Z);
					SafeSetPlayerPos(playerid, X, Y, Z);
					format(string, MAXO_TEXT, "You aren't member in faction %s to use this vehicle.", FactionInfo[CarInfo[vehicleid][cFactionID]][fName]), 
					SendClientMessage(playerid, COLOR_GRAD1, string);					
				}			
			}
		}
	}
	clear.string(string);
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid) {
	switch(CarInfo[vehicleid][cType]) {
		case VEHICLE_TYPE_CARTEST..VEHICLE_TYPE_BOATTEST: {
			if(TakingLesson{playerid}) {
				DMVTimer{playerid} = true;
				SetTimerEx("PlayerLeaveCarTest", 10000 * 3, false, "ui", playerid, vehicleid);
				SendClientMessage(playerid, COLOR_GREY, "Ai la dispozitie "ALBASTRU2"30 "GRI3"de secunde sa revii in masina de test!");
			}
		}
	}
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	new string[MAXO_TEXT];
	if(IsVehicleWithEngine(vehicleid)) {
		CarInfo[vehicleid][cEngine] = false;
		CarInfo[vehicleid][cStareBroken] = false;
		CarInfo[vehicleid][cHealth] = 1000.0;
		Gas[vehicleid] = RandomEx(20, 80);
		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, alarm, doors, bonnet, boot, objective);
	}
	else
		SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);
	StopCarRadio(vehicleid);
	for(new i = 0; i < MAX_PLAYERS; i ++) {
		if(HireCar[i] == vehicleid) {
			if(i != INVALID_PLAYER_ID) {
				if(HireCar[i] > 0)
					format(string, MAXO_TEXT, "* "GRI3"You vehicle rented (ID: %d), it has been returned.", HireCar[i]), SendClientMessage(i, COLOR_LIGHTBLUE, string);
				HireCar[i] = INVALID_PLAYER_ID;
				Update3DtextRentCar(vehicleid);
			}
		}
		if(!IsPlayerInAnyVehicle(i))
			gLastDriver[vehicleid] = INVALID_PLAYER_ID,
			gLastCar[i] = 0;
	}
	switch(CarInfo[vehicleid][cType]) {
		case VEHICLE_TYPE_CARTEST..VEHICLE_TYPE_BOATTEST: Gas[vehicleid] = GasMax;
		case VEHICLE_TYPE_PERSONAL: LoadVehicleMods(vehicleid);
		case VEHICLE_TYPE_GENERIC: DestroyVehicle(vehicleid), TotalVehicles --;
		case VEHICLE_TYPE_FARMER_A..VEHICLE_TYPE_TRUCKER: {
			CarInfo[vehicleid][cModel] = 0;
			CarInfo[vehicleid][cRespawnTime] = 0;
			CarInfo[vehicleid][cHealth] = 0;
			CarInfo[vehicleid][cType] = VEHICLE_TYPE_GENERIC;
			CarInfo[vehicleid][cFactionID] = FACT_CIVIL;
			CarInfo[vehicleid][cRank] = 0;
			CarInfo[vehicleid][cBiz] = 0;
			CarInfo[vehicleid][cLastBroken] = 0;
			CarInfo[vehicleid][cEngine] = false;
			CarInfo[vehicleid][cLock] = 0;
			DestroyVehicle(vehicleid),
			TotalVehicles --;
		}
	}
	if(ISBetween(CarInfo[vehicleid][cFactionID], FACT_LSPD, MAX_FACTIONS)) {
		if(CarInfo[vehicleid][cLastBroken] <= gLocalTimeStamp) {
			new
				panels, tires;
			GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
			panels = encode_panels(1, 2, 1, 2, 1, 2, 1);
			doors = encode_doors(2, 2, 2, 2, 2, 2);
			UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
			foreach(Player, i)
				SetVehicleParamsForPlayer(vehicleid, i, 0, 0);
		}
	}
	UnLockCar(vehicleid);
	clear.string(string);
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	new
		informeaza = gLastDriver[vehicleid];
	if(IsARentableVehicle(vehicleid)) {
		if(IsPlayerConnected(informeaza)) {
			SendClientMessage(informeaza, COLOR_LIGHTBLUE, "* "GRI3"You have destroyed your rented vehicle. It has been returned!");
			HireCar[killerid] = INVALID_PLAYER_ID;
			Update3DtextRentCar(vehicleid);
		}
	}
	if(CarInfo[vehicleid][cType] == VEHICLE_TYPE_PERSONAL) {
		for(new m = 0; m < MAX_MODS; m++) 
			CarInfo[vehicleid][cMods][m] = 0; // resetam tunning-ul default
		SaveVehMods(vehicleid); // salvam tunning-ul default al masinii
	}
	return 1;
}

stock IsVehicleForCop(vID) {
	switch(CarInfo[vID][cFactionID]) {
		case FACT_LSPD: return true;
		case FACT_FBI: return true;
	}
	return false;
}

COMMAND:fuelcars(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] > 1) {
		for(new i = 0; i < MAX_VEHICLES; i ++) {
			Gas[i] = GasMax;
		}
		SendClientMessage(playerid, COLOR_GREY, "* All vehicles has been filled.");
	} else NotAuthorized();
	return true;
}

COMMAND:engine(playerid, params[]) {
	new vID = GetPlayerVehicleID(playerid);
	new engine, lights, alarm, doors, bonnet, boot, objective;
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		if(IsVehicleWithEngine(vID)) {
			if(ISBetween(CarInfo[vID][cFactionID], FACT_LSPD, MAX_FACTIONS) && CarInfo[vID][cLastBroken] <= gLocalTimeStamp)
				return SendClientMessage(playerid, COLOR_GRAD1, "Your engine is broken. Repair it first: /repaircar");
			if(Gas[vID] < 1)
				return SendClientMessage(playerid, COLOR_GRAD1, "You don't have fuel anymore, the engine can't be started.");
			GetVehicleParamsEx(vID, engine, lights, alarm, doors, bonnet, boot, objective);
			if(PlayerInfo[playerid][pFarmingTime] == 0 && CarInfo[vID][cType] == VEHICLE_TYPE_FARMER_A)
				return ShowPlayerInformation(playerid, "Farmer Job", "Trebuie sa mergi cu acest vehicul timp de ~r~02:00 minute ~y~cu o viteza > de 25 km/h pentru a indeplini misiunea de recoltare.");
			if(engine == VEHICLE_PARAMS_OFF) {
				gettime(gHours, gMinutes, gSeconds);
				if(gHours >= 19 || gHours < 8)
					SetVehicleParamsEx(vID, VEHICLE_PARAMS_ON, VEHICLE_PARAMS_ON, alarm, doors, bonnet, boot, objective);
				else
					SetVehicleParamsEx(vID, VEHICLE_PARAMS_ON, VEHICLE_PARAMS_OFF, alarm, doors, bonnet, boot, objective);
				SendClientMessage(playerid, COLOR_GREY, "You have turned "VERDE"on "GRI3"the engine.");
			}
			else if(engine == VEHICLE_PARAMS_ON) {
				SetVehicleParamsEx(vID, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, alarm, doors, bonnet, boot, objective);
				SendClientMessage(playerid, COLOR_GREY, "You have turned "ROSU"off "GRI3"the engine.");
			}
		}
	}
	return true;
}

COMMAND:fill(playerid, params[]) {
	new
		string[MAXO_TEXT], vID = GetPlayerVehicleID(playerid), benzina, station, FillUp;
	if(vID != INVALID_VEHICLE_ID) {
		if(!IsVehicleBike(vID) && !IsVehicleBoat(vID) && !IsVehiclePlane(vID)) {
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				benzina = Gas[vID];
				if(benzina < 100) {
					station = GetBizSQLID(playerid, 7.0);
					if(BizInfo[station][bType] == BIZ_TYPE_BENZINARIE) {
						if(IsPlayerInRangeOfPoint(playerid, 7.0, BizInfo[station][bEntrancex], BizInfo[station][bEntrancey], BizInfo[station][bEntrancez])) {
							if(PlayerInfo[playerid][pCash] >= BizInfo[station][bEnterPrice]) {
								if(BizInfo[station][bProducts] > 0) {
									GameTextForPlayer(playerid, "~w~~n~~n~~n~~n~~n~~n~~n~~n~~n~Re-Fueling Vehicle, please wait", 2000, 3);
									TogglePlayerControllable(playerid, false);
									SetTimerEx("Fillup", 4000, false, "ddd", playerid, vID, station);
								} else GameTextForPlayer(playerid, "Out of stock!", 2500, 1);
							}
							else
							{
								format(string, MAXO_TEXT, "* Not enough Money to refill, it costs $%s to fill your Vehicle.", FormatNumber(FillUp, 0, '.'));
								SendClientMessage(playerid, COLOR_GRAD1, string);
								clear.string(string);
							}
						} else SendClientMessage(playerid, COLOR_GRAD1, "You must to be in near of gas station.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You are not at Gas Station.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You don't need to refill this vehicle.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You are not the vehicle driver.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You don't need to refill this vehicle.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You can't refill. You are on foot!");
	return true;
}

COMMAND:respawncars(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pAdmin]) {
		new
			bool: vehicululjuc[MAX_VEHICLES];
		for(new i = 0; i < MAX_PLAYERS; i ++) {
			if(GetPlayerVehicleID(i) != INVALID_VEHICLE_ID) {
				vehicululjuc[GetPlayerVehicleID(i)] = true;
			}
		}
		for(new v; v < MAX_VEHICLES; v++) {
			if(GetVehicleModel(v)) {
				if(!vehicululjuc[v])
					SetVehicleToRespawn(v);
			}
		}
		format(string, MAXO_TEXT, "AdmCmd: Admin %s has respawned all vehicles unoccupied.", PlayerName(playerid));
		OOCNews(COLOR_LIGHTRED, string);
		clear.string(string);
	} else NotAuthorized();
	return true;
}

COMMAND:rac(playerid, params[]) {
	return cmd_respawncars(playerid, params);
}
COMMAND:createvehicle(playerid, params[]) {
	new
		string[MAXO_TEXT2], vModel, Float:vPos[4], vColor[2], faction, type, rank, biz, job, vID;
	if(PlayerInfo[playerid][pAdmin] > 2) {
		if(!sscanf(params, "p<,>iffffiiiiiii", vModel, vPos[0], vPos[1], vPos[2], vPos[3], vColor[0], vColor[1], type, faction, rank, job, biz)) {
			if(ISBetween(vModel, 400, 612)) {
				if(ISBetween(rank, 0, 6)) {
					if(ISBetween(faction, FACT_CIVIL, MAX_FACTIONS)) {
						TotalVehicles ++;
						vID = CreateVehicle(vModel, vPos[0], vPos[1], vPos[2], vPos[3], vColor[0], vColor[1], DEFAULT_RESPAWN_TIME);
						CarInfo[vID][cSQLID] = TotalVehicles;
						CarInfo[vID][cModel] = vModel;
						CarInfo[vID][cLocation][0] = vPos[0];
						CarInfo[vID][cLocation][1] = vPos[1];
						CarInfo[vID][cLocation][2] = vPos[2];
						CarInfo[vID][cAngle] = vPos[3];
						CarInfo[vID][cColor][0] = vColor[0];
						CarInfo[vID][cColor][1] = vColor[1];
						CarInfo[vID][cRespawnTime] = DEFAULT_RESPAWN_TIME;
						CarInfo[vID][cHealth] = 1000.0;
						CarInfo[vID][cType] = type;
						CarInfo[vID][cFactionID] = faction;
						CarInfo[vID][cRank] = rank;
						CarInfo[vID][cBiz] = biz;
						CarInfo[vID][cJob] = job;
						CarInfo[vID][cEngine] = false;
						Gas[vID] = GasMax;
						StopCarRadio(vID);
						format(string, MAX_PLAYER_NAME, "eG %d %s", CarInfo[vID][cSQLID], NamePlateVehicle(CarInfo[vID][cFactionID]));
						SetVehicleNumberPlate(vID, string);
						SetVehicleToRespawn(vID);
						format(string, MAXO_TEXT2, "INSERT INTO `vehicles` (`Model`,`LocationX`,`LocationY`,`LocationZ`,`Angle`,`Color1`,`Color2`,`Type`,`Faction`,`Rank`,`Job`,`Biz`) VALUES ('%d','%f','%f','%f','%f','%d','%d','%d','%d','%d','%d','%d')", CarInfo[vID][cModel], CarInfo[vID][cLocation][0], CarInfo[vID][cLocation][1], CarInfo[vID][cLocation][2], CarInfo[vID][cAngle], CarInfo[vID][cColor][0], CarInfo[vID][cColor][1], CarInfo[vID][cType], CarInfo[vID][cFactionID], CarInfo[vID][cRank], CarInfo[vID][cJob], CarInfo[vID][cBiz]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", VEHICLE_THREAD_ID);
						SendClientMessage(playerid, COLOR_YELLOW, "[Vehicles] "ALB"Vehicul adaugat cu succes in baza de date.");
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid faction.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid rank.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid model.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/createvehicle [Model] [PosX] [PosY] [PosZ] [Angle] [Color1] [Color2] [Type] [Faction] [Rank] [JobID] [BizID]");
	} else NotAuthorized();
	return true;
}

COMMAND:repaircar(playerid) {
	new
		string[MAXO_TEXT],
		newcar = GetPlayerVehicleID(playerid);
	if(newcar != INVALID_VEHICLE_ID) {
		if(FACT_LSPD <= CarInfo[newcar][cFactionID] <= FACT_CRIPS) {
			if(CarInfo[newcar][cLastBroken] <= gLocalTimeStamp) {
				format(string, sizeof(string), "Are you sure? Repair cost is: $%s", FormatNumber(PlayerInfo[playerid][pLevel] * 500, 0, '.'));
				ShowPlayerDialog(playerid, DIALOGID_VEHICLE_REPAIR, DIALOG_STYLE_MSGBOX, "Vehicle Repair", string, "Yes", "No");
			} else SendClientMessage(playerid, COLOR_GREY, "Your vehicle is not broken !");
		} else SendClientMessage(playerid, COLOR_GREY, "You can't repair that vehicle type !");
	} else SendClientMessage(playerid, COLOR_GREY, "You are not inside a vehicle !");
	return true;
}

COMMAND:rentcar(playerid, params[]) {
	new vID = GetPlayerVehicleID(playerid), found;
	if(vID != INVALID_VEHICLE_ID) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			foreach(Player, i) {
				if(HireCar[i] == vID) {
					found = true;
					break;
				}
			}
			if(found) return SendClientMessage(playerid, COLOR_GRAD1, "This vehicle it's already rented by someone else.");
			new bizul, cartype, pretmasina;
			bizul = CarInfo[vID][cBiz];
			cartype = CarInfo[vID][cType];
			pretmasina = CarInfo[vID][cValue];
			if(BizInfo[bizul][bProducts] < 5)
				return GameTextForPlayer(playerid, "Out of stock!", 2500, 1);
			if(cartype == VEHICLE_TYPE_RENTCAR) {
				if(HireCar[playerid] == INVALID_PLAYER_ID) {
					if(PlayerInfo[playerid][pCash] > pretmasina) {
						new string[MAXO_TEXT];
						SafeGivePlayerMoney(playerid, -pretmasina);
						format(string, MAXO_TEXT1, "Rented by: %s", PlayerName(playerid));
						BizInfo[bizul][bTakings] += pretmasina;
						BizInfo[bizul][bProducts] -= 5;
						format(string, MAXO_TEXT2, "UPDATE bizz SET Takings = %d, Products = %d WHERE ID = %d", BizInfo[bizul][bTakings], BizInfo[bizul][bProducts], BizInfo[bizul][bSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
						format(string, MAX_PLAYER_NAME, "~r~-~g~$~y~%s", FormatNumber(pretmasina, 0, '.'));
						GameTextForPlayer(playerid, string, 2500, 1);
						HireCar[playerid] = vID;
						TogglePlayerControllable(playerid, true);
						PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
						for(new m; m < 2; m ++) {
							if(PlayerInfo[playerid][pDailyMission][m] == MISSION_RENTCAR)
								CheckMission(playerid, m);
						}
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have enough money to rent this vehicle.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You have already an vehicle rented.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "This vehicle isn't for rent, try to find another vehicle.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must be the driver to rent this vehicle.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in the vehicle for rent to rent it.");
	return true;
}

COMMAND:unrentcar(playerid, params[]) {
	new vID = GetPlayerVehicleID(playerid);
	if(!vID) {
		new carid = HireCar[playerid];
		if(carid != INVALID_PLAYER_ID && CarInfo[carid][cType] == VEHICLE_TYPE_RENTCAR) {
			GameTextForPlayer(playerid, "~w~You gave up the rented vehicle!", 3500, 4);
			HireCar[playerid] = INVALID_PLAYER_ID;
			SetVehicleToRespawn(carid);
			Update3DtextRentCar(carid);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have a rented vehicle.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command from a vehicle.");
	return true;
}

COMMAND:lock(playerid,params[]) {
	if(HireCar[playerid] == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, COLOR_GRAD1, "You don't have a Vehicle.");
	new carid;
	if(HireCar[playerid] != INVALID_PLAYER_ID) {
		carid = HireCar[playerid];
	}
	if(GetVehicleModel(carid) ==  407)
		return SendClientMessage(playerid, COLOR_GRAD1, "You are not allowed to lock a mission vehicle!");
	else
	{
		switch (CarInfo[carid][cLock]) {
			case 0: {
				if(HireCar[playerid] == INVALID_PLAYER_ID)
					return SendClientMessage(playerid, COLOR_GRAD2, "You don't have a Vehicle");
				else if(HireCar[playerid] == carid) {
					GameTextForPlayer(playerid, "~w~Hire Vehicle ~r~Locked", 5000, 6);
					PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
					LockCar(carid);
				}
			}
			case 1: {
				if(HireCar[playerid] == INVALID_PLAYER_ID)
					return SendClientMessage(playerid, COLOR_GRAD1, "You don't have a Vehicle");
				else if(HireCar[playerid] == carid) {
					GameTextForPlayer(playerid, "~w~Hire Vehicle ~g~Unlocked", 5000, 6);
					PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
					UnLockCar(carid);
				}
			}
			default: SendClientMessage(playerid, COLOR_GRAD1, "Error!");
		}
	}
	return 1;
}

stock IsAJOBVehicle(vID) {
	if(vID != INVALID_VEHICLE_ID) {
		switch(CarInfo[vID][cType]) {
			case VEHICLE_TYPE_FARMER_A, VEHICLE_TYPE_FARMER_B: return true;
			case VEHICLE_TYPE_SWEEPER, VEHICLE_TYPE_DUSTMAN: return true;
			case VEHICLE_TYPE_TRUCKER: return true;
		}
	}
	return false;
}

// End Of File ...
