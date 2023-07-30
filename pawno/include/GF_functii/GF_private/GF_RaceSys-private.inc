/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/

#if defined GF_RaceSys_included
	#endinput
#else
	#define GF_RaceSys_included
#endif

#define ROSSO		 		0xFF3233FF
#define TURCHESE              0x3C93FFFF

#define DIALOGGARE            	8016
#define DIALOGINFO            	8017
#define DIALOGINFOBuilder 		8018
#define DIALOGNOMEGARA        	8019
#define DIALOGLapsGARA        	8020
#define DIALOGCostsGARA       	8021
#define DIALOGINFOGARA2       	8022
#define DIALOGINSEGUIMENTO    	8023
#define DIALOGID_RACE_AIRTYPE   8024	
#define DIALOGID_RACE_VOTE 		8024	

new Iterator:CurseFMA<MAX_RACES>;
new RaceTimpVechi;
new AllLoadedRaces = 0;
new Float:XPosizione,Float:YPosizione,Float:ZPosizione;
new Text:txtSemaf = Text:INVALID_TEXT_DRAW;

stock FMAhasAccess(playerid) {
	switch(PlayerInfo[playerid][pFactiune]) {
		case FACT_CIVIL, FACT_MEDIC..FACT_FMA: { 
			return true; 
		}
	}
	return false;
}

stock ColisionInfo(playerid) {
	if(RaceVoteColision[FinalVote] == COLISION_DISABLED) {
		RacePL[playerid][Colision] = COLISION_DISABLED;
		DisableRemoteVehicleCollisions(playerid, RacePL[playerid][Colision]);
		SendClientMessage(playerid, COLOR_WHITE, "[{A60099}FMARace{FFFFFF}] Collisions are disabled for this race. (Voted by racers).");
	}
	return true;
}	

stock StartRace(playerid, idRace) {
	Race[idRace][Started] = 1;
	new string[MAXO_TEXT];
	if(RacePL[playerid][IdRace] == idRace) {
		TogglePlayerControllable(playerid,0);
		if(Race[idRace][Chase]) {
			format(string, sizeof(string), "Points: ~b~%d ~w~Status: ~h~~y~Neutral~w~", RacePL[playerid][Points]);
			ShowPlayerInformation(playerid, "Race Statistics", string);
		}
		SetTimerEx("StartCount",1000,false,"dd",playerid, 0);
		ColisionInfo(playerid);
	}
	return true;
}

function StartCount(playerid, counter) {
	counter++;
	switch (counter) {
		case 1: {
			TextDrawSetString(txtSemaf, "LD_ROUL:roulred");
			if(RacePL[playerid][IdRace] == IDCursa && RacePL[playerid][RReady]) {
				TextDrawShowForPlayer(playerid,txtSemaf);
				PlayerPlaySound(playerid,1056, 0.0, 0.0, 0.0);
				RacePL[playerid][TimeRC]=0;
				RacePL[playerid][Position] = 0;
				RacePL[playerid][RLap]=1;
				GetPlayerPos(playerid,XPosizione,YPosizione,ZPosizione);
				SetPlayerCameraPos(playerid,XPosizione+4,YPosizione+2,ZPosizione+3);
				SetPlayerCameraLookAt(playerid,XPosizione,YPosizione,ZPosizione);
			}
			SetTimerEx("StartCount",1000,false,"dd",playerid,counter);
		}
		case 2: {
			TextDrawSetString(txtSemaf, "LD_ROUL:roulbla");
			if(RacePL[playerid][IdRace] == IDCursa && RacePL[playerid][RReady]) {
				PlayerPlaySound(playerid,1056, 0.0, 0.0, 0.0);
				GetPlayerPos(playerid,XPosizione,YPosizione,ZPosizione);
				SetPlayerCameraPos(playerid,XPosizione-4,YPosizione-2,ZPosizione+3);
				SetPlayerCameraLookAt(playerid,XPosizione,YPosizione,ZPosizione);
			}
			SetTimerEx("StartCount",1000,false,"dd",playerid, counter);
		}
		case 3: {
			TextDrawSetString(txtSemaf, "LD_ROUL:roulgre");
			if(RacePL[playerid][IdRace] == IDCursa && RacePL[playerid][RReady]) {
				PlayerPlaySound(playerid,1056, 0.0, 0.0, 0.0);
				GetPlayerPos(playerid,XPosizione,YPosizione,ZPosizione);
				SetPlayerCameraPos(playerid,XPosizione+4,YPosizione-2,ZPosizione+3);
				SetPlayerCameraLookAt(playerid,XPosizione,YPosizione,ZPosizione);
			}
			SetTimerEx("StartCount",1000,false,"dd",playerid, counter);
		}
		case 4: {
			if(RacePL[playerid][IdRace] == IDCursa && RacePL[playerid][RReady]) {
				TextDrawHideForPlayer(playerid,txtSemaf);
				SetCameraBehindPlayer(playerid);
				GameTextForPlayer(playerid,"~w~Go!",3000,3);
				PlayerPlaySound(playerid,1057, 0.0, 0.0, 0.0);
				TogglePlayerControllable(playerid,1);
				#if defined _stream_checkpoints
				if(IsPlayerInDynamicRaceCP(playerid, checkpointFMARace[playerid]))
					OnPlayerEnterDynamicRaceCP(playerid, checkpointFMARace[playerid]);
				#else
				if(CPid[playerid] == CP_FMA_RACE && IsPlayerInRaceCheckpoint(playerid))
					OnPlayerEnterRaceCheckpoint(playerid);
				#endif
				RaceTimerZ(playerid);
			}
		}
	}
	return true;
}

function UpdateRaceInfo(playerid) {
	new
		Minuti = floatround(RacePL[playerid][TimeRC]/60),
		Secondi = RacePL[playerid][TimeRC]-(Minuti*60),
		stringinfo[MAXO_TEXT2];
	format(stringinfo, sizeof(stringinfo), "~y~Race Name: ~b~%s~n~~n~ ~y~Position ~g~%d~r~%s~n~~n~ ~y~Laps ~g~%d ~y~of ~r~%d~n~ ~y~Checkpoint ~g~%d ~y~of ~r~%d~n~ ~y~Cronometer ~g~%02d:%02d",
		 Race[IDCursa][Nome], GetPlayerPosition(playerid), returnOrdinal(GetPlayerPosition(playerid)), RacePL[playerid][RLap], Race[IDCursa][Laps], RacePL[playerid][Checkpoint], Race[IDCursa][CheckpointNr], Minuti, Secondi);
	ShowPlayerInformation(playerid, "Race Statistics", stringinfo);
	return true;
}

