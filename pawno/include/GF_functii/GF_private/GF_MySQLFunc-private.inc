/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_MySQLFunc_included
	#endinput
#else
	#define GF_MySQLFunc_included
#endif

#if defined _srv_official
	#define MYSQL_HOST "localhost"
	#define	MYSQL_USER "root"
	#define	MYSQL_DATA "mydb"
	#define	MYSQL_PASS ""
	/*#define MYSQL_HOST "193.203.39.73"
	#define	MYSQL_USER "hc95samp76"
	#define	MYSQL_DATA "hc95samp76"
	#define	MYSQL_PASS "YzWwoGppRImKAaOo"
	#define BIND "188.212.102.25"
	#define MYSQL_HOST "188.212.100.198"
	#define	MYSQL_USER "client111_samp"
	#define	MYSQL_DATA "client111_samp"
	#define	MYSQL_PASS "22sjSWw2L1Lv"*/
#else
	/*#define MYSQL_HOST "193.203.39.132"
	#define	MYSQL_USER "kuramaeg"
	#define	MYSQL_DATA "kuramaeg"
	#define	MYSQL_PASS "Warlord1996"*/
	#define MYSQL_HOST "localhost"
	#define	MYSQL_USER "root"
	#define	MYSQL_DATA "mydb"
	#define	MYSQL_PASS ""
#endif

stock MySQLConnect(host[], user[], data[], pass[]) {
	connectionHandle = mysql_connect(host, user, data, pass);
	print("It stabilizes the connection to the database ...");
	printf("SQL_HOST: "MYSQL_HOST" SQL_USER: "MYSQL_USER" SQL_DATA: "MYSQL_DATA", SQL_PASS: "MYSQL_PASS"");
	return true;
}

AntiDeAMX() {
    new antidamx[][] = {
                "Unarmed (Fist)",
                "Brass K",
                "Fire Ex"
    };
    #pragma unused antidamx
}

stock SavePlayerData(playerid) {
	new
		sqlid = PlayerInfo[playerid][pSQLID], string[MAXO_TEXT2];
	format(string, MAXO_TEXT2, "UPDATE players SET Mute = %d, MuteTime = %d WHERE ID = %d", PlayerInfo[playerid][pMute], PlayerInfo[playerid][pMuteTime], sqlid);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	format(string, MAXO_TEXT, "UPDATE players SET PayCheck = %d WHERE ID = %d", PlayerInfo[playerid][pPayCheck], sqlid);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	format(string, MAXO_TEXT, "UPDATE players SET JailTime = %d WHERE ID = %d", PlayerInfo[playerid][pJailTime], PlayerInfo[playerid][pSQLID]);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	format(string, MAXO_TEXT, "UPDATE players SET DisableTime = %d WHERE ID = %d", PlayerInfo[playerid][pDisableTime], PlayerInfo[playerid][pSQLID]);
	mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
	clear.string(string);
	return true;
}

// End Of File ...
