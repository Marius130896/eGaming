/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_CommandsGen_included
	#endinput
#else
	#define GF_CommandsGen_included
#endif

#tryinclude <GF_functii/GF_private/GF_CommandsPriv-private>

COMMAND:stats(playerid, params[]) {
	ShowStats(playerid, playerid);
	return true;
}

COMMAND:help(playerid, params[]) {
	SendClientMessage(playerid, COLOR_GREEN, "_____________________________________________________________________________");
	SendClientMessage(playerid, COLOR_GRAD1, "*** ACCOUNT *** /stats");
	SendClientMessage(playerid, COLOR_GRAD1, "*** GENERAL *** /licenses /carradio /engine /buylevel /admins /spawnchange /disabletime /n(ewbie) /spawnls /spawnsf /getfuel");
	SendClientMessage(playerid, COLOR_GRAD1, "*** GENERAL *** /needhelp /mutetime /smokecig /stats /accept /cancel /usepills /report /helpers /unrent /placenews /dice");
	SendClientMessage(playerid, COLOR_GRAD1, "*** GENERAL *** /get /accept /cancel /service /contract /placenews /w(hisper) /factions /leaders /pay /transfer /numbers");
	SendClientMessage(playerid, COLOR_GRAD1, "*** GENERAL *** /bank /withdraw /jobs /skills /surrender /time /ad(vertisment) /usedrugs /getout /toglive /me /call /sms");
	if(PlayerInfo[playerid][pFactiune]) {
		switch(PlayerInfo[playerid][pFactiune]) {
			case FACT_LSPD, FACT_FBI:
			{
				SendClientMessage(playerid, COLOR_GRAD2, "*** S.A.P.D. *** /r(adio) /d(epartment) /m(egaphone) /su(spect) /jail /wanted /backup /jaillist");
				SendClientMessage(playerid, COLOR_GRAD2, "*** S.A.P.D. *** /showbadge /getincar /cuff /uncuff /frisk /take /ticket /duty /ram /backupclear");
				SendClientMessage(playerid, COLOR_GRAD2, "*** S.A.P.D. *** /gov(ernment) /unjail /clearwanted /roadblock /s(how)m(embers) /spikes");
			}
			case FACT_MEDIC: SendClientMessage(playerid, COLOR_GRAD2, "*** Medics/Firemans: /r(adio) /d(epartment) /s(how)m(embers) /heal /sellpills /factionspawn");
			case FACT_LCN, FACT_YKZ, FACT_BLOODS, FACT_CRIPS: SendClientMessage(playerid, COLOR_GRAD2, "*** Faction *** /f(action) /rivalwar /s(how)m(embers) /tie /untie /heal /factionspawn");
			case FACT_HITMAN: SendClientMessage(playerid, COLOR_GRAD2, "*** Faction *** /f(action) /s(how)m(embers) /heal /portable /checkcontracts /deletecontracts /factionspawn");
			case FACT_CNN: SendClientMessage(playerid, COLOR_GRAD2, "*** Faction *** /f(action) /s(how)m(embers) /heal /news /newsduty /acceptnews /live /rejectnews /factionspawn");
			case FACT_TAXI: SendClientMessage(playerid, COLOR_GRAD2, "*** Faction *** /f(action) /s(how)m(embers) /heal /fare /factionspawn");
			case FACT_FMA: SendClientMessage(playerid, COLOR_GRAD2, "*** Faction *** /f(action) /s(how)m(embers) /heal /racers /joinrace /loadrace /leave /racekick /votecol /endrace /ready");
		}
	}
	if(PlayerInfo[playerid][pJob] > JOB_NONE) {
		switch(PlayerInfo[playerid][pJob]) {
			case JOB_FARMER: SendClientMessage(playerid, COLOR_GRAD3, "*** Job Farmer *** /startfarm /stopfarm /takeflour /sellflour");
			case JOB_SWEEPER: SendClientMessage(playerid, COLOR_GRAD3, "*** Job Street Sweeper *** /startsweep /stopsweep");
			case JOB_DUSTMAN: SendClientMessage(playerid, COLOR_GRAD3, "*** Job Dustman *** /startcollect /stopcollect");
			case JOB_TRUCKER: SendClientMessage(playerid, COLOR_GRAD3, "*** Job Trucker *** /getprods /sellprods");
			case JOB_CARJACKER: SendClientMessage(playerid, COLOR_GRAD3, "*** Job Car Jacker *** /dropcar");
			case JOB_ARMSDEALER: SendClientMessage(playerid, COLOR_GRAD3, "*** Job Arms Dealer *** /buymats /delivermats /sellgun");
			case JOB_DRUGSDEALER: SendClientMessage(playerid, COLOR_GRAD3, "*** Job Drugs Dealer *** /buydrugs /deliverdrugs /selldrugs");
		}
	}
	SendClientMessage(playerid, COLOR_GRAD5, "** OTHER *** /househelp /bizhelp");
	SendClientMessage(playerid, COLOR_GRAD6, "** PERSONAL VEHICLE *** /mycarhelp");
	if(PlayerInfo[playerid][pAdmin]) SendClientMessage(playerid, COLOR_GRAD2, "*** ADMIN *** /a(dmin)h(elp)");
	if(PlayerInfo[playerid][pLeader]) SendClientMessage(playerid, COLOR_GRAD2, "*** LEADER *** /leaderhelp");
	if(PlayerInfo[playerid][pHelper]) SendClientMessage(playerid, COLOR_GRAD2, "*** HELPER *** /helperhelp");
	SendClientMessage(playerid, COLOR_GREEN, "_____________________________________________________________________________");
	return true;
}

COMMAND:adminhelp(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin]) {
		SendClientMessage(playerid, COLOR_GREEN, "_____________________________________________________________________________");
		if(PlayerInfo[playerid][pAdmin] >= 1) {
			SendClientMessage(playerid, COLOR_GRAD1, "*** ADMIN 1: /ban /warn(ining) /a(dminchat) /kick /respawn /checkweapons /respawncars or /rac /check");
			SendClientMessage(playerid, COLOR_GRAD1, "*** ADMIN 1: /spec(tate) /spec(tate)off /o(oc) /c(lear)c(hat) /setint /setvw /checkactivity /prison");
			SendClientMessage(playerid, COLOR_GRAD1, "*** ADMIN 1: /mute /unmute /freeze /unfreeze /goto /goback /slap /givegun /aunjail /ajail /fly /unprison");
		}
		if(PlayerInfo[playerid][pAdmin] >= 2) {
			SendClientMessage(playerid, COLOR_GRAD2, "*** ADMIN 2: /gotopos /weather /givelicense /resetwartime /ouninvite");
			SendClientMessage(playerid, COLOR_GRAD2, "*** ADMIN 2: /gotog /gotom /gotols /gotosf /gotolv /takelicense /nonewbie /o(ffline)ban /o(ffline)warn(ning)");
		}
		if(PlayerInfo[playerid][pAdmin] >= 3) {
			SendClientMessage(playerid, COLOR_GRAD3, "*** ADMIN 3: /levelupall /rpupall");
			SendClientMessage(playerid, COLOR_GRAD3, "*** ADMIN 3: /healall /armourall /skydive /gotocar /fuck /fixveh");
		}
		if(PlayerInfo[playerid][pAdmin] >= 4) {
			SendClientMessage(playerid, COLOR_GRAD4, "*** ADMIN 4: /gotohouse /gotobiz");
		}
		if(PlayerInfo[playerid][pAdmin] >= 5) {
			SendClientMessage(playerid, COLOR_GRAD5, "*** ADMIN 5: /givemoneyacc /setstat /unban /unbanip /sethp /resetmissions /makeleader /givemoney");
		}
		if(PlayerInfo[playerid][pAdmin] >= 1337) {
			SendClientMessage(playerid, COLOR_GRAD5, "*** ADMIN 1337+: /makeadmin /makehelper /startfire /changetypesafe");
			SendClientMessage(playerid, COLOR_GRAD5, "*** ADMIN 1337+: /insertstock /updatestock /spawntvehicle /setfactionlevel");
		}
		if(IsPlayerFounder(playerid)) {
			SendClientMessage(playerid, COLOR_GRAD5, "*** Owner/Scripter: /updatec(ar)p(osition) /createvehicle /addpickup /addobject /createhouse /createbiz /enterupdatehq /exitupdatehq");
			SendClientMessage(playerid, COLOR_GRAD5, "*** Owner/Scripter: /c(reate)f(action) /addturf /editnameturf /updatecolorcar /u(pdate)spawn /u(pdate)spawn2 /updaterankname /createsafe");
			SendClientMessage(playerid, COLOR_GRAD5, "*** Owner/Scripter: /updateexithouse /updatecpfromhouse /enterupdatetr /exitupdatetr /addskin /updateskin /propertywipe");
		}
		SendClientMessage(playerid, COLOR_GREEN, "_____________________________________________________________________________");
	} else NotAuthorized();
	return true;
}

COMMAND:ah(playerid, params[]) {
	return cmd_adminhelp(playerid, params);
}

COMMAND:helperhelp(playerid, params[]) {
	if(PlayerInfo[playerid][pHelper]) {
		SendClientMessage(playerid, COLOR_GREEN, "_____________________________________________________________________________");
		SendClientMessage(playerid, COLOR_GRAD1, "*** HELPER COMMANDS *** /makehelper (This command is available for helpers level +1337);");
		SendClientMessage(playerid, COLOR_GRAD2, "*** HELPER COMMANDS *** /respawn /setint /setvw /freeze /unfreeze /goto /goback /hsay /hc /slap /disable /undisable");
		SendClientMessage(playerid, COLOR_GREEN, "_____________________________________________________________________________");
	} else NotAuthorized();
	return true;
}

COMMAND:hh(playerid, params[]) {
	return cmd_helperhelp(playerid, params);
}

