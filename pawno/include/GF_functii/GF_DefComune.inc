/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_DefComune_included
	#endinput
#else
	#define GF_DefComune_included
#endif

#define function%0(%1) forward%0(%1); public%0(%1)
#define ISBetween(%0,%1,%2) ((%1) <= %0 <= (%2))
#define clear.string(%0) \ 
	%0[0] = '\0'

#define NotAuthorized() SendClientMessage(playerid, 0xF67900F6, "DENIED: {FFF1AF}You are not authorized to use this command.")
#define IsPlayerSilent() SendClientMessage(playerid, -1, ""ROSU2"You cannot speak, you have been silenced. Use /mutetime.")
#define GoBackHint() SendClientMessage(playerid, 0xB4B5B7FF, "HINT: {FFF1AF}Use {00FFEE}/goback {FFF1AF}to restore previous position.")

#define MAXO_TEXT 128
#define MAXO_TEXT1 64
#define MAXO_TEXT2 256

#define C_FACTION_ANN	"{F58C5B}"
#define ALBASTRU 		"{2641FE}"
#define ROSU 			"{FF2400}"
#define PORTOCALIU 		"{FF9900}"
#define VERDE 			"{669933}"
#define VERDE2 			"{99CC33}"
#define VISINIU			"{8E2323}"
#define GRI 			"{6C6C6C}"
#define GALBEN 			"{F3FF02}"
#define ALBASTRU2 		"{33CCFF}"
#define ROZ 			"{FF33FF}"
#define ALBASTRU3 		"{000066}"
#define PORTOCALIU2 	"{FFCC00}"
#define ALBASTRU4 		"{33FFFF}"
#define MOV				"{CD9DFF}"
#define ALB				"{FFFFFF}"
#define GALBEN2 		"{D5E461}"
#define MOV2 			"{C9529A}"
#define GRI2 			"{939393}"
#define GRI3 			"{BABABA}"
#define ROSU2 			"{F08080}"
#define ALBASTRU5 		"{4682B4}"
#define AURIU			"{F5DEB3}"

#define COLOR_LIGHTBLUE 	0x33CCFFAA
#define COLOR_GRAD1	 		0xB4B5B7FF
#define COLOR_WHITE 		0xFFFFFFAA
#define COLOR_GRAD2 		0xBFC0C2AA
#define COLOR_GRAD3 		0xCBCCCEFF
#define COLOR_GRAD4 		0xD8D8D8FFF
#define COLOR_GRAD5 		0xE3E3E3FF
#define COLOR_GRAD6 		0xF0F0F0FF
#define COLOR_GREY 			0xAFAFAFAA
#define COLOR_FADE1 		0xE6E6E6E6
#define COLOR_FADE2 		0xC8C8C8C8
#define COLOR_FADE3 		0xAAAAAAAA
#define COLOR_FADE4 		0x8C8C8C8C
#define	COLOR_FADE5 		0x6E6E6E6E
#define COLOR_LIGHTGREEN 	0x9ACD32AA
#define COLOR_LIGHTRED  	0xFF6347AA
#define COLOR_GREEN 		0x33AA33AA
#define COLOR_YELLOW 		0xFFFF00AA
#define COLOR_RADIO			0x8D8DFF00
#define COLOR_DEPARTMENT 	0xFF8282AA
#define COLOR_ORANGE 		0xF97804FF
#define COLOR_OOC 			0xE0FFFFAA
#define COLOR_FAMILY		0x01FCFFC8
#define COLOR_JOB 			0xF67900F6
#define ROSSO 				0xFF3233FF
#define BIANCO 				0xFFFFFFFF
#define TURCHESE 			0x3C93FFFF
#define COLOR_PROPERTY		0x00FFFFFF
#define COLOR_NEWS2 		0xA6A6D2FF
#define COLOR_YELLOW2 		0xF5DEB3AA
#define COLOR_PURPLE 		0xC2A2DAAA
#define COLOR_BRIGHTRED 	0xDC143CAA
#define COLOR_RED 			0xAA3333AA
#define COLOR_RENTED		0xBEBEBEFF
#define COLOR_PROPERTY_NONE 0xABD51EFF

#define GasMax (100)
#define LSPD_VW 3000
#define SFPD_VW 3001
#define DMV_VW 3002
#define JAIL_VW 3003

#define FACTIONSPAWN_PRIMARY 0
#define FACTIONSPAWN_SECONDARY 1

#define TEST_TYPE_NONE 0
#define TEST_TYPE_CAR 1
#define TEST_TYPE_FLYING 2
#define TEST_TYPE_SAILING 3

#define MAPICON_DRIVING 1
#define MAPICON_FLYING  2
#define MAPICON_SAILING 3
#define MAPICON_FIREPLACE 4
#define MAPICON_FINDCAR 5
#define MAPICON_HOUSES 6

