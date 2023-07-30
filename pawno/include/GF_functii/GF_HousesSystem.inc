/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_HousesSystem_included
	#endinput
#else
	#define GF_HousesSystem_included
#endif

#define INVALID_VALUE_ID (-1)

enum hInfo {
	hSQLID,
	hDescription[MAX_PLAYER_NAME],
	Float:hEntrancex,
	Float:hEntrancey,
	Float:hEntrancez,
	Float:hExitx,
	Float:hExity,
	Float:hExitz,
	hOwner[MAX_PLAYER_NAME],
	hOwned,
	hInterior,
	hVirtualWorld,
	hLocked,
	hLevel,
	hPrice,
	hRentable,
	hRentPrice,
	hTakings,
	hHeal,
	hArmour,
	Text3D:hLabel,
	hPickup,
	Float:hCP[3]
};
#define MAX_HOUSES (51)
new HouseInfo[MAX_HOUSES][hInfo],
	PropertyString[MAXO_TEXT2],
	TotalHouseLoaded = -1,
	HouseIcon[MAX_HOUSES];

//=========================%<==============================
// (c) copyrighted
#tryinclude <GF_functii/GF_private/GF_HousesSystem-private>
//=========================%>==============================
	
#if !defined GF_HousesSystemPriv_included
	stock LoadHouses() {
		return true;
	}
	function LoadHousesThread() {
		return true;
	}
	function GetHouseSQLID(playerid, Float:range) {
		#pragma unused playerid
		#pragma unused range
		return false;
	}
	stock IsPlayerOwnerAHouse(playerid) {
		#pragma unused playerid
		return false;
	}
#endif

stock HouseLog(string[]) {
	format(string, MAXO_TEXT2, "INSERT INTO house_log (Action) VALUES ('%s')", string);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", ADDCHAT_THREAD_ID);
	clear.string(string);
	return true;
}

