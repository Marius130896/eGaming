/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/

#if defined GF_Menu03xFunc_included
	#endinput
#else
	#define GF_Menu03xFunc_included
#endif

public OnPlayerExitedMenu(playerid) {
	if(!IsValidMenu(GetPlayerMenu(playerid))) return 1;
	ShowMenuForPlayer(GetPlayerMenu(playerid), playerid);
	return 1;
}

function ShowMenuInBusiness() {
	new string[MAXO_TEXT];
	MenuGunsAN = CreateMenu("Weapons", 1, 20.0, 170.0, 200.0, 200.0);
	format(string, MAXO_TEXT, "%s (%d) ~g~$%s", GunNames[PretArmeInfo[WEAPON_BRASSKNUCKLE][nrArma]], PretArmeInfo[WEAPON_BRASSKNUCKLE][nrGloante], FormatNumber(PretArmeInfo[WEAPON_BRASSKNUCKLE][pretArma], 0, ','));
	AddMenuItem(MenuGunsAN, 0, string);
	format(string, MAXO_TEXT, "%s (%d) ~g~$%s", GunNames[PretArmeInfo[WEAPON_GOLFCLUB][nrArma]], PretArmeInfo[WEAPON_GOLFCLUB][nrGloante], FormatNumber(PretArmeInfo[WEAPON_GOLFCLUB][pretArma], 0, ','));
	AddMenuItem(MenuGunsAN, 0, string);
	format(string, MAXO_TEXT, "%s (%d) ~g~$%s", GunNames[PretArmeInfo[WEAPON_BAT][nrArma]], PretArmeInfo[WEAPON_BAT][nrGloante], FormatNumber(PretArmeInfo[WEAPON_BAT][pretArma], 0, ','));
	AddMenuItem(MenuGunsAN, 0, string);
	format(string, MAXO_TEXT, "%s (%d) ~g~$%s", GunNames[PretArmeInfo[WEAPON_SHOVEL][nrArma]], PretArmeInfo[WEAPON_SHOVEL][nrGloante], FormatNumber(PretArmeInfo[WEAPON_SHOVEL][pretArma], 0, ','));
	AddMenuItem(MenuGunsAN, 0, string);
	format(string, MAXO_TEXT, "%s (%d) ~g~$%s", GunNames[PretArmeInfo[WEAPON_SILENCED][nrArma]], PretArmeInfo[WEAPON_SILENCED][nrGloante], FormatNumber(PretArmeInfo[WEAPON_SILENCED][pretArma], 0, ','));
	AddMenuItem(MenuGunsAN, 0, string);
	format(string, MAXO_TEXT, "%s (%d) ~g~$%s", GunNames[PretArmeInfo[WEAPON_DEAGLE][nrArma]], PretArmeInfo[WEAPON_DEAGLE][nrGloante], FormatNumber(PretArmeInfo[WEAPON_DEAGLE][pretArma], 0, ','));
	AddMenuItem(MenuGunsAN, 0, string);
	format(string, MAXO_TEXT, "%s (%d) ~g~$%s", GunNames[PretArmeInfo[WEAPON_PARACHUTE][nrArma]], PretArmeInfo[WEAPON_PARACHUTE][nrGloante], FormatNumber(PretArmeInfo[WEAPON_PARACHUTE][pretArma], 0, ','));
	AddMenuItem(MenuGunsAN, 0, string);
	AddMenuItem(MenuGunsAN, 0, "Exit");

	MenuBurger = CreateMenu("Food", 1, 20.0, 170.0, 200.0, 200.0);
	format(string, MAXO_TEXT, "%s ~g~$%s", PretBurgerInfo[1][nameProdus], FormatNumber(PretBurgerInfo[1][pretProdus]));
	AddMenuItem(MenuBurger, 0, string);
	format(string, MAXO_TEXT, "%s ~g~$%s", PretBurgerInfo[2][nameProdus], FormatNumber(PretBurgerInfo[2][pretProdus]));
	AddMenuItem(MenuBurger, 0, string);
	format(string, MAXO_TEXT, "%s ~g~$%s", PretBurgerInfo[3][nameProdus], FormatNumber(PretBurgerInfo[3][pretProdus]));
	AddMenuItem(MenuBurger, 0, string);
	format(string, MAXO_TEXT, "%s ~g~$%s", PretBurgerInfo[4][nameProdus], FormatNumber(PretBurgerInfo[4][pretProdus]));
	AddMenuItem(MenuBurger, 0, string);
	format(string, MAXO_TEXT, "%s ~g~$%s", PretBurgerInfo[5][nameProdus], FormatNumber(PretBurgerInfo[5][pretProdus]));
	AddMenuItem(MenuBurger, 0, string);
	AddMenuItem(MenuBurger, 0, "Exit");

	MenuStore = CreateMenu("Items", 1, 20.0, 170.0, 200.0, 200.0);
	format(string, MAXO_TEXT, "%s ~g~$%s", PretItemInfo[1][nameItem], FormatNumber(PretItemInfo[1][pretItem], 0, '.'));
	AddMenuItem(MenuStore, 0, string);
	format(string, MAXO_TEXT, "%s ~g~$%s", PretItemInfo[2][nameItem], FormatNumber(PretItemInfo[2][pretItem], 0, '.'));
	AddMenuItem(MenuStore, 0, string);
	format(string, MAXO_TEXT, "%s ~g~$%s", PretItemInfo[3][nameItem], FormatNumber(PretItemInfo[3][pretItem], 0, '.'));
	AddMenuItem(MenuStore, 0, string);
	format(string, MAXO_TEXT, "%s ~g~$%s", PretItemInfo[4][nameItem], FormatNumber(PretItemInfo[4][pretItem], 0, '.'));
	AddMenuItem(MenuStore, 0, string);
	format(string, MAXO_TEXT, "%s ~g~$%s", PretItemInfo[5][nameItem], FormatNumber(PretItemInfo[5][pretItem], 0, '.'));
	AddMenuItem(MenuStore, 0, string);
	AddMenuItem(MenuStore, 0, "Next");

	MenuStore2 = CreateMenu("Items", 1, 20.0, 170.0, 200.0, 200.0);
	format(string, MAXO_TEXT, "%s ~g~$%s", PretItemInfo[6][nameItem], FormatNumber(PretItemInfo[6][pretItem], 0, '.'));
	AddMenuItem(MenuStore2, 0, string);
	format(string, MAXO_TEXT, "%s ~g~$%s", PretItemInfo[7][nameItem], FormatNumber(PretItemInfo[7][pretItem], 0, '.'));
	AddMenuItem(MenuStore2, 0, string);
	format(string, MAXO_TEXT, "%s ~g~$%s", PretItemInfo[8][nameItem], FormatNumber(PretItemInfo[8][pretItem], 0, '.'));
	AddMenuItem(MenuStore2, 0, string);
	format(string, MAXO_TEXT, "%s ~g~$%s", PretItemInfo[9][nameItem], FormatNumber(PretItemInfo[9][pretItem], 0, '.'));
	AddMenuItem(MenuStore2, 0, string);
	format(string, MAXO_TEXT, "%s ~g~$%s", PretItemInfo[10][nameItem], FormatNumber(PretItemInfo[10][pretItem], 0, '.'));
	AddMenuItem(MenuStore2, 0, string);
	AddMenuItem(MenuStore2, 0, "Exit");
	clear.string(string);
	return true;
}