new vehName[][] = { "Landstalker", "Bravura", "Buffalo", "Linerunner", "Perrenial", "Sentinel", "Dumper", "Firetruck", "Trashmaster", "Stretch", "Manana", "Infernus", "Voodoo", "Pony", "Mule", "Cheetah", "Ambulance", "Leviathan", "Moonbeam", "Esperanto", "Taxi", "Washington", "Bobcat", "Whoopee", "BF Injection", "Hunter", "Premier",
"Enforcer", "Securicar", "Banshee", "Predator", "Bus", "Rhino", "Barracks", "Hotknife", "Trailer", "Previon", "Coach", "Cabbie", "Stallion", "Rumpo", "RC Bandit", "Romero", "Packer", "Monster", "Admiral", "Squalo", "Seasparrow", "Pizzaboy", "Tram", "Trailer", "Turismo", "Speeder", "Reefer", "Tropic", "Flatbed", "Yankee", "Caddy",
"Solair", "Berkley's RC Van", "Skimmer", "PCJ-600", "Faggio", "Freeway", "RC Baron", "RC Raider", "Glendale", "Oceanic", "Sanchez", "Sparrow", "Patriot", "Quad", "Coastguard", "Dinghy", "Hermes", "Sabre", "Rustler", "ZR-350", "Walton", "Regina", "Comet", "BMX", "Burrito", "Camper", "Marquis", "Baggage", "Dozer", "Maverick",
"News Chopper", "Rancher", "FBI Rancher", "Virgo", "Greenwood", "Jetmax", "Hotring", "Sandking", "Blista Compact", "Police Maverick", "Boxvillde", "Benson", "Mesa", "RC Goblin", "Hotring Racer A", "Hotring Racer B", "Bloodring Banger", "Rancher", "Super GT", "Elegant", "Journey", "Bike", "Mountain Bike", "Beagle", "Cropduster",
"Stunt", "Tanker", "Roadtrain", "Nebula", "Majestic", "Buccaneer", "Shamal", "Hydra", "FCR-900", "NRG-500", "HPV1000", "Cement Truck", "Tow Truck", "Fortune", "Cadrona", "FBI Truck", "Willard", "Forklift", "Tractor", "Combine", "Feltzer", "Remington", "Slamvan", "Blade", "Freight", "Streak", "Vortex", "Vincent", "Bullet", "Clover",
"Sadler", "Firetruck", "Hustler", "Intruder", "Primo", "Cargobob", "Tampa", "Sunrise", "Merit", "Utility", "Nevada", "Yosemite", "Windsor", "Monster", "Monster", "Uranus", "Jester", "Sultan", "Stratum", "Elegy", "Raindance", "RC Tiger", "Flash", "Tahoma", "Savanna", "Bandito", "Freight Flat", "Streak Carriage", "Kart", "Mower", "Dune",
"Sweeper", "Broadway", "Tornado", "AT-400", "DFT-30", "Huntley", "Stafford", "BF-400", "News Van", "Tug", "Trailer", "Emperor", "Wayfarer", "Euros", "Hotdog", "Club", "Freight Box", "Trailer", "Andromada", "Dodo", "RC Cam", "Launch", "Police Car", "Police Car", "Police Car", "Police Ranger", "Picador", "S.W.A.T", "Alpha", "Phoenix",
"Glendale", "Sadler", "Luggage", "Luggage", "Stairs", "Boxville", "Tiller", "Utility Trailer" };

