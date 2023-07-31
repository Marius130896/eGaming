/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_OnPlayerPickup_included
	#endinput
#else
	#define GF_OnPlayerPickup_included
#endif

enum pickInfo {
	pickSQLID,
	pickModel,
	pickType,
	Float:pickPos[3],
	pickVW,
	pickInterior,
	pickText[MAXO_TEXT],
	pickPickupType,
/*
					Pickup Type INFO:

	Type 0: Pickup care utilizeaza functia GameTextForPlayer
	Type 1: Pickup care utilizeaza functia ShowPlayerDialog
	Type 2: Pickup care utilizeaza functia Create3DTextLabel
*/
	pickForAction
};
new PickupInfo[MAX_PICKUPS][pickInfo];

#define PICKUP_USE_GAMETEXT	0
#define PICKUP_USE_DIALOG 1
#define PICKUP_USE_3DTEXT 2

#define ACTION_PICK_DRIVING_LICENSE 1
#define ACTION_PICK_FLYING_LICENSE 2
#define ACTION_PICK_SAILING_LICENSE 3
#define ACTION_PICK_ORDER_HITMAN 4
#define ACTION_PICK_DEALERSHIP 5
#define ACTION_PICK_GUN_DMV 6

stock LoadPickups() {
	mysql_tquery(connectionHandle, "SELECT * FROM pickups", "LoadPickupsThread", "d", PICKUP_THREAD_ID);
	return true;
}

function LoadPickupsThread() {
	if(cache_num_rows()) {
		new
			pickupModel, pickupType, Float: pickupPosX, Float: pickupPosY, Float: pickupPosZ, pickupVW, pickupInt, pickupID;
		for(new p; p < cache_num_rows(); p ++) {
			pickupModel = cache_get_row_int(p, 1);
			pickupType = cache_get_row_int(p, 2);
			pickupPosX = cache_get_row_float(p, 3);
			pickupPosY = cache_get_row_float(p, 4);
			pickupPosZ = cache_get_row_float(p, 5);
			pickupVW = cache_get_row_int(p, 6);
			pickupInt = cache_get_row_int(p, 7);

		#if defined _stream_pickups
			pickupID = CreateDynamicPickup(pickupModel, pickupType, pickupPosX, pickupPosY, pickupPosZ, -1);
		#else
			pickupID = CreatePickup(pickupModel, pickupType, pickupPosX, pickupPosY, pickupPosZ, -1);
		#endif

			if(pickupID != -1) {
				PickupInfo[pickupID][pickModel] = pickupModel;
				PickupInfo[pickupID][pickType] = pickupType;
				PickupInfo[pickupID][pickPos][0] = pickupPosX;
				PickupInfo[pickupID][pickPos][1] = pickupPosY;
				PickupInfo[pickupID][pickPos][2] = pickupPosZ;
				PickupInfo[pickupID][pickVW] = pickupVW;
				PickupInfo[pickupID][pickInterior] = pickupInt;
				cache_get_row(p, 8, PickupInfo[pickupID][pickText], .max_len = MAXO_TEXT);
				PickupInfo[pickupID][pickPickupType] = cache_get_row_int(p, 9);
				PickupInfo[pickupID][pickForAction] = cache_get_row_int(p, 10);

				if(PickupInfo[pickupID][pickPickupType] == PICKUP_USE_3DTEXT) {
					new
						string[MAXO_TEXT];
					format(string, MAXO_TEXT, "%s", PickupInfo[pickupID][pickText]);
					Create3DTextLabel(string, COLOR_YELLOW, PickupInfo[pickupID][pickPos][0], PickupInfo[pickupID][pickPos][1], PickupInfo[pickupID][pickPos][2] + 1, 15, 0 , 1 );
					clear.string(string);
				}
			} else printf("Eroare la incarea pickup id: %d", cache_get_row_int(p, 0));
		}
	}
	return true;
}

