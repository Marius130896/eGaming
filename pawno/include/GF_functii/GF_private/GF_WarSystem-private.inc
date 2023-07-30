/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/

#if defined GF_WarSystemPriv_included
	#endinput
#else
	#define GF_WarSystemPriv_included
#endif

stock StartRivalWarsBetweenPlayers(turfid, AtackTeam, DefendTeam) {
	if(turfid != INVALID_TURF_ID) {
		TurfInfo[turfid][TurfAttacker] = AtackTeam;
		TurfInfo[turfid][TurfWarStarted] = DURATA_RIVALWAR;
		TeamInfo[AtackTeam][LastAttack] = gLocalTimeStamp + PAUSE_FOR_LAST_ATTACK;
		TeamInfo[AtackTeam][InWar] = 1;
		TeamInfo[DefendTeam][InWar] = 1;
		TeamInfo[AtackTeam][TeamScore] = 0;
		TeamInfo[DefendTeam][TeamScore] = 0;
		TeamInfo[AtackTeam][StartWarTime] = gLocalTimeStamp;
		foreach(Player, i) {
			new string[MAXO_TEXT];
			if(PlayerInfo[i][pFactiune] == AtackTeam) {
				format(string, MAXO_TEXT2, "* Rival-Wars: We have provoked a rival-war in %s Turf. against the %s. *", TurfInfo[turfid][TurfName], FactionInfo[DefendTeam][fName]);
				SendClientMessage(i, COLOR_WHITE, string);
				if(showTurfs{i})
					GangZoneFlashForPlayer(i, TurfInfo[turfid][TurfSQLID], COLOR_FLASHTURF);
				PlayerAtRivalWar[i] = PLAYER_IN_TURF;
				SetPlayerMarkerForPlayer(AtackTeam, DefendTeam, GetPlayerColor(i));
			}
			else if(PlayerInfo[i][pFactiune] == DefendTeam) {
				format(string, MAXO_TEXT2, "* Rival-Wars: The %s have provoked a war for %s Turf. *", FactionInfo[AtackTeam][fName], TurfInfo[turfid][TurfName]);
				SendClientMessage(i, COLOR_WHITE, string);
				if(showTurfs{i})
					GangZoneFlashForPlayer(i, TurfInfo[turfid][TurfSQLID], COLOR_FLASHTURF);
				PlayerAtRivalWar[i] = PLAYER_IN_TURF;
				SetPlayerMarkerForPlayer(DefendTeam, AtackTeam, GetPlayerColor(i));
			}
			clear.string(string);
		}
	}
	return true;
}