#define DIALOGID_NO_ACTION 0
#define DIALOGID_REGISTER 1
#define DIALOGID_LOGIN 2
#define DIALOGID_SEX 3
#define DIALOGID_AGE 4
#define DIALOGID_EMAIL 5
#define DIALOGID_SWORD 6
#define DIALOGID_QUESTION_BAN 9
#define DIALOGID_OPTIONS_BAN 10
#define DIALOGID_MINUTE_BAN 11
#define DIALOGID_HOUR_BAN 12
#define DIALOGID_DMV_ACTION 13
#define DIALOGID_LIFT1_LSPD 14
#define DIALOGID_LIFT2_LSPD 15
#define DIALOGID_LIFT3_LSPD 16
#define DIALOGID_JOB_ARMSDEALER 17
#define DIALOGID_DMV_RLICENSE 18
#define DIALOGID_DMP_ACTION 19
#define DIALOGID_DMP_RLICENSE 20
#define DIALOGID_DMB_ACTION 21
#define DIALOGID_DMB_RLICENSE 22
#define DIALOGID_CAR_RADIO 23
#define DIALOGID_REPORT 24
#define DIALOGID_JOB_CARJACKER 25
#define DIALOGID_JOB_TRUCKER 26
#define DIALOGID_VEHICLE_REPAIR 27
#define DIALOGID_SAFE_INFO 28
#define DIALOGID_SAFE_DRUGS 29
#define DIALOGID_SAFE_MATERIALS 30
#define DIALOGID_SAFE_MONEY 31
#define DIALOGID_SAFE_PUT_DRUGS 32
#define DIALOGID_SAFE_TAKE_DRUGS 33
#define DIALOGID_SAFE_PUT_MATERIALS 34
#define DIALOGID_SAFE_TAKE_MATERIALS 35
#define DIALOGID_SAFE_PUT_MONEY 36
#define DIALOGID_SAFE_TAKE_MONEY 37
#define DIALOGID_SAFE_BALANCE 38
#define DIALOGID_JOB_SWEEPER 39
#define DIALOGID_SELECT_ROUTE 40
#define DIALOGID_JOB_FARMER 41
#define DIALOGID_JOB_DUSTMAN 42
#define DIALOGID_JOBS 43
#define DIALOGID_DEALERSHIP 44
#define DIALOGID_DAY_BAN 45
#define DIALOGID_MONTH_BAN 46
#define DIALOGID_YEAR_BAN 47
#define DIALOGID_PERM_BAN 48
#define DIALOGID_PLAYER_BANAT 49
#define DIALOGID_OFFBAN1 50
#define DIALOGID_OFFBAN2 51
#define DIALOGID_OFFWARN 52
#define DIALOGID_OFFWARN2 53
#define DIALOGID_JOB_DRUGSDEALER 54
#define DIALOGID_BUY_WALKIETALKIE 55
#define DIALOGID_REFERRAL_PLAYER 56


#define CP_NO_ACTION 	1
#define CP_LICENSES		2
#define CP_ENTER_BIZ 	3
#define CP_CALLER 		4
#define CP_FARMER		5
#define CP_SWEEPER		6
#define CP_DUSTMAN		7
#define CP_TRUCKER		8
#define CP_CARJACKER	9
#define CP_HOUSE		10
#define CP_SWEEPER2		11
#define CP_FMA_RACE 	12

new
	checkpointNoAction[MAX_PLAYERS],
	checkpointLicenses[MAX_PLAYERS],
	checkpointEnterBiz[MAX_PLAYERS],
	checkpointCaller[MAX_PLAYERS],
	checkpointFarmer[MAX_PLAYERS],
	checkpointSweeper[MAX_PLAYERS],
	checkpointDustman[MAX_PLAYERS],
	checkpointTrucker[MAX_PLAYERS],
	checkpointCarJacker[MAX_PLAYERS],
	checkpointHouse[MAX_PLAYERS],
	checkpointSweeper2[MAX_PLAYERS],
	checkpointFMARace[MAX_PLAYERS],
	CPid[MAX_PLAYERS]
;

new connectionHandle, rows, fields;

new gPlayerLogged[MAX_PLAYERS char];
new bool:ServerUnlocked = false;
#pragma unused ServerUnlocked

