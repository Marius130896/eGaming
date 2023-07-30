/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/

#if defined GF_BusinessSystem_included
	#endinput
#else
	#define GF_BusinessSystem_included
#endif

#define MAX_BIZ_NAME (64)
enum bInfo {
	bSQLID,
	bDescription[MAX_BIZ_NAME],
	Float:bEntrancex,
	Float:bEntrancey,
	Float:bEntrancez,
	Float:bExitx,
	Float:bExity,
	Float:bExitz,
	bOwner[MAX_PLAYER_NAME],
	bOwned,
	bInterior,
	bVirtualWorld,
	bLevel,
	bPrice,
	bEnterPrice,
	bTakings,
	bType,
	Text3D:bLabel,
	bPickup,
	bProducts
};
#define MAX_BIZ (30)
new BizInfo[MAX_BIZ][bInfo],
	TotalBizLoaded = -1,
	BizIcon[MAX_BIZ];

#define MAX_PRODUCT_NAME 16
#define MAX_PRODUCTS 6

enum pretBurger {
	nrProdus,
	nameProdus[MAX_PRODUCT_NAME],
	pretProdus,
	Float:viataProdus
};
new PretBurgerInfo[MAX_PRODUCTS][pretBurger];

#define MAX_ITEMS 11

enum preItem {
	nrItem,
	pretItem,
	nameItem[MAX_PRODUCT_NAME]
};
new PretItemInfo[MAX_ITEMS][preItem];

//=========================%>================================
// (c) copyrighted 
#tryinclude <GF_functii/GF_private/GF_BusinessSystem-private>
//=========================<%================================

#if !defined GF_BusinessSystemPriv_included
	stock LoadBiz() {
		return true;
	}
	function LoadBizThread() {
		return true;
	}
	stock LoadProdsBurger() {
		return true;
	}
	function InitPrBurgerThread() {
		return true;
	}
	stock PlayerBuyFood(playerid, idfood) {
		return true;
	}
	stock LoadPrItemsThread() {
		return true;
	}
	function InitPrItemsThread() {
		return true;
	}
	stock PlayerBuyItem(playerid, itemid) {
		return true;
	}
	function GetBizSQLID(playerid, Float:range) {
		#pragma unused playerid
		#pragma unused range
		return false;
	}
	stock IsPlayerOwnerABiz(playerid) {
		#pragma unused playerid
		return false;
	}
	stock NuDeschideBiz(tipbiz) {
		#pragma unused tipbiz
		return false;
	}
#endif

stock BizLog(string[]) {
	format(string, MAXO_TEXT2, "INSERT INTO biz_log (Action) VALUES ('%s')", string);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", ADDCHAT_THREAD_ID);
	clear.string(string);
	return true;
}

