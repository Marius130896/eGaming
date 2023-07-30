/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_HousesSystemPriv_included
	#endinput
#else
	#define GF_HousesSystemPriv_included
#endif

stock LoadHouses() {
	mysql_tquery(connectionHandle, "SELECT * FROM houses", "LoadHousesThread", "d", HOUSE_THREAD_ID);
	return true;
}

function LoadHousesThread() {
	rows = cache_num_rows();
	if(rows) {
		for(new i = 1; i <= rows; i ++) {
			new
				h = i - 1;
			if(i != INVALID_VALUE_ID) {
				HouseInfo[i][hSQLID] = i;
				cache_get_row(h, 1, HouseInfo[i][hDescription], .max_len = MAX_PLAYER_NAME);
				HouseInfo[i][hEntrancex] = cache_get_row_float(h, 2);
				HouseInfo[i][hEntrancey] = cache_get_row_float(h, 3);
				HouseInfo[i][hEntrancez] = cache_get_row_float(h, 4);
				HouseInfo[i][hExitx] = cache_get_row_float(h, 5);
				HouseInfo[i][hExity] = cache_get_row_float(h, 6);
				HouseInfo[i][hExitz] = cache_get_row_float(h, 7);
				cache_get_row(h, 8, HouseInfo[i][hOwner], .max_len = MAX_PLAYER_NAME);
				HouseInfo[i][hOwned] = cache_get_row_int(h, 9);
				HouseInfo[i][hInterior] = cache_get_row_int(h, 10);
				HouseInfo[i][hVirtualWorld] = cache_get_row_int(h, 11);
				HouseInfo[i][hLocked] = cache_get_row_int(h, 12);
				HouseInfo[i][hLevel] = cache_get_row_int(h, 13);
				HouseInfo[i][hPrice] = cache_get_row_int(h, 14);
				HouseInfo[i][hRentable] = cache_get_row_int(h, 15);
				HouseInfo[i][hRentPrice] = cache_get_row_int(h, 16);
				HouseInfo[i][hTakings] = cache_get_row_int(h, 17);
				HouseInfo[i][hHeal] = cache_get_row_int(h, 18);
				HouseInfo[i][hArmour] = cache_get_row_int(h, 19);
				HouseInfo[i][hCP][0] = cache_get_row_float(h, 20);
				HouseInfo[i][hCP][1] = cache_get_row_float(h, 21);
				HouseInfo[i][hCP][2] = cache_get_row_float(h, 22);

				if(HouseInfo[i][hOwned] == 0) {
					format(PropertyString, MAXO_TEXT2, "This house is available to buy!\nOwner: %s\nLevel: %d, Price: $%s\nDescription: %s\nTo buy /buyhouse", HouseInfo[i][hOwner], HouseInfo[i][hLevel], FormatNumber(HouseInfo[i][hPrice], 0, '.'), HouseInfo[i][hDescription]);
					HouseInfo[i][hLabel] = Create3DTextLabel(PropertyString, COLOR_PROPERTY_NONE, HouseInfo[i][hEntrancex], HouseInfo[i][hEntrancey], HouseInfo[i][hEntrancez]+1, 25, 0, 1);
					#if defined _stream_pickups
						HouseInfo[i][hPickup] = CreateDynamicPickup(1273, 23, HouseInfo[i][hEntrancex], HouseInfo[i][hEntrancey], HouseInfo[i][hEntrancez],-1);
					#else
						HouseInfo[i][hPickup] = CreatePickup(1273, 23, HouseInfo[i][hEntrancex], HouseInfo[i][hEntrancey], HouseInfo[i][hEntrancez],-1);
					#endif
				}
				else if(HouseInfo[i][hOwned] != 0) {
					if(HouseInfo[i][hRentable] == 0) {
						format(PropertyString, MAXO_TEXT2, "This house is owned by %s\nLevel: %d\nNot available for rent!", HouseInfo[i][hOwner], HouseInfo[i][hLevel]);
						HouseInfo[i][hLabel] = Create3DTextLabel(PropertyString, COLOR_PROPERTY, HouseInfo[i][hEntrancex], HouseInfo[i][hEntrancey], HouseInfo[i][hEntrancez]+1, 25, 0, 1);
					}
					else if(HouseInfo[i][hRentable] != 0) {
						format(PropertyString, MAXO_TEXT2, "House available for rent!\nOwner: %s\nLevel: %d, Rent Price: $%s\nTo Rent Type /rentroom", HouseInfo[i][hOwner], HouseInfo[i][hLevel], FormatNumber(HouseInfo[i][hRentPrice], 0, '.'));
						HouseInfo[i][hLabel] = Create3DTextLabel(PropertyString, COLOR_PROPERTY, HouseInfo[i][hEntrancex], HouseInfo[i][hEntrancey], HouseInfo[i][hEntrancez]+1, 25, 0, 1);
					}
					#if defined _stream_pickups
						HouseInfo[i][hPickup] = CreateDynamicPickup(1272, 23, HouseInfo[i][hEntrancex], HouseInfo[i][hEntrancey], HouseInfo[i][hEntrancez],-1);
					#else
						HouseInfo[i][hPickup] = CreatePickup(1272, 23, HouseInfo[i][hEntrancex], HouseInfo[i][hEntrancey], HouseInfo[i][hEntrancez],-1);
					#endif
				}
				HouseIcon[i] = CreateDynamicMapIcon(HouseInfo[i][hEntrancex], HouseInfo[i][hEntrancey], HouseInfo[i][hEntrancez], 31, MAPICON_LOCAL);
				TotalHouseLoaded ++;
				clear.string(PropertyString);
			}
		} 
		printf("LoadHousesThread() - called (%d houses loaded).", rows);
	}
	return true;
}

