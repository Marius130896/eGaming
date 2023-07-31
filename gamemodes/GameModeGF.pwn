// This is a comment
// uncomment the line below if you want to write a filterscript
//#define FILTERSCRIPT

// ---------
// eGaming RPG GodFather - SA:MP 2009-2019 (c) - Kurama - eGaming TEAM
//----------

// -- versiunea core-ului
// ---- Tasta F6 in Notepad ++ acceseaza compilatorul
// -- GameMode created by Kurama --
// -- Creation on date: January 2018 --

//#define _srv_official "da"

#define _srv_test "da"

#if defined _srv_official
	#define gamemode_version "eGaming RPG v4 - Rebuild"
#else
	#define gamemode_version ""server_Tname" v.Test-"
#endif

#define server_Tname "eGaming RPG"
#define server_name "eGaming v4"
#define gamemode_map "LS | SF"
#define gamemode_forum "http://forum.eGaming.ro"

// vom pune ca si include principal aici pentru a prelua toate datele
// fiecare sistem/definitie sau comanda este preluat din INC-ul cu denumirile cat mai sugerabile
// sistemele vor fi preluate atat din partea publica a GM-ului cat si din partea privata
//===============================================================================================
//									** SERVER BASE INCLUDE **
#include <GF_Kurama_Base_GM>
//===============================================================================================

stock SetPlayerSpawnInfo(playerid, spawn = USE_RESPAWN) {
	if(!IsPlayerNPC(playerid)) {
		if(!Spectated[playerid][Command]) {
			if(!PlayerInfo[playerid][pTut] || !PlayerInfo[playerid][pReg]) {
				ShowPlayerDialog(playerid, DIALOGID_SEX, DIALOG_STYLE_MSGBOX, "Sex Selecting", "Which of these are you ?", "male", "female");
			}
			if(PlayerInfo[playerid][pJailed] != 0) {
				if(PlayerInfo[playerid][pJailed] == 1) PutPlayerInCell(playerid), TogglePlayerControllable(playerid, true);
				else if(PlayerInfo[playerid][pJailed] == 2) SetSpawnInfo(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pSkin], 107.2300, 1920.6311, 18.5208, 0.0, 0, 0, 0, 0, 0, 0), TogglePlayerControllable(playerid, false);
			}
			else
			{
				new casa = PlayerInfo[playerid][pPhousekey], factiune = PlayerInfo[playerid][pFactiune];
				if(casa && !PlayerInfo[playerid][pSpawnChange])
					SetSpawnInfo(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pSkin], HouseInfo[casa][hEntrancex], HouseInfo[casa][hEntrancey], HouseInfo[casa][hEntrancez]+0.3, 0, FactionInfo[factiune][fWeapon1], FactionInfo[factiune][fAmmo1], FactionInfo[factiune][fWeapon2], FactionInfo[factiune][fAmmo2], FactionInfo[factiune][fWeapon3], FactionInfo[factiune][fAmmo3]), SafeSetPlayerInterior(playerid, 0), SafeSetPlayerVirtualWorld(playerid, 0);
				else
				{
					if(!PlayerInfo[playerid][pFactionSpawn])
						SetSpawnInfo(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pSkin], FactionInfo[factiune][fSpawnx], FactionInfo[factiune][fSpawny], FactionInfo[factiune][fSpawnz]+0.3, FactionInfo[factiune][fSpawnrot], FactionInfo[factiune][fWeapon1], FactionInfo[factiune][fAmmo1], FactionInfo[factiune][fWeapon2], FactionInfo[factiune][fAmmo2], FactionInfo[factiune][fWeapon3], FactionInfo[factiune][fAmmo3]);
					else
						SetSpawnInfo(playerid, PlayerInfo[playerid][pTeam], PlayerInfo[playerid][pSkin], FactionInfo[factiune][fSpawnx2], FactionInfo[factiune][fSpawny2], FactionInfo[factiune][fSpawnz2]+0.3, FactionInfo[factiune][fSpawnrot2], FactionInfo[factiune][fWeapon1], FactionInfo[factiune][fAmmo1], FactionInfo[factiune][fWeapon2], FactionInfo[factiune][fAmmo2], FactionInfo[factiune][fWeapon3], FactionInfo[factiune][fAmmo3]);

				}
			}
			if(spawn == USE_RESPAWN)
				SpawnPlayer(playerid);
		}
	}
	return true;
}

stock ShowStats(playerid, targetid) {
	new
		string[MAXO_TEXT], rtext[31], factiune = PlayerInfo[targetid][pFactiune],
		jobID[MAX_PLAYER_NAME];
	if(IsPlayerConnected(playerid) && IsPlayerConnected(targetid)) {
		switch(PlayerInfo[targetid][pRank]) {
			case 0: format(rtext, 31, "%s", FactionInfo[factiune][fRank0]);
			case 1: format(rtext, 31, "%s", FactionInfo[factiune][fRank1]);
			case 2: format(rtext, 31, "%s", FactionInfo[factiune][fRank2]);
			case 3: format(rtext, 31, "%s", FactionInfo[factiune][fRank3]);
			case 4: format(rtext, 31, "%s", FactionInfo[factiune][fRank4]);
			case 5: format(rtext, 31, "%s", FactionInfo[factiune][fRank5]);
			case 6: format(rtext, 31, "%s", FactionInfo[factiune][fRank6]);
		}
		switch(PlayerInfo[targetid][pJob]) {
			case JOB_NONE: jobID = "None";
			case JOB_FARMER: jobID = "Farmer";
			case JOB_SWEEPER: jobID = "Street Sweeper";
			case JOB_DUSTMAN: jobID = "Dustman";
			case JOB_TRUCKER: jobID = "Trucker";
			case JOB_CARJACKER: jobID = "Car Jacker";
			case JOB_ARMSDEALER: jobID = "Arms Dealer";
			case JOB_DRUGSDEALER: jobID = "Drugs Dealer";
		}
		SendClientMessage(playerid, COLOR_GREEN, "_______________________________________________________________________");
		format(string, MAXO_TEXT, "xxx [ %s (Referral ID: %d) - Level %d, %s %s ] xxx", PlayerName(targetid), PlayerInfo[targetid][pSQLID], PlayerInfo[targetid][pLevel], FactionInfo[PlayerInfo[targetid][pFactiune]][fName], rtext);
		SendClientMessage(playerid, COLOR_LIGHTGREEN, string);
		format(string, MAXO_TEXT, "» Age:[%d] Cash:[$%s] Bank:[$%s] SpawnHealth:[%.1f] Phone:[%d] Pills:[%d]", PlayerInfo[targetid][pAge], FormatNumber(PlayerInfo[targetid][pCash], 0, '.'), FormatNumber(PlayerInfo[targetid][pAccount], 0, '.'), PlayerInfo[targetid][pSHealth], PlayerInfo[targetid][pPnumber], PlayerInfo[targetid][pPills]);
		SendClientMessage(playerid, COLOR_GRAD1, string);
		format(string, MAXO_TEXT, "» Respect:[%d/%d] NextLevel:[$%s] Warnings:[%d] OnlineHours:[%d] Drugs:[%d grams] Materials:[%d] WantedLevel:[%d]", PlayerInfo[targetid][pExp], (PlayerInfo[targetid][pLevel]+1)*levelexp, FormatNumber((PlayerInfo[targetid][pLevel]+1)*levelcost, 0, '.'), PlayerInfo[targetid][pWarnings], PlayerInfo[targetid][pConnectTime], PlayerInfo[targetid][pDrugs], PlayerInfo[targetid][pMats], PlayerInfo[targetid][pWlvl]);
		SendClientMessage(playerid, COLOR_GRAD2, string);
		format(string, MAXO_TEXT, "» Contracts:[%d] FactionWarn:[%d/3] Kills:[%d] Deaths:[%d] Job:[%s] GiftPoints:[%d] CarSlots:[%d]", PlayerInfo[targetid][pContracts], PlayerInfo[targetid][pFWarn], PlayerInfo[targetid][pKills], PlayerInfo[targetid][pDeaths], jobID, PlayerInfo[targetid][pGiftPoints], PlayerInfo[targetid][pCarSlots]);
		SendClientMessage(playerid, COLOR_GRAD3, string);
		if(PlayerInfo[targetid][pAdmin]) {
			format(string, MAXO_TEXT, "» Phousekey:[%d] Pbizkey:[%d]", PlayerInfo[targetid][pPhousekey], PlayerInfo[targetid][pPbizkey]);
			SendClientMessage(playerid, COLOR_GRAD5, string);
		}
		SendClientMessage(playerid, COLOR_GREEN, "_______________________________________________________________________");
		clear.string(rtext);
		clear.string(jobID);
		clear.string(string);
	}
	return true;
}

function PlayerPlayMusic(playerid) {
	if(IsPlayerConnected(playerid)) {
		SetTimer("StopMusic", 5000, 0);
		PlayerPlaySound(playerid, 1068, 0.0, 0.0, 0.0);
	}
}

function StopMusic() {
	foreach(Player, i) {
		if(IsPlayerConnected(i)) {
			PlayerPlaySound(i, 1069, 0.0, 0.0, 0.0);
		}
	}
}

function Wnews() {
	new
		rand = random(sizeof(gRandomWeatherIDs)), strout[MAXO_TEXT];
	SetWeather(gRandomWeatherIDs[rand][wt_id]);
	format(strout, MAXO_TEXT, "NR: Possible weather forecast, coming up: %s", gRandomWeatherIDs[rand][wt_text]);
	SendClientMessageToAll(COLOR_NEWS2, strout);
	clear.string(strout);
}

function HelperToAll() {
	foreach(Player, i) {
		if(1 <= PlayerInfo[i][pHelper] <= 1337 || PlayerInfo[i][pLevel] >= 1) {
			SendClientMessage(i, COLOR_YELLOW2, "[Helper Bot: Pentru intrebari / probleme / nelamuriri tastati /needhelp ]");
			SendClientMessage(i, COLOR_YELLOW2, "[Helper Bot: /needhelp aiurea / din mers / pentru bani se pedepseste cu /disable ]");
		}
		GenFireMission();
	}
}

function SendMSG() {
	new randMSG = random(sizeof(RandomMSG)), string[MAXO_TEXT2];
	format(string, MAXO_TEXT2, ""ALBASTRU2"(( "PORTOCALIU"INFO: {FFFFFF}%s "ALBASTRU2"))", RandomMSG[randMSG]);
    SendClientMessageToAll(COLOR_LIGHTBLUE, string);
    clear.string(string);
	return true;
}

function SearchingHit(playerid) {
	new string[MAXO_TEXT], searchhit = 0;
	foreach(Player, i) {
		if(searchhit == 0) {
			if(PlayerInfo[i][pHeadValue] > 0 && GotHit[i] == 0 && PlayerInfo[i][pFactiune] != FACT_HITMAN) {
				searchhit = 1;
				hitfound = 1;
				HitM = i;
				foreach(Player, k) {
					if(PlayerInfo[k][pFactiune] == FACT_HITMAN) {
						SendClientMessage(k, COLOR_WHITE, "|__________________ Hitman Agency News __________________|");
						SendClientMessage(k, COLOR_LIGHTBLUE, "*** Incoming Message: A Hit has become available. ***");
						format(string, MAXO_TEXT, "Person: %s | ID: %d | Value: $%s", PlayerName(i), i, FormatNumber(PlayerInfo[i][pHeadValue], 0, '.'));
						SendClientMessage(k, COLOR_LIGHTBLUE, string);
						SendClientMessage(k, COLOR_YELLOW, "Use Givehit hitmanid, to assign the Contract to one of the Hitmans.");
						SendClientMessage(k, COLOR_WHITE, "|________________________________________________________|");
					}
				}
				return false;
			}
		}
	}
	if(searchhit == 0)
		return SendClientMessage(playerid, COLOR_GRAD1, "No Contracts available !");
	clear.string(string);
	return false;
}