function RaceTimerZ(playerid) {
	if(IDCursa != INVALID_RACE_ID) {
		if(RacePL[playerid][IdRace] == IDCursa) {
			RacePL[playerid][TimeRC]++;
			if(Race[IDCursa][Chase]) {
				foreach(Player, x) {
					if(RacePL[x][IdRace]==RacePL[x][IdRace] && x!=playerid) {
						GetPlayerPos(x,XPosizione,YPosizione,ZPosizione);
						break;
					}
				}
				new string[MAXO_TEXT];
				if(!RacePL[playerid][Pursuer]) {
					if(IsPlayerInRangeOfPoint(playerid,15.0,XPosizione,YPosizione,ZPosizione)) {
						RacePL[playerid][Points]+=3; 
						format(string, sizeof(string), "Points: ~b~%d ~w~Status: ~r~Bad~w~", RacePL[playerid][Points]);
					}
					else if (IsPlayerInRangeOfPoint(playerid,30.0,XPosizione,YPosizione,ZPosizione)) {
						RacePL[playerid][Points]+=5;
						format(string, sizeof(string), "Points: ~b~%d ~w~Status: ~h~~r~Average~w~", RacePL[playerid][Points]);
					}
					else if(IsPlayerInRangeOfPoint(playerid,40.0,XPosizione,YPosizione,ZPosizione)) {
						RacePL[playerid][Points]+=7; 
						format(string, sizeof(string), "Points: ~b~%d ~w~Status: ~y~Good~w~", RacePL[playerid][Points]);
					}
					else
					{
						RacePL[playerid][Points]+=8; 
						format(string, sizeof(string), "Points: ~b~%d ~w~Status: ~h~~b~Excellent~w~", RacePL[playerid][Points]);
					}
					
				}
				else
				{
					if(IsPlayerInRangeOfPoint(playerid,15.0,XPosizione,YPosizione,ZPosizione)) {
						RacePL[playerid][Points]+=8; 
						format(string, sizeof(string), "Points: ~b~%d ~w~Status: ~h~~b~Excellent~w~", RacePL[playerid][Points]);
					}
					else if (IsPlayerInRangeOfPoint(playerid,30.0,XPosizione,YPosizione,ZPosizione)) {
						RacePL[playerid][Points]+=7; 
						format(string, sizeof(string), "Points: ~b~%d ~w~Status: ~y~Good~w~", RacePL[playerid][Points]);
					}
					else if(IsPlayerInRangeOfPoint(playerid,40.0,XPosizione,YPosizione,ZPosizione)) {
						RacePL[playerid][Points]+=5; 
						format(string, sizeof(string), "Points: ~b~%d ~w~Status: ~h~~r~Average~w~", RacePL[playerid][Points]);
					}
					else
					{
						RacePL[playerid][Points]+=3; 
						format(string, sizeof(string), "Points: ~b~%d ~w~Status: ~r~Bad~w~", RacePL[playerid][Points]);
					}
				}
				ShowPlayerInformation(playerid, "Race Statistics", string);
			} else UpdateRaceInfo(playerid); 
		}
		SetTimerEx("RaceTimerZ", 1000, false, "i", playerid);
	}
	return true;
}

stock LeaveRace(playerid) {
	new IDCursaJucator = RacePL[playerid][IdRace],
		stringa[MAXO_TEXT];
	if(IDCursaJucator != INVALID_RACE_ID) {
		Race[IDCursaJucator][Participants]--;
		if(Race[IDCursaJucator][Started] == 0) {
			if(RacePL[playerid][RReady]) {
				RacePL[playerid][RReady] = 0;
				Race[IDCursaJucator][ParticipantsReady]--;
			}
			if(Race[IDCursaJucator][ParticipantsReady] == Race[IDCursaJucator][Participants] && Race[IDCursaJucator][Participants] > 1) {
				format(stringa,sizeof(stringa),"[{A60099}FMARace{FFFFFF}] Race {446ED1}%s"ALB" starts!",Race[IDCursaJucator][Nome]);
				SendFMARaceMessage(stringa);
				foreach(Player, x) {
					if(RacePL[x][IdRace] == IDCursaJucator) StartRace(x, IDCursaJucator); 
				}
			}
		}
		format(stringa,sizeof(stringa),"[{A60099}FMARace{FFFFFF}] {446ED1}%s "ALB"quit the race.", PlayerName(playerid));
		SendFMARaceMessage(stringa);
		RacePL[playerid][Checkpoint] = 0;
		RacePL[playerid][IdRace] = INVALID_RACE_ID;
		RacePL[playerid][TimeRC] = 0;
		RacePL[playerid][Position] = 0;
		RacePL[playerid][RLap]=1;
		RacePL[playerid][Pursuer]=0;
		RacePL[playerid][Points]=0;
		if(RacePL[playerid][Colision]) {
			DisableRemoteVehicleCollisions(playerid, COLISION_ENABLED);
			RacePL[playerid][Colision]=0;
			RaceVoteColision[FinalVote] = COLISION_ENABLED;
		}
		DeleteRaceCP(checkpointFMARace, playerid);
		TogglePlayerControllable(playerid, 1);
	}
	return true;
}

stock FinishRace(idRace) {
	new stringa[MAXO_TEXT];
	if(Race[idRace][Participants] == 0 && idRace != INVALID_RACE_ID) {
		Race[idRace][Participants] = 0;
		Race[idRace][ParticipantsReady] = 0;
		Race[idRace][Started] = 0;
		format(stringa,sizeof(stringa),"[{A60099}FMARace{FFFFFF}] Race {446ED1}%s"ALB" finish.",Race[idRace][Nome]);
		SendFMARaceMessage(stringa);
		idRace = INVALID_RACE_ID;
		IDCursa = INVALID_RACE_ID;
		RaceVoteColision[FinalVote] = 0;
		RaceVoteColision[VotedYes] = 0;
		RaceVoteColision[VotedNo] = 0;
	}
	return true;
}

stock RaceSysInit() {
	LoadCurseFMA();
	txtSemaf = TextDrawCreate(296.000000, 90.000000, "LD_ROUL:roulred");
	TextDrawBackgroundColor(txtSemaf, 255);
	TextDrawFont(txtSemaf, 4);
	TextDrawLetterSize(txtSemaf, 5.229988, 39.399997);
	TextDrawColor(txtSemaf, -1);
	TextDrawSetOutline(txtSemaf, 0);
	TextDrawSetProportional(txtSemaf, 1);
	TextDrawSetShadow(txtSemaf, 1);
	TextDrawUseBox(txtSemaf, 1);
	TextDrawTextSize(txtSemaf, 40.000000, 60.000000);

	for (new i; i < MAX_PLAYERS; i++)
		RacePL[i][IdRace] = INVALID_RACE_ID;
	return true;
}

stock PRaceJoin(playerid, idrace) {
	Race[idrace][Participants]++;
	RacePL[playerid][IdRace] = idrace;
	return true;
}

