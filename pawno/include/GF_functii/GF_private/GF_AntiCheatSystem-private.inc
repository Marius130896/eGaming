/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_AntiCheatSystem_included
	#endinput
#else
	#define GF_AntiCheatSystem_included
#endif

function OnPlayerFloodControl(playerid, iCount, iTimeSpan) {
    if(IsPlayerNPC(playerid)) return true;
    if(iCount > 10 && iTimeSpan < 10000) {
        KickDeelay(playerid);
    }
    return true;
}

function tazerexit(playerid) {
	if(!IsPlayerInAnyVehicle(playerid)) {
		IsPlayerCuffed{playerid} = false;
		PlayerInfo[playerid][pTazed] = 0;
		TogglePlayerControllable(playerid, true);
		SetPlayerDrunkLevel (playerid, 4000);
		ClearAnimations(playerid);
		GameTextForPlayer(playerid, "~y~Now you feel better!", 3500, 1);
	}
	return true;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart) {
	new string[MAXO_TEXT];
	if(damagedid != INVALID_PLAYER_ID) {
		switch(weaponid) {
			case WEAPON_NITESTICK: { // verificam daca arma politistului, este bastonul
				if(PlayerInfo[playerid][pFactiune] == FACT_LSPD) { // verificam daca utilizatorul bastonului este memberu PD
					if(random(100) < 61) { // daca variabila a luat valoare mai mica de 61(adica de la 0 la 60) continuam
						if(!IsPlayerCop(damagedid)) {
							if(IsPlayerCuffed{damagedid})
								return SendClientMessage(playerid, COLOR_GRAD1, "Player already Cuffed!");
							if(IsPlayerInAnyVehicle(damagedid))
								return SendClientMessage(playerid, COLOR_GRAD1, "Suspect is in a Car, get him out first!");
							// trimitem mesaje de informare pentru Cop/ criminal si pentru cei din jurul lor
							// pe o distanta de 30.0 unitati
							format(string, MAXO_TEXT, "* You were Tazed by %s for 20 seconds.", PlayerName(playerid));
							SendClientMessage(damagedid, COLOR_LIGHTBLUE, string);
							format(string, MAXO_TEXT, "* You Tazed %s for 20 seconds.", PlayerName(damagedid));
							SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
							format(string, MAXO_TEXT, "* %s hit with his Tazer at %s, and tazed him.", PlayerName(playerid), PlayerName(damagedid));
							SendPlayerMessage(30.0, damagedid, string, COLOR_PURPLE);
							ClearAnimations(damagedid); // vom curata animatiile criminalului
							ApplyAnimation(damagedid, "CRACK", "crckdeth2", 4.1, 1, 1, 1, 1, 1); // aplicam animatia /crack pentru criminal
							SetTimerEx("tazerexit", 15000, false, "i", damagedid); //punem un timer pentru a ii da unfreeze(15 secunde)
							IsPlayerCuffed{damagedid} = true; //  validam ca este incatusat
							PlayerInfo[damagedid][pTazed] = 1; // validam ca este pe true tazed
							SetPlayerDrunkLevel(damagedid, 49900); // i se invarte ecranul ca si cum ar fi beat
							TogglePlayerControllable(damagedid, false); // blocam criminalul ca sa nu se mai miste
							ApplyAnimation(damagedid, "CRACK", "crckdeth2", 4.1, 1, 1, 1, 1, 1); // aplicam animatia /crack pentru criminal
							clear.string(string);
						}
					}
				}
			}
			case WEAPON_SNIPER: { // Sniper Hitman
				if(PlayerInfo[playerid][pFactiune] == FACT_HITMAN) { // Daca face parte din factiunea hitman
					if(bodypart == 9) { // Daca se da cu sniperul in cap
						if(GoChase[playerid] == damagedid && PlayerInfo[damagedid][pHeadValue] > 0) { // Daca hitmanul are contract pe jucatorul respectiv
							OnPlayerDeath(damagedid, playerid, weaponid);
							SetPlayerHealth(damagedid, 0);
						}
					}
				}
			}
		}
	}
	return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid) {
    return 1;
}

stock WarningPlayers(playerid, reason[]) {
	new string[MAXO_TEXT];
	format(string, MAXO_TEXT, "AdmCmd: %s was been kicked by Anti-Cheat, Reason: %s.", PlayerName(playerid), reason);
	OOCNews(COLOR_LIGHTRED, string);
	KickDeelay(playerid);
	clear.string(string);
	return true;
}

stock IsAdminsOnline() {
	new count = 0;
	foreach(Player, i) {
		if(PlayerInfo[i][pAdmin] > 0)
			count ++;
	}
	return count;
}

