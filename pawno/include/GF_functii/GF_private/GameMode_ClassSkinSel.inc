/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/

#if defined GameMode_ClassSkinSel_included
	#endinput
#else
	#define GameMode_ClassSkinSel_included
#endif

#define MAX_SKINS 			310

new
	PlayerText:gCurrentPageTextDrawId[MAX_PLAYERS]=PlayerText:INVALID_TEXT_DRAW,
	PlayerText:gHeaderTextDrawId[MAX_PLAYERS]=PlayerText:INVALID_TEXT_DRAW,
	PlayerText:gBackgroundTextDrawId[MAX_PLAYERS]=PlayerText:INVALID_TEXT_DRAW,
	PlayerText:gNextButtonTextDrawId[MAX_PLAYERS]=PlayerText:INVALID_TEXT_DRAW,
	PlayerText:gPrevButtonTextDrawId[MAX_PLAYERS]=PlayerText:INVALID_TEXT_DRAW,
	PlayerText:gCancelButtonTextDrawId[MAX_PLAYERS]=PlayerText:INVALID_TEXT_DRAW;

enum sknInfo
{
	faction,
	rankid,
	skinid,
	Float:ppos_x,
	Float:ppos_y,
	Float:ppos_z,
	Float:ppos_a,
	ppos_int,
	Float:cpos_x,
	Float:cpos_y,
	Float:cpos_z,
	Float:cpos_zDif
};
new SkinInfo[MAX_SKINS][sknInfo];
new wSkinClass[MAX_SKINS];

stock LoadSkins() return mysql_tquery(connectionHandle, "SELECT * FROM skinuri_class", "InitSkinThread", "d", SKINS_THREAD_ID);

function InitSkinThread(extraid)
{
	rows = cache_get_row_count();
	new factiune;
	
	for(new i;i < rows;i++)
	{
		factiune = cache_get_row_int(i, 1);
		SkinInfo[i][faction] = factiune;
		SkinInfo[i][rankid] = cache_get_row_int(i, 2);
		SkinInfo[i][skinid] = cache_get_row_int(i, 3);
		SkinInfo[i][ppos_x] = cache_get_row_float(i, 4);
		SkinInfo[i][ppos_y] = cache_get_row_float(i, 5);
		SkinInfo[i][ppos_z] = cache_get_row_float(i, 6);
		SkinInfo[i][ppos_a] = cache_get_row_float(i, 7);
		SkinInfo[i][ppos_int] = cache_get_row_int(i, 8);
		SkinInfo[i][cpos_x] = cache_get_row_float(i, 9);
		SkinInfo[i][cpos_y] = cache_get_row_float(i, 10);
		SkinInfo[i][cpos_z] = cache_get_row_float(i, 11);
		SkinInfo[i][cpos_zDif] = cache_get_row_float(i, 12);
		wSkinClass[SkinInfo[i][skinid]] = AddPlayerClass(SkinInfo[i][skinid],SkinInfo[i][ppos_x],SkinInfo[i][ppos_y],SkinInfo[i][ppos_z],SkinInfo[i][ppos_a],-1,-1,-1,-1,-1,-1);
	}
	printf("InitSkinThread() - called (%d skins loaded).", rows);
	return true;
}

stock SetupPlayerForClassSelection(playerid,classid) {
	new VecheaClasa = OldClassSelect[playerid];
	SafeSetPlayerInterior(playerid, SkinInfo[classid][ppos_int]);
	SafeSetPlayerPos(playerid,SkinInfo[classid][ppos_x],SkinInfo[classid][ppos_y],SkinInfo[classid][ppos_z]);
	SetPlayerFacingAngle(playerid, SkinInfo[classid][ppos_a]);
	if(SkinInfo[classid][cpos_x] != SkinInfo[VecheaClasa][cpos_x]) {
		//InterpolateCameraPos(playerid, SkinInfo[VecheaClasa][cpos_x],SkinInfo[VecheaClasa][cpos_y],SkinInfo[VecheaClasa][cpos_z], SkinInfo[classid][cpos_x],SkinInfo[classid][cpos_y],SkinInfo[classid][cpos_z], 1500, CAMERA_MOVE);
		//InterpolateCameraLookAt(playerid, SkinInfo[VecheaClasa][ppos_x],SkinInfo[VecheaClasa][ppos_y],SkinInfo[VecheaClasa][ppos_z]+SkinInfo[classid][cpos_zDif],SkinInfo[classid][ppos_x],SkinInfo[classid][ppos_y],SkinInfo[classid][ppos_z]+SkinInfo[classid][cpos_zDif], 1500, CAMERA_MOVE);
		SetPlayerCameraPos(playerid,SkinInfo[classid][cpos_x],SkinInfo[classid][cpos_y],SkinInfo[classid][cpos_z]);
		SetPlayerCameraLookAt(playerid,SkinInfo[classid][ppos_x],SkinInfo[classid][ppos_y],SkinInfo[classid][ppos_z]);//+SkinInfo[classid][cpos_zDif]);
	}
	ApplyAnimation(playerid,"DANCING","DNCE_M_B",4.0,1,0,0,0,-1); 
	OldClassSelect[playerid] = classid;
	return true;
}