new
	Tutorial[MAX_PLAYERS],
	TutorialTimer[MAX_PLAYERS],
	SpectatePlayerID[MAX_PLAYERS],
	SpectateType[MAX_PLAYERS],
	Gas[MAX_VEHICLES],
	/* DMV System */
	DMVPrepare[MAX_PLAYERS],
	TakingLesson[MAX_PLAYERS char],
	DMVTimer[MAX_PLAYERS char],
	pTestType[MAX_PLAYERS char],
	// Other
	NoFuel[MAX_PLAYERS],
	IsPlayerCuffed[MAX_PLAYERS char],
	TicketOffer[MAX_PLAYERS],
	TicketMoney[MAX_PLAYERS],
	PillsOffer[MAX_PLAYERS],
	PillsPrice[MAX_PLAYERS],
	Pills[MAX_PLAYERS],
	PInfo_Active[MAX_PLAYERS],
	AcceptTime[MAX_PLAYERS],
	bool: ClientCaller[MAX_PLAYERS char],
	ClientAccept[MAX_PLAYERS],
	IsPlayerTied[MAX_PLAYERS char],
	IsPlayerSterilized[MAX_PLAYERS char],
	PlayerSterilizedTime[MAX_PLAYERS],
	IsPlayerInWar[MAX_PLAYERS char],
	GotHit[MAX_PLAYERS],
	GoChase[MAX_PLAYERS],
	GetChased[MAX_PLAYERS],
	OrderReady[MAX_PLAYERS],
	ConnectedToPC[MAX_PLAYERS],
	PlacedNews[MAX_PLAYERS],
	bool:news_duty[MAX_PLAYERS char],
	bool:news_accepted[MAX_PLAYERS char],
	news_occupied_with[MAX_PLAYERS],
	LiveOffer[MAX_PLAYERS],
	TalkingLive[MAX_PLAYERS],
	TransportValue[MAX_PLAYERS],
	HireCar[MAX_PLAYERS],
	gLastCar[MAX_VEHICLES],
	gLastDriver[MAX_VEHICLES],
	showTurfs[MAX_PLAYERS char],
	PlayerAtRivalWar[MAX_PLAYERS],
	FarmPartener[MAX_PLAYERS],
	FarmCantitate[MAX_PLAYERS],
	FarmCantitateFaina[MAX_PLAYERS],
	JOBVehicleTimer[MAX_PLAYERS],
	dustvehicle[MAX_PLAYERS],
	IsCopDuty[MAX_PLAYERS char],
	IsCopUndercover[MAX_PLAYERS char],
	PlayerStoned[MAX_PLAYERS],
	bool:OnFly[MAX_PLAYERS char],
	gFindMCarTime[MAX_PLAYERS],
	bool:gFindMyCar[MAX_PLAYERS char],
	PTransfered[MAX_PLAYERS char],
	TogglePlayerLive[MAX_PLAYERS char],
	PropertyOffer[MAX_PLAYERS],
	PropertyPrice[MAX_PLAYERS],
	NewbieChatTimer[MAX_PLAYERS],
	bool:isNewbieChatActive = false,
	iPlayerChatTime[MAX_PLAYERS],
	szPlayerChatMsg[MAX_PLAYERS][MAXO_TEXT],
	PlayerIP[MAX_PLAYERS][16],
	PhoneOnline[MAX_PLAYERS],
	Mobile[MAX_PLAYERS],
	RingTone[MAX_PLAYERS],
	CellTime[MAX_PLAYERS],
	CallCost[MAX_PLAYERS],
	JucatorulAreMateriale[MAX_PLAYERS],
	LocatiaRandom[MAX_PLAYERS char],
	GunOffer[MAX_PLAYERS],
	GunPrice[MAX_PLAYERS],
	Gun[MAX_PLAYERS],
	ConsumingMoney[MAX_PLAYERS],
	CurrentMoney[MAX_PLAYERS],
	JucatorulAreDroguri[MAX_PLAYERS],
    WasFlew[MAX_PLAYERS],
    DrugsOffer[MAX_PLAYERS],
    DrugsPrice[MAX_PLAYERS],
    Drugs[MAX_PLAYERS],
    AntiSpamProtection[MAX_PLAYERS],
    ItemFrom247[MAX_PLAYERS],
    HaveFishingRog[MAX_PLAYERS char],
    HaveFishingBait[MAX_PLAYERS],
    HaveGasCan[MAX_PLAYERS char],
    HaveGasInCan[MAX_PLAYERS]
;

#define INVALID_TEXTDRAW_ID (Text:-1)
new
	Text:turftxt[MAX_PLAYERS] = INVALID_TEXTDRAW_ID,
	Text:PInfo_TXT[MAX_PLAYERS] = { INVALID_TEXTDRAW_ID, ...},
	Text:spectatortxt[MAX_PLAYERS] = INVALID_TEXTDRAW_ID,
	Text:Animation = INVALID_TEXTDRAW_ID,
	Text:DigiHP[MAX_PLAYERS],
	Text:DigiAP[MAX_PLAYERS],
	Text:propertytxt,
	PlayerText: Speedo
;

new gGlobalTick;

#define NEWBIE_TIME 30

new levelcost = 5000;
new levelexp = 4;
new mapname[64];
new ExpiraLicenta = 2592000;
new hitfound = 0;
new HitM = 999;
new cchargetime = 60;
new callcost = 10;
new FarmCantitateHambar = 0;

new gLocalTimeStamp;
new gHours, gMinutes, gSeconds;
new gYears, gMonths, gDays;

new Menu:MenuGunsAN;
new Menu:MenuBurger;
new Menu:MenuStore;
new Menu:MenuStore2;
new	Menu:HUMenu1;
new	Menu:HUMenu2;
new	Menu:MagazinMenu;
new	Menu:MagazinMenu1;

#define MAX_SPIKESTRIPS 200

enum sInfo
{
	sCreated,
    Float:sX,
    Float:sY,
    Float:sZ,
    sObject,
};
new SpikeInfo[MAX_SPIKESTRIPS][sInfo];

