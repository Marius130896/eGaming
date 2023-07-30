/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_SafesSystems_included
	#endinput
#else
	#define GF_SafesSystem_included
#endif

enum seInfo {
	seifSQLID,
	Float:seifPos[3],
	seifDrugs,
	seifMaterials,
	seifMoney,
	seifVW,
	seifType
};
new SafeInfo[MAX_FACTIONS][seInfo], SafePickup;

#define SAFE_NONE_TYPE 0
#define SAFE_DRUGS_TYPE	1
#define SAFE_MATS_TYPE 2
#define SAFE_MONEYS_TYPE 3
#define SAFE_DRUGS_MATS_TYPE 4
#define SAFE_DRUGS_MONEY_TYPE 5
#define SAFE_MATS_MONEY_TYPE 6
#define SAFE_ALL_TYPE 7

stock LoadSafes() {
	mysql_tquery(connectionHandle, "SELECT * FROM safes", "LoadSafesThread", "d", SAFE_THREAD_ID);
	return true;
}

function LoadSafesThread() {
	rows = cache_num_rows();
	if(rows) {
		for(new i = 0; i < rows; i ++) {
			SafeInfo[i][seifSQLID] = cache_get_row_int(i, 0);
			SafeInfo[i][seifPos][0] = cache_get_row_float(i, 1);
			SafeInfo[i][seifPos][1] = cache_get_row_float(i, 2);
			SafeInfo[i][seifPos][2] = cache_get_row_float(i, 3);
			SafeInfo[i][seifDrugs] = cache_get_row_int(i, 4);
			SafeInfo[i][seifMaterials] = cache_get_row_int(i, 5);
			SafeInfo[i][seifMoney] = cache_get_row_int(i, 6);
			SafeInfo[i][seifVW] = cache_get_row_int(i, 7);
			SafeInfo[i][seifType] = cache_get_row_int(i, 8);

			#if defined _stream_pickups
				SafePickup = CreateDynamicPickup(1210, 2, SafeInfo[i][seifPos][0], SafeInfo[i][seifPos][1], SafeInfo[i][seifPos][2], SafeInfo[i][seifVW]);
			#else
				SafePickup = CreatePickup(1210, 2, SafeInfo[i][seifPos][0], SafeInfo[i][seifPos][1], SafeInfo[i][seifPos][2], SafeInfo[i][seifVW]);
			#endif
		}
		printf("LoadSafesThread() - called (%d safes loaded).", rows);
	}
	return true;
}

