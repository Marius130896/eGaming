/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_VehiclesSystemPriv_included
	#endinput
#else
	#define GF_VehiclesSystemPriv_included
#endif

const object_undamaged = 0;
const door_swinging = 1;
const door_damaged = 2;
const door_damaged_swinging = 3;
const door_fell_off = 4;

const windshield_crackedA = 1;
const windshield_crackedB = 2;
const windshielddestroyed = 3;

encode_lights(light1, light2, light3, light4) {
	return light1 | (light2 << 1) | (light3 << 2) | (light4 << 3);
}

#pragma unused encode_lights

encode_tires(tire1, tire2, tire3, tire4) {
	return tire1 | (tire2 << 1) | (tire3 << 2) | (tire4 << 3);
}

#pragma unused encode_tires

encode_tires_bike(rear, front) {
	return rear | (front << 1);
}

#pragma unused encode_tires_bike

encode_doors(Bonnet, Boot, driver_door, passenger_door, behind_driver_door, behind_passenger_door) {
	#pragma unused behind_driver_door
	#pragma unused behind_passenger_door
	return Bonnet | (Boot << 8) | (driver_door << 16) | (passenger_door << 24);
}

#pragma unused encode_doors

encode_panels(flp, frp, rlp, rrp, windshield, front_bumper, rear_bumper) {
	return flp | (frp << 4)  | (rlp << 8)  | (rrp << 12)  | (windshield << 16)  | (front_bumper << 20)  | (rear_bumper << 24);
}

#pragma unused encode_panels

breakcar(PlayerID) {
	if (GetPlayerVehicleID(PlayerID) != INVALID_VEHICLE_ID) {
		new panels, doors, lights, tires;
		GetVehicleDamageStatus(GetPlayerVehicleID(PlayerID), panels, doors, lights, tires);
		panels = encode_panels(1, 1, 1, 1, 3, 3, 3); // damage windshield & make bumpers swing
		doors = encode_doors(4, 4, 4, 4, 0, 0); // make them all fall off
		lights = encode_lights(1, 1, 1, 1);  // damage all lights
		tires = encode_tires(1, 1, 1, 1); // damage all tires
		UpdateVehicleDamageStatus(GetPlayerVehicleID(PlayerID), panels, doors, lights, tires);
	}
	return true;
}

#pragma unused breakcar

stock LoadVehicles() {
	mysql_tquery(connectionHandle, "SELECT * FROM vehicles", "LoadVehiclesThread", "d", VEHICLE_THREAD_ID);
	return true;
}

function LoadVehiclesThread() {
	rows = cache_num_rows();
	if(rows) {
		new
			VehicleModel, Float:VehiclePos[4], VehicleColor[2], VehicleRTime, vID, factiune;
		for(new r; r < rows; r ++) {
			VehicleModel = cache_get_row_int(r, 1);
			VehiclePos[0] = cache_get_row_float(r, 2);
			VehiclePos[1] = cache_get_row_float(r, 3);
			VehiclePos[2] = cache_get_row_float(r, 4);
			VehiclePos[3] = cache_get_row_float(r, 5);
			VehicleColor[0] = cache_get_row_int(r, 6);
			VehicleColor[1] = cache_get_row_int(r, 7);
			VehicleRTime = cache_get_row_int(r, 8);
			factiune = cache_get_row_int(r, 10);

			vID = CreateVehicle(VehicleModel, VehiclePos[0], VehiclePos[1], VehiclePos[2] + 0.25, VehiclePos[3], VehicleColor[0], VehicleColor[1], VehicleRTime);

			if(vID != INVALID_VEHICLE_ID) {
				TotalVehicles ++;
				CarInfo[vID][cSQLID] = cache_get_row_int(r, 0);
				CarInfo[vID][cModel] = VehicleModel;
				CarInfo[vID][cLocation][0] = VehiclePos[0];
				CarInfo[vID][cLocation][1] = VehiclePos[1];
				CarInfo[vID][cLocation][2] = VehiclePos[2];
				CarInfo[vID][cAngle] = VehiclePos[3];
				CarInfo[vID][cColor][0] = VehicleColor[0];
				CarInfo[vID][cColor][1] = VehicleColor[1];
				CarInfo[vID][cRespawnTime] = VehicleRTime;
				CarInfo[vID][cType] = cache_get_row_int(r, 9);
				CarInfo[vID][cFactionID] = factiune;
				CarInfo[vID][cRank] = cache_get_row_int(r, 11);
				CarInfo[vID][cBiz] = cache_get_row_int(r, 12);
				CarInfo[vID][cJob] = cache_get_row_int(r, 13);
				CarInfo[vID][cLastBroken] = cache_get_row_int(r, 14);
				CarInfo[vID][cValue] = cache_get_row_int(r, 15);
				CarInfo[vID][cHealth] = 1000.0;
				CarInfo[vID][cEngine] = false;

				SetVehicleForPlayers(vID);
			}
		}
		printf("LoadVehiclesThread() - called (%d vehicles loaded.", rows);
	}
	return true;
}