#define MAX_PASS_LENGHT (129)
enum pInfo {
	pSQLID,
	pPassword[MAX_PASS_LENGHT],
	pEmail[MAXO_TEXT],
	pSecret[MAXO_TEXT],
	pLastLoginDate[MAXO_TEXT],
	pReg,
	pTut,
	pSex,
	pAge,
	pCash,
	pLevel,
	pSkin,
	pLastLogin,
	pAdmin,
	pHelper,
	pLeader,
	pFactiune,
	pRank,
	pTeam,
	pAccount,
	pExp,
	pUpgradeP,
	Float:pSHealth,
	pConnectTime,
	pDeelayNeedHelp,
	pMute,
	pMuteTime,
	pWarnings,
	pDrivingLicense,
	pFlyingLicense,
	pSailingLicense,
	pPhousekey,
	pPbizkey,
	pCigarettes,
	pLighter,
	pPnumber,
	pPhoneBook,
	pInBizzID,
	pWlvl,
	pJailed,
	pJailTime,
	pDrugs,
	pMats,
	pFJoined[20],
	pPills,
	pUsePillsTime,
	pReportTime,
	pInHouseID,
	pInHQID,
	pHeadValue,
	pContracts,
	pPayCheck,
	pNewsSkill,
	pFWarn,
	pKills,
	pDeaths,
	pCarTime,
	pDustSkill,
	pJob,
	pTakeVehiclePause,
	pFactionSpawn,
	pSpawnChange,
	pInterior,
	pVirtualWorld,
	pActiveCounter,
	pPayDayTime,
	pActiveTime,
	pFarmerSkill,
	pCarJackerSkill,
	pGiftPoints,
	pCursorDealer,
	pCarSlots,
	pFarmingTime,
	pAdvertismentTime,
	pDrugsTime,
	pRequestingBackup,
	pTazed,
	pNMute,
	pDisable,
	pDisableTime,
	pMissions,
	pDailyMission[2],
	pProgress[2],
	pNeedProgress[2],
	pTotalPD,
	pLastDayOfPD,
	pLastTimeOfPD,
	pArmsDealerSkill,
	pWantedDown,
	pCPSweeper,
	pSweeperSkill,
	pCPSweeper2,
	pDrugsDealerSkill,
	pFrequence,
	pFreqNO,
	pDice,
	pBiggestFish,
	pFishSkill,
	pReferralID,
	pReferralCash,
	pReferralRespect,
	pRobPoints
};
new PlayerInfo[MAX_PLAYERS][pInfo];

#define BIZ_TYPE_ANY (-1)
#define BIZ_TYPE_GS 0
#define BIZ_TYPE_HOUSEUPG 1
#define BIZ_TYPE_BENZINARIE 2
#define BIZ_TYPE_BURGERSHOT 3
#define BIZ_TYPE_24_7 4
#define BIZ_TYPE_ELECTRICA 5
#define BIZ_TYPE_BANK 6
#define BIZ_TYPE_RENTCAR 7 
#define BIZ_TYPE_BINCO 8

#define FACT_CIVIL 0
#define FACT_LSPD 1
#define FACT_FBI 2
#define FACT_MEDIC 3
#define FACT_LCN 4
#define FACT_YKZ 5
#define FACT_HITMAN 6
#define FACT_CNN 7
#define FACT_TAXI 8
#define FACT_BLOODS 9
#define FACT_CRIPS 10
#define FACT_FMA 11

#define DEFAULT_RESPAWN_TIME 1800

#define VEHICLE_TYPE_GENERIC 0
#define VEHICLE_TYPE_CARTEST 1
#define VEHICLE_TYPE_FLYTEST 2
#define VEHICLE_TYPE_BOATTEST 3
#define VEHICLE_TYPE_FACTION 4
#define VEHICLE_TYPE_RENTCAR 5
#define VEHICLE_TYPE_FARMER_A 6
#define VEHICLE_TYPE_FARMER_B 7
#define VEHICLE_TYPE_SWEEPER 8
#define VEHICLE_TYPE_DUSTMAN 9
#define VEHICLE_TYPE_TRUCKER 10
#define VEHICLE_TYPE_PERSONAL 11

enum weather_info {
	wt_id,
	wt_text[MAXO_TEXT1]
};

new gRandomWeatherIDs[21][weather_info] = {
	{0, "Extra Sunny"},
	{1, "Sunny"},
	{2, "Extra Sunny Smog"},
	{3, "Sunny Smog"},
	{4, "Cloudy"},
	{5, "Sunny"},
	{6, "Extra Sunny"},
	{7, "Cloudy"},
	{8, "Rainy"},
	{9, "Foggy"},
	{10, "Sunny Vegas"},
	{11, "Extra Sunny Vegas (heat waves)"},
	{12, "Cloudy Vegas"},
	{13, "Extra Sunny Country Side"},
	{14, "Sunny Country Side"},
	{15, "Cloudy Country Side"},
	{16, "Rainy Country Side"},
	{17, "Extra Sunny Desert"},
	{18, "Sunny Desert"},
	{19, "Sand Storm Desert"},
	{20, "Underwater (greenish, foggy)"}
};

