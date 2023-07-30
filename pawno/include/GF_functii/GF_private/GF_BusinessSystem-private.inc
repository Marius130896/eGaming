/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_BusinessSystemPriv_included
	#endinput
#else
	#define GF_BusinessSystemPriv_included
#endif

stock LoadBiz() {
	mysql_tquery(connectionHandle, "SELECT * FROM bizz", "LoadBizThread", "d", BIZ_THREAD_ID);
	return true;
}

function LoadBizThread() {
	rows = cache_num_rows();
	if(rows) {
		for(new i; i < rows; i ++) {
			BizInfo[i][bSQLID] = cache_get_row_int(i, 0);
			cache_get_row(i, 1, BizInfo[i][bDescription], .max_len = MAX_BIZ_NAME);
			BizInfo[i][bEntrancex] = cache_get_row_float(i, 2);
			BizInfo[i][bEntrancey] = cache_get_row_float(i, 3);
			BizInfo[i][bEntrancez] = cache_get_row_float(i, 4);
			BizInfo[i][bExitx] = cache_get_row_float(i, 5);
			BizInfo[i][bExity] = cache_get_row_float(i, 6);
			BizInfo[i][bExitz] = cache_get_row_float(i, 7);
			cache_get_row(i, 8, BizInfo[i][bOwner], .max_len = MAX_PLAYER_NAME);
			BizInfo[i][bOwned] = cache_get_row_int(i, 9);
			BizInfo[i][bInterior] = cache_get_row_int(i, 10);
			BizInfo[i][bVirtualWorld] = cache_get_row_int(i, 11);
			BizInfo[i][bLevel] = cache_get_row_int(i, 12);
			BizInfo[i][bPrice] = cache_get_row_int(i, 13);
			BizInfo[i][bEnterPrice] = cache_get_row_int(i, 14);
			BizInfo[i][bTakings] = cache_get_row_int(i, 15);
			BizInfo[i][bType] = cache_get_row_int(i, 16);
			BizInfo[i][bProducts] = cache_get_row_int(i, 17);

			if(BizInfo[i][bOwned] == 0) {
				format(PropertyString, MAXO_TEXT2, "This biz is available to buy!\nOwner: %s\nLevel: %d, Price: $%s\nDescription: %s\nTo buy /buybiz", BizInfo[i][bOwner], BizInfo[i][bLevel], FormatNumber(BizInfo[i][bPrice], 0, '.'), BizInfo[i][bDescription]);
				BizInfo[i][bLabel] = Create3DTextLabel(PropertyString, COLOR_PROPERTY_NONE, BizInfo[i][bEntrancex], BizInfo[i][bEntrancey], BizInfo[i][bEntrancez]+1, 25, 0, 1);
				#if defined _stream_pickups
					BizInfo[i][bPickup] = CreateDynamicPickup(1314, 23, BizInfo[i][bEntrancex], BizInfo[i][bEntrancey], BizInfo[i][bEntrancez], -1);
				#else
					BizInfo[i][bPickup] = CreatePickup(1314, 23, BizInfo[i][bEntrancex], BizInfo[i][bEntrancey], BizInfo[i][bEntrancez], -1);
				#endif
			}
			else if(BizInfo[i][bOwned] == 1) {
				format(PropertyString, MAXO_TEXT2, "Biz %s\nLevel: %d\nOwned by: %s\nEntrance: $%s\nPress ENTER to enter", BizInfo[i][bDescription], BizInfo[i][bLevel], BizInfo[i][bOwner], FormatNumber(BizInfo[i][bEnterPrice], 0, '.'));
				BizInfo[i][bLabel] = Create3DTextLabel(PropertyString, COLOR_PROPERTY, BizInfo[i][bEntrancex], BizInfo[i][bEntrancey], BizInfo[i][bEntrancez]+1, 25, 0, 1);
				#if defined _stream_pickups
					BizInfo[i][bPickup] = CreateDynamicPickup(1314, 23, BizInfo[i][bEntrancex], BizInfo[i][bEntrancey], BizInfo[i][bEntrancez], -1);
				#else
					BizInfo[i][bPickup] = CreatePickup(1314, 23, BizInfo[i][bEntrancex], BizInfo[i][bEntrancey], BizInfo[i][bEntrancez], -1);
				#endif
			}
			switch(BizInfo[i][bType]) {
				case BIZ_TYPE_GS: BizIcon[i] = CreateDynamicMapIcon(BizInfo[i][bEntrancex], BizInfo[i][bEntrancey], BizInfo[i][bEntrancez], 6, MAPICON_LOCAL);
				case BIZ_TYPE_HOUSEUPG: BizIcon[i] = CreateDynamicMapIcon(BizInfo[i][bEntrancex], BizInfo[i][bEntrancey], BizInfo[i][bEntrancez], 32, MAPICON_LOCAL);
				case BIZ_TYPE_BENZINARIE: BizIcon[i] = CreateDynamicMapIcon(BizInfo[i][bEntrancex], BizInfo[i][bEntrancey], BizInfo[i][bEntrancez], 36, MAPICON_LOCAL);
				case BIZ_TYPE_BURGERSHOT: BizIcon[i] = CreateDynamicMapIcon(BizInfo[i][bEntrancex], BizInfo[i][bEntrancey], BizInfo[i][bEntrancez], 10, MAPICON_LOCAL);
				case BIZ_TYPE_24_7: BizIcon[i] = CreateDynamicMapIcon(BizInfo[i][bEntrancex], BizInfo[i][bEntrancey], BizInfo[i][bEntrancez], 17, MAPICON_LOCAL);
				case BIZ_TYPE_ELECTRICA: BizIcon[i] = CreateDynamicMapIcon(BizInfo[i][bEntrancex], BizInfo[i][bEntrancey], BizInfo[i][bEntrancez], 19, MAPICON_LOCAL);
				case BIZ_TYPE_BANK: BizIcon[i] = CreateDynamicMapIcon(BizInfo[i][bEntrancex], BizInfo[i][bEntrancey], BizInfo[i][bEntrancez], 52, MAPICON_LOCAL);
				case BIZ_TYPE_RENTCAR: BizIcon[i] = CreateDynamicMapIcon(BizInfo[i][bEntrancex], BizInfo[i][bEntrancey], BizInfo[i][bEntrancez], 55, MAPICON_LOCAL);
				case BIZ_TYPE_BINCO: BizIcon[i] = CreateDynamicMapIcon(BizInfo[i][bEntrancex], BizInfo[i][bEntrancey], BizInfo[i][bEntrancez], 45, MAPICON_LOCAL);
			}
		}
		TotalBizLoaded ++;
	}
	printf("LoadBizThread() - called (%d business loaded).", rows);
	return true;
}