stock GivePlayerAwardForWinRivalWars(AtackTeam, DefendTeam) {
	new string[MAXO_TEXT];
	for(new i = 0; i < MAX_PLAYERS; i ++) {
		if(PlayerInfo[i][pFactiune] == AtackTeam) {
			format(string, MAXO_TEXT, "* Rival-Wars: We won the rival-war against the %s ! *", FactionInfo[DefendTeam][fName]);
			SendClientMessage(i, COLOR_WHITE, string);
			if(!IsPlayerPaused(i)) {
				SafeGivePlayerMoney(i, RivalWarsMoney);
				PlayerInfo[i][pDrugs] += RivalWarsDrugs;
				PlayerInfo[i][pMats] += RivalWarsMaterials;
				format(string, MAXO_TEXT, "* Rival-Wars Award: You received: "VERDE"$"ALB"%s, %d grams drugs and %s materials.", FormatNumber(RivalWarsMoney, 0, ','), RivalWarsDrugs, FormatNumber(RivalWarsMaterials, 0, '.'));
				SendClientMessage(i, COLOR_WHITE, string);
				format(string, MAXO_TEXT2, "UPDATE players SET Drugs = %d, Materials = %d WHERE ID = %d", PlayerInfo[i][pDrugs], PlayerInfo[i][pMats], PlayerInfo[i][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			} else SendClientMessage(i, COLOR_WHITE, "* Rival-Wars Award: Because you were AFK you did not receive the award. *");
		}
		else if(PlayerInfo[i][pFactiune] == DefendTeam) {
			format(string, MAXO_TEXT, "* Rival-Wars: The "ROSU"%s"ALB" have taken over our turf!", FactionInfo[AtackTeam][fName]);
			SendClientMessage(i, COLOR_WHITE, string);
		}
		clear.string(string);
	}
	return true;
}

stock StopRivalWarsBetweenPlayers(turfid, AtackTeam, DefendTeam) {
	if(turfid != INVALID_TURF_ID) {
		if(TurfInfo[turfid][TurfWarStarted] == 0) {
			new string[MAXO_TEXT];
			foreach(new i : Player) {
				if(gPlayerLogged{i}) {
					if(TeamInfo[AtackTeam][TeamScore] > TeamInfo[DefendTeam][TeamScore]) {
						TurfInfo[turfid][TurfAttacker] = MAX_FACTIONS;
						TeamInfo[AtackTeam][InWar] = 0;
						TeamInfo[DefendTeam][InWar] = 0;
						TurfInfo[turfid][TurfOwner] = AtackTeam;
						TurfInfo[turfid][TurfColor] = FactionColor(AtackTeam);
						GivePlayerAwardForWinRivalWars(AtackTeam, DefendTeam);
						format(string, MAXO_TEXT2, "* Rival-Wars: Final score from the rival-war in %s Turf. %s %d - %d %s. *", TurfInfo[turfid][TurfName], FactionInfo[AtackTeam][fName], TeamInfo[AtackTeam][TeamScore], TeamInfo[DefendTeam][TeamScore], FactionInfo[DefendTeam][fName]);
						SendClientMessage(i, COLOR_ORANGE, string);
						TeamInfo[DefendTeam][AttackPause] = gLocalTimeStamp + WAR_PAUSE;
						TurfInfo[turfid][TurfWarPause] = gLocalTimeStamp + TURF_CMD_DELAY;
						format(string, MAXO_TEXT2, "UPDATE turfs_rivalwars SET TurfOwner = %d, TimePaused = %d WHERE SQLID = %d", AtackTeam, TurfInfo[turfid][TurfWarPause], turfid);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", TURFS_THREAD_ID);
						if(showTurfs{i}) {
							GangZoneStopFlashForPlayer(i, TurfInfo[turfid][TurfSQLID]);
							GangZoneShowForPlayer(i, TurfInfo[turfid][TurfSQLID], FactionColor(AtackTeam));
						}
						SetPlayerMarkerForPlayer(TeamInfo[AtackTeam][InWar], TeamInfo[DefendTeam][InWar], 0xFFFFFF00);
					}
					if(TeamInfo[DefendTeam][TeamScore] > TeamInfo[AtackTeam][TeamScore]) {
						TurfInfo[turfid][TurfAttacker] = MAX_FACTIONS;
						TeamInfo[AtackTeam][InWar] = 0;
						TeamInfo[DefendTeam][InWar] = 0;
						TurfInfo[turfid][TurfOwner] = DefendTeam;
						TurfInfo[turfid][TurfColor] = FactionColor(DefendTeam);
						GivePlayerAwardForWinRivalWars(AtackTeam, DefendTeam);
						format(string, MAXO_TEXT2, "* Rival-Wars: Final score from the rival-war in %s Turf. %s %d - %d %s. *", TurfInfo[turfid][TurfName], FactionInfo[AtackTeam][fName], TeamInfo[AtackTeam][TeamScore], TeamInfo[DefendTeam][TeamScore], FactionInfo[DefendTeam][fName]);
						SendClientMessage(i, COLOR_ORANGE, string);
						TeamInfo[DefendTeam][AttackPause] = gLocalTimeStamp + WAR_PAUSE;
						TurfInfo[turfid][TurfWarPause] = gLocalTimeStamp + TURF_CMD_DELAY;
						format(string, MAXO_TEXT2, "UPDATE turfs_rivalwars SET TurfOwner = %d, TimePaused = %d WHERE SQLID = %d", AtackTeam, TurfInfo[turfid][TurfWarPause], turfid);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", TURFS_THREAD_ID);
						if(showTurfs{i}) {
							GangZoneStopFlashForPlayer(i, TurfInfo[turfid][TurfSQLID]);
							GangZoneShowForPlayer(i, TurfInfo[turfid][TurfSQLID], FactionColor(DefendTeam));
						}
						SetPlayerMarkerForPlayer(TeamInfo[DefendTeam][InWar], TeamInfo[AtackTeam][InWar], 0xFFFFFF00);
					}
					else if(TeamInfo[AtackTeam][TeamScore] == TeamInfo[DefendTeam][TeamScore]) {
						TurfInfo[turfid][TurfWarStarted] = DURATA_WAR_SCORE_EGAL;
						if(PlayerInfo[i][pFactiune] == AtackTeam || PlayerInfo[i][pFactiune] == DefendTeam) {
							format(string, MAXO_TEXT2, "* Rival-Wars: The score is equal, the war was extended by another %s minutes! *", ConvertTime(TurfInfo[turfid][TurfWarStarted]));
							SendClientMessage(i, COLOR_WHITE, string);
						}
					}
				}
				HidePlayerInformation(i);
				PlayerAtRivalWar[i] = 0;
				clear.string(string);
			}
		}
		TeamInfo[AtackTeam][TeamScore] = 0;
		TeamInfo[DefendTeam][TeamScore] = 0;
	}
	return true;
}

COMMAND:rivalwar(playerid, params[]) {
	if(IsPlayerGangster(playerid)) {
		new MyTurf = GetPlayerTurfID(playerid);
		if(PlayerInfo[playerid][pRank] > 4) {
			if(IsAWarArea(MyTurf)) {
				new MyFaction = PlayerInfo[playerid][pFactiune];
				if(RivalFactions(playerid)) {
					if(!TurfInfo[MyTurf][TurfWarStarted]) {
						new string[MAXO_TEXT];
						if(gettime() > TurfInfo[MyTurf][TurfWarPause]) {
							new TurfFaction = TurfInfo[MyTurf][TurfOwner];
							if(gettime() > TeamInfo[TurfFaction][AttackPause]) {
								if(TurfFaction != MyFaction) {
									if(TeamInfo[MyFaction][InWar] == 0 && TeamInfo[TurfFaction][InWar] == 0) {
										StartRivalWarsBetweenPlayers(MyTurf, MyFaction, TurfFaction);
									} else SendClientMessage(playerid, COLOR_GRAD1, "You can't start two wars in the same time.");
								} else SendClientMessage(playerid, COLOR_GRAD1, "You can't attack your own territory.");
							} else format(string, MAXO_TEXT, "This faction can be attacked in date of %s.", DateToTimestamp(TeamInfo[TurfFaction][AttackPause])), SendClientMessage(playerid, COLOR_GRAD1, string);
						} else format(string, MAXO_TEXT, "This turf can be attacked in date of %s.", DateToTimestamp(TurfInfo[MyTurf][TurfWarPause])), SendClientMessage(playerid, COLOR_GRAD1, string);
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "This turf is already in war.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "This turf is not a rival, you can't to start an war.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You're not on a turf of war.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You're not member Rank 5+ in your faction.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You're not a faction of Death-Match.");
	return true;
}

// End Of File ...