new RandomMSG[][] = {
	"Nu sunt permise afacerile cu bani reali. Orice abatere, se pedepseste cu +1 warn!",
	"Imprumuturile de orice fel (bani/proprietati) se fac pe propria raspundere. Nu ai garantia ca le vei recupera!",
	"Pentru a castiga bani, ia-ti un job si distreaza-te cu prietenii tai."
};

enum hNews {
	hTaken1,
	hTaken2,
	hTaken3,
	hTaken4,
	hTaken5,
	hAdd1[MAXO_TEXT],
	hAdd2[MAXO_TEXT],
	hAdd3[MAXO_TEXT],
	hAdd4[MAXO_TEXT],
	hAdd5[MAXO_TEXT],
	hContact1[MAXO_TEXT],
	hContact2[MAXO_TEXT],
	hContact3[MAXO_TEXT],
	hContact4[MAXO_TEXT],
	hContact5[MAXO_TEXT],
};
new News[hNews];

enum txInfo {
	TaxiDuty,
	TaxiEarn,
	InTaxi,
	DrivingTaxi
};
new TaxiST[MAX_PLAYERS][txInfo];

enum eGAC {
	eGACSpeed,
	eGACTunningHack,
	eGWarningCheat
};
new AntiCheat[MAX_PLAYERS][eGAC];

#define NOT_USE_RESPAWN	0
#define USE_RESPAWN	1

// --------------------
// --- Jobs Names
// --------------------

#define JOB_NONE 0
#define JOB_FARMER 1
#define JOB_SWEEPER 2
#define JOB_DUSTMAN 3
#define JOB_TRUCKER 4
#define JOB_CARJACKER 5
#define JOB_ARMSDEALER 6
#define JOB_DRUGSDEALER 7

enum PN {
	nume_introdus[MAX_PLAYER_NAME],
	mesaj_introdus[MAXO_TEXT],
	jucator_gasit
}
new PartialName[MAX_PLAYERS][PN];

#if !defined MAX_JOIN_LOGS
    #define MAX_JOIN_LOGS (50)
#endif

#define IP_LIMIT 2
#define SAME_IP_CONNECT 2
#define Time_Limit 3500

new
	ban_s[25]
;

#define ACTION_KICK 1
#define ACTION_BAN 2
#define ACTION_JAIL 3
#define ACTION_WARN 4
#define ACTION_MUTE 5

function InsertSanctionInPanel(targetid, playerid, type_s, reason[]) {
	new string[MAXO_TEXT2], nume_admin[64], nume_victima[64];
	format(nume_admin, 64, "%s (%d)", PlayerName(playerid), PlayerInfo[playerid][pSQLID]);
	format(nume_victima, 64, "%s (%d)", PlayerName(targetid), PlayerInfo[targetid][pSQLID]);
	format(string, MAXO_TEXT2, "INSERT INTO `sanctions` (`Player`, `By`, `Userid`, `Type`, `Reason`) VALUES ('%s', '%s', '%d', '%d', '%s')", nume_victima, nume_admin, PlayerInfo[playerid][pSQLID], type_s, reason);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", ADDCHAT_THREAD_ID);
	clear.string(string);
	return true;
}

#define LOG_VEHICLES 1
#define LOG_HOUSES 2
#define LOG_BUSINESS 3
#define LOG_TRANSFER 4
#define LOG_PAY 5

function InsertLogInPanel(playerid, type_l, text[]) {
	new string[MAXO_TEXT2];
	GetPlayerIp(playerid, PlayerIP[playerid], 16);
	format(string, MAXO_TEXT2, "INSERT INTO `logs` (`Userid`, `Text`, `Type`, `IP`) VALUES ('%d', '%s', '%d',  '%s')", PlayerInfo[playerid][pSQLID], text, type_l, PlayerIP[playerid]);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", ADDCHAT_THREAD_ID);
	clear.string(string);
	return true;
}

#define MISSION_RENTCAR 0
#define MISSION_ANNOUNCE 1
#define MISSION_PILLS 2
#define MISSION_DELIVERYPRODS 3
#define MISSION_DELIVERYVEHS 4
#define MISSION_SELLFLOUR 5
#define MISSION_BUYGUN 6
#define MISSION_BUYFOOD 7

#define ADMIN_SPEC_TYPE_NONE 	0
#define ADMIN_SPEC_TYPE_PLAYER 	1
#define ADMIN_SPEC_TYPE_VEHICLE 2

#define TextDrawSetFormat(%0,%1) do { new _str[128]; format(_str,128,%1); TextDrawSetString(%0,_str); } while(FALSE)

#define IANUARIE 1
#define FEBRUARIE 2
#define MARTIE 3
#define APRILIE 4
#define MAI 5
#define IUNIE 6
#define IULIE 7
#define AUGUST 8
#define SEPTEMBRIE 9
#define OCTOMBRIE 10
#define NOIEMBRIE 11
#define DECEMBRIE 12