COMMAND:racehelp(playerid, params[]) {
	SendClientMessage(playerid, COLOR_GREEN, "[{A60099}FMARace{FFFFFF}] Racing Help:");
	SendClientMessage(playerid, COLOR_WHITE, "{8CE46C}/loadrace"ALB" to load a track and start it. Use {8CE46C}/joinrace"ALB" to join");
	SendClientMessage(playerid, COLOR_WHITE, "go to the checkpoint and type {8CE46C}/ready"ALB". The race will start when all others");
	SendClientMessage(playerid, COLOR_WHITE, "are ready as well. {8CE46C}/leave"ALB" to leave a joined race.");
	SendClientMessage(playerid, COLOR_WHITE, "The race can be forced to start with: {8CE46C}/endrace"ALB" command.");
	SendClientMessage(playerid, COLOR_WHITE, "{8CE46C}/racekick"ALB" - kicks someone from the race.");
	SendClientMessage(playerid, COLOR_WHITE, "{8CE46C}/racers"ALB" - list of people that joined current race.");
	SendClientMessage(playerid, COLOR_WHITE, "You can disable display of FMA messages  with {8CE46C}/togfma"ALB" command.");
	SendClientMessage(playerid, COLOR_WHITE, "{8CE46C}/votecol"ALB" to disable colision in the race.");
	if(PlayerInfo[playerid][pLeader] == FACT_FMA) {
		SendClientMessage(playerid, COLOR_WHITE, "{A60099}/racebuilder{FFFFFF} - create a race from scratch.");
		SendClientMessage(playerid, COLOR_WHITE, "{A60099}/createcp{FFFFFF} - creates a checkpoint.");
		SendClientMessage(playerid, COLOR_WHITE, "{A60099}/lastcp{FFFFFF} - the last checkpoint.");
	}
	SendClientMessage(playerid, COLOR_GRAD1, "NOTE: Racing system is not allowed for cops!");
	return true;
}

COMMAND:togfma(playerid, params[]) {
	if(FMAhasAccess(playerid)) {
		if (pFMAMessageON{playerid}) {
			pFMAMessageON{playerid} = false;
			SendClientMessage(playerid, COLOR_GRAD2, "FMA messages Disabled !");
		}
		else
		{
			pFMAMessageON{playerid} = true;
			SendClientMessage(playerid, COLOR_GRAD2, "FMA messages Enabled !");
		}
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have access to this command.");
	return true;
}

COMMAND:endrace(playerid, params[]) {
	if(PlayerInfo[playerid][pFactiune] == FACT_FMA) {
		if(IDCursa != INVALID_RACE_ID) {
			new stringa[MAXO_TEXT];
			format(stringa,sizeof(stringa),"[{A60099}FMARace{FFFFFF}] {446ED1}%s{FFFFFF} has forced race ending.",PlayerName(playerid));
			SendFMARaceMessage(stringa);
			foreach(Player, i) LeaveRace(i);
			FinishRace(IDCursa);
		} else SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] No race started");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You need to be an FMA member.");
	return true;
}

COMMAND:leave(playerid) {
	if(!FMAhasAccess(playerid)) 
		return SendClientMessage(playerid, COLOR_GRAD1, "You don't have access to this command.");
	if(RacePL[playerid][IdRace] == INVALID_RACE_ID) 
		return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You did not join any race.");
	new stringa[MAXO_TEXT];
	if(Race[IDCursa][Chase] && Race[IDCursa][Started] == 1) {
		foreach(Player, i) {
			if(RacePL[i][IdRace] == IDCursa && i != playerid) {
				format(stringa,sizeof(stringa),"[{A60099}FMARace{FFFFFF}] {446ED1}%s{FFFFFF} wons the race because the opponent quitted.",PlayerName(i));
				SendFMARaceMessage(stringa);
				SafeGivePlayerMoney(i,Race[RacePL[i][IdRace]][Costs]*2);
				LeaveRace(i);
			}
		}
	}
	LeaveRace(playerid);
	format(stringa,sizeof(stringa),"| Total Participants: {8ECE46}%d"ALB" | Ready: {8ECE46}%d"ALB" |",Race[IDCursa][Participants], Race[IDCursa][ParticipantsReady]);
	SendClientMessage(playerid, COLOR_WHITE, stringa); 
	return true;
}

COMMAND:joinrace(playerid,params[]) {
	if(FMAhasAccess(playerid)) {
		if(IDCursa != INVALID_RACE_ID) {
			if(IsInsideInterior(playerid)) return SendClientMessage(playerid, COLOR_GRAD1, "* You can't use this function from inside a building/interior!");
			if(PlayerInfo[playerid][pJailed]) return SendClientMessage(playerid, COLOR_GRAD1, "You are in jail. Can't do this right now.");
			if(PlayerInfo[playerid][pCash] < Race[IDCursa][Costs]) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You don't have the money needed.");
			if(Race[IDCursa][Participants] < MAX_RACE_PARTICIPANTS) {
				new string[MAXO_TEXT];
				if(Race[IDCursa][Started]) {
					SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] This race is already started. Wait its ending before joining.");
					format(string,sizeof(string),"| Total Participants: {8ECE46}%d"ALB" |", Race[IDCursa][Participants]);
					SendClientMessage(playerid,COLOR_WHITE, string); 
				}
				else
				{
					if(RacePL[playerid][IdRace] == IDCursa) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You already joined this race.");
					if(Race[IDCursa][Chase] == 1) {
						if(Race[IDCursa][Participants] == 2) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] There are already two player in this race (chase race limit)");
						if(Race[IDCursa][Participants] == 0) SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You are the hunted. When the race starts, stay in front of your opponent and try to escape.");
						else if(Race[IDCursa][Participants] == 1) {
							SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You are the hunter. When the race starts, stay behind your opponent and chase him.");
							RacePL[playerid][Pursuer] = 1;
						}
					}
					PRaceJoin(playerid, IDCursa);
					format(string,sizeof(string),"[{A60099}FMARace{FFFFFF}] {446ED1}%s{FFFFFF} joined the race.",PlayerName(playerid));
					SendFMARaceMessage(string);
					SafeGivePlayerMoney(playerid,-Race[IDCursa][Costs]);
					SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You joined the race. Go to the checkpoint and type \"{C14124}/ready"ALB"\" when you are ready.");
					CreateRaceCP(playerid,checkpointFMARace,CP_FMA_RACE,CheckpointRace[IDCursa][0][CXPos],CheckpointRace[IDCursa][0][CYPos],CheckpointRace[IDCursa][0][CZPos],CheckpointRace[IDCursa][1][CXPos],CheckpointRace[IDCursa][1][CYPos],CheckpointRace[IDCursa][1][CZPos],0);
					new minuti=floatround(Race[IDCursa][Record]/60),
						secondi=Race[IDCursa][Record]-(minuti*60),
						rand = RandomEx(1,4),
						earning = floatround(Race[IDCursa][Costs]*rand*5/rand);
					format(string,sizeof(string),"{446ED1}Track: {8CE46C}%s\n",Race[IDCursa][Nome]);
					strcat(VeryLargeString, string);
					format(string,sizeof(string),"{446ED1}Laps: {8CE46C}%d\n",Race[IDCursa][Laps]);
					strcat(VeryLargeString, string);
					format(string,sizeof(string),"{446ED1}Entry Fee: {33AA33}${8CE46C}%s\n",FormatNumber(Race[IDCursa][Costs], 0, ','));
					strcat(VeryLargeString, string);
					format(string,sizeof(string),"{446ED1}Player's Record: {8CE46C}%s\n",Race[IDCursa][RacePLRecord]);
					strcat(VeryLargeString, string);
					format(string,sizeof(string),"{446ED1}Record: {8CE46C}%02d:%02d\n",minuti,secondi);
					strcat(VeryLargeString, string);
					format(string,sizeof(string),"{446ED1}Checkpoints: {8CE46C}%d\n",Race[IDCursa][CheckpointNr]+1);
					strcat(VeryLargeString, string);
					format(string,sizeof(string),"{446ED1}Possible Earning: {33AA33}${8CE46C}%s\n",FormatNumber(earning, 0, ','));
					strcat(VeryLargeString, string);
					strcat(VeryLargeString, "{446ED1}Bonus Earning: {33AA33}${8CE46C}250,000{446ED1} if you are holding still the Record.");
					ShowPlayerDialog(playerid,DIALOGID_NO_ACTION,DIALOG_STYLE_MSGBOX,"Race Info",VeryLargeString,"Ok","");
					clear.string(VeryLargeString);
					format(string,sizeof(string),"| Total Participants: {8ECE46}%d"ALB" | Ready: {8ECE46}%d"ALB" |",Race[IDCursa][Participants], Race[IDCursa][ParticipantsReady]);
					SendClientMessage(playerid,COLOR_WHITE, string); 
				}
			} else SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] Can't join. Maximum number of participants reached for this race!");
		} else SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] No race loaded!");
	} else SendClientMessage(playerid, COLOR_WHITE, "[{A60099}FMARace{FFFFFF}] Can't join. Cops can't participate.");
	return true;
}

