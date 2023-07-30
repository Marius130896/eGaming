/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_JobsSystems_included
	#endinput
#else
	#define GF_JobsSystems_included
#endif

new
	Float:CreateTruckInParking[][4] = {
		{-30.5000000, -296.7999900, 6.6000000, 270.0000000},
		{-30.5000000, -283.5000000, 6.6000000, 270.0000000},
		{-30.6000000, -290.2999900, 6.6000000, 270.0000000},
		{-30.5000000, -276.6000100, 6.6000000, 270.0000000}
	};

enum pHaul {
	pCapasity,
	pLoad
};
new PlayerHaul[MAX_VEHICLES][pHaul];

new
	Float: FarmLocations[][3] = {
		{-545.6116,-1429.1364,12.7414},
		{-583.0197,-1341.5518,22.6998},
		{-563.3803,-1295.3439,24.4893},
		{-559.5171,-1346.5735,22.9873},
		{-537.2106,-1421.5797,13.5005},
		{-520.1445,-1363.8977,19.0357},
		{-523.7994,-1297.0476,24.0501},
		{-497.9665,-1319.9424,29.3788},
		{-492.0222,-1397.0448,19.2106},
		{-457.0275,-1402.6888,20.8737},
		{-432.5782,-1307.7629,34.4859},
		{-398.8360,-1283.8440,33.8939},
		{-390.0345,-1379.0331,24.3991},
		{-320.3821,-1319.7963,10.2744},
		{-206.4353,-1318.5729,9.6140},
		{-180.2255,-1355.6687,5.0364},
		{-251.0336,-1362.4474,10.3792},
		{-313.2203,-1371.3331,10.7818},
		{-185.0276,-1381.4071,5.5833},
		{-187.5405,-1411.6732,4.0716},
		{-323.9139,-1428.4928,16.0119},
		{-329.8000,-1471.6348,15.5602},
		{-282.6957,-1473.4106,6.6083},
		{-223.1787,-1480.3694,7.8898},
		{-224.3614,-1534.7686,7.8819},
		{-309.7311,-1555.8646,12.9518},
		{-284.0658,-1535.8844,7.7500},
		{-244.4505,-1508.0417,8.0117},
		{-328.3295,-1476.8176,15.2699}
	};

new Float:DustmanSFPoints[][3] = {
	{1147.5486,-1388.5276,13.8397},
	{1331.1040,-1235.9567,13.5469},
	{1786.6860,-1113.2426,24.0859},
	{1441.8835,-1326.7284,13.5459},
	{1459.2675,-1486.6141,13.5469},
	{952.2265,-1386.9473,13.3726},
	{1098.9457,-1878.4148,13.5469},
	{1427.2955,-1844.7407,13.5469},
	{794.1313,-845.1971,60.6415},
	{971.1773,-814.5321,97.4079},
	{857.2391,-1384.2224,13.8022},
	{873.3157,-1338.6449,13.5469},
	{995.4435,-1385.5741,13.2416},
	{-54.8734,-1578.8315,2.6107},
	{2176.6982,-1342.5160,23.9844},
	{2187.2537,-1258.8292,23.9459},
	{2428.2439,-1017.5159,54.3192},
	{2546.7703,-1037.4371,69.5839},
	{1918.3042,-2120.1367,13.5886},
	{436.9756,-1749.7410,9.0557},
	{946.1527,-699.2653,122.1987}
};

#define MAX_CP_ROUTE_ONE 19
new
	Float:LocationRouteOneSweeper[20][3] = {
		{-2482.6267, 1194.3904, 36.5291},
		{-2452.8735, 1320.2592, 13.3820},
		{-2476.0967, 1379.6038, 6.9140},
		{-2586.9138, 1349.5233, 6.9187},
		{-2706.9180, 1294.5745, 6.9216},
		{-2851.1218, 1240.1667, 5.3281},
		{-2883.9917, 1104.6748, 27.0778},
		{-2858.8965, 992.7953, 41.1523},
		{-2809.3569, 850.4709, 44.3946},
		{-2762.2520, 806.3781, 52.6803},
		{-2697.7695, 810.9900, 49.7031},
		{-2579.2993, 806.6002, 49.7013},
		{-2525.2122, 820.5112, 49.7032},
		{-2523.9702, 903.9000, 64.7109},
		{-2524.2864, 987.6098, 78.0377},
		{-2520.9817, 1084.6426, 55.4610},
		{-2580.0962, 1133.3585, 55.3320},
		{-2649.4182, 1187.9601, 55.3007},
		{-2604.8279, 1207.4379, 52.0089},
		{-2530.5837, 1185.2072, 42.0318}
	};

#define MAX_CP_ROUTE_TWO 22
new
	Float:LocationRouteTwoSweeper[23][3] = {
		{-2472.9163,1199.5109,34.9774},
		{-2453.5212,1248.1323,32.6915},
		{-2452.2527,1346.4811,6.6418},
		{-2393.1436,1373.4725,6.6359},
		{-2300.4351,1344.6979,6.6105},
		{-2209.0313,1328.1007,6.6125},
		{-2138.8877,1327.2906,6.6046},
		{-2058.9739,1305.3120,6.7348},
		{-2083.9714,1275.6841,12.6469},
		{-2190.0107,1276.0898,30.8761},
		{-2268.7407,1197.2169,54.4741},
		{-2266.5166,1088.4525,79.4242},
		{-2267.5244,947.0995,66.0655},
		{-2268.6213,872.0601,66.0657},
		{-2288.3650,808.1821,49.0240},
		{-2383.4019,944.0685,44.8626},
		{-2374.0466,1047.2577,55.1417},
		{-2397.8818,1109.6582,55.1437},
		{-2515.0420,1119.1823,55.1438},
		{-2606.5686,1145.7266,54.9959},
		{-2649.3708,1202.6469,54.9896},
		{-2592.4172,1203.8478,49.9727},
		{-2542.4961,1187.9520,43.0437}
	};
	
enum joInfo {
	joSQLID,
	joName[MAX_PLAYER_NAME],
	Float:joPos[3]
};
#define MAX_JOBS 8
new JobInfo[MAX_JOBS][joInfo];
new JobPickup;
#pragma unused JobPickup

stock LoadJobs() {
	mysql_tquery(connectionHandle, "SELECT * FROM jobs", "LoadJobsThread", "d", JOBS_THREAD_ID);
	return true;
}

function LoadJobsThread() {
	rows = cache_num_rows();
	if(rows) {
		for(new i = 0; i < rows; i ++) {
			JobInfo[i][joSQLID] = cache_get_row_int(i, 0);
			cache_get_row(i, 1, JobInfo[i][joName], .max_len = MAX_PLAYER_NAME);
			JobInfo[i][joPos][0] = cache_get_row_float(i, 2);
			JobInfo[i][joPos][1] = cache_get_row_float(i, 3);
			JobInfo[i][joPos][2] = cache_get_row_float(i, 4);
			#if defined _stream_pickups
				JobPickup = CreateDynamicPickup(1210, 2, JobInfo[i][joPos][0], JobInfo[i][joPos][1], JobInfo[i][joPos][2]);
			#else
				JobPickup = CreatePickup(1210, 2, JobInfo[i][joPos][0], JobInfo[i][joPos][1], JobInfo[i][joPos][2]);
			#endif
		}
		printf("LoadJobsThread() - called (%d jobs loaded).", rows);
	}
	return true;
}

