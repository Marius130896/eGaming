/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_FlyPlayerSystem_included
	#endinput
#else
	#define GF_FlyPlayerSystem_included
#endif

stock StartFly(playerid)
{
	if(OnFly{playerid})
        return SendClientMessage(playerid, COLOR_GRAD1, "You already have flymode activated."); // nu cred ca este o posibilitate sa se intampla asta .. dar pt safe
    OnFly{playerid} = true;
	new Float:x,Float:y,Float:z, string[MAXO_TEXT1];
	GetPlayerPos(playerid,x,y,z);
	SetPlayerPos(playerid,x,y,z+5.0);
	ApplyAnimation(playerid,"PARACHUTE","PARA_steerR",6.1,1,1,1,1,0,1);
	Fly(playerid); // se apeleaza
	ShowPlayerInformation(playerid, "FlyMode", "~r~Functions~n~~n~~w~LEFT CLICK - ~b~Increase height~n~~w~RIGHT CLICK - ~b~Reduce height~n~\
	~g~~w~SPRINT KEY - ~b~Increase speed~n~~w~~k~~SNEAK_ABOUT~ - ~b~Reduce Speed");
	format(string, MAXO_TEXT1, "Admin %s is now on flymode.", PlayerName(playerid));
	ABroadCast(COLOR_LIGHTRED, string, 1);
	SetPlayerHealth(playerid, 100.0);
	clear.string(string);
	return true;
}

stock StopFly(playerid) {
	if(!OnFly{playerid})
        return false;
	new Float:x,Float:y,Float:z, string[MAXO_TEXT1];
	GetPlayerPos(playerid,x,y,z);
	SetPlayerPos(playerid,x,y,z);
	OnFly{playerid} = false;
	SetPlayerHealth(playerid, 100.0);
	ShowPlayerInformation(playerid, "FlyMode", "~b~FlyMode ~r~deactivated~w~");
	format(string, MAXO_TEXT1, "Admin %s is now off flymode.", PlayerName(playerid));
	ABroadCast(COLOR_LIGHTRED, string, 1);
	WasFlew[playerid] = gLocalTimeStamp+5;
	clear.string(string);
	return true;
}

function Fly(playerid) {
	if(!IsPlayerConnected(playerid))
		return 1;
	new k, ud,lr;
	GetPlayerKeys(playerid,k,ud,lr);
	new Float:v_x,Float:v_y,Float:v_z,
		Float:x,Float:y,Float:z;
	if(ud < 0)	// forward
	{
		GetPlayerCameraFrontVector(playerid,x,y,z);
		v_x = x+0.1;
		v_y = y+0.1;
	}
	if(k & 128)	// down
		v_z = -0.2;
	else if(k & KEY_FIRE)	// up
		v_z = 0.2;
	if(k & KEY_WALK)	// slow
	{
		v_x /=5.0;
		v_y /=5.0;
		v_z /=5.0;
	}
	if(k & KEY_SPRINT)	// fast
	{
		v_x *=4.0;
		v_y *=4.0;
		v_z *=4.0;
	}
	if(v_z == 0.0)
		v_z = 0.025;
	SetPlayerVelocity(playerid,v_x,v_y,v_z);
	if(v_x == 0 && v_y == 0)
	{
		if(GetPlayerAnimationIndex(playerid) == 959)
			ApplyAnimation(playerid,"PARACHUTE","PARA_steerR",6.1,1,1,1,1,0,1);
	}
	else
	{
		GetPlayerCameraFrontVector(playerid,v_x,v_y,v_z);
		GetPlayerCameraPos(playerid,x,y,z);
		SetPlayerLookAt(playerid,v_x*500.0+x,v_y*500.0+y);
		if(GetPlayerAnimationIndex(playerid) != 959)
			ApplyAnimation(playerid,"PARACHUTE","FALL_SkyDive_Accel",6.1,1,1,1,1,0,1);
	}
	if(OnFly{playerid})
		SetTimerEx("Fly",100,false,"i",playerid);
	return 1;
}

function SetPlayerLookAt(playerid,Float:x,Float:y) {
	new Float:Px, Float:Py, Float: Pa;
	GetPlayerPos(playerid, Px, Py, Pa);
	Pa = floatabs(atan((y-Py)/(x-Px)));
	if (x <= Px && y >= Py) 		Pa = floatsub(180.0, Pa);
	else if (x < Px && y < Py) 		Pa = floatadd(Pa, 180.0);
	else if (x >= Px && y <= Py)	Pa = floatsub(360.0, Pa);
	Pa = floatsub(Pa, 90.0);
	if (Pa >= 360.0)
		Pa = floatsub(Pa, 360.0);
	SetPlayerFacingAngle(playerid, Pa);
	return;
}

// End Of File ...
