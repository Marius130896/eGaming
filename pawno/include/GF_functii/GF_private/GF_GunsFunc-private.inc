/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_GunsFuncPriv_included
	#endinput
#else
	#define GF_GunsFuncPriv_included
#endif

stock GetWeaponNameEx(id, name[], len) return format(name, len, "%s", GunNames[id]);

stock LoadProdsGuns() {
	mysql_tquery(connectionHandle, "SELECT * FROM prices_guns", "InitPrArmThread", "d", PRODSGUN_THREAD_ID);
	return true;
}

function InitPrArmThread() {
	new indexarm;
	rows = cache_num_rows();
	if(rows) {
		for(new i; i < rows; i++) {
			indexarm = cache_get_row_int(i, 0);
			PretArmeInfo[indexarm][nrArma] = cache_get_row_int(i, 1);
			PretArmeInfo[indexarm][nrGloante] = cache_get_row_int(i, 2);
			PretArmeInfo[indexarm][maxGloante] = cache_get_row_int(i, 3);
			PretArmeInfo[indexarm][pretArma] = cache_get_row_int(i, 4);
		}
		printf("InitPrArmThread - called (%d prices).", rows);
	}
	return true;
}

stock PlayerBuyWeapon(playerid, weaponID) {
	new idbiz = PlayerInfo[playerid][pInBizzID];
	new string[MAXO_TEXT], gunname[MAX_GUN_NAME], weapon, ammo;
	GetWeaponName(weaponID, gunname, sizeof(gunname));
	new pretarma = PretArmeInfo[weaponID][pretArma];
	if(BizInfo[idbiz][bProducts] > 0) {
		if(PlayerInfo[playerid][pCash] >= pretarma) {
			GetPlayerWeaponData(playerid, WeaponSlot(weaponID), weapon, ammo);
			if((ammo + PretArmeInfo[weaponID][nrGloante]) <= PretArmeInfo[weaponID][maxGloante]) {
				format(string, MAXO_TEXT,"* You bought an %s with %d ammo for $%s.", gunname, PretArmeInfo[weaponID][nrGloante], FormatNumber(pretarma, 0, ',' ));
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				GivePlayerWeapon(playerid, weaponID, PretArmeInfo[weaponID][nrGloante]);
				SafeGivePlayerMoney(playerid,-pretarma);
				BizInfo[idbiz][bProducts] --;
				BizInfo[idbiz][bTakings] += pretarma;
				format(string, MAXO_TEXT2, "UPDATE bizz SET Products = %d, Takings = %d", BizInfo[idbiz][bProducts], BizInfo[idbiz][bTakings], BizInfo[idbiz][bSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
				TogglePlayerControllable(playerid, true);
				SetCameraBehindPlayer(playerid);
				PlayerPlaySound(playerid, 1053  , 0.0, 0.0, 0.0);
				PlayerPlaySound(playerid, 1186  , 0.0, 0.0, 0.0);
				for(new m; m < 2; m ++) {
					if(PlayerInfo[playerid][pDailyMission][m] == MISSION_DELIVERYPRODS)
						CheckMission(playerid, m);
				}
			}
			else
			{
				format(string, MAXO_TEXT,"You can't buy more ammo. Max ammo for %s is %d.", gunname, PretArmeInfo[weaponID][maxGloante]);
				SendClientMessage(playerid, COLOR_GRAD1, string);
				TogglePlayerControllable(playerid, true);
				SetCameraBehindPlayer(playerid);
				PlayerPlaySound(playerid, 1053  , 0.0, 0.0, 0.0);
				PlayerPlaySound(playerid, 1186  , 0.0, 0.0, 0.0);
			}
		}
		else
		{
			format(string, MAXO_TEXT, "You don't have enough money, you need %s to buy this gun.", FormatNumber(pretarma, 0, '.'));
			SendClientMessage(playerid, COLOR_GRAD1, string);
			TogglePlayerControllable(playerid, true);
			SetCameraBehindPlayer(playerid);
			PlayerPlaySound(playerid, 1053  , 0.0, 0.0, 0.0);
			PlayerPlaySound(playerid, 1186  , 0.0, 0.0, 0.0);
		}
	} 
	else 
	{
		GameTextForPlayer(playerid, "~r~Out of stock!", 2500, 1);
		TogglePlayerControllable(playerid, true);
		SetCameraBehindPlayer(playerid);
		PlayerPlaySound(playerid, 1053  , 0.0, 0.0, 0.0);
		PlayerPlaySound(playerid, 1186  , 0.0, 0.0, 0.0);
	}
	clear.string(string);
	return true;
}

stock WeaponSlot(weaponid) {
    new slot;
    switch(weaponid) {
        case 0, 1: slot = 0;
        case 2 .. 9: slot = 1;
        case 10 .. 15: slot = 10;
        case 16 .. 18, 39: slot = 8;
        case 22 .. 24: slot = 2;
        case 25 .. 27: slot = 3;
        case 28, 29, 32: slot = 4;
        case 30, 31: slot = 5;
        case 33, 34: slot = 6;
        case 35 .. 38: slot = 7;
        case 40: slot = 12;
        case 41 .. 43: slot = 9;
        case 44 .. 46: slot = 11;
    }
    return slot;
}

// End Of File ...