COMMAND:racekick(playerid,params[]) {
	if(PlayerInfo[playerid][pFactiune] == FACT_FMA) {
		if(IDCursa != INVALID_RACE_ID) {
			new motiv[64], giveplayerid, stringa[MAXO_TEXT];
			if (sscanf(params, "us[63]", giveplayerid,motiv)) return SendClientMessage(playerid, COLOR_GRAD2, "USAGE: /racekick [playerid/PartOfName] [reason]");
			if(giveplayerid != INVALID_PLAYER_ID) {
				if(RacePL[giveplayerid][IdRace] == IDCursa) {
					format(stringa,sizeof(stringa),"[{A60099}FMARace{FFFFFF}] {446ED1}%s{FFFFFF} kicks {8ECE46}%s"ALB" from the race because: %s",PlayerName(playerid),PlayerName(giveplayerid),motiv);
					SendFMARaceMessage(stringa);
					LeaveRace(giveplayerid);
					format(stringa,sizeof(stringa),"| Total Participants: {8ECE46}%d"ALB" | Ready: {8ECE46}%d"ALB" |",Race[IDCursa][Participants], Race[IDCursa][ParticipantsReady]);
					SendClientMessage(playerid,COLOR_WHITE, stringa); 
				} else SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] That player is not active in any race!");
			} else SendClientMessage(playerid, COLOR_GRAD2, "Can not find user - Unknown user");
		} else SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] No race loaded!");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You need to be a FMA member.");
	return true;
}

COMMAND:racers(playerid,params[]) {
	if(FMAhasAccess(playerid)) {
		if(IDCursa != INVALID_RACE_ID) {
			SendClientMessage(playerid, COLOR_WHITE, "|_______{8ECE46}Racers Online"ALB"______|");
			new stringa[MAXO_TEXT];
			foreach(Player, i) {
				if(RacePL[i][IdRace] == IDCursa) {
					format(stringa,sizeof(stringa),"ID: %d | {8ECE46}%s"ALB" | Ready: %s",i,PlayerName(i),(RacePL[i][RReady]) ? ("{8ECE46}Yes") : ("{C14124}No"));
					SendClientMessage(playerid,COLOR_WHITE, stringa);
				}
			}
			format(stringa,sizeof(stringa),"| Total Participants: {8ECE46}%d"ALB" | Ready: {8ECE46}%d"ALB" |",Race[IDCursa][Participants], Race[IDCursa][ParticipantsReady]);
			SendClientMessage(playerid,COLOR_WHITE, stringa); 
		} else SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] No race loaded!");
	} else SendClientMessage(playerid, COLOR_GRAD1, "[{A60099}FMARace{FFFFFF}] Cops can't use this command!");
	return true;
}

COMMAND:ready(playerid) {
	if(IDCursa != INVALID_RACE_ID) {
		if(!Race[IDCursa][Started]) {
			if(RacePL[playerid][IdRace] == INVALID_RACE_ID) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You did not join any race.");
			if(RacePL[playerid][RReady]) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You are yet ready, wait opponents to be.");
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
				if(IsPlayerInRangeOfPoint(playerid, DEFAULT_RACE_CP_SIZE, CheckpointRace[IDCursa][0][CXPos],CheckpointRace[IDCursa][0][CYPos],CheckpointRace[IDCursa][0][CZPos])) {
					new stringa[MAXO_TEXT];
					format(stringa,sizeof(stringa),"{8CE46C}%s "ALB"is ready to start.",PlayerName(playerid));
					SendFMARaceMessage(stringa);
					SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] Wait other players to be ready.");
					RacePL[playerid][RReady] = 1;
					Race[IDCursa][ParticipantsReady]++;
					format(stringa,sizeof(stringa),"| Total Participants: {8ECE46}%d"ALB" | Ready: {8ECE46}%d"ALB" |",Race[IDCursa][Participants], Race[IDCursa][ParticipantsReady]);
					SendClientMessage(playerid,COLOR_WHITE, stringa); 
					if(Race[IDCursa][Chase])  {
						if(Race[IDCursa][ParticipantsReady] == 2)  {
							format(stringa,sizeof(stringa),"[{A60099}FMARace{FFFFFF}] Race {446ED1}%s"ALB" starts!",Race[IDCursa][Nome]);
							SendFMARaceMessage(stringa);
							foreach(Player, x) {
								if(RacePL[x][IdRace] == IDCursa) StartRace(x, IDCursa); 
							}
						}
					}
					else
					{
						#if !defined _versiune_test
						if((Race[IDCursa][ParticipantsReady] == Race[IDCursa][Participants]) && (Race[IDCursa][Participants] > 1))
						#else
						if((Race[IDCursa][ParticipantsReady] == Race[IDCursa][Participants]))
						#endif
						{
							format(stringa,sizeof(stringa),"[{A60099}FMARace{FFFFFF}] Race {446ED1}%s"ALB" starts!",Race[IDCursa][Nome]);
							SendFMARaceMessage(stringa);
							foreach(Player, x) {
								if(RacePL[x][IdRace] == IDCursa) StartRace(x, IDCursa); 
							}
						}
					}
				} else SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] Go to the checkpoint and type "ALB"/ready.");
			} else SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You must be driver for this action.");
		} else SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You can't join the race right now.");
	} else SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] No race loaded!");
	return true;
}

stock LoadCurseFMA()
	return mysql_tquery(connectionHandle, "SELECT * FROM Races_id", "LoadRacez2", "d", INITCURSEFMA_THREAD_ID);