stock SafeOnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	if(dialogid == DIALOGID_SAFE_INFO) {
		if(response) {
			switch(listitem) {
				case 0: ShowPlayerDialog(playerid, DIALOGID_SAFE_DRUGS, DIALOG_STYLE_LIST, "Drugs Section", "1. Put Drugs\n2. Take Drugs", "Select", "Cancel");
				case 1: ShowPlayerDialog(playerid, DIALOGID_SAFE_MATERIALS, DIALOG_STYLE_LIST, "Materials Section", "1. Put Materials\n2. Take Materials", "Select", "Cancel");
				case 2: ShowPlayerDialog(playerid, DIALOGID_SAFE_MONEY, DIALOG_STYLE_LIST, "Money Section", "1. Put Money\n2. Take Money", "Select", "Cancel");
				case 3: {
					new
						string[MAXO_TEXT], fID = PlayerInfo[playerid][pFactiune];
					format(string, sizeof(string), "The balance of the faction's vault:\n\n* Drugs: %d\n* Materials: %d\n* Money: $%s", SafeInfo[fID][seifDrugs], SafeInfo[fID][seifMaterials], FormatNumber(SafeInfo[fID][seifMoney], 0, '.'));
					ShowPlayerDialog(playerid, DIALOGID_SAFE_BALANCE, DIALOG_STYLE_MSGBOX, "Safe Balance", string, "Ok", "Cancel");
					clear.string(string);
				}
			}
		}
	}
	else if(dialogid == DIALOGID_SAFE_DRUGS) {
		if(response) {
			switch(listitem) {
				case 0: ShowPlayerDialog(playerid, DIALOGID_SAFE_PUT_DRUGS, DIALOG_STYLE_INPUT, "Put Drugs Section", "Type the amount of drugs you want to deposit in the safe:", "Put", "Exit");
				case 1: ShowPlayerDialog(playerid, DIALOGID_SAFE_TAKE_DRUGS, DIALOG_STYLE_INPUT, "Take Drugs Section", "Type the amount of drugs you want to take in the safe:", "Take", "Exit");
			}
		}
	}
	else if(dialogid == DIALOGID_SAFE_MATERIALS) {
		if(response) {
			switch(listitem) {
				case 0: ShowPlayerDialog(playerid, DIALOGID_SAFE_PUT_MATERIALS, DIALOG_STYLE_INPUT, "Put Materials Section", "Type the amount of materials you want to deposit in the safe:", "Put", "Exit");
				case 1: ShowPlayerDialog(playerid, DIALOGID_SAFE_TAKE_MATERIALS, DIALOG_STYLE_INPUT, "Put Materials Section", "Type the amount of materials you want to take in the safe:", "Take", "Exit");
			}
		}
	}
	else if(dialogid == DIALOGID_SAFE_MONEY) {
		if(response) {
			switch(listitem) {
				case 0: ShowPlayerDialog(playerid, DIALOGID_SAFE_PUT_MONEY, DIALOG_STYLE_INPUT, "Put Money Section", "Type the amount of money you want to deposit in the safe:", "Put", "Exit");
				case 1: ShowPlayerDialog(playerid, DIALOGID_SAFE_TAKE_MONEY, DIALOG_STYLE_INPUT, "Put Money Section", "Type the amount of money you want to take in the safe:", "Take", "Exit");
			}
		}
	}
	else if(dialogid == DIALOGID_SAFE_PUT_DRUGS) {
		if(response) {
			new
				drugsdeposit = strval(inputtext), fID = PlayerInfo[playerid][pFactiune], string[MAXO_TEXT];
			if(drugsdeposit <= PlayerInfo[playerid][pDrugs]) {
				if(drugsdeposit + SafeInfo[fID][seifDrugs] <= 1000000) {
					if(SafeInfo[fID][seifType] == SAFE_DRUGS_TYPE || SafeInfo[fID][seifType] == SAFE_DRUGS_MATS_TYPE || SafeInfo[fID][seifType] == SAFE_DRUGS_MONEY_TYPE || SafeInfo[fID][seifType] == SAFE_ALL_TYPE) {
						PlayerInfo[playerid][pDrugs] -= drugsdeposit;
						SafeInfo[fID][seifDrugs] += drugsdeposit;

						format(string, sizeof(string), "UPDATE players SET Drugs = %d WHERE ID = %d", PlayerInfo[playerid][pDrugs], PlayerInfo[playerid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						format(string, sizeof(string), "UPDATE safes SET seifDrugs = %d WHERE ID = %d", SafeInfo[fID][seifDrugs], fID);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", SAFE_THREAD_ID);

						format(string, sizeof(string), "* You put %d grams of drugs in your faction safe.", drugsdeposit);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						format(string, sizeof(string),  "* %s puts %d grams of drugs in the faction safe. Remained: %d grams", PlayerName(playerid), drugsdeposit, SafeInfo[fID][seifDrugs]);
						SendFamilyMessage(COLOR_LIGHTBLUE, string, fID);
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot put the drugs in the safe, not is available.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "The safe is full of drugs. You cannot puts other quantity.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have this quantity at you.");
		}
	}
	else if(dialogid == DIALOGID_SAFE_TAKE_DRUGS) {
		if(response) {
			new
				drugstake = strval(inputtext), fID = PlayerInfo[playerid][pFactiune], string[MAXO_TEXT];
			if(drugstake <= SafeInfo[fID][seifDrugs]) {
				if(drugstake + PlayerInfo[playerid][pDrugs] <= 100) {
					if(SafeInfo[fID][seifType] == SAFE_DRUGS_TYPE || SafeInfo[fID][seifType] == SAFE_DRUGS_MATS_TYPE || SafeInfo[fID][seifType] == SAFE_DRUGS_MONEY_TYPE || SafeInfo[fID][seifType] == SAFE_ALL_TYPE) {
						PlayerInfo[playerid][pDrugs] += drugstake;
						SafeInfo[fID][seifDrugs] -= drugstake;

						format(string, sizeof(string), "UPDATE players SET Drugs = %d WHERE ID = %d", PlayerInfo[playerid][pDrugs], PlayerInfo[playerid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						format(string, sizeof(string), "UPDATE safes SET seifDrugs = %d WHERE ID = %d", SafeInfo[fID][seifDrugs], fID);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", SAFE_THREAD_ID);

						format(string, sizeof(string), "* You taken %d grams of drugs from the faction safe.", drugstake);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						format(string, sizeof(string), "* %s took %d grams of drugs from the faction safe. Remained: %d grams", PlayerName(playerid), drugstake, SafeInfo[fID][seifDrugs]);
						SendFamilyMessage(COLOR_LIGHTBLUE, string, fID);
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot take the drugs from this safe.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot take much more of 100 grams of drugs from this safe.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "This quantity cannot be taken from this safe.");
		}
	}
	else if(dialogid == DIALOGID_SAFE_PUT_MATERIALS) {
		if(response) {
			new
				materialsdeposit = strval(inputtext), fID = PlayerInfo[playerid][pFactiune], string[MAXO_TEXT];
			if(materialsdeposit <= PlayerInfo[playerid][pMats]) {
				if(materialsdeposit + SafeInfo[fID][seifMaterials] <= 1000000) {
					if(SafeInfo[fID][seifType] == SAFE_MATS_TYPE || SafeInfo[fID][seifType] == SAFE_DRUGS_MATS_TYPE || SafeInfo[fID][seifType] == SAFE_MATS_MONEY_TYPE || SafeInfo[fID][seifType] == SAFE_ALL_TYPE) {
						PlayerInfo[playerid][pMats] -= materialsdeposit;
						SafeInfo[fID][seifMaterials] += materialsdeposit;

						format(string, sizeof(string), "UPDATE players SET Materials = %d WHERE ID = %d", PlayerInfo[playerid][pMats], PlayerInfo[playerid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						format(string, sizeof(string), "UPDATE safes SET seifMaterials = %d WHERE ID = %d", SafeInfo[fID][seifMaterials], fID);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", SAFE_THREAD_ID);

						format(string, sizeof(string), "* You put %d materials in your faction safe.", materialsdeposit);
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						format(string, sizeof(string),  "* %s puts %d materials in the faction safe. Remained: %d materials", PlayerName(playerid), materialsdeposit, SafeInfo[fID][seifMaterials]);
						SendFamilyMessage(COLOR_LIGHTBLUE, string, fID);
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot puts the materials from this safe.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "The safe is full of materials. You cannot puts other quantity.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have this quantity of materials at you.");
		}
	}
	else if(dialogid == DIALOGID_SAFE_TAKE_MATERIALS) {
		if(response) {
			new
				materialstake = strval(inputtext), fID = PlayerInfo[playerid][pFactiune], string[MAXO_TEXT];
			if(materialstake <= SafeInfo[fID][seifMaterials]) {
				if(SafeInfo[fID][seifType] == SAFE_MATS_TYPE || SafeInfo[fID][seifType] == SAFE_DRUGS_MATS_TYPE || SafeInfo[fID][seifType] == SAFE_MATS_MONEY_TYPE || SafeInfo[fID][seifType] == SAFE_ALL_TYPE) {
					PlayerInfo[playerid][pMats] += materialstake;
					SafeInfo[fID][seifMaterials] -= materialstake;

					format(string, sizeof(string), "UPDATE players SET Materials = %d WHERE ID = %d", PlayerInfo[playerid][pMats], PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					format(string, sizeof(string), "UPDATE safes SET seifMaterials = %d WHERE ID = %d", SafeInfo[fID][seifMaterials], fID);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", SAFE_THREAD_ID);

					format(string, sizeof(string), "* You taken %d materials in your faction safe.", materialstake);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					format(string, sizeof(string),  "* %s took %d materials in the faction safe. Remained: %d materials", PlayerName(playerid), materialstake, SafeInfo[fID][seifMaterials]);
					SendFamilyMessage(COLOR_LIGHTBLUE, string, fID);
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot take the materials from this safe.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot take this amount of materials from safe.");
		}
	}
	else if(dialogid == DIALOGID_SAFE_PUT_MONEY) {
		if(response) {
			new
				moneydeposit = strval(inputtext), fID = PlayerInfo[playerid][pFactiune], string[MAXO_TEXT];
			if(moneydeposit <= PlayerInfo[playerid][pCash]) {
				if(moneydeposit + SafeInfo[fID][seifMoney] <= 1000000) {
					if(SafeInfo[fID][seifMoney] <= 0) {
						if(SafeInfo[fID][seifType] == SAFE_MONEYS_TYPE || SafeInfo[fID][seifType] == SAFE_DRUGS_MONEY_TYPE || SafeInfo[fID][seifType] == SAFE_MATS_MONEY_TYPE || SafeInfo[fID][seifType] == SAFE_ALL_TYPE) {
							SafeGivePlayerMoney(playerid, -moneydeposit);
							SafeInfo[fID][seifMoney] += moneydeposit;
							ConsumingMoney[playerid] = 1;

							format(string, sizeof(string), "UPDATE safes SET seifMoney = %d WHERE ID = %d", SafeInfo[fID][seifMoney], fID);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", SAFE_THREAD_ID);

							format(string, sizeof(string), "* You put $%s cash in your faction safe.", FormatNumber(moneydeposit, 0, '.'));
							SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
							format(string, sizeof(string), "* %s puts $%s cash in the faction safe. Remained: $%s cash", PlayerName(playerid), FormatNumber(moneydeposit, 0, '.'), FormatNumber(SafeInfo[fID][seifMoney], 0, '.'));
							SendFamilyMessage(COLOR_LIGHTBLUE, string, fID);
							clear.string(string);
						} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot put the money in this safe.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "An error has been detected in your safe of money.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "The safe is full of money. You cannot puts other quantity.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have this amount at you.");
		}
	}
	else if(dialogid == DIALOGID_SAFE_TAKE_MONEY) {
		if(response) {
			new
				moneytake = strval(inputtext), fID = PlayerInfo[playerid][pFactiune], string[MAXO_TEXT];
			if(moneytake <= SafeInfo[fID][seifMoney]) {
				if(SafeInfo[fID][seifMoney] > 1) {
					if(SafeInfo[fID][seifType] == SAFE_MONEYS_TYPE || SafeInfo[fID][seifType] == SAFE_DRUGS_MONEY_TYPE || SafeInfo[fID][seifType] == SAFE_MATS_MONEY_TYPE || SafeInfo[fID][seifType] == SAFE_ALL_TYPE) {
						if(PlayerInfo[playerid][pLeader] != FACT_CIVIL) {
							SafeGivePlayerMoney(playerid, moneytake);
							SafeInfo[fID][seifMoney] -= moneytake;

							format(string, sizeof(string), "UPDATE safes SET seifMoney = %d WHERE ID = %d", SafeInfo[fID][seifMoney], fID);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", SAFE_THREAD_ID);

							format(string, sizeof(string), "* You take $%s cash in your faction safe.", FormatNumber(moneytake, 0, '.'));
							SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
							format(string, sizeof(string), "* %s took $%s cash in the faction safe. Remained: $%s cash", PlayerName(playerid), FormatNumber(moneytake, 0, '.'), FormatNumber(SafeInfo[fID][seifMoney], 0, '.'));
							SendFamilyMessage(COLOR_LIGHTBLUE, string, fID);
							clear.string(string);
						} else NotAuthorized();
					} else SendClientMessage(playerid, COLOR_GRAD1, "In this safe can to take only money.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "In safe not exis this amount.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You can't to withdraw this amount from this safe.");
		}
	}
	return true;
}

// End Of File ...