COMMAND:bizhelp(playerid, params[]) {
	if(IsPlayerOwnerABiz(playerid)) {
		SendClientMessage(playerid, COLOR_GREEN, "______________________________________________________________________");
		SendClientMessage(playerid, -1, "*** Biz Help - type a command for more informations. ***");
		SendClientMessage(playerid, COLOR_GREY, "*** Biz Commands *** /sellbiztostate /bizwithdraw /setenterprice /sellbizto /mybizinfo /putmoneyinbiz");
		SendClientMessage(playerid, COLOR_GREEN, "______________________________________________________________________");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have a business to see the commands available.");
	return true;
}

COMMAND:buybiz(playerid, params[]) {
	new
		string[MAXO_TEXT2], id = GetBizSQLID(playerid, 3.0);
	if(!IsPlayerOwnerABiz(playerid)) {
		if(IsPlayerInRangeOfPoint(playerid, 3.0, BizInfo[id][bEntrancex], BizInfo[id][bEntrancey], BizInfo[id][bEntrancez])) {
			if(PlayerInfo[playerid][pLevel] >= BizInfo[id][bLevel]) {
				if(PlayerInfo[playerid][pAccount] >= BizInfo[id][bPrice]) {
					if(BizInfo[id][bOwned] == 0) {
						if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
							if(HaveVisibleCheckpoint(playerid))
								return SendClientMessage(playerid, COLOR_LIGHTRED, "You cannot enter in biz right now, because you have visible an checkpoint.");
							PlayerInfo[playerid][pPbizkey] = BizInfo[id][bSQLID];
							PlayerInfo[playerid][pAccount] -= BizInfo[id][bPrice];
							strmid(BizInfo[id][bOwner], PlayerName(playerid), 0, strlen(PlayerName(playerid)), 255);
							BizInfo[id][bOwned] = 1;
							if(!NuDeschideBiz(id)) {
								format(string, 64, "Inside %s's Biz.", BizInfo[id][bOwner]);
								TextDrawSetString(propertytxt, string);
								TextDrawShowForPlayer(playerid, propertytxt);
								SafeSetPlayerPos(playerid, BizInfo[id][bExitx], BizInfo[id][bExity], BizInfo[id][bExitz]);
								SafeSetPlayerInterior(playerid, BizInfo[id][bInterior]);
								SafeSetPlayerVirtualWorld(playerid, BizInfo[id][bVirtualWorld]+2000);
								PlayerInfo[playerid][pInBizzID] = id;
							}
							format(string, MAXO_TEXT2, "UPDATE players SET Pbizkey = %d, Account = %d WHERE ID = %d", PlayerInfo[playerid][pPbizkey], PlayerInfo[playerid][pAccount], PlayerInfo[playerid][pSQLID]);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT2, "UPDATE bizz SET Owner = '%s', Owned = %d WHERE ID = %d", BizInfo[id][bOwner], BizInfo[id][bOwned], BizInfo[id][bSQLID]);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
							format(PropertyString, MAXO_TEXT2, "Biz %s\nLevel: %d\nOwned by: %s\nEntrance: $%s\nPress ENTER to enter", BizInfo[id][bDescription], BizInfo[id][bLevel], BizInfo[id][bOwner], FormatNumber(BizInfo[id][bEnterPrice], 0, '.'));
							Update3DTextLabelText(BizInfo[id][bLabel], COLOR_PROPERTY, PropertyString);
							format(string, MAXO_TEXT, "* Congratulations "GALBEN"%s"ALB", for your new purchase in value of "VERDE"$"ALB"%s.", PlayerName(playerid), FormatNumber(BizInfo[id][bPrice], 0, '.'));
							SendClientMessage(playerid, -1, string);
							SendClientMessage(playerid, -1, "* Type "ROSU2"/bizhelp "ALB"to view the commands available for your purchase.");
							GameTextForPlayer(playerid, "~w~ Welcome ~n~ You can exit at any time by moving to this door and press ~g~ENTER", 5000, 3);
							new log[MAXO_TEXT2];
							format(log, MAXO_TEXT2, "%s bought the business with ID %d at a price of $%s.", PlayerName(playerid), BizInfo[id][bSQLID], FormatNumber(BizInfo[id][bPrice], 0, '.'));
							InsertLogInPanel(playerid, LOG_BUSINESS, log);
							clear.string(string);
							clear.string(PropertyString);
							clear.string(log);
						} else SendClientMessage(playerid, COLOR_GRAD1, "You must be pedestrian for this action.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This biz is already owned bv someone.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have the moneys necessary to buy this biz.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have the level necessary to buy this biz.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in front of biz.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot purchase this biz, because you have already a biz.");
	return true;
}

COMMAND:sellbiztostate(playerid, params[]) {
	new
		string[MAXO_TEXT2], id = PlayerInfo[playerid][pPbizkey];
	if(id) {
		if(IsPlayerInRangeOfPoint(playerid, 3.0, BizInfo[id][bEntrancex], BizInfo[id][bEntrancey], BizInfo[id][bEntrancez])) {
			strmid(BizInfo[id][bOwner], "The_State", 0, strlen("The_State"), 255);
			BizInfo[id][bOwned] = 0;
			PlayerInfo[playerid][pPbizkey] = 0;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			new pret = CalculateSellPrice(BizInfo[id][bPrice]);
			PlayerInfo[playerid][pAccount] += pret;
			format(string, MAXO_TEXT, "UPDATE players SET Account = %d WHERE ID = %d", PlayerInfo[playerid][pAccount], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			GameTextForPlayer(playerid, "~w~Congratulations ~n~ You have sold that property", 10000, 3);
			format(string, MAXO_TEXT2, "UPDATE bizz SET Owner = '%s', Owned = %d WHERE ID = %d", BizInfo[id][bOwner], BizInfo[id][bOwned], BizInfo[id][bSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
			format(string, MAXO_TEXT2, "UPDATE players SET Pbizkey = %d WHERE ID = %d", PlayerInfo[playerid][pPbizkey], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(PropertyString, MAXO_TEXT2, "This biz is available to buy!\nOwner: %s\nLevel: %d, Price: $%s\nDescription: %s\nTo buy /buybiz", BizInfo[id][bOwner], BizInfo[id][bLevel], FormatNumber(BizInfo[id][bPrice], 0, '.'), BizInfo[id][bDescription]);
			Update3DTextLabelText(BizInfo[id][bLabel], COLOR_PROPERTY_NONE, PropertyString);
			format(string, MAXO_TEXT, "* You received $%s (65 percent) for your business.", FormatNumber(pret, 0, '.'));
			SendClientMessage(playerid, COLOR_YELLOW, string);
			new log[MAXO_TEXT2];
			format(log, MAXO_TEXT2, "%s a vandut biz-ul cu ID-ul %d la pret de $%s.", PlayerName(playerid), BizInfo[id][bSQLID], FormatNumber(pret, 0, '.'));
			BizLog(log);
			clear.string(string);
			clear.string(PropertyString);
			clear.string(log);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in front of biz.");
	} else NotAuthorized();
	return true;
}

COMMAND:bizwithdraw(playerid, params[]) {
	new
		string[MAXO_TEXT], amount, biz = PlayerInfo[playerid][pPbizkey];
	if(biz) {
		if(!sscanf(params, "d", amount)) {
			if(IsPlayerInRangeOfPoint(playerid, 3.0, BizInfo[biz][bEntrancex], BizInfo[biz][bEntrancey], BizInfo[biz][bEntrancez])) {
				if(ISBetween(amount, 1, BizInfo[biz][bTakings])) {
					SafeGivePlayerMoney(playerid, amount);
					BizInfo[biz][bTakings] -= amount;
					format(string, MAXO_TEXT, "UPDATE bizz SET Takings = %d WHERE ID = %d", BizInfo[biz][bTakings], BizInfo[biz][bSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
					format(string, MAXO_TEXT, "You has withdrawn $%s from your cashbox. Remain: $%s", FormatNumber(amount, 0, '.'), FormatNumber(BizInfo[biz][bTakings], 0, '.'));
					SendClientMessage(playerid, -1, string);
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "This amount not is in your cashbox.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in front of biz.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/bizwithdraw [amount]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not the owner of this biz.");
	return true;
}

COMMAND:setenterprice(playerid, params[]) {
	new
		string[MAXO_TEXT], amount, biz = PlayerInfo[playerid][pPbizkey];
	if(biz) {
		if(!sscanf(params, "d", amount)) {
			if(IsPlayerInRangeOfPoint(playerid, 3.0, BizInfo[biz][bEntrancex], BizInfo[biz][bEntrancey], BizInfo[biz][bEntrancez])) {
				if(ISBetween(amount, 1, 500)) {
					BizInfo[biz][bEnterPrice] = amount;
					format(string, MAXO_TEXT, "UPDATE bizz SET EnterPrice = %d WHERE ID = %d", BizInfo[biz][bEnterPrice], BizInfo[biz][bSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
					format(PropertyString, MAXO_TEXT2, "Biz %s\nLevel: %d\nOwned by: %s\nEntrance: $%s\nPress ENTER to enter", BizInfo[biz][bDescription], BizInfo[biz][bLevel], BizInfo[biz][bOwner], FormatNumber(BizInfo[biz][bEnterPrice], 0, '.'));
					Update3DTextLabelText(BizInfo[biz][bLabel], COLOR_PROPERTY, PropertyString);
					format(string, MAXO_TEXT, "You set the enter price in your biz: $%s.", FormatNumber(amount, 0, '.'));
					SendClientMessage(playerid, -1, string);
					clear.string(PropertyString);
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "The amount must be between $1-$500.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in front of house.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/setenterprice [amount]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not the owner of this biz.");
	return true;
}

COMMAND:asellbiz(playerid, params[]) {
	new
		string[MAXO_TEXT2], id = GetBizSQLID(playerid, 3.0);
	if(PlayerInfo[playerid][pAdmin] > 3) {
		if(IsPlayerInRangeOfPoint(playerid, 3.0, BizInfo[id][bEntrancex], BizInfo[id][bEntrancey], BizInfo[id][bEntrancez])) {
			strmid(BizInfo[id][bOwner], "The_State", 0, strlen("The_State"), 255);
			BizInfo[id][bOwned] = 0;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			GameTextForPlayer(playerid, "~w~Congratulations ~n~ You have sold that property", 10000, 3);
			format(string, MAXO_TEXT2, "UPDATE bizz SET Owner = '%s', Owned = %d WHERE ID = %d", BizInfo[id][bOwner], BizInfo[id][bOwned], BizInfo[id][bSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
			format(string, MAXO_TEXT2, "UPDATE players SET Pbizkey = 0 WHERE Pbizkey = %d", PlayerInfo[playerid][pPbizkey]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(PropertyString, MAXO_TEXT2, "This biz is available to buy!\nOwner: %s\nLevel: %d, Price: $%s\nDescription: %s\nTo buy /buybiz", BizInfo[id][bOwner], BizInfo[id][bLevel], FormatNumber(BizInfo[id][bPrice], 0, '.'), BizInfo[id][bDescription]);
			Update3DTextLabelText(BizInfo[id][bLabel], COLOR_PROPERTY_NONE, PropertyString);
			new log[MAXO_TEXT2];
			format(log, MAXO_TEXT2, "Adminul %s a vandut biz-ul cu ID-ul %d la pret de $%s.", PlayerName(playerid), BizInfo[id][bSQLID], FormatNumber(BizInfo[id][bPrice], 0, '.'));
			BizLog(log);
			clear.string(PropertyString);
			clear.string(log);
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in front of biz.");
	} else NotAuthorized();
	return true;
}

COMMAND:sellbizto(playerid, params[]) {
	new string[MAXO_TEXT], targetid, amount;
	if(IsPlayerOwnerABiz(playerid)) {
		if(!sscanf(params, "s[24]d", PartialName[playerid][nume_introdus], amount)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(PlayerInfo[targetid][pLevel] >= HouseInfo[PlayerInfo[playerid][pPhousekey]][hLevel]) {
						if(PlayerInfo[targetid][pAccount] >= amount) {
							if(GetDistanceBetweenPlayers(playerid, targetid) < 4) {
								format(string, MAXO_TEXT, "* %s wants to sell you his business for $%s, (type /accept %d biz) to buy.", PlayerName(playerid), FormatNumber(amount, 0, '.'), playerid);
								SendClientMessage(targetid, COLOR_FAMILY, string);
								format(string, MAXO_TEXT, "* You offered %s your business at the price of $%s.", PlayerName(targetid), FormatNumber(amount, 0, '.'));
								SendClientMessage(playerid, COLOR_FAMILY, string);
								PropertyOffer[targetid] = playerid;
								PropertyPrice[targetid] = amount;
								PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
								clear.string(string);
							} else SendClientMessage(playerid, COLOR_GRAD1, "This player is too far away from you.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "This player not have enough money to buy the business from you.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not have the level necessary to buy the business from you.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can't sell the business yourself.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid player.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/sellbizto [playerid/PartOfName] [price]");
	} else NotAuthorized();
	return true;
}

COMMAND:gotobiz(playerid, params[]) {
	new
		string[MAXO_TEXT], biz;
	if(PlayerInfo[playerid][pAdmin] > 3) {
		if(!sscanf(params, "d", biz)) {
			if(ISBetween(biz, 1, MAX_BIZ-1)) {
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
					new factiune = PlayerInfo[playerid][pFactiune];
					SetSpawnInfo(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pSkin], BizInfo[biz][bEntrancex], BizInfo[biz][bEntrancey], BizInfo[biz][bEntrancez]+0.3, 0, FactionInfo[factiune][fWeapon1], FactionInfo[factiune][fAmmo1], FactionInfo[factiune][fWeapon2], FactionInfo[factiune][fAmmo2], FactionInfo[factiune][fWeapon3], FactionInfo[factiune][fAmmo3]);
					SpawnPlayer(playerid);
					if(IsPlayerInInside(playerid))
						SafeSetPlayerInterior(playerid, 0),
						SafeSetPlayerVirtualWorld(playerid, 0);
					GameTextForPlayer(playerid, "~g~Teleporting...", 3000, 1);
					format(string, MAXO_TEXT, "* You have been teleported at biz with SQLID %d.", BizInfo[biz][bSQLID]);
					SendClientMessage(playerid, COLOR_LIGHTRED, string);
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "You must be pedestrian for this action.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid bizid.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/gotobiz [bizid]");
	} else NotAuthorized();
	return true;
}

COMMAND:mybizinfo(playerid, params[]) {
	if(PlayerInfo[playerid][pPbizkey] != 0) {
		new string[MAXO_TEXT];
		format(string, MAXO_TEXT, "%s (%d) status\n\nEnter Price: $%s;\nFounds: $%s;\nProducts: %d;", BizInfo[PlayerInfo[playerid][pPbizkey]][bDescription], PlayerInfo[playerid][pPbizkey], FormatNumber(BizInfo[PlayerInfo[playerid][pPbizkey]][bEnterPrice], 0, '.'), FormatNumber(BizInfo[PlayerInfo[playerid][pPbizkey]][bTakings], 0, '.'), BizInfo[PlayerInfo[playerid][pPbizkey]][bProducts]);
		ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Info", string, "Ok", "");
		clear.string(string);
	} else NotAuthorized();
	return true;
}

COMMAND:putmoneyinbiz(playerid, params[]) {
	new string[MAXO_TEXT], amount, id = PlayerInfo[playerid][pPbizkey];
	if(PlayerInfo[playerid][pPbizkey] != 0) {
		if(!sscanf(params, "d", amount)) {
			if(ISBetween(amount, 1, PlayerInfo[playerid][pCash])) {
				SafeGivePlayerMoney(playerid, -amount);
				BizInfo[id][bTakings] += amount;
				format(string, MAXO_TEXT, "UPDATE bizz SET Takings = %d WHERE ID = %d", BizInfo[id][bTakings], BizInfo[id][bSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
				format(string, MAXO_TEXT, "* You deposited $%s in your business.", FormatNumber(amount, 0, '.'));
				SendClientMessage(playerid, COLOR_YELLOW, string);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "You don't this amount.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/putmoneyinbiz [amount]");
	} else NotAuthorized();
	return true;
}

// End Of File ...