stock LoadCurseFMACheckpoints(idcursa) {
	new query[MAXO_TEXT];
	mysql_format(connectionHandle, query, sizeof(query), "SELECT X,Y,Z FROM Races_checkpoints WHERE IDCursa = %d", idcursa);
	mysql_tquery(connectionHandle, query, "LoadRacesCheckpoints", "d", idcursa);
	return true;
}

function LoadRacez2()
{
	rows = cache_num_rows();
	if(rows) 
	{
		for(new r; r < rows; r++) {
			Race[r][IDCursaDB] = cache_get_row_int(r, 1);
			cache_get_row(r, 2, Race[r][Nome], .max_len = MAX_PLAYER_NAME); // race name
			Race[r][Laps] = cache_get_row_int(r, 3);
			Race[r][Costs] = cache_get_row_int(r, 4);
			cache_get_row(r, 5, Race[r][RCreator], .max_len = MAX_PLAYER_NAME); // player creator
			Race[r][Chase] = cache_get_row_int(r, 6);
			Race[r][Record] = cache_get_row_int(r, 7);
			cache_get_row(r, 8, Race[r][RacePLRecord], .max_len = MAX_PLAYER_NAME); // player record
			Race[r][Air] = cache_get_row_int(r, 9);
			LoadCurseFMACheckpoints(r);
		}
		AllLoadedRaces = rows;
		printf("LoadRacez2 - called (%d races).", rows);
	} 
	return 1;
}

function LoadRacesCheckpoints(idcursa) {
	rows = cache_num_rows();
	if(rows)  {
		Race[idcursa][CheckpointNr] = -1;
		for(new r; r < rows; r++) {
			CheckpointRace[idcursa][r][CXPos] = cache_get_row_float(r, 2);
			CheckpointRace[idcursa][r][CYPos] = cache_get_row_float(r, 3);
			CheckpointRace[idcursa][r][CZPos] = cache_get_row_float(r, 4);
			Race[idcursa][CheckpointNr]++;
		}
		Iter_Add(CurseFMA, idcursa); 
		printf("%d checkpoints loaded for Race %d.",rows,idcursa);
	} else printf("No checkpoints loaded from table Races_checkpoints for IDCursa: %d.", idcursa);
	return true;
}

stock SaveRaceZ(playerid)
{
	new idcursa = RacePL[playerid][RaceEditorId], string[MAXO_TEXT2+MAXO_TEXT1], numarchecks = Race[idcursa][CheckpointNr], playerrecord[MAX_PLAYER_NAME];
	playerrecord = "Nobody";
	Race[idcursa][RacePLRecord] = playerrecord;
	Race[idcursa][Record] = 0;
	format(string, sizeof(string), "INSERT INTO Races_id (IDCursa, Name, Laps, Entry, Creator, TipChase, TimeRecord, RecordPlayer, Air) VALUES (%d, '%s', %d, %d, '%s', %d, %d, '%s', %d)",
	Race[idcursa][IDCursaDB],
	Race[idcursa][Nome],
	Race[idcursa][Laps],
	Race[idcursa][Costs],
	Race[idcursa][RCreator],
	Race[idcursa][Chase],
	Race[idcursa][Record],
	Race[idcursa][RacePLRecord],
	Race[idcursa][Air]
	);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);	
	for(new i; i < (numarchecks+1); i++) {
		format(string, sizeof(string), "INSERT INTO Races_checkpoints (IDCursa, X, Y, Z) VALUES (%d, %f, %f, %f)", Race[idcursa][IDCursaDB], CheckpointRace[idcursa][i][CXPos],CheckpointRace[idcursa][i][CYPos],CheckpointRace[idcursa][i][CZPos]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	}
	Iter_Add(CurseFMA, Race[idcursa][IDCursaDB]);
	return true;
}

function ClearPVarRace(playerid) {
	RacePL[playerid][IdRace] = INVALID_RACE_ID;
	RacePL[playerid][RReady] = 0;
	RacePL[playerid][RLap] = 1;
	RacePL[playerid][Pursuer] = 0;
	RacePL[playerid][Points] = 0;
	RacePL[playerid][Checkpoint] = 0;
	RacePL[playerid][Builder] = 0;
	RacePL[playerid][TimeRC] = 0;
	RacePL[playerid][Position] = 0;
	return true;
}

stock AbortBuilder(playerid, idcursa) {
	new numarchecks = Race[idcursa][CheckpointNr];
	Race[idcursa][IDCursaDB] = 0;
	Race[idcursa][Nome] = 0;
	Race[idcursa][Laps] = 0;
	Race[idcursa][Costs] = 0;
	Race[idcursa][RCreator] = 0;
	Race[idcursa][Chase] = 0;
	Race[idcursa][RacePLRecord] = 0;
	for(new r; r < numarchecks; r++)  {
		CheckpointRace[idcursa][r][CXPos] = 0;
		CheckpointRace[idcursa][r][CYPos] = 0;
		CheckpointRace[idcursa][r][CZPos] = 0;
		Race[idcursa][CheckpointNr]--;
	}
	RacePL[playerid][RaceEditorId] = 0;
	SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You aborted the racebuilding.");
	return true;
}

stock SendFMARaceMessage(message[]) {
	foreach(Player, i) {
		if(gPlayerLogged{i}) {
			if(pFMAMessageON{i}) {
				if(FMAhasAccess(i)) 
					SendClientMessage(i, COLOR_WHITE, message);
			}
		}
	}
	return true;
}

stock NewRecordFMA(playerid) {
	new
		Minuti = floatround(RacePL[playerid][TimeRC]/60),
		Secondi = RacePL[playerid][TimeRC]-(Minuti*60),
		string[MAXO_TEXT];
	
	format(VeryLargeString,sizeof(VeryLargeString),"[{A60099}FMARace{FFFFFF}] Player: {8ECE46}%s"ALB" Track: {446ED1}%s"ALB" Record: {C14124}%02d:%02d.",PlayerName(playerid),Race[IDCursa][Nome],Minuti,Secondi);
	SendFMARaceMessage(VeryLargeString);
	clear.string(VeryLargeString);
	new RecordPlayer[MAX_PLAYER_NAME];
	format(RecordPlayer, sizeof(RecordPlayer), "%s", PlayerName(playerid));
	Race[IDCursa][RacePLRecord] = RecordPlayer;
	Race[IDCursa][Record] = RacePL[playerid][TimeRC];
	format(string, sizeof(string), "UPDATE Races_id SET TimeRecord = %d, RecordPlayer = '%s' WHERE IDCursa = %d", Race[IDCursa][Record], Race[IDCursa][RacePLRecord], IDCursa);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	return true;
}