function RingToner() {
	foreach (new i : Player) {
	    if(IsPlayerConnected(i)) {
			if(RingTone[i] != 6 && RingTone[i] != 0 && RingTone[i] < 11) {
				RingTone[i] = RingTone[i] -1;
				PlayerPlaySound(i, 1138, 0.0, 0.0, 0.0);
			}
			if(RingTone[i] == 6) {
				RingTone[i] = RingTone[i] -1;
			}
			if(RingTone[i] == 20) {
				RingTone[i] = RingTone[i] -1;
				PlayerPlaySound(i, 1139, 0.0, 0.0, 0.0);
			}
		}
	}
	SetTimer("RingTonerRev", 1000, 0);
	return 1;
}

function RingTonerRev() {
	foreach (new i : Player) {
	    if(IsPlayerConnected(i)) {
			if(RingTone[i] != 5 && RingTone[i] != 0 && RingTone[i] < 10) {
				RingTone[i] = RingTone[i] -1;
				PlayerPlaySound(i, 1137, 0.0, 0.0, 0.0);
			}
			if(RingTone[i] == 5) {
				RingTone[i] = RingTone[i] -1;
			}
			if(RingTone[i] == 19) {
				PlayerPlaySound(i, 1139, 0.0, 0.0, 0.0);
				RingTone[i] = 0;
			}
		}
	}
	SetTimer("RingToner", 1000, 0);
	return 1;
}

main() {
	print("\n---------------------------------------");
	print("Running "gamemode_version" - by Kurama \n");
	print("---------------------------------------\n");
}

public OnGameModeInit() {
	new string[64], parola[20];
	format(mapname, MAXO_TEXT1, "mapname %s", gamemode_map);
	SendRconCommand(mapname);
	SetWeather(3);
	MySQLConnect(MYSQL_HOST, MYSQL_USER, MYSQL_DATA, MYSQL_PASS);
	mysql_log(LOG_ERROR | LOG_WARNING, LOG_TYPE_HTML);
	AntiDeAMX();

	LoadFactions();
	LoadPickups();
	LoadObjects();
	LoadVehicles();
	LoadHouses();
	LoadBiz();
	LoadSkins();
	LoadTurf();
	nodmzone = GangZoneCreate(-2081.805, -139.7016, -1904.122, 341.584);
	nodmzone2 = GangZoneCreate(1200.85, -1433.15, 1295.92, -1271.3);
	LoadSafes();
	LoadJobs();
	LoadDealership();
	WlvlInit();
	LoadProdsGuns();
	LoadProdsBurger();
	LoadPrItemsThread();
	RaceSysInit();
	SetTimerEx("LoadTimersThread", 300, false, "i", 0);
	SetTimerEx("LoadTimersThread", 400, false, "i", 1);
	SetTimerEx("LoadTimersThread", 500, false, "i", 2);
	SetTimerEx("LoadTimersThread", 600, false, "i", 3);
	SetTimerEx("LoadTimersThread", 700, false, "i", 4);
	SetTimerEx("LoadTimersThread", 800, false, "i", 5);
	SetTimerEx("LoadTimersThread", 900, false, "i", 6);
	GetConsoleVarAsString("password", parola, sizeof(parola));
	#if defined _srv_official
		getdate(gYears, gMonths, gDays);
		format(string, 64, "eGaming.ro, %02d/%02d/%04d %02d:%02d", gDays, gMonths, gYears, gHours, gMinutes);
		if(!parola[0] || !strcmp(parola, "test037rpg", true)) {
			if(!strcmp(parola, "test037rpg", true)) {
				print("ServerUnlocked - called (26) seconds...");
				SetTimerEx("LoadTimersThread", 26000, false, "i", 7);
			} else SendRconCommand("password test037rp");
		}
	#else
		gettime(gHours, gMinutes, gSeconds);
		format(string, 64, "%s%02d.%02d", gamemode_version, gHours, gMinutes);
		SendRconCommand("password test037rpg");
	#endif
	ResetRobVariables();

	gLocalTimeStamp = gettime(gHours, gMinutes, gSeconds);
	SetGameModeText(string);
	News[hTaken1] = 0; News[hTaken2] = 0;
	News[hTaken3] = 0; News[hTaken4] = 0; News[hTaken5] = 0;
	format(string, MAX_PLAYER_NAME, "Nothing");
	strmid(News[hAdd1], string, 0, strlen(string), 255);
	strmid(News[hAdd2], string, 0, strlen(string), 255);
	strmid(News[hAdd3], string, 0, strlen(string), 255);
	strmid(News[hAdd4], string, 0, strlen(string), 255);
	strmid(News[hAdd5], string, 0, strlen(string), 255);
	format(string, MAX_PLAYER_NAME, "No-one");
	strmid(News[hContact1], string, 0, strlen(string), 255);
	strmid(News[hContact2], string, 0, strlen(string), 255);
	strmid(News[hContact3], string, 0, strlen(string), 255);
	strmid(News[hContact4], string, 0, strlen(string), 255);
	strmid(News[hContact5], string, 0, strlen(string), 255);

	new pl, mx = GetMaxPlayers();
	while(pl != mx) {
		turftxt[pl] = TextDrawCreate(10, 430, " ");
		TextDrawSetOutline(turftxt[pl], 1);
		TextDrawSetShadow(turftxt[pl], 1);
		TextDrawColor(turftxt[pl], COLOR_WHITE);

		spectatortxt[pl] = TextDrawCreate(200.000000, 400.000000, " ");
		TextDrawSetOutline(spectatortxt[pl], 0);
		TextDrawSetShadow(spectatortxt[pl], 1);

		TDWantedDown[pl] = TextDrawCreate(490.000000, 125.000000, "");
		TextDrawLetterSize(TDWantedDown[pl], 0.358124, 1.249999);
		TextDrawAlignment(TDWantedDown[pl], 1);
		TextDrawColor(TDWantedDown[pl], -1);
		TextDrawSetShadow(TDWantedDown[pl], 0);
		TextDrawSetOutline(TDWantedDown[pl], 1);
		TextDrawBackgroundColor(TDWantedDown[pl], 51);
		TextDrawFont(TDWantedDown[pl], 1);
		TextDrawSetProportional(TDWantedDown[pl], 1);

		pl ++;
	}
	FarmCantitateHambar = 0;

	EnableStuntBonusForAll(0);
	AllowInteriorWeapons(1);
	UsePlayerPedAnims();
    DisableInteriorEnterExits();
	LimitGlobalChatRadius(10.0);
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_STREAMED);
	LimitPlayerMarkerRadius(30.0);
	ManualVehicleEngineAndLights();
	Streamer_TickRate(100);

    HUMenu1 = CreateMenu("House Options", 1, 50.0, 180.0, 200.0, 200.0);
    AddMenuItem(HUMenu1, 0, "House Upgrades");
    HUMenu2 = CreateMenu("H. Upgrades", 1, 50.0, 180.0, 200.0, 200.0);
    AddMenuItem(HUMenu2, 0, "Heal Upgrade ~r~100.000~y~$");
    AddMenuItem(HUMenu2, 0, "Armor Upgrade ~r~50.000~y~$");

    MagazinMenu = CreateMenu("Store List", 1, 50.0, 180.0, 200.0, 200.0);
    AddMenuItem(MagazinMenu, 0, "Devices");

    MagazinMenu1 = CreateMenu("Devices", 1, 50.0, 180.0, 200.0, 200.0);
    AddMenuItem(MagazinMenu1, 0, "Cell Phone (1) ~r~500~y~$");
    AddMenuItem(MagazinMenu1, 0, "Phone Book (1) ~r~100~y~$");
    AddMenuItem(MagazinMenu1, 0, "Exit");

	Logo = TextDrawCreate(552.000000,21.000000,""#server_name"");
	TextDrawAlignment(Logo,0);
	TextDrawBackgroundColor(Logo,0x000000FF);
	TextDrawFont(Logo,1);
	TextDrawLetterSize(Logo,0.32,1.0);
	TextDrawColor(Logo,0x00D7D7FF);
	TextDrawSetOutline(Logo,1);
	TextDrawSetProportional(Logo,1);
	TextDrawSetShadow(Logo,1);

    //Hours
	TextdrawHour = TextDrawCreate(560.000000,29.000000,"_");
	TextDrawFont(TextdrawHour,2);
	TextDrawLetterSize(TextdrawHour,0.399999,1.800000);
	TextDrawColor(TextdrawHour,0xA5BA4BFF);
	TextDrawSetOutline(TextdrawHour,2);

	//zi
	TextdrawDay = TextDrawCreate(500.000000,10.000000,"--");
	TextDrawAlignment(TextdrawDay,0);
	TextDrawBackgroundColor(TextdrawDay,0x000000FF);
	TextDrawFont(TextdrawDay,2);
	TextDrawLetterSize(TextdrawDay,0.44,1.2);
	TextDrawColor(TextdrawDay,0xA5BA4BFF);
	TextDrawSetOutline(TextdrawDay,1);
	TextDrawSetProportional(TextdrawDay,1);
	TextDrawSetShadow(TextdrawDay,1);

	//luna
	TextdrawMonth = TextDrawCreate(530.000000,10.000000,"---------");
	TextDrawAlignment(TextdrawMonth,0);
	TextDrawBackgroundColor(TextdrawMonth,0x000000FF);
	TextDrawFont(TextdrawMonth,2);
	TextDrawLetterSize(TextdrawMonth,0.44,1.2);
	TextDrawColor(TextdrawMonth,0xA5BA4BFF);
	TextDrawSetOutline(TextdrawMonth,1);
	TextDrawSetProportional(TextdrawMonth,1);
	TextDrawSetShadow(TextdrawMonth,1);

	Animation = TextDrawCreate(610.0, 400.0, "~w~Type ~b~/stopani ~w~to stop the animation.");
	TextDrawUseBox(Animation, 0);
	TextDrawFont(Animation, 2);
	TextDrawSetShadow(Animation, 0);
	TextDrawSetOutline(Animation, 1);
	TextDrawBackgroundColor(Animation, 0x000000FF);
	TextDrawColor(Animation, 0xFFFFFFFF);
	TextDrawAlignment(Animation, 3);

	propertytxt = TextDrawCreate(10, 430, " ");
	TextDrawSetOutline(propertytxt, 1);
	TextDrawSetShadow(propertytxt, 1);
	TextDrawColor(propertytxt, COLOR_WHITE);

	new ServerHour, Month;
	switch(Month) {
		case IANUARIE: TextDrawSetString(TextdrawMonth, "Ianuarie");
		case FEBRUARIE: TextDrawSetString(TextdrawMonth, "Februarie");
		case MARTIE: TextDrawSetString(TextdrawMonth, "Martie");
		case APRILIE: TextDrawSetString(TextdrawMonth, "Aprilie");
		case MAI: TextDrawSetString(TextdrawMonth, "Mai");
		case IUNIE: TextDrawSetString(TextdrawMonth, "Iunie");
		case IULIE: TextDrawSetString(TextdrawMonth, "Iulie");
		case AUGUST: TextDrawSetString(TextdrawMonth, "August");
		case SEPTEMBRIE: TextDrawSetString(TextdrawMonth, "Septembrie");
		case OCTOMBRIE: TextDrawSetString(TextdrawMonth, "Octombrie");
		case NOIEMBRIE: TextDrawSetString(TextdrawMonth, "Noiembrie");
		case DECEMBRIE: TextDrawSetString(TextdrawMonth, "Decembrie");
	}
	if(ServerHour == 22)
		SetWorldTime(22);
	else
		SetWorldTime(ServerHour);
	if(realtime) {
		new tmphour, tmpminute, tmpsecond;
		gettime(tmphour, tmpminute, tmpsecond);
		FixHour(tmphour);
		tmphour = shifthour;
		SetWorldTime(tmphour);
	}

	BlackBox = TextDrawCreate(354.000000, 422.000000, "_");
	TextDrawBackgroundColor(BlackBox, 255);
	TextDrawFont(BlackBox, 1);
	TextDrawLetterSize(BlackBox, 0.509999, 1.000000);
	TextDrawColor(BlackBox, -1);
	TextDrawSetOutline(BlackBox, 0);
	TextDrawSetProportional(BlackBox, 1);
	TextDrawSetShadow(BlackBox, 1);
	TextDrawUseBox(BlackBox, 1);
	TextDrawBoxColor(BlackBox, 0xE0EEEE);
	TextDrawTextSize(BlackBox, 277.000000, 51.000000);
	new zx,	maxpl = GetMaxPlayers();
	while (zx != maxpl) {
		Fuel[zx] = TextDrawCreate(258.000000, 421.000000, " ");
		TextDrawBackgroundColor(Fuel[zx], 255);
		TextDrawFont(Fuel[zx], 1);
		TextDrawLetterSize(Fuel[zx], 0.250000, 1.100000);
		TextDrawColor(Fuel[zx], -1);
		TextDrawSetOutline(Fuel[zx], 0);
		TextDrawSetProportional(Fuel[zx], 1);
		TextDrawSetShadow(Fuel[zx], 1);

		Moving[zx] = TextDrawCreate(280.000000, 422.000000, "_");
		TextDrawBackgroundColor(Moving[zx], 255);
		TextDrawFont(Moving[zx], 1);
		TextDrawLetterSize(Moving[zx], 0.509999, 1.000000);
		TextDrawColor(Moving[zx], -1);
		TextDrawSetOutline(Moving[zx], 0);
		TextDrawSetProportional(Moving[zx], 1);
		TextDrawSetShadow(Moving[zx], 1);
		TextDrawUseBox(Moving[zx], 1);
		TextDrawBoxColor(Moving[zx], 0x3399FF);
		TextDrawTextSize(Moving[zx], 277.000000, 51.000000);
		++ zx;
	}
	VehicleHPBar[0] = TextDrawCreate(549.0, 50.0, "KABOOM!");
	TextDrawUseBox(VehicleHPBar[0], true);
	TextDrawBoxColor(VehicleHPBar[0], COLOR_BRIGHTRED);
	TextDrawSetShadow(VehicleHPBar[0],0);
	TextDrawTextSize(VehicleHPBar[0], 625, 0);

	VehicleHPBar[1] = TextDrawCreate(551.0, 59.0, " ");
	TextDrawUseBox(VehicleHPBar[1], true);
	TextDrawBoxColor(VehicleHPBar[1], COLOR_BRIGHTRED);
	TextDrawSetShadow(VehicleHPBar[1],0);
	TextDrawTextSize(VehicleHPBar[1], 551, 0);

	VehicleHPBar[2] = TextDrawCreate(551.0, 59.0, " ");
	TextDrawUseBox(VehicleHPBar[2], true);
	TextDrawBoxColor(VehicleHPBar[2], COLOR_BRIGHTRED);
	TextDrawSetShadow(VehicleHPBar[2],0);
	TextDrawTextSize(VehicleHPBar[2], 556, 0);

	VehicleHPBar[3] = TextDrawCreate(551.0, 59.0, " ");
	TextDrawUseBox(VehicleHPBar[3], true);
	TextDrawBoxColor(VehicleHPBar[3], COLOR_BRIGHTRED);
	TextDrawSetShadow(VehicleHPBar[3],0);
	TextDrawTextSize(VehicleHPBar[3], 561, 0);

	VehicleHPBar[4] = TextDrawCreate(551.0, 59.0, " ");
	TextDrawUseBox(VehicleHPBar[4], true);
	TextDrawBoxColor(VehicleHPBar[4], COLOR_YELLOW);
	TextDrawSetShadow(VehicleHPBar[4],0);
	TextDrawTextSize(VehicleHPBar[4], 566, 0);

	VehicleHPBar[5] = TextDrawCreate(551.0, 59.0, " ");
	TextDrawUseBox(VehicleHPBar[5], true);
	TextDrawBoxColor(VehicleHPBar[5], COLOR_YELLOW);
	TextDrawSetShadow(VehicleHPBar[5],0);
	TextDrawTextSize(VehicleHPBar[5], 571, 0);

	VehicleHPBar[6] = TextDrawCreate(551.0, 59.0, " ");
	TextDrawUseBox(VehicleHPBar[6], true);
	TextDrawBoxColor(VehicleHPBar[6], COLOR_YELLOW);
	TextDrawSetShadow(VehicleHPBar[6],0);
	TextDrawTextSize(VehicleHPBar[6], 576, 0);

	VehicleHPBar[7] = TextDrawCreate(551.0, 59.0, " ");
	TextDrawUseBox(VehicleHPBar[7], true);
	TextDrawBoxColor(VehicleHPBar[7], COLOR_YELLOW);
	TextDrawSetShadow(VehicleHPBar[7],0);
	TextDrawTextSize(VehicleHPBar[7], 581, 0);

	VehicleHPBar[8] = TextDrawCreate(551.0, 59.0, " ");
	TextDrawUseBox(VehicleHPBar[8], true);
	TextDrawBoxColor(VehicleHPBar[8], COLOR_GREEN);
	TextDrawSetShadow(VehicleHPBar[8],0);
	TextDrawTextSize(VehicleHPBar[8], 586, 0);

	VehicleHPBar[9] = TextDrawCreate(551.0, 59.0, " ");
	TextDrawUseBox(VehicleHPBar[9], true);
	TextDrawBoxColor(VehicleHPBar[9], COLOR_GREEN);
	TextDrawSetShadow(VehicleHPBar[9],0);
	TextDrawTextSize(VehicleHPBar[9], 591, 0);

	VehicleHPBar[10] = TextDrawCreate(551.0, 59.0, " ");
	TextDrawUseBox(VehicleHPBar[10], true);
	TextDrawBoxColor(VehicleHPBar[10], COLOR_GREEN);
	TextDrawSetShadow(VehicleHPBar[10],0);
	TextDrawTextSize(VehicleHPBar[10], 596, 0);

	VehicleHPBar[11] = TextDrawCreate(551.0, 59.0, " ");
	TextDrawUseBox(VehicleHPBar[11], true);
	TextDrawBoxColor(VehicleHPBar[11], COLOR_GREEN);
	TextDrawSetShadow(VehicleHPBar[11],0);
	TextDrawTextSize(VehicleHPBar[11], 602, 0);

	VehicleHPBar[12] = TextDrawCreate(549.0, 50.0, "EXTREME!");
	TextDrawUseBox(VehicleHPBar[12], true);
	TextDrawBoxColor(VehicleHPBar[12], COLOR_GREEN);
	TextDrawSetShadow(VehicleHPBar[12],0);
	TextDrawTextSize(VehicleHPBar[12], 625, 0);
	clear.string(string);
	return 1;
}