new Float: LivreazaPachetul[15][3] = {
	{-2050.0674, 881.9077, 63.1752},
	{-2153.6917, 1231.5933, 33.9347},
	{-1945.4976, 799.4177, 55.7188},
	{-2571.1560, 321.7312, 10.5625},
	{-2740.7273, 130.1921, 4.5391},
	{918.9909, -1252.2506, 16.2109},
	{2611.8501, -1395.1960, 35.0646},
	{2491.2478, -2468.7578, 17.8828},
	{1576.0925, -1476.3011, 14.2213},
	{1242.4213, 371.8886, 19.5547},
	{1679.4277, 2359.5908, 10.8130},
	{2498.7097, 1149.2780, 22.0232},
	{1053.4034, 2148.3621, 10.8203},
	{-775.3300, 2764.7559, 48.2556},
	{-657.0605, 1456.2897, 13.7861}
};

stock GetJOBLocation(playerid, jobID) {
	new fLoc;
	switch(jobID) {
		case JOB_FARMER: {
			fLoc = random(sizeof(FarmLocations)-1);
			if(IsPlayerInRangeOfPoint(playerid, 6.0, FarmLocations[fLoc][0], FarmLocations[fLoc][1], FarmLocations[fLoc][2])) fLoc += 1;
		}
		case JOB_DUSTMAN: {
			fLoc = random(sizeof(DustmanSFPoints)-1);
			if(IsPlayerInRangeOfPoint(playerid, 6.0, DustmanSFPoints[fLoc][0], DustmanSFPoints[fLoc][1], DustmanSFPoints[fLoc][2])) fLoc += 1;
		}
		case JOB_ARMSDEALER: {
			fLoc = random(sizeof(LivreazaPachetul)-1);
			if(IsPlayerInRangeOfPoint(playerid, 3.0, LivreazaPachetul[fLoc][0], LivreazaPachetul[fLoc][1], LivreazaPachetul[fLoc][2])) fLoc += 1;
		}
	}
	return fLoc;
}