#define BLACK 0x000000FF

new
	Text:TextdrawHour = INVALID_TEXTDRAW_ID,
	Text:TextdrawDay = INVALID_TEXTDRAW_ID,
	Text:TextdrawMonth = INVALID_TEXTDRAW_ID,
	Text:Logo = INVALID_TEXTDRAW_ID
;

new FALSE = false;
new ghour = 0;
new realtime = 1;
new timeshift = -1;
new shifthour;

#define DIVBY 1.450
#define INVALID_VEH_HP (-1)
#define COLOR_BRIGHTRED 0xDC143CAA

new Float:VHPBar[MAX_PLAYERS];

new
	Text: Fuel[MAX_PLAYERS] = {INVALID_TEXTDRAW_ID, ...},
	Text: BlackBox = INVALID_TEXTDRAW_ID,
	Text: Moving[MAX_PLAYERS] = INVALID_TEXTDRAW_ID,
	Text: VehicleHPBar[13]= { INVALID_TEXTDRAW_ID, ...}
;

#define COLOR_FACT_CIVIL 0xFFFFFFAA
#define COLOR_FACT_LSPD 0x2641FEAA
#define COLOR_FACT_FBI 0x2641FEAA
#define COLOR_FACT_MEDIC 0xFF6347AA
#define COLOR_FACT_LCN 0xFF680090
#define COLOR_FACT_YKZ 0xF81414AA
#define COLOR_FACT_HITMAN 0x8E2323FF
#define COLOR_FACT_CNN 0xC2A2DAAA
#define COLOR_FACT_TAXI 0xFFFF00AA
#define COLOR_FACT_BLOODS 0x006C0090
#define COLOR_FACT_CRIPS 0xD900D3C8

#define INVALID_VJOB_TIMER 0

enum SpecPlayerEnum {
	bool:Status,
	bool:Command,
	vehicleIDj,
	IDj,
	Type,
}
new Spectated[MAX_PLAYERS][SpecPlayerEnum];

stock Float:GetDistanceBetweenPlayers(p1, p2) {
	new
		Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2;
	if(!IsPlayerConnected(p1) || !IsPlayerConnected(p2)) {
		return -1.00;
	}
	GetPlayerPos(p1, x1, y1, z1);
	GetPlayerPos(p2, x2, y2, z2);
	return floatsqroot(floatpower(floatabs(floatsub(x2, x1)), 2) + floatpower(floatabs(floatsub(y2, y1)), 2) + floatpower(floatabs(floatsub(z2, z1)), 2));
}

enum gbInfo {
	Float:gbPos[4],
	gbInterior,
	gbVirtualWorld,
	gbHouseID,
	gbBizzID,
	Float:gbHealth,
	Float:gbArmour,
	gbWeapons[6],
	bool:gbUsed
};
new GoBackInfo[MAX_PLAYERS][gbInfo];

stock Float:GetDistanceBetweenPoints(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2) {
	return floatadd(floatadd(floatsqroot(floatpower(floatsub(x1, x2), 2)), floatsqroot(floatpower(floatsub(y1, y2), 2))), floatsqroot(floatpower(floatsub(z1, z2), 2)));
}

new
	Float: JailLocation[24][3] = {
		{ 1757.3688,-1564.4794,1734.9430 },
		{ 1761.6173,-1563.5674,1734.9430 },
		{ 1766.3730,-1564.7240,1734.9430 },
		{ 1770.3439,-1563.8926,1734.9430 },
		{ 1774.3746,-1564.4496,1734.9430 },
		{ 1778.6067,-1562.6073,1734.9430 },
		{ 1757.3892,-1563.6677,1738.6935 },
		{ 1761.8068,-1563.9098,1738.6935 },
		{ 1765.8212,-1563.6265,1738.6935 },
		{ 1770.1068,-1563.9138,1738.6935 },
		{ 1774.2511,-1563.3611,1738.6935 },
		{ 1778.4351,-1563.5629,1738.6937 },
		{ 1778.6292,-1581.2501,1734.9430 },
		{ 1774.1827,-1582.5835,1734.9430 },
		{ 1770.2516,-1582.0681,1734.9430 },
		{ 1766.0259,-1581.9242,1734.9430 },
		{ 1761.5872,-1581.6364,1734.9430 },
		{ 1757.4595,-1582.5719,1734.9430 },
		{ 1778.4358,-1581.9659,1738.7173 },
		{ 1774.5413,-1581.7151,1738.7173 },
		{ 1770.2783,-1582.8451,1738.7173 },
		{ 1765.4357,-1582.8391,1738.7173 },
		{ 1761.4236,-1583.4019,1738.7173 },
		{ 1757.2567,-1583.0640,1738.7173 }
	};

