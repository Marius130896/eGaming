/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_WantedSystem_included
	#endinput
#else
	#define GF_WantedSystem_included
#endif

#define WANTED_DOWN_TIME 10

new
	Text:tStar7=Text:INVALID_TEXT_DRAW,
	Text:tStar8=Text:INVALID_TEXT_DRAW,
	Text:tStar9=Text:INVALID_TEXT_DRAW,
	Text:tStar10=Text:INVALID_TEXT_DRAW,
	Text:TDWantedDown[MAX_PLAYERS] = {Text:INVALID_TEXT_DRAW, ...}
;

#define WLCheck(%1) if ( PlayerInfo[wantedto][pWlvl] >= %1 ) TextDrawShowForPlayer( wantedto, tStar%1 ); else TextDrawHideForPlayer( wantedto, tStar%1 )

Text:CreateStarTD( starnum ) {
	new Text:tStar = TextDrawCreate( 503.5 - ( 18 * ( starnum - 7 ) ), 102.1, "]" );

	TextDrawColor          ( tStar, 0x906210FF );
	TextDrawBackgroundColor( tStar, 0x000000AA );
	TextDrawFont           ( tStar,          2 );
	TextDrawSetShadow      ( tStar,          0 );
	TextDrawSetProportional( tStar,       true );
	TextDrawLetterSize     ( tStar,  0.6,  2.4 );
	TextDrawAlignment      ( tStar,          3 );
	TextDrawSetOutline     ( tStar,          1 );

	return tStar;
}

stock WlvlInit() {
	tStar7  = CreateStarTD(  7 );
	tStar8  = CreateStarTD(  8 );
	tStar9  = CreateStarTD(  9 );
	tStar10 = CreateStarTD( 10 );
	for (new i; i < MAX_PLAYERS; i ++) PlayerInfo[i][pWlvl] = 0;
}

stock SetPlayerWanted(wantedto, wantedfrom, level) {
	#pragma unused wantedfrom
	new query[MAXO_TEXT];
	if(level )
		PlayerInfo[wantedto][pWantedDown] = 60 * WANTED_DOWN_TIME;
	else
	{
		PlayerInfo[wantedto][pWantedDown] = 0;
		UpdateWantedDown(wantedto);
	}
	if(level >= 0) {
		SetPlayerWantedLevel(wantedto, level);
		WLCheck(7);
		WLCheck(8);
		WLCheck(9);
		WLCheck(10);
	}
	format(query, MAXO_TEXT, "UPDATE players SET Wanted = %d WHERE ID = %d", level, PlayerInfo[wantedto][pSQLID]);
	mysql_tquery(connectionHandle, query, "NoReturnThread", "d", UPDATE_THREAD_ID);
	clear.string(query);
	return true;
}

stock UpdateWantedDown(playerid, wTime = 0) {
	if(gPlayerLogged{playerid}) {
		new string[32];
		if(wTime) {
			format(string, sizeof(string), "~w~Wanted Down: ~r~%s", ConvertTime(wTime));
			TextDrawSetString(TDWantedDown[playerid], string);
			TextDrawShowForPlayer(playerid, TDWantedDown[playerid]);
		} 
		else 
		{
			TextDrawHideForPlayer(playerid, TDWantedDown[playerid]);
			clear.string(string);
		}
	}
	return true;
}

// End Of File ...
