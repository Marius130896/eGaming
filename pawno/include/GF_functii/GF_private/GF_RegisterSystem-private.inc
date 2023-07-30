/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_RegisterSystem_included
	#endinput
#else
	#define GF_RegisterSystem_included
#endif

function CheckMySQLAccount(extraid) {
	new
		query[MAXO_TEXT];
	format(query, MAXO_TEXT, "SELECT * FROM `players` WHERE `Name` = '%s'", PlayerName(extraid));
	mysql_tquery(connectionHandle, query, "WhenAccountCheck", "d", extraid);
	clear.string(query);
	return true;
}

function WhenAccountCheck(playerid, password[]) {
	new
		string[MAXO_TEXT2];
	InterpolateCameraPos(playerid, 167.098159, -1421.648315, 82.077346, 349.565612, -1391.623168, 82.077346, 15000);
	InterpolateCameraLookAt(playerid, 171.344833, -1419.167724, 81.176048, 344.660125, -1391.467773, 81.122314, 15000);
	if(cache_num_rows()) {
	    PlayerInfo[playerid][pReg] = 1;
	}
	else if(!cache_num_rows()) {
		PlayerInfo[playerid][pReg] = 0;
	}
	if(!gPlayerLogged{playerid}) {
		SendClientMessage(playerid, COLOR_YELLOW, "Account data is loaded...");
		SendClientMessage(playerid, COLOR_YELLOW, "Wait for the box to enter your account password.");
		SendClientMessage(playerid, COLOR_YELLOW, "If you get a crash because of the game, we expect you to "gamemode_forum".");
	    if(PlayerInfo[playerid][pReg]) {
			PlayerInfo[playerid][pLastLogin] = cache_get_row_int(0, 10);
			format(string, MAXO_TEXT2, "{FFFFFF}Hello {DBED15}%s, {FFFFFF}welcome to the {88AA88}e{FFFFFF}Gaming {88AA88}RPG{FFFFFF}! Your last login date: {DBED15}%s\n\n{FFFFFF}Please login into your account by entering the password below:", PlayerName(playerid), DateToTimestamp(PlayerInfo[playerid][pLastLogin], 1));
			ShowPlayerDialog(playerid, DIALOGID_LOGIN, DIALOG_STYLE_PASSWORD, "Account Login", string, "Login", "Quit");
			GameTextForPlayer(playerid, "~w~Welcome ~n~ ~y~Enter password", 4000, 1);
	    }
	    else if(!PlayerInfo[playerid][pReg]) {
			format(string, MAXO_TEXT2, "Hello %s! This account is not registered in our database. \n\nPlease enter a password for this account in the box below:", PlayerName(playerid));
			ShowPlayerDialog(playerid, DIALOGID_REGISTER, DIALOG_STYLE_PASSWORD, "Account Register", string, "Register", "Quit");
		}
		clear.string(string);
	}
	return true;
}

function OnPlayerRegister(playerid, password[]) {
	InterpolateCameraPos(playerid, 322.030578, -1249.503173, 111.792312, 167.098159, -1421.648315, 82.077346, 15000);
	InterpolateCameraLookAt(playerid, 320.934448, -1254.075805, 110.092506, 171.352172, -1419.225341, 81.061035, 15000);
	if(IsPlayerConnected(playerid)) {
	    new
			string[MAXO_TEXT2];
		strmid(PlayerInfo[playerid][pPassword], password, 0, strlen(password), 255);
		mysql_format(connectionHandle, string, MAXO_TEXT2, "INSERT INTO `players` (`Name`, `Password`) VALUES ('%e', '%e')", PlayerName(playerid), password);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", ADDACCOUNT_THREAD_ID);
        format(string, MAXO_TEXT2, "Hello %s! This account is not registered in our database. \n\nPlease enter a password for this account in the box below:", PlayerName(playerid));
        ShowPlayerDialog(playerid, DIALOGID_LOGIN, DIALOG_STYLE_PASSWORD, "Account Login", string, "Login", "Quit");
		clear.string(string);
	}
	return true;
}