COMMAND:takevehicle(playerid, params[]) {
	new string[MAXO_TEXT];
	if(PlayerInfo[playerid][pDrivingLicense] > 1) {
		if(!GetPlayerVehicleID(playerid)) {
			if(!PlayerInfo[playerid][pTakeVehiclePause]) {
				new vID = INVALID_VEHICLE_ID;
				if(PlayerInfo[playerid][pJob] == JOB_FARMER) {
					if(IsPlayerInRangeOfPoint(playerid, 3.0, -401.7422,-1419.6466,26.2417)) {
						vID = CreateVehicle(532, -377.3339, -1418.8485, 26.7084, 355.2869, -1, -1, 300);
						if(vID != INVALID_VEHICLE_ID) {
							CarInfo[vID][cModel] = 532;
							CarInfo[vID][cType] = VEHICLE_TYPE_FARMER_A;
						} else SendClientMessage(playerid, COLOR_GRAD1, "The vehicle cannot be created, report on forum.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You are not at farm to use this command.");
				}
				else if(PlayerInfo[playerid][pJob] == JOB_SWEEPER) {
					if(IsPlayerInRangeOfPoint(playerid, 3.0, -2542.7722, 1216.2623, 37.4392)) {
						vID = CreateVehicle(574, -2512.1462, 1209.6335, 36.9938, 269.3760, -1, -1, 300);
						if(vID != INVALID_VEHICLE_ID) {
							CarInfo[vID][cModel] = 574;
							CarInfo[vID][cType] = VEHICLE_TYPE_SWEEPER;
						} else SendClientMessage(playerid, COLOR_GRAD1, "The vehicle cannot be created, report on forum.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You are not in base to use this command.");
				}
				else if(PlayerInfo[playerid][pJob] == JOB_DUSTMAN) {
					if(IsPlayerInRangeOfPoint(playerid, 3.0, 1616.0367, -1897.2677, 13.5491)) {
						vID = CreateVehicle(408, 1621.0250, -1887.6735, 13.2721, 357.6123, 26, 26, 300);
						if(vID != INVALID_VEHICLE_ID) {
							CarInfo[vID][cModel] = 408;
							CarInfo[vID][cType] = VEHICLE_TYPE_DUSTMAN;
							dustvehicle[playerid] = vID;
						} else SendClientMessage(playerid, COLOR_GRAD1, "The vehicle cannot be created, report on forum.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You are not in base to use this command.");
				}
				else if(PlayerInfo[playerid][pJob] == JOB_TRUCKER) {
					if(IsPlayerInRangeOfPoint(playerid, 3.0, -19.0057, -269.7075, 5.4297)) {
						new tplace = RandomEx(0, 4);
						vID = CreateVehicle(456, CreateTruckInParking[tplace][0], CreateTruckInParking[tplace][1], CreateTruckInParking[tplace][2], CreateTruckInParking[tplace][3], 96, 26, 300);
						if(vID != INVALID_VEHICLE_ID) {
							CarInfo[vID][cModel] = 456;
							CarInfo[vID][cType] = VEHICLE_TYPE_TRUCKER;
							PlayerHaul[vID][pCapasity] = 100;
							PlayerHaul[vID][pLoad] = 100;
						}
					} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't in the base to use this command.");
				}
				if(vID != INVALID_VEHICLE_ID) {
					gLastDriver[vID] = playerid;
					CarInfo[vID][cRespawnTime] = 300;
					CarInfo[vID][cHealth] = 1000.0;
					CarInfo[vID][cValue] = 0;
					CarInfo[vID][cFactionID] = FACT_CIVIL;
					CarInfo[vID][cRank] = 0;
					CarInfo[vID][cBiz] = 0;
					CarInfo[vID][cLastBroken] = gLocalTimeStamp+86400;
					CarInfo[vID][cEngine] = false;
					CarInfo[vID][cLock] = 0;
					new engine, lights, alarm, doors, bonnet, boot, objective;
    				DisableRemoteVehicleCollisions(playerid, true);
					GetVehicleParamsEx(vID, engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(vID, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
					Gas[vID] = GasMax;
					StopCarRadio(vID);
					PutPlayerInVehicle(playerid, vID, 0);
					PlayerInfo[playerid][pTakeVehiclePause] = 180;
				}
			} else format(string, MAXO_TEXT, "You must to wait %s to use again this command.", ConvertTime(PlayerInfo[playerid][pTakeVehiclePause])), SendClientMessage(playerid, COLOR_GRAD1, string);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot to use this command from an vehicle.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have a driving license validate.");
	clear.string(string);
	return true;
}

#define FARMING_TIME 2*60
COMMAND:startfarm(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] == JOB_FARMER) {
		if(CarInfo[GetPlayerVehicleID(playerid)][cType] == VEHICLE_TYPE_FARMER_A) {
			if(IsPlayerInRangeOfPoint(playerid, 10.0, -377.3339, -1418.8485, 26.7084)) {
				if(PlayerInfo[playerid][pFarmingTime] == 0) {
					if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
						PlayerInfo[playerid][pFarmingTime] = FARMING_TIME;
					} else SendClientMessage(playerid, COLOR_GRAD1, "To start the work, you must be in an vehicle as driver.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You are already at work, you can no longer use this command.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't in the location where the command can be used.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "This type of vehicle isn't for the job of Farmer.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't farmer to use this command.");
	return true;
}

COMMAND:stopfarm(playerid, params[]) {
	new vID = GetPlayerVehicleID(playerid);
	if(PlayerInfo[playerid][pJob] == JOB_FARMER) {
		if(CarInfo[vID][cType] == VEHICLE_TYPE_FARMER_A) {
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				if(PlayerInfo[playerid][pFarmingTime]) {
					PlayerInfo[playerid][pFarmingTime] = 0;
					HidePlayerInformation(playerid);
					FarmCantitate[playerid] = 0;
					SetVehicleToRespawn(vID);
					SendClientMessage(playerid, COLOR_ORANGE, "INFO: Pentru ca ai oprit cultivarea graului, nu ai fost rasplatit de catre fermier.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "In this moment, you not work, use startfarm.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must be the driver if you want to stop the work.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "To stop the wotk, you must be in combine.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You haven't the Farmer job.");
	return true;
}

COMMAND:sellbag(playerid, params[]) {
	new string[MAXO_TEXT];
	if(PlayerInfo[playerid][pJob] == JOB_FARMER) {
		if(FarmCantitate[playerid]) {
			if(IsPlayerInRangeOfPoint(playerid, 3.0, -87.9676, -29.1070, 3.1172)) {
				PlayerInfo[playerid][pFarmerSkill] ++;
				format(string, MAXO_TEXT, "UPDATE players SET FarmerSkill = %d WHERE ID = %d", PlayerInfo[playerid][pFarmerSkill], PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				FarmCantitateHambar += 50;
				FarmCantitate[playerid] = 0;
				new Rand;
				switch(PlayerInfo[playerid][pFarmerSkill]) {
					case 0..48: Rand = RandomEx(1200, 1300), SafeGivePlayerMoney(playerid, Rand);
					case 49..144: Rand = RandomEx(1420, 1500), SafeGivePlayerMoney(playerid, Rand);
					case 145..336: Rand = RandomEx(1620, 1700), SafeGivePlayerMoney(playerid, Rand);
					case 337..720: Rand = RandomEx(1840, 1910), SafeGivePlayerMoney(playerid, Rand);
					default: Rand = RandomEx(2050, 2110), SafeGivePlayerMoney(playerid, Rand);
				}
				format(string, MAXO_TEXT, "INFO: Ai primit $%s pentru graul vandut catre acest fermier.", FormatNumber(Rand, 0, '.'));
				SendClientMessage(playerid, COLOR_ORANGE, string);
				format(string, MAX_PLAYER_NAME, "~r~+~g~$%s", FormatNumber(Rand, 0, '.'));
				GameTextForPlayer(playerid, string, 4000, 3);
				switch(PlayerInfo[playerid][pFarmerSkill]) {
					case 48: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations! Your Farmer Skill is now Level 2.");
					case 144: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations! Your Farmer Skill is now Level 3.");
					case 336: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations! Your Farmer Skill is now Level 4.");
					case 720: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations! Your Farmer Skill is now Level 5.");
				}
			}
			else
			{
				if(!HaveVisibleCheckpoint(playerid))
					CreateCP(playerid,-87.9676,-29.1070,3.1172,3.0,checkpointNoAction,CP_NO_ACTION);
			}
		} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have a bag to sell.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You haven't the Farmer job.");
	clear.string(string);
	return true;
}

COMMAND:takeflour(playerid, params[]) {
	new string[MAXO_TEXT], vID = GetPlayerVehicleID(playerid);
	if(PlayerInfo[playerid][pJob] == JOB_FARMER) {
		if(IsPlayerInRangeOfPoint(playerid, 3.0, -87.9676, -29.1070, 3.1172)) {
			if(FarmCantitateHambar != 0) {
				if(FarmCantitateFaina[playerid] != 50) {
					if(PlayerInfo[playerid][pFarmerSkill] >= 336) {
						if(CarInfo[vID][cType] != VEHICLE_TYPE_FARMER_B)
							return SendClientMessage(playerid, COLOR_GRAD1, "You must be in the flour transport vehicle (Bobcat).");
						new vehicleID = INVALID_VEHICLE_ID;

						vehicleID = CreateVehicle(422, -88.2210, -11.5813, 3.0983, 247.6880, -1, -1, 15);

						if(vehicleID != INVALID_VEHICLE_ID) {
							CarInfo[vehicleID][cModel] = 422;
							CarInfo[vehicleID][cType] = VEHICLE_TYPE_FARMER_B;
							gLastDriver[vehicleID] = playerid;
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
							PutPlayerInVehicle(playerid, vehicleID, 0);
						}
						FarmCantitateHambar -= 50;
						FarmCantitateFaina[playerid] = 50;
						format(string, MAXO_TEXT, "INFO: Ai luat un sac de faina de 50 kg, au mai ramas %d kg disponibile.", FarmCantitateHambar);
						SendClientMessage(playerid, COLOR_ORANGE, string);
						if(!HaveVisibleCheckpoint(playerid)) {
							CreateCP(playerid,1520.2157,1066.9105,10.8203,3.0,checkpointNoAction,CP_NO_ACTION);
							SendClientMessage(playerid, COLOR_ORANGE, "INFO: Mergi la checkpointul rosu, marcat pe minimap pentru a vinde faina.");
							SendClientMessage(playerid, COLOR_ORANGE, "INFO: Odata ajuns la acel checkpoint, foloseste comanda /sellflour.");
						}
					} else SendClientMessage(playerid, COLOR_GRAD1, "You need of Skill Level 3+ for this action.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You has took already a bag of flour, can't to take anymore another one.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "In the barn isn't flour anymore.");
		}
		else
		{
			if(!HaveVisibleCheckpoint(playerid)) {
				CreateCP(playerid,-87.9676,-29.1070,3.1172,3.0,checkpointNoAction,CP_NO_ACTION);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "You must be in the red checkpoint to use this command.");
			}
		}
	} else SendClientMessage(playerid, COLOR_GRAD1, "You haven't the job of farmer, to use this action.");
	clear.string(string);
	return true;
}

COMMAND:sellflour(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] == JOB_FARMER) {
		if(IsPlayerInRangeOfPoint(playerid, 3.0, 1520.2157,1066.9105,10.8203)) {
			if(FarmCantitateFaina[playerid] == 50) {
				new Rand, string[MAXO_TEXT];
				switch(PlayerInfo[playerid][pFarmerSkill]) {
					case 145..336: Rand = RandomEx(1100, 1200), SafeGivePlayerMoney(playerid, Rand);
					case 337..720: Rand = RandomEx(1200, 1300), SafeGivePlayerMoney(playerid, Rand);
					default: Rand = RandomEx(1300, 1400), SafeGivePlayerMoney(playerid, Rand);
				}
				format(string, MAXO_TEXT, "INFO: Ai primit $%s pentru sacul de faina vandut pe care l-ai luat din hambar.", FormatNumber(Rand, 0, '.'));
				SendClientMessage(playerid, COLOR_ORANGE, string);
				format(string, MAX_PLAYER_NAME, "~r~+~g~$%s", FormatNumber(Rand, 0, '.'));
				GameTextForPlayer(playerid, string, 4000, 3);
				FarmCantitateFaina[playerid] = 0;
				for(new m; m < 2; m ++) {
					if(PlayerInfo[playerid][pDailyMission][m] == MISSION_SELLFLOUR)
						CheckMission(playerid, m);
				}
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command, because you not took a bag with flour.");
		}
		else
		{
			if(!HaveVisibleCheckpoint(playerid)) {
				CreateCP(playerid,1520.2157,1066.9105,10.8203,3.0,checkpointNoAction,CP_NO_ACTION);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "You must be in the red checkpoint to use this command.");
			}
		}
	} else SendClientMessage(playerid, COLOR_GRAD1, "You haven't the job of farmer, to use this action.");
	return true;
}

stock GetVehicleSpeed(vehicleid) {
	new
		Float:Pos[3];
	GetVehicleVelocity(vehicleid, Pos[0], Pos[1], Pos[2]);
	Pos[0] *= 170;
	Pos[1] *= 170;
	Pos[2] *= 170;
	return floatround(VectorSize(Pos[0], Pos[1], Pos[2]));
}

function ExitJOBVehicle(playerid, vID) {
	if(vID != INVALID_VEHICLE_ID) {
		if(GetPlayerVehicleID(playerid) != vID) {
			switch(CarInfo[vID][cType]) {
				case VEHICLE_TYPE_FARMER_A, VEHICLE_TYPE_FARMER_B: {
					if(checkpointFarmer[playerid] != INVALID_CHECKPOINT_ID) {
						DeleteCP(checkpointFarmer, playerid);
						HidePlayerInformation(playerid);
						PlayerInfo[playerid][pFarmingTime] = 0;
					}
				}
				case VEHICLE_TYPE_SWEEPER: {
					if(checkpointSweeper[playerid] != INVALID_CHECKPOINT_ID) {
						DeleteCP(checkpointSweeper, playerid);
						if(PlayerInfo[playerid][pCPSweeper] != -1)
							PlayerInfo[playerid][pCPSweeper] = -1;
						if(PlayerInfo[playerid][pCPSweeper2] != -1)
							PlayerInfo[playerid][pCPSweeper] = -1;
					}
				}
				case VEHICLE_TYPE_DUSTMAN: {
					if(checkpointDustman[playerid] != INVALID_CHECKPOINT_ID) {
						DeleteCP(checkpointDustman, playerid);
					}
				}
				case VEHICLE_TYPE_TRUCKER: {
					SetVehicleToRespawn(vID);
				}
			}
			SetVehicleToRespawn(vID);
			SendClientMessage(playerid, COLOR_ORANGE, "INFO: Because you didn't come back fast in your vehicle, this has been respawned.");
		}
	}
	JOBVehicleTimer[playerid] = INVALID_VJOB_TIMER;
	return true;
}

stock JobAwards(playerid) {
	new
		award = 0;
	switch(PlayerInfo[playerid][pJob]) {
		case JOB_FARMER: {
			switch(PlayerInfo[playerid][pFarmerSkill]) {
				case 0..50: 	award = 4;
				case 51..150: 	award = 6;
				case 151..300: 	award = 8;
				case 301..500: 	award = 10;
				default:		award = 12;
			}
		}
		case JOB_DUSTMAN: {
			switch(PlayerInfo[playerid][pDustSkill]) {
				case 0..50:     award = 4;
				case 51..150:   award = 6;
				case 151..300:  award = 8;
				case 301..500:  award = 10;
				default:		award = 12;
			}
		}
		case JOB_CARJACKER: {
			switch(PlayerInfo[playerid][pCarJackerSkill]) {
				case 0..50:     award = 4;
				case 51..150:   award = 6;
				case 151..300:  award = 8;
				case 301..500:  award = 10;
				default:		award = 12;
			}
		}
	}
	return award;
}

COMMAND:startsweep(playerid, params[]) {
	new tmasina = GetPlayerVehicleID(playerid);
	if(PlayerInfo[playerid][pJob] == JOB_SWEEPER) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			if(!HaveVisibleCheckpoint(playerid)) {
				if(CarInfo[tmasina][cType] == VEHICLE_TYPE_SWEEPER) {
					if(IsPlayerInRangeOfPoint(playerid, 10.0, -2512.1462, 1209.6335, 36.9938))
						ShowPlayerDialog(playerid, DIALOGID_SELECT_ROUTE, DIALOG_STYLE_MSGBOX, "Sweeper route", "Choose the route of sweeping:", "Route 1", "Route 2");
					else
						SendClientMessage(playerid, COLOR_GRAD1, "You must be in base to use this command.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in the vehicle of job to use this command.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You can't to use this command, because you have an checkpoint active.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must be the driver, to use this command.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have the job Sweeper to use this command.");
	return true;
}

COMMAND:stopsweep(playerid, params[]) {
	new vID = GetPlayerVehicleID(playerid);
	if(PlayerInfo[playerid][pJob] == JOB_SWEEPER) {
		DeleteCP(checkpointSweeper, playerid);
		if(CarInfo[vID][cType] == VEHICLE_TYPE_SWEEPER)
			SetVehicleToRespawn(vID);
		if(PlayerInfo[playerid][pCPSweeper] != -1)
			PlayerInfo[playerid][pCPSweeper] = -1;
		if(PlayerInfo[playerid][pCPSweeper2] != -1)
			PlayerInfo[playerid][pCPSweeper] = -1;
		else
			SendClientMessage(playerid, COLOR_GRAD1, "You must be in the vehicle of job to use this command.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have the job Sweeper to use this command.");
	return true;
}

COMMAND:startcollect(playerid, params[]) {
	if(PlayerInfo[playerid][pJob] == JOB_DUSTMAN) {
		new vID = GetPlayerVehicleID(playerid);
		if(CarInfo[vID][cType] == VEHICLE_TYPE_DUSTMAN && GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			#if defined _stream_checkpoints
			if(IsValidDynamicCP(checkpointDustman[playerid]))
			#else
			if(CPid[playerid] == CP_DUSTMAN)
			#endif
				return SendClientMessage(playerid, COLOR_GRAD1, "You already collect the garbage, the command, cannot be used anymore.");
			new dLoc = GetJOBLocation(playerid, JOB_DUSTMAN);
			CreateCP(playerid,DustmanSFPoints[dLoc][0],DustmanSFPoints[dLoc][1],DustmanSFPoints[dLoc][2],6.0,checkpointDustman,CP_DUSTMAN);
			SendClientMessage(playerid, COLOR_ORANGE, "INFO: Follow the checkpoint from minimap to collect the trash.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "When using this command, you must be the driver of a trash car.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have the job of Dustman.");
	return true;
}

COMMAND:stopcollect(playerid, params[]) {
	new tmasina = GetPlayerVehicleID(playerid);
	if(PlayerInfo[playerid][pJob] == JOB_DUSTMAN) {
		if(CarInfo[tmasina][cType] == VEHICLE_TYPE_DUSTMAN) {
			#if defined _stream_checkpoints
			if(IsValidDynamicCP(checkpointDustman[playerid]))
			#else
			if(CPid[playerid] == CP_DUSTMAN)
			#endif
			{
				DeleteCP(checkpointDustman, playerid);
				TogglePlayerControllable(playerid, true);
				SetVehicleToRespawn(tmasina);
			} else SendClientMessage(playerid, COLOR_GRAD1, "You not work in this momment.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in the vehicle of service to use this command.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You hane't the job Dustman to use this command.");
	return true;
}

COMMAND:quitjob(playerid, params[]) {
	if(PlayerInfo[playerid][pJob]) {
		if(!GetPlayerVehicleID(playerid)) {
			PlayerInfo[playerid][pJob] = JOB_NONE;
			new string[MAXO_TEXT];
			format(string, MAXO_TEXT, "UPDATE players SET Job = %d WHERE ID = %d", PlayerInfo[playerid][pJob], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* {FFFFFF}Now, you don't have any job. Can to go to get engaged.");
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You can't to use this command from an vehicle.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have any job, can't to use this command.");
	return true;
}

function UploadTrash(playerid) {
	new string[MAXO_TEXT], dLoc, Rand;
	PlayerInfo[playerid][pDustSkill] ++;
	switch(PlayerInfo[playerid][pDustSkill]) {
		case 201:  SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations, Your Dustman Skill, is now Level 2.");
		case 601: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations, Your Dustman Skill, is now Level 3.");
		case 1401: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations, Your Dustman Skill, is now Level 4.");
		case 3001: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations, Your Dustman Skill, is now Level 5.");
	}
	switch(PlayerInfo[playerid][pDustSkill]) {
		case 0..200: Rand = RandomEx(275, 325), SafeGivePlayerMoney(playerid, Rand);
		case 201..600: Rand = RandomEx(325, 375), SafeGivePlayerMoney(playerid, Rand);
		case 601..1400: Rand = RandomEx(375, 425), SafeGivePlayerMoney(playerid, Rand);
		case 1401..3000: Rand = RandomEx(425, 475), SafeGivePlayerMoney(playerid, Rand);
		default: Rand = RandomEx(475, 525), SafeGivePlayerMoney(playerid, Rand);
	}
	format(string, MAXO_TEXT, "UPDATE players SET DustSkill = %d WHERE ID = %d", PlayerInfo[playerid][pDustSkill], PlayerInfo[playerid][pSQLID]);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	DeleteCP(checkpointDustman, playerid);
	dLoc = GetJOBLocation(playerid, JOB_DUSTMAN);
	CreateCP(playerid,DustmanSFPoints[dLoc][0],DustmanSFPoints[dLoc][1],DustmanSFPoints[dLoc][2],6.0,checkpointDustman,CP_DUSTMAN);
	format(string, MAXO_TEXT, "INFO: You received $%s for this container collected.", FormatNumber(Rand, 0, '.'));
	SendClientMessage(playerid, COLOR_ORANGE, string);
	SendClientMessage(playerid, COLOR_ORANGE, "INFO: Go at the next checkpoint to collect the trash.");
	TogglePlayerControllable(playerid, true);
	clear.string(string);
	return true;
}

COMMAND:dropcar(playerid, params[]) {
	new string[MAXO_TEXT];
	if(PlayerInfo[playerid][pJob] == JOB_CARJACKER) {
		if(IsPlayerInAnyVehicle(playerid)) {
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				if(!PlayerInfo[playerid][pCarTime]) {
					GameTextForPlayer(playerid, "~w~Car Selling ~n~~r~Drop the car at the Crane", 5000, 1);
					CreateCP(playerid,-1548.3618,123.6438,3.2966,6.0,checkpointCarJacker,CP_CARJACKER);
				} else format(string, MAXO_TEXT, "You must to wait %s untill when you'll can to use again this command.", ConvertTime(PlayerInfo[playerid][pCarTime])), SendClientMessage(playerid, COLOR_GRAD1, string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must to be the driver as to use this command.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must to be in an vehicle to use this command.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have the job of Car Jacker.");
	clear.string(string);
	return true;
}

COMMAND:buymats(playerid, params[]) {
	new string[MAXO_TEXT], LocRandom = RandomEx(1, 15);
	if(PlayerInfo[playerid][pJob] == JOB_ARMSDEALER) {
		if(IsPlayerInRangeOfPoint(playerid, 3.0, 2770.7, -1628.1, 12.1775)) {
			gettime(gHours, gMinutes, gSeconds);
			if(gHours >= 12 || gHours <= 23) {
				switch(PlayerInfo[playerid][pArmsDealerSkill]) {
					case 0..50: {
						if(PlayerInfo[playerid][pCash] < 5000)
							return SendClientMessage(playerid, COLOR_GRAD1, "You need $5.000 to buy un package of materials.");
						if(JucatorulAreMateriale[playerid] > 0)
							return SendClientMessage(playerid, COLOR_GRAD1, "You have already a package of materials, you can't buy another one.");
						JucatorulAreMateriale[playerid] = 5000;
						SafeGivePlayerMoney(playerid, -5000);
						CreateCP(playerid,LivreazaPachetul[LocRandom][0],LivreazaPachetul[LocRandom][1],LivreazaPachetul[LocRandom][2],6.0,checkpointNoAction,CP_NO_ACTION);
						LocatiaRandom{playerid} = LocRandom;
						format(string, MAXO_TEXT, "* You took one package of %s materials at price of $5.000.", FormatNumber(JucatorulAreMateriale[playerid], 0, '.'));
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* To deliver the package type: /delivermats");
					}
					case 51..150: {
						if(PlayerInfo[playerid][pCash] < 10000)
							return SendClientMessage(playerid, COLOR_GRAD1, "You need $10.000 to buy un package of materials.");
						if(JucatorulAreMateriale[playerid] > 0)
							return SendClientMessage(playerid, COLOR_GRAD1, "You have already a package of materials, you can't buy another one.");
						JucatorulAreMateriale[playerid] = 10000;
						SafeGivePlayerMoney(playerid, -10000);
						CreateCP(playerid,LivreazaPachetul[LocRandom][0],LivreazaPachetul[LocRandom][1],LivreazaPachetul[LocRandom][2],6.0,checkpointNoAction,CP_NO_ACTION);
						LocatiaRandom{playerid} = LocRandom;
						format(string, MAXO_TEXT, "* You took one package of %s materials at price of $10.000.", FormatNumber(JucatorulAreMateriale[playerid], 0, '.'));
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* To deliver the package type: /delivermats");
					}
					case 151..246: {
						if(PlayerInfo[playerid][pCash] < 15000)
							return SendClientMessage(playerid, COLOR_GRAD1, "You need $15.000 to buy un package of materials.");
						if(JucatorulAreMateriale[playerid] > 0)
							return SendClientMessage(playerid, COLOR_GRAD1, "You have already a package of materials, you can't buy another one.");
						JucatorulAreMateriale[playerid] = 15000;
						SafeGivePlayerMoney(playerid, -15000);
						PlayerInfo[playerid][pWlvl] += 1;
						SetPlayerWanted(playerid, INVALID_PLAYER_ID, PlayerInfo[playerid][pWlvl]);
						CreateCP(playerid,LivreazaPachetul[LocRandom][0],LivreazaPachetul[LocRandom][1],LivreazaPachetul[LocRandom][2],6.0,checkpointNoAction,CP_NO_ACTION);
						LocatiaRandom{playerid} = LocRandom;
						format(string, MAXO_TEXT, "* You took one package of %s materials at price of $15.000.", FormatNumber(JucatorulAreMateriale[playerid], 0, '.'));
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* To deliver the package type: /delivermats");
					}
					case 247..438: {
						if(PlayerInfo[playerid][pCash] < 25000)
							return SendClientMessage(playerid, COLOR_GRAD1, "You need $25.000 to buy un package of materials.");
						if(JucatorulAreMateriale[playerid] > 0)
							return SendClientMessage(playerid, COLOR_GRAD1, "You have already a package of materials, you can't buy another one.");
						JucatorulAreMateriale[playerid] = 50000;
						SafeGivePlayerMoney(playerid, -25000);
						PlayerInfo[playerid][pWlvl] += 1;
						SetPlayerWanted(playerid, INVALID_PLAYER_ID, PlayerInfo[playerid][pWlvl]);
						CreateCP(playerid,LivreazaPachetul[LocRandom][0],LivreazaPachetul[LocRandom][1],LivreazaPachetul[LocRandom][2],6.0,checkpointNoAction,CP_NO_ACTION);
						LocatiaRandom{playerid} = LocRandom;
						format(string, MAXO_TEXT, "* You took one package of %s materials at price of $25.000.", FormatNumber(JucatorulAreMateriale[playerid], 0, '.'));
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* To deliver the package type: /delivermats");
					}
					default: {
						if(PlayerInfo[playerid][pCash] < 50000)
							return SendClientMessage(playerid, COLOR_GRAD1, "You need $50.000 to buy un package of materials.");
						if(JucatorulAreMateriale[playerid] > 0)
							return SendClientMessage(playerid, COLOR_GRAD1, "You have already a package of materials, you can't buy another one.");
						JucatorulAreMateriale[playerid] = 100000;
						SafeGivePlayerMoney(playerid, -50000);
						PlayerInfo[playerid][pWlvl] += 3;
						SetPlayerWanted(playerid, INVALID_PLAYER_ID, PlayerInfo[playerid][pWlvl]);
						CreateCP(playerid,LivreazaPachetul[LocRandom][0],LivreazaPachetul[LocRandom][1],LivreazaPachetul[LocRandom][2],6.0,checkpointNoAction,CP_NO_ACTION);
						LocatiaRandom{playerid} = LocRandom;
						format(string, MAXO_TEXT, "* You took one package of %s materials at price of $50.000.", FormatNumber(JucatorulAreMateriale[playerid], 0, '.'));
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* To deliver the package type: /delivermats");
					}
				}
			} else SendClientMessage(playerid, COLOR_GRAD1, "You can to take one package of materials between 12:00-00:00.");
		}
		else
		{
			SendClientMessage(playerid, COLOR_GRAD1, "You aren't in front of the deposit to take one package of materials.");
			if(!HaveVisibleCheckpoint(playerid))
				CreateCP(playerid,2770.7, -1628.1, 12.1775,3.0,checkpointNoAction,CP_NO_ACTION);
		}
	} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't a dealer of guns.");
	clear.string(string);
	return true;
}

stock IsPlayerAtDepositOfMaterials(playerid) {
	switch(LocatiaRandom{playerid}) {
		case 1: if(IsPlayerInRangeOfPoint(playerid, 3.0, -2153.6917, 1231.5933, 33.9347)) return true;
		case 2: if(IsPlayerInRangeOfPoint(playerid, 3.0, -1945.4976, 799.4177, 55.7188)) return true;
		case 3: if(IsPlayerInRangeOfPoint(playerid, 3.0, -2571.1560, 321.7312, 10.5625)) return true;
		case 4: if(IsPlayerInRangeOfPoint(playerid, 3.0, -2740.7273, 130.1921, 4.5391)) return true;
		case 5: if(IsPlayerInRangeOfPoint(playerid, 3.0, 918.9909, -1252.2506, 16.2109)) return true;
		case 6: if(IsPlayerInRangeOfPoint(playerid, 3.0, 2611.8501, -1395.1960, 35.0646)) return true;
		case 7: if(IsPlayerInRangeOfPoint(playerid, 3.0, 2491.2478, -2468.7578, 17.8828)) return true;
		case 8: if(IsPlayerInRangeOfPoint(playerid, 3.0, 1576.0925, -1476.3011, 14.2213)) return true;
		case 9: if(IsPlayerInRangeOfPoint(playerid, 3.0, 1242.4213, 371.8886, 19.5547)) return true;
		case 10: if(IsPlayerInRangeOfPoint(playerid, 3.0, 1679.4277, 2359.5908, 10.8130)) return true;
		case 11: if(IsPlayerInRangeOfPoint(playerid, 3.0, 2498.7097, 1149.2780, 22.0232)) return true;
		case 12: if(IsPlayerInRangeOfPoint(playerid, 3.0, 1053.4034, 2148.3621, 10.8203)) return true;
		case 13: if(IsPlayerInRangeOfPoint(playerid, 3.0, -775.3300, 2764.7559, 48.2556)) return true;
		case 14: if(IsPlayerInRangeOfPoint(playerid, 3.0, -657.0605, 1456.2897, 13.7861)) return true;
		case 15: if(IsPlayerInRangeOfPoint(playerid, 3.0, -2050.0674, 881.9077, 63.1752)) return true;
	}
	return false;
}

COMMAND:delivermats(playerid, params[]) {
	new string[MAXO_TEXT2];
	if(PlayerInfo[playerid][pJob] == JOB_ARMSDEALER) {
		if(JucatorulAreMateriale[playerid] > 0) {
			if(IsPlayerAtDepositOfMaterials(playerid)) {
				switch(PlayerInfo[playerid][pArmsDealerSkill]) {
					case 0..50: SafeGivePlayerMoney(playerid, 6250), SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You received $6.250 for this delivery.");
					case 51..150: SafeGivePlayerMoney(playerid, 11475), SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You received $11.475 for this delivery.");
					case 151..246: SafeGivePlayerMoney(playerid, 18500), SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You received $18.500 for this delivery.");
					case 247..438: SafeGivePlayerMoney(playerid, 28750), SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You received $28.750 for this delivery.");
					default: SafeGivePlayerMoney(playerid, 70000), PlayerInfo[playerid][pMats] = 5000, SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You received $70.000 and 5.000 materials for this delivery.");
				}
				JucatorulAreMateriale[playerid] = 0;
				LocatiaRandom{playerid} = 0;
				PlayerInfo[playerid][pArmsDealerSkill] ++;
				switch(PlayerInfo[playerid][pArmsDealerSkill]) {
					case 51:  SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations, Your Arms Dealer Skill, is now Level 2.");
					case 151: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations, Your Arms Dealer Skill, is now Level 3.");
					case 247: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations, Your Arms Dealer Skill, is now Level 4.");
					case 439: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations, Your Arms Dealer Skill, is now Level 5.");
				}
				format(string, MAXO_TEXT2, "UPDATE players SET Materials = %d, ArmsDealerSkill = %d WHERE ID = %d", PlayerInfo[playerid][pMats], PlayerInfo[playerid][pArmsDealerSkill], PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must be at an deposit of materials to delivery this package.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have any package of materials to deliver it.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't guns dealer to use this command.");
	return true;
}

stock WeaponsAvailable(weapons) {
	switch(weapons) {
		case WEAPON_BRASSKNUCKLE, WEAPON_GOLFCLUB: return true;
		case WEAPON_KNIFE..WEAPON_CANE: return true;
		case WEAPON_COLT45..WEAPON_SHOTGUN: return true;
		case WEAPON_MP5..WEAPON_M4: return true;
	}
	return false;
}

COMMAND:sellgun(playerid, params[]) {
	new string[MAXO_TEXT], targetid, gunID, price;
	if(PlayerInfo[playerid][pJob] == JOB_ARMSDEALER) {
		if(!sscanf(params, "s[24]dd", PartialName[playerid][nume_introdus], gunID, price)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != playerid) {
				if(price > 0) {
					if(!IsPlayerCop(targetid)) {
						if(WeaponsAvailable(gunID)) {
							if(GetDistanceBetweenPlayers(playerid, targetid) < 4) {
								if(PlayerInfo[playerid][pMats]) {
									GunOffer[targetid] = playerid;
									GunPrice[targetid] = price;
									Gun[targetid] = gunID;
									if(PlayerInfo[playerid][pFactiune] == PlayerInfo[targetid][pFactiune] && PlayerInfo[playerid][pFactiune] > FACT_CIVIL) {
										format(string, MAXO_TEXT, "* You offerd %s a gun (ID: %d)", PlayerName(targetid), gunID);
										SendClientMessage(playerid, COLOR_FAMILY, string);
										format(string, MAXO_TEXT, "* Dealer %s wants to sell you a gun ID %d, (type /accept %d gun) to buy.", PlayerName(playerid), gunID, playerid);
										SendClientMessage(targetid, COLOR_FAMILY, string);
									}
									else
									{
										format(string, MAXO_TEXT, "* You offerd %s a gun (ID: %d) at price of $%s.", PlayerName(targetid), gunID, FormatNumber(price, 0, '.'));
										SendClientMessage(playerid, COLOR_FAMILY, string);
										format(string, MAXO_TEXT, "* Dealer %s wants to sell you a gun ID %d at price of $%s, (type /accept %d gun) to buy.", PlayerName(playerid), gunID, FormatNumber(price, 0, '.'), playerid);
										SendClientMessage(targetid, COLOR_FAMILY, string);
									}
									PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
									clear.string(string);
								} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have the materials to create a gun.");
							} else SendClientMessage(playerid, COLOR_GRAD1, "This player is too far away from you.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid weapon id");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You can't sell a gun to a cop.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "The price must be bigger of 0.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You can't sell weapons to yourself.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/sellgun [playerid/PartOfName] [gunID] [price]"), SendClientMessage(playerid, COLOR_GREY, "Weapons ID Available: 1, 2, 4-15, 22-25, 29-31");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't guns dealer to use this command.");
	return true;
}

COMMAND:buydrugs(playerid, params[]) {
	new string[MAXO_TEXT], LocRandom = RandomEx(1, 15);
	if(PlayerInfo[playerid][pJob] == JOB_DRUGSDEALER) {
		if(IsPlayerInRangeOfPoint(playerid, 3.0, 316.1890,1118.5377,1083.8828)) {
			gettime(gHours, gMinutes, gSeconds);
			if(gHours >= 12 || gHours <= 23) {
				switch(PlayerInfo[playerid][pDrugsDealerSkill]) {
					case 0..50: {
						if(PlayerInfo[playerid][pCash] < 5000)
							return SendClientMessage(playerid, COLOR_GRAD1, "You need $5.000 to buy un package of drugs.");
						if(JucatorulAreDroguri[playerid] > 0)
							return SendClientMessage(playerid, COLOR_GRAD1, "You have already a package of drugs, you can't buy another one.");
						JucatorulAreDroguri[playerid] = 5000;
						SafeGivePlayerMoney(playerid, -5000);
						CreateCP(playerid,LivreazaPachetul[LocRandom][0],LivreazaPachetul[LocRandom][1],LivreazaPachetul[LocRandom][2],6.0,checkpointNoAction,CP_NO_ACTION);
						LocatiaRandom{playerid} = LocRandom;
						format(string, MAXO_TEXT, "* You took one package of %s drugs at price of $5.000.", FormatNumber(JucatorulAreDroguri[playerid], 0, '.'));
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Now, you must to deliver this package if you type /deliverdrugs.");
					}
					case 51..150: {
						if(PlayerInfo[playerid][pCash] < 10000)
							return SendClientMessage(playerid, COLOR_GRAD1, "You need $10.000 to buy un package of drugs.");
						if(JucatorulAreDroguri[playerid] > 0)
							return SendClientMessage(playerid, COLOR_GRAD1, "You have already a package of drugs, you can't buy another one.");
						JucatorulAreDroguri[playerid] = 10000;
						SafeGivePlayerMoney(playerid, -10000);
						CreateCP(playerid,LivreazaPachetul[LocRandom][0],LivreazaPachetul[LocRandom][1],LivreazaPachetul[LocRandom][2],6.0,checkpointNoAction,CP_NO_ACTION);
						LocatiaRandom{playerid} = LocRandom;
						format(string, MAXO_TEXT, "* You took one package of %s drugs at price of $10.000.", FormatNumber(JucatorulAreDroguri[playerid], 0, '.'));
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Now, you must to deliver this package if you type /deliverdrugs.");
					}
					case 151..246: {
						if(PlayerInfo[playerid][pCash] < 15000)
							return SendClientMessage(playerid, COLOR_GRAD1, "You need $15.000 to buy un package of drugs.");
						if(JucatorulAreDroguri[playerid] > 0)
							return SendClientMessage(playerid, COLOR_GRAD1, "You have already a package of drugs, you can't buy another one.");
						JucatorulAreDroguri[playerid] = 15000;
						SafeGivePlayerMoney(playerid, -15000);
						PlayerInfo[playerid][pWlvl] += 1;
						SetPlayerWanted(playerid, INVALID_PLAYER_ID, PlayerInfo[playerid][pWlvl]);
						CreateCP(playerid,LivreazaPachetul[LocRandom][0],LivreazaPachetul[LocRandom][1],LivreazaPachetul[LocRandom][2],6.0,checkpointNoAction,CP_NO_ACTION);
						LocatiaRandom{playerid} = LocRandom;
						format(string, MAXO_TEXT, "* You took one package of %s drugs at price of $15.000.", FormatNumber(JucatorulAreDroguri[playerid], 0, '.'));
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Now, you must to deliver this package if you type /deliverdrugs.");
					}
					case 247..438: {
						if(PlayerInfo[playerid][pCash] < 25000)
							return SendClientMessage(playerid, COLOR_GRAD1, "You need $25.000 to buy un package of drugs.");
						if(JucatorulAreDroguri[playerid] > 0)
							return SendClientMessage(playerid, COLOR_GRAD1, "You have already a package of drugs, you can't buy another one.");
						JucatorulAreDroguri[playerid] = 50000;
						SafeGivePlayerMoney(playerid, -25000);
						PlayerInfo[playerid][pWlvl] += 1;
						SetPlayerWanted(playerid, INVALID_PLAYER_ID, PlayerInfo[playerid][pWlvl]);
						CreateCP(playerid,LivreazaPachetul[LocRandom][0],LivreazaPachetul[LocRandom][1],LivreazaPachetul[LocRandom][2],6.0,checkpointNoAction,CP_NO_ACTION);
						LocatiaRandom{playerid} = LocRandom;
						format(string, MAXO_TEXT, "* You took one package of %s drugs at price of $25.000.", FormatNumber(JucatorulAreDroguri[playerid], 0, '.'));
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Now, you must to deliver this package if you type /deliverdrugs.");
					}
					default: {
						if(PlayerInfo[playerid][pCash] < 50000)
							return SendClientMessage(playerid, COLOR_GRAD1, "You need $50.000 to buy un package of drugs.");
						if(JucatorulAreDroguri[playerid] > 0)
							return SendClientMessage(playerid, COLOR_GRAD1, "You have already a package of drugs, you can't buy another one.");
						JucatorulAreDroguri[playerid] = 100000;
						SafeGivePlayerMoney(playerid, -50000);
						PlayerInfo[playerid][pWlvl] += 3;
						SetPlayerWanted(playerid, INVALID_PLAYER_ID, PlayerInfo[playerid][pWlvl]);
						CreateCP(playerid,LivreazaPachetul[LocRandom][0],LivreazaPachetul[LocRandom][1],LivreazaPachetul[LocRandom][2],6.0,checkpointNoAction,CP_NO_ACTION);
						LocatiaRandom{playerid} = LocRandom;
						format(string, MAXO_TEXT, "* You took one package of %s drugs at price of $50.000.", FormatNumber(JucatorulAreDroguri[playerid], 0, '.'));
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Now, you must to deliver this package if you type /deliverdrugs.");
					}
				}
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "You can to take one package of drugs between 12:00-00:00.");
		}
		else
		{
			SendClientMessage(playerid, COLOR_GRAD1, "You aren't at Crack House to take one package of drugs.");
			if(!HaveVisibleCheckpoint(playerid))
				CreateCP(playerid,2165.9526,-1671.1735,15.0732,3.0,checkpointNoAction,CP_NO_ACTION);
		}
	} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't a dealer of drugs.");
	return true;
}

COMMAND:deliverdrugs(playerid, params[]) {
	new string[MAXO_TEXT2];
	if(PlayerInfo[playerid][pJob] == JOB_DRUGSDEALER) {
		if(JucatorulAreDroguri[playerid] > 0) {
			if(IsPlayerAtDepositOfMaterials(playerid)) {
				switch(PlayerInfo[playerid][pDrugsDealerSkill]) {
					case 0..50: SafeGivePlayerMoney(playerid, 6250), SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You received $6.250 for this delivery.");
					case 51..150: SafeGivePlayerMoney(playerid, 11475), SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You received $11.475 for this delivery.");
					case 151..246: SafeGivePlayerMoney(playerid, 18500), SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You received $18.500 for this delivery.");
					case 247..438: SafeGivePlayerMoney(playerid, 28750), SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You received $28.750 for this delivery.");
					default: SafeGivePlayerMoney(playerid, 70000), PlayerInfo[playerid][pDrugs] = 5000, SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You received $70.000 and 5.000 Drugs for this delivery.");
				}
				JucatorulAreDroguri[playerid] = 0;
				LocatiaRandom{playerid} = 0;
				PlayerInfo[playerid][pDrugsDealerSkill] ++;
				switch(PlayerInfo[playerid][pDrugsDealerSkill]) {
					case 50:  SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations, Your Drugs Dealer Skill, is now Level 2.");
					case 150: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations, Your Drugs Dealer Skill, is now Level 3.");
					case 246: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations, Your Drugs Dealer Skill, is now Level 4.");
					case 438: SendClientMessage(playerid, COLOR_YELLOW, "* Congratulations, Your Drugs Dealer Skill, is now Level 5.");
				}
				format(string, MAXO_TEXT2, "UPDATE players SET Drugs = %d, DrugsDealerSkill = %d WHERE ID = %d", PlayerInfo[playerid][pDrugs], PlayerInfo[playerid][pDrugsDealerSkill], PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must be at an deposit of Drugs to delivery this package.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have any package of Drugs to deliver it.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't drugs dealer to use this command.");
	return true;
}

COMMAND:selldrugs(playerid, params[]) {
	new string[MAXO_TEXT], targetid, amount, price;
	if(PlayerInfo[playerid][pJob] == JOB_DRUGSDEALER) {
		if(!sscanf(params, "s[24]dd", PartialName[playerid][nume_introdus], amount, price)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != playerid) {
				if(price > 0) {
					if(!IsPlayerCop(targetid)) {
						if(amount > 0) {
							if(GetDistanceBetweenPlayers(playerid, targetid) < 4) {
								if(PlayerInfo[playerid][pDrugs]) {
									DrugsOffer[targetid] = playerid;
									DrugsPrice[targetid] = price;
									Drugs[targetid] = amount;
									if(PlayerInfo[playerid][pFactiune] == PlayerInfo[targetid][pFactiune] && PlayerInfo[playerid][pFactiune] > FACT_CIVIL) {
										format(string, MAXO_TEXT, "* You offerd %s %d grams of drugs", PlayerName(targetid), amount);
										SendClientMessage(playerid, COLOR_FAMILY, string);
										format(string, MAXO_TEXT, "* Dealer %s wants to sell you %d grams of drugs, (type /accept %d drugs) to buy.", PlayerName(playerid), amount, playerid);
										SendClientMessage(targetid, COLOR_FAMILY, string);
									}
									else
									{
										format(string, MAXO_TEXT, "* You offerd %s %d gram of drugs at price of $%s.", PlayerName(targetid), amount, FormatNumber(price, 0, '.'));
										SendClientMessage(playerid, COLOR_FAMILY, string);
										format(string, MAXO_TEXT, "* Dealer %s wants to sell you %d grams of drugs at price of $%s, (type /accept %d drugs) to buy.", PlayerName(playerid), amount, FormatNumber(price, 0, '.'), playerid);
										SendClientMessage(targetid, COLOR_FAMILY, string);
									}
									PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
									clear.string(string);
								} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have the drugs.");
							} else SendClientMessage(playerid, COLOR_GRAD1, "This player is too far away from you.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid amount");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You can't sell a drugs to a cop.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "The price must be bigger of 0.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You can't sell drugs to yourself.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/selldrugs [playerid/PartOfName] [amount] [price]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't drugs dealer to use this command.");
	return true;
}

stock CalculeazaBaniiLaJob(playerid, prods) {
	new Float:PriceProds;
	new Float:X, Float:Y, Float:Z;
	GetPlayerPos(playerid, X, Y, Z);
	PriceProds = (GetDistanceBetweenPoints(-19.0057, -269.7075, 5.4297, X, Y, Z)/100)*prods;
	return floatround(PriceProds, floatround_round);
}

COMMAND:sellprods(playerid, params[]) {
	new vID = GetPlayerVehicleID(playerid), x = GetBizSQLID(playerid, 8.0), string[MAXO_TEXT], Float:X, Float:Y, Float:Z;
	if(PlayerInfo[playerid][pJob] == JOB_TRUCKER) {
		if(CarInfo[vID][cType] == VEHICLE_TYPE_TRUCKER) {
			if(IsPlayerInRangeOfPoint(playerid, 8.0, BizInfo[x][bEntrancex], BizInfo[x][bEntrancey], BizInfo[x][bEntrancez])) {
				if(PlayerHaul[vID][pLoad] > 0) {
					if(BizInfo[x][bProducts] != 100) {
						GetPlayerPos(playerid, X, Y, Z);
						new produse = 100 - BizInfo[x][bProducts];
						PlayerHaul[vID][pLoad] -= produse;
						BizInfo[x][bProducts] += produse;
						new banideprimit = CalculeazaBaniiLaJob(playerid, produse);
						format(string, MAXO_TEXT, "UPDATE bizz SET Products = %d WHERE ID = %d", BizInfo[x][bProducts], BizInfo[x][bSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
						SafeGivePlayerMoney(playerid, banideprimit);
						format(string, MAXO_TEXT, "INFO: You got $%s for delivery, from %.02f meters distance from deposit.", FormatNumber(banideprimit, 0, '.'), GetDistanceBetweenPoints(-19.0057, -269.7075, 5.4297, X, Y, Z));
						SendClientMessage(playerid, COLOR_ORANGE, string);
						format(string, MAXO_TEXT, "INFO: The owner of this business bought %d products from you.", produse);
						SendClientMessage(playerid, COLOR_ORANGE, string);
						format(string, MAXO_TEXT, "* You have anymore %d/100 products in your truck.", PlayerHaul[vID][pLoad]);
						SendClientMessage(playerid, COLOR_ORANGE, string);
						for(new m; m < 2; m ++) {
							if(PlayerInfo[playerid][pDailyMission][m] == MISSION_DELIVERYPRODS)
								CheckMission(playerid, m);
						}
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "This business is already full with products.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have the products anymore.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't in front of the business to use this command.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't in a vehicle from Job.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't truck driver.");
	return true;
}

COMMAND:getprods(playerid, params[]) {
	new vID = GetPlayerVehicleID(playerid);
	if(PlayerInfo[playerid][pJob] == JOB_TRUCKER) {
		if(CarInfo[vID][cType] == VEHICLE_TYPE_TRUCKER) {
			if(IsPlayerInRangeOfPoint(playerid, 20.0, -19.0057, -269.7075, 5.4297)) {
				if(PlayerHaul[vID][pLoad] == 0) {
					PlayerHaul[vID][pLoad] = 100;
					SendClientMessage(playerid, COLOR_ORANGE, "INFO: Your truck has been loaded with 100/100 products.");
					SendClientMessage(playerid, COLOR_ORANGE, "INFO: Now, you can go to business and sell the products.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "Already, you have anymore products in your truck.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in base to load your truck.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "This vehicle is not from Trucker Job.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You must be trucker as to use this command.");
	return true;
}

COMMAND:createjob(playerid, params[]) {
	if(IsPlayerFounder(playerid)) {
		if(!sscanf(params, "s[25]", params)) {
			if(strlen(params) < 25) {
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
					new Float:positionjob[3];
					GetPlayerPos(playerid, positionjob[0], positionjob[1], positionjob[2]);
					new string[MAXO_TEXT];
					format(string, MAXO_TEXT, "INSERT INTO jobs (JobName, JobPosX, JobPosY, JobPosZ) VALUES ('%s', '%f', '%f', '%f')", params, positionjob[0], positionjob[1], positionjob[2]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", JOBS_THREAD_ID);
					SendClientMessage(playerid, COLOR_YELLOW, "[Job] {FFFFFF} Job adaugat cu succes in baza de date.");
					#if defined _stream_pickups
						JobPickup = CreateDynamicPickup(1210, 2, positionjob[0], positionjob[1], positionjob[2]);
					#else
						JobPickup = CreatePickup(1210, 2, positionjob[0], positionjob[1], positionjob[2]);
					#endif
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "You must be pedestrian for this action.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "The name of the job is too long.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/createjob [jobname]");
	} else NotAuthorized();
	return true;
}

// End Of File ...