stock GetPlayerPosition(playerid) {
	new index;
	for (new j; j < MAX_PLAYERS; j++) {
	    if(RacePL[playerid][IdRace] != INVALID_RACE_ID)  {
	    	if(j != playerid) {
				if(RacePL[playerid][Checkpoint] < RacePL[j][Checkpoint])	
				    index++; 
				if(RacePL[playerid][Checkpoint] == RacePL[j][Checkpoint]) {
				    new PlayerCheckPoint = RacePL[playerid][Checkpoint],
						ElseCheckPoint = RacePL[j][Checkpoint];
    				if(GetPlayerDistanceFromPoint(playerid, CheckpointRace[IDCursa][PlayerCheckPoint][CXPos]+1,CheckpointRace[IDCursa][PlayerCheckPoint][CYPos]+1, CheckpointRace[IDCursa][PlayerCheckPoint][CZPos]+1) > GetPlayerDistanceFromPoint(j, CheckpointRace[IDCursa][ElseCheckPoint][CXPos]+1, CheckpointRace[IDCursa][ElseCheckPoint][CYPos]+1, CheckpointRace[IDCursa][ElseCheckPoint][CZPos]+1))
				    	index++;
				}
			}
		}
	}
	RacePL[playerid][Position] = index +1;
	return RacePL[playerid][Position];
}

stock returnOrdinal(number) {
	new
	    string[4]
	;
	number = number < 0 ? -number : number;

	if(10 < (number % 100) && (number % 100) < 14) return format(string, 4, "%s", "th"), string;

	switch(number % 10) {
	    case 1: return format(string, 4, "%s", "st"), string;
	    case 2: return format(string, 4, "%s", "nd"), string;
	    case 3: return format(string, 4, "%s", "rd"), string;
	    default: return format(string, 4, "%s", "th"), string;
	}
	return format(string, 4, "%s", "N/A"), string;
}

stock CalculateVote() {
	new yes = RaceVoteColision[VotedYes], no = RaceVoteColision[VotedNo], text[9];
	if(yes > no) RaceVoteColision[FinalVote] = COLISION_DISABLED;
	else if(yes < no) RaceVoteColision[FinalVote] = COLISION_ENABLED;
	else if(yes == no) RaceVoteColision[FinalVote] = RandomEx(COLISION_ENABLED,COLISION_DISABLED);
	switch (RaceVoteColision[FinalVote])
	{
		case COLISION_ENABLED: text = "enabled", format(VeryLargeString,sizeof(VeryLargeString),"[{A60099}FMARace{FFFFFF}] Colision is {446ED1}%s{FFFFFF} for this race (after voting).",text);
		case COLISION_DISABLED: text = "disabled", format(VeryLargeString,sizeof(VeryLargeString),"[{A60099}FMARace{FFFFFF}] Colision is {446ED1}%s{FFFFFF} for this race (after voting).",text);
	}
	SendFMARaceMessage(VeryLargeString);
	clear.string(VeryLargeString);
	return true;
}	

COMMAND:racebuilder(playerid) {
	if(AllLoadedRaces > MAX_RACES) {
		new string[MAXO_TEXT1];
		format(string, sizeof(string), "[{A60099}FMARace{FFFFFF}] You cannot build races. Maximum races reached (%d).", MAX_RACES);
		SendClientMessage(playerid,COLOR_WHITE, string);
		return 1;
	}
	foreach (Player, i) {
		if(RacePL[i][Builder]) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You cannot build races. Someone is already doing that.");
	}
	if(IDCursa != INVALID_RACE_ID) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You cannot build races when are loaded races.");
	if(RacePL[playerid][IdRace] != INVALID_RACE_ID) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You cannot build races while racing.");
	if(PlayerInfo[playerid][pLeader] != FACT_FMA) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] Only the leader can build races."); 
	ShowPlayerDialog(playerid,DIALOGINFOBuilder,DIALOG_STYLE_MSGBOX,"Info Builder",""ALB"Welcome in the builder mode of {C14124}eGaming Racing"ALB".\nNow you have to insert some race informations:\n•Race's Name\n•Laps\n•Cost\n•Creation of a checkpoint list\n\nNote: During the builder mode you cannot join races.","Proceed","Close");
	return true;
}

COMMAND:createcp(playerid) {
	if(!RacePL[playerid][Builder]) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You are not in builder mode.");
	if(!RacePL[playerid][CheckEnable]) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] Finish to insert race information before creating a checkpoint list.");
	new idcursa = RacePL[playerid][RaceEditorId], 
		idcheck = Race[idcursa][CheckpointNr],
		string[MAXO_TEXT],
		inveh = GetPlayerVehicleID(playerid);
	if(idcheck == (MAX_CHECKPOINT-1)) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You can't make more checkpoints, please end it."); // (MAX_CHECKPOINT-1) folosim asa pt ca se numeroteaza de la 0 idcheck
	if(inveh == INVALID_VEHICLE_ID) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You need a vehicle to start making checkpoints.");
	GetPlayerPos(playerid,XPosizione,YPosizione,ZPosizione);
	CheckpointRace[idcursa][idcheck][CXPos] = XPosizione;
	CheckpointRace[idcursa][idcheck][CYPos] = YPosizione;
	CheckpointRace[idcursa][idcheck][CZPos] = ZPosizione;
	switch (Race[idcursa][CheckpointNr]) {
		case 0: format(string, sizeof(string), "[{A60099}FMARace{FFFFFF}] [CHECKPOINT:] "ALB"Checkpoint %d saved. (Start line here).", Race[idcursa][CheckpointNr]);
		default: format(string, sizeof(string), "[{A60099}FMARace{FFFFFF}] [CHECKPOINT:] "ALB"Checkpoint %d saved.", Race[idcursa][CheckpointNr]);
	}
	SendClientMessage(playerid,COLOR_WHITE, string);
	Race[idcursa][CheckpointNr]++;
	return true;
}

COMMAND:lastcp(playerid) {
	if(RacePL[playerid][Builder]==0) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You are not in builder mode.");
	if(RacePL[playerid][CheckEnable]==0) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] To finish, create first a checkpoint list with {33CCFF}/createcp.");
	new idcursa = RacePL[playerid][RaceEditorId], idcheck = Race[idcursa][CheckpointNr];
	if(Race[idcursa][CheckpointNr] < 4) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You need to create 5 checkpoints in order to set the finish line here.");
	RacePL[playerid][Builder]=0;
	RacePL[playerid][CheckEnable]=0;
	SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You completed the race.");
	GetPlayerPos(playerid,XPosizione,YPosizione,ZPosizione);
	CheckpointRace[idcursa][idcheck][CXPos] = XPosizione;
	CheckpointRace[idcursa][idcheck][CYPos] = YPosizione;
	CheckpointRace[idcursa][idcheck][CZPos] = ZPosizione;
	SendClientMessage(playerid,-1,"[CHECKPOINT:] "ALB"You set the finish line here.");
	SaveRaceZ(playerid);
	SendFMARaceMessage("[{A60099}FMARace{FFFFFF}] Administrator has build a new race. Now is available on loading races.");
	return true;
}