function GetHouseSQLID(playerid, Float:range) {
	for(new i = 0; i < sizeof(HouseInfo); i ++) {
		if(IsPlayerInRangeOfPoint(playerid, range, HouseInfo[i][hEntrancex], HouseInfo[i][hEntrancey], HouseInfo[i][hEntrancez]))
			return i;
	}
	return false;
}

stock IsPlayerOwnerAHouse(playerid) {
	new
		casa = PlayerInfo[playerid][pPhousekey];
	if(casa != 0 && strcmp(PlayerName(playerid), HouseInfo[casa][hOwner], true) == 0) {
		return true;
	}
	return false;
}

stock SalveazaCasele(idx) {
	if(idx != 0) {
		new string[MAXO_TEXT2];
		format(string, MAXO_TEXT, "UPDATE houses SET Owner = '%s' WHERE ID = %d", HouseInfo[idx][hOwner], HouseInfo[idx][hSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
		format(string, MAXO_TEXT, "UPDATE houses SET Owned = %d WHERE ID = %d", HouseInfo[idx][hOwned], HouseInfo[idx][hSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
		format(string, MAXO_TEXT, "UPDATE houses SET Locked = %d WHERE ID = %d", HouseInfo[idx][hLocked], HouseInfo[idx][hSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);	
		format(string, MAXO_TEXT, "UPDATE houses SET Rentable = %d WHERE ID = %d", HouseInfo[idx][hRentable], HouseInfo[idx][hSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);	
		format(string, MAXO_TEXT, "UPDATE houses SET Takings = %d WHERE ID = %d", HouseInfo[idx][hTakings], HouseInfo[idx][hSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
		format(string, MAXO_TEXT, "UPDATE houses SET RentPrice = %d WHERE ID = %d", HouseInfo[idx][hRentPrice], HouseInfo[idx][hSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
		format(string, MAXO_TEXT, "UPDATE houses SET Heal = %d WHERE ID = %d", HouseInfo[idx][hHeal], HouseInfo[idx][hSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
		format(string, MAXO_TEXT, "UPDATE houses SET Armour = %d WHERE ID = %d", HouseInfo[idx][hArmour], HouseInfo[idx][hSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
		clear.string(string);
	}
	return true;
}

// End Of File ...