stock PutPlayerInCell(playerid) {
	new cellid = RandomEx(1, 24);
	if(IsPlayerInAnyVehicle(playerid)) 
		RemovePlayerFromVehicle(playerid);
	SafeSetPlayerVirtualWorld(playerid, JAIL_VW); 
	SetPlayerPos(playerid, JailLocation[cellid][0], JailLocation[cellid][1], JailLocation[cellid][2]);
	SafeSetPlayerInterior(playerid, 0);
	return true;
}

stock DateToTimestamp( timestamp, _form=0 )
{
    /*
        ~ convert a Timestamp to a Date.
        ~ 10.07.2009

        date( 1247182451 )  will print >> 09.07.2009-23:34:11
        date( 1247182451, 1) will print >> 09/07/2009, 23:34:11
        date( 1247182451, 2) will print >> July 09, 2009, 23:34:11
        date( 1247182451, 3) will print >> 9 Jul 2009, 23:34
    */
    new Year=1970, Day=0, Month=0, Hour=0, Mins=0, Sec=0;

    new Days_of_Month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    new names_of_Month[12][10] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
    new returnstring[32];

    while(timestamp>31622400){
        timestamp -= 31536000;
        if ( ((Year % 4 == 0) && (Year % 100 != 0)) || (Year % 400 == 0) ) timestamp -= 86400;
        Year++;
    }

    if ( ((Year % 4 == 0) && (Year % 100 != 0)) || (Year % 400 == 0) )
        Days_of_Month[1] = 29;
    else
        Days_of_Month[1] = 28;


    while(timestamp>86400){
        timestamp -= 86400, Day++;
        if(Day==Days_of_Month[Month]) Day=0, Month++;
    }

    while(timestamp>60){
        timestamp -= 60, Mins++;
        if( Mins == 60) Mins=0, Hour++;
    }

    Sec=timestamp;

    switch( _form ){
        case 1: format(returnstring, 31, "%02d/%02d/%d %02d:%02d:%02d", Day+1, Month+1, Year, Hour, Mins, Sec);
        case 2: format(returnstring, 31, "%s %02d, %d, %02d:%02d:%02d", names_of_Month[Month],Day+1,Year, Hour, Mins, Sec);
        case 3: format(returnstring, 31, "%d %c%c%c %d, %02d:%02d", Day+1,names_of_Month[Month][0],names_of_Month[Month][1],names_of_Month[Month][2], Year,Hour,Mins);

        default: format(returnstring, 31, "%02d/%02d/%d %02d:%02d:%02d", Day+1, Month+1, Year, Hour, Mins, Sec);
    }

    return returnstring;
}

new OldClassSelect[MAX_PLAYERS];
new RaceParticipant[MAX_PLAYERS];    
#pragma unused RaceParticipant               
new pFMAMessageON[MAX_PLAYERS char];

#define INVALID_RACE_ID 		(-1)
#define MAX_RACE_PARTICIPANTS 	12
#define COLISION_ENABLED 		0
#define COLISION_DISABLED 		1


new IDCursa = INVALID_RACE_ID;

enum RaceVoteInfo 
{
	VotedYes,
	VotedNo,
	FinalVote,
	Counter
}
new
	RaceVoteColision[RaceVoteInfo];

enum InfoRacePL
{
	IdRace,
	TimeRC,
	RLap,
	Checkpoint,
	RReady,
	Builder,
	RaceEditorId,
	CheckEnable,
	Pursuer,
	Points,
	Position,
	Colision // 1 disable (adica trece prin masinile celorlalti), iar 0 enable
};
new RacePL[MAX_PLAYERS][InfoRacePL];

#define MAX_RACES              40
#define MAX_CHECKPOINT        	50

#define RACE_CHECKPOINT_NORMAL		0
#define RACE_CHECKPOINT_FINNORMAL	1
#define RACE_CHECKPOINT_NORMAL2		2
#define RACE_CHECKPOINT_AIR			3	
#define RACE_CHECKPOINT_FINAIR		4	

#define NO_RECORD_YET			0	

enum InfoRace {
	IDCursaDB,
	Nome[MAX_PLAYER_NAME],
	Laps,
	CheckpointNr,
	Chase,
	Costs,
	Participants,
	ParticipantsReady,
	Started,
	Record,
	RacePLRecord[MAX_PLAYER_NAME],
	RCreator[MAX_PLAYER_NAME],
	Podium,
	Air 
};
new Race[MAX_RACES][InfoRace];

enum CheckInfo {
	Float:CXPos,
	Float:CYPos,
	Float:CZPos
};
new CheckpointRace[MAX_RACES][MAX_CHECKPOINT][CheckInfo];

new VeryLargeString[3072];

// End Of File ...