public OnGameModeExit() {
	GameTextForAll("~r~SERVER RESTART ...", 5000, 4);
 	for(new i; i < GetMaxPlayers(); i ++) {
		if(IsPlayerConnected(i)) {
			TextDrawDestroy(DigiHP[i]);
			TextDrawDestroy(DigiAP[i]);
		}
	}
	mysql_close(connectionHandle);
	GameModeExit();
	SendRconCommand("exit");
	return 1;
}

public OnPlayerConnect(playerid)
{
	CheckMySQLAccount(playerid);
	KuramaCheckBanned(playerid);
	PlayAudioStreamForPlayer(playerid, "http://kyuuby.podbean.com/mf/play/pk3anc/girlsharero_TYDOLLASIGN-ONLYRIGHTINSTRUMENTALPRODDJMUSTARDREPRODYOUNGJAKEmp3cutnet.mp3");
	GetPlayerIp(playerid, PlayerIP[playerid], 16);
	ResetCheckpoints(playerid);
	ResetGBVar(playerid); ResetSpectateVar(playerid); ResetVarFishing(playerid);
	Tutorial[playerid] = 0; TutorialTimer[playerid] = 0; TicketOffer[playerid] = 999;
	SpectatePlayerID[playerid] = 0; SpectateType[playerid] = 0; NoFuel[playerid] = 0;
	DMVPrepare[playerid] = 0; TakingLesson{playerid} = false; DMVTimer{playerid} = false; JucatorulAreDroguri[playerid] = 0;
	pTestType{playerid} = TEST_TYPE_NONE; IsPlayerCuffed{playerid} = false; TicketMoney[playerid] = 0; ConsumingMoney[playerid] = 0; CurrentMoney[playerid] = 0; pFMAMessageON{playerid} = true;
	PillsOffer[playerid] = 999; PillsPrice[playerid] = 0; Pills[playerid] = 0; HireCar[playerid] = INVALID_PLAYER_ID; GunOffer[playerid] = INVALID_PLAYER_ID; GunPrice[playerid] = 0; HaveGasInCan[playerid] = 0;
	AcceptTime[playerid] = 0; ClientCaller{playerid} = false; ClientAccept[playerid] = INVALID_PLAYER_ID; PTransfered{playerid} = false; PhoneOnline[playerid] = 0; Mobile[playerid] = 255; HaveFishingRog{playerid} = false;
	IsPlayerTied{playerid} = false; IsPlayerSterilized{playerid} = false; PlayerSterilizedTime[playerid] = 0; gFindMyCar{playerid} = false; NewbieChatTimer[playerid] = 0; Gun[playerid] = -1; HaveFishingBait[playerid] = 0;
	IsPlayerInWar{playerid} = false; ConnectedToPC[playerid] = 0; OrderReady[playerid] = 0; GotHit[playerid] = 0; OnFly{playerid} = false; PropertyOffer[playerid] = INVALID_PLAYER_ID; ItemFrom247[playerid] = INVALID_PLAYER_ID;
	GoChase[playerid] = 999; GetChased[playerid] = 999; PlacedNews[playerid] = 0; news_duty{playerid} = false; IsCopUndercover{playerid} = false; PropertyPrice[playerid] = 0; gFindMCarTime[playerid] = 0; HaveGasCan{playerid} = false;
	news_accepted{playerid} = false; gPlayerLogged{playerid} = false; news_occupied_with[playerid] = INVALID_PLAYER_ID; IsCopDuty{playerid} = false; TogglePlayerLive{playerid} = true; DrugsPrice[playerid] = 0; Drugs[playerid] = 0;
	TalkingLive[playerid] = 255; LiveOffer[playerid] = 999; gLastCar[playerid] = 0; showTurfs{playerid} = false; dustvehicle[playerid] = INVALID_VEHICLE_ID; FarmCantitateFaina[playerid] = 0; DrugsOffer[playerid] = INVALID_PLAYER_ID;
	PlayerAtRivalWar[playerid] = 0; FarmPartener[playerid] = INVALID_PLAYER_ID; FarmCantitate[playerid] = 0; PlayerStoned[playerid] = 0; JucatorulAreMateriale[playerid] = 0; LocatiaRandom{playerid} = 0; OldClassSelect[playerid] = 0;
	if(JOBVehicleTimer[playerid])
		KillTimer(JOBVehicleTimer[playerid]);
	JOBVehicleTimer[playerid] = INVALID_VJOB_TIMER; 

    gHeaderTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gBackgroundTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gCurrentPageTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gNextButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gPrevButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gCancelButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;

	DigiHP[playerid] = TextDrawCreate(566.000000, 67.000000, "~w~~h~100");
	TextDrawBackgroundColor(DigiHP[playerid], 255);
	TextDrawFont(DigiHP[playerid], 1);
	TextDrawLetterSize(DigiHP[playerid], 0.340000, 0.799998);
	TextDrawSetOutline(DigiHP[playerid], 1);
	TextDrawSetProportional(DigiHP[playerid], 1);

	DigiAP[playerid] = TextDrawCreate(566.000000, 45.000000, "~w~~h~100");
	TextDrawBackgroundColor(DigiAP[playerid], 255);
	TextDrawFont(DigiAP[playerid], 1);
	TextDrawLetterSize(DigiAP[playerid], 0.340000, 0.799998);
	TextDrawSetOutline(DigiAP[playerid], 1);
	TextDrawSetProportional(DigiAP[playerid], 1);

	Speedo = CreatePlayerTextDraw(playerid, 550.999816, 169.674087, "Speed: 100 km/h~n~Fuel: 100%~n~Doors: Unlocked~n~Odometer: 1002 km");
	PlayerTextDrawLetterSize(playerid, Speedo, 0.277999, 1.189332);
	PlayerTextDrawAlignment(playerid, Speedo, 2);
	PlayerTextDrawColor(playerid, Speedo, -1);
	PlayerTextDrawSetShadow(playerid, Speedo, 1);
	PlayerTextDrawSetOutline(playerid, Speedo, 1);
	PlayerTextDrawBackgroundColor(playerid, Speedo, 108);
	PlayerTextDrawFont(playerid, Speedo, 1);
	PlayerTextDrawSetProportional(playerid, Speedo, 1);
	PlayerTextDrawSetShadow(playerid, Speedo, 1);

	GangZoneShowForPlayer(playerid, nodmzone, COLOR_NODMZONE);
	GangZoneShowForPlayer(playerid, nodmzone2, COLOR_NODMZONE);

	//========================
	// -- Anti-Cheat
	AntiCheat[playerid][eGACSpeed] = 0;
	AntiCheat[playerid][eGACTunningHack] = 0;
	AntiCheat[playerid][eGWarningCheat] = 0;

	TransportValue[playerid] = 0;
	TaxiST[playerid][TaxiDuty] = 0;
	TaxiST[playerid][TaxiEarn] = 0;
	TaxiST[playerid][InTaxi] = 0;
	TaxiST[playerid][DrivingTaxi] = INVALID_PLAYER_ID;

	PlayerInfo[playerid][pReg] = 0;
	PlayerInfo[playerid][pSex] = 0;
	PlayerInfo[playerid][pAge] = 0;
	PlayerInfo[playerid][pTut] = 0;
	PlayerInfo[playerid][pCash] = 0;
	PlayerInfo[playerid][pLevel] = 0;
	PlayerInfo[playerid][pSkin] = 0;
	PlayerInfo[playerid][pAdmin] = 0;
	PlayerInfo[playerid][pHelper] = 0;
	PlayerInfo[playerid][pLeader] = FACT_CIVIL;
	PlayerInfo[playerid][pFactiune] = FACT_CIVIL;
	PlayerInfo[playerid][pRank] = 0;
	PlayerInfo[playerid][pTeam] = FACT_CIVIL;
	PlayerInfo[playerid][pAccount] = 0;
	PlayerInfo[playerid][pExp] = 0;
	PlayerInfo[playerid][pUpgradeP] = 0;
	PlayerInfo[playerid][pSHealth] = 100.0;
	PlayerInfo[playerid][pConnectTime] = 0;
	PlayerInfo[playerid][pDeelayNeedHelp] = 0;
	PlayerInfo[playerid][pMute] = 0;
	PlayerInfo[playerid][pMuteTime] = 0;
	PlayerInfo[playerid][pWarnings] = 0;
	PlayerInfo[playerid][pDrivingLicense] = 0;
	PlayerInfo[playerid][pFlyingLicense] = 0;
	PlayerInfo[playerid][pSailingLicense] = 0;
	PlayerInfo[playerid][pPhousekey] = 0;
	PlayerInfo[playerid][pPbizkey] = 0;
	PlayerInfo[playerid][pCigarettes] = 0;
	PlayerInfo[playerid][pLighter] = 0;
	PlayerInfo[playerid][pPnumber] = 0;
	PlayerInfo[playerid][pPhoneBook] = 0;
	PlayerInfo[playerid][pInBizzID] = 0;
	PlayerInfo[playerid][pWlvl] = 0;
	PlayerInfo[playerid][pJailed] = 0;
	PlayerInfo[playerid][pJailTime] = 0;
	PlayerInfo[playerid][pDrugs] = 0;
	PlayerInfo[playerid][pMats] = 0;
	PlayerInfo[playerid][pPills] = 0;
	PlayerInfo[playerid][pUsePillsTime] = 0;
	PlayerInfo[playerid][pReportTime] = 0;
	PlayerInfo[playerid][pInHouseID] = 0;
	PlayerInfo[playerid][pInHQID] = 0;
	PlayerInfo[playerid][pHeadValue] = 0;
	PlayerInfo[playerid][pContracts] = 0;
	PlayerInfo[playerid][pPayCheck] = 0;
	PlayerInfo[playerid][pNewsSkill] = 0;
	PlayerInfo[playerid][pFWarn] = 0;
	PlayerInfo[playerid][pKills] = 0;
	PlayerInfo[playerid][pDeaths] = 0;
	PlayerInfo[playerid][pCarTime] = 0;
	PlayerInfo[playerid][pDustSkill] = 0;
	PlayerInfo[playerid][pJob] = JOB_NONE;
	PlayerInfo[playerid][pTakeVehiclePause] = 0;
	PlayerInfo[playerid][pFactionSpawn] = 0;
	PlayerInfo[playerid][pSpawnChange] = 0;
	PlayerInfo[playerid][pInterior] = 0;
	PlayerInfo[playerid][pVirtualWorld] = 0;
	PlayerInfo[playerid][pPayDayTime] = 0;
	PlayerInfo[playerid][pActiveTime] = 0;
	PlayerInfo[playerid][pActiveCounter] = 0;
	PlayerInfo[playerid][pFarmerSkill] = 0;
	PlayerInfo[playerid][pCarJackerSkill] = 0;
	PlayerInfo[playerid][pGiftPoints] = 0;
	PlayerInfo[playerid][pCursorDealer] = 0;
	PlayerInfo[playerid][pCarSlots] = 0;
	PlayerInfo[playerid][pFarmingTime] = 0;
	PlayerInfo[playerid][pAdvertismentTime] = 0;
	PlayerInfo[playerid][pDrugsTime] = 0;
	PlayerInfo[playerid][pRequestingBackup] = 0;
	PlayerInfo[playerid][pTazed] = 0;
	PlayerInfo[playerid][pNMute] = 0;
	PlayerInfo[playerid][pDisable] = 0;
	PlayerInfo[playerid][pDisableTime] = 0;
	/* Resetam misiunile la logare */
	PlayerInfo[playerid][pDailyMission][0] = -1;
	PlayerInfo[playerid][pDailyMission][1] = -1;
	PlayerInfo[playerid][pProgress][0] = 0;
	PlayerInfo[playerid][pProgress][1] = 0;
	PlayerInfo[playerid][pNeedProgress][0] = 0;
	PlayerInfo[playerid][pNeedProgress][1] = 0;
	/* Resetam valorile pentru Daily Award Login */
	PlayerInfo[playerid][pTotalPD] = 0;
	PlayerInfo[playerid][pLastDayOfPD] = 0;
	PlayerInfo[playerid][pLastTimeOfPD] = 0;
	PlayerInfo[playerid][pArmsDealerSkill] = 0;
	PlayerInfo[playerid][pWantedDown] = 0;
	PlayerInfo[playerid][pCPSweeper] = -1;
	PlayerInfo[playerid][pSweeperSkill] = 0;
	PlayerInfo[playerid][pCPSweeper2] = -1;
	PlayerInfo[playerid][pDrugsDealerSkill] = 0;
	PlayerInfo[playerid][pFrequence] = NONE_FREQUENCE;
	PlayerInfo[playerid][pFreqNO] = NONE_FREQUENCE;
	PlayerInfo[playerid][pDice] = 0;
	PlayerInfo[playerid][pBiggestFish] = 0;
	PlayerInfo[playerid][pFishSkill] = 0;
	PlayerInfo[playerid][pReferralID] = 0;
	PlayerInfo[playerid][pReferralCash] = 0;
	PlayerInfo[playerid][pReferralRespect] = 0;
	PlayerInfo[playerid][pRobPoints] = 10;

	SetPlayerColor(playerid, COLOR_GRAD2);
	return 1;
}

