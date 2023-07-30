#if defined GF_RobberySystem_included
	#endinput
#else
	#define GF_RobberySystem_included
#endif

#define TOTAL_ROB_POINTS 10
#define LEVEL_ROB_NECESSARY 5
#define MINIMUM_ROB_MEMBERS 2
#define MAXIMUM_ROB_MEMBERS 4

enum Robbery {
	bool:roActive,
	roParticipant1,
	roParticipant2,
	roParticipant3,
	roParticipant4,
	roTotalParticipants,
	roBizRobbed
};
new RobInfo[Robbery], bool:IsPlayerRobber[MAX_PLAYERS];

stock ResetRobParticipants() {
	RobInfo[roParticipant1] = INVALID_PLAYER_ID;
	RobInfo[roParticipant2] = INVALID_PLAYER_ID;
	RobInfo[roParticipant3] = INVALID_PLAYER_ID;
	RobInfo[roParticipant4] = INVALID_PLAYER_ID;
	RobInfo[roTotalParticipants] = 0;
	return true;
}

stock ResetRobVariables() {
	ResetRobParticipants();
	RobInfo[roActive] = false;
	RobInfo[roBizRobbed] = 0;
	return true;
}

function InoviceTheRobbers() {
	new string[MAXO_TEXT];
	if(RobInfo[roActive] == true) {
		switch(RobInfo[roTotalParticipants]) {
			case MINIMUM_ROB_MEMBERS: {
				format(string, MAXO_TEXT, "ALERT! %s, %s and %s started to rob the %s.", PlayerName(RobInfo[roParticipant1]), PlayerName(RobInfo[roParticipant2]), PlayerName(RobInfo[roParticipant3]), BizInfo[RobInfo[roBizRobbed]][bDescription]);
				SendClientMessageToAll(COLOR_LIGHTRED, string);
				PlayerInfo[RobInfo[roParticipant1]][pWlvl] = 6;
				PlayerInfo[RobInfo[roParticipant2]][pWlvl] = 6;
				PlayerInfo[RobInfo[roParticipant3]][pWlvl] = 6;
				SetPlayerWanted(RobInfo[roParticipant1], INVALID_PLAYER_ID, PlayerInfo[RobInfo[roParticipant1]][pWlvl]);
				SetPlayerWanted(RobInfo[roParticipant2], INVALID_PLAYER_ID, PlayerInfo[RobInfo[roParticipant2]][pWlvl]);
				SetPlayerWanted(RobInfo[roParticipant3], INVALID_PLAYER_ID, PlayerInfo[RobInfo[roParticipant2]][pWlvl]);
				SendClientMessage(RobInfo[roParticipant1], COLOR_LIGHTRED, "You've commited a crime: You robbed the Bank +6 Wanted Level.");
				SendClientMessage(RobInfo[roParticipant2], COLOR_LIGHTRED, "You've commited a crime: You robbed the Bank +6 Wanted Level.");
				SendClientMessage(RobInfo[roParticipant3], COLOR_LIGHTRED, "You've commited a crime: You robbed the Bank +6 Wanted Level.");
				IsPlayerRobber[RobInfo[roParticipant1]] = true;
				IsPlayerRobber[RobInfo[roParticipant2]] = true;
				IsPlayerRobber[RobInfo[roParticipant3]] = true;
				SendClientMessage(RobInfo[roParticipant1], COLOR_ORANGE, "Rob Information: Now, you have to go to open the safe.");
				format(string, MAXO_TEXT, "Rob Information: After %s opens the safe, go to put the money in the bag.", PlayerName(RobInfo[roParticipant1]));
				SendClientMessage(RobInfo[roParticipant2], COLOR_ORANGE, string);
				//ApplyAnimation(RobInfo[roParticipant1], "ROB_BANK", "CAT_Safe_Open", 4.0, 1, 0, 0, 0, 0, 1);
				clear.string(string);
			}
		}
	}
	return true;
}