#if defined _stream_pickups
public OnPlayerPickUpDynamicPickup(playerid, pickupid) {
#else
public OnPlayerPickUpPickup(playerid, pickupid) {
#endif
	new string[MAXO_TEXT];
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
		for(new i = 0; i < MAX_FACTIONS; i ++) {
			if(IsPlayerInRangeOfPoint(playerid, 3.0, SafeInfo[i][seifPos][0], SafeInfo[i][seifPos][1], SafeInfo[i][seifPos][2])) {
				ShowPlayerDialog(playerid, DIALOGID_SAFE_INFO, DIALOG_STYLE_LIST, "Safe Options", "1. Drugs\n2. Materials\n3. Money\n4. Balance", "Ok", "Cancel");
			}
		}
		for(new i = 0; i < MAX_JOBS; i ++) {
			if(IsPlayerInRangeOfPoint(playerid, 3.0, JobInfo[i][joPos][0], JobInfo[i][joPos][1], JobInfo[i][joPos][2])) {
				switch(JobInfo[i][joSQLID]) {
					case JOB_FARMER: ShowPlayerDialog(playerid, DIALOGID_JOB_FARMER, DIALOG_STYLE_MSGBOX, "Farmer for hire !", "{BFEFFF}You can take this job if you want\n\nDo you want to become Farmer ?", "Yes", "No");
					case JOB_SWEEPER: ShowPlayerDialog(playerid, DIALOGID_JOB_SWEEPER, DIALOG_STYLE_MSGBOX, "Street Sweeper for hire !", "{BFEFFF}You can take this job if you want\n\nDo you want to become Street Sweeper ?", "Yes", "No");
					case JOB_DUSTMAN: ShowPlayerDialog(playerid, DIALOGID_JOB_DUSTMAN, DIALOG_STYLE_MSGBOX, "Dustman for hire !", "{BFEFFF}You can take this job if you want\n\nDo you want to become Dustman ?", "Yes", "No");
					case JOB_TRUCKER: ShowPlayerDialog(playerid, DIALOGID_JOB_TRUCKER, DIALOG_STYLE_MSGBOX, "Trucker for hire !", "{BFEFFF}You can take this job if you want\n\nDo you want to become Trucker ?", "Yes", "No");
					case JOB_CARJACKER: ShowPlayerDialog(playerid, DIALOGID_JOB_CARJACKER, DIALOG_STYLE_MSGBOX, "Car Jacker for hire !", "{BFEFFF}You can take this job if you want\n\nDo you want to become Car Jacker ?", "Yes", "No");
					case JOB_ARMSDEALER: ShowPlayerDialog(playerid, DIALOGID_JOB_ARMSDEALER, DIALOG_STYLE_MSGBOX, "Arms Dealer for hire !", "{BFEFFF}You can take this job if you want\n\nDo you want to become Arms Dealer ?", "Yes", "No");
					case JOB_DRUGSDEALER: ShowPlayerDialog(playerid, DIALOGID_JOB_DRUGSDEALER, DIALOG_STYLE_MSGBOX, "Drugs Dealer for hire !", "{BFEFFF}You can take this job if you want\n\nDo you want to become Drugs Dealer ?", "Yes", "No");
				}
			}
		}
		switch(PickupInfo[pickupid][pickPickupType]) {
			case PICKUP_USE_GAMETEXT:
			{
				format(string, sizeof(string), "%s", PickupInfo[pickupid][pickText]);
				GameTextForPlayer(playerid, string, 5000, 3);
				switch(PickupInfo[pickupid][pickForAction]) {
					case ACTION_PICK_ORDER_HITMAN:
					{
						if(OrderReady[playerid] != 0) {
							switch (OrderReady[playerid]) {
								case 1:
								{
									GivePlayerWeapon(playerid, 24, 50); GivePlayerWeapon(playerid, 29, 500); GivePlayerWeapon(playerid, 25, 50); GivePlayerWeapon(playerid, 4, 1);
									SafeGivePlayerMoney(playerid, -5000);
									SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You picked up your Ordered Package.");
								}
								case 2:
								{
									GivePlayerWeapon(playerid, 24, 50); GivePlayerWeapon(playerid, 29, 500); GivePlayerWeapon(playerid, 25, 50); GivePlayerWeapon(playerid, 31, 500); GivePlayerWeapon(playerid, 4, 1);
									SafeGivePlayerMoney(playerid, -6000);
									SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You picked up your Ordered Package.");
								}
								case 3:
								{
									GivePlayerWeapon(playerid, 24, 50); GivePlayerWeapon(playerid, 29, 500); GivePlayerWeapon(playerid, 25, 50); GivePlayerWeapon(playerid, 30, 500); GivePlayerWeapon(playerid, 4, 1);
									SafeGivePlayerMoney(playerid, -6000);
									SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You picked up your Ordered Package.");
								}
								case 4:
								{
									GivePlayerWeapon(playerid, 24, 50); GivePlayerWeapon(playerid, 29, 500); GivePlayerWeapon(playerid, 25, 50); GivePlayerWeapon(playerid, 31, 500); GivePlayerWeapon(playerid, 4, 1); GivePlayerWeapon(playerid, 34, 20);
									SafeGivePlayerMoney(playerid, -8000);
									SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You picked up your Ordered Package.");
								}
								case 5:
								{
									GivePlayerWeapon(playerid, 24, 50); GivePlayerWeapon(playerid, 29, 500); GivePlayerWeapon(playerid, 25, 50); GivePlayerWeapon(playerid, 30, 500); GivePlayerWeapon(playerid, 4, 1); GivePlayerWeapon(playerid, 34, 20);
									SafeGivePlayerMoney(playerid, -8000);
									SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You picked up your Ordered Package.");
								}
								case 6:
								{
									GivePlayerWeapon(playerid, 24, 50); GivePlayerWeapon(playerid, 29, 500); GivePlayerWeapon(playerid, 25, 50); GivePlayerWeapon(playerid, 31, 500); GivePlayerWeapon(playerid, 4, 1); GivePlayerWeapon(playerid, 34, 20);
									SafeGivePlayerMoney(playerid, -8500);
									SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You picked up your Ordered Package.");
								}
								case 7:
								{
									GivePlayerWeapon(playerid, 24, 50); GivePlayerWeapon(playerid, 29, 500); GivePlayerWeapon(playerid, 25, 50); GivePlayerWeapon(playerid, 30, 500); GivePlayerWeapon(playerid, 4, 1); GivePlayerWeapon(playerid, 34, 20);
									SafeGivePlayerMoney(playerid, -8500);
									SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You picked up your Ordered Package.");
								}
							}
							OrderReady[playerid] = 0;
						}
					}
				}
			}
			case PICKUP_USE_DIALOG:
			{
				switch(PickupInfo[pickupid][pickForAction]) {
					case ACTION_PICK_DRIVING_LICENSE:
					{
						if(pTestType{playerid} == TEST_TYPE_NONE) {
							if(PlayerInfo[playerid][pCash] >= (PlayerInfo[playerid][pLevel]*2500)) {
								RemovePlayerMapIcon(playerid, MAPICON_DRIVING);
								format(string, MAXO_TEXT, "Do you want to start Driving Exam?\nCost: $%s", FormatNumber(PlayerInfo[playerid][pLevel] * 2500, 0, '.'));
								ShowPlayerDialog(playerid, DIALOGID_DMV_ACTION, DIALOG_STYLE_MSGBOX, "DMV Test Authority", string, "Yes", "No");
							} else format(string, MAXO_TEXT, "You cannot renew the driving license! You need $%s.", FormatNumber(PlayerInfo[playerid][pLevel] * 2500, 0, '.')), SendClientMessage(playerid, COLOR_GRAD1, string);
						} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "DMV Test Authority", "You cannot give this test, because you already have a test.", "Understand", "");
					}
					case ACTION_PICK_FLYING_LICENSE:
					{
						if(pTestType{playerid} == TEST_TYPE_NONE) {
							if(PlayerInfo[playerid][pLevel] < 4)
								return SendClientMessage(playerid, COLOR_GRAD1, "You cannot obtain the flying license, because you have the level lower than 4.");
							if(PlayerInfo[playerid][pCash] < (PlayerInfo[playerid][pLevel]*3000))
								return format(string, MAXO_TEXT, "You cannot renew the flying license! You need $%s.", FormatNumber(PlayerInfo[playerid][pLevel] * 3000, 0, '.')), SendClientMessage(playerid, COLOR_GRAD1, string);
							RemovePlayerMapIcon(playerid, MAPICON_FLYING);
							if(PlayerInfo[playerid][pFlyingLicense] == 0) {
								format(string, MAXO_TEXT, "You want to start Flying Exam?\nCost: $%s", FormatNumber(PlayerInfo[playerid][pLevel] * 3000, 0, '.'));
								ShowPlayerDialog(playerid, DIALOGID_DMP_ACTION, DIALOG_STYLE_MSGBOX, "DMP Test Authority", string, "Yes", "No");
							}
						} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "DMV Test Authority", "You cannot give this test, because you already have a test.", "Understand", "");
					}
					case ACTION_PICK_SAILING_LICENSE:
					{
						if(pTestType{playerid} == TEST_TYPE_NONE) {
							RemovePlayerMapIcon(playerid, MAPICON_SAILING);
							if(PlayerInfo[playerid][pCash] < (PlayerInfo[playerid][pLevel]*2000))
								return format(string, MAXO_TEXT, "You cannot renew the flying license! You need $%s.", FormatNumber(PlayerInfo[playerid][pLevel] * 2000, 0, '.')), SendClientMessage(playerid, COLOR_GRAD1, string);
							if(PlayerInfo[playerid][pSailingLicense] == 0) {
								format(string, MAXO_TEXT, "You want to start Sailing Exam?\nCost: $%s", FormatNumber(PlayerInfo[playerid][pLevel] * 2000, 0, '.'));
								ShowPlayerDialog(playerid, DIALOGID_DMB_ACTION, DIALOG_STYLE_MSGBOX, "DMP Test Authority", string, "Yes", "No");
							}
						} else ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "DMV Test Authority", "You cannot give this test, because you already have a test.", "Understand", "");
					}
					case ACTION_PICK_DEALERSHIP: {
						format(string, MAXO_TEXT, "%s", PickupInfo[pickupid][pickText]),
						ShowPlayerDialog(playerid, DIALOGID_DEALERSHIP, DIALOG_STYLE_MSGBOX, "Dealership Car", string, "Select", "Cancel");
					}
					case ACTION_PICK_GUN_DMV: {
						format(string, MAXO_TEXT, "Do you want to start Gun Training?\n First time cost is $10.000\nIf you win, you'll have to pay extra $10.000.\n\nRenewal cost: $%s",(gDynPlayerInfo[playerid][pGunLicType] == 0) ? FormatNumber( PlayerInfo[playerid][pLevel]*1000 , 0, ',' ) : FormatNumber( PlayerInfo[playerid][pLevel]*1500 , 0, ',' ));
						ShowPlayerDialog(playerid, DIALOGID_DMV_WEAP, DIALOG_STYLE_MSGBOX, "DMV Test Authority", string, "Yes", "No");
					}
				}
			}
		}
		for(new i = 0; i < MAX_FACTIONS; i++) {
			if(IsPlayerInRangeOfPoint(playerid, 3.0, FactionInfo[i][fTREnterx], FactionInfo[i][fTREntery], FactionInfo[i][fTREnterz])) {
				format(string, MAXO_TEXT2, "%s", FactionInfo[i][fTextTR]);
				GameTextForPlayer(playerid, string, 5000, 3);
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, FactionInfo[i][fHQEnterx], FactionInfo[i][fHQEntery], FactionInfo[i][fHQEnterz])) {
				format(string, MAXO_TEXT2, "%s", FactionInfo[i][fText]);
				GameTextForPlayer(playerid, string, 5000, 3);
			}
		}
	}
	clear.string(string);
	return 1;
}

COMMAND:addpickup(playerid, params[]) {
	new
		string[MAXO_TEXT2+33], model, type, picktype, foraction;
	if(PlayerInfo[playerid][pAdmin] > 2) {
		if(!sscanf(params, "p<,>dddds[129]", model, type, picktype, foraction, params)) {
			if(strlen(params) < 129) {
				if(ISBetween(type, 0, 23)) {
					new Float:pPos[3];
					GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
					format(string, MAXO_TEXT2+33, "INSERT INTO pickups (Model, Type, PosX, PosY, PosZ, Interior, VirtualWorld, Text, PickupType, PickupForAction) VALUES ('%d', '%d', '%f', '%f', '%f', '%d', '%d', '%s', '%d', '%d')", model, type, pPos[0], pPos[1], pPos[2], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), params, picktype, foraction);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", PICKUP_THREAD_ID);
					SendClientMessage(playerid, COLOR_YELLOW, "[Pickups] "ALB"Pickup adaugat cu succes in baza de date.");
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid type pickup.");
			} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/addpickup [model] [type] [picktype] [pickforaction] [text]");
	} else NotAuthorized();
	return true;
}

// End Of File ...