stock LoadProdsBurger() {
	mysql_tquery(connectionHandle, "SELECT * FROM prices_burger", "InitPrBurgerThread", "d", PRODBURGER_THREAD_ID);
	return true;
}

function InitPrBurgerThread() {
	new indexul;
	rows = cache_num_rows();
	if(rows) {
		for(new i; i < rows; i ++) {
			indexul = cache_get_row_int(i, 0);
			PretBurgerInfo[indexul][nrProdus] = cache_get_row_int(i, 1);
			cache_get_row(i, 2, PretBurgerInfo[indexul][nameProdus], .max_len = MAX_PRODUCT_NAME);
			PretBurgerInfo[indexul][pretProdus] = cache_get_row_int(i, 3);
			PretBurgerInfo[indexul][viataProdus] = cache_get_row_float(i, 4);
		}
		printf("InitPrBurgerThread - called (%d prices).", rows);
	}
	return true;
}

stock PlayerBuyFood(playerid, idfood) {
	new string[MAXO_TEXT], idbiz = PlayerInfo[playerid][pInBizzID];
	new pretprod = PretBurgerInfo[idfood][pretProdus], Float:PlHealth;
	if(BizInfo[idbiz][bProducts] > 0) {
		if(PlayerInfo[playerid][pCash] >= PretBurgerInfo[idfood][pretProdus]) {
			GetPlayerHealth(playerid, PlHealth);
			if(PlHealth < 100) {
				SetPlayerHealth(playerid, ((PlHealth >= 75.0) ? 100.0 : (PlHealth + PretBurgerInfo[idfood][viataProdus])));				
				format(string, MAXO_TEXT, "* You bought a Menu %s for $%s.", PretBurgerInfo[idfood][nameProdus], FormatNumber(pretprod, 0, '.'));
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);				
				SafeGivePlayerMoney(playerid, -pretprod);
				BizInfo[idbiz][bProducts] --;
				BizInfo[idbiz][bTakings] += pretprod;
				format(string, MAXO_TEXT2, "UPDATE bizz SET Products = %d, Takings = %d", BizInfo[idbiz][bProducts], BizInfo[idbiz][bTakings], BizInfo[idbiz][bSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
				TogglePlayerControllable(playerid, true);
				SetCameraBehindPlayer(playerid);
				PlayerPlaySound(playerid, 1053  , 0.0, 0.0, 0.0);
				PlayerPlaySound(playerid, 1186  , 0.0, 0.0, 0.0);
				for(new m; m < 2; m ++) {
					if(PlayerInfo[playerid][pDailyMission][m] == MISSION_BUYFOOD)
						CheckMission(playerid, m);
				}
			}
			else
			{ 
				SendClientMessage(playerid, COLOR_GRAD1, "You can't consume anyting anymore, you will throw up!");
				TogglePlayerControllable(playerid, true);
				SetCameraBehindPlayer(playerid);
				PlayerPlaySound(playerid, 1053  , 0.0, 0.0, 0.0);
				PlayerPlaySound(playerid, 1186  , 0.0, 0.0, 0.0);					
			}		
		}
		else
		{
			format(string, MAXO_TEXT, "You don't have enough money, you need %s to buy this menu.", FormatNumber(pretprod, 0, '.'));
			SendClientMessage(playerid, COLOR_GRAD1, string);
			TogglePlayerControllable(playerid, true);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 1053  , 0.0, 0.0, 0.0);
			PlayerPlaySound(playerid, 1186  , 0.0, 0.0, 0.0);			
		}
	}
	else
	{
		GameTextForPlayer(playerid, "~r~Out of stock~", 2500, 1);
		TogglePlayerControllable(playerid, true);
		SetCameraBehindPlayer(playerid);
		PlayerPlaySound(playerid, 1053  , 0.0, 0.0, 0.0);
		PlayerPlaySound(playerid, 1186  , 0.0, 0.0, 0.0);
	}
	clear.string(string);
	return true;
}