COMMAND:househelp(playerid, params[]) {
	if(IsPlayerOwnerAHouse(playerid)) {
		SendClientMessage(playerid, COLOR_GREEN, "______________________________________________________________________");
		SendClientMessage(playerid, -1, "*** House Help - type a command for more informations. ***");
		SendClientMessage(playerid, COLOR_GREY, "*** House Commands *** /buyhouse /sellhouse /rentroom /unrent /home /sellhouseto");
		SendClientMessage(playerid, COLOR_GREY, "*** /setrentprice /setrentable /evict /housewithdraw /evictall /renters");
		SendClientMessage(playerid, COLOR_GREEN, "______________________________________________________________________");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have a house to see the commands available.");
	return true;
}

COMMAND:buyhouse(playerid, params[]) {
	new
		string[MAXO_TEXT2], id = GetHouseSQLID(playerid, 3.0);
	if(PlayerInfo[playerid][pPhousekey] == 0) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			if(IsPlayerInRangeOfPoint(playerid, 3.0, HouseInfo[id][hEntrancex], HouseInfo[id][hEntrancey], HouseInfo[id][hEntrancez])) {
				if(PlayerInfo[playerid][pLevel] >= HouseInfo[id][hLevel]) {
					if(PlayerInfo[playerid][pAccount] >= HouseInfo[id][hPrice]) {
						if(HouseInfo[id][hOwned] == 0) {
							if(HaveVisibleCheckpoint(playerid))
								return SendClientMessage(playerid, COLOR_LIGHTRED, "You cannot enter in enter right now, because you have visible an checkpoint.");
							PlayerInfo[playerid][pAccount] -= HouseInfo[id][hPrice];
							PlayerInfo[playerid][pPhousekey] = HouseInfo[id][hSQLID];
							PlayerInfo[playerid][pInHouseID] = HouseInfo[id][hSQLID];
							HouseInfo[id][hOwned] = 1;
							HouseInfo[id][hRentable] = 1;
							strmid(HouseInfo[id][hOwner], PlayerName(playerid), 0, strlen(PlayerName(playerid)), 255);
							format(string, 37, "Inside %s's House.", HouseInfo[id][hOwner]);
							TextDrawSetString(propertytxt, string);
							TextDrawShowForPlayer(playerid, propertytxt);
							SafeSetPlayerPos(playerid, HouseInfo[id][hExitx], HouseInfo[id][hExity], HouseInfo[id][hExitz]);
							SafeSetPlayerInterior(playerid, HouseInfo[id][hInterior]);
							SafeSetPlayerVirtualWorld(playerid, HouseInfo[id][hVirtualWorld]+1000);
							format(string, MAXO_TEXT2, "UPDATE players SET Account = %d, Phousekey = %d WHERE ID = %d", PlayerInfo[playerid][pAccount], PlayerInfo[playerid][pPhousekey], PlayerInfo[playerid][pSQLID]);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT2, "UPDATE houses SET Owner = '%s', Owned = %d, Rentable = %d WHERE ID = %d", HouseInfo[id][hOwner], HouseInfo[id][hOwned], HouseInfo[id][hRentable], HouseInfo[id][hSQLID]);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
							#if defined _stream_pickups
								DestroyDynamicPickup(HouseInfo[id][hPickup]);
								HouseInfo[id][hPickup] = CreateDynamicPickup(1272, 23, HouseInfo[PlayerInfo[playerid][pInHouseID]][hEntrancex], HouseInfo[PlayerInfo[playerid][pInHouseID]][hEntrancey], HouseInfo[PlayerInfo[playerid][pInHouseID]][hEntrancez],-1);
							#else
								DestroyPickup(HouseInfo[PlayerInfo[playerid][pInHouseID]][hPickup]);
								HouseInfo[PlayerInfo[playerid][pInHouseID]][hPickup] = CreatePickup(1272, 23, HouseInfo[id][hEntrancex], HouseInfo[id][hEntrancey], HouseInfo[id][hEntrancez],-1);
							#endif
							format(PropertyString, MAXO_TEXT2, "House available for rent!\nOwner: %s\nLevel: %d\nRent Price: $%s\nTo Rent Type /rentroom", HouseInfo[id][hOwner], HouseInfo[id][hLevel], FormatNumber(HouseInfo[id][hRentPrice], 0, '.'));
							Update3DTextLabelText(HouseInfo[id][hLabel], COLOR_PROPERTY, PropertyString);
							GameTextForPlayer(playerid, "~w~ Welcome ~n~ You can exit at any time by moving to this door and press ~g~ENTER", 5000, 3);
							format(string, MAXO_TEXT, "* Congratulations %s, for your new purchase in value of $%s.", PlayerName(playerid), FormatNumber(HouseInfo[id][hPrice], 0, '.'));
							SendClientMessage(playerid, -1, string);
							SendClientMessage(playerid, -1, "* Type "ROSU"/househelp "ALB"to view the commands available for your purchase.");
							new log[MAXO_TEXT2];
							format(log, MAXO_TEXT2, "%s bought the house with ID %d at a price of $%s.", PlayerName(playerid), HouseInfo[id][hSQLID], FormatNumber(HouseInfo[id][hPrice], 0, '.'));
							InsertLogInPanel(playerid, LOG_HOUSES, log);
							clear.string(PropertyString);
							clear.string(string);
							clear.string(log);
						} else SendClientMessage(playerid, COLOR_GRAD1, "This house is already owned of someone.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot purchase this house, because you don't have enough money in bank.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot purchase this house, because your level is lower.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You are not in front of a house.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must be pedestrian for this action.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are already owner of a house.");
	return true;
}

COMMAND:sellhouse(playerid, params[]) {
	new
		string[MAXO_TEXT2], casa = PlayerInfo[playerid][pPhousekey];
	if(IsPlayerInRangeOfPoint(playerid, 3.0, HouseInfo[casa][hEntrancex], HouseInfo[casa][hEntrancey], HouseInfo[casa][hEntrancez])) {
		if(IsPlayerOwnerAHouse(playerid)) {
			strmid(HouseInfo[casa][hOwner], "The State", 0, strlen("The State"), 255);
			HouseInfo[casa][hOwned] = 0;
			HouseInfo[casa][hLocked] = 1;
			HouseInfo[casa][hRentable] = 1;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			GameTextForPlayer(playerid, "~w~Congratulations ~n~ You have sold that property", 10000, 3);
			format(string, MAXO_TEXT2, "UPDATE houses SET Owner = '%s', Owned = %d WHERE ID = %d", HouseInfo[casa][hOwned], HouseInfo[casa][hSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
			format(string, MAXO_TEXT2, "UPDATE houses SET Locked = %d, Rentable = %d WHERE ID = %d", HouseInfo[casa][hLocked], HouseInfo[casa][hRentable], HouseInfo[casa][hSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
			format(string, MAXO_TEXT2, "UPDATE players SET Phousekey = 0 WHERE Phousekey = %d", PlayerInfo[playerid][pPhousekey]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			#if defined _stream_pickups
				DestroyDynamicPickup(HouseInfo[casa][hPickup]);
				HouseInfo[casa][hPickup] = CreateDynamicPickup(1273, 23, HouseInfo[casa][hEntrancex], HouseInfo[casa][hEntrancey], HouseInfo[casa][hEntrancez],-1);
			#else
				DestroyPickup(HouseInfo[casa][hPickup]);
				HouseInfo[casa][hPickup] = CreatePickup(1273, 23, HouseInfo[casa][hEntrancex], HouseInfo[casa][hEntrancey], HouseInfo[casa][hEntrancez],-1);
			#endif
			format(PropertyString, MAXO_TEXT2, "This house is available to buy!\nOwner: %s\nLevel: %d, Price: $%s\nDescription: %s\nTo buy /buyhouse", HouseInfo[casa][hOwner], HouseInfo[casa][hLevel], FormatNumber(HouseInfo[casa][hPrice], 0, '.'), HouseInfo[casa][hDescription]);
			Update3DTextLabelText(HouseInfo[casa][hLabel], COLOR_PROPERTY_NONE, PropertyString);
			foreach(Player, i) {
				if(PlayerInfo[i][pPhousekey] == casa) {
					if(IsPlayerInRangeOfPoint(i, 40, HouseInfo[casa][hExitx], HouseInfo[casa][hExity], HouseInfo[casa][hExitz])) {
						SafeSetPlayerPos(i, HouseInfo[casa][hEntrancex], HouseInfo[casa][hEntrancey], HouseInfo[casa][hEntrancez]);
						SafeSetPlayerInterior(i, 0);
						SafeSetPlayerVirtualWorld(i, 0);
						PlayerInfo[i][pInHouseID] = 0;
						TextDrawHideForPlayer(i, propertytxt);
						DeleteCP(checkpointHouse, i);
					}
					PlayerInfo[i][pPhousekey] = 0;
					SendClientMessage(i, -1, "You have been evicted from your house.");
				}
			}
			new log[MAXO_TEXT];
			format(log, MAXO_TEXT2, "%s a vandut casa cu ID-ul %d cu suma $1.", PlayerName(playerid), HouseInfo[casa][hSQLID]);
			HouseLog(log);
			clear.string(string);
			clear.string(PropertyString);
			clear.string(log);
		} else NotAuthorized();
	} else SendClientMessage(playerid, COLOR_GRAD1, "You're not standing at your house entrance.");
	return true;
}

COMMAND:rentroom(playerid, params[]) {
	new
		string[MAXO_TEXT], id = GetHouseSQLID(playerid, 3.0);
	if(!IsPlayerOwnerAHouse(playerid)) {
		if(PlayerInfo[playerid][pPhousekey] == 0) {
			if(IsPlayerInRangeOfPoint(playerid, 3.0, HouseInfo[id][hEntrancex], HouseInfo[id][hEntrancey], HouseInfo[id][hEntrancez])) {
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
					if(HouseInfo[id][hRentable] != 0 && HouseInfo[id][hOwned] == 1) {
						if(PlayerInfo[playerid][pCash] >= HouseInfo[id][hRentPrice]) {
							if(HaveVisibleCheckpoint(playerid))
								return SendClientMessage(playerid, COLOR_LIGHTRED, "You cannot enter in house right now, because you have visible an checkpoint.");
							PlayerInfo[playerid][pPhousekey] = id;
							PlayerInfo[playerid][pInHouseID] = id;
							SafeGivePlayerMoney(playerid, -HouseInfo[id][hRentPrice]);
							HouseInfo[id][hTakings] += HouseInfo[id][hRentPrice];
							format(string, MAXO_TEXT, "UPDATE players SET Phousekey = %d, Cash = %d WHERE ID = %d", PlayerInfo[playerid][pPhousekey], PlayerInfo[playerid][pCash], PlayerInfo[playerid][pSQLID]);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "UPDATE houses SET Takings = %d WHERE ID = %d", HouseInfo[id][hTakings], HouseInfo[id][hSQLID]);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
							SafeSetPlayerPos(playerid, HouseInfo[id][hExitx], HouseInfo[id][hExity], HouseInfo[id][hExitz]);
							SafeSetPlayerInterior(playerid, HouseInfo[id][hInterior]);
							SafeSetPlayerVirtualWorld(playerid, HouseInfo[id][hVirtualWorld]+1000);
							format(string, 37, "Inside %s's house.", HouseInfo[id][hOwner]);
							TextDrawSetString(propertytxt, string);
							TextDrawShowForPlayer(playerid, propertytxt);
							SendClientMessage(playerid, -1, "{33CCFF}Congratulations. {FFFFFF}You can enter and exit here anytime.");
							SendClientMessage(playerid, -1, "{33CCFF}/help {FFFFFF}to review the new property help section.");
							SendClientMessage(playerid, -1, "{33CCFF}NOTE: {FFFFFF}You will pay rent at each payday.");
							SendClientMessage(playerid, -1, "{33CCFF}ANTIABUSE: {FFFFFF}House owner will get 90 %% of the rent ONLY at payday time.");
							clear.string(string);
						} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have enough money to rent this house.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This house not is for rent or not is owned by someone.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You must be pedestrian for this action.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in front a house for this action.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You have already rent somewhere, type /unrent first.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are owner of a house, so cannot rent a house.");
	return true;
}

COMMAND:unrent(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(!IsPlayerOwnerAHouse(playerid)) {
		if(PlayerInfo[playerid][pPhousekey] != 0) {
			new
				casa = PlayerInfo[playerid][pPhousekey];
			if(IsPlayerInRangeOfPoint(playerid, 40, HouseInfo[casa][hExitx], HouseInfo[casa][hExity], HouseInfo[casa][hExitz])) {
				SafeSetPlayerPos(playerid, HouseInfo[casa][hEntrancex], HouseInfo[casa][hEntrancey], HouseInfo[casa][hEntrancez]);
				SafeSetPlayerInterior(playerid, 0);
				SafeSetPlayerVirtualWorld(playerid, 0);
				SendClientMessage(playerid, -1, "* You was been evicted automatically, because now you not renter.");
				TextDrawHideForPlayer(playerid, propertytxt);
				PlayerInfo[playerid][pInHouseID] = 0;
			}
			PlayerInfo[playerid][pPhousekey] = 0;
			format(string, MAXO_TEXT, "UPDATE players SET Phousekey = 0 WHERE ID = %d", PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			SendClientMessage(playerid, -1, "* You are now homeless, if you want to be renter to go in front a house and type "ALBASTRU2"/rentroom");
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You are not renter, cannot use this command.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You can not give up rent because you are the owner of this house.");
	return true;
}

COMMAND:setrentable(playerid, params[]) {
	new
		string[MAXO_TEXT], casa = PlayerInfo[playerid][pPhousekey], value;
	if(IsPlayerOwnerAHouse(playerid)) {
		if(!sscanf(params, "d", value)) {
			if(IsPlayerInRangeOfPoint(playerid, 3.0, HouseInfo[casa][hEntrancex], HouseInfo[casa][hEntrancey], HouseInfo[casa][hEntrancez])) {
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
					if(ISBetween(value, 0, 1)) {
						switch(value) {
							case 0: format(PropertyString, MAXO_TEXT2, "This house is owned by %s\nLevel: %d\nNot available for rent!", HouseInfo[casa][hOwner], HouseInfo[casa][hLevel]);
							case 1: format(PropertyString, MAXO_TEXT2, "House available for rent!\nOwner: %s\nLevel: %d, Rent Price: $%s\nTo Rent Type /rentroom", HouseInfo[casa][hOwner], HouseInfo[casa][hLevel], FormatNumber(HouseInfo[casa][hRentPrice], 0, '.'));
						}
						Update3DTextLabelText(HouseInfo[casa][hLabel], COLOR_PROPERTY, PropertyString);
						HouseInfo[casa][hRentable] = value;
						format(string, MAXO_TEXT, "UPDATE houses SET Rentable = %d WHERE ID = %d", HouseInfo[casa][hRentable], HouseInfo[casa][hSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
						format(string, MAXO_TEXT, "* Now, your house %s for rent, Price: $%s.", (value ? "is" : "is not"), FormatNumber(HouseInfo[casa][hRentPrice], 0, '.'));
						SendClientMessage(playerid, COLOR_YELLOW, string);
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "The values must be between 0-1.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You must be pedestrian for this action.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in front a house to use this command.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/setrentable [value(0-1)]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command, because you don't own a house.");
	return true;
}

COMMAND:setrentprice(playerid, params[]) {
	new
		string[MAXO_TEXT], value, casa = PlayerInfo[playerid][pPhousekey];
	if(IsPlayerOwnerAHouse(playerid)) {
		if(!sscanf(params, "d", value)) {
			if(IsPlayerInRangeOfPoint(playerid, 3.0, HouseInfo[casa][hEntrancex], HouseInfo[casa][hEntrancey], HouseInfo[casa][hEntrancez])) {
				if(ISBetween(value, 1, 5000)) {
					if(HouseInfo[casa][hRentable]) {
						HouseInfo[casa][hRentPrice] = value;
						format(PropertyString, MAXO_TEXT2, "House available for rent!\nOwner: %s\nLevel: %d, Rent Price: $%s\nTo Rent Type /rentroom", HouseInfo[casa][hOwner], HouseInfo[casa][hLevel], FormatNumber(HouseInfo[casa][hRentPrice], 0, '.'));
						Update3DTextLabelText(HouseInfo[casa][hLabel], COLOR_PROPERTY, PropertyString);
						format(string, MAXO_TEXT, "UPDATE houses SET RentPrice = %d WHERE ID = %d", HouseInfo[casa][hRentPrice], HouseInfo[casa][hSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
						format(string, MAXO_TEXT, "* You set the rent price $%s, now the players can use /rentroom", FormatNumber(HouseInfo[casa][hRentPrice], 0, '.'));
						SendClientMessage(playerid, COLOR_YELLOW, string);
						for(new i = 0; i < MAX_PLAYERS; i ++) {
							format(string, sizeof(string), "NOTICE: Owner %s has set house rent to a new value of: $%s", PlayerName(playerid), FormatNumber(HouseInfo[casa][hRentPrice], 0, '.' ));
							SendClientMessage(i, -1, string);
							break;
						}
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "Your house not is for rent, use /setrentable first.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "The price must be between $1-$5.000.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in front a house to use this command.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/setrentprice [price($1-$5.000)]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command, because you don't own a house.");
	return true;
}

COMMAND:housewithdraw(playerid, params[]) {
	new
		string[MAXO_TEXT], casa = PlayerInfo[playerid][pPhousekey], value;
	if(IsPlayerOwnerAHouse(playerid)) {
		if(!sscanf(params, "d", value)) {
			if(IsPlayerInRangeOfPoint(playerid, 3.0, HouseInfo[casa][hEntrancex], HouseInfo[casa][hEntrancey], HouseInfo[casa][hEntrancez])) {
				if(ISBetween(value, 1, HouseInfo[casa][hTakings])) {
					HouseInfo[casa][hTakings] -= value;
					SafeGivePlayerMoney(playerid, value);
					ConsumingMoney[playerid] = 1;
					format(string, MAXO_TEXT, "UPDATE houses SET Takings = %d WHERE ID = %d", HouseInfo[casa][hTakings], HouseInfo[casa][hSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
					format(string, MAXO_TEXT, "You has withdrawn $%s from your cashbox. Remain: $%s", FormatNumber(value, 0, '.'), FormatNumber(HouseInfo[casa][hTakings], 0, '.'));
					SendClientMessage(playerid, -1, string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have this amount in your cashbox.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in front a house to use this command.");
		} 
		else 
		{
			SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/housewithdraw [amount]");
			format(string, MAXO_TEXT, "You have $%s in your cashbox.", FormatNumber(HouseInfo[casa][hTakings], 0, '.'));
			SendClientMessage(playerid, COLOR_GREY, string);
		}
		clear.string(string);
	} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command, because you don't own a house.");
	return true;
}

COMMAND:evict(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid, oldhouse;
	if(IsPlayerOwnerAHouse(playerid)) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(PlayerInfo[targetid][pPhousekey] == PlayerInfo[playerid][pPhousekey]) {
					if(playerid == targetid)
						return SendClientMessage(playerid, COLOR_GRAD1, "You can not evict yourself.");
					oldhouse = PlayerInfo[targetid][pPhousekey];
					if(IsPlayerInRangeOfPoint(targetid, 40, HouseInfo[oldhouse][hExitx], HouseInfo[oldhouse][hExity], HouseInfo[oldhouse][hExitz])) {
						SafeSetPlayerPos(targetid, HouseInfo[oldhouse][hEntrancex], HouseInfo[oldhouse][hEntrancey], HouseInfo[oldhouse][hEntrancez]);
						SafeSetPlayerInterior(targetid, 0);
						SafeSetPlayerVirtualWorld(targetid, 0);
						TextDrawHideForPlayer(targetid, propertytxt);
						PlayerInfo[targetid][pInHouseID] = 0;
						DeleteCP(checkpointHouse, targetid);
					}
					PlayerInfo[targetid][pPhousekey] = 0;
					format(string, MAXO_TEXT, "UPDATE players SET Phousekey = 0 WHERE ID = %d", PlayerInfo[targetid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					format(string, MAXO_TEXT, "NOTICE: You has been evicted by Owner: %s.", PlayerName(playerid));
					SendClientMessage(targetid, -1, string);
					format(string, MAXO_TEXT, "* You evicted on %s, because you do not want to be a renter.", PlayerName(targetid));
					SendClientMessage(playerid, -1, string);
					PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "That player not is in rent at your house.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/evict [playerid/PartOfName]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command, because you don't own a house.");
	return true;
}

COMMAND:evictall(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(IsPlayerOwnerAHouse(playerid)) {
		for(new i = 0; i < MAX_PLAYERS; i ++) {
			if(PlayerInfo[i][pPhousekey] == PlayerInfo[playerid][pPhousekey]) {
				if(i != playerid) {
					if(IsPlayerInRangeOfPoint(i, 40, HouseInfo[PlayerInfo[i][pPhousekey]][hExitx], HouseInfo[PlayerInfo[i][pPhousekey]][hExity], HouseInfo[PlayerInfo[i][pPhousekey]][hExitz])) {
						SafeSetPlayerPos(i, HouseInfo[PlayerInfo[i][pPhousekey]][hEntrancex], HouseInfo[PlayerInfo[i][pPhousekey]][hEntrancey], HouseInfo[PlayerInfo[i][pPhousekey]][hEntrancez]);
						SafeSetPlayerInterior(i, 0);
						SafeSetPlayerVirtualWorld(i, 0);
						TextDrawHideForPlayer(i, propertytxt);
						DeleteCP(checkpointHouse, i);
					}
					PlayerInfo[i][pPhousekey] = 0;
					PlayerInfo[i][pInHouseID] = 0;
					format(string, MAXO_TEXT, "UPDATE players SET Phousekey = 0 WHERE Phousekey = %d", PlayerInfo[i][pPhousekey]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					format(string, MAXO_TEXT, "NOTICE: You has been evicted by Owner: %s.", PlayerName(playerid));
					SendClientMessage(i, -1, string);
				}
			}
		} 
		SendClientMessage(playerid, COLOR_WHITE, "* You has evicted all renters from your house.");
		clear.string(string);
	} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command, because you don't own a house.");
	return true;
}

COMMAND:renters(playerid, params[]) {
	new
		string[MAXO_TEXT], count = 0;
	if(IsPlayerOwnerAHouse(playerid)) {
		SendClientMessage(playerid, -1, "|____________ Online Renters ____________|");
		foreach(Player, i) {
			if(gPlayerLogged{i}) {
				if(PlayerInfo[i][pPhousekey] == PlayerInfo[playerid][pPhousekey] && i != playerid) {
					count ++;
					format(string, MAXO_TEXT, "* Name - [%d]%s", i, PlayerName(i));
					SendClientMessage(playerid, COLOR_GREY, string);
				}
				if(count == INVALID_PLAYER_ID)
					return SendClientMessage(playerid, COLOR_GRAD1, "In this momment not is any renter online.");
			}
		}
		clear.string(string);
	} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command, because you don't own a house.");
	return true;
}

COMMAND:home(playerid, params[]) {
	new
		casa = PlayerInfo[playerid][pPhousekey];
	if(casa) {
		if(GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0) {
			if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
				if(!HaveVisibleCheckpoint(playerid)) {
					CreateCP(playerid,HouseInfo[casa][hEntrancex],HouseInfo[casa][hEntrancey],HouseInfo[casa][hEntrancez],3.0,checkpointNoAction,CP_NO_ACTION);
					GameTextForPlayer(playerid, "~w~Waypoint set ~r~ Home", 5000, 1);
				} else SendClientMessage(playerid, COLOR_GRAD1, "You have already an checkpoint active.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must be pedestrian for this action.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command from an interior.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not renter.");
	return true;
}

COMMAND:asellhouse(playerid, params[]) {
	new
		string[MAXO_TEXT], id = GetHouseSQLID(playerid, 3.0);
	if(PlayerInfo[playerid][pAdmin] > 3) {
		if(IsPlayerInRangeOfPoint(playerid, 3.0, HouseInfo[id][hEntrancex], HouseInfo[id][hEntrancey], HouseInfo[id][hEntrancez])) {
			HouseInfo[id][hOwned] = 0;
			strmid(HouseInfo[id][hOwner], "The State", 0, strlen("The State"), 255);
			format(string, MAXO_TEXT, "UPDATE houses SET Owner = '%s', Owned = %d WHERE ID = %d", HouseInfo[id][hOwner], HouseInfo[id][hOwned], HouseInfo[id][hSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			#if defined _stream_pickups
				DestroyDynamicPickup(HouseInfo[id][hPickup]);
				HouseInfo[id][hPickup] = CreateDynamicPickup(1273, 23, HouseInfo[id][hEntrancex], HouseInfo[id][hEntrancey], HouseInfo[id][hEntrancez],-1);
			#else
				DestroyPickup(HouseInfo[id][hPickup]);
				HouseInfo[id][hPickup] = CreatePickup(1273, 23, HouseInfo[id][hEntrancex], HouseInfo[id][hEntrancey], HouseInfo[id][hEntrancez],-1);
			#endif
			format(PropertyString, MAXO_TEXT2, "This house is available to buy!\nOwner: %s\nLevel: %d, Price: $%s\nDescription: %s\nTo buy /buyhouse", HouseInfo[id][hOwner], HouseInfo[id][hLevel], FormatNumber(HouseInfo[id][hPrice], 0, '.'), HouseInfo[id][hDescription]);
			Update3DTextLabelText(HouseInfo[id][hLabel], COLOR_PROPERTY_NONE, PropertyString);
			for(new i = 0; i < MAX_PLAYERS; i ++) {
				if(PlayerInfo[i][pPhousekey] == id) {
					if(IsPlayerInRangeOfPoint(i, 40, HouseInfo[id][hExitx], HouseInfo[id][hExity], HouseInfo[id][hExitz])) {
						SafeSetPlayerPos(i, HouseInfo[id][hEntrancex], HouseInfo[id][hEntrancey], HouseInfo[id][hEntrancez]);
						TextDrawHideForPlayer(i, propertytxt);
						SafeSetPlayerInterior(i, 0);
						SafeSetPlayerVirtualWorld(i, 0);
						PlayerInfo[i][pInHouseID] = 0;
					}
					PlayerInfo[i][pPhousekey] = 0;
					SendClientMessage(i, -1, "You have been evicted from your house.");
					format(string, MAXO_TEXT, "UPDATE players SET Phousekey = 0 WHERE Phousekey = %d", HouseInfo[id][hSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				}
				break;
			}
			format(string, MAXO_TEXT, "UPDATE players SET Phousekey = 0 WHERE Phousekey = %d", HouseInfo[id][hSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			GameTextForPlayer(playerid, "~w~Congratulations ~n~ You have sold that property", 10000, 3);
			new log[MAXO_TEXT];
			format(log, MAXO_TEXT2, "Adminul %s a vandut casa cu ID-ul %d cu suma $1.", PlayerName(playerid), HouseInfo[id][hSQLID]);
			HouseLog(log);
			clear.string(string);
			clear.string(PropertyString);
			clear.string(log);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in front a house.");
	} else NotAuthorized();
	return true;
}

COMMAND:sellhouseto(playerid, params[]) {
	new string[MAXO_TEXT], targetid, amount;
	if(IsPlayerOwnerAHouse(playerid)) {
		if(!sscanf(params, "s[24]d", PartialName[playerid][nume_introdus], amount)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(PlayerInfo[targetid][pLevel] >= HouseInfo[PlayerInfo[playerid][pPhousekey]][hLevel]) {
						if(PlayerInfo[targetid][pAccount] >= amount) {
							if(GetDistanceBetweenPlayers(playerid, targetid) < 4) {
								format(string, MAXO_TEXT, "* %s wants to sell you his house for $%s, (type /accept %d house) to buy.", PlayerName(playerid), FormatNumber(amount, 0, '.'), playerid);
								SendClientMessage(targetid, COLOR_FAMILY, string);
								format(string, MAXO_TEXT, "* You offered %s your house at the price of $%s.", PlayerName(targetid), FormatNumber(amount, 0, '.'));
								SendClientMessage(playerid, COLOR_FAMILY, string);
								PropertyOffer[targetid] = playerid;
								PropertyPrice[targetid] = amount;
								PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
								clear.string(string);
							} else SendClientMessage(playerid, COLOR_GRAD1, "This player is too far away from you.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "This player not have enough money to buy the house from you.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not have the level necessary to buy the house from you.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can't sell the house yourself.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/sellhouseto [playerid/PartOfName] [price]");
	} else NotAuthorized();
	return true;
}

COMMAND:gotohouse(playerid, params[]) {
	new
		string[MAXO_TEXT], id;
	if(PlayerInfo[playerid][pAdmin] > 3) {
		if(!sscanf(params, "d", id)) {
			if(ISBetween(id, 1, MAX_HOUSES-1)) {
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
					new factiune = PlayerInfo[playerid][pFactiune];
					SetSpawnInfo(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pSkin], HouseInfo[id][hEntrancex], HouseInfo[id][hEntrancey], HouseInfo[id][hEntrancez]+0.3, 0, FactionInfo[factiune][fWeapon1], FactionInfo[factiune][fAmmo1], FactionInfo[factiune][fWeapon2], FactionInfo[factiune][fAmmo2], FactionInfo[factiune][fWeapon3], FactionInfo[factiune][fAmmo3]);
					SpawnPlayer(playerid);
					if(IsPlayerInInside(playerid))
						SafeSetPlayerInterior(playerid, 0),
						SafeSetPlayerVirtualWorld(playerid, 0);
					GameTextForPlayer(playerid, "~g~Teleporting...", 3000, 1);
					format(string, MAXO_TEXT, "* You have been teleported at house with SQLID %d.", HouseInfo[id][hSQLID]);
					SendClientMessage(playerid, COLOR_LIGHTRED, string);
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "You must be pedestrian for this action.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid houseid.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/gotohouse [house id]");
	} else NotAuthorized();
	return true;
}

COMMAND:createhouse(playerid, params[]) {
	new
		Float:iPos[3], interior, price, level;
	if(IsPlayerFounder(playerid)) {
		if(!sscanf(params, "p<,>fffddd", iPos[0], iPos[1], iPos[2], interior, price, level)) {
			if(ISBetween(price, 1, 1000000)) {
				if(ISBetween(level, 2, 15)) {
					TotalHouseLoaded ++;
					new
						virtual_world = TotalHouseLoaded, Float:pPos[3], string[300],
						casa = TotalHouseLoaded;
					GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
					if(pPos[0] == 0 && pPos[1] == 0 && pPos[2] == 0)
						return SendClientMessage(playerid, COLOR_LIGHTRED, "You cannot create a new biz, because don't was founded the coords.");
					HouseInfo[casa][hEntrancex] = pPos[0];
					HouseInfo[casa][hEntrancey] = pPos[1];
					HouseInfo[casa][hEntrancez] = pPos[2];
					HouseInfo[casa][hExitx] = iPos[0];
					HouseInfo[casa][hExity] = iPos[1];
					HouseInfo[casa][hExitz] = iPos[2];
					strmid(HouseInfo[casa][hOwner], "The_State", 0, strlen("The_State"), 255);
					strmid(HouseInfo[casa][hDescription], "Apartment Luxury", 0, strlen("Apartment Luxury"), 255);
					HouseInfo[casa][hOwned] = 0;
					HouseInfo[casa][hLocked] = 1;
					HouseInfo[casa][hInterior] = interior;
					HouseInfo[casa][hVirtualWorld] = virtual_world+1;
					HouseInfo[casa][hRentable] = 1;
					HouseInfo[casa][hRentPrice] = 1;
					HouseInfo[casa][hTakings] = 0;
					HouseInfo[casa][hLevel] = level;
					HouseInfo[casa][hPrice] = price;
					format(string, MAXO_TEXT2+44, "INSERT INTO houses (EnterX, EnterY, EnterZ, ExitX, ExitY, ExitZ, Interior, VirtualWorld, Level, Price) VALUES ('%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d')", HouseInfo[casa][hEntrancex], HouseInfo[casa][hEntrancey], HouseInfo[casa][hEntrancez], HouseInfo[casa][hExitx], HouseInfo[casa][hExity], HouseInfo[casa][hExitz], HouseInfo[casa][hInterior], HouseInfo[casa][hVirtualWorld], HouseInfo[casa][hLevel], HouseInfo[casa][hPrice]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
					format(PropertyString, MAXO_TEXT2, "This house is available to buy!\nOwner: %s\nLevel: %d, Price: $%s\nDescription: %s\nTo buy /buyhouse", HouseInfo[casa][hOwner], HouseInfo[casa][hLevel], FormatNumber(HouseInfo[casa][hPrice], 0, '.'), HouseInfo[casa][hDescription]);
					HouseInfo[casa][hLabel] = Create3DTextLabel(PropertyString, COLOR_PROPERTY_NONE, HouseInfo[casa][hEntrancex], HouseInfo[casa][hEntrancey], HouseInfo[casa][hEntrancez]+1, 25, 0, 1);
					#if defined _stream_pickups
						HouseInfo[casa][hPickup] = CreateDynamicPickup(1273, 23, HouseInfo[casa][hEntrancex], HouseInfo[casa][hEntrancey], HouseInfo[casa][hEntrancez]);
					#else
						HouseInfo[casa][hPickup] = CreatePickup(1273, 23, HouseInfo[casa][hEntrancex], HouseInfo[casa][hEntrancey], HouseInfo[casa][hEntrancez]);
					#endif
					clear.string(string);
					clear.string(PropertyString);
				} else SendClientMessage(playerid, COLOR_GRAD1, "The level must be between 2-15.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "The price must be between $1-$1.000.000.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/createhouse [iX] [iY] [iZ] [interior id] [price] [level]");
	} else NotAuthorized();
	return true;
}

// End Of File ...