COMMAND:rob(playerid, params[]) {
	new string[MAXO_TEXT], idbiz = PlayerInfo[playerid][pInBizzID], participants = 0;
	if(!IsPlayerCop(playerid)) {
		if(PlayerInfo[playerid][pWlvl] < 1) {
			if(PlayerInfo[playerid][pRobPoints] >= TOTAL_ROB_POINTS) {
				if(PlayerInfo[playerid][pLevel] >= LEVEL_ROB_NECESSARY) {
					if(BizInfo[idbiz][bType] == BIZ_TYPE_BANK) {
						if(IsPlayerRobber[playerid] == false) {
							if(RobInfo[roActive] == false) {
								foreach(Player, i) {
									if(PlayerInfo[i][pInBizzID] == PlayerInfo[playerid][pInBizzID]) {
										if(PlayerInfo[i][pRobPoints] >= TOTAL_ROB_POINTS) {
											if(PlayerInfo[i][pWlvl] < 1) {
												if(PlayerInfo[i][pLevel] >= LEVEL_ROB_NECESSARY) {
													if(!IsPlayerCop(i)) {
														if(IsPlayerRobber[i] == false) {
															participants ++;
															if(RobInfo[roParticipant1] == INVALID_PLAYER_ID)
																RobInfo[roParticipant1] = i;
															else if(RobInfo[roParticipant2] == INVALID_PLAYER_ID)
																RobInfo[roParticipant2] = i;
															else if(RobInfo[roParticipant3] == INVALID_PLAYER_ID)
																RobInfo[roParticipant3] = i;
															else if(RobInfo[roParticipant4] == INVALID_PLAYER_ID)
																RobInfo[roParticipant4] = i;
															RobInfo[roBizRobbed] = idbiz;	
														} else SendClientMessage(playerid, COLOR_GRAD1, "Someone from inside bank is a robber."), ResetRobParticipants();											
													} else SendClientMessage(playerid, COLOR_GRAD1, "Someone from inside bank is cop."), ResetRobParticipants();
												} else SendClientMessage(playerid, COLOR_GRAD1, "Someone from inside bank haven't the level necessary (5)."), ResetRobParticipants();
											} else SendClientMessage(playerid, COLOR_GRAD1, "Someone from inside bank, are is wanted."), ResetRobParticipants();
										} else SendClientMessage(playerid, COLOR_GRAD1, "Someone from inside bank, haven't 10+ Rob Points."), ResetRobParticipants();
									}
								}
								if(participants == MINIMUM_ROB_MEMBERS) {
									SetTimer("InoviceTheRobbers", 60000, false);	
									SendClientMessage(RobInfo[roParticipant1], COLOR_LIGHTRED, "TEAM: We have 60 seconds until when to cops will be announced.");
									SendClientMessage(RobInfo[roParticipant2], COLOR_LIGHTRED, "TEAM: We have 60 seconds until when to cops will be announced.");
									SendClientMessage(RobInfo[roParticipant3], COLOR_LIGHTRED, "TEAM: We have 60 seconds until when to cops will be announced.");
									RobInfo[roParticipant4] = INVALID_PLAYER_ID;	
									RobInfo[roActive] = true;
									RobInfo[roTotalParticipants] = MINIMUM_ROB_MEMBERS;
									PlayerInfo[RobInfo[roParticipant1]][pRobPoints] -= 5;
									PlayerInfo[RobInfo[roParticipant2]][pRobPoints] -= 5;
									PlayerInfo[RobInfo[roParticipant3]][pRobPoints] -= 5;
									format(string, MAXO_TEXT, "UPDATE players SET RobPoints = %d WHERE ID = %d", PlayerInfo[RobInfo[roParticipant1]][pRobPoints], PlayerInfo[RobInfo[roParticipant1]][pSQLID]);
									mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
									format(string, MAXO_TEXT, "UPDATE players SET RobPoints = %d WHERE ID = %d", PlayerInfo[RobInfo[roParticipant2]][pRobPoints], PlayerInfo[RobInfo[roParticipant2]][pSQLID]);
									mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
									format(string, MAXO_TEXT, "UPDATE players SET RobPoints = %d WHERE ID = %d", PlayerInfo[RobInfo[roParticipant3]][pRobPoints], PlayerInfo[RobInfo[roParticipant3]][pSQLID]);
									mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
									clear.string(string);
								}
							} else SendClientMessage(playerid, COLOR_GRAD1, "The bank is already robbed.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "You rob the bank already.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "You have to be in the bank to start the robbery.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You need Level 5 to rob the bank.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "You need 10+ Rob Points to rob the bank.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command, you're wanted.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command, you're cop.");
	return true;
}

// End Of File ...