COMMAND:loadrace(playerid) {
	if(PlayerInfo[playerid][pFactiune] != FACT_FMA) return SendClientMessage(playerid, COLOR_GRAD1, "You are not a FMA member.");
	if(IsInsideInterior(playerid)) return SendClientMessage(playerid, COLOR_GRAD1, "* You can't use this function from inside a building/interior!");
	if(PlayerInfo[playerid][pJailed]) return SendClientMessage(playerid, COLOR_GRAD1, "You are in jail. Can't do this right now.");
	foreach (Player, i) {
		if(RacePL[i][Builder]) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You cannot load races right now.");
	}
	new string[MAXO_TEXT];
	new timp = gettime() - RaceTimpVechi;
	if (timp < 900 && !PlayerInfo[playerid][pAdmin]) {
		if(timp < 840) format(VeryLargeString, sizeof(VeryLargeString), "Please try again later in %d minutes !", (900-timp)/60);
		else format(VeryLargeString, sizeof(VeryLargeString), "Please try again later in %d seconds !", 900-timp);
		SendClientMessage(playerid, 0xFFFF00AA, VeryLargeString);
		clear.string(VeryLargeString);
		return 1;
	}
	if(IDCursa != INVALID_RACE_ID) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] A race is already active!");
	if(RacePL[playerid][Builder]==1) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You are in builder mode.");
	if(Iter_Count(CurseFMA)) {
		new type[16];
		foreach (new i : CurseFMA) {
			if(Race[i][Chase]) type = "Yes";
			else type = "No";
			format(string, sizeof(string), "\tName\tChase\tEntry fee\tLaps/Checks\n%s\t%s\t{33AA33}${FFFFFF}%s\t%d/%d", Race[i][Nome], type, FormatNumber( Race[i][Costs], 0, ',' ), Race[i][Laps], Race[i][CheckpointNr]+1);
			// store
			strcat(VeryLargeString, string);
		}
		ShowPlayerDialog(playerid,DIALOGGARE,DIALOG_STYLE_TABLIST_HEADERS,"Available Races",VeryLargeString,"Load","Cancel");
		clear.string(string);
		clear.string(VeryLargeString);
	} else SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] No races available. Use /racebuilder.");
	return 1;
}

COMMAND:votecol(playerid,params[]) {
	if(PlayerInfo[playerid][pFactiune] == FACT_FMA) {
		if(IDCursa != INVALID_RACE_ID) {
			RaceVoteColision[Counter] = 0;
			foreach(Player, x) {
				if(RacePL[x][IdRace] == IDCursa) ShowPlayerDialog(x, DIALOGID_RACE_VOTE, DIALOG_STYLE_MSGBOX, "Vote for colision", "{FFFFFF}Yes - colision {AA3333}off{FFFFFF} and No - colision {9ACD32}on", "Yes", "No"), RaceVoteColision[Counter]++;
			}
			format(VeryLargeString,sizeof(VeryLargeString),"[{A60099}FMARace{FFFFFF}] {446ED1}%s{FFFFFF} enabled the voting for colision. Votes need (%d).",PlayerName(playerid), RaceVoteColision[Counter]);
			SendFMARaceMessage(VeryLargeString);
			clear.string(VeryLargeString);
			
		} else SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] No race loaded!");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You need to be a FMA member.");
	return true;
}

