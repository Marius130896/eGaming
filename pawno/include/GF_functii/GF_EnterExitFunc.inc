/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_EnterExitFunc_included
	#endinput
#else
	#define GF_EnterExitFunc_included
#endif

stock EnterPlayerInHouseBiz(playerid) {
	new string[MAXO_TEXT], idhome = GetHouseSQLID(playerid, 3.0);
	new homeid = PlayerInfo[playerid][pInHouseID];
	if(IsPlayerInRangeOfPoint(playerid, 3.0, HouseInfo[idhome][hEntrancex], HouseInfo[idhome][hEntrancey], HouseInfo[idhome][hEntrancez])) {
		if(PlayerInfo[playerid][pPhousekey] == HouseInfo[idhome][hSQLID] || HouseInfo[idhome][hLocked] == 0 || PlayerInfo[playerid][pAdmin] == 1339) {
		    if(GetTickCount() - AntiSpamProtection[playerid] < 1000 && AntiSpamProtection[playerid] != 0) 
		    	return SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: "ALB"Please wait 2 seconds.");
			AntiSpamProtection[playerid] = GetTickCount();
			if(HaveVisibleCheckpoint(playerid))
				return SendClientMessage(playerid, COLOR_LIGHTRED, "You cannot enter in house right now, because you have visible an checkpoint.");
			GameTextForPlayer(playerid, "~w~Welcome Home", 5000, 1);
			format(string, 64, "Inside %s's House.", HouseInfo[idhome][hOwner]);
			TextDrawSetString(propertytxt, string);
			TextDrawShowForPlayer(playerid, propertytxt);
			CreateCP(playerid,HouseInfo[idhome][hCP][0],HouseInfo[idhome][hCP][1],HouseInfo[idhome][hCP][2],1.5,checkpointHouse,CP_HOUSE);
			SafeSetPlayerPos(playerid, HouseInfo[idhome][hExitx], HouseInfo[idhome][hExity], HouseInfo[idhome][hExitz]);
			SafeSetPlayerInterior(playerid, HouseInfo[idhome][hInterior]);
			SafeSetPlayerVirtualWorld(playerid, HouseInfo[idhome][hVirtualWorld]+1000);
			PlayerInfo[playerid][pInHouseID] = HouseInfo[idhome][hSQLID];
		} else GameTextForPlayer(playerid, "~r~Locked", 5000, 1);
	}
	if(IsPlayerInRangeOfPoint(playerid, 3.0, HouseInfo[homeid][hExitx], HouseInfo[homeid][hExity], HouseInfo[homeid][hExitz]) && GetPlayerVirtualWorld(playerid) == HouseInfo[homeid][hVirtualWorld]+1000) {
		if(HouseInfo[homeid][hHeal]) {
			new Float:temphealth;
			GetPlayerHealth(playerid, temphealth);
			if(temphealth < 100)
				SetPlayerHealth(playerid, 100.0), SendClientMessage(playerid, COLOR_WHITE, "You have been healed because of the house upgrade.");
		}
		if(HouseInfo[homeid][hArmour]) {
			new Float:temparmour;
			GetPlayerArmour(playerid, temparmour);
			if(temparmour < 100.0 && IsPlayerCop(playerid))
				SetPlayerArmour(playerid, 100.0);
		}
		SafeSetPlayerPos(playerid, HouseInfo[homeid][hEntrancex], HouseInfo[homeid][hEntrancey], HouseInfo[homeid][hEntrancez]);
		SafeResetPlayerInterior(playerid);
		DeleteCP(checkpointHouse, playerid);
		TextDrawHideForPlayer(playerid, propertytxt);
	}
	new idbiz = GetBizSQLID(playerid, 3.0);
	new bizid = PlayerInfo[playerid][pInBizzID];
	if(IsPlayerInRangeOfPoint(playerid, 3.0, BizInfo[idbiz][bEntrancex], BizInfo[idbiz][bEntrancey], BizInfo[idbiz][bEntrancez])) {
	    if(GetTickCount() - AntiSpamProtection[playerid] < 1000 && AntiSpamProtection[playerid] != 0) 
	    	return SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: "ALB"Please wait 2 seconds.");
		AntiSpamProtection[playerid] = GetTickCount();
		if(NuDeschideBiz(idbiz))
			return GameTextForPlayer(playerid, "~r~Locked", 5000, 1);
		if(HaveVisibleCheckpoint(playerid))
			return SendClientMessage(playerid, COLOR_LIGHTRED, "You cannot enter in biz right now, because you have visible an checkpoint.");
		if(BizInfo[idbiz][bProducts] < 1)
			return GameTextForPlayer(playerid, "~r~Out of stock", 2500, 1);
		SafeSetPlayerPos(playerid, BizInfo[idbiz][bExitx], BizInfo[idbiz][bExity], BizInfo[idbiz][bExitz]);
		SafeSetPlayerInterior(playerid, BizInfo[idbiz][bInterior]);
		SafeSetPlayerVirtualWorld(playerid, BizInfo[idbiz][bVirtualWorld]+2000);
		BizInfo[idbiz][bTakings] += BizInfo[idbiz][bEnterPrice];
		SafeGivePlayerMoney(playerid, -BizInfo[idbiz][bEnterPrice]);
		if(BizInfo[idbiz][bType] == BIZ_TYPE_24_7 || BizInfo[idbiz][bType] == BIZ_TYPE_BURGERSHOT || 
			BizInfo[idbiz][bType] == BIZ_TYPE_BINCO || BizInfo[idbiz][bType] == BIZ_TYPE_HOUSEUPG ||
			BizInfo[idbiz][bType] == BIZ_TYPE_BANK)
			BizInfo[idbiz][bProducts] -= 3;
		else
			BizInfo[idbiz][bProducts] -= 2;
		format(string, MAXO_TEXT, "UPDATE bizz SET Takings = %d, Products = %d WHERE ID = %d", BizInfo[idbiz][bTakings], BizInfo[idbiz][bProducts], BizInfo[idbiz][bSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
		format(string, 13, "~r~-~y~$%s", FormatNumber(BizInfo[idbiz][bEnterPrice], 0, '.'));
		GameTextForPlayer(playerid, string, 5000, 1);
		format(string, 64, "Inside %s's Biz.", BizInfo[idbiz][bOwner]);
		TextDrawSetString(propertytxt, string);
		TextDrawShowForPlayer(playerid, propertytxt);
		PlayerInfo[playerid][pInBizzID] = idbiz;
		switch(BizInfo[idbiz][bType]) {
			case BIZ_TYPE_GS: CreateCP(playerid,314.2584,-133.6431,999.6016,2.0,checkpointEnterBiz,CP_ENTER_BIZ);
			case BIZ_TYPE_HOUSEUPG: CreateCP(playerid,2176.8533,1619.2428,999.9766,2.0,checkpointEnterBiz,CP_ENTER_BIZ);
			case BIZ_TYPE_BURGERSHOT: CreateCP(playerid,375.7126,-67.7081,1001.5151,2.0,checkpointEnterBiz,CP_ENTER_BIZ);
			case BIZ_TYPE_24_7: CreateCP(playerid,-22.1478,-138.6254,1003.5469,2.0,checkpointEnterBiz,CP_ENTER_BIZ);
			case BIZ_TYPE_BINCO: CreateCP(playerid,207.4880,-100.7235,1005.2578,2.0,checkpointEnterBiz,CP_ENTER_BIZ);
		}
	}
	if(IsPlayerInRangeOfPoint(playerid, 3.0, BizInfo[bizid][bExitx], BizInfo[bizid][bExity], BizInfo[bizid][bExitz])) {
		SafeSetPlayerPos(playerid, BizInfo[bizid][bEntrancex], BizInfo[bizid][bEntrancey], BizInfo[bizid][bEntrancez]);
		DeleteCP(checkpointEnterBiz, playerid);
		SafeSetPlayerInterior(playerid, 0);
		SafeSetPlayerVirtualWorld(playerid, 0);
		PlayerInfo[playerid][pInBizzID] = 0;
		TextDrawHideForPlayer(playerid, propertytxt);
	}
	clear.string(string);
	return true;
}

stock EnterPlayerInHQ(playerid) {
	for(new i = 0; i < sizeof(FactionInfo); i ++) {
		if(IsPlayerInRangeOfPoint(playerid, 3.0, FactionInfo[i][fHQEnterx], FactionInfo[i][fHQEntery], FactionInfo[i][fHQEnterz])) {
			if(PlayerInfo[playerid][pFactiune] == FactionInfo[i][fSQLID]) {
				if(!HaveVisibleCheckpoint(playerid)) {
					if(!PlayerInfo[playerid][pWlvl]) {
						if(PlayerInfo[playerid][pFactiune] != FACT_LSPD) {
							if(gGlobalTick - AntiSpamProtection[playerid] > 1000) {
								SafeSetPlayerPos(playerid, FactionInfo[i][fHQExitx], FactionInfo[i][fHQExity], FactionInfo[i][fHQExitz]);
								SafeSetPlayerInterior(playerid, FactionInfo[i][fInterior]);
								SafeSetPlayerVirtualWorld(playerid, FactionInfo[i][fVirtualWorld]);
								PlayerInfo[playerid][pInHQID] = PlayerInfo[playerid][pFactiune];
								AntiSpamProtection[playerid] = GetTickCount();
							} else SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: "ALB"Please wait 2 seconds.");
						} else ShowPlayerDialog(playerid, DIALOGID_LIFT1_LSPD, DIALOG_STYLE_LIST, "Elevator", "HeadQuarter\nRoof LSPD\nLSPD Station", "Select", "Cancel");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You are wanted by cop, can't enter in HeadQuarter.");
				} else SendClientMessage(playerid, COLOR_LIGHTRED, "You cannot enter in HQ right now, because you have visible an checkpoint.");
			}
		}
		if(IsPlayerInRangeOfPoint(playerid, 3.0, FactionInfo[i][fHQExitx], FactionInfo[i][fHQExity], FactionInfo[i][fHQExitz])) {
			if(PlayerInfo[playerid][pFactiune] == FactionInfo[i][fSQLID]) {
				if(PlayerInfo[playerid][pFactiune] != FACT_LSPD) {
					SafeSetPlayerPos(playerid, FactionInfo[i][fHQEnterx], FactionInfo[i][fHQEntery], FactionInfo[i][fHQEnterz]);
					SafeSetPlayerInterior(playerid, 0);
					SafeSetPlayerVirtualWorld(playerid, 0);
					PlayerInfo[playerid][pInHQID] = 0;
				}
				else if(PlayerInfo[playerid][pFactiune] == FACT_LSPD) {
					ShowPlayerDialog(playerid, DIALOGID_LIFT2_LSPD, DIALOG_STYLE_LIST, "Elevator", "Ground floor\nRoof LSPD\nLSPD Station", "Select", "Cancel");
				}
			}
		}
		if(IsPlayerInRangeOfPoint(playerid, 3.0, FactionInfo[i][fTREnterx], FactionInfo[i][fTREntery], FactionInfo[i][fTREnterz])) {
			if(PlayerInfo[playerid][pFactiune] == FactionInfo[i][fSQLID]) {
			    if(GetTickCount() - AntiSpamProtection[playerid] < 1000 && AntiSpamProtection[playerid] != 0) 
			    	return SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: "ALB"Please wait 2 seconds.");
				AntiSpamProtection[playerid] = GetTickCount();
				if(!HaveVisibleCheckpoint(playerid)) {
					if(!PlayerInfo[playerid][pWlvl]) {
						SafeSetPlayerPos(playerid, FactionInfo[i][fTRExitx], FactionInfo[i][fTRExity], FactionInfo[i][fTRExitz]);
						SafeSetPlayerInterior(playerid, FactionInfo[i][fTRInterior]);
						SafeSetPlayerVirtualWorld(playerid, FactionInfo[i][fVirtualWorld]);
						PlayerInfo[playerid][pInHQID] = PlayerInfo[playerid][pFactiune];
					} else SendClientMessage(playerid, COLOR_GRAD1, "You are wanted by cop, can't enter in Training Room.");
				} else SendClientMessage(playerid, COLOR_LIGHTRED, "You cannot enter in HQ right now, because you have visible an checkpoint.");
			}
		}
		if(IsPlayerInRangeOfPoint(playerid, 3.0, FactionInfo[i][fTRExitx], FactionInfo[i][fTRExity], FactionInfo[i][fTRExitz])) {
			if(PlayerInfo[playerid][pFactiune] == FactionInfo[i][fSQLID]) {
				SafeSetPlayerPos(playerid, FactionInfo[i][fTREnterx], FactionInfo[i][fTREntery], FactionInfo[i][fTREnterz]);
				SafeSetPlayerInterior(playerid, 0);
				SafeSetPlayerVirtualWorld(playerid, 0);
				PlayerInfo[playerid][pInHQID] = 0;
			}
		}
	}
	return true;
}

stock EnterPlayerInOtherInterior(playerid) {
	new string[MAXO_TEXT];
	if(!HaveVisibleCheckpoint(playerid)) {
		if(IsPlayerInRangeOfPoint(playerid, 3.0, 1555.4949, -1675.5715, 16.1953)) {
			if(gGlobalTick - AntiSpamProtection[playerid] > 1000) {
				SafeSetPlayerPos(playerid, 246.7885, 62.3467, 1003.6406);
				SafeSetPlayerInterior(playerid, 6);
				SafeSetPlayerVirtualWorld(playerid, LSPD_VW);
				format(string, MAXO_TEXT, "~w~Welcome to ~n~ LSPD Station ~n~ ~y~ %s", PlayerName(playerid));
				GameTextForPlayer(playerid, string, 5000, 1);
				AntiSpamProtection[playerid] = GetTickCount();
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: "ALB"Please wait 2 seconds.");
		}
		if(IsPlayerInRangeOfPoint(playerid, 3.0, -1605.6346, 710.4967, 13.8672)) {
			if(gGlobalTick - AntiSpamProtection[playerid] > 1000) {
				SafeSetPlayerPos(playerid, 246.7885, 62.3467, 1003.6406);
				SafeSetPlayerInterior(playerid, 6);
				SafeSetPlayerVirtualWorld(playerid, SFPD_VW);
				format(string, MAXO_TEXT, "~w~Welcome to ~n~ SFPD Station ~n~ ~y~ %s", PlayerName(playerid));
				GameTextForPlayer(playerid, string, 5000, 1);
				AntiSpamProtection[playerid] = GetTickCount();
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: "ALB"Please wait 2 seconds.");
		}
		if(IsPlayerInRangeOfPoint(playerid, 3.0, 1564.9653, -1666.9790, 28.3956)) {
			if(PlayerInfo[playerid][pFactiune] == FACT_LSPD) {
				ShowPlayerDialog(playerid, DIALOGID_LIFT3_LSPD, DIALOG_STYLE_LIST, "Elevator", "HeadQuarter\nGround floor\nLSPD Station", "Select", "Cancel");
			}
		}
		if(IsPlayerInRangeOfPoint(playerid, 3.0, -2695.5554, 640.1650, 14.4531)) {
			if(PlayerInfo[playerid][pFactiune] == FACT_MEDIC) {
				if(gGlobalTick - AntiSpamProtection[playerid] > 1000) {
					SafeSetPlayerPos(playerid, -2682.5168, 589.8640, 66.0938);
					SafeSetPlayerInterior(playerid, 0);
					SafeSetPlayerVirtualWorld(playerid, 0);
					AntiSpamProtection[playerid] = GetTickCount();
				} else SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: "ALB"Please wait 2 seconds.");
			}
		}
		if(IsPlayerInRangeOfPoint(playerid, 3.0, -2065.4038, 486.5061, 139.7422)) {
			if(PlayerInfo[playerid][pFactiune] == FACT_CNN) {
				if(gGlobalTick - AntiSpamProtection[playerid] > 1000) {
					SafeSetPlayerPos(playerid, -2060.9719, 461.2803, 35.1719);
					SafeSetPlayerInterior(playerid, 0);
					SafeSetPlayerVirtualWorld(playerid, 0);
					AntiSpamProtection[playerid] = GetTickCount();
				} else SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: "ALB"Please wait 2 seconds.");
			}
		}
		if(IsPlayerInRangeOfPoint(playerid, 3.0, 246.5154,88.0078,1003.6406) && GetPlayerVirtualWorld(playerid) == LSPD_VW) {
			SafeSetPlayerPos(playerid, FactionInfo[FACT_LSPD][fHQExitx], FactionInfo[FACT_LSPD][fHQExity], FactionInfo[FACT_LSPD][fHQExitz]);
			SafeSetPlayerInterior(playerid, FactionInfo[FACT_LSPD][fInterior]);
			SafeSetPlayerVirtualWorld(playerid, FactionInfo[FACT_LSPD][fVirtualWorld]);
			PlayerInfo[playerid][pInHQID] = PlayerInfo[playerid][pFactiune];
			format(string, MAXO_TEXT, "~w~Headquarter ~n~ ~y~%s", FactionInfo[FACT_LSPD][fName]);
			GameTextForPlayer(playerid, string, 5000, 1);
			clear.string(string);
		}
		//----------------------------------- intrare lift medici LS
		if(IsPlayerInRangeOfPoint(playerid, 3.0, 1172.37, -1325.5, 15.4063)) {
			if(PlayerInfo[playerid][pFactiune] == FACT_MEDIC) {
				if(gGlobalTick - AntiSpamProtection[playerid] > 1000) {
					SafeSetPlayerPos(playerid, 1161.51, -1329.66, 31.4949);
					SafeSetPlayerInterior(playerid, 0);
					SafeSetPlayerVirtualWorld(playerid, 0);
					AntiSpamProtection[playerid] = GetTickCount();
				} else SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: "ALB"Please wait 2 seconds.");
			}
		}
		//----------------------------------- intrare crack house
		if(IsPlayerInRangeOfPoint(playerid, 3.0, 2165.9526,-1671.1735,15.0732)) {
			if(gGlobalTick - AntiSpamProtection[playerid] > 1000) {
				SafeSetPlayerPos(playerid, 318.5867,1114.7329,1083.8828);
				GameTextForPlayer(playerid, "~w~Crack House", 2500, 1);
				SafeSetPlayerInterior(playerid, 5);
				AntiSpamProtection[playerid] = GetTickCount();
			} else SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: "ALB"Please wait 2 seconds.");
		}
		//----------------------------------- intrare inchisoare LS
		if(IsPlayerInRangeOfPoint(playerid, 3.0, 1797.4335,-1578.8820,14.0848)) {
			if(IsPlayerCop(playerid)) {
				if(gGlobalTick - AntiSpamProtection[playerid] > 1000) {
					SafeSetPlayerPos(playerid, 1779.8503,-1576.4623,1734.9430);
					SafeSetPlayerInterior(playerid, 0);
					SafeSetPlayerVirtualWorld(playerid, JAIL_VW);
					AntiSpamProtection[playerid] = GetTickCount();
				} else SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: "ALB"Please wait 2 seconds.");
			}
		}
	}
	if(IsPlayerInRangeOfPoint(playerid, 3.0, 246.7885, 62.3467, 1003.6406)) {
		if(GetPlayerVirtualWorld(playerid) == LSPD_VW) {
			SafeSetPlayerPos(playerid, 1555.4949, -1675.5715, 16.1953);
			GameTextForPlayer(playerid, "~w~Los Santos", 5000, 1);
		}
		else if(GetPlayerVirtualWorld(playerid) == SFPD_VW) {
			SafeSetPlayerPos(playerid, -1605.6346, 710.4967, 13.8672);
			GameTextForPlayer(playerid, "~w~San Fierro", 5000, 1);
		}
		SafeSetPlayerInterior(playerid, 0);
		SafeSetPlayerVirtualWorld(playerid, 0);
	}
	if(IsPlayerInRangeOfPoint(playerid, 3.0, -2682.5168, 589.8640, 66.0938)) {
		if(PlayerInfo[playerid][pFactiune] == FACT_MEDIC) {
			SafeSetPlayerPos(playerid, -2695.5554, 640.1650, 14.4531);
			SafeSetPlayerInterior(playerid, 0);
			SafeSetPlayerVirtualWorld(playerid, 0);
		}
	}
	if(IsPlayerInRangeOfPoint(playerid, 3.0, -2060.9719, 461.2803, 35.1719)) {
		if(PlayerInfo[playerid][pFactiune] == FACT_CNN) {
			SafeSetPlayerPos(playerid, -2065.4038, 486.5061, 139.7422);
			SafeSetPlayerInterior(playerid, 0);
			SafeSetPlayerVirtualWorld(playerid, 0);
		}
	}
	if(IsPlayerInRangeOfPoint(playerid, 3.0, 1161.51, -1329.66, 31.4949)) {
		if(PlayerInfo[playerid][pFactiune] == FACT_MEDIC) {
			SafeSetPlayerPos(playerid, 1172.37, -1325.5, 15.4063);
			SafeSetPlayerInterior(playerid, 0);
			SafeSetPlayerVirtualWorld(playerid, 0);
		}
	}
	if(IsPlayerInRangeOfPoint(playerid, 3.0, 318.5867,1114.7329,1083.8828)) {
		SafeSetPlayerPos(playerid, 2165.9526,-1671.1735,15.0732);
		GameTextForPlayer(playerid, "~w~Los Santos", 2500, 1);
		SafeSetPlayerInterior(playerid, 0);
	}
	if(IsPlayerInRangeOfPoint(playerid, 3.0, 1779.8503,-1576.4623,1734.9430)) {
		if(IsPlayerCop(playerid)) {
			SafeSetPlayerInterior(playerid, 0);
			SafeSetPlayerVirtualWorld(playerid, 0);
			SafeSetPlayerPos(playerid, 1797.4335,-1578.8820,14.0848);
		}
	}
	HidePlayerInformation(playerid);
	return true;
}

// End Of File ...