stock LoadPrItemsThread() {
	mysql_tquery(connectionHandle, "SELECT * FROM prices_item", "InitPrItemsThread", "d", PRODITEMS_THREAD_ID);
	return true;
}

function InitPrItemsThread() {
	new indexul;
	rows = cache_num_rows();
	if(rows) {
		for (new i; i < rows; i ++) {
			indexul = cache_get_row_int(i, 0);
			PretItemInfo[indexul][nrItem] = cache_get_row_int(i, 1);
			PretItemInfo[indexul][pretItem] = cache_get_row_int(i, 2);
			cache_get_row(i, 3, PretItemInfo[indexul][nameItem], .max_len = MAX_PRODUCT_NAME);
		}
		printf("InitPrItemsThread - called (%d prices loaded).", rows);
	}
	return true;
}

stock SellItemDenied(playerid, color, message[], Menu:menu_p) {
	return SendClientMessage(playerid, color, message), ShowMenuForPlayer(menu_p, playerid);
}

stock PlayerBuyItem(playerid, itemid) {
	new idbiz = PlayerInfo[playerid][pInBizzID], string[MAXO_TEXT];
	if(BizInfo[idbiz][bProducts] > 0) {
		if(PlayerInfo[playerid][pCash] >= PretItemInfo[itemid][pretItem]) {
			switch(itemid) {
				case 1: if(PlayerInfo[playerid][pPnumber] > 0) return SellItemDenied(playerid, COLOR_GRAD1, "You have already an Mobile Phone.", MenuStore);
				case 2: if(PlayerInfo[playerid][pPhoneBook] > 0) return SellItemDenied(playerid, COLOR_GRAD1, "You have already a Phone Book.", MenuStore);
				case 3: if(PlayerInfo[playerid][pFreqNO] > 0) return SellItemDenied(playerid, COLOR_GRAD1, "You have already a Walkie Talkie.", MenuStore);
				case 4: if(PlayerInfo[playerid][pDice] > 0) return SellItemDenied(playerid, COLOR_GRAD1, "You have already Dice.", MenuStore);
				case 5: {
					new weapons[13][2];
					for (new i = 1; i <= 12; i ++) {
					    GetPlayerWeaponData(playerid, i, weapons[i][0], weapons[i][1]);
					    if(weapons[i][0] == WEAPON_CAMERA && weapons[i][1] > 0) 
					    	return SellItemDenied(playerid, COLOR_GRAD1, "You have already a Camera Photo.", MenuStore);
					}
				}
				case 6: if(HaveFishingRog{playerid}) return SellItemDenied(playerid, COLOR_GRAD1, "You have already a Fishing Rog.", MenuStore2);
				case 7: if(HaveFishingBait[playerid] > 0) return SellItemDenied(playerid, COLOR_GRAD1, "You have already a Fishing Bait.", MenuStore2);
				case 8: if(PlayerInfo[playerid][pCigarettes] > 0) return SellItemDenied(playerid, COLOR_GRAD1, "You have already an package of Cigaretts.", MenuStore2);
				case 9: if(PlayerInfo[playerid][pLighter] > 0) return SellItemDenied(playerid, COLOR_GRAD1, "You have already a Lighter.", MenuStore2);
				case 10: if(HaveGasCan{playerid}) return SellItemDenied(playerid, COLOR_GRAD1, "You have already a Gas Canister.", MenuStore2);
			}
			ItemFrom247[playerid] = itemid;
			SafeGivePlayerMoney(playerid, -PretItemInfo[itemid][pretItem]);
			format(string, MAXO_TEXT1, "~r~-~y~$%s", FormatNumber(PretItemInfo[itemid][pretItem], 0, '.'));
			GameTextForPlayer(playerid, string, 5000, 1);
			BizInfo[idbiz][bTakings] += PretItemInfo[itemid][pretItem];
			format(string, MAXO_TEXT, "UPDATE bizz SET Takings = %d WHERE ID = %d", BizInfo[idbiz][bTakings], BizInfo[idbiz][bSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
			TogglePlayerControllable(playerid, true);
			SetCameraBehindPlayer(playerid);
			GetPlayerItem(playerid);
			clear.string(string);
		}
	}
	return true;
}

stock GetPlayerItem(playerid) {
	new string[MAXO_TEXT], id = PlayerInfo[playerid][pInBizzID];
	switch(ItemFrom247[playerid]) {
		case 1: {
			new Phone = RandomEx(1000, 9999);
			PlayerInfo[playerid][pPnumber] = Phone;
			BizInfo[id][bProducts] -= 5;
			format(string, MAXO_TEXT, "UPDATE players SET Pnumber = %d WHERE ID = %d", PlayerInfo[playerid][pPnumber], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(string, MAXO_TEXT, "* You bought a cell phone with the number %d at price of $%s. Type /help to see the commands!", FormatNumber(PretItemInfo[1][pretItem], 0, '.'), PlayerInfo[playerid][pPnumber]);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
		}
		case 2: {
			PlayerInfo[playerid][pPhoneBook] = 1;
			BizInfo[id][bProducts] -= 2;
			format(string, MAXO_TEXT, "UPDATE players SET PhoneBook = %d WHERE ID = %d", PlayerInfo[playerid][pPhoneBook], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(string, MAXO_TEXT, "* You bought an Phone Book at price of $%s. Type /numbers to see the numbers!", FormatNumber(PretItemInfo[2][pretItem], 0, '.'));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
		}
		case 3: ShowPlayerDialog(playerid, DIALOGID_BUY_WALKIETALKIE, DIALOG_STYLE_INPUT, "Buy Walkie Talkie Menu", "Type below the frequency number you want to buy:", "Next", "Abort");
		case 4: {
			PlayerInfo[playerid][pDice] = 1;
			BizInfo[id][bProducts] -= 2;
			format(string, MAXO_TEXT, "* You bought a pair of dice at price of $%s. Type /dice to roll the dice!", FormatNumber(PretItemInfo[4][pretItem], 0, '.'));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);			
		}
		case 5: {
			BizInfo[id][bProducts] -= 2;
			GivePlayerWeapon(playerid, WEAPON_CAMERA, 150);
			format(string, MAXO_TEXT, "* You bought a Camera Photo at price of $%s.", FormatNumber(PretItemInfo[5][pretItem], 0, '.'));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);	
		}
		case 6: {
			HaveFishingRog{playerid} = true;
			BizInfo[id][bProducts] -= 2;
			format(string, MAXO_TEXT, "* You bought a Fishing Rod at price of $%s.", FormatNumber(PretItemInfo[6][pretItem], 0, '.'));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);	
		}
		case 7: {
			HaveFishingBait[playerid] = 50;
			BizInfo[id][bProducts] -= 2;
			format(string, MAXO_TEXT, "* You bought 50 Fishing Bait at price of $%s.", FormatNumber(PretItemInfo[7][pretItem], 0, '.'));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);	
		}
		case 8: {
			PlayerInfo[playerid][pCigarettes] = 20;
			BizInfo[id][bProducts] -= 2;
			format(string, MAXO_TEXT, "* You bought an package of Cigarettes of 20 cigarettes at price of $%s.", FormatNumber(PretItemInfo[8][pretItem], 0, '.'));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);	
		}
		case 9: {
			PlayerInfo[playerid][pLighter] = 1;
			BizInfo[id][bProducts] -= 2;
			format(string, MAXO_TEXT, "* You bought a Lighter at price of $%s.", FormatNumber(PretItemInfo[9][pretItem], 0, '.'));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);	
		}
		case 10: {
			HaveGasCan{playerid} = true;
			BizInfo[id][bProducts] -= 2;
			format(string, MAXO_TEXT, "* You bought a Gas Canister at price of $%s.", FormatNumber(PretItemInfo[10][pretItem], 0, '.'));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);	
		}
	}
	format(string, MAXO_TEXT, "UPDATE bizz SET Products = %d WHERE ID = %d", BizInfo[id][bProducts], BizInfo[id][bSQLID]);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
	clear.string(string);
	return true;
}