public OnPlayerSelectedMenuRow(playerid, row) {
	new
		id = PlayerInfo[playerid][pPbizkey], string[MAXO_TEXT],
		casa = PlayerInfo[playerid][pPhousekey];
	new Menu:CurrentMenu = GetPlayerMenu(playerid);
	if(CurrentMenu == MenuGunsAN) {
		switch(row) {
			case 0: PlayerBuyWeapon(playerid, WEAPON_BRASSKNUCKLE);
			case 1: PlayerBuyWeapon(playerid, WEAPON_GOLFCLUB);
			case 2: PlayerBuyWeapon(playerid, WEAPON_BAT);
			case 3: PlayerBuyWeapon(playerid, WEAPON_SHOVEL);
			case 4: PlayerBuyWeapon(playerid, WEAPON_SILENCED);
			case 5: PlayerBuyWeapon(playerid, WEAPON_DEAGLE);
			case 6: PlayerBuyWeapon(playerid, WEAPON_PARACHUTE);
			case 7: {
				SetCameraBehindPlayer(playerid); 
				TogglePlayerControllable(playerid, true);
				PlayerPlaySound(playerid, 1053  , 0.0, 0.0, 0.0);
				PlayerPlaySound(playerid, 1186  , 0.0, 0.0, 0.0);
				format(string, MAXO_TEXT, "* Thank you for buying from %s. Have a nice day!", BizInfo[PlayerInfo[playerid][pInBizzID]][bDescription]);
				SendClientMessage(playerid, COLOR_WHITE, string);
			}
		}
	}
	else if(CurrentMenu == MenuBurger) {
		switch(row) {
			case 0: PlayerBuyFood(playerid, PretBurgerInfo[1][nrProdus]);
			case 1: PlayerBuyFood(playerid, PretBurgerInfo[2][nrProdus]);
			case 2: PlayerBuyFood(playerid, PretBurgerInfo[3][nrProdus]);
			case 3: PlayerBuyFood(playerid, PretBurgerInfo[4][nrProdus]);
			case 4: PlayerBuyFood(playerid, PretBurgerInfo[5][nrProdus]);
			case 5: {
				SetCameraBehindPlayer(playerid); 
				TogglePlayerControllable(playerid, true);
				PlayerPlaySound(playerid, 1053  , 0.0, 0.0, 0.0);
				PlayerPlaySound(playerid, 1186  , 0.0, 0.0, 0.0);
				format(string, MAXO_TEXT, "* Thank you for buying from %s. Have a nice day!", BizInfo[PlayerInfo[playerid][pInBizzID]][bDescription]);
				SendClientMessage(playerid, COLOR_WHITE, string);				
			}
		}
	}
	else if(CurrentMenu == MenuStore) {
		switch(row) {
			case 0: PlayerBuyItem(playerid, PretItemInfo[1][nrItem]);
			case 1: PlayerBuyItem(playerid, PretItemInfo[2][nrItem]);
			case 2: PlayerBuyItem(playerid, PretItemInfo[3][nrItem]);
			case 3: PlayerBuyItem(playerid, PretItemInfo[4][nrItem]);
			case 4: PlayerBuyItem(playerid, PretItemInfo[5][nrItem]);
			case 5: ShowMenuForPlayer(MenuStore2, playerid);
		}
	}
	else if(CurrentMenu == MenuStore2) {
		switch(row) {
			case 0: PlayerBuyItem(playerid, PretItemInfo[6][nrItem]);
			case 1: PlayerBuyItem(playerid, PretItemInfo[7][nrItem]);
			case 2: PlayerBuyItem(playerid, PretItemInfo[8][nrItem]);
			case 3: PlayerBuyItem(playerid, PretItemInfo[9][nrItem]);
			case 4: PlayerBuyItem(playerid, PretItemInfo[10][nrItem]);
			case 5: {
				SetCameraBehindPlayer(playerid); 
				TogglePlayerControllable(playerid, true);
				PlayerPlaySound(playerid, 1053  , 0.0, 0.0, 0.0);
				PlayerPlaySound(playerid, 1186  , 0.0, 0.0, 0.0);
				format(string, MAXO_TEXT, "* Thank you for buying from %s. Have a nice day!", BizInfo[PlayerInfo[playerid][pInBizzID]][bDescription]);
				SendClientMessage(playerid, COLOR_WHITE, string);				
			}
		}
	}

	else if(GetPlayerMenu(playerid) == HUMenu1) {
        switch(row) {
            case 0: ShowMenuForPlayer(HUMenu2, playerid);
		}
	}
	else if(GetPlayerMenu(playerid) == HUMenu2) {
	    switch(row) {
	        case 0:
			{
				if(IsPlayerOwnerAHouse(playerid)) {
					if(PlayerInfo[playerid][pCash] >= 100000) {
						if(HouseInfo[casa][hHeal] == 0) {
							HouseInfo[casa][hHeal] = 1;
							SafeGivePlayerMoney(playerid, -100000);
							BizInfo[id][bTakings] += 100000;
							BizInfo[id][bProducts] -= 10;
							TogglePlayerControllable(playerid, true);
							GameTextForPlayer(playerid, "~r~-~y~$100.000", 5000, 1);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Now you've installed a new item at your house, type /heal inside the house.");
							format(string, MAXO_TEXT, "UPDATE bizz SET Takings = %d, Products = %d WHERE ID = %d", BizInfo[id][bTakings], BizInfo[id][bProducts], BizInfo[id][bSQLID]);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
							format(string, MAXO_TEXT, "UPDATE houses SET Heal = %d WHERE ID = %d", HouseInfo[casa][hHeal], HouseInfo[casa][hSQLID]);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
						}
						else
						{
							SendClientMessage(playerid, COLOR_GRAD1, "You already installed this item at your house.");
							TogglePlayerControllable(playerid, true);
							SetCameraBehindPlayer(playerid);
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_GRAD1, "You don't have enough money to purchase this item.");
						TogglePlayerControllable(playerid, true);
						SetCameraBehindPlayer(playerid);
					}
				}
				else
				{
				    SendClientMessage(playerid, COLOR_GRAD1, "You don't own a house.");
					TogglePlayerControllable(playerid, true);
					SetCameraBehindPlayer(playerid);
				}
			}
			case 1:
			{
				if(IsPlayerOwnerAHouse(playerid)) {
					if(PlayerInfo[playerid][pCash] >= 50000) {
						if(HouseInfo[casa][hArmour] == 0) {
							if(PlayerInfo[playerid][pFactiune] == FACT_LSPD || PlayerInfo[playerid][pFactiune] == FACT_FBI) {
								HouseInfo[casa][hArmour] = 1;
								SafeGivePlayerMoney(playerid, -50000);
								BizInfo[id][bTakings] += 50000;
								BizInfo[id][bProducts] -= 5;
								TogglePlayerControllable(playerid, true);
								GameTextForPlayer(playerid, "~r~-~y~$50.000", 5000, 1);
								SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Now you've installed a new item at your house, type /heal inside the house.");
								format(string, MAXO_TEXT, "UPDATE bizz SET Takings = %d, Products = %d WHERE ID = %d", BizInfo[id][bTakings], BizInfo[id][bProducts], BizInfo[id][bSQLID]);
								mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
								format(string, MAXO_TEXT, "UPDATE houses SET Armour = %d WHERE ID = %d", HouseInfo[casa][hArmour], HouseInfo[casa][hSQLID]);
								mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
							}
							else
							{
								SendClientMessage(playerid, COLOR_GRAD1, "You cannot install this item for your house, because you not are cop.");
								TogglePlayerControllable(playerid, true);
								SetCameraBehindPlayer(playerid);
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_GRAD1, "You already installed this item at your house.");
							TogglePlayerControllable(playerid, true);
							SetCameraBehindPlayer(playerid);
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_GRAD1, "You don't have enough money to purchase this item.");
						TogglePlayerControllable(playerid, true);
						SetCameraBehindPlayer(playerid);
					}
				}
				else
				{
				    SendClientMessage(playerid, COLOR_GRAD1, "You don't own a house.");
					TogglePlayerControllable(playerid, true);
					SetCameraBehindPlayer(playerid);
				}
			}
		}
	}
	clear.string(string);
    return 1;
}

// End Of File ...