public OnPlayerSpawn(playerid) {
	PlayerPlaySound(playerid, 0, 0.0, 0.0, 0);
	SetPlayerArmour(playerid, 0.0);
	SetPlayerHealth(playerid, 100.0);
	SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
	SetTimerEx("SetPlayerTurfName", 500, true, "u", playerid);
	SetPlayerFactionColor(playerid, PlayerInfo[playerid][pFactiune]);
	if(!PlayerInfo[playerid][pJailed])
		SafeResetPlayerInterior(playerid);
	gFindMyCar{playerid} = false;
	SetPlayerSpawnInfo(playerid, NOT_USE_RESPAWN);
	return 1;
}

stock IsPlayerFlooding(playerid) {
	if(gGlobalTick - iPlayerChatTime[playerid] < 1000) return 1;
	return 0;
}

public OnPlayerCommandReceived(playerid, cmdtext[]) {
	if(IsPlayerFlooding(playerid)) {
		SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: "ALB"Please wait 2 seconds.");
		iPlayerChatTime[playerid] = gGlobalTick;
		return 0;
	}
	iPlayerChatTime[playerid] = gGlobalTick;

	new string[MAXO_TEXT1];
	format(string, MAXO_TEXT1, "%s [CMD:]%s", PlayerName(playerid), cmdtext);
	CommandsLogs(string);
	clear.string(string);
	return 1;
}