function GetBizSQLID(playerid, Float:range) {
	for(new i = 0; i < sizeof(BizInfo); i ++) {
		if(IsPlayerInRangeOfPoint(playerid, range, BizInfo[i][bEntrancex], BizInfo[i][bEntrancey], BizInfo[i][bEntrancez]))
			return i;
	}
	return false;
}

stock IsPlayerOwnerABiz(playerid) {
	new
		biz = PlayerInfo[playerid][pPbizkey];
	if(biz != 0 && strcmp(PlayerName(playerid), BizInfo[biz][bOwner], true) == 0) {
		return true;
	}
	return false;
}

stock NuDeschideBiz(tipbiz) {
	switch(BizInfo[tipbiz][bType]) {
		case BIZ_TYPE_BENZINARIE: return true;
		case BIZ_TYPE_ELECTRICA: return true;
		case BIZ_TYPE_RENTCAR: return true;
	}
	return false;
}

COMMAND:createbiz(playerid, params[]) {
	new
		Float:iPos[3], interior, price, level, type;
	if(IsPlayerFounder(playerid)) {
		if(!sscanf(params, "p<,>fffdddds[64]", iPos[0], iPos[1], iPos[2], interior, price, level, type, params)) {
			if(ISBetween(price, 1, 1000000)) {
				if(ISBetween(level, 2, 15)) {
					if(strlen(params) < 64) {
						TotalBizLoaded ++;
						new
							virtual_world = TotalBizLoaded, Float:pPos[3], string[400],
							biz = TotalBizLoaded;
						GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
						if(pPos[0] == 0 && pPos[1] == 0 && pPos[2] == 0)
							return SendClientMessage(playerid, COLOR_LIGHTRED, "You cannot create a new biz, because don't was founded the coords.");
						BizInfo[biz][bEntrancex] = pPos[0];
						BizInfo[biz][bEntrancey] = pPos[1];
						BizInfo[biz][bEntrancez] = pPos[2];
						BizInfo[biz][bExitx] = iPos[0];
						BizInfo[biz][bExity] = iPos[1];
						BizInfo[biz][bExitz] = iPos[2];
						strmid(BizInfo[biz][bOwner], "The_State", 0, strlen("The_State"), 255);
						strmid(BizInfo[biz][bDescription], params, 0, strlen(params), 255);
						BizInfo[biz][bOwned] = 0;
						BizInfo[biz][bInterior] = interior;
						BizInfo[biz][bVirtualWorld] = virtual_world+1;
						BizInfo[biz][bTakings] = 0;
						BizInfo[biz][bLevel] = level;
						BizInfo[biz][bPrice] = price;
						BizInfo[biz][bEnterPrice] = 1;
						BizInfo[biz][bType] = type;
						format(string, 400, "INSERT INTO bizz (EnterX, EnterY, EnterZ, ExitX, ExitY, ExitZ, Description, Interior, VirtualWorld, Level, Price, Type, Owner) VALUES ('%f', '%f', '%f', '%f', '%f', '%f', '%s', '%d', '%d', '%d', '%d', '%d', 'The_State')", BizInfo[biz][bEntrancex], BizInfo[biz][bEntrancey], BizInfo[biz][bEntrancez], BizInfo[biz][bExitx], BizInfo[biz][bExity], BizInfo[biz][bExitz], BizInfo[biz][bDescription], BizInfo[biz][bInterior], BizInfo[biz][bVirtualWorld], BizInfo[biz][bLevel], BizInfo[biz][bPrice], BizInfo[biz][bType]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
						format(PropertyString, MAXO_TEXT2, "This biz is available to buy!\nOwner: %s\nLevel: %d, Price: $%s\nDescription: %s\nTo buy /buybiz", BizInfo[biz][bOwner], BizInfo[biz][bLevel], FormatNumber(BizInfo[biz][bPrice], 0, '.'), BizInfo[biz][bDescription]);
						BizInfo[biz][bLabel] = Create3DTextLabel(PropertyString, COLOR_PROPERTY_NONE, BizInfo[biz][bEntrancex], BizInfo[biz][bEntrancey], BizInfo[biz][bEntrancez]+1, 25, 0, 1);
						#if defined _stream_pickups
							BizInfo[biz][bPickup] = CreateDynamicPickup(1314, 23, BizInfo[biz][bEntrancex], BizInfo[biz][bEntrancey], BizInfo[biz][bEntrancez], -1);
						#else
							BizInfo[biz][bPickup] = CreatePickup(1314, 23, BizInfo[biz][bEntrancex], BizInfo[biz][bEntrancey], BizInfo[biz][bEntrancez], -1);
						#endif
						clear.string(string);
						clear.string(PropertyString);
					} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "The level must be between 2-15.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "The price must be between $1-$1.000.000.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/createbiz [iX] [iY] [iZ] [interior id] [price] [level] [type] [params]");
	} else NotAuthorized();
	return true;
}

// End Of File ...