public OnPlayerRequestClass(playerid, classid) {
	if(gPlayerLogged{playerid}) {
		PlayerPlaySound(playerid, 1097,0.0,0.0,0.0);
		wSkinClass[SkinInfo[classid][skinid]] = classid;
		SetupPlayerForClassSelection(playerid,classid);
		new string[MAXO_TEXT], textsfarsitM[30], textinceput[30];
		new textsfarsitL[30] =" ~y~< ~n~Leaders only!";
		format(textsfarsitM, sizeof(textsfarsitM), " ~y~< ~n~ Member Rank %d",SkinInfo[classid][rankid]);
		PlayerInfo[playerid][pSkin] = SkinInfo[classid][skinid];
		switch(SkinInfo[classid][faction]) {
			case FACT_LSPD:  		 format(textinceput, sizeof(textinceput), "~y~> ~p~Police");
			case FACT_FBI: 		 format(textinceput, sizeof(textinceput), "~y~> ~p~FBI/ATF");
			case FACT_MEDIC:     format(textinceput, sizeof(textinceput), "~y~> ~p~Fire/Ambulance");
			case FACT_LCN:       format(textinceput, sizeof(textinceput), "~y~> ~p~La Cosa Nostra");
			case FACT_YKZ:    format(textinceput, sizeof(textinceput), "~y~> ~p~Yakuza");
			case FACT_HITMAN:    format(textinceput, sizeof(textinceput), "~y~> ~p~Hitman");
			case FACT_CNN:      format(textinceput, sizeof(textinceput), "~y~> ~p~News Reporters");
			case FACT_TAXI:      format(textinceput, sizeof(textinceput), "~y~> ~p~Taxi Cab Company");
			case FACT_CRIPS:     format(textinceput, sizeof(textinceput), "~y~> ~p~Crips Gang");
			case FACT_BLOODS:    format(textinceput, sizeof(textinceput), "~y~> ~p~Bloods Gang");
			case FACT_FMA:    format(textinceput, sizeof(textinceput), "~y~> ~p~FMA");
			default: format(textinceput, sizeof(textinceput), "~y~> ~g~Civilian");
		}
		if (SkinInfo[classid][rankid] == 6) 
			format(string, sizeof(string), "%s%s",textinceput,textsfarsitL);
		else if (SkinInfo[classid][rankid] == 0) 
			format(string, sizeof(string), "%s ~y~<",textinceput);
		else 
			format(string, sizeof(string), "%s%s",textinceput,textsfarsitM);
		GameTextForPlayer(playerid,string,3500,6);
	} 
	else
		GameTextForPlayer(playerid,"~r~eGaming RPG",3500,4);
	return true;
}

public OnPlayerRequestSpawn(playerid)
{
	if(IsPlayerNPC(playerid)) return 1;
	if(gPlayerLogged{playerid}) {
		new textul[MAXO_TEXT], factiune;
		new ClasaSkin = wSkinClass[GetPlayerSkin(playerid)];
		PlayerInfo[playerid][pSkin] = SkinInfo[ClasaSkin][skinid];
		factiune = PlayerInfo[playerid][pFactiune];
		if(SkinInfo[ClasaSkin][faction] == factiune && SkinInfo[ClasaSkin][rankid] == PlayerInfo[playerid][pRank]) {
			new string[MAXO_TEXT];
			SetPlayerSpawnInfo(playerid);
			format(string, sizeof(string), "UPDATE players SET Skin = %d WHERE ID = %d", PlayerInfo[playerid][pSkin], PlayerInfo[playerid][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			if(PlayerInfo[playerid][pFactiune] == FACT_CIVIL) {
				PlayerInfo[playerid][pRank] = 0;
				format(string, sizeof(string), "UPDATE players SET Rank = 0 WHERE ID = %d", PlayerInfo[playerid][pSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			}
			return true;
		}
		if(PlayerInfo[playerid][pRank] < 6) format(textul, sizeof(textul), "~r~Choose other skin~n~You are ~w~%s~r~ rank ~w~%d", FactionInfo[factiune][fName],PlayerInfo[playerid][pRank]);
		else format(textul, sizeof(textul), "~r~Choose other skin~n~You are ~w~%s~r~ faction leader",FactionInfo[factiune][fName]);
		GameTextForPlayer(playerid, textul, 500, 1);
	}
	return false;
}

// EOF