stock RaceSysOnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	new idnewrace = RacePL[playerid][RaceEditorId],
		stringa[MAXO_TEXT];
	if(dialogid==DIALOGINFOGARA2) {
		RacePL[playerid][CheckEnable]=1;
		return 1;
	}
	else if(dialogid==DIALOGID_RACE_AIRTYPE) {
		if(response) {
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "» Air Type: Yes.");
			Race[idnewrace][Air] = 1;
		}
		else if(!response) {
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "» Air Type: No.");
			Race[idnewrace][Air] = 0;
		}
		Race[idnewrace][CheckpointNr] = 0;
		ShowPlayerDialog(playerid,DIALOGINFOGARA2,0,"Race Info Menu",""ALB"You created the race's info file.\nNow you need a checkpoint list.\nUse the command \"{C14124}/createcp"ALB"\" to create checkpoint for your race.\nOnce you've finished, type \"{C14124}/lastcp"ALB"\" to exit builder mode and load the new race.","Go","");
		return 1;
	}
	else if(dialogid==DIALOGINSEGUIMENTO) {
		if(response)
		{
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "» Chase Type: Yes.");
			Race[idnewrace][Chase] = 1;
		}
		else if(!response)
		{
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "» Chase Type: No.");
			Race[idnewrace][Chase] = 0;
		}
		ShowPlayerDialog(playerid,DIALOGID_RACE_AIRTYPE,DIALOG_STYLE_MSGBOX,"Air option",""ALB"This option make the checkpoints for Air.\n\nIf you say 'Yes' than you need a plane/heli or boat to make this work.","Yes","No");
		return 1;
	}
	else if(dialogid==DIALOGCostsGARA) {
		if(response) {
			if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext)<=0) return ShowPlayerDialog(playerid,DIALOGCostsGARA,DIALOG_STYLE_INPUT,"Race's Cost",""ALB"Type the cost to join your race (min $1):","Continue","Abort");
			Race[idnewrace][Costs] = strval(inputtext);
			ShowPlayerDialog(playerid,DIALOGINSEGUIMENTO,DIALOG_STYLE_MSGBOX,"Chase option",""ALB"Do you want this race to be a Chase type?","Yes","No");
			return 1;
		}
		else if(!response) {
			AbortBuilder(playerid, idnewrace);
			return 1;
		}
	}
	else if(dialogid==DIALOGLapsGARA) {
		if(!strlen(inputtext) || !isNumeric(inputtext) || strval(inputtext)<=0) return ShowPlayerDialog(playerid,DIALOGLapsGARA,DIALOG_STYLE_INPUT,"Race's Laps",""ALB"ERROR:\nType the number of laps for your races (1:sprint 2-more:circuit)","Continue","");
		Race[idnewrace][Laps] = strval(inputtext);
		ShowPlayerDialog(playerid,DIALOGCostsGARA,DIALOG_STYLE_INPUT,"Race's Cost",""ALB"Type the cost to join your race (min 1):","Continue","Abort");
		return 1;
	}
	else if(dialogid==DIALOGNOMEGARA) {
		new typed = strlen(inputtext);
		if(typed > 25) return ShowPlayerDialog(playerid,DIALOGNOMEGARA,DIALOG_STYLE_INPUT,"Race's Name",""ALB"ERROR:\nType the name of your race:\n\nLess characters this time.","Continue","");
		new namecursa[MAX_PLAYER_NAME];
		format(namecursa, sizeof(namecursa), "%s", inputtext);
		Race[idnewrace][Nome] = namecursa;
		new namecreator[MAX_PLAYER_NAME];
		format(namecreator, sizeof(namecreator), "%s", PlayerName(playerid));
		Race[idnewrace][RCreator] = namecreator;
		ShowPlayerDialog(playerid,DIALOGLapsGARA,DIALOG_STYLE_INPUT,"Race's Laps",""ALB"Type the number of laps for your races (1:sprint 2-more:circuit)","Continue","");
		return 1;
	}
	else if(dialogid==DIALOGINFOBuilder) {
		if(response) {
			RacePL[playerid][RaceEditorId] = 0;
			new last = Iter_Last(CurseFMA), newidcursa;
			if(Iter_Count(CurseFMA) == 0) newidcursa = 0;
			else newidcursa = last+1;
			RacePL[playerid][RaceEditorId] = newidcursa;
			Race[newidcursa][IDCursaDB] = newidcursa;
			RacePL[playerid][Builder] = 1;
			ShowPlayerDialog(playerid,DIALOGNOMEGARA,DIALOG_STYLE_INPUT,"Race's Name",""ALB"Type the name of you race:","Continue","");
			return 1;
		}
		else if(!response)
		{
			ShowPlayerDialog(playerid,DIALOGID_NO_ACTION,DIALOG_STYLE_MSGBOX,"Canceled","You canceled the procedure.","Close","");
			return 1;
		}
		return 1;
	}
	else if(dialogid==DIALOGINFO) return 1;
	else if(dialogid==DIALOGGARE && response)
	{
		if(IDCursa == INVALID_RACE_ID)
		{
			foreach (Player, i) ClearPVarRace(i); 
			IDCursa = listitem;
			if(PlayerInfo[playerid][pCash] < Race[IDCursa][Costs]) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You don't have the money needed to load a race.");
			Race[IDCursa][Participants] = 0;
			Race[IDCursa][Podium] = 0;
			if(RacePL[playerid][IdRace] != INVALID_RACE_ID) return SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You already joined another race.");
			if(Race[IDCursa][Chase])
				SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] You are the hunted. When the race starts, stay in front of your opponent and try to escape.");
			RaceTimpVechi = gettime();
			Race[IDCursa][ParticipantsReady] = 0;
			PRaceJoin(playerid, IDCursa);
			if(Race[IDCursa][Laps]>1 && Race[IDCursa][Chase]==0) format(VeryLargeString,sizeof(VeryLargeString),"[{A60099}FMARace{FFFFFF}] {446ED1}%s{FFFFFF} loaded {F58C5B}Circuit - "ALB"%s (%d laps)",PlayerName(playerid), Race[IDCursa][Nome],Race[IDCursa][Laps]);
			if(Race[IDCursa][Laps]==1 && Race[IDCursa][Chase]==0) format(VeryLargeString,sizeof(VeryLargeString),"[{A60099}FMARace{FFFFFF}] {446ED1}%s{FFFFFF} loaded {97EA68}Sprint - "ALB"%s",PlayerName(playerid), Race[IDCursa][Nome]);
			if(Race[IDCursa][Laps]>1 && Race[IDCursa][Chase]==1) format(VeryLargeString,sizeof(VeryLargeString),"[{A60099}FMARace{FFFFFF}] {446ED1}%s{FFFFFF} loaded {446ED1}Chase - "ALB"%s (%d laps)",PlayerName(playerid), Race[IDCursa][Nome],Race[IDCursa][Laps]);
			if(Race[IDCursa][Laps]==1 && Race[IDCursa][Chase]==1) format(VeryLargeString,sizeof(VeryLargeString),"[{A60099}FMARace{FFFFFF}] {446ED1}%s{FFFFFF} loaded {446ED1}Chase - "ALB"%s",PlayerName(playerid), Race[IDCursa][Nome]);
			SendFMARaceMessage(VeryLargeString);
			clear.string(VeryLargeString);
			format(stringa,sizeof(stringa),"{8CE46C}%s "ALB"joined the race.",PlayerName(playerid));
			SendFMARaceMessage(stringa);
			SendFMARaceMessage("{8CE46C}[NOTICE] "ALB"You can toggle FMA messages with {8CE46C}/togfma"ALB" command.");
			SafeGivePlayerMoney(playerid,-Race[IDCursa][Costs]);
			#if defined TELEPORT_TO_START
			SafeSetPlayerPos(playerid,CheckpointRace[IDCursa][0][CXPos],CheckpointRace[IDCursa][0][CYPos],CheckpointRace[IDCursa][0][CZPos]);
			SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] Automatically joined the race. Type \"{C14124}/Ready"ALB"\" when you are ready.");
			#else
			SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] Automatically joined the race. Go to the checkpoint and type \"{C14124}/Ready"ALB"\" when you are ready.");
			#endif
			CreateRaceCP(playerid,checkpointFMARace,CP_FMA_RACE,CheckpointRace[IDCursa][0][CXPos],CheckpointRace[IDCursa][0][CYPos],CheckpointRace[IDCursa][0][CZPos],CheckpointRace[IDCursa][1][CXPos],CheckpointRace[IDCursa][1][CYPos],CheckpointRace[IDCursa][1][CZPos],0); 
			new minuti=floatround(Race[IDCursa][Record]/60),
				secondi=Race[IDCursa][Record]-(minuti*60),
				rand = RandomEx(1,4),
				earning = floatround(Race[IDCursa][Costs]*rand*5/rand);
			new string[MAXO_TEXT];
			format(string,sizeof(string),"{446ED1}Track: {8CE46C}%s\n",Race[IDCursa][Nome]);
			strcat(VeryLargeString, string);
			format(string,sizeof(string),"{446ED1}Laps: {8CE46C}%d\n",Race[IDCursa][Laps]);
			strcat(VeryLargeString, string);
			format(string,sizeof(string),"{446ED1}Entry Fee: {33AA33}${8CE46C}%s\n",FormatNumber(Race[IDCursa][Costs], 0, ','));
			strcat(VeryLargeString, string);
			format(string,sizeof(string),"{446ED1}Player's Record: {8CE46C}%s\n",Race[IDCursa][RacePLRecord]);
			strcat(VeryLargeString, string);
			format(string,sizeof(string),"{446ED1}Record: {8CE46C}%02d:%02d\n",minuti,secondi);
			strcat(VeryLargeString, string);
			format(string,sizeof(string),"{446ED1}Checkpoints: {8CE46C}%d\n",Race[IDCursa][CheckpointNr]+1);
			strcat(VeryLargeString, string);
			format(string,sizeof(string),"{446ED1}Posible Earning: {33AA33}${8CE46C}%s\n",FormatNumber(earning, 0, ','));
			strcat(VeryLargeString, string);
			strcat(VeryLargeString, "{446ED1}Bonus Earning: {33AA33}${8CE46C}250,000{446ED1} if you are holding still the Record.");
			ShowPlayerDialog(playerid,DIALOGID_NO_ACTION,DIALOG_STYLE_MSGBOX,"Race Info",VeryLargeString,"Ok","");
			clear.string(VeryLargeString);
		}
		else 
		{
			if(Race[IDCursa][Started])  {
				SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] There already is a race started. Wait its ending before loading another.");
				format(stringa,sizeof(stringa),"| Total Participants: {8ECE46}%d"ALB" |", Race[IDCursa][Participants]);
				SendClientMessage(playerid,COLOR_WHITE, stringa); 
			}
			else 
			{
				SendClientMessage(playerid,COLOR_WHITE,"[{A60099}FMARace{FFFFFF}] There already is a race loaded. To join FMARace type {8CE46C}/joinrace.");
				format(stringa,sizeof(stringa),"| Total Participants: {8ECE46}%d"ALB" | Ready: {8ECE46}%d"ALB" |",Race[IDCursa][Participants], Race[IDCursa][ParticipantsReady]);
				SendClientMessage(playerid,COLOR_WHITE, stringa); 
			}
		}
	}
	return true;
}

// EOF
