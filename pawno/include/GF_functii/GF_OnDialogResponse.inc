/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_OnDialogResponse_included
	#endinput
#else
	#define GF_OnDialogResponse_included
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	new
		string[MAXO_TEXT], vID = GetPlayerVehicleID(playerid);
	RegOnDialogResponse(playerid, dialogid, response, listitem, inputtext); // register system copyrighted - Kurama
	BanSysOnDialogResponse(playerid, dialogid, response, listitem, inputtext); // ban system copyrighted - Kurama
	DMVOnDialogResponse(playerid, dialogid, response, listitem, inputtext); // drive motor vehicle system copyrighted - Kurama
	SafeOnDialogResponse(playerid, dialogid, response, listitem, inputtext); // safes system copyrighted - Kurama
	WalOnDialogResponse(playerid, dialogid, response, listitem, inputtext); // walkie talkie system copyrighted - Kurama
	RaceSysOnDialogResponse(playerid, dialogid, response, listitem, inputtext); //race system copyrighted - Kurama
	if(dialogid == DIALOGID_CAR_RADIO) {
		if(response) {
			StartCarRadio(vID, listitem, 0, playerid);
		}
	}
	else if(dialogid == DIALOGID_REPORT) {
		if(response) {
			if(strval(inputtext) < 75) {
				format(string, MAXO_TEXT, "* ( REPORT From [%d]%s: "ALB"%s "GALBEN") *", playerid, PlayerName(playerid), inputtext);
				ABroadCast(COLOR_YELLOW, string, 1);
				format(string, MAXO_TEXT, "* ( Your report: "ALB"%s "GALBEN") *", inputtext);
				SendClientMessage(playerid, COLOR_YELLOW, string);
				PlayerInfo[playerid][pReportTime] = 30;
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You cancelled this action.");
	}
	else if(dialogid == DIALOGID_VEHICLE_REPAIR) {
		if(response) {
			new extras = PlayerInfo[playerid][pLevel]*500;
			if(PlayerInfo[playerid][pCash] > extras) {
				new newcar = GetPlayerVehicleID(playerid);
				if(newcar != INVALID_VEHICLE_ID) {
					new tlabel[20];
					SafeGivePlayerMoney(playerid, -extras);
					format(tlabel, sizeof(tlabel), "~r~-%d~y~$", extras);
					GameTextForPlayer(playerid, tlabel, 1500, 1);
					new engine, lights, alarm, doors, bonnet, boot, objective;
					if(ISBetween(CarInfo[newcar][cFactionID], FACT_LSPD, MAX_FACTIONS)) CarInfo[newcar][cLastBroken] = gLocalTimeStamp+259200;
					GetVehicleParamsEx(newcar, engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(newcar, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, alarm, VEHICLE_PARAMS_ON, bonnet, boot, objective);
					RepairVehicle(newcar), SendClientMessage(playerid, COLOR_GREY, "Vehicle Fixed !");
					if(ISBetween(CarInfo[newcar][cFactionID], FACT_LSPD, MAX_FACTIONS)) format(string, MAXO_TEXT, "UPDATE vehicles SET LastBroken = %d WHERE ID = '%d' LIMIT 1",CarInfo[newcar][cLastBroken],CarInfo[newcar][cSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", VEHICLE_THREAD_ID);
					SetVehicleToRespawn(newcar);
					clear.string(tlabel);
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "You are not in inside a vehicle.");
			} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Repair aborted", "No action has been taken. You don't have enough money.", "Ok", "");
		} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Repair aborted", "No action has been taken. You aborted the repair.", "Ok", "");
	}
	else if(dialogid == DIALOGID_JOB_SWEEPER) {
		if(response) {
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Congratulations with your new Job, type {FFFFFF}/help{33CCFF} to see your new command.");
			PlayerInfo[playerid][pJob] = JOB_SWEEPER;
			format(string, MAXO_TEXT, "UPDATE players SET Job = %d WHERE ID = %d", PlayerInfo[playerid][pJob], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			clear.string(string);
		}
	}
	else if(dialogid == DIALOGID_SELECT_ROUTE) {
		if(response) {
			PlayerInfo[playerid][pCPSweeper] = 0, 
			CreateCP(playerid,LocationRouteOneSweeper[PlayerInfo[playerid][pCPSweeper]][0],LocationRouteOneSweeper[PlayerInfo[playerid][pCPSweeper]][1],LocationRouteOneSweeper[PlayerInfo[playerid][pCPSweeper]][2],DEFAULT_CP_SIZE,checkpointSweeper,CP_SWEEPER); 
		}
		else if(!response) {
			PlayerInfo[playerid][pCPSweeper2] = 0, 
			CreateCP(playerid,LocationRouteTwoSweeper[PlayerInfo[playerid][pCPSweeper2]][0],LocationRouteTwoSweeper[PlayerInfo[playerid][pCPSweeper2]][1],LocationRouteTwoSweeper[PlayerInfo[playerid][pCPSweeper2]][2],DEFAULT_CP_SIZE,checkpointSweeper2,CP_SWEEPER2);
		}
	}
	else if(dialogid == DIALOGID_JOB_FARMER) {
		if(response) {
			if(PlayerInfo[playerid][pJob] == JOB_NONE) {
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Congratulations with your new Job, type {FFFFFF}/help{33CCFF} to see your new command.");
				PlayerInfo[playerid][pJob] = JOB_FARMER;
				format(string, MAXO_TEXT, "UPDATE players SET Job = %d WHERE ID = %d", PlayerInfo[playerid][pJob], PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				clear.string(string);
			} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Job", "You have already an job.\nType /quitjob an try again to enter in this pickup.", "Ok", "");
		}
	}
	else if(dialogid == DIALOGID_JOB_DUSTMAN) {
		if(response) {
			if(PlayerInfo[playerid][pJob] == JOB_NONE) {
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Congratulations with your new Job, type {FFFFFF}/help{33CCFF} to see your new command.");
				PlayerInfo[playerid][pJob] = JOB_DUSTMAN;
				format(string, MAXO_TEXT, "UPDATE players SET Job = %d WHERE ID = %d", PlayerInfo[playerid][pJob], PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				clear.string(string);
			} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Job", "You have already an job.\nType /quitjob an try again to enter in this pickup.", "Ok", "");
		}
	}
	else if(dialogid == DIALOGID_JOB_TRUCKER) {
		if(response) {
			if(PlayerInfo[playerid][pJob] == JOB_NONE) {
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Congratulations with your new Job, type {FFFFFF}/help{33CCFF} to see your new command.");
				PlayerInfo[playerid][pJob] = JOB_TRUCKER;
				format(string, MAXO_TEXT, "UPDATE players SET Job = %d WHERE ID = %d", PlayerInfo[playerid][pJob], PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				clear.string(string);
			} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Job", "You have already an job.\nType /quitjob an try again to enter in this pickup.", "Ok", "");
		}
	}
	else if(dialogid == DIALOGID_JOB_CARJACKER) {
		if(response) {
			if(PlayerInfo[playerid][pJob] == JOB_NONE) {
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Congratulations with your new Job, type {FFFFFF}/help{33CCFF} to see your new command.");
				PlayerInfo[playerid][pJob] = JOB_CARJACKER;
				format(string, MAXO_TEXT, "UPDATE players SET Job = %d WHERE ID = %d", PlayerInfo[playerid][pJob], PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				clear.string(string);
			} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Job", "You have already an job.\nType /quitjob an try again to enter in this pickup.", "Ok", "");
		}
	}
	else if(dialogid == DIALOGID_JOBS) {
		if(response) {
			if(listitem == 0) { // Farmer
				CreateCP(playerid,-392.252,-1439.17,26.3336,DEFAULT_CP_SIZE,checkpointNoAction,CP_NO_ACTION);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Where is the checkpoint, there can you find the job selected.");
			}
			else if(listitem == 1) { // Street Sweeper
				CreateCP(playerid,-2524.15,1216.25,37.5487,DEFAULT_CP_SIZE,checkpointNoAction,CP_NO_ACTION);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Where is the checkpoint, there can you find the job selected.");
			}
			else if(listitem == 2) { // Dustman
				CreateCP(playerid,1611.3513,-1893.8300,13.5469,DEFAULT_CP_SIZE,checkpointNoAction,CP_NO_ACTION);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Where is the checkpoint, there can you find the job selected.");
			}
			else if(listitem == 3) { // Trucker
				CreateCP(playerid,-49.9815,-269.363,6.63319,DEFAULT_CP_SIZE,checkpointNoAction,CP_NO_ACTION);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Where is the checkpoint, there can you find the job selected.");
			}
			else if(listitem == 4) { // Car Jacker
				CreateCP(playerid,-1741.85,36.1556,3.55469,DEFAULT_CP_SIZE,checkpointNoAction,CP_NO_ACTION);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Where is the checkpoint, there can you find the job selected.");
			}
			else if(listitem == 5) { // Arms Dealer
				CreateCP(playerid,1366.4086,-1275.4865,13.5469,DEFAULT_CP_SIZE,checkpointNoAction,CP_NO_ACTION);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Where is the checkpoint, there can you find the job selected.");
			}
			else if(listitem == 6) { // Drugs Dealer Dealer
				CreateCP(playerid,2163.9717,-1675.5319,15.0859,DEFAULT_CP_SIZE,checkpointNoAction,CP_NO_ACTION);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Where is the checkpoint, there can you find the job selected.");
			}
		}
	}
	else if(dialogid == DIALOGID_DEALERSHIP) {
		if(response) {
			if(PlayerInfo[playerid][pWlvl])
				return SendClientMessage(playerid, COLOR_GRAD1, "You can't to enter in Dealership, go to surrender yourself.");
			ShowDSEnvironment(playerid);
		} else SendClientMessage(playerid, COLOR_LIGHTBLUE, "* "ALB"You cancelled this action.");
	}
	else if(dialogid == DIALOGID_LIFT1_LSPD) {
		if(response) {
			new fID = PlayerInfo[playerid][pFactiune];
			switch(listitem) {
				case 0: { // HeadQuarter
					SafeSetPlayerPos(playerid, FactionInfo[fID][fHQExitx], FactionInfo[fID][fHQExity], FactionInfo[fID][fHQExitz]);
					SafeSetPlayerInterior(playerid, FactionInfo[fID][fInterior]);
					SafeSetPlayerVirtualWorld(playerid, FactionInfo[fID][fVirtualWorld]);
					PlayerInfo[playerid][pInHQID] = PlayerInfo[playerid][pFactiune];
					format(string, MAXO_TEXT, "~w~Headquarter ~n~ ~y~%s", FactionInfo[FACT_LSPD][fName]);
					GameTextForPlayer(playerid, string, 5000, 1);
				}
				case 1: { // Roof LSPD
					SafeSetPlayerPos(playerid, 1564.9653, -1666.9790, 28.3956);
					SafeSetPlayerInterior(playerid, 0);
					SafeSetPlayerVirtualWorld(playerid, 0);
					GameTextForPlayer(playerid, "~w~Los Santos", 5000, 1);
				}
				case 2: { // LSPD Station
					SafeSetPlayerPos(playerid, 246.5154,88.0078,1003.6406);
					SafeSetPlayerInterior(playerid, 6);
					SafeSetPlayerVirtualWorld(playerid, LSPD_VW);
					format(string, MAXO_TEXT, "~w~Welcome to ~n~ LSPD Station ~n~ ~y~ %s", PlayerName(playerid));
					GameTextForPlayer(playerid, string, 5000, 1);
				}
			}
			clear.string(string);
		}
	}
	else if(dialogid == DIALOGID_LIFT2_LSPD) {
		if(response) {
			new fID = PlayerInfo[playerid][pFactiune];
			switch(listitem) {
				case 0: { // Ground floor
					SafeSetPlayerPos(playerid, FactionInfo[fID][fHQEnterx], FactionInfo[fID][fHQEntery], FactionInfo[fID][fHQEnterz]);
					SafeSetPlayerInterior(playerid, 0);
					SafeSetPlayerVirtualWorld(playerid, 0);
					PlayerInfo[playerid][pInHQID] = FACT_CIVIL;
				}
				case 1: { // Roof LSPD
					SafeSetPlayerPos(playerid, 1564.9653, -1666.9790, 28.3956);
					SafeSetPlayerInterior(playerid, 0);
					SafeSetPlayerVirtualWorld(playerid, 0);
					GameTextForPlayer(playerid, "~w~Los Santos", 5000, 1);
				}
				case 2: { // LSPD Station
					SafeSetPlayerPos(playerid, 246.5154,88.0078,1003.6406);
					SafeSetPlayerInterior(playerid, 6);
					SafeSetPlayerVirtualWorld(playerid, LSPD_VW);
					format(string, MAXO_TEXT, "~w~Welcome to ~n~ LSPD Station ~n~ ~y~ %s", PlayerName(playerid));
					GameTextForPlayer(playerid, string, 5000, 1);
				}
			}
			clear.string(string);
		}
	}
	else if(dialogid == DIALOGID_LIFT3_LSPD) {
		if(response) {
			new fID = PlayerInfo[playerid][pFactiune];
			switch(listitem) {
				case 0: { // HeadQuarter
					SafeSetPlayerPos(playerid, FactionInfo[fID][fHQExitx], FactionInfo[fID][fHQExity], FactionInfo[fID][fHQExitz]);
					SafeSetPlayerInterior(playerid, FactionInfo[fID][fInterior]);
					SafeSetPlayerVirtualWorld(playerid, FactionInfo[fID][fVirtualWorld]);
					PlayerInfo[playerid][pInHQID] = PlayerInfo[playerid][pFactiune];
				}
				case 1: { // Ground floor
					SafeSetPlayerPos(playerid, FactionInfo[fID][fHQEnterx], FactionInfo[fID][fHQEntery], FactionInfo[fID][fHQEnterz]);
					SafeSetPlayerInterior(playerid, 0);
					SafeSetPlayerVirtualWorld(playerid, 0);
					PlayerInfo[playerid][pInHQID] = FACT_CIVIL;
				}
				case 2: { // LSPD Station
					SafeSetPlayerPos(playerid, 246.5154,88.0078,1003.6406);
					SafeSetPlayerInterior(playerid, 6);
					SafeSetPlayerVirtualWorld(playerid, LSPD_VW);
					format(string, MAXO_TEXT, "~w~Welcome to ~n~ LSPD Station ~n~ ~y~ %s", PlayerName(playerid));
					GameTextForPlayer(playerid, string, 5000, 1);
				}
			}
			clear.string(string);
		}
	}
	else if(dialogid == DIALOGID_JOB_ARMSDEALER) {
		if(response) {
			if(PlayerInfo[playerid][pJob] == JOB_NONE) {
				if(IsPlayerCop(playerid))
					return ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Job", "This job isn't available for you.", "Ok", "");
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Congratulations with your new Job, type {FFFFFF}/help{33CCFF} to see your new command.");
				PlayerInfo[playerid][pJob] = JOB_ARMSDEALER;
				format(string, MAXO_TEXT, "UPDATE players SET Job = %d WHERE ID = %d", PlayerInfo[playerid][pJob], PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				clear.string(string);
			} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Job", "You have already an job.\nType /quitjob an try again to enter in this pickup.", "Ok", "");
		}
	}
	else if(dialogid == DIALOGID_JOB_DRUGSDEALER) {
		if(response) {
			if(PlayerInfo[playerid][pJob] == JOB_NONE) {
				if(IsPlayerCop(playerid))
					return ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Job", "This job isn't available for you.", "Ok", "");
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Congratulations with your new Job, type {FFFFFF}/help{33CCFF} to see your new command.");
				PlayerInfo[playerid][pJob] = JOB_DRUGSDEALER;
				format(string, MAXO_TEXT, "UPDATE players SET Job = %d WHERE ID = %d", PlayerInfo[playerid][pJob], PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				clear.string(string);
			} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Job", "You have already an job.\nType /quitjob an try again to enter in this pickup.", "Ok", "");
		}
	}
	return 1;
}


// End Of File ...