public OnVehicleMod(playerid, vehicleid, componentid) {
	if(GetPlayerInterior(playerid) == 0) {
		AntiCheat[playerid][eGACTunningHack] ++;
		if(AntiCheat[playerid][eGACTunningHack] > 1) {
			AntiCheat[playerid][eGACTunningHack] = 0;
			WarningPlayers(playerid, "Tunning Hacks");
		}
		return 0;
	}
	else
	{
		if(IsValidComponent(vehicleid, componentid)) return true;
	}
	return 1;
}

public OnEnterExitModShop(playerid, enterexit, interiorid) {
	new vID = GetPlayerVehicleID(playerid);
    if(enterexit == 0) {
        SendClientMessage(playerid, COLOR_WHITE, "*** Nice car! Be careful to do not broken it. ***");
		if(CarInfo[vID][cType] == VEHICLE_TYPE_PERSONAL)
			GetVehicleMods(playerid, vID);
	}
	else if(enterexit == 1)
		SendClientMessage(playerid, COLOR_WHITE, "*** You have entered in a Tuning Shop. ***");
    return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid) {
	if(gPlayerLogged{playerid}) {
		if(CarInfo[vehicleid][cType] == VEHICLE_TYPE_PERSONAL) {
			CarInfo[vehicleid][cPaintJob] = paintjobid;
			ChangeVehiclePaintjob(vehicleid, paintjobid);
			new string[MAXO_TEXT];
			format(string, MAXO_TEXT, "UPDATE vehicles_personal SET PaintJob = %d WHERE ID = %d", CarInfo[vehicleid][cPaintJob], CarInfo[vehicleid][cSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", TUNNING_THREAD_ID);
			clear.string(string);
		}
		else
		{
			CarInfo[vehicleid][cPaintJob] = paintjobid;
			ChangeVehiclePaintjob(vehicleid, paintjobid);
		}
	}
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2) {
	if(gPlayerLogged{playerid}) {
		if(CarInfo[vehicleid][cType] == VEHICLE_TYPE_PERSONAL) {
			if(CarInfo[vehicleid][cColor][0] != color1 || CarInfo[vehicleid][cColor][1] != color2) {
				CarInfo[vehicleid][cColor][0] = color1;
				CarInfo[vehicleid][cColor][1] = color2;
				ChangeVehicleColor(vehicleid, color1, color2);
				new string[MAXO_TEXT];
				format(string, MAXO_TEXT, "UPDATE vehicles_personal SET Color1 = %d, Color2 = %d WHERE ID = %d", CarInfo[vehicleid][cColor][0], CarInfo[vehicleid][cColor][1], CarInfo[vehicleid][cSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", TUNNING_THREAD_ID);
				clear.string(string);
			}
		}
	}
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

// End Of File ...