function OnPlayerLogin(playerid, password[]) {
	if(IsPlayerConnected(playerid)) {
		new query[MAXO_TEXT2];
		InterpolateCameraPos(playerid, 167.098159, -1421.648315, 82.077346, 349.565612, -1391.623168, 82.077346, 15000);
		InterpolateCameraLookAt(playerid, 171.344833, -1419.167724, 81.176048, 344.660125, -1391.467773, 81.122314, 15000);
		mysql_format(connectionHandle, query, MAXO_TEXT2, "SELECT * FROM `players` WHERE `Name` = '%e' AND `Password` = '%e'", PlayerName(playerid), password);
		mysql_tquery(connectionHandle, query, "WhenPlayerLogin", "i", playerid);
		clear.string(query);
	}
	return true;
}

function WhenPlayerLogin(playerid) {
	if(IsPlayerConnected(playerid)) {
		new
			string[MAXO_TEXT2];
		if(cache_num_rows()) {
			PlayerInfo[playerid][pSQLID] = cache_get_row_int(0, 0);
			cache_get_row(0, 1, PlayerName(playerid), .max_len = MAX_PLAYER_NAME);
			cache_get_row(0, 2, PlayerInfo[playerid][pPassword], .max_len = MAX_PASS_LENGHT);
			PlayerInfo[playerid][pLevel] = cache_get_row_int(0, 3);
			PlayerInfo[playerid][pCash] = cache_get_row_int(0, 4);
			PlayerInfo[playerid][pSex] = cache_get_row_int(0, 5);
			PlayerInfo[playerid][pAge] = cache_get_row_int(0, 6);
			PlayerInfo[playerid][pTut] = cache_get_row_int(0, 7);
			PlayerInfo[playerid][pSkin] = cache_get_row_int(0, 8);
			PlayerInfo[playerid][pReg] = cache_get_row_int(0, 9);
			//PlayerInfo[playerid][pLastLogin] - este deja folosita la dialogul de intampinare Login (nr. 10)
			cache_get_row(0, 11, PlayerInfo[playerid][pEmail], .max_len = MAXO_TEXT);
			cache_get_row(0, 12, PlayerInfo[playerid][pSecret], .max_len = MAXO_TEXT);
			PlayerInfo[playerid][pAdmin] = cache_get_row_int(0, 13);
			PlayerInfo[playerid][pHelper] = cache_get_row_int(0, 14);
			PlayerInfo[playerid][pLeader] = cache_get_row_int(0, 15);
			PlayerInfo[playerid][pFactiune] = cache_get_row_int(0, 16);
			PlayerInfo[playerid][pRank] = cache_get_row_int(0, 17);
			PlayerInfo[playerid][pTeam] = cache_get_row_int(0, 18);
			PlayerInfo[playerid][pAccount] = cache_get_row_int(0, 19);
			PlayerInfo[playerid][pExp] = cache_get_row_int(0, 20);
			PlayerInfo[playerid][pUpgradeP] = cache_get_row_int(0, 21);
			PlayerInfo[playerid][pSHealth] = cache_get_row_float(0, 22);
			PlayerInfo[playerid][pConnectTime] = cache_get_row_int(0, 23);
			PlayerInfo[playerid][pMute] = cache_get_row_int(0, 24);
			PlayerInfo[playerid][pMuteTime] = cache_get_row_int(0, 25);
			PlayerInfo[playerid][pWarnings] = cache_get_row_int(0, 26);
			PlayerInfo[playerid][pDrivingLicense] = cache_get_row_int(0, 27);
			PlayerInfo[playerid][pFlyingLicense] = cache_get_row_int(0, 28);
			PlayerInfo[playerid][pSailingLicense] = cache_get_row_int(0, 29);
			PlayerInfo[playerid][pPhousekey] = cache_get_row_int(0, 30);
			PlayerInfo[playerid][pPbizkey] = cache_get_row_int(0, 31);
			PlayerInfo[playerid][pPnumber] = cache_get_row_int(0, 32);
			PlayerInfo[playerid][pPhoneBook] = cache_get_row_int(0, 33);
			PlayerInfo[playerid][pWlvl] = cache_get_row_int(0, 34);
			PlayerInfo[playerid][pJailed] = cache_get_row_int(0, 35);
			PlayerInfo[playerid][pJailTime] = cache_get_row_int(0, 36);
			PlayerInfo[playerid][pDrugs] = cache_get_row_int(0, 37);
			PlayerInfo[playerid][pMats] = cache_get_row_int(0, 38);
			cache_get_row(0, 39, PlayerInfo[playerid][pFJoined], .max_len = 20);
			PlayerInfo[playerid][pPills] = cache_get_row_int(0, 40);
			PlayerInfo[playerid][pHeadValue] = cache_get_row_int(0, 41);
			PlayerInfo[playerid][pContracts] = cache_get_row_int(0, 42);
			PlayerInfo[playerid][pNewsSkill] = cache_get_row_int(0, 43);
			PlayerInfo[playerid][pFWarn] = cache_get_row_int(0, 44);
			PlayerInfo[playerid][pKills] = cache_get_row_int(0, 45);
			PlayerInfo[playerid][pDeaths] = cache_get_row_int(0, 46);
			PlayerInfo[playerid][pDustSkill] = cache_get_row_int(0, 47);
			PlayerInfo[playerid][pJob] = cache_get_row_int(0, 48);
			PlayerInfo[playerid][pFactionSpawn] = cache_get_row_int(0, 51);
			PlayerInfo[playerid][pActiveCounter] = cache_get_row_int(0, 52);
			PlayerInfo[playerid][pPayDayTime] = cache_get_row_int(0, 53);
			PlayerInfo[playerid][pActiveTime] = cache_get_row_int(0, 54);
			PlayerInfo[playerid][pPayCheck] = cache_get_row_int(0, 55);
			PlayerInfo[playerid][pFarmerSkill] = cache_get_row_int(0, 56);
			PlayerInfo[playerid][pCarJackerSkill] = cache_get_row_int(0, 57);
			PlayerInfo[playerid][pGiftPoints] = cache_get_row_int(0, 58);
			PlayerInfo[playerid][pCarSlots] = cache_get_row_int(0, 59);
			PlayerInfo[playerid][pNMute] = cache_get_row_int(0, 60);
			PlayerInfo[playerid][pDisable] = cache_get_row_int(0, 61);
			PlayerInfo[playerid][pDisableTime] = cache_get_row_int(0, 62);
			/* Incarcam misiunile si progresul din tabelul cu conturi */
			PlayerInfo[playerid][pDailyMission][0] = cache_get_row_int(0, 63);
			PlayerInfo[playerid][pDailyMission][1] = cache_get_row_int(0, 64);
			PlayerInfo[playerid][pProgress][0] = cache_get_row_int(0, 65);
			PlayerInfo[playerid][pProgress][1] = cache_get_row_int(0, 66);
			PlayerInfo[playerid][pNeedProgress][0] = cache_get_row_int(0, 67);
			PlayerInfo[playerid][pNeedProgress][1] = cache_get_row_int(0, 68);

			PlayerInfo[playerid][pTotalPD] = cache_get_row_int(0, 69);
			PlayerInfo[playerid][pLastDayOfPD] = cache_get_row_int(0, 70);
			PlayerInfo[playerid][pLastTimeOfPD] = cache_get_row_int(0, 71);
			PlayerInfo[playerid][pArmsDealerSkill] = cache_get_row_int(0, 72);
			PlayerInfo[playerid][pSweeperSkill] = cache_get_row_int(0, 73);
			PlayerInfo[playerid][pDrugsDealerSkill] = cache_get_row_int(0, 74);
			PlayerInfo[playerid][pFrequence] = cache_get_row_int(0, 75);
			PlayerInfo[playerid][pFreqNO] = cache_get_row_int(0, 76);
			PlayerInfo[playerid][pBiggestFish] = cache_get_row_int(0, 77);
			PlayerInfo[playerid][pFishSkill] = cache_get_row_int(0, 78);
			/*Referral System */
			PlayerInfo[playerid][pReferralID] = cache_get_row_int(0, 79);
			PlayerInfo[playerid][pReferralCash] = cache_get_row_int(0, 80);
			PlayerInfo[playerid][pReferralRespect] = cache_get_row_int(0, 81);
		}
		else
		{
		    format(string, MAXO_TEXT2, "%s, you incorrectly entered the password for this account.\nEnter the password for this account in the box below:", PlayerName(playerid));
			ShowPlayerDialog(playerid, DIALOGID_LOGIN, DIALOG_STYLE_PASSWORD, "Account Login", string, "Login", "Quit");
			return 1;
		}
		if(!PlayerInfo[playerid][pReg]) {
			PlayerInfo[playerid][pLevel] = 1;
			SafeGivePlayerMoney(playerid, 10000);
			PlayerInfo[playerid][pReg] = 1;
			PlayerInfo[playerid][pAccount] = 50000;
			PlayerInfo[playerid][pCarSlots] = 1;
			format(string, MAXO_TEXT2, "UPDATE players SET Level = %d, Reg = %d, Account = %d WHERE ID = %d", PlayerInfo[playerid][pLevel], PlayerInfo[playerid][pReg], PlayerInfo[playerid][pAccount], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(string, MAXO_TEXT, "UPDATE players SET CarSlots = %d, Registered = CURRENT_TIMESTAMP WHERE ID = %d", PlayerInfo[playerid][pCarSlots], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		}
		format(string, MAXO_TEXT2, "UPDATE players SET LastLogin = %d WHERE ID = %d", gLocalTimeStamp, PlayerInfo[playerid][pSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		/* Mesaje afisate dupa login */
		SendClientMessage(playerid, -1, "");
		SendClientMessage(playerid, -1, "");
		SendClientMessage(playerid, -1, "");
		SendClientMessage(playerid, -1, "");
		SendClientMessage(playerid, -1, "");
		format(string, sizeof(string), "SERVER: Welcome to the State of San Andreas, %s.", PlayerName(playerid));
		SendClientMessage(playerid, -1, string);
		SendClientMessage(playerid, -1, "");
		SendClientMessage(playerid, -1, "");
		SendClientMessage(playerid, -1, "");
		if(PlayerInfo[playerid][pAdmin]) {
			format(string, sizeof(string), "SERVER: You are logged in as Admin %d Level.", PlayerInfo[playerid][pAdmin]);
			SendClientMessage(playerid, -1, string);
		}
		SendClientMessage(playerid, -1, "");
		if(PlayerInfo[playerid][pHelper]) {
			format(string, sizeof(string), "SERVER: You are logged in as Helper %d Level.", PlayerInfo[playerid][pHelper]);
			SendClientMessage(playerid, -1, string);
		}
		if(PlayerInfo[playerid][pFactiune]) {
			format(string, MAXO_TEXT, "SERVER: You are in {F58C5B}%s{FFFFFF}, since {F58C5B}%s{FFFFFF}.", FactionInfo[PlayerInfo[playerid][pFactiune]][fName], PlayerInfo[playerid][pFJoined]);
			SendClientMessage(playerid, -1, string);
			new len = strlen(FactionInfo[PlayerInfo[playerid][pFactiune]][fAnnounce]);
			if(ISBetween(len, 5, 128)) {
				SendClientMessage(playerid, -1, "");
				format(string, MAXO_TEXT, "Faction ANNO: {FFFFFF}%s.", FactionInfo[PlayerInfo[playerid][pFactiune]][fAnnounce]);
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
			}
		}
		SendClientMessage(playerid, -1, "");
		/* Hai sa dam o misiune la logarea pe server */
		SendClientMessage(playerid, -1, "");
		if(PlayerInfo[playerid][pDailyMission][0] == -1 || PlayerInfo[playerid][pDailyMission][1] == -1)
			GivePlayerMission(playerid);
		CheckMissionStatus(playerid);
		CurrentMoney[playerid] = PlayerInfo[playerid][pCash];
		format(string, sizeof(string), "~y~welcome ~n~ ~w~%s", PlayerName(playerid));
		GameTextForPlayer(playerid, string, 5000, 1);
		ShowPlayerDateTime(playerid);
		SendClientMessage(playerid, -1, "");
		SetTimerEx("NotIsPlayerLogged", 100, false, "u", playerid);
		SetTimerEx("IsPlayerLogged", 3000, false, "u", playerid);
		StopAudioStreamForPlayer(playerid);
		if(PlayerInfo[playerid][pFactiune] == FACT_MEDIC) {
			if(TimpIncendiu)
				SetPlayerMapIcon(playerid, MAPICON_FIREPLACE,  HouseInfo[NumarCase][hEntrancex], HouseInfo[NumarCase][hEntrancey], HouseInfo[NumarCase][hEntrancez], 20, 0, MAPICON_GLOBAL_CHECKPOINT);
		}
		SetPlayerSpawnInfo(playerid, USE_RESPAWN);
		if(IsPlayerGangster(playerid))
			ShowTurfs(playerid), showTurfs{playerid} = true;
		if(PlayerInfo[playerid][pWlvl] > 0)
			SetPlayerWanted(playerid, INVALID_PLAYER_ID, PlayerInfo[playerid][pWlvl]);
		// Afisam textdraw-ul digital ce reprezinta viata/armura jucatorului
		TextDrawShowForPlayer(playerid, DigiHP[playerid]);
	    new Float:Armour;
		GetPlayerArmour(playerid, Armour);
		if(Armour >= 1) 
			TextDrawShowForPlayer(playerid, DigiAP[playerid]);
		else 
			TextDrawHideForPlayer(playerid, DigiAP[playerid]);
		clear.string(string);
	}
	return true;
}

function NotIsPlayerLogged(playerid) {
	TogglePlayerControllable(playerid, false);
	SendClientMessage(playerid, COLOR_YELLOW, "Loading player data...");
}

function IsPlayerLogged(playerid) {
	TogglePlayerControllable(playerid, true);
	gPlayerLogged{playerid} = true;
	SendClientMessage(playerid, COLOR_YELLOW, "Loading complete...");
}

stock iseMailadress(email[]) {
  	new len = strlen(email), cstate=0, i;
  	for(i = 0; i < len; i ++) {
	    if((cstate == 0 || cstate == 1) && (email[i] >= 'A' && email[i] <= 'Z')||(email[i] >= '0' && email[i] <= '9') || (email[i] >= 'a' && email[i] <= 'z')  || (email[i] == '.')  || (email[i] == '-')  || (email[i] == '_')) {
	    }
		else
		{
	       if ((cstate == 0) && (email[i] == '@')) {
	          cstate = 1;
	       }
		   else
		   {
	          return false;
	       }
	 	}
	}
  	if(cstate < 1) return false;
  	if(len < 6) return false;
  	if((email[len - 3] == '.') || (email[len - 4] == '.') || (email[len - 5] == '.')) return true;
  	return false;
}

stock RegOnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	#pragma unused listitem
	new
		string[MAXO_TEXT2], query[MAXO_TEXT];
	switch(dialogid) {
		case DIALOGID_REGISTER:
		{
			if(response) {
			    if(strlen(inputtext) >= 3 && strlen(inputtext) <= 20) {
					new tmppass[MAXO_TEXT];
				 	mysql_escape_string(inputtext, tmppass);
				 	if(strlen(tmppass) < 3) {
				        format(string, MAXO_TEXT2, "Hello %s! This account is not registered in our database. \n\nPlease enter a password for this account in the box below:", PlayerName(playerid));
				        ShowPlayerDialog(playerid, DIALOGID_LOGIN, DIALOG_STYLE_PASSWORD, "Account Login", string, "Login", "Quit");
					}
					OnPlayerRegister(playerid, tmppass);
				}
				else
				{
		 	        format(string, MAXO_TEXT2, "Hello %s! This account is not registered in our database. \n\nPlease enter a password for this account in the box below:", PlayerName(playerid));
					ShowPlayerDialog(playerid, DIALOGID_REGISTER, DIALOG_STYLE_PASSWORD, "Account Register", string, "Register", "Quit");
				}
				clear.string(string);
			} else Kick(playerid);
		}
		case DIALOGID_LOGIN:
		{
		    if(response) {
		        if(ISBetween(strlen(inputtext), 3, 20)) {
		             new tmppass[MAXO_TEXT];
					 mysql_escape_string(inputtext, tmppass);
					 if(strlen(tmppass) < 3) {
					    format(string, MAXO_TEXT2, "%s, you incorrectly entered the password for this account.\nEnter the password for this account in the box below:", PlayerName(playerid));
						ShowPlayerDialog(playerid, DIALOGID_LOGIN, DIALOG_STYLE_PASSWORD, "Account Login", string, "Login", "Quit");
					 }
					 OnPlayerLogin(playerid, tmppass);
		        }
				else
				{
				    format(string, MAXO_TEXT2, "%s, you incorrectly entered the password for this account.\nEnter the password for this account in the box below:", PlayerName(playerid));
					ShowPlayerDialog(playerid, DIALOGID_LOGIN, DIALOG_STYLE_PASSWORD, "Account Login", string, "Login", "Quit");
				}
				clear.string(string);
		    } else Kick(playerid);
		}
		case DIALOGID_SEX:
		{
			if(response) {
			    SendClientMessage(playerid, -1, "SERVER: You've set your character's gender to male.");
                PlayerInfo[playerid][pSex] = 1;
			}
			else
			{
		        SendClientMessage(playerid, -1, "SERVER: You've set your character's gender to female.");
		        PlayerInfo[playerid][pSex] = 2;
			}
			InterpolateCameraPos(playerid, 611.223022, -1245.331176, 67.418869, 767.808532, -1470.823730, 37.281574, 15000);
			InterpolateCameraLookAt(playerid, 614.834228, -1248.154296, 65.421524, 763.657592, -1468.047485, 37.031677, 15000);
			ShowPlayerDialog(playerid, DIALOGID_AGE, DIALOG_STYLE_INPUT, "Enter your age", "How old are you ?", "Continue", "");
   			format(query, MAXO_TEXT, "UPDATE players SET Sex = %d WHERE ID = %d", PlayerInfo[playerid][pSex], PlayerInfo[playerid][pSQLID]);
   			mysql_tquery(connectionHandle, query, "NoReturnThread", "d", UPDATE_THREAD_ID);
			clear.string(query);
		}
		case DIALOGID_AGE:
		{
		    if(response) {
		        if(ISBetween(strval(inputtext), 10, 45)) {
		            format(string, sizeof(string), "SERVER: So, you have %s years,", inputtext);
		            SendClientMessage(playerid, -1, string);
					PlayerInfo[playerid][pAge] = strval(inputtext);
					format(query, MAXO_TEXT, "UPDATE players SET Age = %d WHERE ID = %d", PlayerInfo[playerid][pAge], PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, query, "NoReturnThread", "d", UPDATE_THREAD_ID);
					InterpolateCameraPos(playerid, 767.808471, -1470.823608, 37.281585, 1056.167846, -1548.353759, 77.369461, 15000);
					InterpolateCameraLookAt(playerid, 763.606811, -1468.114624, 37.195652, 1052.093994, -1546.000244, 75.677009, 15000);
					ShowPlayerDialog(playerid, DIALOGID_EMAIL, DIALOG_STYLE_INPUT, "Enter your email address", "You must enter a valid email address.\nWhat is your email address ?", "Continue", "");
					clear.string(query);
				} else ShowPlayerDialog(playerid, DIALOGID_AGE, DIALOG_STYLE_INPUT, "Enter your age", "How old are you ?\nThe age must be between 10-45 years.", "Continue", "");
		    } else ShowPlayerDialog(playerid, DIALOGID_AGE, DIALOG_STYLE_INPUT, "Enter your age", "How old are you ?\nThe age must be between 10-45 years.", "Continue", "");
		}
		case DIALOGID_EMAIL:
		{
		    if(response) {
		        if(iseMailadress(inputtext) && ISBetween(strlen(inputtext), 4, 64)) {
		            strmid(PlayerInfo[playerid][pEmail], inputtext, 0, strlen(inputtext), MAXO_TEXT);
		            format(string, sizeof(string), "SERVER: So, you have your email address %s.", inputtext);
		            SendClientMessage(playerid, -1, string);
					format(query, MAXO_TEXT, "UPDATE players SET Email = '%s' WHERE ID = %d", inputtext, PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, query, "NoReturnThread", "d", UPDATE_THREAD_ID);
					InterpolateCameraPos(playerid, 1056.166992, -1548.353515, 77.369338, 769.906982, -1487.664184, 34.512619, 15000);
					InterpolateCameraLookAt(playerid, 1051.557373, -1546.733764, 76.307182, 774.182922, -1485.351196, 33.343845, 15000);
		            ShowPlayerDialog(playerid, DIALOGID_SWORD, DIALOG_STYLE_INPUT, "Enter your secret word", "What is your word secret ?\nThis word will be necessary more later, don't forget it.", "Finish", "");
					clear.string(string);
					clear.string(query);
				} else ShowPlayerDialog(playerid, DIALOGID_EMAIL, DIALOG_STYLE_INPUT, "Enter your email address", "This email address is incorrectly!\nWhat is your email address ?", "Continue", "");
		    } else ShowPlayerDialog(playerid, DIALOGID_EMAIL, DIALOG_STYLE_INPUT, "Enter your email address", "You must enter a valid email address.\nWhat is your email address ?", "Continue", "");
		}
		case DIALOGID_SWORD:
		{
		    if(response) {
				if(ISBetween(strlen(inputtext), 4, 64)) {
		            strmid(PlayerInfo[playerid][pSecret], inputtext, 0, strlen(inputtext), MAXO_TEXT);
 		            format(string, MAXO_TEXT, "SERVER: So, your word secret is %s.", inputtext);
		            SendClientMessage(playerid, -1, string);
					format(query, MAXO_TEXT, "UPDATE players SET SWord = '%s' WHERE ID = %d", inputtext, PlayerInfo[playerid][pSQLID]);
					mysql_tquery(connectionHandle, query, "NoReturnThread", "d", UPDATE_THREAD_ID);
					ShowPlayerDialog(playerid, DIALOGID_REFERRAL_PLAYER, DIALOG_STYLE_INPUT, "Set your Referral", "If you has beed bring on server by someone, type below, his Referral ID.\nIf you hasn't been bring by someone, press Skip button:", "Finish", "Skip");
					clear.string(string);
					clear.string(query);
				} else ShowPlayerDialog(playerid, DIALOGID_SWORD, DIALOG_STYLE_INPUT, "Enter your secret word", "What is your word secret ?\nThis word will be necessary more later, don't forget it.", "Finish", "");
		    } else ShowPlayerDialog(playerid, DIALOGID_SWORD, DIALOG_STYLE_INPUT, "Enter your secret word", "You must enter an secret word for this account.\nWhat is your word secret ?\nThis word will be necessary more later, don't forget it.", "Finish", "");
		}
		case DIALOGID_REFERRAL_PLAYER: {
			if(response) { 
				if(isNumeric(inputtext)) {
					if(PlayerInfo[playerid][pSQLID] != strval(inputtext)) {
						mysql_format(connectionHandle, string, MAXO_TEXT, "SELECT ID FROM players WHERE ID = %d", strval(inputtext));
						mysql_tquery(connectionHandle, string, "ValidReferral", "d", playerid);
						clear.string(string);
					} else ShowPlayerDialog(playerid, DIALOGID_REFERRAL_PLAYER, DIALOG_STYLE_INPUT, "Set your Referral", "You can't use your Referral ID!\nIf you has beed bring on server by someone, type below, his Referral ID.\nIf you hasn't been bring by someone, press Skip button:", "Finish", "Skip");
				} else ShowPlayerDialog(playerid, DIALOGID_REFERRAL_PLAYER, DIALOG_STYLE_INPUT, "Set your Referral", "This Referral ID is incorrect, please try again!\nIf you has beed bring on server by someone, type below, his Referral ID.\nIf you hasn't been bring by someone, press Skip button:", "Finish", "Skip");
			}
			else
			{
				ClearChatBox(playerid, 15);
				CreateCP(playerid,328.616,-1512.91,36.0391,1.5,checkpointNoAction,CP_NO_ACTION);
				TogglePlayerSpectating(playerid, false);
				TogglePlayerControllable(playerid, true);
				SetCameraBehindPlayer(playerid);
				SendClientMessage(playerid, COLOR_ORANGE, "Mergi la checkpointul rosu marcat pe minimap. Acolo vei sustine examenul pentru licenta de conducere.");
				PlayerInfo[playerid][pSkin] = 264;
				SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
				PlayerInfo[playerid][pTut] = 1;
				format(string, MAXO_TEXT, "UPDATE players SET Tut = 1 WHERE ID = %d", PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				format(string, MAXO_TEXT2, "UPDATE players SET Skin = %d WHERE ID = %d", PlayerInfo[playerid][pSkin], PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
				SetPlayerSpawnInfo(playerid);	
				clear.string(string);
			}
		}
	}
	return true;
}


// End Of File ....