public OnPlayerText(playerid, text[]) {
	new tmp[MAXO_TEXT2], string[MAXO_TEXT], giveplayerid;
	if(gPlayerLogged{playerid}) {
		if(IsPlayerFlooding(playerid)) {
			SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: "ALB"Please wait 2 seconds.");
			iPlayerChatTime[playerid] = gGlobalTick;
			return 0;			
		}
		if(PlayerInfo[playerid][pMute] != 0) {
			IsPlayerSilent();
			return false;
		}
		if(PlayerInfo[playerid][pAdmin] < 1) {
			if(strlen(text) == strlen(szPlayerChatMsg[playerid]) && !strcmp(szPlayerChatMsg[playerid], text,  false)) {
				SendClientMessage(playerid, 0xFFFF00AA, "Anti-Spam: {FFFFFF}Nu te repeta!");
				format(szPlayerChatMsg[playerid], MAXO_TEXT, "%s", text);
				return false;
			}
		}
		if(GetPlayerVirtualWorld(playerid) != 0) {
			format(szPlayerChatMsg[playerid], MAXO_TEXT, "Â» %s: %s Â«", PlayerName(playerid), text);
			SendPlayerMessage(30.0, playerid, szPlayerChatMsg[playerid], COLOR_WHITE);
			return false;
		}
	}
	if(ConnectedToPC[playerid] == 255) {
		new idx;
	    tmp = strtok(text, idx);
	    if ((strcmp("Contracts", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("Contracts"))) {
		    if(PlayerInfo[playerid][pRank] < 4) {
		        SendClientMessage(playerid, COLOR_GREY, "Only Hitman with Rank 4 or above can search and assign Contracts !");
		        return false;
		    }
		    SearchingHit(playerid);
			return false;
		}
		else if ((strcmp("Checkmycontracts", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("Checkmycontracts"))) {
		    format(string, MAXO_TEXT, "Fulfilled contracts: %d", PlayerInfo[playerid][pContracts]);
			SendClientMessage(playerid, COLOR_YELLOW2, string);
			return false;
		}
		else if ((strcmp("News", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("News"))) {
			new x_nr[MAXO_TEXT2];
			x_nr = strtok(text, idx);
			if(!strlen(x_nr)) {
				SendClientMessage(playerid, COLOR_WHITE, "|__________________ Hitman Agency News __________________|");
				SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}News [number] or News delete [number] or News delete all");
				format(string, MAXO_TEXT, "1: %s :: Hitman: %s", News[hAdd1], News[hContact1]);
				SendClientMessage(playerid, COLOR_GREY, string);
				format(string, MAXO_TEXT, "2: %s :: Hitman: %s", News[hAdd2], News[hContact2]);
				SendClientMessage(playerid, COLOR_GREY, string);
				format(string, MAXO_TEXT, "3: %s :: Hitman: %s", News[hAdd3], News[hContact3]);
				SendClientMessage(playerid, COLOR_GREY, string);
				format(string, MAXO_TEXT, "4: %s :: Hitman: %s", News[hAdd4], News[hContact4]);
				SendClientMessage(playerid, COLOR_GREY, string);
				format(string, MAXO_TEXT, "5: %s :: Hitman: %s", News[hAdd5], News[hContact5]);
				SendClientMessage(playerid, COLOR_GREY, string);
				SendClientMessage(playerid, COLOR_WHITE, "|________________________________________________________|");
				return false;
			}
			if(strcmp(x_nr, "1", true) == 0) {
				if(PlacedNews[playerid] == 1) { SendClientMessage(playerid, COLOR_GRAD1, "Already placed a News Message, it must be deleted first !"); return false; }
				if(PlayerInfo[playerid][pRank] < 3) { SendClientMessage(playerid, COLOR_GRAD1, "You must be Rank 3 to write messages to the News Channel !"); return false; }
				if(News[hTaken1] == 0) {
					if(strlen(text)-(strlen(x_nr)) < 9) { SendClientMessage(playerid, COLOR_GREY, "News Text to short !"); return false; }
					format(string, MAXO_TEXT, "%s", right(text,strlen(text)-7));
					strmid(News[hAdd1], string, 0, strlen(string), 255);
					format(string, MAXO_TEXT, "%s", PlayerName(playerid));
					strmid(News[hContact1], string, 0, strlen(string), 255);
					News[hTaken1] = 1; PlacedNews[playerid] = 1;
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You placed a News Message on the Hitman Agency's News Channel.");
					return false;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GRAD1, "Spot 1 is already Taken !");
					return false;
				}
			}
			else if(strcmp(x_nr, "2", true) == 0) {
				if(PlacedNews[playerid] == 1) { SendClientMessage(playerid, COLOR_GRAD1, "Already placed a News Message, it must be deleted first !"); return false; }
				if(PlayerInfo[playerid][pRank] < 3) { SendClientMessage(playerid, COLOR_GRAD1, "You must be Rank 3 to write messages to the News Channel !"); return false; }
				if(News[hTaken2] == 0) {
					if(strlen(text)-(strlen(x_nr)) < 9) { SendClientMessage(playerid, COLOR_GRAD1, "News Text to short !"); return 0; }
					format(string, MAXO_TEXT, "%s", right(text, strlen(text)-7));
					strmid(News[hAdd2], string, 0, strlen(string), 255);
					format(string, MAXO_TEXT, "%s", PlayerName(playerid));
					strmid(News[hContact2], string, 0, strlen(string), 255);
					News[hTaken2] = 1; PlacedNews[playerid] = 1;
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You placed a News Message on the Hitman Agency's News Channel.");
					return false;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GRAD1, "Spot 2 is already Taken !");
					return false;
				}
			}
			else if(strcmp(x_nr, "3", true) == 0) {
				if(PlacedNews[playerid] == 1) { SendClientMessage(playerid, COLOR_GRAD1, "Already placed a News Message, it must be deleted first !"); return false; }
				if(PlayerInfo[playerid][pRank] < 3) { SendClientMessage(playerid, COLOR_GRAD1, "You must be Rank 3 to write messages to the News Channel !"); return false; }
				if(News[hTaken3] == 0) {
					if(strlen(text) - (strlen(x_nr)) < 9) { SendClientMessage(playerid, COLOR_GRAD1, "News Text to short !"); return false; }
					format(string, MAXO_TEXT, "%s", right(text, strlen(text)-7));
					strmid(News[hAdd3], string, 0, strlen(string), 255);
					format(string, MAXO_TEXT, "%s", PlayerName(playerid));
					strmid(News[hContact3], string, 0, strlen(string), 255);
					News[hTaken3] = 1; PlacedNews[playerid] = 1;
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You placed a News Message on the Hitman Agency's News Channel.");
					return false;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GRAD1, "Spot 3 is already Taken !");
					return false;
				}
			}
			else if(strcmp(x_nr, "4", true) == 0) {
				if(PlacedNews[playerid] == 1) { SendClientMessage(playerid, COLOR_GRAD1, "Already placed a News Message, it must be deleted first !"); return false; }
				if(PlayerInfo[playerid][pRank] < 3) { SendClientMessage(playerid, COLOR_GREY, "You must be Rank 3 to write messages to the News Channel !"); return false; }
				if(News[hTaken4] == 0) {
					if(strlen(text) - (strlen(x_nr)) < 9) { SendClientMessage(playerid, COLOR_GRAD1, "News Text to short !"); return false; }
					format(string, MAXO_TEXT, "%s", right(text,strlen(text)-7));
					strmid(News[hAdd4], string, 0, strlen(string), 255);
					format(string, MAXO_TEXT, "%s", PlayerName(playerid));
					strmid(News[hContact4], string, 0, strlen(string), 255);
					News[hTaken4] = 1; PlacedNews[playerid] = 1;
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You placed a News Message on the Hitman Agency's News Channel.");
					return false;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "Spot 4 is already Taken !");
					return false;
				}
			}
			else if(strcmp(x_nr, "5", true) == 0) {
				if(PlacedNews[playerid] == 1) { SendClientMessage(playerid, COLOR_GRAD1, "Already placed a News Message, it must be deleted first !"); return false; }
				if(PlayerInfo[playerid][pRank] < 3) { SendClientMessage(playerid, COLOR_GRAD1, "You must be Rank 3 to write messages to the News Channel !"); return false; }
				if(News[hTaken5] == 0) {
					if(strlen(text) - (strlen(x_nr)) < 9) { SendClientMessage(playerid, COLOR_GRAD1, "News Text to short !"); return false; }
					format(string, MAXO_TEXT, "%s", right(text, strlen(text)-7));
					strmid(News[hAdd5], string, 0, strlen(string), 255);
					format(string, MAXO_TEXT, "%s", PlayerName(playerid));
					strmid(News[hContact5], string, 0, strlen(string), 255);
					News[hTaken5] = 1; PlacedNews[playerid] = 1;
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You placed a News Message on the Hitman Agency's News Channel.");
					return false;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GREY, "Spot 5 is already Taken !");
					return false;
				}
			}
			else if(strcmp(x_nr, "delete", true) == 0) {
				if(PlayerInfo[playerid][pRank] < 4) {
					SendClientMessage(playerid, COLOR_GRAD1, "You must be Rank 4 to delete messages from the News Channel !");
					return false;
				}
				new string1[MAX_PLAYER_NAME];
				new x_tel[MAXO_TEXT2];
				x_tel = strtok(text, idx);
				if(!strlen(x_tel)) {
					SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF} News delete [number] or News delete all.");
					return false;
				}
				if(strcmp(x_tel, "1", true) == 0) {
					format(string, MAXO_TEXT, "Nothing"); strmid(News[hAdd1], string, 0, strlen(string), 255);
					format(string1, MAX_PLAYER_NAME, "No-one");	strmid(News[hContact1], string1, 0, strlen(string1), 255);
					News[hTaken1] = 0;
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You deleted News Message (1) from the Hitman Agency's News Channel.");
					return false;
				}
				else if(strcmp(x_tel, "2", true) == 0) {
					format(string, MAXO_TEXT, "Nothing"); strmid(News[hAdd2], string, 0, strlen(string), 255);
					format(string1, MAX_PLAYER_NAME, "No-one");	strmid(News[hContact2], string1, 0, strlen(string1), 255);
					News[hTaken2] = 0;
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You deleted News Message (2) from the Hitman Agency's News Channel.");
					return false;
				}
				else if(strcmp(x_tel, "3", true) == 0) {
					format(string, MAXO_TEXT, "Nothing"); strmid(News[hAdd3], string, 0, strlen(string), 255);
					format(string1, MAX_PLAYER_NAME, "No-one");	strmid(News[hContact3], string1, 0, strlen(string1), 255);
					News[hTaken3] = 0;
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You deleted News Message (3) from the Hitman Agency's News Channel.");
					return false;
				}
				else if(strcmp(x_tel, "4", true) == 0) {
					format(string, MAXO_TEXT, "Nothing"); strmid(News[hAdd4], string, 0, strlen(string), 255);
					format(string1, MAX_PLAYER_NAME, "No-one");	strmid(News[hContact4], string1, 0, strlen(string1), 255);
					News[hTaken4] = 0;
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You deleted News Message (4) from the Hitman Agency's News Channel.");
					return false;
				}
				else if(strcmp(x_tel, "5", true) == 0) {
					format(string, MAXO_TEXT, "Nothing"); strmid(News[hAdd5], string, 0, strlen(string), 255);
					format(string1, MAX_PLAYER_NAME, "No-one");	strmid(News[hContact5], string1, 0, strlen(string1), 255);
					News[hTaken5] = 0;
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You deleted News Message (5) from the Hitman Agency's News Channel.");
					return false;
				}
				else if(strcmp(x_tel, "all", true) == 0) {
					format(string, MAXO_TEXT, "Nothing"); strmid(News[hAdd1], string, 0, strlen(string), 255);
					format(string1, MAX_PLAYER_NAME, "No-one");	strmid(News[hContact1], string1, 0, strlen(string1), 255);
					News[hTaken1] = 0;
					format(string, MAXO_TEXT, "Nothing"); strmid(News[hAdd2], string, 0, strlen(string), 255);
					format(string1, MAX_PLAYER_NAME, "No-one");	strmid(News[hContact2], string1, 0, strlen(string1), 255);
					News[hTaken2] = 0;
					format(string, MAXO_TEXT, "Nothing"); strmid(News[hAdd3], string, 0, strlen(string), 255);
					format(string1, MAX_PLAYER_NAME, "No-one");	strmid(News[hContact3], string1, 0, strlen(string1), 255);
					News[hTaken3] = 0;
					format(string, MAXO_TEXT, "Nothing"); strmid(News[hAdd4], string, 0, strlen(string), 255);
					format(string1, MAX_PLAYER_NAME, "No-one");	strmid(News[hContact4], string1, 0, strlen(string1), 255);
					News[hTaken4] = 0;
					format(string, MAXO_TEXT, "Nothing"); strmid(News[hAdd5], string, 0, strlen(string), 255);
					format(string1, MAX_PLAYER_NAME, "No-one");	strmid(News[hContact5], string1, 0, strlen(string1), 255);
					News[hTaken5] = 0;
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You deleted all the News Message from the Hitman Agency's News Channel.");
					return false;
				}
				else
				{
					SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}News delete [number] or News delete all.");
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else if ((strcmp("Givehit", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("Givehit"))) {
		    if(PlayerInfo[playerid][pRank] < 4) {
		        SendClientMessage(playerid, COLOR_GRAD1, "You need Rank 4 to Give Contracts to Hitmans !");
		        return false;
		    }
		    if(hitfound == 0) {
		        SendClientMessage(playerid, COLOR_GRAD1, "There is no Hit Founded yet, use Contracts in the Portable first !");
		        return false;
		    }
		    tmp = strtok(text, idx);
		    if(!strlen(tmp)) {
				SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}Givehit [playerid/PartOfName]");
				return false;
			}
			giveplayerid = ReturnUser(tmp);
			if(giveplayerid != INVALID_PLAYER_ID) {
				if(PlayerInfo[giveplayerid][pFactiune] != FACT_HITMAN) {
					SendClientMessage(playerid, COLOR_GRAD1, "That player is not a Hitman !");
					return false;
				}
				if(GoChase[giveplayerid] < 999) {
					SendClientMessage(playerid, COLOR_GRAD1, "That Hitman is already busy with a Contract !");
					return false;
				}
				if(HitM != INVALID_PLAYER_ID) {
					format(string, MAXO_TEXT, "* Hitman %s, assigned Hitman %s to kill: %s(ID:%d), for %s.", PlayerName(playerid), PlayerName(giveplayerid), PlayerName(HitM), HitM, FormatNumber(PlayerInfo[HitM][pHeadValue], 0, '.'));
					SendFamilyMessage(COLOR_ORANGE, string, FACT_HITMAN);
					GoChase[giveplayerid] = HitM;
					GetChased[HitM] = giveplayerid;
					GotHit[HitM] = 1;
					HitM = 0;
					hitfound = 0;
					return false;
				}
				else
				{
					SendClientMessage(playerid, COLOR_GRAD1, "The Contracted Person is offline, use Contracts in the Portable again !");
					return false;
				}
			}
			else
			{
			    SendClientMessage(playerid, COLOR_GRAD1, "That Hitman is not Online, or ain't a Hitman !");
			    return false;
			}
		}
		else if ((strcmp("Myhit", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("Myhit"))) {
	   		foreach(Player, x) {
	       		if(PlayerInfo[x][pHeadValue] > 0) {
	            	if(GoChase[playerid] != 999) {
	                    if(GoChase[playerid] == x) {
	                        format(string, MAXO_TEXT, "* Your hit is: %s, Value: %s.", PlayerName(x), FormatNumber(PlayerInfo[x][pHeadValue], 0, '.'));
	                        SendClientMessage(playerid, COLOR_YELLOW2, string);
	                        return false;
	                    }
	                }
	                else
	                {
	                    SendClientMessage(playerid, COLOR_GRAD1, "You don't have a hit !");
	                    return false;
	                }
	            }
	        }
		}
		else if ((strcmp("Ranks", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("Ranks"))) {
			SendClientMessage(playerid, COLOR_WHITE, "|__________________ Agency's Ranks __________________|");
		    foreach(Player, i){
				if(PlayerInfo[i][pFactiune] == FACT_HITMAN) {
					format(string, MAXO_TEXT, "* %s: Rank %d", PlayerName(i), PlayerInfo[i][pRank]);
					SendClientMessage(playerid, COLOR_GREY, string);
				}
			}
		}
		else if ((strcmp("Undercover", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("Undercover"))) {
		    tmp = strtok(text, idx);
		    if((strcmp("On", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("On"))) {
		        SendClientMessage(playerid, COLOR_WHITE, "Undercover On.");
  				foreach(Player, i) {
        			SetPlayerColor(playerid, 0xFFFFFF00);
    			}
			}
			else if((strcmp("Off", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("Off"))) {
			    SendClientMessage(playerid, COLOR_WHITE, "Undercover Off.");
       			foreach(Player, i) {
        			SetPlayerColor(playerid, 0xA63232FF);
    			}
			}
			else
			{
			    SendClientMessage(playerid, COLOR_WHITE, "Undercover [On/Off]");
			    return false;
			}
		}
		else if ((strcmp("Order", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("Order"))) {
		    if(OrderReady[playerid] > 0) {
		        SendClientMessage(playerid, COLOR_GRAD1, "You already Ordered a Package, pick it up at Deliver Place with a Sniper Icon!");
		        return false;
		    }
		    tmp = strtok(text, idx);
		    if((strcmp("1", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("1"))) {
			    if(PlayerInfo[playerid][pRank] < 1) { SendClientMessage(playerid, COLOR_GRAD1, "Your Rank is not high enough to Order that Package !"); return false; }
			    if(PlayerInfo[playerid][pCash] > 4999) {
			        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have Ordered Package 1 ($5.000), it will be delivered at Deliver Place with a Sniper Icon!");
			        OrderReady[playerid] = 1;
			        return true;
			    }
			    else
			    {
			        SendClientMessage(playerid, COLOR_GRAD1, "You can't afford that Package !");
			        return false;
			    }
			}
			else if((strcmp("2", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("2"))) {
			    if(PlayerInfo[playerid][pRank] < 2) {
					SendClientMessage(playerid, COLOR_GRAD1, "Your Rank is not high enough to Order that Package !");
					return false;
				}
			    if(PlayerInfo[playerid][pCash] > 5999) {
			        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have Ordered Package 2 ($6.000), it will be delivered at Deliver Place with a Sniper Icon!");
			        OrderReady[playerid] = 2;
			        return false;
			    }
			    else
			    {
			        SendClientMessage(playerid, COLOR_GRAD1, "You can't afford that Package !");
			        return false;
			    }
			}
			else if((strcmp("3", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("3"))) {
			    if(PlayerInfo[playerid][pRank] < 2) { SendClientMessage(playerid, COLOR_GRAD1, "Your Rank is not high enough to Order that Package !"); return false; }
			    if(PlayerInfo[playerid][pCash] > 5999) {
			        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have Ordered Package 3 ($6.000), it will be delivered at Deliver Place with a Sniper Icon!");
			        OrderReady[playerid] = 3;
			        return false;
			    }
			    else
			    {
			        SendClientMessage(playerid, COLOR_GRAD1, "You can't afford that Package !");
			        return false;
			    }
			}
			else if((strcmp("4", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("4"))) {
			    if(PlayerInfo[playerid][pRank] < 3) { SendClientMessage(playerid, COLOR_GRAD1, "Your Rank is not high enough to Order that Package !"); return false; }
			    if(PlayerInfo[playerid][pCash] > 7999) {
			        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have Ordered Package 4 ($8.000), it will be delivered at Deliver Place with a Sniper Icon!");
			        OrderReady[playerid] = 4;
			        return false;
			    }
			    else
			    {
			        SendClientMessage(playerid, COLOR_GRAD1, "You can't afford that Package !");
			        return false;
			    }
			}
			else if((strcmp("5", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("5"))) {
			    if(PlayerInfo[playerid][pRank] < 3) { SendClientMessage(playerid, COLOR_GRAD1, "Your Rank is not high enough to Order that Package !"); return false; }
			    if(PlayerInfo[playerid][pCash] > 7999) {
			        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have Ordered Package 5 ($8.000), it will be delivered at Deliver Place with a Sniper Icon!");
			        OrderReady[playerid] = 5;
			        return false;
			    }
			    else
			    {
			        SendClientMessage(playerid, COLOR_GRAD1, "You can't afford that Package !");
			        return false;
			    }
			}
			else if((strcmp("6", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("6"))) {
			    if(PlayerInfo[playerid][pRank] < 4) { SendClientMessage(playerid, COLOR_GRAD1, "Your Rank is not high enough to Order that Package !"); return false; }
			    if(PlayerInfo[playerid][pCash] > 8499) {
			        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have Ordered Package 6 ($8.500), it will be delivered at Deliver Place with a Sniper Icon!");
			        OrderReady[playerid] = 6;
			        return false;
			    }
			    else
			    {
			        SendClientMessage(playerid, COLOR_GRAD1, "You can't afford that Package !");
			        return false;
			    }
			}
			else if((strcmp("7", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("7"))) {
			    if(PlayerInfo[playerid][pRank] < 4) { SendClientMessage(playerid, COLOR_GRAD1, "Your Rank is not high enough to Order that Package !"); return false; }
			    if(PlayerInfo[playerid][pCash] > 8499) {
			        SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have Ordered Package 7 ($8.500), it will be delivered at Deliver Place with a Sniper Icon!");
			        OrderReady[playerid] = 7;
			        return false;
			    }
			    else
			    {
			        SendClientMessage(playerid, COLOR_GRAD1, "You can't afford that Package !");
			        return false;
			    }
			}
			else
			{
			    SendClientMessage(playerid, COLOR_WHITE, "|__________________ Available Packages __________________|");
			    if(PlayerInfo[playerid][pRank] >= 1) { SendClientMessage(playerid, COLOR_GREY, "|(1) ($5.000 ) Rank 1 - 5: Knife, Desert Eagle, MP5, Shotgun"); }
			    if(PlayerInfo[playerid][pRank] >= 2) { SendClientMessage(playerid, COLOR_GREY, "|(2) ($6.000 ) Rank 2 - 5: Knife, Desert Eagle, M4, MP5, Shotgun"); }
			    if(PlayerInfo[playerid][pRank] >= 2) { SendClientMessage(playerid, COLOR_GREY, "|(3) ($6.000 ) Rank 2 - 5: Knife, Desert Eagle, AK47, MP5, Shotgun"); }
			    if(PlayerInfo[playerid][pRank] >= 3) { SendClientMessage(playerid, COLOR_GREY, "|(4) ($8.000) Rank 3 - 5: Knife, Desert Eagle, M4, MP5, Shotgun, Sniper"); }
			    if(PlayerInfo[playerid][pRank] >= 3) { SendClientMessage(playerid, COLOR_GREY, "|(5) ($8.000) Rank 3 - 5: Knife, Desert Eagle, AK47, MP5, Shotgun, Sniper"); }
			    if(PlayerInfo[playerid][pRank] >= 4) { SendClientMessage(playerid, COLOR_GREY, "|(6) ($8.500) Rank 4 - 5: Knife, Desert Eagle, M4, MP5, Shotgun, Sniper"); }
			    if(PlayerInfo[playerid][pRank] >= 4) { SendClientMessage(playerid, COLOR_GREY, "|(7) ($8.500) Rank 4 - 5: Knife, Desert Eagle, AK47, MP5, Shotgun, Sniper"); }
			    SendClientMessage(playerid, COLOR_WHITE, "|________________________________________________________|");
			    return false;
			}
		}
		else if((strcmp("Logout", tmp, true, strlen(tmp)) == 0) && (strlen(tmp) == strlen("Logout"))) {
		    SendClientMessage(playerid, COLOR_LIGHTBLUE, "* You have shutdowned your Laptop, and Disconnected from your Agency.");
      		ConnectedToPC[playerid] = 0;
		    return false;
		}
		else
		{
		    SendClientMessage(playerid, COLOR_WHITE, "|___ Hitman Agency ___|");
		    SendClientMessage(playerid, COLOR_YELLOW2, "| - News");
		    SendClientMessage(playerid, COLOR_YELLOW2, "| - Contracts");
		    SendClientMessage(playerid, COLOR_YELLOW2, "| - Givehit");
		    SendClientMessage(playerid, COLOR_YELLOW2, "| - Backup");
		    SendClientMessage(playerid, COLOR_YELLOW2, "| - Order");
		    SendClientMessage(playerid, COLOR_YELLOW2, "| - Ranks");
			SendClientMessage(playerid, COLOR_YELLOW2, "| - Myhit");
			SendClientMessage(playerid, COLOR_YELLOW2, "| - CheckMyContracts");
		    SendClientMessage(playerid, COLOR_YELLOW2, "| - Logout");
		    SendClientMessage(playerid, COLOR_YELLOW2, "|");
			SendClientMessage(playerid, COLOR_WHITE, "|______________|00:00|");
		    return false;
		}
	    return false;
	}
	if(TalkingLive[playerid] != 255) {
		if(PlayerInfo[playerid][pFactiune] == FACT_CNN)
			format(string, MAXO_TEXT, "LiveNR %s: %s", PlayerName(playerid), text);
		else
			format(string, MAXO_TEXT, "LivePlayer %s: %s", PlayerName(playerid), text);
		LiveChat(COLOR_LIGHTGREEN, string);
		return false;

	}
	else if(!gPlayerLogged{playerid}) return false;
	format(szPlayerChatMsg[playerid], MAXO_TEXT, "%s", text);
	iPlayerChatTime[playerid] = gGlobalTick;
	clear.string(string);
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate) {
	new
		vID = GetPlayerVehicleID(playerid), string[MAXO_TEXT];
	if(newstate == PLAYER_STATE_ONFOOT) {
		// vom pune conditia daca noul status este de tip 'pieton'
		// apoi vom verifica daca vechiul status este cel de sofer al masinii de timp RENT;
		// verificam daca vehiculul este de tip RENT;
		// clasificam fiecare timp de vehicul rentabil;
		// ca si ultim pas, stabilim textele afisate pe masini;
		new ultmasina = gLastCar[playerid];
		if(oldstate == PLAYER_STATE_DRIVER) {
			new tipmasina = CarInfo[ultmasina][cType];
			if(tipmasina == VEHICLE_TYPE_RENTCAR) {
				new carstring[MAXO_TEXT];
				new valoare = CarInfo[ultmasina][cValue];
				switch(tipmasina) {
					case VEHICLE_TYPE_RENTCAR: format(carstring, MAXO_TEXT, "Vehicle for rent!\nRent price: $%s\nType: /rentcar", FormatNumber(valoare, 0, '.'));
				}
				Update3DtextRentCar(ultmasina);
			}
			if(tipmasina == VEHICLE_TYPE_PERSONAL) {
				format(string, 36, "%s's vehicle", CarInfo[ultmasina][cOwner]);
				Update3DTextLabelText(CarInfo[ultmasina][cText], COLOR_GRAD1, string);
			}
			if(IsAJOBVehicle(ultmasina)) {
				SendClientMessage(playerid, COLOR_ORANGE, "INFO: You have 15 seconds to get back in the car !"),
				JOBVehicleTimer[playerid] = SetTimerEx("ExitJOBVehicle", 15000, false, "ii", playerid, ultmasina);
			}
			if(pDSMasinaTestDrive[playerid] != INVALID_VEHICLE_ID) {
				HideDSEnvironment(playerid);
				SendClientMessage(playerid, -1, "Deoarece ai iesit din masina, testul a fost oprit fortat.");
				KillTimer(timertestdrive);
			}
		}
	}
	else if(newstate == PLAYER_STATE_DRIVER) {
		new newcar, TipMas;
		newcar = GetPlayerVehicleID(playerid);
		gLastCar[playerid] = newcar;
		gLastDriver[newcar] = playerid;
		TipMas = CarInfo[newcar][cType];
		if(IsARentableVehicle(newcar)) {
			Update3DTextLabelText(CarInfo[newcar][cText], COLOR_GRAD1, " ");
			if(HireCar[playerid] != newcar) {
				if(TipMas == VEHICLE_TYPE_RENTCAR) return EnterOnRentCar(playerid, newcar);
			}
		}
		if(TipMas == VEHICLE_TYPE_PERSONAL) return EnterOnPersonalCar(playerid, newcar);
		if(IsAJOBVehicle(newcar)) {
			if(TipMas == VEHICLE_TYPE_FARMER_A) {
				if(PlayerInfo[playerid][pJob] == JOB_FARMER)
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "*** "GRI3"Available commands: /startfarm | /stopfarm"),
					SendClientMessage(playerid, COLOR_ORANGE, "INFO: First time, type the command /startfarm and after start the engine."),
					ShowPlayerInformation(playerid, "Farmer Job", "Trebuie sa mergi cu acest vehicul timp de ~r~02:00 minute ~y~cu o viteza > de 25 km/h pentru a indeplini misiunea de recoltare.");
				else
					RemovePlayerFromVehicle(playerid),
					SendClientMessage(playerid, COLOR_GRAD1, "You don't have the job of Farmer.");
			}
			else if(TipMas == VEHICLE_TYPE_FARMER_B) {
				if(PlayerInfo[playerid][pJob] == JOB_FARMER) 
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "*** "GRI3"Available commands: /takeflour | /sellflour");
				else
					RemovePlayerFromVehicle(playerid),
					SendClientMessage(playerid, COLOR_GRAD1, "You don't have the job of Farmer.");
			}
			else if(TipMas == VEHICLE_TYPE_SWEEPER) {
				if(PlayerInfo[playerid][pJob] == JOB_SWEEPER) {
					SendClientMessage(playerid, COLOR_ORANGE, "INFO: Type the command /startsweep and follow the route of checkpoint.");
					SendClientMessage(playerid, COLOR_ORANGE, "INFO: You will receive the money at every checkpoint.");
				}
				else
					RemovePlayerFromVehicle(playerid),
					SendClientMessage(playerid, COLOR_GRAD1, "You don't have the job of Sweeper.");
			}
			else if(TipMas == VEHICLE_TYPE_DUSTMAN) {
				if(PlayerInfo[playerid][pJob] == JOB_DUSTMAN)
					SendClientMessage(playerid, COLOR_ORANGE, "INFO: To start the work, type /startcollect and follow the checkpoints."),
					SendClientMessage(playerid, COLOR_ORANGE, "INFO: If you want to stop yourself from work, type /stopcollect.");
				else
					RemovePlayerFromVehicle(playerid),
					SendClientMessage(playerid, COLOR_GRAD1, "You don't have the job of Dustman.");
			}
			else if(TipMas == VEHICLE_TYPE_TRUCKER) {
				if(PlayerInfo[playerid][pJob] == JOB_TRUCKER)
					SendClientMessage(playerid, COLOR_ORANGE, "INFO: Your truck was loaded with 100/100 products."),
					SendClientMessage(playerid, COLOR_ORANGE, "INFO: To deliver the products, go to a biz and use the command /sellprods.");
				else
					RemovePlayerFromVehicle(playerid),
					SendClientMessage(playerid, COLOR_GRAD1, "You don't have the job of Trucker.");
			}
			if(JOBVehicleTimer[playerid]) {
				if(newcar == gLastCar[playerid])
					KillTimer(JOBVehicleTimer[playerid]), JOBVehicleTimer[playerid] = INVALID_VJOB_TIMER;
			}
		}
	}
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		if(PlayerInfo[playerid][pDrivingLicense] <= gLocalTimeStamp && !IsVehicleBike(vID) && !IsVehiclePlane(vID) && !IsVehicleBoat(vID)) {
			if(!TakingLesson{playerid}) {
				SendClientMessage(playerid, -1, "");
				SendClientMessage(playerid, COLOR_YELLOW, "Avertisment! "GRI3"Nu detii o licenta valida de condus autovehicule.");
				SendClientMessage(playerid, COLOR_GREY, "* Urmeaza insemnul de pe harta pentru a sustine examenul.");
				SendClientMessage(playerid, COLOR_GREY, "* Daca ai alte nelamuriri, tasteaza /needhelp si asteapta un Helper.");
				SetPlayerMapIcon(playerid, MAPICON_DRIVING, 328.546, -1512.85, 36.039, 55, 0, MAPICON_GLOBAL_CHECKPOINT);
				RemovePlayerFromVehicle(playerid);
			}
		}
		if(PlayerInfo[playerid][pFlyingLicense] <= gLocalTimeStamp && IsVehiclePlane(vID)) {
			if(!TakingLesson{playerid}) {
				SendClientMessage(playerid, -1, "");
				SendClientMessage(playerid, COLOR_YELLOW, "Avertisment! "GRI3"Nu detii o licenta valida pentru a pilota avioane.");
				SendClientMessage(playerid, COLOR_GREY, "* Urmeaza insemnul de pe harta pentru a sustine examenul.");
				SendClientMessage(playerid, COLOR_GREY, "* Daca ai alte nelamuriri, tasteaza /needhelp si asteapta un Helper.");
				SetPlayerMapIcon(playerid, MAPICON_FLYING, 1524.9723, -2432.8401, 13.5547, 5, 0, MAPICON_GLOBAL_CHECKPOINT);
				RemovePlayerFromVehicle(playerid);
			}
		}
		if(PlayerInfo[playerid][pSailingLicense] <= gLocalTimeStamp && IsVehicleBoat(vID)) {
			if(!TakingLesson{playerid}) {
				SendClientMessage(playerid, -1, "");
				SendClientMessage(playerid, COLOR_YELLOW, "Avertisment! "GRI3"Nu detii o licenta valida de navigat.");
				SendClientMessage(playerid, COLOR_GREY, "* Urmeaza insemnul de pe harta pentru a sustine examenul.");
				SendClientMessage(playerid, COLOR_GREY, "* Daca ai alte nelamuriri, tasteaza /needhelp si asteapta un Helper.");
				SetPlayerMapIcon(playerid, MAPICON_SAILING, 154.1533, -1946.6228, 5.3903, 9, 0, MAPICON_GLOBAL_CHECKPOINT);
				RemovePlayerFromVehicle(playerid);
			}
		}
		if(RadioCars[vID] != NONE_RADIO) { StartCarRadio(vID, RadioCars[vID], 1, playerid); }
		if(IsVehicleWithEngine(vID)) {
			if(ISBetween(CarInfo[vID][cFactionID], FACT_LSPD, MAX_FACTIONS) && CarInfo[vID][cLastBroken] <= gLocalTimeStamp)
				return SendClientMessage(playerid, COLOR_GRAD1, "Your engine is broken. Repair it first: "AURIU"/repaircar");
			new engine, lights, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(vID, engine, lights, alarm, doors, bonnet, boot, objective);
			if(engine == VEHICLE_PARAMS_ON)
				return SendClientMessage(playerid, COLOR_GREY, "The engine is already started.");
			else if(engine == VEHICLE_PARAMS_OFF)
				return SendClientMessage(playerid, COLOR_GREY, "The engine is stopped, To start press "VERDE"Y"GRI3" or type "GALBEN"/engine"GRI3".");
		}
		if(TaxiST[playerid][TaxiDuty]) {
			foreach (Player, i) {
				if(TaxiST[i][DrivingTaxi] == playerid) {
					if(TaxiST[i][TaxiEarn]) {
						format(string, MAXO_TEXT, "* You paid %s $%s for the amount of fare you owned him.", PlayerName(playerid), FormatNumber(TaxiST[i][TaxiEarn], 0, '.' ));
						SendClientMessage(i, COLOR_WHITE, string);
						format(string, MAXO_TEXT, "* You earned $%s from passenger %s.", FormatNumber(TaxiST[i][TaxiEarn], 0, '.' ), PlayerName(i));
						SendClientMessage(playerid, COLOR_WHITE, string);
						SafeGivePlayerMoney(playerid, TaxiST[i][TaxiEarn]);
						SafeGivePlayerMoney(i, -TaxiST[i][TaxiEarn]);
					}
					TaxiST[i][InTaxi] = 0;
					TaxiST[i][DrivingTaxi] = INVALID_PLAYER_ID;
					TaxiST[i][TaxiEarn] = TransportValue[playerid];
					RemovePlayerFromVehicle(i);
				}
			}
			format(string, MAXO_TEXT, "* You are now Off Duty and earned {FFFF2A}${FFFFFF}%s.", FormatNumber( TaxiST[playerid][TaxiEarn], 0, '.' ));
			SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
			TaxiST[playerid][TaxiDuty] = 0;
		}
	}
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
		StopAudioStreamForPlayer(playerid);
		HideCarTD(playerid);
	}
	if(GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) {
		if(RadioCars[vID] != NONE_RADIO)
			StartCarRadio(vID, RadioCars[vID], 1, playerid);
		foreach(Player, i) {
			if(TaxiST[i][DrivingTaxi] == playerid && TaxiST[i][TaxiDuty] > 0) {
				SendClientMessage(i, COLOR_LIGHTBLUE, "Your Transport Driver, has left vehicle.");
				RemovePlayerFromVehicle(i);
			}
			if(GetPlayerState(i) == PLAYER_STATE_DRIVER) {
				if(IsPlayerInVehicle(i, vID) && TaxiST[i][TaxiDuty] > 0) {
					new
						CostTransport = TransportValue[i];
					if(PlayerInfo[i][pCash] < CostTransport) {
						format(string, MAXO_TEXT, "* You need $%s to enter.", FormatNumber(CostTransport, 0, '.'));
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						RemovePlayerFromVehicle(playerid);
					}
					else
					{
						if(TaxiST[i][TaxiDuty] == 1) {
							format(string, MAXO_TEXT, "* You paid $%s to the Taxi Driver.", FormatNumber(CostTransport, 0, '.' ));
							SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
							format(string, MAXO_TEXT, "* Passenger %s has entered your Taxi.", PlayerName(playerid));
							SendClientMessage(i, COLOR_LIGHTBLUE, string);
							TaxiST[playerid][TaxiEarn] = CostTransport;
							TaxiST[playerid][InTaxi] = 1;
							TaxiST[playerid][DrivingTaxi] = i;
						}
					}
				}
			}
		}
	}
	clear.string(string);
	return 1;
}

public OnRconCommand(cmd[]) {
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid) {
	foreach(Player,i) {
		if(Spectated[i][Type] != ADMIN_SPEC_TYPE_NONE) {
			if(Spectated[i][IDj] == playerid) {
				SetTimerEx("SpecStreamUpdate", 1000, false, "iii", i, playerid, newinteriorid);
			}
		}
	}
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	new
		vID = GetPlayerVehicleID(playerid);
	if(newkeys == KEY_YES) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
			if(IsVehicleWithEngine(vID)) {
				if(ISBetween(CarInfo[vID][cFactionID], FACT_LSPD, MAX_FACTIONS) && CarInfo[vID][cLastBroken] <= gLocalTimeStamp)
					return SendClientMessage(playerid, COLOR_GRAD1, "Your engine is broken. Repair it first: "AURIU"/repaircar");
				if(CarInfo[vID][cType] == VEHICLE_TYPE_FARMER_A && PlayerInfo[playerid][pFarmingTime] == 0)
					return ShowPlayerInformation(playerid, "Farmer Job", "Trebuie sa mergi cu acest vehicul timp de ~r~02:00 minute ~y~cu o viteza > de 25 km/h pentru a indeplini misiunea de recoltare.");
				if(Gas[vID] < 1)
					return SendClientMessage(playerid, COLOR_GRAD1, "You don't have fuel anymore, the engine can't be started.");
				new engine, lights, alarm, doors, bonnet, boot, objective;
				GetVehicleParamsEx(vID, engine, lights, alarm, doors, bonnet, boot, objective);
				if(engine == VEHICLE_PARAMS_OFF) {
					gettime(gHours, gMinutes, gSeconds);
					if(gHours >= 19 || gHours < 8)
						SetVehicleParamsEx(vID, VEHICLE_PARAMS_ON, VEHICLE_PARAMS_ON, alarm, doors, bonnet, boot, objective);
					else
						SetVehicleParamsEx(vID, VEHICLE_PARAMS_ON, VEHICLE_PARAMS_OFF, alarm, doors, bonnet, boot, objective);
					SendClientMessage(playerid, COLOR_GREY, "You have turned "VERDE"on "GRI3"the engine.");
				}
				else if(engine == VEHICLE_PARAMS_ON) {
					SetVehicleParamsEx(vID, VEHICLE_PARAMS_OFF, VEHICLE_PARAMS_OFF, alarm, doors, bonnet, boot, objective);
					SendClientMessage(playerid, COLOR_GREY, "You have turned "ROSU"off "GRI3"the engine.");
				}
			}
		}
	}
	else if(newkeys == KEY_SECONDARY_ATTACK) {
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
			EnterPlayerInHouseBiz(playerid);
			EnterPlayerInHQ(playerid);
			EnterPlayerInOtherInterior(playerid);
		}
		if(NoFuel[playerid] == 1){
			TogglePlayerControllable(playerid, true);
			RemovePlayerFromVehicle(playerid);
			NoFuel[playerid] = 0;
			GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~Left car", 500, 3);
		}
		if(GetPlayerVehicleID(playerid) != INVALID_VEHICLE_ID) {
			if(IsARentableVehicle(GetPlayerVehicleID(playerid))) {
				TogglePlayerControllable(playerid, true);
				RemovePlayerFromVehicle(playerid);
			}
		}
	}
	else if(newkeys == KEY_CROUCH) {
		if(IsPlayerInAnyVehicle(playerid)) {
			if(IsPlayerCop(playerid)) {
				if(DelayBariera(LSPDGATE1)) {
					if(IsPlayerInRangeOfPoint(playerid, 30.0, 1544.7860, -1627.1316, 13.3828)) 
						DeschideLSPDGATE1();
				}
				if(DelayBariera(NGGATE1)) {
					if(IsPlayerInRangeOfPoint(playerid, 30.0, -1572.2012, 658.8007, 6.8812)) 
						DeschideNGGATE1();
				}
				if(DelayBariera(NGGATE2)) {
					if(IsPlayerInRangeOfPoint(playerid, 30.0, -1701.4327, 687.5764, 24.6882)) 
						DeschideNGGATE2();
				}
				if(DelayBariera(barrierdeposit)) {
					if(IsPlayerInRangeOfPoint(playerid, 30.0, -1526.4384, 481.3883, 6.9296)) 
						DeschideDEPGATE();
				}
				if(IsPlayerInRangeOfPoint(playerid, 30.0, 1597.846802, -1638.088257, 14.655367)) DeschideLSPDGATE2();
				else if(IsPlayerInRangeOfPoint(playerid, 30.0, -1631.5826, 688.1768, 8.7092)) DeschideNGGATE3();
			}
			if(PlayerInfo[playerid][pFactiune] == FACT_MEDIC) {
				if(IsPlayerInRangeOfPoint(playerid, 30.0, -2566.8726, 577.7012, 14.4598)) DeschideMEDGATE1();
				else if(IsPlayerInRangeOfPoint(playerid, 30.0, -2607.2712, 698.0201, 27.8125)) DeschideMEDGATE2();
				else if(IsPlayerInRangeOfPoint(playerid, 30.0, -2666.3245, 578.0235, 14.4612)) DeschideMEDGATE3();
			}
			if(PlayerInfo[playerid][pFactiune] == FACT_CNN) {
				if(IsPlayerInRangeOfPoint(playerid, 30.0, -2016.9852, 464.9441, 35.1719)) DeschideCNNGATE();
			}
		}
	}
	else if(newkeys == KEY_NO) {
		if(HaveAPersonalCar(playerid) != INVALID_VEHICLE_ID) {
			new personalcar = HaveAPersonalCar(playerid);
			if(PlayerInfo[playerid][pSQLID] == CarInfo[personalcar][cOwnerSQLID]) {
				SwitchVehicleLock(personalcar, playerid);  
			}
		}
	}
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return 1;
}

stock IsPlayerFounder(playerid) {
	if(strcmp(PlayerName(playerid), "Kurama", true) == 0 || strcmp(PlayerName(playerid), "Ursu93", true) == 0) 
		return true;
	return false;
}

// End Of File ...
