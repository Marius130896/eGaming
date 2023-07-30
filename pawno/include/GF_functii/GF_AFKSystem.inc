/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_AFKSystem_included
	#endinput
#else
	#define GF_AFKSystem_included
#endif

enum afInfo {
	aAFKDetect,
	bool:aAFKPlayer,
	aAFKTime
};
new AFKInfo[MAX_PLAYERS][afInfo];

forward TimeSincePaused(playerid);

public OnPlayerUpdate(playerid) {
	gGlobalTick = GetTickCount();

	TryDamageForVehicle(playerid);
	AFKInfo[playerid][aAFKTime] = gettime();
	new Float:Health;
	new HealthNum[15];
	GetPlayerHealth(playerid, Health);
	format(HealthNum, sizeof(HealthNum), "%.0f", Health);
	TextDrawSetString(DigiHP[playerid], HealthNum);
	TextDrawShowForPlayer(playerid, DigiHP[playerid]);

    new Float:Armour;
	GetPlayerArmour(playerid, Armour);
	if(Armour >= 1) {
		new ArmourNum[15];
        format(ArmourNum, 15, "%.0f", Armour);
		TextDrawSetString(DigiAP[playerid], ArmourNum);
		TextDrawShowForPlayer(playerid, DigiAP[playerid]);
  	}
	else 
	{
		TextDrawHideForPlayer(playerid, DigiAP[playerid]);
	}
	return true;
}

stock IsPlayerPaused(playerid) {
	return gettime() - AFKInfo[playerid][aAFKTime] > 3;
}

stock TimeSincePaused(playerid) {
	if(AFKInfo[playerid][aAFKPlayer] == true) return gettime()-AFKInfo[playerid][aAFKTime];
	else return AFKInfo[playerid][aAFKTime];
}

// End Of File ...