stock Carspeed(playerid, mode = 1) {
    new Float:Velocity [3];
    GetVehicleVelocity ( GetPlayerVehicleID ( playerid ) , Velocity [ 0 ] , Velocity [ 1 ] , Velocity [ 2 ] ) ;
    return IsPlayerInAnyVehicle ( playerid ) ? floatround ( ( ( floatsqroot ( ( ( Velocity [ 0 ] * Velocity [ 0 ] ) + ( Velocity [ 1 ] * Velocity [ 1 ] ) + ( Velocity [ 2 ] * Velocity [ 2 ] ) ) ) * ( !mode ? 105.0 : 170.0 ) ) ) * 1 ) : 0;
}

function VerificaCheatPlayer() {
	new anim, Float:animpos[3], string[MAXO_TEXT];
	new Float: ArmourP, Float: HP;
	foreach(Player, i) {
		if(!OnFly{i}) {
			anim = GetPlayerAnimationIndex(i);
			GetPlayerVelocity(i, animpos[0], animpos[1], animpos[2]);
			if(animpos[0] <= -0.800000 || animpos[1] <= -0.800000 || animpos[2] <= -0.800000 && anim == 1008) {
				new surfx = GetPlayerSurfingVehicleID(i);
				if(surfx == INVALID_VEHICLE_ID) {
					if(IsAdminsOnline() > 0) {
						format(string, MAXO_TEXT, "[CHEAT]: %s (%d) is suspected that can use FlyHack, /spec)tate him.", PlayerName(i), i);
						ABroadCast(COLOR_YELLOW, string, 1);
						AntiCheat[i][eGWarningCheat] += 2;
						if(AntiCheat[i][eGWarningCheat] >= 6) WarningPlayers(i, "Hacks » Fly Hack");
					} else WarningPlayers(i, "Hacks » Fly Hack");
				}
			}
		}
		if(GetPlayerSpecialAction(i) == SPECIAL_ACTION_USEJETPACK) {
			if(IsAdminsOnline() > 0) {
				format(string, MAXO_TEXT, "[CHEAT]: %s (%d) is suspected that can use JetPack, /spec)tate him.", PlayerName(i), i);
				ABroadCast(COLOR_YELLOW, string, 1);
				AntiCheat[i][eGWarningCheat] += 2;
				if(AntiCheat[i][eGWarningCheat] >= 6) WarningPlayers(i, "Hacks » Jetpack");
			} else WarningPlayers(i, "Hacks » Jetpack");
		}
		if(GetPlayerState(i) == PLAYER_STATE_DRIVER && !IsVehiclePlane(GetPlayerVehicleID(i))) {
			new speed = Carspeed(i);
			if(speed > 230 && !IsPlayerInArea(i, -3000, -2274.5, -1776, -859.5)) {
				if(GetVehicleModel(i) == 522 && speed < 250) return 1;
				if(IsAdminsOnline() > 0) {
					format(string, MAXO_TEXT, "[CHEAT]: %s (%d) drive with the speed of %.0d km/h a %s.", PlayerName(i), i, speed, vehName[GetVehicleModel(GetPlayerVehicleID(i))-400]);
					ABroadCast(COLOR_YELLOW, string, 1);
				} else WarningPlayers(i, "Hacks » Speed Hack");
			}
		}
		GetPlayerArmour(i, ArmourP);
		if(ArmourP > 100 && GetPVarInt(i, "Armour") == 0) {
			WarningPlayers(i, "Hacks » Armour Hack");
		}
		GetPlayerHealth(i, HP);
		if(HP > 150 && GetPVarInt(i, "Health") > 150 && GetPlayerDrunkLevel(i) != 2500) {
			WarningPlayers(i, "Hacks » Health Hack");
		}
		if(PlayerInfo[i][pCash] - CurrentMoney[i] >= 50000) {
			if(ConsumingMoney[i])
				CurrentMoney[i] = PlayerInfo[i][pCash], ConsumingMoney[i] = 0;
			else
			{
				format(string, MAXO_TEXT, "[CHEAT]: [%d]%s just spawned above $50.000 in one second (moneycheat), use /check on him.", i, PlayerName(i));
				ABroadCast(COLOR_YELLOW, string, 1);
				PlayerInfo[i][pCash] = CurrentMoney[i];
				SetPlayerMoney(i, PlayerInfo[i][pCash]);
			}
		} else CurrentMoney[i] = PlayerInfo[i][pCash];
		if(AntiCheat[i][eGWarningCheat] > 0) AntiCheat[i][eGWarningCheat] --;
	}
	clear.string(string);
	return true;
}

stock GetStampIP(playerid){
	new S_IP[16];
	Join_Stamp = GetTickCount();
	GetPlayerIp(playerid, S_IP, 16);
	format(ban_s, 16, "%s", S_IP);
}


stock SafeGivePlayerMoney(playerid, money) {
	new string[MAXO_TEXT];
	if(playerid != INVALID_PLAYER_ID) {
		PlayerInfo[playerid][pCash] += money;
		format(string, MAXO_TEXT, "UPDATE players SET Cash = %d WHERE ID = %d", PlayerInfo[playerid][pCash], PlayerInfo[playerid][pSQLID]);
		mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		clear.string(string);
	}
	return true;
}

// End Of File ...