COMMAND:buylevel(playerid, params[]) {
	new
		string[MAXO_TEXT], nxtlevel, costlevel, expamount;
	if(PlayerInfo[playerid][pLevel] >= 0) {
		nxtlevel = PlayerInfo[playerid][pLevel] + 1;
		costlevel = nxtlevel * levelcost;
		expamount = nxtlevel * levelexp;
		if(PlayerInfo[playerid][pCash] < costlevel) {
			format(string, MAXO_TEXT, "You do not have enough Cash ($%s).", FormatNumber(costlevel, 0, '.'));
			SendClientMessage(playerid, COLOR_GRAD1, string);
		}
		else if(PlayerInfo[playerid][pExp] < expamount) {
			format(string, MAXO_TEXT, "You need %d Respect Points, you have curently %d.", expamount, PlayerInfo[playerid][pExp]);
			SendClientMessage(playerid, COLOR_GRAD1, string);
		}
		else
		{
			format(string, MAXO_TEXT, "~g~LEVEL UP ~n~ ~w~You are now %d", nxtlevel);
			GameTextForPlayer(playerid, string, 5000, 1);
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			PlayerPlayMusic(playerid);
			SafeGivePlayerMoney(playerid, -costlevel);
			PlayerInfo[playerid][pLevel] ++;
			PlayerInfo[playerid][pExp] -= expamount;
			PlayerInfo[playerid][pUpgradeP] += 2;
			format(string, MAXO_TEXT, "UPDATE players SET Level = %d WHERE ID = %d", PlayerInfo[playerid][pLevel], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(string, MAXO_TEXT, "UPDATE players SET Respect = %d WHERE ID = %d", PlayerInfo[playerid][pExp], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(string, MAXO_TEXT, "UPDATE players SET UpgradeP = %d WHERE ID = %d", PlayerInfo[playerid][pUpgradeP], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(string, MAXO_TEXT, "You bought Level %d for $%s, type /stats to see the new details.", nxtlevel, FormatNumber(costlevel, 0, '.'));
			SendClientMessage(playerid, COLOR_OOC, string);
			/* Award for Referral ID */
			new refMoneys, refRespect;
			if(PlayerInfo[playerid][pReferralID] > 0) {
				if(PlayerInfo[playerid][pLevel] < 15)
					refMoneys = ((PlayerInfo[playerid][pLevel] + 1) * costlevel) / 95,
					refRespect = (((PlayerInfo[playerid][pLevel] + (PlayerInfo[playerid][pLevel] - 1)) * expamount)) / (PlayerInfo[playerid][pLevel] * 17);
				else if(ISBetween(PlayerInfo[playerid][pLevel], 15, 30))
					refMoneys = (((PlayerInfo[playerid][pLevel] + 1) * costlevel)) / 90,
					refRespect = (((PlayerInfo[playerid][pLevel] + (PlayerInfo[playerid][pLevel] - 1)) * expamount)) / (PlayerInfo[playerid][pLevel] * 15);
				else if(PlayerInfo[playerid][pLevel] > 30)
					refMoneys = (((PlayerInfo[playerid][pLevel] + 1) * costlevel)) / 85,
					refRespect = (((PlayerInfo[playerid][pLevel] + (PlayerInfo[playerid][pLevel] - 1)) * expamount)) / (PlayerInfo[playerid][pLevel] * 13);
				format(string, MAXO_TEXT, "SELECT `Name`, `ReferralCash`, `ReferralRespect` FROM `players` WHERE `ID` = '%d'", PlayerInfo[playerid][pReferralID]);
				mysql_tquery(connectionHandle, string, "ReferralBonus", "dddd", playerid, PlayerInfo[playerid][pReferralID], refMoneys, refRespect);
			}
		}
		clear.string(string);
	}
	return true;
}

/*COMMAND:upgrade(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(!sscanf(params, "s[10]", params)) {
		if(!strcmp(params, "shealth", true)) {
			if(PlayerInfo[playerid][pUpgradeP]) {
				if(PlayerInfo[playerid][pSHealth] < 100) {
					PlayerInfo[playerid][pSHealth] += 10.0;
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					PlayerPlayMusic(playerid);
					format(string, MAXO_TEXT, "UPDATE players SET SHealth = %f WHERE ID = %d", PlayerInfo[playerid][pSHealth], PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					format(string, sizeof(string), "New Upgrade: You Will Now Spawn With %.1f Health(+10).", PlayerInfo[playerid][pSHealth]);
					SendClientMessage(playerid, COLOR_OOC, string);
					GameTextForPlayer(playerid, "~g~upgraded!", 5000, 1);
				} else SendClientMessage(playerid, COLOR_GRAD1, "You have already maximum spawn health.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have enough Upgrade Points available.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "Option available, please try again.");
	} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/upgrade [option]"), SendClientMessage(playerid, COLOR_GRAD1, "Options available: shealth");
	return true;
}

COMMAND:resetupgrades(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pCash] > 99999) {
		if(PlayerInfo[playerid][pLevel] > 2) {
			PlayerInfo[playerid][pUpgradeP] = (PlayerInfo[playerid][pLevel] - 1) * 2;
			SafeGivePlayerMoney(playerid, -100000);
			PlayerInfo[playerid][pSHealth] = 30.0;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			PlayerPlayMusic(playerid);
			format(string, MAXO_TEXT, "UPDATE players SET UpgradeP = %d WHERE ID = %d", PlayerInfo[playerid][pUpgradeP], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(string, MAXO_TEXT, "UPDATE players SET SHealth = %f WHERE ID = %d", PlayerInfo[playerid][pSHealth], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(string, MAXO_TEXT, "You have %d unspent Upgrade Points.", PlayerInfo[playerid][pUpgradeP]);
			SendClientMessage(playerid, COLOR_OOC, string);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must have the level much more of 2.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have $100.000 cash for this action.");
	return true;
}*/

COMMAND:needhelp(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(!PlayerInfo[playerid][pDeelayNeedHelp]) {
		if(!PlayerInfo[playerid][pDisable]) {
			if(PlayerInfo[playerid][pMute])
				return IsPlayerSilent();
			PlayerInfo[playerid][pDeelayNeedHelp] = 30;
			format(string, MAXO_TEXT, "%s[%d] - %s are nevoie de ajutor.", PlayerName(playerid), playerid, FactionInfo[PlayerInfo[playerid][pFactiune]][fName]);
			foreach(Player, i) {
				if(PlayerInfo[i][pHelper])
					SendClientMessage(i, COLOR_LIGHTRED, string);
				if(i == INVALID_PLAYER_ID)
					return SendClientMessage(playerid, COLOR_GRAD1, "In this momment not is any helper online.");
			}
			SendClientMessage(playerid, COLOR_OOC, "* Ramai pe loc, mesajul tau a fost trimis catre helperii disponibili.");
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You have been disabled by an helper.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You must wait 30 seconds.");
	return true;
}

COMMAND:mutetime(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pMute]) {
		format(string, MAXO_TEXT, "~w~You have ~r~%s ~w~~n~until you ~g~finish ~w~MUTE.", ConvertTime(PlayerInfo[playerid][pMuteTime]));
		GameTextForPlayer(playerid, string, 5000, 1);
		clear.string(string);
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not muted.");
	return true;
}

COMMAND:smokecig(playerid, params[]) {
	if(PlayerInfo[playerid][pLighter] != 0) {
		if(PlayerInfo[playerid][pCigarettes] != 0) {
			PlayerInfo[playerid][pCigarettes] --;
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
			SendClientMessage(playerid, -1, "* You have lighted an cigarette.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have any cigarette.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have an lighter.");
	return true;
}

COMMAND:dice(playerid, params[]) {
	new string[MAXO_TEXT], dice = random(6)+1;
	if(PlayerInfo[playerid][pDice] > 0) {
		format(string, MAXO_TEXT, "* %s Throws a Dice that lands on %d.", PlayerName(playerid), dice);
		SendPlayerMessage(5.0, playerid, string, COLOR_GREEN);
		clear.string(string);
	} else SendClientMessage(playerid, COLOR_GRAD1, "You Don't Have A Dice.");
	return 1;
}

COMMAND:accept(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(!sscanf(params, "s[24]s[64]", PartialName[playerid][nume_introdus], params)) {
		CheckName(playerid, PartialName[playerid][nume_introdus]);
		targetid = PartialName[playerid][jucator_gasit];
		if(targetid != INVALID_PLAYER_ID) {
			if(strlen(params) < 64) {
				if(!strcmp(params, "ticket", true)) {
					if(TicketOffer[playerid] < 999) {
						SafeGivePlayerMoney(playerid, -TicketMoney[playerid]);
						SafeGivePlayerMoney(targetid, TicketMoney[playerid]);
						ConsumingMoney[targetid] = 1;
						format(string, MAXO_TEXT, "* You have paid the Ticket of $%s to Officer %s.", FormatNumber(TicketMoney[playerid], 0, '.'), PlayerName(targetid));
						SendClientMessage(playerid, COLOR_FAMILY, string);
						format(string, MAXO_TEXT, "* %s has paid your Ticket of $%s.", PlayerName(playerid), FormatNumber(TicketMoney[playerid], 0, '.'));
						SendClientMessage(targetid, COLOR_FAMILY, string);
						TicketMoney[playerid] = 0;
						TicketMoney[targetid] = 0;
						TicketOffer[playerid] = 999;
						TicketOffer[targetid] = 999;

					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not offerd nothing.");
				}
				else if(!strcmp(params, "pills", true)) {
					if(PillsOffer[playerid] < 999) {
						format(string, MAXO_TEXT, "* You bought %d pills for %s from Medic %s.", Pills[playerid], FormatNumber(PillsPrice[playerid], 0, '.'), PlayerName(targetid));
						SendClientMessage(playerid, COLOR_FAMILY, string);
						format(string, MAXO_TEXT, "* %s has bought your %d pills, for amount of $%s.", PlayerName(playerid), Pills[playerid], FormatNumber(PillsPrice[playerid], 0, '.'));
						SendClientMessage(targetid, COLOR_FAMILY, string);
						SafeGivePlayerMoney(playerid, -PillsPrice[playerid]);
						SafeGivePlayerMoney(targetid, PillsPrice[playerid]);
						ConsumingMoney[targetid] = 1;
						PlayerInfo[playerid][pPills] += Pills[playerid];
						PlayerInfo[targetid][pPills] -= Pills[playerid];
						format(string, MAXO_TEXT, "UPDATE players SET Pills = %d WHERE ID = %d", PlayerInfo[targetid][pPills], PlayerInfo[targetid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						format(string, MAXO_TEXT, "UPDATE players SET Pills = %d WHERE ID = %d", PlayerInfo[playerid][pPills], PlayerInfo[playerid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						PillsOffer[playerid] = 999;
						PillsPrice[playerid] = 0;
						Pills[playerid] = 0;
						PillsOffer[targetid] = 999;
						PillsPrice[targetid] = 0;
						Pills[targetid] = 0;
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not offerd nothing.");
				}
				else if(!strcmp(params, "ambulance", true)) {
					if(!PlayerInfo[playerid][pInBizzID] || !PlayerInfo[playerid][pInHouseID] || !PlayerInfo[playerid][pInHQID]) {
						if(!HaveVisibleCheckpoint(playerid)) {
							if(ClientAccept[playerid] == INVALID_PLAYER_ID) {
								if(ClientCaller{targetid}) {
									ClientAccept[playerid] = targetid;
									ClientCaller{targetid} = false;
									format(string, MAXO_TEXT, "* You have accepted the Ambulance Call from %s.", PlayerName(targetid));
									SendClientMessage(playerid, COLOR_FAMILY, string);
									format(string, MAXO_TEXT, "* Medic %s has accepted your Ambulance Call please wait at your current Position.", PlayerName(playerid));
									SendClientMessage(targetid, COLOR_FAMILY, string);
									GameTextForPlayer(playerid, "~w~Medic Caller~n~~r~Goto redmarker", 5000, 1);
									new
										Float: Pos[3];
									GetPlayerPos(targetid, Pos[0], Pos[1], Pos[2]);
									CreateCP(playerid,Pos[0],Pos[1],Pos[2],5.0,checkpointCaller,CP_CALLER);
								} else SendClientMessage(playerid, COLOR_GRAD1, "This player not have need of this service.");
							} else SendClientMessage(playerid, COLOR_GRAD1, "You have already a command, can not use this command.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command, you have an checkpoint visible.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command from an interior.");
				}
				else if(!strcmp(params, "live", true)) {
					if(LiveOffer[playerid] < 999) {
						if(PlayerInfo[playerid][pMute])
							return IsPlayerSilent();
						SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are frozen till the Live Conversation ends.");
						SendClientMessage(targetid, COLOR_LIGHTBLUE, "* You are frozen till the Live Conversation ends (use /live again).");
						TogglePlayerControllable(playerid, false);
						TogglePlayerControllable(targetid, false);
						TalkingLive[playerid] = LiveOffer[playerid];
						TalkingLive[targetid] = playerid;
						LiveOffer[playerid] = 999;
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not offerd you a conversation live.");
				}
				else if(!strcmp(params, "taxi", true)) {
					if(!PlayerInfo[playerid][pInBizzID] || !PlayerInfo[playerid][pInHouseID] || !PlayerInfo[playerid][pInHQID]) {
						if(!HaveVisibleCheckpoint(playerid)) {
							if(ClientAccept[playerid] == INVALID_PLAYER_ID) {
								if(ClientCaller{targetid}) {
									ClientAccept[playerid] = targetid;
									ClientCaller{targetid} = false;
									format(string, MAXO_TEXT, "* You have accepted the Taxi Call from %s.", PlayerName(targetid));
									SendClientMessage(playerid, COLOR_FAMILY, string);
									format(string, MAXO_TEXT, "* Taxi driver %s has accepted your Call please wait at your current Position.", PlayerName(playerid));
									SendClientMessage(targetid, COLOR_FAMILY, string);
									GameTextForPlayer(playerid, "~w~Taxi Caller~n~~r~Goto redmarker", 5000, 1);
									new
										Float: Pos[3];
									GetPlayerPos(targetid, Pos[0], Pos[1], Pos[2]);
									CreateCP(playerid,Pos[0],Pos[1],Pos[2],5.0,checkpointCaller,CP_CALLER);
								} else SendClientMessage(playerid, COLOR_GRAD1, "This player not have need of this service.");
							} else SendClientMessage(playerid, COLOR_GRAD1, "You have already a command, can not use this command.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command, you have an checkpoint visible.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command from an interior.");
				}
				else if(!strcmp(params, "house", true)) {
					if(PropertyOffer[playerid] != INVALID_PLAYER_ID) {
						if(!PlayerInfo[playerid][pPhousekey]) {
							if(PlayerInfo[playerid][pAccount] >= PropertyPrice[playerid]) {
								if(PlayerInfo[playerid][pLevel] >= HouseInfo[PlayerInfo[PropertyOffer[playerid]][pPhousekey]][hLevel]) {
									// prima data trimitem mesajele de informare de la vanzator la cumparator
									format(string, MAXO_TEXT, "* You bought the house from %s, at price of $%s. Type /househelp to see the commands.", PlayerName(PropertyOffer[playerid]), FormatNumber(PropertyPrice[playerid], 0, '.'));
									SendClientMessage(playerid, COLOR_FAMILY, string);
									format(string, MAXO_TEXT, "* %s has bought the house from you at price of $%s.", PlayerName(playerid), FormatNumber(PropertyPrice[playerid], 0, '.'));
									SendClientMessage(PropertyOffer[playerid], COLOR_FAMILY, string);
									// incepem setarile pentru transferul casei catre noul proprietar;
									PlayerInfo[playerid][pAccount] -= PropertyPrice[playerid];
									PlayerInfo[targetid][pAccount] += PropertyPrice[playerid];
									format(string, MAXO_TEXT, "UPDATE players SET Account = %d WHERE ID = %d", PlayerInfo[playerid][pAccount], PlayerInfo[playerid][pSQLID]);
									mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
									format(string, MAXO_TEXT, "UPDATE players SET Account = %d WHERE ID = %d", PlayerInfo[targetid][pAccount], PlayerInfo[targetid][pSQLID]);
									mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
									PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
									PlayerPlaySound(targetid, 1052, 0.0, 0.0, 0.0);
									GameTextForPlayer(targetid, "~w~Congratulations ~n~ You have sold that property", 10000, 3);
									PlayerInfo[playerid][pPhousekey] = PlayerInfo[PropertyOffer[playerid]][pPhousekey];
									format(string, MAXO_TEXT, "UPDATE players SET Phousekey = %d WHERE ID = %d", PlayerInfo[playerid][pPhousekey], PlayerInfo[playerid][pSQLID]);
									mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
									strmid(HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], PlayerName(playerid), 0, strlen(PlayerName(playerid)), 255);
									format(string, MAXO_TEXT, "UPDATE houses SET Owner = '%s' WHERE ID = %d", HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], HouseInfo[PlayerInfo[playerid][pPhousekey]][hSQLID]);
									mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
									switch(HouseInfo[PlayerInfo[playerid][pPhousekey]][hRentable]) {
										case 0: format(PropertyString, MAXO_TEXT2, "This house is owned by %s\nLevel: %d\nNot available for rent!", HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], HouseInfo[PlayerInfo[playerid][pPhousekey]][hLevel]);
										case 1: format(PropertyString, MAXO_TEXT2, "House available for rent!\nOwner: %s\nLevel: %d, Rent Price: $%s\nTo Rent Type /rentroom", HouseInfo[PlayerInfo[playerid][pPhousekey]][hOwner], HouseInfo[PlayerInfo[playerid][pPhousekey]][hLevel], FormatNumber(HouseInfo[PlayerInfo[playerid][pPhousekey]][hRentPrice], 0, '.'));
									}
									Update3DTextLabelText(HouseInfo[PlayerInfo[playerid][pPhousekey]][hLabel], COLOR_PROPERTY, PropertyString);
									PlayerInfo[targetid][pPhousekey] = 0;
									format(string, MAXO_TEXT, "UPDATE players SET Phousekey = %d WHERE ID = %d", PlayerInfo[targetid][pPhousekey], PlayerInfo[targetid][pSQLID]);
									mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
									SendClientMessage(targetid, COLOR_WHITE, "NOTE: You are homeless now, you don't have a house anymore.");
									// acum resetam transferul ca fiind invalid pentru vanzator si cumparator
									PropertyOffer[playerid] = INVALID_PLAYER_ID;
									PropertyPrice[playerid] = 0;
									PropertyOffer[targetid] = INVALID_PLAYER_ID;
									PropertyPrice[targetid] = 0;
								} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have the level necessary to accept this offer.");
							} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have enough money to accept this offer.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "You can't accept this offer, because you have already a house.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You not received any offer to accept it.");
				}
				else if(!strcmp(params, "biz", true)) {
					if(PropertyOffer[playerid] != INVALID_PLAYER_ID) {
						if(!PlayerInfo[playerid][pPbizkey]) {
							if(PlayerInfo[playerid][pAccount] >= PropertyPrice[playerid]) {
								if(PlayerInfo[playerid][pLevel] >= BizInfo[PlayerInfo[PropertyOffer[playerid]][pPbizkey]][bLevel]) {
									// prima data trimitem mesajele de informare de la vanzator la cumparator
									format(string, MAXO_TEXT, "* You bought the biz from %s, at price of $%s. Type /bizhelp to see the commands.", PlayerName(PropertyOffer[playerid]), FormatNumber(PropertyPrice[playerid], 0, '.'));
									SendClientMessage(playerid, COLOR_FAMILY, string);
									format(string, MAXO_TEXT, "* %s has bought the biz from you at price of $%s.", PlayerName(playerid), FormatNumber(PropertyPrice[playerid], 0, '.'));
									SendClientMessage(PropertyOffer[playerid], COLOR_FAMILY, string);
									// incepem setarile pentru transferul casei catre noul proprietar;
									PlayerInfo[playerid][pAccount] -= PropertyPrice[playerid];
									PlayerInfo[targetid][pAccount] += PropertyPrice[playerid];
									format(string, MAXO_TEXT, "UPDATE players SET Account = %d WHERE ID = %d", PlayerInfo[playerid][pAccount], PlayerInfo[playerid][pSQLID]);
									mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
									format(string, MAXO_TEXT, "UPDATE players SET Account = %d WHERE ID = %d", PlayerInfo[targetid][pAccount], PlayerInfo[targetid][pSQLID]);
									mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
									PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
									PlayerPlaySound(targetid, 1052, 0.0, 0.0, 0.0);
									GameTextForPlayer(targetid, "~w~Congratulations ~n~ You have sold that property", 10000, 3);
									PlayerInfo[playerid][pPbizkey] = PlayerInfo[PropertyOffer[playerid]][pPbizkey];
									format(string, MAXO_TEXT, "UPDATE players SET Pbizkey = %d WHERE ID = %d", PlayerInfo[playerid][pPbizkey], PlayerInfo[playerid][pSQLID]);
									mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
									strmid(BizInfo[PlayerInfo[playerid][pPbizkey]][bOwner], PlayerName(playerid), 0, strlen(PlayerName(playerid)), 255);
									format(string, MAXO_TEXT, "UPDATE bizz SET Owner = '%s' WHERE ID = %d", BizInfo[PlayerInfo[playerid][pPbizkey]][bOwner], BizInfo[PlayerInfo[playerid][pPbizkey]][bSQLID]);
									mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
									format(PropertyString, MAXO_TEXT2, "Biz %s\nLevel: %d\nOwned by: %s\nEntrance: $%s\nPress ENTER to enter", BizInfo[PlayerInfo[playerid][pPbizkey]][bDescription], BizInfo[PlayerInfo[playerid][pPbizkey]][bLevel], BizInfo[PlayerInfo[playerid][pPbizkey]][bOwner], FormatNumber(BizInfo[PlayerInfo[playerid][pPbizkey]][bEnterPrice], 0, '.'));
									Update3DTextLabelText(BizInfo[PlayerInfo[playerid][pPbizkey]][bLabel], COLOR_PROPERTY, PropertyString);
									PlayerInfo[targetid][pPbizkey] = 0;
									format(string, MAXO_TEXT, "UPDATE players SET Pbizkey = %d WHERE ID = %d", PlayerInfo[targetid][pPbizkey], PlayerInfo[targetid][pSQLID]);
									mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
									SendClientMessage(targetid, COLOR_WHITE, "NOTE: Now, you don't have any business anymore.");
									// acum resetam transferul ca fiind invalid pentru vanzator si cumparator
									PropertyOffer[playerid] = INVALID_PLAYER_ID;
									PropertyPrice[playerid] = 0;
									PropertyOffer[targetid] = INVALID_PLAYER_ID;
									PropertyPrice[targetid] = 0;
								} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have the level necessary to accept this offer.");
							} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have enough money to accept this offer.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "You can't accept this offer, because you have already a house.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You not received any offer to accept it.");
				}
				else if(!strcmp(params, "gun", true)) {
					if(GunOffer[playerid] != INVALID_PLAYER_ID) {
						if(PlayerInfo[playerid][pFactiune] != PlayerInfo[targetid][pFactiune]) {
							format(string, MAXO_TEXT, "* You bought a gun (ID: %d) for $%s from Dealer %s.", Gun[playerid], FormatNumber(GunPrice[playerid], 0, '.'), PlayerName(targetid));
							SendClientMessage(playerid, COLOR_FAMILY, string);
							format(string, MAXO_TEXT, "* %s has bought your gun (ID: %d), for amount of $%s.", PlayerName(playerid), Gun[playerid], FormatNumber(GunPrice[playerid], 0, '.'));
							SendClientMessage(targetid, COLOR_FAMILY, string);
							SafeGivePlayerMoney(playerid, -GunPrice[playerid]);
						}
						else if(PlayerInfo[playerid][pFactiune] == PlayerInfo[GunOffer[playerid]][pFactiune] && PlayerInfo[playerid][pFactiune] > FACT_CIVIL) {
							format(string, MAXO_TEXT, "* You bought a gun (ID: %d) from Dealer %s.", Gun[playerid],  PlayerName(GunOffer[playerid]));
							SendClientMessage(playerid, COLOR_FAMILY, string);
							format(string, MAXO_TEXT, "* %s has bought your gun (ID: %d).", PlayerName(playerid), Gun[playerid]);
							SendClientMessage(GunOffer[playerid], COLOR_FAMILY, string);
						}
						if(ISBetween(Gun[playerid], WEAPON_BRASSKNUCKLE, WEAPON_GOLFCLUB)) GivePlayerWeapon(playerid, Gun[playerid], 1);
						else if(ISBetween(Gun[playerid], WEAPON_KNIFE, WEAPON_CANE)) GivePlayerWeapon(playerid, Gun[playerid], 1);
						else if(ISBetween(Gun[playerid], WEAPON_COLT45, WEAPON_SHOTGUN)) GivePlayerWeapon(playerid, Gun[playerid], 100);
						else if(ISBetween(Gun[playerid], WEAPON_MP5, WEAPON_M4)) GivePlayerWeapon(playerid, Gun[playerid], 100);
						PlayerInfo[GunOffer[playerid]][pMats] --;
						format(string, MAXO_TEXT, "UPDATE players SET Materials = %d WHERE ID = %d", PlayerInfo[GunOffer[playerid]][pMats], PlayerInfo[GunOffer[playerid]][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoreturnThread", "d", UPDATE_THREAD_ID);
						GunOffer[playerid] = INVALID_PLAYER_ID;
						GunPrice[playerid] = 0;
						Gun[playerid] = 0;
						GunOffer[targetid] = INVALID_PLAYER_ID;
						GunPrice[targetid] = 0;
						Gun[targetid] = 0;
					} else SendClientMessage(playerid, COLOR_GRAD1, "You not received any offer.");
				}
				else if(!strcmp(params, "drugs", true)) {
					if(DrugsOffer[playerid] != INVALID_PLAYER_ID) {
						if(PlayerInfo[playerid][pFactiune] != PlayerInfo[targetid][pFactiune]) {
							format(string, MAXO_TEXT, "* You bought %d grams of drugs for $%s from Dealer %s.", Drugs[playerid], FormatNumber(DrugsPrice[playerid], 0, '.'), PlayerName(targetid));
							SendClientMessage(playerid, COLOR_FAMILY, string);
							format(string, MAXO_TEXT, "* %s has bought from you %d grams of drugs, for amount of $%s.", PlayerName(playerid), Drugs[playerid], FormatNumber(DrugsPrice[playerid], 0, '.'));
							SendClientMessage(targetid, COLOR_FAMILY, string);
							SafeGivePlayerMoney(playerid, -DrugsPrice[playerid]);
						}
						else if(PlayerInfo[playerid][pFactiune] == PlayerInfo[DrugsOffer[playerid]][pFactiune] && PlayerInfo[playerid][pFactiune] > FACT_CIVIL) {
							format(string, MAXO_TEXT, "* You bought %d grams of drugs from Dealer %s.", Drugs[playerid],  PlayerName(DrugsOffer[playerid]));
							SendClientMessage(playerid, COLOR_FAMILY, string);
							format(string, MAXO_TEXT, "* %s has bought %d grams of drugs from you.", PlayerName(playerid), Drugs[playerid]);
							SendClientMessage(DrugsOffer[playerid], COLOR_FAMILY, string);
						}
						PlayerInfo[DrugsOffer[playerid]][pDrugs] -= Drugs[playerid];
						format(string, MAXO_TEXT, "UPDATE players SET Drugs = %d WHERE ID = %d", PlayerInfo[DrugsOffer[playerid]][pDrugs], PlayerInfo[DrugsOffer[playerid]][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoreturnThread", "d", UPDATE_THREAD_ID);
						format(string, MAXO_TEXT, "UPDATE players SET Drugs = %d WHERE ID = %d", PlayerInfo[playerid][pDrugs], PlayerInfo[playerid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoreturnThread", "d", UPDATE_THREAD_ID);
						DrugsOffer[playerid] = INVALID_PLAYER_ID;
						DrugsPrice[playerid] = 0;
						Drugs[playerid] = 0;
						DrugsOffer[targetid] = INVALID_PLAYER_ID;
						DrugsPrice[targetid] = 0;
						Drugs[targetid] = 0;
					} else SendClientMessage(playerid, COLOR_GRAD1, "You not received any offer.");
				}
			} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
			PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
			clear.string(string);
		}
	} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/accept [playerid/PartOfName] [option]"), SendClientMessage(playerid, COLOR_GRAD1, "Options available: ticket | pills | ambulance | live | taxi | house | biz | gun | drugs");
	return true;
}

COMMAND:cancel(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(!sscanf(params, "s[64]", params)) {
		if(strlen(params) < 64) {
			if(!strcmp(params, "ticket", true)) {
				if(TicketOffer[playerid] < 999) {
					format(string, MAXO_TEXT, "* You cancelled the ticket from Cop %s, in value of $%s.", PlayerName(TicketOffer[playerid]), FormatNumber(TicketMoney[playerid], 0, '.'));
					SendClientMessage(playerid, COLOR_FAMILY, string);
					format(string, MAXO_TEXT, "* %s cancelled your ticket in value of $%s.", PlayerName(playerid), FormatNumber(TicketMoney[playerid], 0, '.'));
					SendClientMessage(TicketOffer[playerid], COLOR_FAMILY, string);
					TicketOffer[playerid] = 999;
					TicketMoney[playerid] = 0;
				} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have any offer.");
			}
			else if(!strcmp(params, "pills", true)) {
				if(PillsOffer[playerid] < 999) {
					format(string, MAXO_TEXT, "* You cancelled the pills from Medic %s, in value of $%s.", PlayerName(PillsOffer[playerid]), FormatNumber(PillsPrice[playerid], 0, '.'));
					SendClientMessage(playerid, COLOR_FAMILY, string);
					format(string, MAXO_TEXT, "* %s cancelled your ticket in value of $%s.", PlayerName(playerid), FormatNumber(PillsPrice[playerid], 0, '.'));
					SendClientMessage(PillsOffer[playerid], COLOR_FAMILY, string);
					PillsOffer[playerid] = 999;
					PillsPrice[playerid] = 0;
					Pills[playerid] = 0;
				} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have any offer.");
			}
			else if(!strcmp(params, "ambulance", true)) {
				if(ClientCaller{playerid}) {
					ClientCaller{playerid} = false;
					format(string, MAXO_TEXT, "* %s has cancelled the call to your faction.", PlayerName(playerid));
					SendFamilyMessage(COLOR_FAMILY, string, FACT_MEDIC);
				}
				else if(ClientAccept[playerid] != INVALID_PLAYER_ID) {
					format(string, MAXO_TEXT, "* Medic %s has cancelled you call, type again /service ambulance if you need a medic.", PlayerName(playerid));
					SendClientMessage(ClientAccept[playerid], COLOR_FAMILY, string);
					format(string, MAXO_TEXT, "* You has cancelled the call from %s.", PlayerName(ClientAccept[playerid]));
					SendClientMessage(playerid, COLOR_FAMILY, string);
					ClientAccept[playerid] = INVALID_PLAYER_ID;
					DeleteCP(checkpointCaller, playerid);
				}
			}
			else if(!strcmp(params, "taxi", true)) {
				if(ClientCaller{playerid}) {
					ClientCaller{playerid} = false;
					format(string, MAXO_TEXT, "* %s has cancelled the call to your faction.", PlayerName(playerid));
					SendFamilyMessage(COLOR_FAMILY, string, FACT_MEDIC);
				}
				else if(ClientAccept[playerid] != INVALID_PLAYER_ID) {
					format(string, MAXO_TEXT, "* Taxi driver %s has cancelled you call, type again /service taxi if you need a taxi.", PlayerName(playerid));
					SendClientMessage(ClientAccept[playerid], COLOR_FAMILY, string);
					format(string, MAXO_TEXT, "* You has cancelled the call from %s.", PlayerName(ClientAccept[playerid]));
					SendClientMessage(playerid, COLOR_FAMILY, string);
					ClientAccept[playerid] = INVALID_PLAYER_ID;
					DeleteCP(checkpointCaller, playerid);
				}
			}
			else if(!strcmp(params, "house", true)) {
				if(PropertyOffer[playerid] != INVALID_PLAYER_ID) {
					format(string, MAXO_TEXT, "* %s has cancelled your offer.", PlayerName(playerid));
					SendClientMessage(PropertyOffer[playerid], COLOR_FAMILY, string);
					format(string, MAXO_TEXT, "* You cancelled the offer from %s.", PlayerName(PropertyOffer[playerid]));
					SendClientMessage(playerid, COLOR_FAMILY, string);
					PropertyOffer[playerid] = INVALID_PLAYER_ID;
					PropertyPrice[playerid] = 0;
				} else SendClientMessage(playerid, COLOR_GRAD1, "You don't received any offer from any player.");
			}
			else if(!strcmp(params, "biz", true)) {
				if(PropertyOffer[playerid] != INVALID_PLAYER_ID) {
					format(string, MAXO_TEXT, "* %s has cancelled your offer.", PlayerName(playerid));
					SendClientMessage(PropertyOffer[playerid], COLOR_FAMILY, string);
					format(string, MAXO_TEXT, "* You cancelled the offer from %s.", PlayerName(PropertyOffer[playerid]));
					SendClientMessage(playerid, COLOR_FAMILY, string);
					PropertyOffer[playerid] = INVALID_PLAYER_ID;
					PropertyPrice[playerid] = 0;
				} else SendClientMessage(playerid, COLOR_GRAD1, "You don't received any offer from any player.");
			}
			else if(!strcmp(params, "gun", true)) {
				if(GunOffer[playerid] != INVALID_PLAYER_ID) {
					format(string, MAXO_TEXT, "* %s has cancelled your offer.", PlayerName(playerid));
					SendClientMessage(GunOffer[playerid], COLOR_FAMILY, string);
					format(string, MAXO_TEXT, "* You cancelled the offer from %s.", PlayerName(GunOffer[playerid]));
					SendClientMessage(playerid, COLOR_FAMILY, string);
					GunOffer[playerid] = INVALID_PLAYER_ID;
					GunPrice[playerid] = 0;
				}
			}
			else if(!strcmp(params, "drugs", true)) {
				if(DrugsOffer[playerid] != INVALID_PLAYER_ID) {
					format(string, MAXO_TEXT, "* %s has cancelled your offer.", PlayerName(playerid));
					SendClientMessage(DrugsOffer[playerid], COLOR_FAMILY, string);
					format(string, MAXO_TEXT, "* You cancelled the offer from %s.", PlayerName(DrugsOffer[playerid]));
					SendClientMessage(playerid, COLOR_FAMILY, string);
					DrugsOffer[playerid] = INVALID_PLAYER_ID;
					DrugsPrice[playerid] = 0;
				}
			}
		} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
		clear.string(string);
	} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/cancel [option]"), SendClientMessage(playerid, COLOR_GRAD1, "Options available: ticket | pills | ambulance | taxi | house | biz | gun | drugs");
	return true;
}

COMMAND:get(playerid, params[]) {
	new
		string[MAXO_TEXT], vID = GetPlayerVehicleID(playerid);
	if(!sscanf(params, "s[10]", params)) {
		if(!strcmp(params, "pills", true)) {
			if(PlayerInfo[playerid][pFactiune] == FACT_MEDIC) {
				if(CarInfo[vID][cFactionID] == FACT_MEDIC) {
					if(PlayerInfo[playerid][pPills] < 50) {
						if(PlayerInfo[playerid][pCash] >= 100) {
							PlayerInfo[playerid][pPills] = 50;
							SafeGivePlayerMoney(playerid, -100);
							GameTextForPlayer(playerid, "~r~-~g~$~y~100", 2500, 1);
							SendClientMessage(playerid, -1, "You got 50 pills for $100.");
							format(string, MAXO_TEXT, "UPDATE players SET Pills = %d WHERE ID = %d", PlayerInfo[playerid][pPills], PlayerInfo[playerid][pSQLID]);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							clear.string(string);
						} else SendClientMessage(playerid, COLOR_GRAD1, "You need of $100 to get 50 pills.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You have already 50 pills at you.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in an vehicle of faction (Medics/Firemans).");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must be member Medics/Firemans to use this command.");
		}
	} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/get [option]"), SendClientMessage(playerid, COLOR_GREY, "Options available: pills");
	return true;
}

COMMAND:usepills(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pPills] != 0) {
		if(PlayerInfo[playerid][pUsePillsTime] == 0) {
			SetPlayerHealth(playerid, 100.0);
			PlayerInfo[playerid][pPills] --;
			PlayerInfo[playerid][pUsePillsTime] = 240;
			format(string, MAXO_TEXT, "UPDATE players SET Pills = %d WHERE ID = %d", PlayerInfo[playerid][pPills], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(string, MAXO_TEXT, "* %s took pills and feels very good.", PlayerName(playerid));
			SendPlayerMessage(15.0, playerid, string, COLOR_PURPLE);
			SendClientMessage(playerid, COLOR_GREY, "* You used 1 pill.");
			for(new m; m < 2; m ++) {
				if(PlayerInfo[playerid][pDailyMission][m] == MISSION_PILLS)
					CheckMission(playerid, m);
			}
		} else format(string, MAXO_TEXT, "You can use this command in %s.", ConvertTime(PlayerInfo[playerid][pUsePillsTime])), SendClientMessage(playerid, COLOR_GRAD1, string);
		clear.string(string);
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have any pills at you.");
	return true;
}

COMMAND:report(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pReportTime] == 0) {
		if(PlayerInfo[playerid][pMute])
			return IsPlayerSilent();
		ShowPlayerDialog(playerid, DIALOGID_REPORT, DIALOG_STYLE_INPUT, "Report", "Type below your message for admins:", "Send", "Cancel");
	} else format(string, MAXO_TEXT, "You can use this command in %s.", ConvertTime(PlayerInfo[playerid][pReportTime])), SendClientMessage(playerid, COLOR_GRAD1, string);
	return true;
}

COMMAND:whisper(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pLevel] > 1) {
		if(PlayerInfo[playerid][pMuteTime] < 1) {
			if(!sscanf(params, "s[24]s[75]", PartialName[playerid][nume_introdus], params)) {
				CheckName(playerid, PartialName[playerid][nume_introdus]);
				targetid = PartialName[playerid][jucator_gasit];
				if(strlen(params) < 76) {
					if(targetid != INVALID_PLAYER_ID) {
						if(targetid != playerid) {
							if(GetDistanceBetweenPlayers(playerid, targetid) < 4) {
								if(PlayerInfo[playerid][pMute])
									return IsPlayerSilent();
								format(string, MAXO_TEXT, "[ID: %d] %s whispers: %s", playerid, PlayerName(playerid), params);
								SendClientMessage(targetid, COLOR_ORANGE, string);
								format(string, MAXO_TEXT, "PM sent to [ID: %d] %s: %s", targetid, PlayerName(targetid), params);
								SendClientMessage(playerid, COLOR_ORANGE, string);
								PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
								clear.string(string);
							} else SendClientMessage(playerid, COLOR_GRAD1, "This player is too far away from you, use /call.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command on yourself.");
					}
				} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
			} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/w(hisper) [playerid/PartOfName] [message]");
		} else IsPlayerSilent();
	} else SendClientMessage(playerid, COLOR_GRAD1, "You need of level 2 to use this command.");
	return true;
}

COMMAND:w(playerid, params[]) {
	return cmd_whisper(playerid, params);
}

COMMAND:admins(playerid, params[]) {
	new string[80];
	SendClientMessage(playerid, COLOR_LIGHTGREEN, "|__Admins Online__|");
	foreach(Player, i) {
		if(1 <= PlayerInfo[i][pAdmin] <= 1337) {
			if(!IsPlayerPaused(i))
				format(string, 80, "ID: %d | Admin Level %d: %s", i, PlayerInfo[i][pAdmin], PlayerName(i));
			else
				format(string, MAXO_TEXT, "ID: %d | Admin Level %d: %s| AFK: Yes, of %s", i, PlayerInfo[i][pAdmin], PlayerName(i), ConvertTime(TimeSincePaused(i)));
			SendClientMessage(playerid, 0x6A74F0FF, string);
		}
	}
	clear.string(string);
	return true;
}

COMMAND:helpers(playerid, params[]) {
	new string[80];
	SendClientMessage(playerid, COLOR_LIGHTGREEN, "|__Helpers Online__|");
	foreach(Player, i) {
		if(1 <= PlayerInfo[i][pHelper] <= 1337) {
			if(!IsPlayerPaused(i))
				format(string, 80, "ID: %d | Helper Level %d: %s", i, PlayerInfo[i][pHelper], PlayerName(i));
			else
				format(string, MAXO_TEXT, "ID: %d | Helper Level %d: %s | AFK: Yes, of %s", i, PlayerInfo[i][pHelper], PlayerName(i), ConvertTime(TimeSincePaused(i)));
			SendClientMessage(playerid, COLOR_GREY, string);
		}
	}
	clear.string(string);
	return true;
}

COMMAND:leaders(playerid, params[]) {
	new string[MAXO_TEXT];
	SendClientMessage(playerid, COLOR_LIGHTGREEN, "|______ Leaders Online ______|");
	foreach(Player, i) {
		if(PlayerInfo[i][pLeader] > FACT_CIVIL) {
			if(!IsPlayerPaused(i))
				format(string, MAXO_TEXT, "* ID: %d | Faction: %s | Leader: %s", i, FactionInfo[PlayerInfo[i][pLeader]][fName], PlayerName(i));
			else
				format(string, MAXO_TEXT, "* ID: %d | Faction: %s | Leader: %s | AFK: Yes, of %s", i, FactionInfo[PlayerInfo[i][pLeader]][fName], PlayerName(i), ConvertTime(TimeSincePaused(i)));
			SendClientMessage(playerid, FactionColor(PlayerInfo[i][pLeader]), string);
		}
	}
	clear.string(string);
	return true;
}

COMMAND:bank(playerid, params[]) {
	new string[MAXO_TEXT], amount, idbiz = PlayerInfo[playerid][pInBizzID];
	if(BizInfo[idbiz][bType] == BIZ_TYPE_BANK) {
		if(!sscanf(params, "d", amount)) {
			if(amount < 1)
				return SendClientMessage(playerid, COLOR_GRAD1, "The amount must be more bigger of $1.");
			if(PlayerInfo[playerid][pCash] < amount)
				return SendClientMessage(playerid, COLOR_GRAD1, "You don't have this amount to deposit it.");
			new curfunds = PlayerInfo[playerid][pAccount];
			SafeGivePlayerMoney(playerid, -amount);
			PlayerInfo[playerid][pAccount] += amount;
			SendClientMessage(playerid, COLOR_WHITE, "|___ BANK STATMENT ___|");
			format(string, MAXO_TEXT, "Old Balance: $%s", FormatNumber( curfunds, 0, ',' ));
			SendClientMessage(playerid, COLOR_GRAD2, string);
			format(string, MAXO_TEXT, "Deposit: $%s",FormatNumber( amount, 0, ',' ));
			SendClientMessage(playerid, COLOR_GRAD4, string);
			SendClientMessage(playerid, COLOR_GRAD6, "|-----------------------------------------|");
			format(string, MAXO_TEXT, "New Balance: $%s", FormatNumber( PlayerInfo[playerid][pAccount], 0, ',' ));
			SendClientMessage(playerid, COLOR_WHITE, string);
			format(string, MAXO_TEXT, "UPDATE players SET Account = %d WHERE ID = %d", PlayerInfo[playerid][pAccount], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoreturnThread", "d", UPDATE_THREAD_ID);
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/bank [amount]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in bank to use this command.");
	return true;
}

COMMAND:withdraw(playerid, params[]) {
	new string[MAXO_TEXT], amount, idbiz = PlayerInfo[playerid][pInBizzID];
	if(BizInfo[idbiz][bType] == BIZ_TYPE_BANK) {
		if(!sscanf(params, "d", amount)) {
			if(amount < 1)
				return SendClientMessage(playerid, COLOR_GRAD1, "The amount must be more bigger of $1.");
			if(PlayerInfo[playerid][pAccount] < amount)
				return SendClientMessage(playerid, COLOR_GRAD1, "You don't have this amount to withdraw it.");
			PlayerInfo[playerid][pAccount] -= amount;
			SafeGivePlayerMoney(playerid, amount);
			ConsumingMoney[playerid] = 1;
			format(string, MAXO_TEXT, "UPDATE players SET Account = %d WHERE ID = %d", PlayerInfo[playerid][pAccount], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoreturnThread", "d", UPDATE_THREAD_ID);
			format(string, MAXO_TEXT, "You Have Withdrawn $%s from your account Total: $%s ", FormatNumber(amount, 0, '.'), FormatNumber(PlayerInfo[playerid][pAccount], 0, '.'));
			SendClientMessage(playerid, COLOR_YELLOW, string);
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/withdraw [amount]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in bank to use this command.");
	return true;
}

COMMAND:transfer(playerid, params[]) {
	new string[MAXO_TEXT], amount, idbiz = PlayerInfo[playerid][pInBizzID], targetid;
	if(BizInfo[idbiz][bType] == BIZ_TYPE_BANK) {
		if(!sscanf(params, "s[24]ds[64]", PartialName[playerid][nume_introdus], amount, params)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(amount < 1)
				return SendClientMessage(playerid, COLOR_GRAD1, "The amount must be more bigger of $1.");
			if(PlayerInfo[playerid][pAccount] < amount)
				return SendClientMessage(playerid, COLOR_GRAD1, "You don't have this amountin your account.");
			if(PlayerInfo[playerid][pLevel] < 3)
				return SendClientMessage(playerid, COLOR_GRAD1, "You need Level 3 to use the command /transfer.");
			if(targetid == playerid)
				return SendClientMessage(playerid, COLOR_GRAD1, "You can't transfer money yourself.");
			PlayerInfo[playerid][pAccount] -= amount;
			PlayerInfo[targetid][pAccount] += amount;
			format(string, MAXO_TEXT, "UPDATE players SET Account = %d WHERE ID = %d", PlayerInfo[playerid][pAccount], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(string, MAXO_TEXT, "UPDATE players SET Account = %d WHERE ID = %d", PlayerInfo[targetid][pAccount], PlayerInfo[targetid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(string, MAXO_TEXT, "You have transferd $%s to %s's account, Reason: %s.", FormatNumber(amount, 0, '.'), PlayerName(targetid), params);
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			SendClientMessage(playerid, COLOR_GRAD1, string);
			format(string, MAXO_TEXT, "You have recieved $%s into your account from %s (ID: %d), Reason: %s.", FormatNumber(amount, 0, '.'), PlayerName(playerid), playerid, params);
			SendClientMessage(targetid, COLOR_GRAD1, string);
			format(string, MAXO_TEXT, "AdmTransfer: %s has transfered to %s account $%s, Reason: %s.", PlayerName(playerid), PlayerName(targetid), FormatNumber(amount, 0, '.'), params);
			ABroadCast(COLOR_LIGHTRED, string, 1);
			format(string, MAXO_TEXT, "%s (SQLID: %d) transferred %s (SQLID: %d) $%s.", PlayerName(playerid), PlayerInfo[playerid][pSQLID], PlayerName(targetid), PlayerInfo[targetid][pSQLID], FormatNumber(amount, 0, '.'));
			InsertLogInPanel(playerid, LOG_TRANSFER, string);
			PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/transfer [playerid/PartOfName] [amount] [reason]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in bank to use this command.");
	return true;
}

COMMAND:jobs(playerid, params[]) {
	if(!HaveVisibleCheckpoint(playerid)) {
		if(!PlayerInfo[playerid][pInBizzID] || !PlayerInfo[playerid][pInHQID] || !PlayerInfo[playerid][pInHouseID] || !PlayerInfo[playerid][pInHQID]) {
			ShowPlayerDialog(playerid, DIALOGID_JOBS, DIALOG_STYLE_LIST, "Jobs list", "1. Farmer\n2. Street Sweeper\n3. Dustman\n4. Trucker\n5. Car Jacker\n6. Arms Dealer\n7. Drugs Dealer", "Select", "Cancel");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command from an interior.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command right now.");
	return true;
}

COMMAND:skills(playerid, params[]) {
	new string[MAXO_TEXT], cSkill = 0, nSkill = 0;
	SendClientMessage(playerid, COLOR_GREEN, "|_____________________ Skills _____________________|");
	switch(PlayerInfo[playerid][pFarmerSkill]) {
		case 0..48: cSkill = 1, nSkill = (48 - PlayerInfo[playerid][pFarmerSkill]);
		case 49..144: cSkill = 2, nSkill = (144 - PlayerInfo[playerid][pFarmerSkill]);
		case 145..336: cSkill = 3, nSkill = (336 - PlayerInfo[playerid][pFarmerSkill]);
		case 337..720: cSkill = 4, nSkill = (720 - PlayerInfo[playerid][pFarmerSkill]);
		default: cSkill = 5, nSkill = 0;
	}
	if(nSkill != 0)
		format(string, MAXO_TEXT, "* Farmer: Your skill is: %d, you must to make still %d delivery.", cSkill, nSkill);
	else
		format(string, MAXO_TEXT, "* Farmer: Your skill is: %d.", cSkill);
	SendClientMessage(playerid, COLOR_ORANGE, string);

	switch(PlayerInfo[playerid][pNewsSkill]) {
		case 0..50: cSkill = 1, nSkill = (50 - PlayerInfo[playerid][pNewsSkill]);
		case 51..150: cSkill = 2, nSkill = (150 - PlayerInfo[playerid][pNewsSkill]);
		case 151..300: cSkill = 3, nSkill = (300 - PlayerInfo[playerid][pNewsSkill]);
		case 301..500: cSkill = 4, nSkill = (500 - PlayerInfo[playerid][pNewsSkill]);
		default: cSkill = 5, nSkill = 0;
	}
	if(nSkill != 0)
		format(string, MAXO_TEXT, "* News Reporter: Your skill is: %d, you must to place still %d news.", cSkill, nSkill);
	else
		format(string, MAXO_TEXT, "* News Reporter: Your skill is: %d.", cSkill);
	SendClientMessage(playerid, COLOR_ORANGE, string);

	switch(PlayerInfo[playerid][pDustSkill]) {
		case 0..200: cSkill = 1, nSkill = (200 - PlayerInfo[playerid][pDustSkill]);
		case 201..600: cSkill = 2, nSkill = (600 - PlayerInfo[playerid][pDustSkill]);
		case 601..1400: cSkill = 3, nSkill = (1400 - PlayerInfo[playerid][pDustSkill]);
		case 1401..3000: cSkill = 4, nSkill = (3000 - PlayerInfo[playerid][pDustSkill]);
		default: cSkill = 5, nSkill = 0;
	}
	if(nSkill != 0)
		format(string, MAXO_TEXT, "* Dustman: Your skill is: %d, you must to make still %d uploads of trash.", cSkill, nSkill);
	else
		format(string, MAXO_TEXT, "* Dustman: Your skill is: %d.", cSkill);
	SendClientMessage(playerid, COLOR_ORANGE, string);

	switch(PlayerInfo[playerid][pCarJackerSkill]) {
		case 0..16: cSkill = 1, nSkill = (16 - PlayerInfo[playerid][pCarJackerSkill]);
		case 17..56: cSkill = 2, nSkill = (56 - PlayerInfo[playerid][pCarJackerSkill]);
		case 57..152: cSkill = 3, nSkill = (152 - PlayerInfo[playerid][pCarJackerSkill]);
		case 153..240: cSkill = 4, nSkill = (240 - PlayerInfo[playerid][pCarJackerSkill]);
		default: cSkill = 5, nSkill = 0;
	}
	if(nSkill != 0)
		format(string, MAXO_TEXT, "* Car Jacker: Your skill is: %d, you must to make still %d sales.", cSkill, nSkill);
	else
		format(string, MAXO_TEXT, "* Car Jacker: Your skill is: %d.", cSkill);
	SendClientMessage(playerid, COLOR_ORANGE, string);

	switch(PlayerInfo[playerid][pArmsDealerSkill]) {
		case 0..50: cSkill = 1, nSkill = (50 - PlayerInfo[playerid][pArmsDealerSkill]);
		case 51..150: cSkill = 2, nSkill = (150 - PlayerInfo[playerid][pArmsDealerSkill]);
		case 151..246: cSkill = 3, nSkill = (246 - PlayerInfo[playerid][pArmsDealerSkill]);
		case 247..438: cSkill = 4, nSkill = (438 - PlayerInfo[playerid][pArmsDealerSkill]);
		default: cSkill = 5, nSkill = 0;
	}
	if(nSkill != 0)
		format(string, MAXO_TEXT, "* Arms Dealer: Your skill is: %d, you must to make still %d delivery.", cSkill, nSkill);
	else
		format(string, MAXO_TEXT, "* Arms Dealer: Your skill is: %d.", cSkill, nSkill);
	SendClientMessage(playerid, COLOR_ORANGE, string);

	switch(PlayerInfo[playerid][pSweeperSkill]) {
		case 0..96: cSkill = 1, nSkill = (96 - PlayerInfo[playerid][pSweeperSkill]);
		case 97..288: cSkill = 2, nSkill = (288 - PlayerInfo[playerid][pSweeperSkill]);
		case 289..672: cSkill = 3, nSkill = (672 - PlayerInfo[playerid][pSweeperSkill]);
		case 673..1440: cSkill = 4, nSkill = (1440 - PlayerInfo[playerid][pSweeperSkill]);
		default: cSkill = 5, nSkill = 0;
	}
	if(nSkill != 0)
		format(string, MAXO_TEXT, "* Street Sweeper: Your skill is: %d, you must to make still %d laps.", cSkill, nSkill);
	else
		format(string, MAXO_TEXT, "* Street Sweeper: Your skill is: %d.", cSkill);
	SendClientMessage(playerid, COLOR_ORANGE, string);

	switch(PlayerInfo[playerid][pDrugsDealerSkill]) {
		case 0..50: cSkill = 1, nSkill = (50 - PlayerInfo[playerid][pDrugsDealerSkill]);
		case 51..150: cSkill = 2, nSkill = (150 - PlayerInfo[playerid][pDrugsDealerSkill]);
		case 151..246: cSkill = 3, nSkill = (246 - PlayerInfo[playerid][pDrugsDealerSkill]);
		case 247..438: cSkill = 4, nSkill = (438 - PlayerInfo[playerid][pDrugsDealerSkill]);
		default: cSkill = 5, nSkill = 0;
	}
	if(nSkill != 0)
		format(string, MAXO_TEXT, "* Drugs Dealer: Your skill is: %d, you must to make still %d delivery.", cSkill, nSkill);
	else
		format(string, MAXO_TEXT, "* Drugs Dealer: Your skill is: %d.", cSkill, nSkill);
	SendClientMessage(playerid, COLOR_ORANGE, string);

	switch(PlayerInfo[playerid][pFishSkill]) {
		case 0..10: cSkill = 1, nSkill = (10 - PlayerInfo[playerid][pFishSkill]);
		case 11..50: cSkill = 2, nSkill = (50 - PlayerInfo[playerid][pFishSkill]);
		case 51..200: cSkill = 3, nSkill = (200 - PlayerInfo[playerid][pFishSkill]);
		case 201..400: cSkill = 4, nSkill = (400 - PlayerInfo[playerid][pFishSkill]);
		case 401: cSkill = 5, nSkill = 0;
	}
	if(nSkill != 0)
		format(string, MAXO_TEXT, "* Fisher: Your skill is: %d, you must fishing still %d times.", cSkill, nSkill);
	else
		format(string, MAXO_TEXT, "* Fisher: Your skill is: %d.", cSkill, nSkill);
	SendClientMessage(playerid, COLOR_ORANGE, string);
	clear.string(string);
	return true;
}

COMMAND:surrender(playerid, params[]) {
	new string[MAXO_TEXT];
	if(IsPlayerInRangeOfPoint(playerid, 10.0, 246.4736,67.2395,1003.6406)) {
		if(PlayerInfo[playerid][pWlvl] > 0) {
			if(ISBetween(PlayerInfo[playerid][pWlvl], 1, 6)) {
				if(IsPlayerCop(playerid))
					return SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command, you're cop.");
				if(JucatorulAreMateriale[playerid])
					return SendClientMessage(playerid, COLOR_GRAD1, "You must finish the mission first time, and after to come to surrender yourself.");
				ResetPlayerWeapons(playerid);
				format(string, MAXO_TEXT, "<< %s had surrender having wanted %d >>", PlayerName(playerid), PlayerInfo[playerid][pWlvl]);
				OOCNews(COLOR_LIGHTRED, string);
				PlayerInfo[playerid][pJailTime] = PlayerInfo[playerid][pWlvl] * 100;
				PlayerInfo[playerid][pJailed] = 1;
				PlayerInfo[playerid][pWlvl] = 0;
				SetPlayerWanted(playerid, INVALID_PLAYER_ID, PlayerInfo[playerid][pWlvl]);
				format(string, MAXO_TEXT2, "UPDATE players SET JailTime = %d, Jailed = %d WHERE ID = %d", PlayerInfo[playerid][pJailTime], PlayerInfo[playerid][pJailed], PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				PutPlayerInCell(playerid);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "You can't surrender because the wanted level is too high.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't wanted, can't use this command.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in the inside the Police station SF/LS.");
	return true;
}

COMMAND:time(playerid, params[]) {
	new string[MAXO_TEXT], mtext[MAXO_TEXT1];
	new gYear, gMonth, gDay;
	getdate(gYear, gMonth, gDay);
	switch(gMonth) {
		case 1: mtext = "Ianuarie";
		case 2: mtext = "Februarie";
		case 3: mtext = "Martie";
		case 4: mtext = "Aprilie";
		case 5: mtext = "Mai";
		case 6: mtext = "Iunie";
		case 7: mtext = "Iulie";
		case 8: mtext = "August";
		case 9: mtext = "Septembrie";
		case 10: mtext = "Octombrie";
		case 11: mtext = "Noiembrie";
		case 12: mtext = "Decembrie";
	}
	gettime(gHours, gMinutes, gSeconds);
	if(PlayerInfo[playerid][pJailTime] > 0)
		format(string, MAXO_TEXT, "~w~%02d-%s-%04d~n~~y~Jail Time Left: ~r~%s", gDay, mtext, gYear, ConvertTime(PlayerInfo[playerid][pJailTime]));
	else
		format(string, MAXO_TEXT, "~w~%02d-%s-%04d~n~%02d:%02d:%02d", gDay, mtext, gYear, gHours, gMinutes, gSeconds);
	GameTextForPlayer(playerid, string, 5000, 1);
	ApplyAnimation(playerid, "PLAYIDLES", "time", 3.1, 0, 1, 1, 1, 1);
	clear.string(string);
	return true;
}

COMMAND:ad(playerid, params[]) {
	new string[MAXO_TEXT+50], payout = (strlen(params)*25);
	if(!PlayerInfo[playerid][pMute]) {
		if(!sscanf(params, "s[128]", params)) {
			if(ISBetween(strlen(params), 1, 128)) {
				if(PlayerInfo[playerid][pCash] > payout) {
					if(!PlayerInfo[playerid][pAdvertismentTime]) {
						if(PlayerInfo[playerid][pMute])
							return IsPlayerSilent();
						format(string, MAXO_TEXT, "< Advertisment by %s: %s >", PlayerName(playerid), params);
						SendClientMessage(playerid, 0x00D900C8, string);
						format(string, MAXO_TEXT, "* You has paid $%s for your advertisment witch Contain %d characters.", FormatNumber(payout, 0, '.'), strlen(params));
						SendClientMessage(playerid, COLOR_WHITE, string);
						SafeGivePlayerMoney(playerid, -payout);
						PlayerInfo[playerid][pAdvertismentTime] = 60*4;
						for(new m; m < 2; m ++) {
							if(PlayerInfo[playerid][pDailyMission][m] == MISSION_ANNOUNCE)
								CheckMission(playerid, m);
						}
					} else format(string, MAXO_TEXT, "You can to use the again the command in %s.", ConvertTime(PlayerInfo[playerid][pAdvertismentTime])), SendClientMessage(playerid, COLOR_GRAD1, string);
				} else format(string, MAXO_TEXT, "You need $%s to post an advertisment.", FormatNumber(payout, 0, '.')), SendClientMessage(playerid, COLOR_GRAD1, string);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: {FFFFFF}Line too long.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/ad(vertisment) [message]");
	} else IsPlayerSilent();
	return true;
}

COMMAND:advertisment(playerid, params[]) {
	return cmd_ad(playerid, params);
}

COMMAND:usedrugs(playerid, params[]) {
	new string[MAXO_TEXT], Float:viata;
	if(PlayerInfo[playerid][pDrugs]) {
		if(!PlayerInfo[playerid][pDrugsTime]) {
			PlayerInfo[playerid][pDrugsTime] = 2;
			GetPlayerHealth(playerid, viata);
			if(viata > 150)
				return SendClientMessage(playerid, COLOR_GRAD1, "You have already the health maximum (150)");
			PlayerStoned[playerid] ++;
			if(PlayerStoned[playerid] > 1)
				GameTextForPlayer(playerid, "~w~You are~n~~p~Stoned", 4000, 1);
			PlayerInfo[playerid][pDrugs] -= 2;
			format(string, MAXO_TEXT, "UPDATE players SET Drugs = %d WHERE ID = %d", PlayerInfo[playerid][pDrugs], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			SendClientMessage(playerid, COLOR_GREY, "You have used 2 grams of Drugs!");
			format(string, MAXO_TEXT, "* %s has used 2 grams of drugs!", PlayerName(playerid));
			SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
			SetPlayerHealth(playerid, viata + 20);
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_GRAD1, "Waint 2 seconds.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have no grams of drugs.");
	return true;
}

COMMAND:getout(playerid, params[]) {
	new string[MAXO_TEXT], targetid, vID = GetPlayerVehicleID(playerid);
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != playerid) {
				if(IsPlayerInVehicle(targetid, vID)) {
					format(string, MAXO_TEXT, "* You has been ejected from this vehicle by Driver %s.", PlayerName(playerid));
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					format(string, MAXO_TEXT, "* You taken out from your vehicle on passenger %s.", PlayerName(targetid));
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					RemovePlayerFromVehicle(targetid);
					PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "This player isn't in your vehicle.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command on yourself.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/getout [playerid/PartOfName]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You must be driver when you'll use this command.");
	return true;
}

function payspam(playerid) {
	return PTransfered{playerid} = false;
}

COMMAND:pay(playerid, params[]) {
	new string[MAXO_TEXT], targetid, amount;
	if(!sscanf(params, "s[24]d", PartialName[playerid][nume_introdus], amount)) {
		CheckName(playerid, PartialName[playerid][nume_introdus]);
		targetid = PartialName[playerid][jucator_gasit];
		if(targetid != INVALID_PLAYER_ID) {
			if(targetid != playerid) {
				if(GetDistanceBetweenPlayers(targetid, playerid) < 6) {
					if(ISBetween(amount, 1, 100000)) {
						if(!PTransfered{playerid}) {
							if(PlayerInfo[playerid][pCash] > amount) {
								PTransfered{playerid} = true;
								SafeGivePlayerMoney(playerid, -amount);
								SafeGivePlayerMoney(targetid, amount);
								format(string, MAXO_TEXT, "* You have sent $%s to %s (ID: %d).", FormatNumber(amount, 0, '.'), PlayerName(targetid), targetid);
								SendClientMessage(playerid, COLOR_GRAD1, string);
								format(string, MAXO_TEXT, "%s (SQLID: %d) gave %s (SQLID: %d) $%s.", PlayerName(playerid), PlayerInfo[playerid][pSQLID], PlayerName(targetid), PlayerInfo[targetid][pSQLID], FormatNumber(amount, 0, '.'));
								InsertLogInPanel(playerid, LOG_PAY, string);
								PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
								PlayerPlaySound(targetid, 1052, 0.0, 0.0, 0.0);
								format(string, MAXO_TEXT, "* You has received $%s from %s (ID: %d).", FormatNumber(amount, 0, '.'), PlayerName(playerid), playerid);
								SendClientMessage(targetid, COLOR_GRAD1, string);
								format(string, MAXO_TEXT, "* %s takes out some cash, and hands it to %s.", PlayerName(playerid), PlayerName(targetid));
								SendPlayerMessage(15.0, playerid, string, COLOR_PURPLE);
								SetTimerEx("payspam", 30000, 0, "d", playerid);
								PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
								clear.string(string);
							} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have this amount of money.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "You must wait 30 seconds for another transaction.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "The amount must be between $1-$100.000.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "This player is too far away from you.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You can't pay yourself.");
		}
	} else SendClientMessage(playerid, COLOR_GRAD1, "USAGE: {FFFFFF}/pay [playerid/PartOfName] [amount]");
	return true;
}

COMMAND:toglive(playerid, params[]) {
	if(TogglePlayerLive{playerid})
		TogglePlayerLive{playerid} = false, SendClientMessage(playerid, COLOR_GRAD1, "You has deactivated the Live chat.");
	else
		TogglePlayerLive{playerid} = true, SendClientMessage(playerid, COLOR_GRAD1, "You has activated the Live chat.");
	return true;
}

COMMAND:burger(playerid, params[]) {
	if(IsPlayerInRangeOfPoint(playerid, 3.0, 1250.4, -1352.38, 13.2356)) {
		new Float:viata;
		GetPlayerHealth(playerid, viata);
		if(viata > 99)
			return SendClientMessage(playerid, COLOR_GRAD1, "You health is too high, you can't use this command anymore.");
		SetPlayerHealth(playerid, ((viata >= 75.0) ? 100.0 : (viata + 25.0)));
		ApplyAnimation(playerid, "FOOD","EAT_Burger", 3.0, 0, 0, 0, 0, 0);
		GameTextForPlayer(playerid, "~y~Now, you feel more better.", 3500, 1);
	}
	return true;
}

COMMAND:me(playerid, params[]) {
	new string[MAXO_TEXT];
	if(!PlayerInfo[playerid][pMuteTime]) {
		if(!sscanf(params, "s[80]", params)) {
			if(ISBetween(strlen(params), 1, 80)) {
				if(PlayerInfo[playerid][pMute])
					return IsPlayerSilent();
				format(string, MAXO_TEXT, "* %s %s.", PlayerName(playerid), params);
				SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: {FFFFFF} Line too long.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/me [text]");
	} else IsPlayerSilent();
	return true;
}

COMMAND:newbie(playerid, params[]) {
	new string[MAXO_TEXT];
	if(PlayerInfo[playerid][pLevel] < 5 || PlayerInfo[playerid][pAdmin] || PlayerInfo[playerid][pHelper]) {
		if(!sscanf(params, "s[100]", params)) {
			if(isNewbieChatActive) {
				if(ISBetween(strlen(params), 1, 100)) {
					if(!NewbieChatTimer[playerid]) {
						if(!PlayerInfo[playerid][pMuteTime] || !PlayerInfo[playerid][pNMute]) {
							if(!PlayerInfo[playerid][pHelper])
								format(string, MAXO_TEXT, "Newbie Level %d %s: %s.", PlayerInfo[playerid][pLevel], PlayerName(playerid), params);
							else
								format(string, MAXO_TEXT, "Helper %s: %s.", PlayerName(playerid), params);
							if(PlayerInfo[playerid][pAdmin])
								format(string, MAXO_TEXT, "Admin %s: %s.", PlayerName(playerid), params);
							if(!PlayerInfo[playerid][pAdmin] || PlayerInfo[playerid][pHelper])
								NewbieChatTimer[playerid] = NEWBIE_TIME;
							foreach(Player, i) {
								if(ISBetween(PlayerInfo[i][pLevel], 0, 4) || PlayerInfo[i][pAdmin] || PlayerInfo[i][pHelper])
									SendClientMessage(i, COLOR_LIGHTGREEN, string);
							}
							clear.string(string);
						} else IsPlayerSilent();
					} else SendClientMessage(playerid, COLOR_GRAD1, "You must wait 30 seconds to type another message.");
				} else SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: {FFFFFF}Line too long.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "The newbie chat is deactivated by an Admin.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/n(ewbie) [text]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "Your level is too high, you can't use this chat anymore.");
	return true;
}

COMMAND:n(playerid, params[]) {
	return cmd_newbie(playerid, params);
}

COMMAND:nonewbie(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] > 1) {
		isNewbieChatActive = !isNewbieChatActive;
		if(!isNewbieChatActive)
			SendClientMessage(playerid, COLOR_GRAD1, "You deactivated the /n(ewbie) chat.");
		else
			SendClientMessage(playerid, COLOR_GRAD1, "You activated the /n(ewbie) chat.");
	} else NotAuthorized();
	return true;
}

COMMAND:disabletime(playerid, params[]) {
	if(PlayerInfo[playerid][pDisable]) {
		new string[MAXO_TEXT];
		format(string, MAXO_TEXT, "~y~You have anymore: ~r~%s ~y~minute(s)", ConvertTime(PlayerInfo[playerid][pDisableTime]));
		GameTextForPlayer(playerid, string, 3500, 1);
		clear.string(string);
	} else SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command, you aren't disabled.");
	return true;
}

COMMAND:call(playerid, params[]) {
	new string[MAXO_TEXT], numberP, giveplayerid;
	if(!sscanf(params, "d", numberP)) {
		format(string, MAXO_TEXT, "* %s takes out a cellphone.", PlayerName(playerid));
		SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
		if(numberP == PlayerInfo[playerid][pPnumber]) {
			SendClientMessage(playerid, COLOR_GRAD1, "You just get a busy tone...");
			return true;
		}
		if(Mobile[playerid] != 255) {
			SendClientMessage(playerid, COLOR_GRAD1, "You are already on a call...");
			return true;
		}
		foreach (new i : Player) {
			if(IsPlayerConnected(i)) {
				if(PlayerInfo[i][pPnumber] == numberP && numberP != 0) {
					giveplayerid = i;
					Mobile[playerid] = giveplayerid;
					if(IsPlayerConnected(giveplayerid)) {
						if(giveplayerid != INVALID_PLAYER_ID) {
							if(PhoneOnline[giveplayerid] > 0) {
								SendClientMessage(playerid, COLOR_GREY, "That players Phone is Offline !");
								return true;
							}
							if (Mobile[giveplayerid] == 255) {
								format(string, MAXO_TEXT, "Your Mobile is Ringing Type (/Pickup) CallerID: %s", PlayerName(playerid));
								SendClientMessage(giveplayerid, COLOR_YELLOW, string);
								RingTone[giveplayerid] = 10;
								format(string, MAXO_TEXT, "* %s's phone begins to ring.", PlayerName(giveplayerid));
								SendClientMessage(playerid, COLOR_WHITE, "HINT: You now use T to talk on your cellphone, type /h(angup) to hang up.");
								SendPlayerMessage(30.0, i, string, COLOR_PURPLE);
								CellTime[playerid] = 1;
								return true;
							}
						}
					}
				}
			}
		}
		clear.string(string);
		SendClientMessage(playerid, COLOR_GRAD1, "You just get a Busy tone...");
	} else SendClientMessage(playerid, COLOR_ORANGE, "USAE: {FFFFFF}/call [number phone]");
	return true;
}

COMMAND:sms(playerid, params[]) {
	new number, string[MAXO_TEXT];
	if(PlayerInfo[playerid][pPnumber] > 0) {
		if(!sscanf(params, "ds[100]", number, params)) {
			if(number > 0) {
				if(number != PlayerInfo[playerid][pPnumber]) {
					if(ISBetween(strlen(params), 1, 100)) {
						if(strlen(params) != 0) {
							for(new i = 0; i < MAX_PLAYERS; i ++) {
								if(i != playerid) {
									if(PlayerInfo[i][pPnumber] == number && number != 0) {
										format(string, MAXO_TEXT, "* %s takes out their cellphone and starts pressing some keys.", PlayerName(playerid));
										SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
										format(string, MAXO_TEXT, "SMS: %s, Sender: %s (%d)", params, PlayerName(playerid), PlayerInfo[playerid][pPnumber]);
										SendClientMessage(i, -1, string);
										SendClientMessage(playerid, -1, "Text Message Delivered");
										PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
									}
								}
							}
							clear.string(string);
						} else SendClientMessage(playerid, COLOR_GRAD1, "You can't send an sms empty.");
					} else SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: {FFFFFF}Line too long.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can't send an message yourself.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid number.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "USAGE: {FFFFFF}/sms [number phone] [text]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You need a cellphone to use this command/");
	return true;
}

COMMAND:numbers(playerid, params[]) {
	new string[MAXO_TEXT1], targetid;
	if(PlayerInfo[playerid][pPhoneBook] > 0) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != playerid) {
				if(targetid != INVALID_PLAYER_ID) {
					if(PlayerInfo[targetid][pPnumber] > 0) {
						format(string, MAXO_TEXT1, "* Name: %s | Phone Number: %d", PlayerName(targetid), PlayerInfo[targetid][pPnumber]);
						SendClientMessage(playerid, COLOR_FAMILY, string);
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not have a phone.");
				}
			} else SendClientMessage(playerid, COLOR_GRAD1, "Can you see your number, if type the command /stats.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/numbers [playerid/PartOfName]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You need of a Phonebook to find an number.");
	return true;
}

COMMAND:pickup(playerid, params[]) {
	new string[MAXO_TEXT];
	if(IsPlayerConnected(playerid)) {
		if(Mobile[playerid] != 255) {
			SendClientMessage(playerid, COLOR_GRAD2, "You are already on a call...");
			return true;
		}
		foreach (new i : Player) {
			if(IsPlayerConnected(i)) {
				if(Mobile[i] == playerid) {
					Mobile[playerid] = i;
					SendClientMessage(i,  COLOR_GRAD2, "They Picked up the call.");
					format(string, sizeof(string), "* %s answers his cellphone.", PlayerName(playerid));
					SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
					RingTone[playerid] = 0;
				}
			}
		}
		clear.string(string);
	}
	return true;
}

COMMAND:p(playerid, params[]) {
	return cmd_pickup(playerid, params);
}

COMMAND:hangup(playerid, params[]) {
	if(IsPlayerConnected(playerid)) {
		new caller = Mobile[playerid];
		if(IsPlayerConnected(caller)) {
			if(caller != INVALID_PLAYER_ID) {
				if(caller != 255) {
					if(caller < 255) {
						SendClientMessage(caller,  COLOR_GRAD2, "They hung up.");
						CellTime[caller] = 0;
						CellTime[playerid] = 0;
						SendClientMessage(playerid,  COLOR_GRAD2, "You hung up.");
						Mobile[caller] = 255;
					}
					Mobile[playerid] = 255;
					CellTime[playerid] = 0;
					RingTone[playerid] = 0;
					return 1;
				}
			}
		}
		SendClientMessage(playerid,  COLOR_GRAD2, "Your phone is in your pocket.");
	}
	return true;
}

COMMAND:h(playerid, params[]) {
	return cmd_hangup(playerid, params);
}

COMMAND:spawnls(playerid, params[]) {
	new string[MAXO_TEXT];
	if(PlayerInfo[playerid][pFactiune] < FACT_LSPD) {
		PlayerInfo[playerid][pFactionSpawn] = FACTIONSPAWN_PRIMARY;
		format(string, MAXO_TEXT, "UPDATE players SET FactionSpawn = %d WHERE ID = %d", PlayerInfo[playerid][pFactionSpawn], PlayerInfo[playerid][pSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You will now spawn at Spawn Primary (LS).");
		clear.string(string);
	} else SendClientMessage(playerid, COLOR_GRAD1, "This command can be used by only civillians.");
	return true;
}

COMMAND:spawnsf(playerid, params[]) {
	new string[MAXO_TEXT];
	if(PlayerInfo[playerid][pFactiune] < FACT_LSPD) {
		PlayerInfo[playerid][pFactionSpawn] = FACTIONSPAWN_SECONDARY;
		format(string, MAXO_TEXT, "UPDATE players SET FactionSpawn = %d WHERE ID = %d", PlayerInfo[playerid][pFactionSpawn], PlayerInfo[playerid][pSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You will now spawn at Spawn Secondary (SF).");
		clear.string(string);
	} else SendClientMessage(playerid, COLOR_GRAD1, "This command can be used by only civillians.");
	return true;
}

COMMAND:checkpday(playerid, params[]) {
	new string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pLeader]) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(playerid != targetid) {
				if(targetid != INVALID_PLAYER_ID) {
					if(PlayerInfo[targetid][pFactiune] == FACT_CIVIL && PlayerInfo[targetid][pLeader] == FACT_CIVIL) {
						SendClientMessage(playerid, COLOR_GREEN, "_______________________________________________________________________");
						format(string, MAXO_TEXT, "xxx [ (SQLID: %d) %s - Level %d, %s ] xxx", PlayerInfo[targetid][pSQLID], PlayerName(targetid), PlayerInfo[targetid][pLevel], FactionInfo[PlayerInfo[targetid][pFactiune]][fName]);
						SendClientMessage(playerid, COLOR_LIGHTGREEN, string);
						format(string, MAXO_TEXT, "» NextPayDay: [%d] OnlineHours: [%d] ActiveHours: [%d]", (60 - PlayerInfo[targetid][pPayDayTime]), PlayerInfo[targetid][pConnectTime], PlayerInfo[targetid][pActiveTime]);
						SendClientMessage(playerid, COLOR_GRAD1, string);
						SendClientMessage(playerid, COLOR_GREEN, "_______________________________________________________________________");
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player cannot be checked.");
				}
			} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command for yourself.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/checkpday [playerid/PartOfName]");
	} else NotAuthorized();
	return true;
}

COMMAND:fmotd(playerid, params[]) {
	new string[MAXO_TEXT];
	if(PlayerInfo[playerid][pLeader] > FACT_CIVIL || PlayerInfo[playerid][pRank] > 4) {
		if(!sscanf(params, "s[128]", params)) {
			if(strlen(params) > 5) {
				if(strlen(params) > 5) {
					format(string, MAXO_TEXT, "Faction ANNO: {FFFFFF}%s.", params);
					SendFamilyMessage(COLOR_LIGHTRED, string, PlayerInfo[playerid][pFactiune]);
				}
				FactionInfo[PlayerInfo[playerid][pFactiune]][fAnnounce] = string;
				format(string, MAXO_TEXT, "UPDATE factions SET Announce = '%s' WHERE ID = %d", params, FactionInfo[PlayerInfo[playerid][pFactiune]][fSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", FACTIONS_THREAD_ID);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "The text must be of minimum 6 characters.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/fmotd [text]");
	} else NotAuthorized();
	return true;
}

COMMAND:applications(playerid, params[]) {
	new factiune = PlayerInfo[playerid][pFactiune], string[MAXO_TEXT];
	if(PlayerInfo[playerid][pLeader] > FACT_CIVIL) {
		if(FactionInfo[factiune][fApplication] == 0) {
			FactionInfo[factiune][fApplication] = 1;
			format(string, MAXO_TEXT, "LeadCmd: %s opened the applications for the faction %s.", PlayerName(playerid), FactionInfo[factiune][fName]);
		}
		else
		{
			FactionInfo[factiune][fApplication] = 0;
			format(string, MAXO_TEXT, "LeadCmd: %s closed the applications for the faction %s.", PlayerName(playerid), FactionInfo[factiune][fName]);
		}
		OOCNews(COLOR_LIGHTRED, string);
		format(string, MAXO_TEXT, "UPDATE factions SET App = %d WHERE ID = %d", FactionInfo[factiune][fApplication], factiune);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", FACTIONS_THREAD_ID);
		clear.string(string);
	} else NotAuthorized();
	return true;
}

COMMAND:licenses(playerid, params[]) {
	new
		string[MAXO_TEXT];
	SendClientMessage(playerid, -1, "|__________________ "ALBASTRU2"Licenses"ALB" __________________|");
	if(PlayerInfo[playerid][pDrivingLicense] == 0) {
		SendClientMessage(playerid, COLOR_GRAD1, "** Driving License: "GALBEN"None.");
	}
	else if(PlayerInfo[playerid][pDrivingLicense] >= gLocalTimeStamp) {
		format(string, MAXO_TEXT, "** Driving License valid: "GALBEN"%s", DateToTimestamp(PlayerInfo[playerid][pDrivingLicense], 1));
		SendClientMessage(playerid, COLOR_GRAD1, string);
	}
	else if(PlayerInfo[playerid][pDrivingLicense] <= gLocalTimeStamp) {
		SendClientMessage(playerid, COLOR_GRAD1, "** Driving License: "GALBEN"Expired.");
	}
	if(PlayerInfo[playerid][pFlyingLicense] == 0) {
		SendClientMessage(playerid, COLOR_GRAD1, "** Flying License: "GALBEN"None.");
	}
	else if(PlayerInfo[playerid][pFlyingLicense] >= gLocalTimeStamp) {
		format(string, MAXO_TEXT, "** Flying License valid: "GALBEN"%s", DateToTimestamp(PlayerInfo[playerid][pFlyingLicense], 1));
		SendClientMessage(playerid, COLOR_GRAD1, string);
	}
	else if(PlayerInfo[playerid][pFlyingLicense] <= gLocalTimeStamp) {
		SendClientMessage(playerid, COLOR_GRAD1, "** Flying License: "GALBEN"Expired.");
	}
	if(PlayerInfo[playerid][pSailingLicense] == 0) {
		SendClientMessage(playerid, COLOR_GRAD1, "** Sailing License: "GALBEN"None.");
	}
	else if(PlayerInfo[playerid][pSailingLicense] >= gLocalTimeStamp) {
		format(string, MAXO_TEXT, "** Sailing License valid: "GALBEN"%s", DateToTimestamp(PlayerInfo[playerid][pSailingLicense], 1));
		SendClientMessage(playerid, COLOR_GRAD1, string);
	}
	else if(PlayerInfo[playerid][pSailingLicense] <= gLocalTimeStamp) {
		SendClientMessage(playerid, COLOR_GRAD1, "** Sailing License: "GALBEN"Expired.");
	}
	if(PlayerInfo[playerid][pGunLic] < 10) SendClientMessage(playerid, COLOR_GRAD1, "** Weapon License valid until: "GALBEN"None.");
	else if(PlayerInfo[playerid][pGunLic] >= gLocalTimeStamp) {
		format(string, MAXO_TEXT, "** Weapon License level: "GALBEN"%s "GRI"expires: "GALBEN"%s", (gDynPlayerInfo[playerid][pGunLicType] == 2) ? ("Advanced shooter") : ("Beginner shooter"),DateToTimestamp(PlayerInfo[playerid][pGunLic],1));
		SendClientMessage(playerid, COLOR_GRAD1, string);
	} 
	clear.string(string);
	return true;
}

COMMAND:leaderhelp(playerid, params[]) {
	if(PlayerInfo[playerid][pLeader] > FACT_CIVIL) {
		SendClientMessage(playerid, COLOR_GREEN, "______________________________________________________________________");
		SendClientMessage(playerid, -1, "*** Leader Help - type a command for more informations. ***");
		SendClientMessage(playerid, COLOR_GREY, "*** Leader Commands *** /tmpinvite /invite /uninvite /ouninvite /giverank /fwarn /members /l(eader)c(hat) /fmotd /applications");
		SendClientMessage(playerid, COLOR_GREEN, "______________________________________________________________________");
	} else NotAuthorized();
	return true;
}

COMMAND:fly(playerid,params[]) {
	if(PlayerInfo[playerid][pAdmin] < 1) return NotAuthorized();
	if(IsPlayerInInside(playerid))
		return SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command from an interior.");
	if(PlayerInfo[playerid][pWlvl])
		return SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command because you're wanted."); // Anti Abuz
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
		if(!OnFly{playerid}) StartFly(playerid);
		else StopFly(playerid);
	} else SendClientMessage(playerid, COLOR_GRAD1, "You need to be onfoot to perform this command.");
	return 1;
}

COMMAND:startfire(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] >= 1337) {
		GenFireMission();
	} else NotAuthorized();
	return true;
}

COMMAND:opensafe(playerid, params[]) {
	new fID = PlayerInfo[playerid][pFactiune];
	if(fID > FACT_CIVIL) {
		if(IsPlayerInRangeOfPoint(playerid, 3.0, SafeInfo[fID][seifPos][0], SafeInfo[fID][seifPos][1], SafeInfo[fID][seifPos][2]))
			ShowPlayerDialog(playerid, DIALOGID_SAFE_INFO, DIALOG_STYLE_LIST, "Safe Options", "1. Drugs\n2. Materials\n3. Money\n4. Balance", "Ok", "Cancel");
		else
			SendClientMessage(playerid, COLOR_GRAD1, "You are not close of safe.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You have to be member in a faction to use the safe.");
	return true;
}

COMMAND:changetypesafe(playerid, params[]) {
	new string[MAXO_TEXT], fID, stype;
	if(PlayerInfo[playerid][pAdmin] > 5) {
		if(!sscanf(params, "dd", fID, stype)) {
			if(ISBetween(fID, FACT_CIVIL, MAX_FACTIONS)) {
				if(ISBetween(stype, 0, 7)) {
					SafeInfo[fID][seifType] = stype;
					format(string, MAXO_TEXT, "UPDATE safes SET seifType = %d WHERE ID = %d", SafeInfo[fID][seifType], fID);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", SAFE_THREAD_ID);
					format(string, MAXO_TEXT, "AdmCmd: %s changed your type of safe.", PlayerName(playerid));
					ABroadCast(COLOR_LIGHTRED, string, 1);
					format(string, MAXO_TEXT, "*** FactInfo: You safe type was changed by Admin %s.", PlayerName(playerid));
					SendFamilyMessage(COLOR_LIGHTBLUE, string, fID);
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "invalid type safe.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid faction.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/changetypesafe [factionid] [safetype]");
	} else NotAuthorized();
	return true;
}

COMMAND:spikes(playerid, params[]) {
	new Float:plocx, Float:plocy, Float:plocz, Float:ploca;
	if(IsPlayerCop(playerid)) {
		if(!sscanf(params, "s[4]", params)) {
			if(!IsPlayerInAnyVehicle(playerid)) {
				if(!strcmp(params, "on", true)) {
					GetPlayerPos(playerid, plocx, plocy, plocz);
					GetPlayerFacingAngle(playerid,ploca);
					CreateStrip(plocx,plocy,plocz + 0.1,ploca);
				}
				else if(!strcmp(params, "off", true)) {
					DeleteAllStrip();
				}
			} else SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command from an vehicle.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/spikes [on/off]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't member in the faction PD/NG.");
	return true;
}

COMMAND:clearwanted(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(IsPlayerCop(playerid)) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(PlayerInfo[targetid][pWlvl]) {
					PlayerInfo[targetid][pWlvl] = 0;
					SetPlayerWanted(targetid, INVALID_PLAYER_ID, 0);
					format(string, MAXO_TEXT, "UPDATE players SET Wanted = %d WHERE ID = %d", PlayerInfo[targetid][pWlvl], PlayerInfo[targetid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					format(string, MAXO_TEXT, "* You cleared the Records and Wanted Points of %s.", PlayerName(targetid));
					SendClientMessage(playerid, COLOR_LIGHTRED, string);
					switch(PlayerInfo[playerid][pFactiune]) {
						case FACT_LSPD: format(string, MAXO_TEXT, "* Officer %s has cleared your Record and Wanted Points.", PlayerName(playerid));
						case FACT_FBI: format(string, MAXO_TEXT, "* Agent %s has cleared your Record and Wanted Points.", PlayerName(playerid));
					}
					SendClientMessage(targetid, COLOR_LIGHTRED, string);
					PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is wanted.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/clearwanted [playerid/PartOfName]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG.");
	return true;
}

COMMAND:roadblock(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(IsPlayerCop(playerid)) {
		if(!sscanf(params, "s[4]", params)) {
			if(PlayerInfo[playerid][pRank] > 4) {
				if(IsPlayerInRangeOfPoint(playerid, 30.0, -892.8671, -1110.7469, 98.7)) {
					if(!strcmp(params, "on", true)) {
						#if defined _stream_objects
							MoveDynamicObject(rb1, -893.00000000, -1110.69995117, 98.69999695, 5);
							MoveDynamicObject(rb2, -894.40002441, -1116.00000000, 98.69999695, 5);
							MoveDynamicObject(rbls, -905.40002441, -1101.50000000, 99.30000305, 5);
						#else
							MoveObject(rb1, -893.00000000, -1110.69995117, 98.69999695, 5);
							MoveObject(rb2, -894.40002441, -1116.00000000, 98.69999695, 5);
							MoveObject(rbls, -905.40002441, -1101.50000000, 99.30000305, 5);
						#endif
						switch(PlayerInfo[playerid][pFactiune]) {
							case FACT_LSPD: format(string, MAXO_TEXT, "* Officer %s has activated the LS Road Block.", PlayerName(playerid));
							case FACT_FBI: format(string, MAXO_TEXT, "* Agent %s has activated the LS Road Block.", PlayerName(playerid));
						}
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_LSPD);
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_FBI);
					}
					else if(!strcmp(params, "off", true)) {
						#if defined _stream_objects
							MoveDynamicObject(rb1, -892.90002441, -1110.69995117, 97.09999847, 5);
							MoveDynamicObject(rb2, -894.40002441, -1116.00000000, 97.09999847, 5);
							MoveDynamicObject(rbls,-905.40002441, -1101.50000000, 94.19999695, 5);
						#else
							MoveObject(rb1, -892.90002441, -1110.69995117, 97.09999847, 5);
							MoveObject(rb2, -894.40002441, -1116.00000000, 97.09999847, 5);
							MoveObject(rbls,-905.40002441, -1101.50000000, 94.19999695, 5);
						#endif
						switch(PlayerInfo[playerid][pFactiune]) {
							case FACT_LSPD: format(string, MAXO_TEXT, "* Officer %s has dezactivated the LS Road Block.", PlayerName(playerid));
							case FACT_FBI: format(string, MAXO_TEXT, "* Agent %s has dezactivated the LS Road Block.", PlayerName(playerid));
						}
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_LSPD);
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_FBI);
					}
				}
				if(IsPlayerInRangeOfPoint(playerid, 30.0, -1218.9285, -780.0034, 63.9583)) {
					if(!strcmp(params, "on", true)) {
						#if defined _stream_objects
							MoveDynamicObject(rbsf1, -1223.19995117, -783.09997559, 63.29999924, 5);
							MoveDynamicObject(rbsf2, -1215.80004883, -776.09997559, 63.29999924, 5);
							MoveDynamicObject(rbsf3, -1210.90002441, -788.00000000, 65.00000000, 5);
						#else
							MoveObject(rbsf1, -1223.19995117, -783.09997559, 63.29999924, 5);
							MoveObject(rbsf2, -1215.80004883, -776.09997559, 63.29999924, 5);
							MoveObject(rbsf3, -1210.90002441, -788.00000000, 65.00000000, 5);
						#endif
						switch(PlayerInfo[playerid][pFactiune]) {
							case FACT_LSPD: format(string, MAXO_TEXT, "* Officer %s has activated the SF Road Block.", PlayerName(playerid));
							case FACT_FBI: format(string, MAXO_TEXT, "* Agent %s has activated the SF Road Block.", PlayerName(playerid));
						}
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_LSPD);
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_FBI);
					}
					else if(!strcmp(params, "off", true)) {
						#if defined _stream_objects
							MoveDynamicObject(rbsf1, -1223.19995117, -783.09997559, 62.09999847, 5);
							MoveDynamicObject(rbsf2, -1215.80004883, -776.09997559, 62.09999847, 5);
							MoveDynamicObject(rbsf3, -1210.90002441, -788.00000000, 58.90000153, 5);
						#else
							MoveObject(rbsf1, -1223.19995117, -783.09997559, 62.09999847, 5);
							MoveObject(rbsf2, -1215.80004883, -776.09997559, 62.09999847, 5);
							MoveObject(rbsf3, -1210.90002441, -788.00000000, 58.90000153, 5);
						#endif
						switch(PlayerInfo[playerid][pFactiune]) {
							case FACT_LSPD: format(string, MAXO_TEXT, "* Officer %s has dezactivated the SF Road Block.", PlayerName(playerid));
							case FACT_FBI: format(string, MAXO_TEXT, "* Agent %s has dezactivated the SF Road Block.", PlayerName(playerid));
						}
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_LSPD);
						SendFamilyMessage(COLOR_DEPARTMENT, string, FACT_FBI);
					}
				}
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "You need Rank 5+ to use this command.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/roadblock [on/off]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG.");
	return true;
}

COMMAND:showmembers(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pFactiune] > FACT_CIVIL) {
		SendClientMessage(playerid, -1, "|______________ Online Members ______________|");
		foreach(Player, i) {
			if(IsPlayerConnected(i)) {
				if(PlayerInfo[i][pFactiune] > FACT_CIVIL) {
					if(PlayerInfo[i][pFactiune] == PlayerInfo[playerid][pFactiune]) {
						format(string, MAXO_TEXT, "* [%d]%s: Rank %d *", i, PlayerName(i), PlayerInfo[i][pRank]);
						SendClientMessage(playerid, COLOR_GREY, string);
						clear.string(string);
					}
				}
			}
		}
	} else SendClientMessage(playerid, COLOR_GRAD1, "You must be member in a faction to use this command.");
	return true;
}

COMMAND:sm(playerid, params[]) {
	return cmd_showmembers(playerid, params);
}

COMMAND:heal(playerid, params[]) {
	new
		casa = PlayerInfo[playerid][pInHouseID], string[MAXO_TEXT], targetid, price,
		vID = GetPlayerVehicleID(playerid), Float:tmpheal, hq = PlayerInfo[playerid][pInHQID];
	if(casa) {
		if(IsPlayerCop(playerid)) {
			if(HouseInfo[casa][hArmour] != 0) {
				SetPlayerArmour(playerid, 100.0);
				format(string, MAXO_TEXT, "* %s puts on body armour.", PlayerName(playerid));
				SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
			}
		}
		if(HouseInfo[casa][hHeal] != 0) {
			new
				Float:tmphealth;
			GetPlayerHealth(playerid, tmphealth);
			if(tmphealth < 100.0) {
				SetPlayerHealth(playerid, 100.0);
				SendClientMessage(playerid, -1, "You have been healed to 100 health.");
			}
		}
	}
	else if(hq) {
		if(IsPlayerCop(playerid)) {
			SetPlayerArmour(playerid, 100.0);
			format(string, MAXO_TEXT, "* %s puts on body armour.", PlayerName(playerid));
			SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
			SetPlayerHealth(playerid, 100.0);
			SendClientMessage(playerid, -1, "You have been healed to 100 health.");
		}
		else
		{
			SetPlayerHealth(playerid, 100.0);
			SendClientMessage(playerid, -1, "You have been healed to 100 health.");
		}
	}
	else
	{
		if(!sscanf(params, "s[24]d", PartialName[playerid][nume_introdus], price)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(PlayerInfo[playerid][pFactiune] == FACT_MEDIC) {
				if(targetid != INVALID_PLAYER_ID) {
					if(targetid != playerid) {
						if(ISBetween(price, 1, 5000)) {
							if(PlayerInfo[targetid][pCash] >= price) {
								if(CarInfo[vID][cFactionID] == FACT_MEDIC) {
									GetPlayerHealth(targetid, tmpheal);
									if(tmpheal < 100.0) {
										SetPlayerHealth(targetid, 100.0);
										SafeGivePlayerMoney(playerid, price);
										SafeGivePlayerMoney(targetid, -price);
										ConsumingMoney[playerid] = 1;
										format(string, MAXO_TEXT, "You have been healed by Medic %s, for price of $%s.", PlayerName(playerid), FormatNumber(price, 0, '.'));
										SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
										format(string, MAXO_TEXT, "~r~-~g~$~w~%s", FormatNumber(price, 0, '.'));
										GameTextForPlayer(targetid, string, 3000, 1);
										format(string, MAXO_TEXT, "~g~+~g~$~w~%s", FormatNumber(price, 0, '.'));
										GameTextForPlayer(playerid, string, 3000, 1);
										PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
									} else SendClientMessage(playerid, COLOR_GRAD1, "This player is full healed.");
								} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in an vehicle for your faction.");
							} else SendClientMessage(playerid, COLOR_GRAD1, "This player not have enough money for must be healed.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "The price must be between $1-$5.000.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command on yourself.");
				}
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must be member in Medics/Fireman faction.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/heal [playerid/PartOfName] [price]");
	}
	clear.string(string);
	return true;
}

COMMAND:sellpills(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid, amount, price;
	if(PlayerInfo[playerid][pFactiune] == FACT_MEDIC) {
		if(!sscanf(params, "s[24]dd", PartialName[playerid][nume_introdus], amount, price)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(PlayerInfo[playerid][pPills] >= amount) {
				if(targetid != INVALID_PLAYER_ID) {
					if(targetid != playerid) {
						if(ISBetween(amount, 1, 50)) {
							if(price > 0) {
								if(PlayerInfo[targetid][pCash] >= price) {
									if(GetDistanceBetweenPlayers(playerid, targetid) < 4) {
										if(PlayerInfo[targetid][pPills] + amount <= 50) {
											format(string, MAXO_TEXT, "* You offerd %s %d pills for $%s.", PlayerName(targetid), amount, FormatNumber(price, 0, '.'));
											SendClientMessage(playerid, COLOR_FAMILY, string);
											format(string, MAXO_TEXT, "* Medic %s wants to sell you %d pills for $%s, (type /accept %d pills) to buy.", PlayerName(playerid), amount, FormatNumber(price, 0, '.'), playerid);
											SendClientMessage(targetid, COLOR_FAMILY, string);
											PillsOffer[targetid] = playerid;
											PillsPrice[targetid] = price;
											Pills[targetid] = amount;
											PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
											clear.string(string);
										} else SendClientMessage(playerid, COLOR_GRAD1, "This amount is much more of 50 pills.");
									} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is near you.");
								} else SendClientMessage(playerid, COLOR_GRAD1, "This player don't have enough money to pay your pills.");
							} else SendClientMessage(playerid, COLOR_GRAD1, "The price of the pills should be at least 1.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "Pills not lower then 1, or above 50.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command on yourself.");
				}
			} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have this amount of pills.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "USAGE: {FFFFFF}/sellpills [playerid/PartOfName] [amount] [price]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You must be member Medics/Fireman to use this command.");
	return true;
}

function ResetCaller(playerid) {
	if(ClientCaller{playerid})
		ClientCaller{playerid} = false;
	return 1;
}

#define ACCEPT_TIME	30

stock IsAvailableMembers(fID) {
	new
		NrMembers = 0;
	switch(fID) {
		case FACT_MEDIC: {
			foreach(Player, i) {
				if(PlayerInfo[i][pFactiune] == FACT_MEDIC) {
					if(ClientAccept[i] == INVALID_PLAYER_ID) {
						NrMembers ++,
						AcceptTime[i] = ACCEPT_TIME;
					}
				}
			}
		}
		case FACT_TAXI: {
			foreach(Player, i) {
				if(PlayerInfo[i][pFactiune] == FACT_TAXI) {
					if(ClientAccept[i] == INVALID_PLAYER_ID) {
						NrMembers ++,
						AcceptTime[i] = ACCEPT_TIME;
					}
				}
			}
		}
	}
	return NrMembers;
}

COMMAND:service(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(!sscanf(params, "s[10]", params)) {
		if(!HaveVisibleCheckpoint(playerid)) {
			if(!PlayerInfo[playerid][pInBizzID] || !PlayerInfo[playerid][pInHouseID] || !PlayerInfo[playerid][pInHQID]) {
				if(strlen(params) < 11) {
					if(!strcmp(params, "ambulance", true)) {
						if(PlayerInfo[playerid][pFactiune] != FACT_MEDIC) {
							if(IsAvailableMembers(FACT_MEDIC) != 0) {
								format(string, sizeof(string), "** %s is in need of a Medic. (use /accept %d ambulance to accept the call)", PlayerName(playerid), playerid);
								SendFamilyMessage(COLOR_FAMILY, string, FACT_MEDIC);
								SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have called for a Medic, wait for a reply.");
							} else SendClientMessage(playerid, COLOR_GRAD1, "In this moment not is any medic available, try again later.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "This service is unavailable for Medics.");
					}
					else if(!strcmp(params, "taxi", true)) {
						if(PlayerInfo[playerid][pFactiune] != FACT_TAXI) {
							if(IsAvailableMembers(FACT_TAXI) != 0) {
								format(string, sizeof(string), "** %s is in need of a taxi driver. (use /accept %d taxi to accept the call)", PlayerName(playerid), playerid);
								SendFamilyMessage(COLOR_FAMILY, string, FACT_TAXI);
								SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have called for a Taxi, wait for a reply.");
							} else SendClientMessage(playerid, COLOR_GRAD1, "In this moment not is any taxi driver available, try again later.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "This service is unavailable for Taxi members.");
					}
					else SendClientMessage(playerid, COLOR_GRAD1, "Invalid option, type again /service to view the options available.");
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command from an interior.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command, you have an checkpoint visible.");
		ClientCaller{playerid} = true;
		SetTimerEx("ResetCaller", ACCEPT_TIME * 1000, false, "d", playerid);
	} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/service [option]"), SendClientMessage(playerid, COLOR_GREY, "Options available: ambulance | taxi");
	return true;
}

/*COMMAND:drag(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid, seat, Float:DPositions[3][3];
	if(PlayerInfo[playerid][pFactiune] == FACT_MEDIC) {
		if(!sscanf(params, "ud", targetid, seat)) {
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(ISBetween(seat, 1, 2)) {
						if(!IsPlayerInAnyVehicle(targetid)) {
							if(GetDistanceBetweenPlayers(playerid, targetid) < 4) {
								if(IsPlayerSterilized{targetid}) {
									GetPlayerPos(playerid, DPositions[0][0], DPositions[0][1], DPositions[0][2]);
									GetPlayerPos(targetid, DPositions[1][0], DPositions[1][1], DPositions[1][2]);
									GetVehiclePos(GetPlayerVehicleID(playerid), DPositions[2][0], DPositions[2][1], DPositions[2][2]);
									format(string, MAXO_TEXT, "* You were drug by %s .", PlayerName(playerid));
									SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
									format(string, MAXO_TEXT, "* You drug %s .", PlayerName(targetid));
									SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
									format(string, MAXO_TEXT, "* %s throws %s in the back of the Ambulance.", PlayerName(playerid), PlayerName(targetid));
									SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
									GameTextForPlayer(targetid, "~r~Dragged", 2500, 3);
									ClearAnimations(targetid);
									TogglePlayerControllable(targetid, false);
									PutPlayerInVehicle(targetid, GetPlayerVehicleID(playerid), seat);
								} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is sterilized.");
							} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is near you.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "This player is in an vehicle.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "Seatid is between 1-2.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can not drag yourself.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid player.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/drag [playerid/PartOfName] [seatid]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member Medics/Fireman to use this command.");
	return true;
}

COMMAND:sterile(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pFactiune] == FACT_MEDIC) {
		if(!sscanf(params, "u", targetid)) {
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(!IsPlayerSterilized{targetid}) {
						if(!IsPlayerInAnyVehicle(targetid)) {
							if(GetDistanceBetweenPlayers(playerid, targetid) < 5.0) {
								format(string, MAXO_TEXT, "* You were Sterilized by %s for 30 seconds.", PlayerName(playerid));
								SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
								format(string, MAXO_TEXT, "* You Sterilized %s for 30 seconds.", PlayerName(targetid));
								SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
								format(string, MAXO_TEXT, "* %s takes their syringe out and holds %s down.", PlayerName(playerid), PlayerName(targetid));
								SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
								format(string, MAXO_TEXT, "* %s injects %s, and sterilized them.", PlayerName(playerid), PlayerName(targetid));
								SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
								GameTextForPlayer(targetid, "~r~Sterilized", 2500, 3);
								ApplyAnimation(targetid, "CRACK", "crckdeth2", 4.0, 0, 0, 0, 0, 30000);
								TogglePlayerControllable(targetid, false);
								IsPlayerSterilized{targetid} = true;
								PlayerSterilizedTime[targetid] = 30;
							} else SendClientMessage(playerid, COLOR_GRAD1, "This player is too far away from you.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "This player is in an vehicle.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player is already sterilized.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command on yourself.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid player.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/sterile [playerid/PartOfName]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member Medics/Fireman to use this command.");
	return true;
}*/

COMMAND:tie(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(IsPlayerGangster(playerid)) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(!IsPlayerTied{targetid}) {
						if(!IsPlayerInVehicle(targetid, GetPlayerVehicleID(playerid)) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !IsPlayerInAnyVehicle(targetid)) {
							IsPlayerTied{targetid} = true;
							TogglePlayerControllable(targetid, false);
							format(string, MAXO_TEXT, "* You were tied up by %s, till untie.", PlayerName(playerid));
							SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
							format(string, MAXO_TEXT, "* You tied %s up, till untie.", PlayerName(targetid));
							SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
							format(string, MAXO_TEXT, "* %s ties %s up, so he wont go anywhere.", PlayerName(playerid), PlayerName(targetid));
							SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
							GameTextForPlayer(targetid, "~r~Tied", 2500, 3);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
							clear.string(string);
						} else SendClientMessage(playerid, COLOR_GRAD1, "You are not the driver, or this player not is in your vehicle.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player is already tied.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command on yourself.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/tie [playerid/PartOfName]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not gangster, can not use this command.");
	return true;
}

COMMAND:untie(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(IsPlayerGangster(playerid)) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(IsPlayerTied{targetid}) {
						if(!IsPlayerInVehicle(targetid, GetPlayerVehicleID(playerid)) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
							IsPlayerTied{targetid} = false;
							TogglePlayerControllable(targetid, true);
							format(string, MAXO_TEXT, "* You were Untied by %s.", PlayerName(playerid));
							SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
							format(string, MAXO_TEXT, "* You Untied %s.", PlayerName(targetid));
							SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
							GameTextForPlayer(targetid, "~g~Untied", 2500, 3);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
							clear.string(string);
						} else SendClientMessage(playerid, COLOR_GRAD1, "You are not the driver, or this player not is in your vehicle.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is tied.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command on yourself.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/tie [playerid/PartOfName]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not gangster, can not use this command.");
	return true;
}

COMMAND:contract(playerid, params[]) {
	new
		string[MAXO_TEXT2], targetid, price;
	if(PlayerInfo[playerid][pLevel] > 2) {
		if(!sscanf(params, "s[24]d", PartialName[playerid][nume_introdus], price)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(PlayerInfo[targetid][pFactiune] != FACT_HITMAN) {
						if(PlayerInfo[playerid][pFactiune] != FACT_HITMAN) {
							if(ISBetween(price, 10000, 100000)) {
								if(PlayerInfo[playerid][pCash] >= price) {
									if(IsPlayerCop(targetid) && price != 100000)
										return SendClientMessage(playerid, COLOR_GRAD1, "This player is cop, the price for this contract is $100.000.");
									SafeGivePlayerMoney(playerid, -price);
									PlayerInfo[targetid][pHeadValue] += price;
									format(string, MAXO_TEXT, "* %s has just put contract on %s, for $%s.", PlayerName(playerid), PlayerName(targetid), FormatNumber(price, 0, '.'));
									SendFamilyMessage(COLOR_ORANGE, string, FACT_HITMAN);
									format(string, MAXO_TEXT, "You have put contract on %s, to kill for $%s.", PlayerName(targetid), FormatNumber(price, 0, '.'));
									SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
									format(string, MAXO_TEXT, "UPDATE players SET HeadValue = %d WHERE ID = %d", PlayerInfo[targetid][pHeadValue], PlayerInfo[playerid][pSQLID]);
									mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
									PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
									clear.string(string);
								} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have this amount cash.");
							} else SendClientMessage(playerid, COLOR_GRAD1, "The price must be between $10.000 - $100.000.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command, because you are not Hitman.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You can not put a contract on this player.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command on yourself.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/contract [playerid/PartOfName] [price]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You need of Level 3+ to use this command.");
	return true;
}

COMMAND:portable(playerid, params[]) {
	if(PlayerInfo[playerid][pFactiune] == FACT_HITMAN) {
		if(ConnectedToPC[playerid] == 255) {
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have shutdowned your Laptop, and Disconnected from your Agency.");
			ConnectedToPC[playerid] = 0;
			return true;
		}
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have booted up your Laptop, and Connected to your Agency.");
		SendClientMessage(playerid, COLOR_WHITE, "|___ Hitman Agency ___|");
		SendClientMessage(playerid, COLOR_YELLOW2, "|");
		SendClientMessage(playerid, COLOR_YELLOW2, "| - News");
		SendClientMessage(playerid, COLOR_YELLOW2, "| - Contracts");
		SendClientMessage(playerid, COLOR_YELLOW2, "| - Givehit");
		SendClientMessage(playerid, COLOR_YELLOW2, "| - Order");
		SendClientMessage(playerid, COLOR_YELLOW2, "| - Ranks");
		SendClientMessage(playerid, COLOR_YELLOW2, "| - Undercover");
		SendClientMessage(playerid, COLOR_YELLOW2, "| - Myhit");
		SendClientMessage(playerid, COLOR_YELLOW2, "| - CheckMyContracts");
		SendClientMessage(playerid, COLOR_YELLOW2, "| - Logout");
		SendClientMessage(playerid, COLOR_WHITE, "|______________|00:00|");
		ConnectedToPC[playerid] = 255;
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not a member of the Hitman Agency !");
	return true;
}

COMMAND:checkcontracts(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pFactiune] == FACT_HITMAN) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				SendClientMessage(playerid, -1, "|__________ Contracts available __________|");
				format(string, MAXO_TEXT, "* Fulfilled contracts by %s:  %d", PlayerName(targetid), PlayerInfo[targetid][pContracts]);
				SendClientMessage(playerid, COLOR_GREY, string);
				PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
				clear.string(string);
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/checkcontracts [playerid/PartOfName]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not a member of the Hitman Agency !");
	return true;
}

COMMAND:deletecontracts(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pFactiune] == FACT_HITMAN) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				format(string, MAXO_TEXT, "* You have reset fulfilled contracts by %s.", PlayerName(playerid));
				SendClientMessage(playerid, COLOR_GREY, string);
				SendClientMessage(targetid, COLOR_GREY, "Your contracts has been reset by Leader.");
				PlayerInfo[targetid][pContracts] = 0;
				format(string, MAXO_TEXT, "UPDATE players SET Contracts = 0 WHERE ID = %d", PlayerInfo[targetid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
				clear.string(string);
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/checkcontracts [playerid/PartOfName]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not a member of the Hitman Agency !");
	return true;
}

#define PRICE_PLACE_NEWS 500

COMMAND:news(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pFactiune] == FACT_CNN) {
		if(CarInfo[GetPlayerVehicleID(playerid)][cFactionID] == FACT_CNN) {
			if(!sscanf(params, "s[100]", params)) {
				if(strlen(params) < 100) {
					if(PlayerInfo[playerid][pMute])
						return IsPlayerSilent();
					format(string, MAXO_TEXT, "* Reporter %s: %s. *", PlayerName(playerid), params);
					OOCNews(COLOR_ORANGE, string);
					PlayerInfo[playerid][pNewsSkill] ++;
					format(string, MAXO_TEXT, "UPDATE players SET NewsSkill = %d WHERE ID = %d", PlayerInfo[playerid][pNewsSkill], PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					switch(PlayerInfo[playerid][pNewsSkill]) {
						case 50: SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Congratulations, Your News Reporter Skill is now Level 2.");
						case 100: SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Congratulations, Your News Reporter Skill is now Level 3.");
						case 200: SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Congratulations, Your News Reporter Skill is now Level 4.");
						case 400: SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Congratulations, Your News Reporter Skill is now Level 5.");
					}
					if(news_accepted{playerid}) {
						new
							ReporterAward = (PRICE_PLACE_NEWS / 2) * PlayerInfo[playerid][pRank];
						SafeGivePlayerMoney(playerid, ReporterAward);
						ConsumingMoney[playerid] = 1;
						news_occupied_with[playerid] = INVALID_PLAYER_ID;
						news_accepted{playerid} = false;
						format(string, MAXO_TEXT, "* You received $%s because you placed this announce.", FormatNumber(ReporterAward, 0, '.'));
						SendClientMessage(playerid, COLOR_YELLOW, string);
					}
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_YELLOW, "[Anti-Spam] Line too long.");
			} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/news [message]");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in an vehicle of faction to make public an announce.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command.");
	return true;
}

COMMAND:newsduty(playerid, params[]) {
	new
		string[MAXO_TEXT], vID = GetPlayerVehicleID(playerid);
	if(PlayerInfo[playerid][pFactiune] == FACT_CNN) {
		if(CarInfo[vID][cFactionID] == FACT_CNN) {
			news_duty{playerid} = !news_duty{playerid};
			format(string, sizeof(string), "* You are now %s duty, you %s place an announce.", (news_duty{playerid} ? "on" : "off"), (news_duty{playerid} ? "can" : "cannot"));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in an vehicle of faction.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command.");
	return true;
}

COMMAND:placenews(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pFactiune] != FACT_CNN) {
		if(PlayerInfo[playerid][pCash] > PRICE_PLACE_NEWS) {
			if(!sscanf(params, "s[24]s[100]", PartialName[playerid][nume_introdus], params)) {
				CheckName(playerid, PartialName[playerid][nume_introdus]);
				targetid = PartialName[playerid][jucator_gasit];
				if(strlen(params) < 100) {
					if(targetid != INVALID_PLAYER_ID) {
						if(targetid != playerid) {
							if(news_duty{targetid}) {
								if(news_occupied_with[targetid] == INVALID_PLAYER_ID) {
									if(PlayerInfo[playerid][pMute])
										return IsPlayerSilent();
									news_occupied_with[targetid] = playerid;
									format(string, MAXO_TEXT, "* You has sent an announce at Reporter %s (%s).", PlayerName(targetid), params);
									SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
									format(string, MAXO_TEXT2, "* You has received an announce (%s) from %s.", params, PlayerName(playerid));
									SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
									SendClientMessage(targetid, COLOR_LIGHTBLUE, "* Type /acceptnews or /rejectnews if you want to accept or reject this announce.");
									PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
									clear.string(string);
								} else SendClientMessage(playerid, COLOR_GRAD1, "This reporter is already occupied with place of an announce.");
							} else SendClientMessage(playerid, COLOR_GRAD1, "This reporter not is on duty.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot place an announce yourself.");
					}
				} else SendClientMessage(playerid, COLOR_YELLOW, "[Anti-Spam] Line too long.");
			} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/placenews [playerid/PartOfName] [message]");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have enough money to place an announce.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command.");
	return true;
}

COMMAND:acceptnews(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pFactiune] == FACT_CNN) {
		if(news_occupied_with[playerid] != INVALID_PLAYER_ID) {
			if(news_occupied_with[playerid] != playerid) {
				if(PlayerInfo[playerid][pMute])
					return IsPlayerSilent();
				format(string, MAXO_TEXT, "* You has accepted the announce from %s, for amount of $%s.", PlayerName(news_occupied_with[playerid]), FormatNumber(PRICE_PLACE_NEWS, 0, '.'));
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				format(string, MAXO_TEXT, "* Reporter %s has accepted your announce. Reporter award: $%s.", PlayerName(playerid), FormatNumber(PRICE_PLACE_NEWS, 0, '.'));
				SendClientMessage(news_occupied_with[playerid], COLOR_LIGHTBLUE, string);
				news_accepted{playerid} = true;
				SafeGivePlayerMoney(news_occupied_with[playerid], -PRICE_PLACE_NEWS);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "You don't received any announce.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You don't received any announce.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command.");
	return true;
}

COMMAND:rejectnews(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pFactiune] == FACT_CNN) {
		if(news_occupied_with[playerid] != INVALID_PLAYER_ID) {
			if(news_occupied_with[playerid] != playerid) {
				format(string, MAXO_TEXT, "* You has rejected the announce from %s.", PlayerName(news_occupied_with[playerid]));
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				format(string, MAXO_TEXT, "* Reporter %s has rejected your announce.", PlayerName(playerid));
				SendClientMessage(news_occupied_with[playerid], COLOR_LIGHTBLUE, string);
				news_occupied_with[playerid] = INVALID_PLAYER_ID;
				news_accepted{playerid} = false;
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "You don't received any announce.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You don't received any announce.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command.");
	return true;
}

COMMAND:live(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(TalkingLive[playerid] != 255) {
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Live Conversation ended.");
		SendClientMessage(TalkingLive[playerid], COLOR_LIGHTBLUE, "* Live Conversation ended.");
		TogglePlayerControllable(playerid, true);
		TogglePlayerControllable(TalkingLive[playerid], true);
		TalkingLive[TalkingLive[playerid]] = 255;
		TalkingLive[playerid] = 255;
		return true;
	}
	if(PlayerInfo[playerid][pFactiune] == FACT_CNN) {
		if(!PlayerInfo[playerid][pMute]) {
			if(PlayerInfo[playerid][pNewsSkill] > 399 || PlayerInfo[playerid][pRank] >= 4) {
				if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
					CheckName(playerid, PartialName[playerid][nume_introdus]);
					targetid = PartialName[playerid][jucator_gasit];
					if(GetDistanceBetweenPlayers(playerid, targetid) < 4) {
						if(targetid != playerid) {
							if(targetid != INVALID_PLAYER_ID) {
								if(PlayerInfo[targetid][pMute])
									return SendClientMessage(playerid, COLOR_LIGHTRED, "You can't speak Live with this player, he is mute.");
								if(PlayerInfo[playerid][pMute])
									return IsPlayerSilent();
								format(string, MAXO_TEXT, "* You offered %s to have a Live Conversation.", PlayerName(targetid));
								SendClientMessage(playerid, COLOR_FAMILY, string);
								format(string, MAXO_TEXT, "* %s offered you to have a Live Conversation, type (/accept %d live) to accept.", PlayerName(playerid), playerid);
								SendClientMessage(targetid, COLOR_FAMILY, string);
								LiveOffer[targetid] = playerid;
								AcceptTime[targetid] = ACCEPT_TIME;
								PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
								clear.string(string);
							}
						} else SendClientMessage(playerid, COLOR_GRAD1, "You can not talk live with yourself.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is near you.");
				} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/live [playerid/PartOfName]");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Your news reporter skill is too lower to talk with people.");
		} else IsPlayerSilent();
	} else SendClientMessage(playerid, COLOR_GRAD1, "You must be member in faction News Reporter to use this command.");
	return true;
}

COMMAND:fare(playerid,params[]) {
	new string[MAXO_TEXT], price;
	if(PlayerInfo[playerid][pFactiune] == FACT_TAXI) {
		if(TaxiST[playerid][TaxiDuty] > 0) {
			TaxiST[playerid][TaxiDuty] = 0;
			TransportValue[playerid] = 0;
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You are now Off Duty");
		}
		else
		{
			if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				if(CarInfo[GetPlayerVehicleID(playerid)][cFactionID] == FACT_TAXI) {
					if(!sscanf(params, "d", price)) {
						if(ISBetween(price, 1, 20)) {
							TaxiST[playerid][TaxiDuty] = 1;
							TransportValue[playerid] = price;
							format(string, MAXO_TEXT, "Taxi Driver %s is On Duty, fare: $%s.", PlayerName(playerid), FormatNumber(TransportValue[playerid], 0, '.' ));
							OOCNews(COLOR_GREEN, string);
							clear.string(string);
						} else SendClientMessage(playerid, COLOR_GREY, "Fare price must be between $1 and $20 !");
					} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/fare [price]");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You are not in a Taxi !");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You are not the Driver !");
		}
	} else SendClientMessage(playerid,COLOR_GREY,"You are not a Taxi / Bus Driver !");
	return 1;
}

COMMAND:factionspawn(playerid, params[]) {
	new string[MAXO_TEXT], optiune;
	if(!sscanf(params, "d", optiune)) {
		PlayerInfo[playerid][pFactionSpawn] = !PlayerInfo[playerid][pFactionSpawn];
		if(strlen(params) > 9)
			return SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: {FFFFFF}Line too long.");
		switch(PlayerInfo[playerid][pFactiune]) {
			case FACT_LSPD, FACT_FBI, FACT_MEDIC, FACT_LCN, FACT_YKZ, FACT_CNN, FACT_HITMAN, FACT_TAXI, FACT_BLOODS, FACT_CRIPS: {
				switch(optiune) {
					case 1: PlayerInfo[playerid][pFactionSpawn] = FACTIONSPAWN_PRIMARY;
					case 2: PlayerInfo[playerid][pFactionSpawn] = FACTIONSPAWN_SECONDARY;
					default: return SendClientMessage(playerid, COLOR_GRAD1, "Invalid option.");
				}
				format(string, MAXO_TEXT, "* You will now spawn at Faction Spawn %s.", (PlayerInfo[playerid][pFactionSpawn] ? "secondary" : "primary"));
				SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
				format(string, MAXO_TEXT, "UPDATE players SET FactionSpawn = %d WHERE ID = %d", PlayerInfo[playerid][pFactionSpawn], PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				clear.string(string);
			}
			case FACT_CIVIL: SendClientMessage(playerid, COLOR_GRAD1, "You cannot to change the faction spawn.");
		}
	} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/factionspawn [1 - primary / 2 - secondary]");
	return true;
}

COMMAND:spawnchange(playerid, params[]) {
	if(PlayerInfo[playerid][pPhousekey]) {
		if(PlayerInfo[playerid][pCash] > 999) {
			if(PlayerInfo[playerid][pSpawnChange] == 0) {
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You will now spawn at your Normal Place !");
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* Remember, the spawn will not remain same after server restart !");
				PlayerInfo[playerid][pSpawnChange] = 1;
			}
			else
			{
				PlayerInfo[playerid][pSpawnChange] = 0;
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You will now spawn at your Own / Rented House !");
			}
			SafeGivePlayerMoney(playerid, -1000);
			GameTextForPlayer(playerid, "~r~-~g~$~y~1.000", 2500, 1);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You need of $1.000 to change the spawn.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have a house or you're not renter to change the spawn.");
	return true;
}

COMMAND:duty(playerid, params[]) {
	new string[MAXO_TEXT], factiune = PlayerInfo[playerid][pFactiune];
	if(IsPlayerCop(playerid)) {
		if(GetPlayerVirtualWorld(playerid) == FactionInfo[factiune][fVirtualWorld] || GetPlayerVirtualWorld(playerid) == FactionInfo[factiune][fVirtualWorld]) {
			if(!IsCopDuty{playerid}) {
				SetPlayerHealth(playerid, 100.0);
				SetPlayerArmour(playerid, 100.0);
				GivePlayerWeapon(playerid, WEAPON_DEAGLE, 999);
				GivePlayerWeapon(playerid, WEAPON_SPRAYCAN, 999);
				GivePlayerWeapon(playerid, WEAPON_M4, 999);
				GivePlayerWeapon(playerid, WEAPON_NITESTICK, 1);
				GivePlayerWeapon(playerid, WEAPON_MP5, 999);
				GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 999);
				IsCopDuty{playerid} = true;
				format(string, MAXO_TEXT, "* Officer %s has took the equip from loocker.", PlayerName(playerid));
				SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
			}
			else if(IsCopDuty{playerid}) {
				ResetPlayerWeapons(playerid);
				SetPlayerHealth(playerid, 100.0);
				SetPlayerArmour(playerid, 0.0);
				GivePlayerWeapon(playerid, WEAPON_DEAGLE, 100);
				GivePlayerWeapon(playerid, WEAPON_SPRAYCAN, 500);
				GivePlayerWeapon(playerid, WEAPON_NITESTICK, 1);
				IsCopDuty{playerid} = false;
				format(string, MAXO_TEXT, "* Officer %s has left the badge and the guns in loocker.", PlayerName(playerid));
				SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
			}
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in inside of the HeadQuarter to use this command.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't member in LSPD or NG Agency.");
	return true;
}

COMMAND:ram(playerid, params[]) {
	if(IsPlayerCop(playerid)) {
		for(new i = 0; i < sizeof(HouseInfo); i ++) {
			if(IsPlayerInRangeOfPoint(playerid, 3.0, HouseInfo[i][hEntrancex], HouseInfo[i][hEntrancey], HouseInfo[i][hEntrancez])) {
				SafeSetPlayerPos(playerid, HouseInfo[i][hExitx], HouseInfo[i][hExity], HouseInfo[i][hExitz]);
				SafeSetPlayerInterior(playerid, HouseInfo[i][hInterior]);
				SafeSetPlayerVirtualWorld(playerid, HouseInfo[i][hVirtualWorld]+1000);
				PlayerInfo[playerid][pInHouseID] = i;
				GameTextForPlayer(playerid, "~r~Breached the door", 5000, 1);
			}
		}
	} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't member in faction PD/NG to use this command.");
	return true;
}

#pragma unused SkinRandom
new SkinRandom[][4] = {
	{21},
	{221},
	{236},
	{261}
};

COMMAND:undercover(playerid, params[]) {
	if(PlayerInfo[playerid][pFactiune] == FACT_LSPD) {
		if(PlayerInfo[playerid][pInHQID]) {
			if(!IsCopUndercover{playerid})
				SetPlayerColor(playerid, COLOR_WHITE), SetPlayerSkin(playerid, random(sizeof(SkinRandom)-1)), IsCopUndercover{playerid} = true;
			else
				SetPlayerFactionColor(playerid, PlayerInfo[playerid][pFactiune]), SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]), IsCopUndercover{playerid} = false;
		} else SendClientMessage(playerid, COLOR_GRAD1, "For this action, you must be in Headquarter.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't member in faction PD to use this command.");
	return true;
}

COMMAND:deliver(playerid, params[]) {
	new string[MAXO_TEXT], targetid;
	if(IsPlayerCop(playerid)) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != playerid) {
				if(targetid != INVALID_PLAYER_ID) {
					if(GetDistanceBetweenPlayers(playerid, targetid) < 5.0) {
						if(PlayerInfo[targetid][pWlvl] > 2) {
							SafeSetPlayerPos(targetid, 107.2300, 1920.6311, 18.5208);
							SetPlayerWorldBounds(targetid, 337.5694, 101.5826, 1940.9759, 1798.7453);
							if(IsPlayerInInside(playerid))
								SafeResetPlayerInterior(playerid);
							ResetPlayerWeapons(targetid);
							PlayerInfo[targetid][pJailed] = 2;
							PlayerInfo[targetid][pJailTime] = 3600;
							PlayerInfo[targetid][pWlvl] = 0;
							SetPlayerWanted(targetid, playerid, PlayerInfo[targetid][pWlvl]);
							TogglePlayerControllable(targetid, false);
							format(string, MAXO_TEXT2, "UPDATE players SET JailTime = %d, Jailed = %d, Wanted = %d WHERE ID = %d", PlayerInfo[targetid][pJailTime], PlayerInfo[targetid][pJailed], PlayerInfo[pWlvl], PlayerInfo[targetid][pSQLID]);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, ">> You are jailed in Restricted Area for %s by Cop %s. <<", ConvertTime(PlayerInfo[targetid][pJailTime]), PlayerName(playerid));
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "You has put on %s as prison in Restricted Area for %s.", PlayerName(targetid), ConvertTime(PlayerInfo[targetid][pJailTime]));
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
							clear.string(string);
						} else SendClientMessage(playerid, COLOR_GRAD1, "This player has no wanted level higher than 2.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player is too far away from you.");
				}
			} else SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command on yourself.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/deliver [playerid/PartOfName]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't member in the faction PD/NG.");
	return true;
}

function BackupClear(playerid, calledbytimer) {
	if(IsPlayerCop(playerid)) {
		if(PlayerInfo[playerid][pRequestingBackup] == 1) {
			foreach(new i: Player) {
				if(gPlayerLogged{i}) {
					if(IsPlayerCop(i)) {
						SetPlayerMarkerForPlayer(i, playerid, 1), SetPlayerColor(playerid, COLOR_FACT_LSPD);
					}
				}
			}
			if (calledbytimer != 1) { SendClientMessage(playerid, COLOR_FACT_LSPD, "Your backup request has been cleared."); }
			else { SendClientMessage(playerid, COLOR_FACT_LSPD, "Your backup request has been cleared automatically."); }
			PlayerInfo[playerid][pRequestingBackup] = 0;
		}
		else
		{
			if(calledbytimer != 1) { SendClientMessage(playerid, COLOR_RED, "You don't have an active backup request!"); }
		}
	}
	else
	{
		if(calledbytimer != 1) { SendClientMessage(playerid, COLOR_RED, " You are not a Cop !"); }
	}
	return true;
}

COMMAND:backup(playerid, params[]) {
	new string[MAXO_TEXT];
	if(IsPlayerCop(playerid)) {
		if(!PlayerInfo[playerid][pRequestingBackup]) {
			format(string, MAXO_TEXT, "ALL UNITS: %s is requesting immediate assistance, they have been marked on the map (red).", PlayerName(playerid));
			PlayerInfo[playerid][pRequestingBackup] = 1;
			foreach(new i: Player) {
				if(gPlayerLogged{i}) {
					if(IsPlayerCop(i))
						SetPlayerMarkerForPlayer(i, playerid, 0xFF0000FF),
						SendClientMessage(i, COLOR_DEPARTMENT, string);
				}
			}
			SetTimerEx("BackupClear", 280000, false, "ii", playerid, 1);
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You already have an active backup request.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't member in the faction PD/NG.");
	return true;
}

COMMAND:backupclear(playerid, params[]) {
	new string[MAXO_TEXT];
	if(IsPlayerCop(playerid)) {
		format(string, MAXO_TEXT, "ALL UNITS: %s is no longer in need of backup.", PlayerName(playerid));
		foreach(new i: Player) {
			if(gPlayerLogged{i}) {
				if(IsPlayerCop(i))
					SendClientMessage(playerid, COLOR_DEPARTMENT, string);
			}
		}
		BackupClear(playerid, 0);
		clear.string(string);
	} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't member in the faction PD/NG.");
	return true;
}

COMMAND:jaillist(playerid, params[]) {
	new string[MAXO_TEXT];
	if(IsPlayerCop(playerid)) {
		SendClientMessage(playerid, COLOR_WHITE, "|______________ Jail List ______________|");
		foreach(Player, i) {
			if(PlayerInfo[i][pJailed] != 0) {
				format(string, MAXO_TEXT, "* ID: %d | Name: %s | Jail Time Left: %s *", i, PlayerName(i), ConvertTime(PlayerInfo[i][pJailTime]));
				SendClientMessage(playerid, COLOR_GREY, string);
				if(i == INVALID_PLAYER_ID)
					return SendClientMessage(playerid, COLOR_GRAD1, "In this moment, nobody aren't in jail.");
			}
		}
		clear.string(string);
	} else SendClientMessage(playerid, COLOR_GRAD1, "You aren't member in the faction PD/NG.");
	return true;
}

stock NumeleFactiunii(factionid) {
	new string[MAX_FACTION_NAME+10];
	format(string, MAX_FACTION_NAME+10, "%s", FactionInfo[factionid][fName]);
	return string;
}

stock StatusRecrutari(factionid) {
	new string[MAXO_TEXT1];
	if(FactionInfo[factionid][fApplication] == 0)
		format(string, MAXO_TEXT1, "{FF0000}Closed{FFFFFF}");
	else
		format(string, MAXO_TEXT1, "{2FC914}Opened{FFFFFF}");
	return string;
}

stock LevelRecrutare(factionid) {
	new string[MAX_PLAYER_NAME];
	format(string, MAX_PLAYER_NAME, "%d", FactionInfo[factionid][fFactionLevel]);
	return FactionInfo[factionid][fFactionLevel];
}

COMMAND:factions(playerid, params[]) {
	new string[MAXO_TEXT2], string2[528];
	strcat(string2, "ID\tFaction Name\tApplications\tLevel Requirement\n");
	for(new i = 1; i < MAX_FACTIONS; i ++) {
		format(string, MAXO_TEXT, "%d\t%s\t%s\t%d\n", i, NumeleFactiunii(i), StatusRecrutari(i), LevelRecrutare(i));
		strcat(string2, string);
	}
	ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_TABLIST_HEADERS, "Factions List", string2, "Ok", "");
	clear.string(string);
	clear.string(string2);
	return true;
}

COMMAND:megaphone(playerid, params[]) {
	new
		string[MAXO_TEXT], vID = GetPlayerVehicleID(playerid);
	if(IsPlayerCop(playerid)) {
		if(!sscanf(params, "s[75]", params)) {
			if(IsVehicleForCop(vID)) {
				if(strlen(params) < 75) {
					if(PlayerInfo[playerid][pMute])
						return IsPlayerSilent();
					switch(PlayerInfo[playerid][pFactiune]) {
						case FACT_LSPD: format(string, MAXO_TEXT, "[ Officer %s: o< %s >o ]", PlayerName(playerid), params);
						case FACT_FBI: format(string, MAXO_TEXT, "[ Agent %s: o< %s >o ]", PlayerName(playerid), params);
					}
					SendPlayerMessage(60.0, playerid, string, COLOR_YELLOW);
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in an vehicle of faction (PD/NG) to use this command.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/m(egaphone) [message]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG.");
	return true;
}

COMMAND:m(playerid, params[]) {
	return cmd_megaphone(playerid, params);
}

COMMAND:suspect(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid, wanted;
	if(IsPlayerCop(playerid)) {
		if(!sscanf(params, "s[24]ds[25]", PartialName[playerid][nume_introdus], wanted, params)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(ISBetween(wanted, 1, 10)) {
					if(!IsPlayerCop(targetid)) {
						if(PlayerInfo[targetid][pWlvl] < 10) {
							if(PlayerInfo[targetid][pWlvl] + wanted < 10) {
								if(PlayerInfo[targetid][pJailed] == 0) {
									if(strlen(params) < 25) {
										if(JucatorulAreMateriale[targetid])
											return SendClientMessage(playerid, COLOR_GRAD1, "This player is already wanted by cops.");
										PlayerInfo[targetid][pWlvl] += wanted;
										SetPlayerWanted(targetid, playerid, PlayerInfo[targetid][pWlvl]);
										format(string, MAXO_TEXT, "UPDATE players SET Wanted = %d WHERE ID = %d", PlayerInfo[targetid][pWlvl], PlayerInfo[targetid][pSQLID]);
										mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
										format(string, MAXO_TEXT, "* You commited a crime: %s, Reported by: %s.", params, PlayerName(playerid));
										SendClientMessage(targetid, COLOR_LIGHTRED, string);
										format(string, MAXO_TEXT, "*** HQ: All units APB: Reporter: %s | Suspect: %s - Crime: %s(+%d) ***", PlayerName(playerid), PlayerName(targetid), params, wanted);
										SendFamilyMessage(COLOR_LIGHTRED, string, FACT_LSPD);
										SendFamilyMessage(COLOR_LIGHTRED, string, FACT_FBI);
										PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
										clear.string(string);
									} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
								} else SendClientMessage(playerid, COLOR_GRAD1, "This player is already jailed.");
							} else format(string, MAXO_TEXT, "This player have already wanted level %d, give him a lower wanted level.", PlayerInfo[targetid][pWlvl]), SendClientMessage(playerid, COLOR_GRAD1, string);
						} else SendClientMessage(playerid, COLOR_GRAD1, "This player have already the maximum wanted level.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You can not suspect a cop.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid wanted.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/suspect [playerid/PartOfName] [wanted level(1-10)] [reason]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG.");
	return true;
}

COMMAND:su(playerid, params[]) {
	return cmd_suspect(playerid, params);
}

COMMAND:jail(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid, time;
	if(IsPlayerCop(playerid)) {
		if(!sscanf(params, "s[24]d", PartialName[playerid][nume_introdus], time)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(PlayerInfo[targetid][pWlvl]) {
					if(GetDistanceBetweenPlayers(playerid, targetid) < 4) {
						if(ISBetween(time, 1, 90)) {
							if(IsPlayerInRangeOfPoint(playerid, 5.0, 1528.8196, -1678.1556, 5.8906) || IsPlayerInRangeOfPoint(playerid, 5.0, -1606.4342, 676.2919, -5.2422)) {
								if(IsPlayerCop(targetid))
									return SendClientMessage(playerid, COLOR_GRAD1, "You cannot to arrest an cop.");
								new
									price = (PlayerInfo[targetid][pWlvl] * 1500);
								SafeGivePlayerMoney(playerid, price);
								ConsumingMoney[playerid] = 1;
								SafeGivePlayerMoney(targetid, -price);
								PlayerInfo[targetid][pJailTime] = time * 60;
								PlayerInfo[targetid][pJailed] = 1;
								PlayerInfo[targetid][pWlvl] = 0;
								format(string, MAXO_TEXT2, "UPDATE players SET Jailed = %d, Wanted = %d WHERE ID = %d", PlayerInfo[targetid][pJailed], PlayerInfo[targetid][pWlvl], PlayerInfo[targetid][pSQLID]);
								mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
								SetPlayerWanted(targetid, playerid, PlayerInfo[targetid][pWlvl]);
								ResetPlayerWeapons(targetid);
								TogglePlayerControllable(targetid, true);
								if(IsPlayerCuffed{targetid})
									SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE),
									IsPlayerCuffed{targetid} = false;
								PutPlayerInCell(targetid);
								format(string, MAXO_TEXT, "* You are jailed for %d minutes. Cop earned: $%s.", time, FormatNumber(price, 0, '.'));
								SendClientMessage(targetid, COLOR_LIGHTRED, string);
								switch(PlayerInfo[playerid][pFactiune]) {
									case FACT_LSPD: format(string, MAXO_TEXT, "<< Officer %s arrested suspect %s for %d minutes. Cop earned: $%s. >>", PlayerName(playerid), PlayerName(targetid), time, FormatNumber(price, 0, '.'));
									case FACT_FBI: format(string, MAXO_TEXT, "<< NG Agent %s arrested suspect %s for %d minutes. Cop earned: $%s. >>", PlayerName(playerid), PlayerName(targetid), time, FormatNumber(price, 0, '.'));
								}
								OOCNews(COLOR_LIGHTRED, string);
								InsertSanctionInPanel(targetid, playerid, ACTION_JAIL, string);
								format(string, sizeof(string), "* The State pays you with $%s for your arrest.", FormatNumber(price, 0, '.'));
								SendClientMessage(playerid, COLOR_ORANGE, string);
								PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
								clear.string(string);
							} else SendClientMessage(playerid, COLOR_GRAD1, "You are not near of the jail, can't arrest this player.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "The time must be between 1-90.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is near you.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "Player must be at least Wanted Level 1.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/jail [playerid/PartOfName] [time(minutes)]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG.");
	return true;
}

COMMAND:wanted(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(IsPlayerCop(playerid)) {
		SendClientMessage(playerid, -1, "|____________ Wanted List ____________|");
		foreach(Player, i) {
			if(PlayerInfo[i][pWlvl] >= 1) {
				if(i != playerid) {
					format(string, MAXO_TEXT, "*** ID: %d | Name: %s | Faction: %s | Wanted Level: %d ***", i, PlayerName(i), FactionInfo[PlayerInfo[i][pFactiune]][fName], PlayerInfo[i][pWlvl]);
					SendClientMessage(playerid, COLOR_ORANGE, string);
					clear.string(string);
				}
			}
			if(i == INVALID_PLAYER_ID)
				return SendClientMessage(playerid, COLOR_GRAD1, "In this moment not is any suspect online.");
		}
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG.");
	return true;
}

COMMAND:showbadge(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(IsPlayerCop(playerid)) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(GetDistanceBetweenPlayers(playerid, targetid) < 4) {
						switch(PlayerInfo[playerid][pFactiune]) {
							case FACT_LSPD:
							{
								SendClientMessage(playerid, -1, "|____________ Police Department Badge ____________|");
								switch(PlayerInfo[playerid][pRank]) {
									case 1: format(string, MAXO_TEXT, "*** %s %s ***", PlayerName(playerid), FactionInfo[FACT_LSPD][fRank1]);
									case 2: format(string, MAXO_TEXT, "*** %s %s ***", PlayerName(playerid), FactionInfo[FACT_LSPD][fRank2]);
									case 3: format(string, MAXO_TEXT, "*** %s %s ***", PlayerName(playerid), FactionInfo[FACT_LSPD][fRank3]);
									case 4: format(string, MAXO_TEXT, "*** %s %s ***", PlayerName(playerid), FactionInfo[FACT_LSPD][fRank4]);
									case 5: format(string, MAXO_TEXT, "*** %s %s ***", PlayerName(playerid), FactionInfo[FACT_LSPD][fRank5]);
									case 6: format(string, MAXO_TEXT, "*** %s %s ***", PlayerName(playerid), FactionInfo[FACT_LSPD][fRank6]);
								}
							}
							case FACT_FBI:
							{
								SendClientMessage(playerid, -1, "|____________ NG Agency Badge ____________|");
								switch(PlayerInfo[playerid][pRank]) {
									case 1: format(string, MAXO_TEXT, "*** %s %s ***", PlayerName(playerid), FactionInfo[FACT_FBI][fRank1]);
									case 2: format(string, MAXO_TEXT, "*** %s %s ***", PlayerName(playerid), FactionInfo[FACT_FBI][fRank2]);
									case 3: format(string, MAXO_TEXT, "*** %s %s ***", PlayerName(playerid), FactionInfo[FACT_FBI][fRank3]);
									case 4: format(string, MAXO_TEXT, "*** %s %s ***", PlayerName(playerid), FactionInfo[FACT_FBI][fRank4]);
									case 5: format(string, MAXO_TEXT, "*** %s %s ***", PlayerName(playerid), FactionInfo[FACT_FBI][fRank5]);
									case 6: format(string, MAXO_TEXT, "*** %s %s ***", PlayerName(playerid), FactionInfo[FACT_FBI][fRank6]);
								}
							}
						}
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is near you.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot show the badge yourself.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/showbadge [playerid/PartOfName]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG.");
	return true;
}

COMMAND:getincar(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid, vID = GetPlayerVehicleID(playerid);
	if(IsPlayerCop(playerid)) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(GetDistanceBetweenPlayers(playerid, targetid) < 4) {
					if(IsPlayerCuffed{targetid}) {
						if(IsVehicleForCop(vID)) {
							if(targetid != playerid) {
								PutPlayerInVehicle(targetid, vID, 1);
								TogglePlayerControllable(targetid, false);
								format(string, MAXO_TEXT, "* %s Cuffs %s, so he wont go anywhere.", PlayerName(playerid), PlayerName(targetid));
								SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
								PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
								clear.string(string);
							} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command on yourself.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in an vehicle for faction PD/NG.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is cuffed, use /cuff first.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is near you.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/getincar [playerid/PartOfName]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG.");
	return true;
}

COMMAND:cuff(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(IsPlayerCop(playerid)) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != playerid) {
				if(!IsPlayerCuffed{targetid}) {
					if(GetDistanceBetweenPlayers(playerid, targetid) < 4) {
						if(!IsPlayerInVehicle(targetid, GetPlayerVehicleID(playerid)) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !IsPlayerInAnyVehicle(targetid)) {
							if(!IsPlayerCop(targetid)) {
								SetPlayerSpecialAction(targetid, SPECIAL_ACTION_CUFFED);
								TogglePlayerControllable(targetid, false);
								IsPlayerCuffed{targetid} = true;
								format(string, MAXO_TEXT, "* You have been cuffed by Cop %s.", PlayerName(playerid));
								SendClientMessage(targetid, COLOR_LIGHTRED, string);
								format(string, MAXO_TEXT, "* You cuffed on %s.", PlayerName(targetid));
								SendClientMessage(playerid, COLOR_LIGHTRED, string);
								GameTextForPlayer(targetid, "~r~Cuffed", 3000, 1);
								format(string, sizeof(string), "* %s Hand Cuffs %s, so he wont go anywhere.", PlayerName(playerid), PlayerName(targetid));
								SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
								PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
								clear.string(string);
							} else SendClientMessage(playerid, COLOR_GRAD1, "This player is cop, so cannot use this command on him.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is in an vehicle or you aren't the driver, so cannot cuff him.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is near you.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "This player is already cuffed.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command on yourself.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/cuff [playerid/PartOfName]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG.");
	return true;
}

COMMAND:uncuff(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(IsPlayerCop(playerid)) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(GetDistanceBetweenPlayers(playerid, targetid) < 4) {
					if(IsPlayerCuffed{targetid}) {
						ClearAnimations(targetid);
						IsPlayerCuffed{targetid} = false;
						TogglePlayerControllable(targetid, true);
						GameTextForPlayer(playerid, "~g~Uncuffed", 3000, 1);
						format(string, MAXO_TEXT, "* You have been uncuffed by Cop %s.", PlayerName(playerid));
						SendClientMessage(targetid, COLOR_LIGHTRED, string);
						format(string, MAXO_TEXT, "* You uncuffed on %s.", PlayerName(targetid));
						SendClientMessage(playerid, COLOR_LIGHTRED, string);
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is cuffed.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is near you.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/uncuff [playerid/PartOfName]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG.");
	return true;
}

COMMAND:frisk(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(IsPlayerCop(playerid)) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(GetDistanceBetweenPlayers(playerid, targetid) < 4) {
						if(!IsPlayerCop(targetid)) {
							if(!IsPlayerInAnyVehicle(playerid)) {
								format(string, MAXO_TEXT, "|____________ %s's items ____________|", PlayerName(targetid));
								SendClientMessage(playerid, -1, string);
								if(PlayerInfo[targetid][pDrugs] != 0) {
									format(string, MAXO_TEXT, "* Drugs: %d grams.", PlayerInfo[targetid][pDrugs]);
									SendClientMessage(playerid, COLOR_GRAD1, string);
								}
								if(PlayerInfo[playerid][pMats] != 0) {
									format(string, MAXO_TEXT, "* Materials: %d.", PlayerInfo[targetid][pMats]);
									SendClientMessage(playerid, COLOR_GRAD1, string);
								}
								if(PlayerInfo[targetid][pPnumber] != 0) SendClientMessage(playerid, COLOR_GRAD1, "* 1 Mobile Phone.");
								if(PlayerInfo[targetid][pPhoneBook] != 0) SendClientMessage(playerid, COLOR_GRAD1, "* 1 Phone book.");
								if(PlayerInfo[targetid][pCigarettes] != 0) {
									format(string, MAXO_TEXT, "* %d Cigarettes.", PlayerInfo[targetid][pCigarettes]);
									SendClientMessage(playerid, COLOR_GRAD1, string);
								}
								if(PlayerInfo[targetid][pLighter] != 0) SendClientMessage(playerid, COLOR_GRAD1, "* 1 Lighter.");
								new weapons[13][2], wname[MAX_GUN_NAME], nrarme = 0;
								for (new i = 1; i <= 12; i ++) {
								    GetPlayerWeaponData(targetid, i, weapons[i][0], weapons[i][1]);
								    if(weapons[i][0] != 0 && weapons[i][1] > 0) {
								    	GetWeaponNameEx(weapons[i][0], wname, MAX_GUN_NAME);
									    format(string, MAXO_TEXT, "%s (%d)", wname, weapons[i][1]);
									    SendClientMessage(playerid, COLOR_GRAD1, string);
									    nrarme ++;
									} 
								}
								if(!nrarme) 
									return SendClientMessage(playerid, COLOR_GRAD1, "No weapons.");
								format(string, MAXO_TEXT, "* You has been frisked by Cop %s for any illegal items.", PlayerName(playerid));
								SendClientMessage(targetid, COLOR_PURPLE, string);
								format(string, MAXO_TEXT, "* %s has frisked %s for any illegal items.", PlayerName(playerid), PlayerName(targetid));
								SendPlayerMessage(30.0, playerid, string, COLOR_PURPLE);
								PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
								clear.string(string);
							} else SendClientMessage(playerid, COLOR_GRAD1, "You must be pedestrian for this action.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command on a cop.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is near you.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command on yourself.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/frisk [playerid/PartOfName]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG.");
	return true;
}

COMMAND:take(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid, vID;
	if(IsPlayerCop(playerid)) {
		if(!sscanf(params, "s[24]s[15]", PartialName[playerid][nume_introdus], params)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(GetDistanceBetweenPlayers(playerid, targetid) < 4) {
					if(targetid != playerid) {
						if(!IsPlayerCop(targetid)) {
							if(!strcmp(params, "drugs", true)) {
								PlayerInfo[targetid][pDrugs] = 0;
								format(string, MAXO_TEXT, "* You have taken away %s's drugs.", PlayerName(targetid));
								SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
								format(string, MAXO_TEXT, "* Officer %s has taken away your drugs.", PlayerName(playerid));
								SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
								format(string, MAXO_TEXT, "UPDATE players SET Drugs = %d WHERE ID = %d", PlayerInfo[targetid][pDrugs], PlayerInfo[targetid][pSQLID]);
								mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							}
							else if(!strcmp(params, "materials", true)) {
								PlayerInfo[targetid][pMats] = 0;
								format(string, MAXO_TEXT, "* You have taken away %s's materials.", PlayerName(targetid));
								SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
								format(string, MAXO_TEXT, "* Officer %s has taken away your materials.", PlayerName(playerid));
								SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
								format(string, MAXO_TEXT, "UPDATE players SET Materials = %d WHERE ID = %d", PlayerInfo[targetid][pMats], PlayerInfo[targetid][pSQLID]);
								mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							}
							else if(!strcmp(params, "weapons", true)) {
								ResetPlayerWeapons(targetid);
								format(string, MAXO_TEXT, "* You have taken away %s's weapons.", PlayerName(targetid));
								SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
								format(string, MAXO_TEXT, "* Officer %s has taken away your weapons.", PlayerName(playerid));
								SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
							}
							else if(!strcmp(params, "tun", true)) {
								vID = GetPlayerVehicleID(targetid);
								if(vID != INVALID_VEHICLE_ID && GetPlayerState(targetid) == PLAYER_STATE_DRIVER) {
									if(GetVehicleComponentInSlot(vID, CARMODTYPE_NITRO)) {
										RemoveVehicleComponent(vID, 1008);
										RemoveVehicleComponent(vID, 1009);
										RemoveVehicleComponent(vID, 1010);
									}
									if(GetVehicleComponentInSlot(vID, CARMODTYPE_HYDRAULICS))
										RemoveVehicleComponent(vID, 1087);
									format(string, MAXO_TEXT, "* Cop %s suspended nitro/hidraulics from your vehicle.", PlayerName(playerid));
									SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
									format(string, MAXO_TEXT, "* You had suspended nitro/hidraulics from %s'Vehicle.", PlayerName(targetid));
									SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
								} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is in vehicle or not is driver.");
							}
							else if(!strcmp(params, "drivinglicense", true)) {
								if(PlayerInfo[targetid][pDrivingLicense] >= gLocalTimeStamp) {
									if(PlayerInfo[playerid][pFactiune] == FACT_LSPD) {
										if(GetDistanceBetweenPlayers(playerid, targetid) < 4.0) {
											PlayerInfo[targetid][pDrivingLicense] = 0;
											format(string, MAXO_TEXT, "UPDATE players SET DrivingLicense = %d WHERE ID = %d", PlayerInfo[targetid][pDrivingLicense], PlayerInfo[targetid][pSQLID]);
											mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
											format(string, MAXO_TEXT, "* Cop %s has took your driving license.", PlayerName(playerid));
											SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
											format(string, MAXO_TEXT, "* You took the driving license from %s.", PlayerName(targetid));
											SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
										} else SendClientMessage(playerid, COLOR_GRAD1, "This player is too far away from you.");
									} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have access at this command.");
								} else SendClientMessage(playerid, COLOR_GRAD1, "This player not have driving license validate.");
							}
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
							clear.string(string);
						} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command on a cop.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command on yourself.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is near you.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/take [playerid/PartOfName] [option]"), SendClientMessage(playerid, COLOR_GRAD1, "Options available: drugs | materials | weapons | tun | drivinglicense");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG.");
	return true;
}

COMMAND:ticket(playerid, params[]) {
	new
		string[MAXO_TEXT2], targetid, price;
	if(IsPlayerCop(playerid)) {
		if(!sscanf(params, "s[24]ds[64]", PartialName[playerid][nume_introdus], price, params)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(GetDistanceBetweenPlayers(playerid, targetid) < 4) {
						if(ISBetween(price, 1, 10000)) {
							if(strlen(params) < 64) {
								if(PlayerInfo[targetid][pCash] >= price) {
									TicketOffer[targetid] = playerid;
									TicketMoney[targetid] = price;
									format(string, MAXO_TEXT, "* You offerd %s a ticket in value of $%s, reason: %s.", PlayerName(targetid), FormatNumber(price, 0, '.'), params);
									SendClientMessage(playerid, COLOR_FAMILY, string);
									format(string, MAXO_TEXT2, "* The cop %s wants to offerd you a ticket in values of $%s, reason: %s. Type /accept %d ticket", PlayerName(playerid), FormatNumber(price, 0, '.'), params, playerid);
									SendClientMessage(targetid, COLOR_FAMILY, string);
									PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
									clear.string(string);
								} else SendClientMessage(playerid, COLOR_GRAD1, "This player not have this amount.");
							} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "The price is between $1-$10.000.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is near you.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command on yourself.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/ticket [playerid/PartOfName] [price] [reason]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG.");
	return true;
}

COMMAND:government(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(IsPlayerCop(playerid)) {
		if(!sscanf(params, "s[75]", params)) {
			if(strlen(params) < 75) {
				if(PlayerInfo[playerid][pRank] > 4) {
					if(PlayerInfo[playerid][pMute])
						return IsPlayerSilent();
					if(PlayerInfo[playerid][pRank] == 5) format(string, MAXO_TEXT, "** %s %s: %s )) **", FactionInfo[PlayerInfo[playerid][pFactiune]][fRank5], PlayerName(playerid), params);
					else if(PlayerInfo[playerid][pRank] == 6) format(string, MAXO_TEXT, "** %s %s: %s )) **", FactionInfo[PlayerInfo[playerid][pFactiune]][fRank6], PlayerName(playerid), params);
					OOCNews(-1, "|____________ Government News Announcement ____________|");
					OOCNews(0x2641FEAA, string);
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "You need of Rank 5+ to use this command.");
			} else SendClientMessage(playerid, COLOR_YELLOW, "[Anti-Spam] {FFFFFF}Line too long.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/gov(ernemnt) [message]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG.");
	return true;
}

COMMAND:gov(playerid, params[]) {
	return cmd_government(playerid, params);
}

COMMAND:unjail(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(IsPlayerCop(playerid)) {
		if(!sscanf(params, "s[24]s[64]", PartialName[playerid][nume_introdus], params)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(PlayerInfo[targetid][pJailTime] || PlayerInfo[targetid][pJailed]) {
					if(strlen(params) < 64) {
						if(PlayerInfo[playerid][pRank] > 4) {
							PlayerInfo[targetid][pJailed] = 0;
							PlayerInfo[targetid][pJailTime] = 0;
							SafeSetPlayerInterior(targetid, 0);
							SafeSetPlayerVirtualWorld(targetid, 0);
							TogglePlayerControllable(targetid, true);
							SafeSetPlayerPos(targetid, 1541.7213, -1676.3795, 13.5531);
							SetPlayerWorldBounds(targetid, 20000.0000, -20000.0000, 20000.0000, -20000.0000);
							format(string, MAXO_TEXT2, "UPDATE players SET Jailed = %d, JailTime = %d WHERE ID = %d", PlayerInfo[targetid][pJailed], PlayerInfo[targetid][pJailTime], PlayerInfo[targetid][pSQLID]);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "* %s was relased from jail by %s.", PlayerName(targetid), PlayerName(playerid));
							OOCNews(COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
							clear.string(string);
						} else SendClientMessage(playerid, COLOR_GRAD1, "You need Rank 5+ to use this command.");
					} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "This player isnt't in jail.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/unjail [playerid/PartOfName] [reason]");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You are not member PD/NG.");
	return true;
}

COMMAND:door(playerid, params []) {
    if((IsPlayerCop(playerid))) {
    	if(IsPlayerInRangeOfPoint(playerid, 5.0, 245.0578, 72.4314, 1002.5406)) {
      		MoveObject(door, 244.0578,72.4314,1002.5406, 3.5000);
      		MoveObject(door2, 247.1478,72.4314,1002.5406, 3.5000);
            SetTimer("outdoor", 5000, false);
		} else SendClientMessage(playerid, COLOR_GRAD1,"You are not in Police Station!");
	} else SendClientMessage(playerid, COLOR_GRAD1,"You are not member in LSPD/NG to use this command !");
	return true;
}

COMMAND:getfuel(playerid, params[]) {
	new idbiz = GetBizSQLID(playerid, 3.0);
	if(IsPlayerInRangeOfPoint(playerid, 3.0, BizInfo[idbiz][bEntrancex], BizInfo[idbiz][bEntrancey], BizInfo[idbiz][bEntrancez]) && BizInfo[idbiz][bType] == BIZ_TYPE_BENZINARIE) {
		if(HaveGasCan{playerid}) {
			if(HaveGasInCan[playerid] < 1) {
				HaveGasInCan[playerid] = 100;
				new price = (100*5);
				SafeGivePlayerMoney(playerid, -price);
				SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You took 100 liters of fuel in your Canister at price of $500, use /fillveh to use it.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You have already Gas in your Canister.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have a Gas Canister to take fuel from Gas Station.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You must be at Gas Station to take fuel in Canister.");
	return true;
}

COMMAND:fillveh(playerid, params[]) {
	new vID = GetPlayerVehicleID(playerid);
	new engine, lights, alarm, doors, bonnet, boot, objective;
	if(HaveGasCan{playerid}) {
		if(vID) {
			if(!IsVehicleBike(vID) || !IsVehicleBoat(vID) || !IsVehiclePlane(vID)) {
				if(Gas[vID] < 81) {
					GetVehicleParamsEx(vID, engine, lights, alarm, doors, bonnet, boot, objective);
					if(engine == VEHICLE_PARAMS_ON)
						return SendClientMessage(playerid, COLOR_GRAD1, "You must to stop the engine before to refill it.");
					if(HaveGasInCan[playerid] < 1)
						return SendClientMessage(playerid, COLOR_GRAD1, "You haven't enough fuel in canister to refill the vehicle.");
					Gas[vID] += 20;
					HaveGasInCan[playerid] -= 20;
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "You filled your car with 20 percent Fuel from your Gas Canister.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "Your vehicle have enough fuel to drive it.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "This type of vehicle can't be refilled.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in a vehicle to use this command.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You haven't a canister to refill this vehicle.");
	return true;
}

// End Of File ...
