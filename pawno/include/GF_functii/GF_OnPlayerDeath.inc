/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_OnPlayerDeath_included
	#endinput
#else
	#define GF_OnPlayerDeath_included
#endif

public OnPlayerDeath(playerid, killerid, reason) {
	ResetCheckpoints(playerid);
	if(JucatorulAreMateriale[playerid] > 0) {
		JucatorulAreMateriale[playerid] = 0;
		SendClientMessage(playerid, COLOR_LIGHTRED, "Because you're dead, you lost the materials package.");
	}
	if(JucatorulAreDroguri[playerid] > 0) {
		SendClientMessage(playerid, COLOR_LIGHTRED, "Because you're dead, you lost the drugs package.");
		JucatorulAreDroguri[playerid] = 0;
	}
	if(TakingLesson{playerid}) { IsPlayerDeadInExam(playerid); }
	if(IsCopDuty{playerid}) { IsCopDuty{playerid} = false; }
	new string[MAXO_TEXT], vID = GetPlayerVehicleID(playerid);
	if(IsPlayerNPC(killerid)) return 1;
	if(IsCopUndercover{playerid})
		SetPlayerFactionColor(playerid, PlayerInfo[playerid][pFactiune]), SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]), IsCopUndercover{playerid} = false;
	if(Spectated[playerid][Type] != ADMIN_SPEC_TYPE_NONE)
		SpecStopSpec(playerid),
		SendClientMessage(playerid, COLOR_WHITE, "Your target was killed, type again /spec");
	// daca criminalul si victima nu sunt in jail, atunci se va executa urmatorul script code
	if(PlayerInfo[playerid][pJailed] == 0 && PlayerInfo[killerid][pJailed] == 0) {
		PlayerInfo[killerid][pKills] ++;
		PlayerInfo[playerid][pDeaths] ++;
		if(!IsPlayerCop(killerid)) {
			PlayerInfo[killerid][pWlvl] += 1;
			SetPlayerWanted(killerid, playerid, PlayerInfo[killerid][pWlvl]);
			format(string, MAXO_TEXT, "UPDATE players SET Wanted = %d WHERE ID = %d", PlayerInfo[killerid][pWlvl], PlayerInfo[killerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		}
		format(string, MAXO_TEXT, "UPDATE players SET Kills = %d WHERE ID = %d", PlayerInfo[killerid][pKills], PlayerInfo[killerid][pSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		format(string, MAXO_TEXT, "UPDATE players SET Deaths = %d WHERE ID = %d", PlayerInfo[playerid][pDeaths], PlayerInfo[playerid][pSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		if(PlayerInfo[killerid][pWlvl] > 9) {
			ResetPlayerWeapons(killerid);
			PutPlayerInCell(killerid);
			PlayerInfo[killerid][pJailTime] = 3000;
			PlayerInfo[killerid][pJailed] = 1;
			PlayerInfo[killerid][pWlvl] = 0;
			SetPlayerWanted(killerid, playerid, 0);
			format(string, MAXO_TEXT, "-AUTO JAIL- << Player %s has been jailed for killing with Wanted 10 >>", PlayerName(killerid));
			OOCNews(COLOR_RED, string);
			format(string, MAXO_TEXT2, "UPDATE players SET Wanted = 0, JailTime = 3000, Jailed = 1 WHERE ID = %d", PlayerInfo[killerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		}
	}
	// daca criminalul si victima sunt in jail, atunci folosim urmatorul script
	else
	{
		if(PlayerInfo[killerid][pJailed] != 0) {
			PlayerInfo[killerid][pJailTime] += 30;
			format(string, MAXO_TEXT, "UPDATE players SET JailTime = %d WHERE ID = %d", PlayerInfo[killerid][pJailTime], PlayerInfo[killerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			SendClientMessage(killerid, COLOR_RED, "GUARD: Because you are aggressive in jail, you received +30 seconds in plus at your punish.");
		}
	}
	if(reason == 38) {
		if(IsPlayerConnected(killerid)) {
			format(string, MAXO_TEXT, "[CHEAT]: %s was been killed by [%d]%s with minigun, /spec(tate) on him.", PlayerName(playerid), killerid, PlayerName(killerid));
			ABroadCast(COLOR_YELLOW, string, 1);
		}
	}
	if(killerid != INVALID_PLAYER_ID) {
		format(string, MAXO_TEXT, "[killed] You got killed by %s.", PlayerName(killerid));
		SendClientMessage(playerid, COLOR_RED, string);
		if(!IsPlayerCop(killerid))
			format(string, MAXO_TEXT, "[Crime] You killed %s.", PlayerName(playerid)),
			SendClientMessage(killerid, COLOR_RED, string);

	}
	//================================%<======================
	// -- copyrighted
	new
		factvictima = PlayerInfo[playerid][pFactiune],
		factkiller  = PlayerInfo[killerid][pFactiune],
		zonavictima = GetPlayerTurfID(playerid),
		zonakiller  = GetPlayerTurfID(killerid);
	if(IsAWarArea(zonavictima)) {
		if(zonavictima != INVALID_TURF_ID) {
			if(TeamInfo[factvictima][InWar] && TeamInfo[factkiller][InWar]) {
				if(zonavictima == zonakiller) {
					if(TurfInfo[zonavictima][TurfWarStarted]) {
						if(factvictima == factkiller) {
							TeamInfo[factkiller][TeamScore] --;
						}
						else
						{
							if(TurfInfo[zonavictima][TurfOwner] == factvictima || TurfInfo[zonavictima][TurfOwner] == factkiller) {
								if(!GetPlayerVehicleID(killerid)) {
									TeamInfo[factkiller][TeamScore] ++;
									SafeGivePlayerMoney(killerid, RivalWarsKMoney);
									ConsumingMoney[killerid] = 1;
									format(string, MAX_PLAYER_NAME, "~g~+$~y~%s", FormatNumber(RivalWarsKMoney, 0, '.'));
									GameTextForPlayer(killerid, string, 3000, 1);
								}
							}
						}
						foreach(Player, i) {
							if(PlayerInfo[i][pFactiune] == factkiller) {
								format(string, MAXO_TEXT, "~y~Turf Name: ~r~%s~n~~y~Faction Score: ~r~%d~n~~y~Time Left: ~r~%s",
								TurfInfo[zonavictima][TurfName], TeamInfo[factkiller][TeamScore], ConvertTime(TurfInfo[zonavictima][TurfWarStarted]));
								ShowPlayerInformation(i, "Rival-War Statistics", string);
							}
							else if(PlayerInfo[i][pFactiune] == factvictima) {
								format(string, MAXO_TEXT, "~y~Turf Name: ~r~%s~n~~y~Faction Score: ~r~%d~n~~y~Time Left: ~r~%s",
								TurfInfo[zonavictima][TurfName], TeamInfo[factvictima][TeamScore], ConvertTime(TurfInfo[zonavictima][TurfWarStarted]));
								ShowPlayerInformation(i, "Rival-War Statistics", string);
							}
						}
					}
				}
			}
		}
	}
	//================================>%======================
    if(PlayerInfo[playerid][pHeadValue] != 0) {
	    if(killerid != INVALID_PLAYER_ID) {
		    if(PlayerInfo[killerid][pFactiune] == FACT_HITMAN) {
		        if(GoChase[killerid] == playerid) {
					SafeGivePlayerMoney(killerid, PlayerInfo[playerid][pHeadValue]);
					ConsumingMoney[killerid] = 1;
					format(string, MAXO_TEXT, "<< Agent %s has fulfilled the contract on %s and collected $%s. >>", PlayerName(killerid), PlayerName(playerid), FormatNumber(PlayerInfo[playerid][pHeadValue], 0, '.'));
					SendFamilyMessage(COLOR_ORANGE, string, FACT_HITMAN);
					PlayerInfo[playerid][pHeadValue] = 0;
					format(string, MAXO_TEXT, "UPDATE players SET HeadValue = %d WHERE ID = %d", PlayerInfo[playerid][pHeadValue], PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					PlayerInfo[killerid][pContracts] ++;
					format(string, MAXO_TEXT, "UPDATE players SET Contracts = %d WHERE ID = %d", PlayerInfo[killerid][pContracts], PlayerInfo[killerid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					GotHit[playerid] = 0;
					GetChased[playerid] = 999;
					GoChase[killerid] = 999;
				}
			}
		}
 	}
	if(IsPlayerInArea(killerid, -2081.805, -139.7016, -1904.122, 341.584) || IsPlayerInArea(killerid, 1200.85, -1433.15, 1295.92, -1271.3)) {
		if(PlayerInfo[killerid][pFactiune] > FACT_FBI) {
			SafeSetPlayerVirtualWorld(killerid, LSPD_VW);
			PutPlayerInCell(killerid);
			PlayerInfo[killerid][pJailTime] = 3600;
			PlayerInfo[killerid][pJailed] = 1;
			PlayerInfo[killerid][pWlvl] = 0;
			SetPlayerWanted(killerid, playerid, 0);
			ResetPlayerWeapons(killerid);
			format(string, MAXO_TEXT, "» Player %s has been jailed for killing in the NO DM Zone. «", PlayerName(killerid));
			OOCNews(COLOR_RED, string);
		}
		format(string, MAXO_TEXT2, "UPDATE players SET JailTime = %d, Jailed = %d, Wanted = %d WHERE ID = %d", PlayerInfo[killerid][pJailTime], PlayerInfo[killerid][pJailed], PlayerInfo[killerid][pWlvl]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	}
	if(PlayerInfo[playerid][pWlvl] >= 1) {
		if(TeamInfo[PlayerInfo[playerid][pFactiune]][InWar] == 0) {
			new price = (PlayerInfo[playerid][pWlvl] * 600);
			for(new cop = 0; cop < MAX_PLAYERS; cop ++) {
				if(IsPlayerCop(cop) && GetDistanceBetweenPlayers(playerid, cop) < 30.0 && !Spectated[cop][Status]) {
					format(string, MAXO_TEXT, "~w~Running Suspect ~r~Killed ~n~~w~Bonus: ~g~+~y~%s", FormatNumber(price, 0, '.'));
					GameTextForPlayer(cop, string, 5000, 1);
					SafeGivePlayerMoney(cop, price);
					ConsumingMoney[cop] = 1;
					PlayerPlaySound(cop, 1058, 0.0, 0.0, 0.0);
					SafeGivePlayerMoney(playerid, -price);
					ResetPlayerWeapons(playerid);
					PutPlayerInCell(playerid);
					PlayerInfo[playerid][pJailTime] = (PlayerInfo[playerid][pWlvl]*180);
					PlayerInfo[playerid][pJailed] = 1;
					PlayerInfo[playerid][pWlvl] = 0;
					SetPlayerWanted(playerid, cop, 0);
					format(string, MAXO_TEXT, ">> You are in jail for %s. You has lost -$%s cash. <<", ConvertTime(PlayerInfo[playerid][pJailTime]), FormatNumber(price, 0, '.'));
					SendClientMessage(playerid, COLOR_LIGHTRED, string);
					format(string, MAXO_TEXT2, "UPDATE players SET JailTime = %d, Jailed = %d, Wanted = %d WHERE ID = %d", PlayerInfo[playerid][pJailTime], PlayerInfo[playerid][pJailed], PlayerInfo[playerid][pWlvl], PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				}
			}
		}
	}
	if (vID != INVALID_VEHICLE_ID) {
		if(IsAJOBVehicle(vID)) {
			ExitJOBVehicle(playerid, vID);
		}
		SetVehicleToRespawn(GetVehicleTrailer(vID));
	}
	new caller = Mobile[playerid];
	if(caller != 255) {
		if(caller < 255) {
			SendClientMessage(caller, COLOR_GRAD1, "The line just went dead....");
			CellTime[caller] = 0;
			CellTime[playerid] = 0;
			Mobile[caller] = 255;
		}
		Mobile[playerid] = 255;
		CellTime[playerid] = 0;
	}
	killerid = INVALID_PLAYER_ID;
	clear.string(string);
	return 1;
}

// End Of File ...
