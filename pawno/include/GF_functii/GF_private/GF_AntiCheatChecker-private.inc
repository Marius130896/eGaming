#if defined GF_AntiCheatChecker_included
	#endinput
#else
	#define GF_AntiCheatChecker_included
#endif

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

// End Of File ...
