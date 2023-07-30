/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_CommandsPriv_included
	#endinput
#else
	#define GF_CommandsPriv_included
#endif

#tryinclude <GF_functii/GF_private/GF_AnimationsComm-private>

public OnPlayerCommandPerformed(playerid, cmdtext[], success) {
	if(!success)
		return SendClientMessage(playerid, -1, "SERVER: Unknown command.");
	return 1;
}

COMMAND:spectateoff(playerid, params[]) {
	if (PlayerInfo[playerid][pAdmin]) {
		if(Spectated[playerid][Command])
			SpecStopSpec(playerid),
			TextDrawHideForPlayer(playerid, spectatortxt[playerid]);
		else
			SendClientMessage(playerid, COLOR_GRAD1, "You are not spectating anyone !");
	} else NotAuthorized();
	return true;
}

COMMAND:specoff(playerid, params[]) {
	return cmd_spectateoff(playerid, params);
}

COMMAND:specveh(playerid, params[]) {
	new carid;
	if(PlayerInfo[playerid][pAdmin]) {
		if(!sscanf(params, "d", carid)) {
			if(GetVehicleModel(carid)) {
				Spectated[playerid][Status] = true;
				Spectated[playerid][Command] = true;
				Spectated[playerid][vehicleIDj] = carid;
				Spectated[playerid][Type] = ADMIN_SPEC_TYPE_VEHICLE;
				if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
					StorePlayerData(playerid);
				TogglePlayerSpectating(playerid, true);
				PlayerSpectateVehicle(playerid, carid);
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid vehicle id/dead vehicle.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/specveh [carid]");
	} else NotAuthorized();
	return true;
}

COMMAND:goto(playerid, params[]) {
	new targetid, Float:plpos[3], destint, destvw, string[MAXO_TEXT];
	if(PlayerInfo[playerid][pAdmin] || PlayerInfo[playerid][pHelper]) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID && !IsPlayerNPC(targetid)) {
				if(targetid != playerid) {
					if(!Spectated[playerid][Status]) {
						if(PlayerInfo[playerid][pInHouseID] || PlayerInfo[playerid][pInBizzID]) SendClientMessage(playerid, COLOR_GRAD1, "NOTICE: Last position wasn't saved because you were in a house/biz.");
						else {
							if(!GoBackInfo[playerid][gbUsed])
								StorePlayerData(playerid);
						}
						GetPlayerPos(targetid, plpos[0], plpos[1], plpos[2]);
						destint = PlayerInfo[targetid][pInterior];
						destvw = PlayerInfo[targetid][pVirtualWorld];
						if(plpos[2] > 530.0 && destint == 0) SafeSetPlayerInterior(playerid, 1);
						if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
							if(!destint && !destvw) {
								SetVehiclePos(GetPlayerVehicleID(playerid), plpos[0], plpos[1]+4, plpos[2]);
								LinkVehicleToInterior(GetPlayerVehicleID(playerid), destint);
								SetVehicleVirtualWorld(GetPlayerVehicleID(playerid), destvw);
								PutPlayerInVehicle(playerid, GetPlayerVehicleID(playerid), 0);
							} else SendClientMessage(playerid, COLOR_GRAD1, "Get off from vehicle, that player is inside an interior!");
						}
						else
						{
							SafeSetPlayerInterior(playerid, destint);
							SafeSetPlayerVirtualWorld(playerid, destvw);
							SafeSetPlayerPos(playerid, plpos[0], plpos[1]+1, plpos[2]);
						}
						PlayerInfo[playerid][pVirtualWorld] = PlayerInfo[targetid][pVirtualWorld];
						if(PlayerInfo[playerid][pAdmin]) format(string, MAXO_TEXT, "* "GRI3"Admin %s teleported to %s.", PlayerName(playerid), PlayerName(targetid)), ABroadCast(COLOR_LIGHTBLUE, string, 1);
						else if(PlayerInfo[playerid][pHelper]) format(string, MAXO_TEXT, "* "GRI3"Helper %s teleported to %s.", PlayerName(playerid), PlayerName(targetid)), HBroadCast(COLOR_LIGHTBLUE, string, 1);
						format(string, MAXO_TEXT, "* "GRI3"You have been teleported to %s.", PlayerName(targetid));
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "You are spectating. Use: /specoff first!");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can't to teleport at yourself.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/goto [playerid/PartOfName]");
	} else NotAuthorized();
	return true;
}

COMMAND:goback(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] || PlayerInfo[playerid][pHelper]) {
		if(GoBackInfo[playerid][gbUsed]) {
			SetPlayerBack(playerid);
			SendClientMessage(playerid, COLOR_LIGHTBLUE, "* "GRI3"You have been teleported to previous position.");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You haven't teleported anywhere yet.");
	} else NotAuthorized();
	return true;
}

stock IsPlayerInInside(playerid) {
	if(GetPlayerInterior(playerid) > 0) return true;
	if(GetPlayerVirtualWorld(playerid) > 0) return true;
	if(PlayerInfo[playerid][pInBizzID]) return true;
	if(PlayerInfo[playerid][pInHouseID]) return true;
	if(PlayerInfo[playerid][pInterior]) return true;
	if(PlayerInfo[playerid][pVirtualWorld]) return true;
	return false;
}

COMMAND:spectate(playerid, params[]) {
	new string[MAXO_TEXT], targetid, vID;
	if(PlayerInfo[playerid][pAdmin]) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(!IsPlayerInInside(playerid)) {
						if(Spectated[playerid][Command]) {
							format(string, MAXO_TEXT, "* "GRI3"Spectating alreay in progress. Changing target: %s", PlayerName(playerid)),
							SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						}
						Spectated[playerid][Status] = true;
						Spectated[playerid][Command] = true;
						if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
							StorePlayerData(playerid);
						SafeSetPlayerVirtualWorld(playerid, PlayerInfo[targetid][pVirtualWorld]);
						SafeSetPlayerInterior(playerid, PlayerInfo[targetid][pInterior]);
						TogglePlayerSpectating(playerid, true);
						Spectated[playerid][IDj] = targetid;
						vID = GetPlayerVehicleID(targetid);
						if(vID)
							PlayerSpectateVehicle(playerid, vID),
							Spectated[playerid][Type] = ADMIN_SPEC_TYPE_VEHICLE;
						else
							PlayerSpectatePlayer(playerid, targetid),
							Spectated[playerid][Type] = ADMIN_SPEC_TYPE_PLAYER;
						new
						cash = PlayerInfo[targetid][pCash],
						Float: health;
						GetPlayerHealth(targetid, health);
						format(string, MAXO_TEXT, "Recon: (%d)%s $%s Health: %.0f", targetid, PlayerName(targetid), FormatNumber(cash, 0, '.'), health);
						SendClientMessage(playerid, COLOR_GREEN, string);
						format(string, MAXO_TEXT, "~y~(%d) ~w~%s 		~g~$~w~%s 		~r~Health: ~w~%.0f%", targetid, PlayerName(targetid), FormatNumber(cash, 0, '.'), health);
						TextDrawSetString(spectatortxt[playerid], string);
						TextDrawShowForPlayer(playerid, spectatortxt[playerid]);
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "You are in inside, the command can't be used.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can't spectate yourself.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/spec(tate) [playerid/PartOfName]");
	} else NotAuthorized();
	return true;
}

COMMAND:spec(playerid, params[]) {
	return cmd_spectate(playerid, params);
}

stock SpecStopSpec(playerid) {
	SetPlayerBack(playerid);
	Spectated[playerid][Status] = false;
	Spectated[playerid][Command] = false;
	Spectated[playerid][IDj] = INVALID_PLAYER_ID;
	Spectated[playerid][Type] = ADMIN_SPEC_TYPE_NONE;
	TogglePlayerSpectating(playerid, false);
	TextDrawHideForPlayer(playerid, spectatortxt[playerid]);
	SendClientMessage(playerid, COLOR_WHITE, "You are no longer spectating.");
	return true;
}

COMMAND:spawntvehicle(playerid, params[]) {
	new model, Float:plPos[4], vID;
	if(IsPlayerFounder(playerid)) {
		if(!sscanf(params, "d", model)) {
			if(ISBetween(model, 400, 612)) {
				if(!IsPlayerInAnyVehicle(playerid)) {
					if(!IsPlayerInInside(playerid)) {
						TotalVehicles ++;
						GetPlayerPos(playerid, plPos[0], plPos[1], plPos[2]);
						GetPlayerFacingAngle(playerid, plPos[3]);

						vID = CreateVehicle(model, plPos[0], plPos[1], plPos[2], plPos[3], -1, -1, DEFAULT_RESPAWN_TIME);

						CarInfo[vID][cSQLID] = TotalVehicles;
						CarInfo[vID][cModel] = model;
						CarInfo[vID][cLocation][0] = plPos[0];
						CarInfo[vID][cLocation][1] = plPos[1];
						CarInfo[vID][cLocation][2] = plPos[2];
						CarInfo[vID][cAngle] = plPos[3];
						CarInfo[vID][cColor][0] = -1;
						CarInfo[vID][cColor][1] = -1;
						CarInfo[vID][cRespawnTime] = DEFAULT_RESPAWN_TIME;
						CarInfo[vID][cHealth] = 1000.0;
						CarInfo[vID][cType] = VEHICLE_TYPE_GENERIC;
						CarInfo[vID][cFactionID] = FACT_CIVIL;
						CarInfo[vID][cRank]= 0;
						CarInfo[vID][cJob] = JOB_NONE;
						CarInfo[vID][cBiz] = BIZ_TYPE_ANY;
						CarInfo[vID][cEngine] = false;
						Gas[vID] = GasMax;
						StopCarRadio(vID);
						SetVehicleNumberPlate(vID, "eG GENERIC VEH");
						new engine, lights, alarm, doors, bonnet, boot, objective;
						GetVehicleParamsEx(vID, engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(vID, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
						PutPlayerInVehicle(playerid, vID, 0);
					} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command from an interior.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You must be pedestrian for this action.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid model id.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/spawntvehicle [model]");
	} else NotAuthorized();
	return true;
}

COMMAND:weather(playerid, params[]) {
	new
		string[MAXO_TEXT], weather;
	if(PlayerInfo[playerid][pAdmin] > 1) {
		if(!sscanf(params, "d", weather)) {
			if(ISBetween(weather, 0, 20)) {
				foreach(Player, i)
					SetPlayerWeather(i, weather);
				format(string, MAXO_TEXT, "AdmCmd: The weather was been changed by Admin %s.", PlayerName(playerid));
				OOCNews(COLOR_LIGHTRED, string);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid weather id.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/weahter [weatherid(0-20)]");
	} else NotAuthorized();
	return true;
}

COMMAND:levelupall(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pAdmin] > 2) {
		foreach(Player, i) {
			PlayerInfo[i][pLevel] += 1;
			format(string, MAXO_TEXT, "UPDATE players SET Level = %d WHERE ID = %d", PlayerInfo[i][pLevel], PlayerInfo[i][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		}
		format(string, MAXO_TEXT, "AdmCmd: %s gave 1x Level UP to all players online.", PlayerName(playerid));
		OOCNews(COLOR_LIGHTRED, string);
		clear.string(string);
	} else NotAuthorized();
	return true;
}

COMMAND:rpupall(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pAdmin] > 2) {
		foreach(Player, i) {
			PlayerInfo[i][pExp] += 1;
			format(string, MAXO_TEXT, "UPDATE players SET Respect = %d WHERE ID = %d", PlayerInfo[i][pExp], PlayerInfo[i][pSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
		}
		format(string, MAXO_TEXT, "AdmCmd: %s gave 1x RespectPoint UP to all players online.", PlayerName(playerid));
		OOCNews(COLOR_LIGHTRED, string);
		clear.string(string);
	} else NotAuthorized();
	return true;
}

COMMAND:healall(playerid, params[]) {
	new
		string[MAXO_TEXT], Float:plH;
	if(PlayerInfo[playerid][pAdmin] > 2) {
		foreach(Player, i) {
			GetPlayerHealth(i, plH);
			if(plH < 100.0)
				SetPlayerHealth(i, 100.0);
		}
		format(string, MAXO_TEXT, "AdmCmd: %s gave Health maximum to all players online.", PlayerName(playerid));
		OOCNews(COLOR_LIGHTRED, string);
		clear.string(string);
	} else NotAuthorized();
	return true;
}

COMMAND:armourall(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pAdmin] > 2) {
		foreach(Player, i) {
			SetPlayerArmour(i, 100.0);
		}
		format(string, MAXO_TEXT, "AdmCmd: %s gave Armour maximum to all players online.", PlayerName(playerid));
		OOCNews(COLOR_LIGHTRED, string);
		clear.string(string);
	} else NotAuthorized();
	return true;
}

COMMAND:skydive(playerid, params[]) {
	new
		Float:pPos[3];
	if(PlayerInfo[playerid][pAdmin] > 2) {
		GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
		GivePlayerWeapon(playerid, 46, 0);
		SafeSetPlayerPos(playerid, pPos[0], pPos[2], pPos[2]+1500);
		GameTextForPlayer(playerid, "~g~Open the parachute!", 2500, 4);
	} else NotAuthorized();
	return true;
}

COMMAND:gotocar(playerid, params[]) {
	new
		carid, Float:vPos[3];
	if(PlayerInfo[playerid][pAdmin] > 2) {
		if(!sscanf(params, "d", carid)) {
			if(carid != INVALID_VEHICLE_ID) {
				GetVehiclePos(carid, vPos[0], vPos[1], vPos[2]);
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) SetVehiclePos(GetPlayerVehicleID(playerid), vPos[0], vPos[1], vPos[2]);
				else SafeSetPlayerPos(playerid, vPos[0], vPos[1], vPos[2]);
				GameTextForPlayer(playerid, "~g~You have been teleported!", 2500, 1);
				SafeSetPlayerInterior(playerid, 0);
				SafeSetPlayerVirtualWorld(playerid, 0);
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid vehicle.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/gotocar [carid]");
	} else NotAuthorized();
	return true;
}

COMMAND:fuck(playerid, params[]) {
	new
		targetid, Float:slx, Float:sly, Float:slz;
	if(PlayerInfo[playerid][pAdmin] > 2) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				GetPlayerPos(targetid, slx, sly, slz);
				CreateExplosion(slx, sly, slz, 2, 140.0);
				PlayerPlaySound(targetid, 1130, slx, sly, slz+5);
				PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid player.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/fuck [playerid/PartOfName]");
	} else NotAuthorized();
	return true;
}

COMMAND:fixveh(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] > 2) {
		if(IsPlayerInAnyVehicle(playerid)) {
			SetVehicleHealth(GetPlayerVehicleID(playerid), 1000.0);
			RepairVehicle(GetPlayerVehicleID(playerid));
			SendClientMessage(playerid, COLOR_GREY, "Vehicle Fixed !");
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in an vehicle to use this command.");
	} else NotAuthorized();
	return true;
}

COMMAND:givemoney(playerid, params[]) {
	new string[MAXO_TEXT], targetid, amount;
	if(PlayerInfo[playerid][pAdmin] > 4) {
		if(!sscanf(params, "s[24]d", PartialName[playerid][nume_introdus], amount)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(ISBetween(amount, 1, 1000000000)) {
					SafeGivePlayerMoney(targetid, amount);
					ConsumingMoney[targetid] = 1;
					format(string, MAXO_TEXT, "* You have received $%s from Admin %s.", FormatNumber(amount, 0, '.'), PlayerName(playerid));
					SendClientMessage(targetid, COLOR_LIGHTRED, string);
					format(string, MAXO_TEXT, "* You gave it to %s the amount of $%s (cash), using the command /givemoney.", PlayerName(targetid), FormatNumber(amount, 0, '.'));
					SendClientMessage(playerid, COLOR_LIGHTRED, string);
					PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "The amount must be between $1 - $1.000.000.000");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/givemoney [playerid/PartOfName] [amount]");
	} else NotAuthorized();
	return true;
}

COMMAND:givemoneyacc(playerid, params[]) {
	new string[MAXO_TEXT], targetid, amount;
	if(PlayerInfo[playerid][pAdmin] > 4) {
		if(!sscanf(params, "s[24]d", PartialName[playerid][nume_introdus], amount)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(ISBetween(amount, 1, 1000000000)) {
					PlayerInfo[targetid][pAccount] += amount;
					format(string, MAXO_TEXT, "UPDATE players SET Account = %d WHERE ID = %d", PlayerInfo[targetid][pAccount], PlayerInfo[targetid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					format(string, MAXO_TEXT, "* You have received $%s from Admin %s.", FormatNumber(amount, 0, '.'), PlayerName(playerid));
					SendClientMessage(playerid, COLOR_LIGHTRED, string);
					format(string, MAXO_TEXT, "* You gave it to %s the amount of $%s (account), using the command /givemoneyacc.", PlayerName(targetid), FormatNumber(amount, 0, '.'));
					SendClientMessage(playerid, COLOR_LIGHTRED, string);
					PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "The amount must be between $1 - $1.000.000.000");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid player.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/givemoneyacc [playerid/PartOfName] [amount]");
	} else NotAuthorized();
	return true;
}

COMMAND:hsay(playerid, params[]) {
	new string[MAXO_TEXT];
	if(PlayerInfo[playerid][pHelper]) {
		if(!sscanf(params, "s[128]", params)) {
			if(strlen(params) < 128) {
				if(!PlayerInfo[playerid][pMute]) {
					format(string, MAXO_TEXT, "* Helper %s: %s *", PlayerName(playerid), params);
					OOCNews(COLOR_YELLOW2, string);
					clear.string(string);
				} else IsPlayerSilent();
			} else SendClientMessage(playerid, COLOR_YELLOW, "[Anti-Spam] {FFFFFF}Line too long!");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/hsay [text]");
	} else NotAuthorized();
	return true;
}

COMMAND:hc(playerid, params[]) {
	new string[MAXO_TEXT];
	if(PlayerInfo[playerid][pHelper]) {
		if(!sscanf(params, "s[128]", params)) {
			if(strlen(params) < 128) {
				if(!PlayerInfo[playerid][pMute]) {
					if(PlayerInfo[playerid][pAdmin]) format(string, MAXO_TEXT, "» %s Helper Level %d: %s «", PlayerName(playerid), PlayerInfo[playerid][pHelper], params);
					HBroadCast(COLOR_GREEN, string, 1);
					clear.string(string);
				} else IsPlayerSilent();
			} else SendClientMessage(playerid, COLOR_YELLOW, "[Anti-Spam] {FFFFFF}Line too long.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/hc [text]");
	} else NotAuthorized();
	return true;
}

COMMAND:slap(playerid, params[]) {
	new string[MAXO_TEXT], targetid, Float:plPos[3], Float:health;
	if(PlayerInfo[playerid][pAdmin] || PlayerInfo[playerid][pHelper]) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				GetPlayerHealth(targetid, health);
				SetPlayerHealth(targetid, health-5);
				GetPlayerPos(targetid, plPos[0], plPos[1], plPos[2]);
				SafeSetPlayerPos(targetid, plPos[0], plPos[1], plPos[2]+5);
				PlayerPlaySound(targetid, 1130, plPos[0], plPos[1], plPos[2]+5);
				format(string, MAXO_TEXT, "AdmCmd: You slapped on %s.", PlayerName(targetid));
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				format(string, MAXO_TEXT, "* You has been slapped by Admin %s.", PlayerName(playerid));
				SendClientMessage(targetid, COLOR_LIGHTRED, string);
				PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
				clear.string(string);
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/slap [playerid/PartOfName]");
	} else NotAuthorized();
	return true;
}

COMMAND:gotog(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] > 1) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			SetVehiclePos(GetPlayerVehicleID(playerid), -1986.8563, 139.4351, 27.0911);
		else
			SafeSetPlayerPos(playerid, -1986.8563, 139.4351, 27.0911);
		SafeResetPlayerInterior(playerid);
		GameTextForPlayer(playerid, "~g~You has been teleported!", 3500, 1);
	} else NotAuthorized();
	return true;
}

COMMAND:gotom(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] > 1) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			SetVehiclePos(GetPlayerVehicleID(playerid), -2311.7415, -1637.7587, 483.2643);
		else
			SafeSetPlayerPos(playerid, -2311.7415, -1637.7587, 483.2643);
		SafeResetPlayerInterior(playerid);
		GameTextForPlayer(playerid, "~g~You has been teleported!", 3500, 1);
	} else NotAuthorized();
	return true;
}

COMMAND:gotols(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] > 1) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			SetVehiclePos(GetPlayerVehicleID(playerid), 1529.6, -1691.2, 13.3);
		else
			SafeSetPlayerPos(playerid, 1529.6, -1691.2, 13.3);
		SafeResetPlayerInterior(playerid);
		GameTextForPlayer(playerid, "~g~You has been teleported!", 3500, 1);
	} else NotAuthorized();
	return true;
}

COMMAND:gotolv(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] > 1) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			SetVehiclePos(GetPlayerVehicleID(playerid), 1699.2, 1435.1, 10.7);
		else
			SafeSetPlayerPos(playerid, 1699.2, 1435.1, 10.7);
		SafeResetPlayerInterior(playerid);
		GameTextForPlayer(playerid, "~g~You has been teleported!", 3500, 1);
	} else NotAuthorized();
	return true;
}

COMMAND:gotosf(playerid, params[]) {
	if(PlayerInfo[playerid][pAdmin] > 1) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			SetVehiclePos(GetPlayerVehicleID(playerid), -1417.0, -295.8, 14.1);
		else
			SafeSetPlayerPos(playerid, -1417.0, -295.8, 14.1);
		SafeResetPlayerInterior(playerid);
		GameTextForPlayer(playerid, "~g~You has been teleported!", 3500, 1);
	} else NotAuthorized();
	return true;
}

COMMAND:takelicense(playerid, params[]) {
	new string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pAdmin] > 1) {
		if(!sscanf(params, "s[24]s[10]", PartialName[playerid][nume_introdus], params)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(!strcmp(params, "driving", true)) {
					if(PlayerInfo[targetid][pDrivingLicense]) {
						PlayerInfo[targetid][pDrivingLicense] = 0;
						format(string, MAXO_TEXT, "UPDATE players SET DrivingLicense = 0 WHERE ID = %d", PlayerInfo[targetid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						format(string, MAXO_TEXT, "AdmCmd: Admin %s has took your driving license.", PlayerName(playerid));
						SendClientMessage(targetid, COLOR_LIGHTRED, string);
						format(string, MAXO_TEXT, "* You has took the driving license of %s.", PlayerName(targetid));
						SendClientMessage(playerid, COLOR_LIGHTRED, string);
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not have the driving license.");
				}
				else if(!strcmp(params, "flying", true)) {
					if(PlayerInfo[targetid][pFlyingLicense]) {
						PlayerInfo[targetid][pFlyingLicense] = 0;
						format(string, MAXO_TEXT, "UPDATE players SET FlyingLicense = 0 WHERE ID = %d", PlayerInfo[targetid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						format(string, MAXO_TEXT, "AdmCmd: Admin %s has took your flying license.", PlayerName(playerid));
						SendClientMessage(targetid, COLOR_LIGHTRED, string);
						format(string, MAXO_TEXT, "* You has took the flying license of %s.", PlayerName(targetid));
						SendClientMessage(playerid, COLOR_LIGHTRED, string);
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not have the flying license.");
				}
				else if(!strcmp(params, "sailing", true)) {
					if(PlayerInfo[targetid][pSailingLicense]) {
						PlayerInfo[targetid][pSailingLicense] = 0;
						format(string, MAXO_TEXT, "UPDATE players SET SailingLicense = 0 WHERE ID = %d", PlayerInfo[targetid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						format(string, MAXO_TEXT, "AdmCmd: Admin %s has took your sailing license.", PlayerName(playerid));
						SendClientMessage(targetid, COLOR_LIGHTRED, string);
						format(string, MAXO_TEXT, "* You has took the driving sailing of %s.", PlayerName(targetid));
						SendClientMessage(playerid, COLOR_LIGHTRED, string);
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not have the sailing license.");
				}
				clear.string(string);
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/takelicense [playerid/PartOfName] [option]"), SendClientMessage(playerid, COLOR_GRAD1, "OPTIONS: driving | flying | sailing");
	} else NotAuthorized();
	return true;
}

COMMAND:givegun(playerid, params[]) {
	new string[MAXO_TEXT], targetid, weapons, ammos;
	if(PlayerInfo[playerid][pAdmin]) {
		if(!sscanf(params, "s[24]dd", PartialName[playerid][nume_introdus], weapons, ammos)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(weapons < 1 || weapons > 46 || weapons == 1)
					return SendClientMessage(playerid, COLOR_GRAD1, "Wrong Weapon ID!");
				GivePlayerWeapon(targetid, weapons, ammos);
				format(string, MAXO_TEXT, "AdmCmd: Admin %s has gave you a weapond ID %d with %d ammo.", PlayerName(playerid), weapons, ammos);
				SendClientMessage(targetid, COLOR_LIGHTRED, string);
				format(string, MAXO_TEXT, "* You gave %s a gun with ID %d and %d ammo.", PlayerName(targetid), weapons, ammos);
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
				clear.string(string);
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/givegun [playerid/PartOfName] [weapon ID] [ammo]");
			SendClientMessage(playerid, COLOR_GREY, "2(Golf Club) 3(Club) 4(knife) 5(bat) 6(Shovel) 7(Cue) 8(Katana) 10-13(Dildo) 14(Flowers) 15(Cane) 16(Grenades) ");
			SendClientMessage(playerid, COLOR_GREY, "18(Molotovs) 22(Pistol) 23(SPistol) 24(Eagle) 25(shotgun) 29(MP5) 30(AK47) 31(M4) 33(Rifle) 34(Sniper) 35(Bazoka) 36(HS Rocket Launcher) ");
			SendClientMessage(playerid, COLOR_GREY, "37(Flamethrower) 38(MiniGun) 39(Satchel Charge) 40(Detonator) 41(spray) 42(exting) 43(Camera) 46(Parachute)");
		}
	} else NotAuthorized();
	return true;
}

COMMAND:gethere(playerid, params[]) {
	new targetid, string[MAXO_TEXT], Float:plPos[3];
	if(PlayerInfo[playerid][pAdmin] > 2) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(!IsPlayerInAnyVehicle(targetid)) {
						SafeSetPlayerInterior(targetid, GetPlayerInterior(playerid));
						SafeSetPlayerVirtualWorld(targetid, GetPlayerVirtualWorld(playerid));
						GetPlayerPos(playerid, plPos[0], plPos[1], plPos[2]);
						SafeSetPlayerPos(targetid, plPos[0], plPos[1]+2, plPos[2]);
						format(string, MAXO_TEXT, "AdmCmd: You has been teleported at Admin %s.", PlayerName(playerid));
						SendClientMessage(targetid, COLOR_LIGHTRED, string);
						format(string, MAXO_TEXT, "* You teleported on %s in your closer.", PlayerName(targetid));
						SendClientMessage(playerid, COLOR_LIGHTRED, string);
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player is in a vehicle.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command on yourself.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/gethere [playerid/PartOfName]");
	} else NotAuthorized();
	return true;
}

COMMAND:setstat(playerid, params[]) {
	new string[MAXO_TEXT], targetid, option, amount;
	if(PlayerInfo[playerid][pAdmin] > 4) {
		if(!sscanf(params, "s[24]dd", PartialName[playerid][nume_introdus], option, amount)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid  = PartialName[playerid][jucator_gasit];
			if(ISBetween(option, 0, 23)) {
				if(targetid != INVALID_PLAYER_ID) {
					new sqlid = PlayerInfo[targetid][pSQLID];
					switch(option) {
						case 0: { // Level
							PlayerInfo[targetid][pLevel] = amount;
							format(string, MAXO_TEXT, "UPDATE players SET Level = %d WHERE ID = %d", PlayerInfo[targetid][pLevel], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Level to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Level for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 1: { //  Cash
							PlayerInfo[targetid][pCash] = amount;
							format(string, MAXO_TEXT, "UPDATE players SET Cash = %d WHERE ID = %d", PlayerInfo[targetid][pCash], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Cash Money to $%s.", PlayerName(playerid), FormatNumber(amount, 0, '.'));
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Cash Money for %s to $%s.", PlayerName(targetid), FormatNumber(amount, 0, '.'));
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 2: { // Money Account
							PlayerInfo[targetid][pAccount] = amount;
							format(string, MAXO_TEXT, "UPDATE players SET Account = %d WHERE ID = %d", PlayerInfo[targetid][pAccount], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Money in bank to $%s.", PlayerName(playerid), FormatNumber(amount, 0, '.'));
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Money in bank for %s to $%s.", PlayerName(targetid), FormatNumber(amount, 0, '.'));
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 3: { // Job
							if(amount > MAX_JOBS)
								return SendClientMessage(playerid, COLOR_GRAD1, "Invalid job ID.");
							PlayerInfo[targetid][pJob] = amount;
							format(string, MAXO_TEXT, "UPDATE players SET Job = %d WHERE ID = %d", PlayerInfo[targetid][pJob], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Job to %s.", PlayerName(playerid), JobInfo[amount][joName]);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Job for %s to %s.", PlayerName(targetid), JobInfo[amount][joName]);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 4: { // Spawn Health
							if(amount > 100)
								return SendClientMessage(playerid, COLOR_GRAD1, "The spawn Health must be maximum 100.");
							PlayerInfo[targetid][pSHealth] = amount;
							format(string, MAXO_TEXT, "UPDATE players SET SHealth = %f WHERE ID = %d", PlayerInfo[targetid][pSHealth], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Spawn Health to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Spawn Health for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 5: { // Phone Number
							PlayerInfo[targetid][pPnumber] = amount;
							format(string, MAXO_TEXT, "UPDATE players SET Pnumber = %d WHERE ID = %d", PlayerInfo[targetid][pAccount], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Phone Number to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Phone Number for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 6: { // Upgrade Points
							PlayerInfo[targetid][pUpgradeP] = amount;
							format(string, MAXO_TEXT, "UPDATE players SET UpgradeP = %d WHERE ID = %d", PlayerInfo[targetid][pUpgradeP], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your UpgradePoints to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the UpgradePoints for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 7: { // Pills
							PlayerInfo[targetid][pPills] = amount;
							format(string, MAXO_TEXT, "UPDATE players SET Pills = %d WHERE ID = %d", PlayerInfo[targetid][pPills], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Pills to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Pills for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 8: { // Respect Points
							PlayerInfo[targetid][pExp] = amount;
							format(string, MAXO_TEXT, "UPDATE players SET Respect = %d WHERE ID = %d", PlayerInfo[targetid][pAccount], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Respect Points to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Respect Points for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 9: { // Warnings
							if(amount < 4) {
								if(PlayerInfo[targetid][pWarnings] + amount > 3) {
									memcpy(KuramaBanStruc[playerid][banmotiv], "3Warns -> /setstat", 0, MAX_PLAYER_NAME*4, MAX_PLAYER_NAME*4);
									memcpy(KuramaBanStruc[playerid][nickban], PlayerName(targetid), 0, MAX_PLAYER_NAME*4, MAX_PLAYER_NAME*4);
									KuramaBanStruc[playerid][banidSQLID] = PlayerInfo[targetid][pSQLID];
									KuramaBanStruc[playerid][idinjoc] = targetid;
									GetPlayerIp(targetid, KuramaBanStruc[playerid][ipbanat], 25);
									Ban2(playerid,3,4);
									PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
								}
							}
						}
						case 10: {// Drugs
							PlayerInfo[targetid][pDrugs] = amount;
							format(string, MAXO_TEXT, "UPDATE players SET Drugs = %d WHERE ID = %d", PlayerInfo[targetid][pDrugs], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Drugs to %d grams.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Drugs for %s to %d grams.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 11: { // Materials
							PlayerInfo[targetid][pMats] = amount;
							format(string, MAXO_TEXT, "UPDATE players SET Materials = %d WHERE ID = %d", PlayerInfo[targetid][pMats], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Materials to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Materials for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 12: { // WantedLevel
							if(amount > 10)
								return SendClientMessage(playerid, COLOR_GRAD1, "The wanted Level is maximum 10.");
							if(PlayerInfo[targetid][pWlvl] + amount > 10)
								return SendClientMessage(playerid, COLOR_GRAD1, "This player have already wanted level maximum (10).");
							PlayerInfo[targetid][pWlvl] = amount;
							SetPlayerWanted(targetid, INVALID_PLAYER_ID, amount);
							format(string, MAXO_TEXT, "UPDATE players SET Wanted = %d WHERE ID = %d", PlayerInfo[targetid][pWlvl], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Wanted Level to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Wanted Level for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 13: { // Faction Warns
							if(amount < 4) {
								if(PlayerInfo[targetid][pFactiune] == FACT_CIVIL)
									return SendClientMessage(playerid, COLOR_GRAD1, "This player isn't in a faction.");
								if(PlayerInfo[targetid][pLeader] > FACT_CIVIL)
									return SendClientMessage(playerid, COLOR_GRAD1, "This player is Leader, can't use this command.");
								PlayerInfo[targetid][pFWarn] = amount;
								format(string, MAXO_TEXT, "UPDATE players SET FWarn = %d WHERE ID = %d", PlayerInfo[targetid][pFWarn], sqlid);
								mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
								format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Faction Warnings to %d.", PlayerName(playerid), amount);
								SendClientMessage(targetid, COLOR_LIGHTRED, string);
								format(string, MAXO_TEXT, "* You set the Faction Warnings for %s to %d.", PlayerName(targetid), amount);
								SendClientMessage(playerid, COLOR_LIGHTRED, string);
								//
								PlayerInfo[targetid][pFactiune] = FACT_CIVIL;
								PlayerInfo[targetid][pTeam] = FACT_CIVIL;
								PlayerInfo[targetid][pRank] = 0;
								PlayerInfo[targetid][pFWarn] = 0;
								SetPlayerFactionColor(targetid, PlayerInfo[targetid][pFactiune]);
								SetPlayerSpawnInfo(targetid);
								PlayerInfo[targetid][pSkin] = 264;
								SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
								SpawnPlayer(targetid);
								format(string, MAXO_TEXT, "* You have been kicked from faction your faction by Admin %s.", PlayerName(playerid));
								SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
								SendClientMessage(targetid, COLOR_LIGHTBLUE, "* Now, you are again Civilian.");
								format(string, MAXO_TEXT, "* You have kicked on %s from your faction.", PlayerName(targetid));
								SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
								format(string, MAXO_TEXT2, "UPDATE players SET Faction = %d, Team = %d WHERE ID = %d", PlayerInfo[targetid][pFactiune], PlayerInfo[targetid][pTeam], PlayerInfo[targetid][pSQLID]);
								mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
								format(string, MAXO_TEXT2, "UPDATE players SET Rank = %d, Skin = %d, FWarn = %d WHERE ID = %d", PlayerInfo[targetid][pRank], PlayerInfo[targetid][pSkin], PlayerInfo[targetid][pFWarn], PlayerInfo[targetid][pSQLID]);
								mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
								PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
								new log[MAXO_TEXT2];
								format(log, MAXO_TEXT2, "%s a fost demis din factiunea sa de catre Adminul %s", PlayerName(targetid), PlayerName(playerid));
								FactionsLog(targetid, log);
								//
								PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
							} else SendClientMessage(playerid, COLOR_GRAD1, "The maximum FWarns is 3.");
						}
						case 14: { // Gift Points
							PlayerInfo[targetid][pGiftPoints] = amount;
							format(string, MAXO_TEXT, "UPDATE players SET GiftPoints = %d WHERE ID = %d", PlayerInfo[targetid][pGiftPoints], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Gift Points to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Gift Points for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 15: { // Car Slots
							PlayerInfo[targetid][pCarSlots] = amount;
							format(string, MAXO_TEXT, "UPDATE players SET CarSlots = %d WHERE ID = %d", PlayerInfo[targetid][pCarSlots], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Car Slots to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Car Slots for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 16: { // Farmer Skill
							if(amount > 5 || amount < 1) return SendClientMessage(playerid, COLOR_GRAD1, "Invalid skill level (1-5).");
							switch(amount) {
								case 1: PlayerInfo[targetid][pFarmerSkill] = 48;
								case 2: PlayerInfo[targetid][pFarmerSkill] = 144;
								case 3: PlayerInfo[targetid][pFarmerSkill] = 336;
								case 4: PlayerInfo[targetid][pFarmerSkill] = 720;
								case 5: PlayerInfo[targetid][pFarmerSkill] = 721;
							}
							format(string, MAXO_TEXT, "UPDATE players SET FarmerSkill = %d WHERE ID = %d", PlayerInfo[targetid][pFarmerSkill], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Farmer Skill to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Farmer Skill for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 17: { // Arms Dealer Skill
							if(amount > 5 || amount < 1) return SendClientMessage(playerid, COLOR_GRAD1, "Invalid skill level (1-5).");
							switch(amount) {
								case 1: PlayerInfo[targetid][pArmsDealerSkill] = 50;
								case 2: PlayerInfo[targetid][pArmsDealerSkill] = 150;
								case 3: PlayerInfo[targetid][pArmsDealerSkill] = 246;
								case 4: PlayerInfo[targetid][pArmsDealerSkill] = 438;
								case 5: PlayerInfo[targetid][pArmsDealerSkill] = 439;
							}
							format(string, MAXO_TEXT, "UPDATE players SET ArmsDealerSkill = %d WHERE ID = %d", PlayerInfo[targetid][pArmsDealerSkill], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Arms Dealer Skill to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Arms Dealer Skill for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 18: { // Street Sweeper Skill
							if(amount > 5 || amount < 1) return SendClientMessage(playerid, COLOR_GRAD1, "Invalid skill level (1-5).");
							switch(amount) {
								case 1: PlayerInfo[targetid][pSweeperSkill] = 96;
								case 2: PlayerInfo[targetid][pSweeperSkill] = 288;
								case 3: PlayerInfo[targetid][pSweeperSkill] = 672;
								case 4: PlayerInfo[targetid][pSweeperSkill] = 1440;
								case 5: PlayerInfo[targetid][pSweeperSkill] = 1441;
							}
							format(string, MAXO_TEXT, "UPDATE players SET SweeperSkill = %d WHERE ID = %d", PlayerInfo[targetid][pSweeperSkill], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Street Sweeper Skill to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Street Sweeper Skill for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 19: { // News Reporter Skill
							if(amount > 5 || amount < 1) return SendClientMessage(playerid, COLOR_GRAD1, "Invalid skill level (1-5).");
							switch(amount) {
								case 1: PlayerInfo[targetid][pNewsSkill] = 50;
								case 2: PlayerInfo[targetid][pNewsSkill] = 150;
								case 3: PlayerInfo[targetid][pNewsSkill] = 300;
								case 4: PlayerInfo[targetid][pNewsSkill] = 500;
								case 5: PlayerInfo[targetid][pNewsSkill] = 501;
							}
							format(string, MAXO_TEXT, "UPDATE players SET NewsSkill = %d WHERE ID = %d", PlayerInfo[targetid][pNewsSkill], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your News Skill to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the News Skill for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 20: { // Dust Skill
							if(amount > 5 || amount < 1) return SendClientMessage(playerid, COLOR_GRAD1, "Invalid skill level (1-5).");
							switch(amount) {
								case 1: PlayerInfo[targetid][pDustSkill] = 200;
								case 2: PlayerInfo[targetid][pDustSkill] = 600;
								case 3: PlayerInfo[targetid][pDustSkill] = 1400;
								case 4: PlayerInfo[targetid][pDustSkill] = 3000;
								case 5: PlayerInfo[targetid][pDustSkill] = 3001;
							}
							format(string, MAXO_TEXT, "UPDATE players SET DustSkill = %d WHERE ID = %d", PlayerInfo[targetid][pDustSkill], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Dust Skill to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Dust Skill for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 21: { // Car Jacker Skill
							if(amount > 5 || amount < 1) return SendClientMessage(playerid, COLOR_GRAD1, "Invalid skill level (1-5).");
							switch(amount) {
								case 1: PlayerInfo[targetid][pCarJackerSkill] = 16;
								case 2: PlayerInfo[targetid][pCarJackerSkill] = 56;
								case 3: PlayerInfo[targetid][pCarJackerSkill] = 152;
								case 4: PlayerInfo[targetid][pCarJackerSkill] = 240;
								case 5: PlayerInfo[targetid][pCarJackerSkill] = 241;
							}
							format(string, MAXO_TEXT, "UPDATE players SET CarJackerSkill = %d WHERE ID = %d", PlayerInfo[targetid][pCarJackerSkill], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Car Jacker Skill to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Car Jacker Skill for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 22: { // Drugs Dealer Skill
							if(amount > 5 || amount < 1) return SendClientMessage(playerid, COLOR_GRAD1, "Invalid skill level (1-5).");
							switch(amount) {
								case 1: PlayerInfo[targetid][pDrugsDealerSkill] = 50;
								case 2: PlayerInfo[targetid][pDrugsDealerSkill] = 150;
								case 3: PlayerInfo[targetid][pDrugsDealerSkill] = 246;
								case 4: PlayerInfo[targetid][pDrugsDealerSkill] = 438;
								case 5: PlayerInfo[targetid][pDrugsDealerSkill] = 439;
							}
							format(string, MAXO_TEXT, "UPDATE players SET DrugsDealerSkill = %d WHERE ID = %d", PlayerInfo[targetid][pDrugsDealerSkill], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Drugs Dealer Skill to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Drugs Dealer Skill for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
						case 23: { // Fisher Skill
							if(amount > 5 || amount < 1) return SendClientMessage(playerid, COLOR_GRAD1, "Invalid skill level (1-5).");
							switch(amount) {
								case 1: PlayerInfo[targetid][pFishSkill] = 10;
								case 2: PlayerInfo[targetid][pFishSkill] = 50;
								case 3: PlayerInfo[targetid][pFishSkill] = 200;
								case 4: PlayerInfo[targetid][pFishSkill] = 400;
								case 5: PlayerInfo[targetid][pFishSkill] = 401;
							}
							format(string, MAXO_TEXT, "UPDATE players SET FishSkill = %d WHERE ID = %d", PlayerInfo[targetid][pFishSkill], sqlid);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: Admin %s set your Fisher Skill to %d.", PlayerName(playerid), amount);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You set the Fisher Skill for %s to %d.", PlayerName(targetid), amount);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						}
					}
					clear.string(string);
				}
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid option.");
		}
		else
		{
			SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/setstat [playerid/PartOfName] [option] [amount]");
			SendClientMessage(playerid, COLOR_GRAD1, "OPTIONS: 0) Level 1) Cash 2) Money(account) 3) Job 4) Spawn Health 5) Phone Nr. 6) UpgradePoints 7) Pills");
			SendClientMessage(playerid, COLOR_GRAD2, "OPTIONS: 8) RespectPoints 9) Warnings 10) Drugs 11) Materials 12) WantedLevel 13) FactionWarns");
			SendClientMessage(playerid, COLOR_GRAD3, "OPTIONS: 14) GiftPoints 15) CarSlots 16) Farmer Skill 17) Arms Dealer SKill 18) Street Sweeper Skill 19) News Skill");
			SendClientMessage(playerid, COLOR_GRAD3, "OPTIONS: 20) Dustman Skill 21) Car Jacker Skill 22) Drugs Dealer Skill 23) Fisher Skill");
		}
	} else NotAuthorized();
	return true;
}

COMMAND:ajail(playerid, params[]) {
	new string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pAdmin]) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(PlayerInfo[targetid][pWlvl]) {
					if(!PlayerInfo[targetid][pJailed]) {
						PlayerInfo[targetid][pJailTime] = (PlayerInfo[targetid][pWlvl] * 540);
						PlayerInfo[targetid][pJailed] = 1;
						PlayerInfo[targetid][pWlvl] = 0;
						SetPlayerWanted(targetid, INVALID_PLAYER_ID, PlayerInfo[targetid][pWlvl]);
						SafeSetPlayerVirtualWorld(targetid, LSPD_VW);
						PutPlayerInCell(targetid);
						format(string, MAXO_TEXT2, "UPDATE players SET JailTime = %d, Jailed = %d, Wanted = %d WHERE ID = %d", PlayerInfo[targetid][pJailTime], PlayerInfo[targetid][pJailed], PlayerInfo[targetid][pWlvl], PlayerInfo[targetid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						format(string, MAXO_TEXT, ">> You has been jailed by Admin %s for %s minutes. <<", PlayerName(playerid), ConvertTime(PlayerInfo[targetid][pJailTime]));
						SendClientMessage(targetid, COLOR_LIGHTRED, string);
						InsertSanctionInPanel(targetid, playerid, ACTION_JAIL, string);
						format(string, MAXO_TEXT, "* You got put on %s in jail.", PlayerName(targetid));
						SendClientMessage(playerid, COLOR_LIGHTRED, string);
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player is already in jail.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "This player isn't wanted by cops.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/ajail [playerid/PartOfName]");
	} else NotAuthorized();
	return true;
}

COMMAND:updatecolorcar(playerid, params[]) {
	new string[MAXO_TEXT], vID = GetPlayerVehicleID(playerid);
	if(PlayerInfo[playerid][pAdmin] > 4) {
		new colors[2];
		if(!sscanf(params, "dd", colors[0], colors[1])) {
			if(CarInfo[vID][cType] == VEHICLE_TYPE_PERSONAL)
				return SendClientMessage(playerid, COLOR_GRAD1, "You can't change the colors for this type of vehicle.");
			CarInfo[vID][cColor][0] = colors[0];
			CarInfo[vID][cColor][1] = colors[1];
			ChangeVehicleColor(vID, colors[0], colors[1]);
			format(string, MAXO_TEXT, "UPDATE vehicles SET Color1 = %d, Color2 = %d WHERE ID = %d", colors[0], colors[1], CarInfo[vID][cSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", VEHICLE_THREAD_ID);
			format(string, MAXO_TEXT, "AdmCmd: You changed the color for vehicle ID %d with the colors %d-%d.", vID, colors[0], colors[1]);
			SendClientMessage(playerid, COLOR_LIGHTRED, string);
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/updatecolorcar [color1] [color2]");
	} else NotAuthorized();
	return true;
}

COMMAND:aunjail(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pAdmin]) {
		if(!sscanf(params, "s[24]s[64]", PartialName[playerid][nume_introdus], params)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(PlayerInfo[targetid][pJailTime] || PlayerInfo[targetid][pJailed]) {
					if(strlen(params) < 64) {
						PlayerInfo[targetid][pJailed] = 0;
						PlayerInfo[targetid][pJailTime] = 0;
						SafeSetPlayerInterior(targetid, 0);
						SafeSetPlayerVirtualWorld(targetid, 0);
						TogglePlayerControllable(targetid, true);
						SafeSetPlayerPos(targetid, 1541.7213, -1676.3795, 13.5531);
						SetPlayerWorldBounds(targetid, 20000.0000, -20000.0000, 20000.0000, -20000.0000);
						format(string, MAXO_TEXT2, "UPDATE players SET Jailed = %d, JailTime = %d WHERE ID = %d", PlayerInfo[targetid][pJailed], PlayerInfo[targetid][pJailTime], PlayerInfo[targetid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						format(string, MAXO_TEXT, "* %s was relased from jail by Admin %s.", PlayerName(targetid), PlayerName(playerid));
						OOCNews(COLOR_LIGHTRED, string);
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "This player isn't in jail.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/unjail [playerid/PartOfName] [reason]");
	} else NotAuthorized();
	return true;
}

COMMAND:prison(playerid, params[]) {
	new string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pAdmin]) {
		if(!sscanf(params, "s[24]s[64]", PartialName[playerid][nume_introdus], params)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != playerid) {
				if(targetid != INVALID_PLAYER_ID) {
					SafeSetPlayerPos(targetid, 107.2300, 1920.6311, 18.5208);
					SetPlayerWorldBounds(targetid, 337.5694, 101.5826, 1940.9759, 1798.7453);
					if(IsPlayerInInside(playerid))
						SafeResetPlayerInterior(playerid);
					ResetPlayerWeapons(targetid);
					PlayerInfo[targetid][pJailed] = 2;
					PlayerInfo[targetid][pJailTime] = 3600;
					PlayerInfo[targetid][pWlvl] = 0;
					SetPlayerWanted(targetid, INVALID_PLAYER_ID, PlayerInfo[targetid][pWlvl]);
					TogglePlayerControllable(targetid, false);
					format(string, MAXO_TEXT2, "UPDATE players SET JailTime = %d, Jailed = %d, Wanted = %d WHERE ID = %d", PlayerInfo[targetid][pJailTime], PlayerInfo[targetid][pJailed], PlayerInfo[pWlvl], PlayerInfo[targetid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					format(string, MAXO_TEXT, ">> You are jailed in Restricted Area for %s by Admin %s, Reason: %s. <<", ConvertTime(PlayerInfo[targetid][pJailTime]), PlayerName(playerid), params);
					SendClientMessage(targetid, COLOR_LIGHTRED, string);
					InsertSanctionInPanel(targetid, playerid, ACTION_JAIL, string);
					format(string, MAXO_TEXT, "* You has put on %s as prison in Restricted Area for %s.", PlayerName(targetid), ConvertTime(PlayerInfo[targetid][pJailTime]));
					SendClientMessage(playerid, COLOR_LIGHTRED, string);
					PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
					clear.string(string);
				}
			} else SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command on yourself.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/prison[playerid/PartOfName] [reason]");
	} else NotAuthorized();
	return true;
}

COMMAND:unprison(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pAdmin]) {
		if(!sscanf(params, "s[24]s[64]", PartialName[playerid][nume_introdus], params)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(PlayerInfo[targetid][pJailTime] && PlayerInfo[targetid][pJailed] == 2) {
					if(strlen(params) < 64) {
						ResetPlayerWeapons(targetid);
						PlayerInfo[targetid][pJailed] = 0;
						PlayerInfo[targetid][pJailTime] = 0;
						SafeSetPlayerInterior(targetid, 0);
						SafeSetPlayerVirtualWorld(targetid, 0);
						TogglePlayerControllable(targetid, true);
						SafeSetPlayerPos(targetid, 1541.7213, -1676.3795, 13.5531);
						SetPlayerWorldBounds(targetid, 20000.0000, -20000.0000, 20000.0000, -20000.0000);
						format(string, MAXO_TEXT2, "UPDATE players SET Jailed = %d, JailTime = %d WHERE ID = %d", PlayerInfo[targetid][pJailed], PlayerInfo[targetid][pJailTime], PlayerInfo[targetid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						format(string, MAXO_TEXT, "* %s was relased from Restricted Area by Admin %s.", PlayerName(targetid), PlayerName(playerid));
						OOCNews(COLOR_LIGHTRED, string);
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is in Restricted Area.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/unjail [playerid/PartOfName] [reason]");
	} else NotAuthorized();
	return true;
}

COMMAND:check(playerid, params[]) {
	new string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pAdmin]) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				ShowStats(playerid, targetid);
				format(string, MAXO_TEXT, "AdmCmd: %s has been checked by Admin %s.", PlayerName(targetid), PlayerName(playerid));
				ABroadCast(COLOR_LIGHTRED, string, 1);
				PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid player.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/check [playerid/PartOfName]");
	} else NotAuthorized();
	return true;
}

COMMAND:disable(playerid, params[]) {
	new string[MAXO_TEXT], targetid, time;
	if(PlayerInfo[playerid][pHelper]) {
		if(!sscanf(params, "s[24]ds[64]", PartialName[playerid][nume_introdus], time, params)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(ISBetween(strlen(params), 1, 64)) {
						if(PlayerInfo[targetid][pHelper] < 1 || PlayerInfo[targetid][pAdmin] < 1) {
							if(!PlayerInfo[targetid][pDisable]) {
								PlayerInfo[targetid][pDisable] = 1;
								PlayerInfo[targetid][pDisableTime] += time*60;
								format(string, MAXO_TEXT, "UPDATE players SET Disable = %d, DisableTime = %d WHERE ID = %d", PlayerInfo[targetid][pDisable], PlayerInfo[targetid][pDisableTime], PlayerInfo[targetid][pSQLID]);
								mysql_tquery(connectionHandle, string, "NoReturnThread", "D", UPDATE_THREAD_ID);
								format(string, MAXO_TEXT, "AdmCmd: You has been disable by Helper %s, Reason: %s, Time: %s. Use /disabletime", PlayerName(playerid), params, ConvertTime(PlayerInfo[targetid][pDisableTime]));
								SendClientMessage(targetid, COLOR_LIGHTRED, string);
								format(string, MAXO_TEXT, "HelperWarning: %s was been disable by Helper %s, Reason: %s, Time: %s.", PlayerName(targetid), PlayerName(playerid), params, ConvertTime(PlayerInfo[targetid][pDisableTime]));
								ABroadCast(COLOR_YELLOW, string, 1);
								format(string, MAXO_TEXT, "HelperWarning: %s was been disable by Helper %s, Reason: %s, Time: %s.", PlayerName(targetid), PlayerName(playerid), params, ConvertTime(PlayerInfo[targetid][pDisableTime]));
								HBroadCast(COLOR_YELLOW, string, 1);
								PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
								clear.string(string);
							} else SendClientMessage(playerid, COLOR_GRAD1, "This players is already disable.");
						} else SendClientMessage(playerid, COLOR_GRAD1, "This player is personal, you cannot use this command on him.");
					} else SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: {FFFFFF}Line too long.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command on yourself.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/disable [playerid/PartOfName] [time(minutes)] [reason]");
	} else NotAuthorized();
	return true;
}

COMMAND:undisable(playerid, params[]) {
	new string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pHelper]) {
		if(!sscanf(params, "s[24]s[64]", PartialName[playerid][nume_introdus], params)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(ISBetween(strlen(params), 1, 64)) {
					if(PlayerInfo[targetid][pDisable]) {
						if(targetid != playerid) {
							PlayerInfo[targetid][pDisable] = 0;
							PlayerInfo[targetid][pDisableTime] = 0;
							format(string, MAXO_TEXT, "UPDATE players SET Disable = %d, DisableTime = %d WHERE ID = %d", PlayerInfo[targetid][pDisable], PlayerInfo[targetid][pDisableTime], PlayerInfo[targetid][pSQLID]);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "D", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "AdmCmd: You has been undisable by Helper %s, Reason: %s.", PlayerName(playerid), params, ConvertTime(PlayerInfo[targetid][pDisableTime]));
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "HelperWarning: %s was been undisable by Helper %s, Reason: %s.", PlayerName(targetid), PlayerName(playerid), params);
							ABroadCast(COLOR_YELLOW, string, 1);
							format(string, MAXO_TEXT, "HelperWarning: %s was been undisable by Helper %s, Reason: %s.", PlayerName(targetid), PlayerName(playerid), params);
							HBroadCast(COLOR_YELLOW, string, 1);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
							clear.string(string);
						} else SendClientMessage(playerid, COLOR_GRAD1, "You cannot use this command on yourself.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player isn't disabled.");
				} else SendClientMessage(playerid, COLOR_YELLOW, "Anti-Spam: {FFFFFF}Line too long.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/undisable [playerid/PartOfName] [reason]");
	} else NotAuthorized();
	return true;
}

COMMAND:sethp(playerid, params[]) {
	new string[MAXO_TEXT], targetid, Float:amount;
	if(PlayerInfo[playerid][pAdmin] > 4) {
		if(!sscanf(params, "s[24]f", PartialName[playerid][nume_introdus], amount)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				SetPlayerHealth(targetid, amount);
				format(string, MAXO_TEXT, "AdmCmd: Your health was been set (%.1f) by Admin %s.", amount, PlayerName(playerid));
				SendClientMessage(targetid, COLOR_LIGHTRED, string);
				format(string, MAXO_TEXT, "* You set %s' health (%.1f).", PlayerName(targetid), amount);
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
				clear.string(string);
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/sethp [playerid/PartOfName] [amount]");
	} else NotAuthorized();
	return true;
}

COMMAND:setfactionlevel(playerid, params[]) {
	new fID, fLe, string[MAXO_TEXT];
	if(PlayerInfo[playerid][pAdmin] > 1336) {
		if(!sscanf(params, "dd", fID, fLe)) {
			if(ISBetween(fID, FACT_LSPD, MAX_FACTIONS-1)) {
				if(fLe > 0) {
					FactionInfo[fID][fFactionLevel] = fLe;
					format(string, MAXO_TEXT, "UPDATE factions SET level = %d WHERE ID = %d", fLe, fID);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", FACTIONS_THREAD_ID);
					format(string, MAXO_TEXT, "AdmCmd: %s set the level %d for faction %s.", PlayerName(playerid), fLe, FactionInfo[fID][fName]);
					ABroadCast(COLOR_LIGHTRED, string, 1);
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid level.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid faction id.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/setfactionlevel [factionid] [level]");
	} else NotAuthorized();
	return true;
}

COMMAND:makeadmin(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid, level;
	if(PlayerInfo[playerid][pAdmin] > 5) {
		if(!sscanf(params, "s[24]d", PartialName[playerid][nume_introdus], level)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(ISBetween(level, 0, 1337)) {
					PlayerInfo[targetid][pAdmin] = level;
					format(string, MAXO_TEXT, "UPDATE players SET Admin = %d WHERE ID = %d", PlayerInfo[targetid][pAdmin], PlayerInfo[targetid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					format(string, MAXO_TEXT, "You have been promoted as Admin Level %d by Admin %s.", level, PlayerName(playerid));
					SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
					format(string, MAXO_TEXT, "You promoted on %s as Admin Level %d.", PlayerName(targetid), level);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "The level must be between 0-1337.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: "ALB"/makeadmin [playerid/PartOfName] [level]");
	} else NotAuthorized();
	return true;
}

COMMAND:makehelper(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid, level;
	if(PlayerInfo[playerid][pAdmin] > 5 || PlayerInfo[playerid][pHelper] > 5) {
		if(!sscanf(params, "s[24]d", PartialName[playerid][nume_introdus], level)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(ISBetween(level, 0, 1337)) {
					PlayerInfo[targetid][pHelper] = level;
					format(string, MAXO_TEXT, "UPDATE players SET Helper = %d WHERE ID = %d", PlayerInfo[targetid][pHelper], PlayerInfo[targetid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					format(string, MAXO_TEXT, "You have been promoted as Helper Level %d by %s.", level, PlayerName(playerid));
					SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
					format(string, MAXO_TEXT, "You promoted on %s as Helper Level %d.", PlayerName(targetid), level);
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "The level must be between 0-1337.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: "ALB"/makehelper [playerid/PartOfName] [level]");
	} else NotAuthorized();
	return true;
}

COMMAND:adminchat(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pAdmin]) {
		if(!sscanf(params, "s[128]", params)) {
			if(strlen(params) < 100) {
				if(PlayerInfo[playerid][pMute])
					return IsPlayerSilent();
				format(string, MAXO_TEXT, "» %s Admin Level %d: %s «", PlayerName(playerid), PlayerInfo[playerid][pAdmin], params);
				ABroadCast(COLOR_YELLOW, string, 1);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/a(dmin)c(hat) [message]");
	} else NotAuthorized();
	return true;
}

COMMAND:a(playerid, params[]) {
	return cmd_adminchat(playerid, params);
}

COMMAND:kick(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pAdmin]) {
		if(!sscanf(params, "s[24]s[25]", PartialName[playerid][nume_introdus], params)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(strlen(params) < 25) {
				if(targetid != INVALID_PLAYER_ID) {
					format(string, MAXO_TEXT, "AdmCmd: %s was been kicked by Admin %s, Reason: %s.", PlayerName(targetid), PlayerName(playerid), params);
					SendClientMessageToAll(COLOR_LIGHTRED, string);
					InsertSanctionInPanel(targetid, playerid, ACTION_KICK, string);
					format(string, MAXO_TEXT, "You have been kicked!\nAdmin: %s\nReason: %s\nPt. reclamatii: "gamemode_forum"", PlayerName(playerid), params);
					ShowPlayerDialog(targetid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "You have been kicked!", string, "Okay", "");
					KickDeelay(targetid);
					PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
					clear.string(string);
				}
			} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/kick [playerid/PartOfName] [reason]");
	} else NotAuthorized();
	return true;
}

COMMAND:respawn(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pAdmin] || PlayerInfo[playerid][pHelper]) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(GetPlayerVehicleID(targetid) != INVALID_VEHICLE_ID) {
					new Float:veh[3];
					GetVehiclePos(GetPlayerVehicleID(targetid), veh[0], veh[1], veh[2]);
					SafeSetPlayerPos(targetid, veh[0], veh[1], veh[2]);
				}
				SetPlayerSpawnInfo(targetid);
				SpawnPlayer(targetid);
				format(string, MAXO_TEXT, "* You have been respawned by Admin %s.", PlayerName(playerid));
				SendClientMessage(targetid, COLOR_LIGHTRED, string);
				format(string, MAXO_TEXT, "* You respawned on %s.", PlayerName(targetid));
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				if(PlayerInfo[playerid][pAdmin]) format(string, MAXO_TEXT, "AdmCmd: %s was been respawned by Admin %s.", PlayerName(targetid), PlayerName(playerid));
				else if(PlayerInfo[playerid][pHelper]) format(string, MAXO_TEXT, "AdmCmd: %s was been respawned by Helper %s.", PlayerName(targetid), PlayerName(playerid));
				ABroadCast(COLOR_LIGHTRED, string, 1);
				PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
				clear.string(string);
			}
		} else SendClientMessage(playerid, COLOR_GRAD1, "USAGE: {FFFFFF}/respawn [playerid/PartOfName]");
	} else NotAuthorized();
	return true;
}

COMMAND:checkweapons(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pAdmin]) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				format(string, MAXO_TEXT, "|____________ %s's weapons ____________|", PlayerName(targetid));
				SendClientMessage(playerid, -1, string);
				new weapons[13][2], wname[MAX_GUN_NAME], nrarme = 0;
				for (new i = 1; i <= 12; i ++) {
				    GetPlayerWeaponData(targetid, i, weapons[i][0], weapons[i][1]);
				    if(weapons[i][0] != 0 && weapons[i][1] > 0) {
				    	GetWeaponNameEx(weapons[i][0], wname, MAX_GUN_NAME);
					    format(string, MAXO_TEXT, "%s (%d)", wname, weapons[i][1]);
					    SendClientMessage(playerid, COLOR_GRAD1, string);
					    nrarme ++;
					} 
				}
				if(!nrarme) 
					return SendClientMessage(playerid, COLOR_GRAD1, "No weapons.");
				PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
				clear.string(string);
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/checkweapons [playerid/PartOfName]");
	} else NotAuthorized();
	return true;
}

COMMAND:ooc(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pAdmin]) {
		if(!sscanf(params, "s[75]", params)) {
			if(strlen(params) < 75) {
				if(PlayerInfo[playerid][pMute])
					return IsPlayerSilent();
				format(string, MAXO_TEXT, "(( %s: %s ))", PlayerName(playerid), params);
				OOCNews(COLOR_OOC, string);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/ooc [message]");
	} else NotAuthorized();
	return true;
}

COMMAND:o(playerid, params[]) {
	return cmd_ooc(playerid, params);
}

COMMAND:clearchat(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pAdmin]) {
		foreach(Player, i) {
			ClearChatBox(i, 60);
		}
		format(string, MAXO_TEXT, "AdmCmd: Admin %s has cleared the chat.", PlayerName(playerid));
		OOCNews(COLOR_LIGHTRED, string);
		clear.string(string);
	} else NotAuthorized();
	return true;
}

COMMAND:cc(playerid, params[]) {
	return cmd_clearchat(playerid, params);
}

#define MAX_INTERIOR_ID (19)
COMMAND:setint(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid, intid;
	if(PlayerInfo[playerid][pAdmin] || PlayerInfo[playerid][pHelper]) {
		if(!sscanf(params, "s[24]d", PartialName[playerid][nume_introdus], intid)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(ISBetween(intid, 0, MAX_INTERIOR_ID)) {
					SafeSetPlayerInterior(targetid, intid);
					format(string, MAXO_TEXT, "* Your interior id (%d) was changed by %s.", intid, PlayerName(playerid));
					SendClientMessage(targetid, COLOR_LIGHTRED, string);
					format(string, MAXO_TEXT, "* You changed the interior id (%d) for the player %s.", intid, PlayerName(targetid));
					SendClientMessage(playerid, COLOR_LIGHTRED, string);
					PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "The interior id is between 0-18.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/setint [playerid/PartOfName] [interior id]");
	} else NotAuthorized();
	return true;
}

COMMAND:setvw(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid, intid;
	if(PlayerInfo[playerid][pAdmin] || PlayerInfo[playerid][pHelper]) {
		if(!sscanf(params, "s[24]d", PartialName[playerid][nume_introdus], intid)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				SafeSetPlayerVirtualWorld(targetid, intid);
				format(string, MAXO_TEXT, "* Your virtual id (%d) was changed by %s.", intid, PlayerName(playerid));
				SendClientMessage(targetid, COLOR_LIGHTRED, string);
				format(string, MAXO_TEXT, "* You changed the virtual id (%d) for the player %s.", intid, PlayerName(targetid));
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
				clear.string(string);
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/setvw [playerid/PartOfName] [virtual id]");
	} else NotAuthorized();
	return true;
}

COMMAND:mute(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid, mtime;
	if(PlayerInfo[playerid][pAdmin]) {
		if(!sscanf(params, "s[24]ds[25]", PartialName[playerid][nume_introdus], mtime, params)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(ISBetween(mtime, 1, 240)) {
					if(strlen(params) < 25) {
						PlayerInfo[targetid][pMute] = 1;
						PlayerInfo[playerid][pMuteTime] = (mtime * 60);
						format(string, MAXO_TEXT, "UPDATE players SET Mute = %d WHERE ID = %d", PlayerInfo[targetid][pMute], PlayerInfo[targetid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						format(string, MAXO_TEXT, "UPDATE players SET MuteTime = %d WHERE ID = %d", PlayerInfo[targetid][pMuteTime], PlayerInfo[targetid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						format(string, MAXO_TEXT, "AdmCmd: %s was muted %d minutes by Admin %s, Reason: %s.", PlayerName(targetid), mtime, PlayerName(playerid), params);
						OOCNews(COLOR_LIGHTRED, string);
						InsertSanctionInPanel(targetid, playerid, ACTION_MUTE, string);
						format(string, MAXO_TEXT, "* You have been muted %d minutes by Admin, Reason: %s. Use /mutetime", mtime, PlayerName(playerid), params);
						SendClientMessage(targetid, COLOR_LIGHTRED, string);
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "The time must be between 1-240 minutes.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/mute [playerid/PartOfName] [time(minutes)] [reason]");
	} else NotAuthorized();
	return true;
}

COMMAND:unmute(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pAdmin]) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(PlayerInfo[targetid][pMute]) {
					PlayerInfo[targetid][pMute] = 0;
					PlayerInfo[targetid][pMuteTime] = 0;
					format(string, MAXO_TEXT, "UPDATE players SET Mute = %d WHERE ID = %d", PlayerInfo[targetid][pMute], PlayerInfo[targetid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					format(string, MAXO_TEXT, "UPDATE players SET MuteTime = %d WHERE ID = %d", PlayerInfo[targetid][pMuteTime], PlayerInfo[targetid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "That player not is muted.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/unmute [playerid/PartOfName]");
	} else NotAuthorized();
	return true;
}

COMMAND:freeze(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pAdmin] || PlayerInfo[playerid][pHelper]) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				TogglePlayerControllable(targetid, false);
				format(string, MAXO_TEXT, "* You have been freezed by Admin %s.", PlayerName(playerid));
				SendClientMessage(targetid, COLOR_LIGHTRED, string);
				format(string, MAXO_TEXT, "* You has freezed on %s.", PlayerName(targetid));
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
				clear.string(string);
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/freeze [playerid/PartOfName]");
	} else NotAuthorized();
	return true;
}

COMMAND:unfreeze(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pAdmin] || PlayerInfo[playerid][pHelper]) {
		if(!sscanf(params, "u", targetid)) {
			if(targetid != INVALID_PLAYER_ID) {
				TogglePlayerControllable(targetid, true);
				format(string, MAXO_TEXT, "* You have been unfreezed by Admin %s.", PlayerName(playerid));
				SendClientMessage(targetid, COLOR_LIGHTRED, string);
				format(string, MAXO_TEXT, "* You has unfreezed on %s.", PlayerName(targetid));
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid player.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/freeze [playerid/PartOfName]");
	} else NotAuthorized();
	return true;
}

COMMAND:checkactivity(playerid, params[]) {
	new
		string[MAXO_TEXT], pName[MAX_PLAYER_NAME+1], pID;
	if(PlayerInfo[playerid][pAdmin]) {
		if(!sscanf(params, "s[25]", pName)) {
			if(!sscanf(params, "u", pID)) {
				if(pID == INVALID_PLAYER_ID) {
					format(string, MAXO_TEXT, "SELECT * FROM players WHERE Name = '%s' LIMIT 1", pName);
					mysql_tquery(connectionHandle, string, "CheckPlayerActivity", "d", playerid);
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "This command is used only for offline players.");
			} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/checkactivity [player name]");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/checkactivity [player name]");
	} else NotAuthorized();
	return true;
}

COMMAND:givelicense(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pAdmin] > 1) {
		if(!sscanf(params, "s[24]s[10]", PartialName[playerid][nume_introdus], params)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(!strcmp(params, "driving", true)) {
					PlayerInfo[targetid][pDrivingLicense] = gettime()+ExpiraLicenta;
					format(string, MAXO_TEXT, "UPDATE players SET DrivingLicense = %d WHERE ID = %d", PlayerInfo[targetid][pDrivingLicense], PlayerInfo[targetid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					format(string, MAXO_TEXT, "* Admin %s has give you the driving license valid untill %s.", PlayerName(playerid), DateToTimestamp(PlayerInfo[targetid][pDrivingLicense], 1));
					SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
					format(string, MAXO_TEXT, "* You gave the driving license on %s valid untill %s.", PlayerName(targetid), DateToTimestamp(PlayerInfo[targetid][pDrivingLicense], 1));
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
				}
				else if(!strcmp(params, "flying", true)) {
					PlayerInfo[targetid][pFlyingLicense] = gettime()+ExpiraLicenta;
					format(string, MAXO_TEXT, "UPDATE players SET FlyingLicense = %d WHERE ID = %d", PlayerInfo[targetid][pFlyingLicense], PlayerInfo[targetid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					format(string, MAXO_TEXT, "* Admin %s has give you the flying license valid untill %s.", PlayerName(playerid), DateToTimestamp(PlayerInfo[targetid][pFlyingLicense], 1));
					SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
					format(string, MAXO_TEXT, "* You gave the flying license on %s valid untill %s.", PlayerName(targetid), DateToTimestamp(PlayerInfo[targetid][pFlyingLicense], 1));
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
				}
				else if(!strcmp(params, "sailing", true)) {
					PlayerInfo[targetid][pSailingLicense] = gettime()+ExpiraLicenta;
					format(string, MAXO_TEXT, "UPDATE players SET SailingLicense = %d WHERE ID = %d", PlayerInfo[targetid][pSailingLicense], PlayerInfo[targetid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					format(string, MAXO_TEXT, "* Admin %s has give you the sailing license valid untill %s.", PlayerName(playerid), DateToTimestamp(PlayerInfo[targetid][pSailingLicense], 1));
					SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
					format(string, MAXO_TEXT, "* You gave the sailing license on %s valid untill %s.", PlayerName(targetid), DateToTimestamp(PlayerInfo[targetid][pSailingLicense], 1));
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
					PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
				}
				clear.string(string);
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/givelicense [playerid/PartOfName] [license]"), SendClientMessage(playerid, COLOR_GRAD1, "Available License: driving | flying | sailing");
	} else NotAuthorized();
	return true;
}

function CheckPlayerActivity(playerid) {
	cache_get_data(rows, fields);
	if(rows) {
		new
			string[MAXO_TEXT], pSQL, pName[MAX_PLAYER_NAME+1], pLoginDate[MAX_PLAYER_NAME+1], pFaction, prank;
		pSQL = cache_get_row_int(0, 0);
		cache_get_row(0, 1, pName, .max_len = MAX_PLAYER_NAME+1);
		cache_get_row(0, 10, pLoginDate, .max_len = MAX_PLAYER_NAME+1);
		pFaction = cache_get_row_int(0, 16);
		prank = cache_get_row_int(0, 17);
		format(string, MAXO_TEXT, "* Name: %s(SQLID: %d)\n* Faction: %d\n* Rank: %d\n* Last login date: %s.", pName, pSQL, pFaction, prank, pLoginDate);
		ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Information about player", string, "Ok", "");
		clear.string(string);
	} else SendClientMessage(playerid, COLOR_GRAD1, "This player don't exist in table with players.");
	return true;
}

COMMAND:gotopos(playerid, params[]) {
	new
		Float:pPos[3];
	if(PlayerInfo[playerid][pAdmin] > 1) {
		if(!sscanf(params, "p<,>fff", pPos[0], pPos[1], pPos[2])) {
			if(IsPlayerInAnyVehicle(playerid)) SetVehiclePos(GetPlayerVehicleID(playerid), pPos[0], pPos[1], pPos[2]);
			else if(!IsPlayerInAnyVehicle(playerid)) SafeSetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/gotopos [X] [Y] [Z]");
	} else NotAuthorized();
	return true;
}

COMMAND:getcar(playerid, params[]) {
	new
		vID, Float:pPos[3], string[MAXO_TEXT];
	if(PlayerInfo[playerid][pAdmin] > 1) {
		if(!sscanf(params, "d", vID)) {
			if(ISBetween(vID, 1, MAX_VEHICLES)) {
				GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
				SetVehiclePos(vID, pPos[0], pPos[1]+0.4, pPos[2]);
				SetVehicleVirtualWorld(vID, GetPlayerVirtualWorld(playerid));
				LinkVehicleToInterior(vID, GetPlayerInterior(playerid));
				format(string, MAXO_TEXT, "* You have teleported car sqlid %d to you.", vID);
				SendClientMessage(playerid, COLOR_GREY, string);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid vehicle id.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/getcar [car id]");
	} else NotAuthorized();
	return true;
}

COMMAND:updatecarposition(playerid, params[]) {
	new
		string[MAXO_TEXT2], vID = GetPlayerVehicleID(playerid), Float:pPos[4];
	if(IsPlayerFounder(playerid)) {
		if(IsPlayerInAnyVehicle(playerid)) {
			GetVehiclePos(CarInfo[vID][cSQLID], pPos[0], pPos[1], pPos[2]);
			GetVehicleZAngle(CarInfo[vID][cSQLID], pPos[3]);
			format(string, MAXO_TEXT, "UPDATE vehicles SET LocationX = %f, LocationY = %f, LocationZ = %f, Angle = %f WHERE ID = %d", pPos[0], pPos[1], pPos[2], pPos[3], CarInfo[vID][cSQLID]);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", VEHICLE_THREAD_ID);
			if(vID != INVALID_VEHICLE_ID) {
				CarInfo[vID][cLocation][0] = pPos[0];
				CarInfo[vID][cLocation][1] = pPos[1];
				CarInfo[vID][cLocation][2] = pPos[2];
				CarInfo[vID][cAngle] = pPos[3];
				SendClientMessage(playerid, COLOR_GREY, "* This vehicle was been positioned here.");
				SetVehicleToRespawn(CarInfo[vID][cSQLID]);
			}
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in an vehicle to use this command.");
	} else NotAuthorized();
	return true;
}

COMMAND:updatecp(playerid, params[]) {
	return cmd_updatecarposition(playerid, params);
}

COMMAND:tmpinvite(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pLeader] > FACT_CIVIL) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(PlayerInfo[targetid][pFactiune] == FACT_CIVIL) {
						if(PlayerInfo[targetid][pWlvl] < 1) {
							new fID = PlayerInfo[playerid][pFactiune];
							new level = PlayerInfo[targetid][pLevel];

							if(level < FactionInfo[fID][fFactionLevel])
								return format(string, MAXO_TEXT, "This player can't be invited in your faction, doesn't have minimum level %d.", FactionInfo[fID][fFactionLevel]), SendClientMessage(playerid, COLOR_GRAD1, string);
							PlayerInfo[targetid][pFactiune] = PlayerInfo[playerid][pFactiune];
							PlayerInfo[targetid][pTeam] = PlayerInfo[playerid][pTeam];
							PlayerInfo[targetid][pRank] = 1;
							switch(PlayerInfo[targetid][pFactiune]) {
								case FACT_LSPD: PlayerInfo[targetid][pSkin] = 280, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
								case FACT_FBI: PlayerInfo[targetid][pSkin] = 285, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
								case FACT_MEDIC: PlayerInfo[targetid][pSkin] = 276, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
								case FACT_LCN: PlayerInfo[targetid][pSkin] = 258, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
								case FACT_YKZ: PlayerInfo[targetid][pSkin] = 59, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
								case FACT_HITMAN: PlayerInfo[targetid][pSkin] = 166, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
								case FACT_CNN: PlayerInfo[targetid][pSkin] = 187, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
								case FACT_TAXI: PlayerInfo[targetid][pSkin] = 253, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
								case FACT_BLOODS: PlayerInfo[targetid][pSkin] = 105, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
								case FACT_CRIPS: PlayerInfo[targetid][pSkin] = 28, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
							}
							SetPlayerFactionColor(targetid, PlayerInfo[targetid][pFactiune]);
							PlayerInfo[targetid][pFactionSpawn] = FACTIONSPAWN_PRIMARY;
							SetPlayerSpawnInfo(targetid);
							format(string, MAXO_TEXT, "* You have temporary invited in Faction '%s' by Leader %s.", FactionInfo[PlayerInfo[playerid][pFactiune]][fName], PlayerName(playerid));
							SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
							SendClientMessage(targetid, COLOR_LIGHTBLUE, "* If you pass the tests, you will be invited to faction.");
							format(string, MAXO_TEXT, "* You have invited temporary on %s in your faction.", PlayerName(targetid));
							SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
							clear.string(string);
						} else SendClientMessage(playerid, COLOR_GRAD1, "This player is wanted, cannot be invited in your faction.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player is already in a faction.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command on yourself.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/tmpinvite [playerid/PartOfName]");
	} else NotAuthorized();
	return true;
}

COMMAND:invite(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pLeader] > FACT_CIVIL) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(PlayerInfo[targetid][pFactiune] == FACT_CIVIL) {
						new fID = PlayerInfo[playerid][pFactiune];
						new level = PlayerInfo[targetid][pLevel];

						if(level < FactionInfo[fID][fFactionLevel])
							return format(string, MAXO_TEXT, "This player can't be invited in your faction, doesn't have minimum level %d.", FactionInfo[fID][fFactionLevel]), SendClientMessage(playerid, COLOR_GRAD1, string);
						PlayerInfo[targetid][pFactiune] = PlayerInfo[playerid][pFactiune];
						PlayerInfo[targetid][pTeam] = PlayerInfo[playerid][pTeam];
						PlayerInfo[targetid][pRank] = 1;
						SetPlayerFactionColor(targetid, PlayerInfo[targetid][pFactiune]);
						PlayerInfo[targetid][pFactionSpawn] = FACTIONSPAWN_PRIMARY;
						SetPlayerSpawnInfo(targetid);
						switch(PlayerInfo[targetid][pFactiune]) {
							case FACT_LSPD: PlayerInfo[targetid][pSkin] = 280, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
							case FACT_FBI: PlayerInfo[targetid][pSkin] = 285, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
							case FACT_MEDIC: PlayerInfo[targetid][pSkin] = 276, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
							case FACT_LCN: PlayerInfo[targetid][pSkin] = 258, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
							case FACT_YKZ: PlayerInfo[targetid][pSkin] = 59, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
							case FACT_HITMAN: PlayerInfo[targetid][pSkin] = 166, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
							case FACT_CNN: PlayerInfo[targetid][pSkin] = 187, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
							case FACT_TAXI: PlayerInfo[targetid][pSkin] = 253, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
							case FACT_BLOODS: PlayerInfo[targetid][pSkin] = 105, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
							case FACT_CRIPS: PlayerInfo[targetid][pSkin] = 28, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
						}
						format(string, MAXO_TEXT, "* You have invited in Faction '%s' by Leader %s.", FactionInfo[PlayerInfo[playerid][pFactiune]][fName], PlayerName(playerid));
						SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
						format(string, MAXO_TEXT, "* You have invited on %s in your faction.", PlayerName(targetid));
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						format(string, MAXO_TEXT2, "UPDATE players SET Faction = %d, Team = %d, Rank = %d, FactionSpawn = %d, Skin = %d WHERE ID = %d", PlayerInfo[targetid][pFactiune], PlayerInfo[targetid][pTeam], PlayerInfo[targetid][pRank], PlayerInfo[targetid][pFactionSpawn], PlayerInfo[targetid][pSkin], PlayerInfo[targetid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						new log[MAXO_TEXT2];
						format(log, MAXO_TEXT2, "%s a fost invitat in factiunea %s de catre Leaderul %s", PlayerName(targetid), FactionInfo[PlayerInfo[playerid][pFactiune]][fName], PlayerName(playerid));
						FactionsLog(targetid, log);
						clear.string(string);
						clear.string(log);
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player is already in a faction.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command on yourself.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/invite [playerid/PartOfName]");
	} else NotAuthorized();
	return true;
}

COMMAND:uninvite(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pLeader] > FACT_CIVIL) {
		if(!sscanf(params, "s[24]", PartialName[playerid][nume_introdus])) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(PlayerInfo[targetid][pFactiune] == PlayerInfo[playerid][pFactiune]) {
						PlayerInfo[targetid][pFactiune] = FACT_CIVIL;
						PlayerInfo[targetid][pTeam] = FACT_CIVIL;
						PlayerInfo[targetid][pRank] = 0;
						PlayerInfo[targetid][pFWarn] = 0;
						SetPlayerFactionColor(targetid, PlayerInfo[targetid][pFactiune]);
						SetPlayerSpawnInfo(targetid);
						PlayerInfo[targetid][pSkin] = 264;
						SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
						SpawnPlayer(targetid);
						format(string, MAXO_TEXT, "* You have been kicked from faction '%s' by Leader %s.", FactionInfo[PlayerInfo[playerid][pFactiune]][fName], PlayerName(playerid));
						SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
						SendClientMessage(targetid, COLOR_LIGHTBLUE, "* Now, you are again Civilian.");
						format(string, MAXO_TEXT, "* You have kicked on %s from your faction.", PlayerName(targetid));
						SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
						format(string, MAXO_TEXT2, "UPDATE players SET Faction = %d, Team = %d WHERE ID = %d", PlayerInfo[targetid][pFactiune], PlayerInfo[targetid][pTeam], PlayerInfo[targetid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						format(string, MAXO_TEXT2, "UPDATE players SET Rank = %d, Skin = %d, FWarn = %d WHERE ID = %d", PlayerInfo[targetid][pRank], PlayerInfo[targetid][pSkin], PlayerInfo[targetid][pFWarn], PlayerInfo[targetid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
						PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
						new log[MAXO_TEXT2];
						format(log, MAXO_TEXT2, "%s a fost demis din factiunea %s de catre Leaderul %s", PlayerName(targetid), FactionInfo[PlayerInfo[playerid][pFactiune]][fName], PlayerName(playerid));
						FactionsLog(targetid, log);
						clear.string(string);
						clear.string(log);
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is in your faction.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command on yourself.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/uninvite [playerid/PartOfName]");
	} else NotAuthorized();
	return true;
}

COMMAND:ouninvite(playerid, params[]) {
	new
		string[MAXO_TEXT], pName[MAX_PLAYER_NAME+1], pID;
	if(PlayerInfo[playerid][pAdmin] > 1 || PlayerInfo[playerid][pLeader] > FACT_CIVIL) {
		if(!sscanf(params, "s[25]", pName)) {
			if(!sscanf(params, "u", pID)) {
				if(pID == INVALID_PLAYER_ID) {
					format(string, MAXO_TEXT, "SELECT * FROM players WHERE Name = '%s' LIMIT 1", pName);
					mysql_tquery(connectionHandle, string, "OfflineUninvitePlayer", "d", playerid);
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command, because he is connected.");
			} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/ouninvite [player name]");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/ouninvite [player name]");
	} else NotAuthorized();
	return true;
}

function OfflineUninvitePlayer(playerid) {
	cache_get_data(rows, fields);
	if(rows) {
		new
			string[MAXO_TEXT], pName[MAX_PLAYER_NAME+1], pFaction, Leader;
		cache_get_row(0, 1, pName, .max_len = MAX_PLAYER_NAME+1);
		Leader = cache_get_row_int(0, 15);
		pFaction = cache_get_row_int(0, 16);
		if(pFaction == PlayerInfo[playerid][pFactiune]) {
			if(Leader > 0)
				return SendClientMessage(playerid, COLOR_GRAD1, "This player is leader, you can not use this command on he.");
			format(string, 300, "UPDATE players SET Faction = 0, Team = 0, Rank = 0, Skin = 264, FWarn = 0 WHERE Name = '%s' LIMIT 1", pName);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
			format(string, MAXO_TEXT, "LeadCMD: You kicked (offline) on %s out of your faction.", pName);
			SendClientMessage(playerid, COLOR_LIGHTRED, string);
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is in your faction.");
	} else SendClientMessage(playerid, COLOR_GRAD1, "This player don't exist in table with players.");
	return true;
}

COMMAND:giverank(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid, level;
	if(PlayerInfo[playerid][pLeader] > FACT_CIVIL) {
		if(!sscanf(params, "s[24]d", PartialName[playerid][nume_introdus], level)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(ISBetween(level, 1, 6)) {
					if(PlayerInfo[targetid][pFactiune] == PlayerInfo[playerid][pFactiune]) {
						if(targetid != playerid) {
							SendClientMessage(targetid, COLOR_LIGHTBLUE, "Now, can you go at Binco, to change the skin available.");
							PlayerInfo[targetid][pRank] = level;
							format(string, MAXO_TEXT, "* You have been promoted as Rank Level %d by Leader %s.", level, PlayerName(playerid));
							SendClientMessage(targetid, COLOR_LIGHTBLUE, string);
							format(string, MAXO_TEXT, "* You promoted on %s with Rank Level %d.", PlayerName(targetid), level);
							SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
							format(string, MAXO_TEXT, "UPDATE players SET Rank = %d WHERE ID = %d", PlayerInfo[targetid][pRank], PlayerInfo[targetid][pSQLID]);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
							new log[MAXO_TEXT2];
							format(log, MAXO_TEXT2, "%s a fost promovat cu Rank %d de catre Leaderul %s.", PlayerName(targetid), level, PlayerName(playerid));
							FactionsLog(targetid, log);
							clear.string(string);
							clear.string(log);
						} else SendClientMessage(playerid, COLOR_GRAD1, "You can't promote yourself in rank.");
					} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is in your faction.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "The rank level must be between 1-6.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/giverank [playerid/PartOfName] [rank level]");
	} else NotAuthorized();
	return true;
}

COMMAND:members(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pLeader] > FACT_CIVIL) {
		format(string, MAXO_TEXT, "SELECT * FROM players WHERE Faction = %d", PlayerInfo[playerid][pFactiune]);
		mysql_tquery(connectionHandle, string, "CheckMembersFaction", "d", playerid);
		clear.string(string);
	} else NotAuthorized();
	return true;
}

function CheckMembersFaction(playerid) {
	new
		string[MAXO_TEXT], pName[MAX_PLAYER_NAME], rank, LastLogin[MAX_PLAYER_NAME], fwarn;
	if(cache_num_rows()) {
		cache_get_row(0, 1, pName, .max_len = MAX_PLAYER_NAME);
		cache_get_row(0, 10, LastLogin, .max_len = MAX_PLAYER_NAME);
		rank = cache_get_row_int(0, 17);
		fwarn = cache_get_row_int(0, 44);
		format(string, 1024, "* Name member: %s | Rank Level: %d | Last Login Date: %s | FWarn: %d\n", pName, rank, LastLogin, fwarn);
		ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Information members", string, "Okay", "");
		clear.string(string);
	} else SendClientMessage(playerid, COLOR_GRAD1, "You don't have any member in your faction.");
	return true;
}

COMMAND:fwarn(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid;
	if(PlayerInfo[playerid][pLeader] > FACT_CIVIL) {
		if(!sscanf(params, "s[24]s[64]", PartialName[playerid][nume_introdus], params)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(targetid != playerid) {
					if(strlen(params) < 64) {
						if(PlayerInfo[targetid][pFactiune] == PlayerInfo[playerid][pFactiune]) {
							PlayerInfo[targetid][pFWarn] ++;
							format(string, MAXO_TEXT, "UPDATE players SET FWarn = %d WHERE ID = %d", PlayerInfo[targetid][pFWarn], PlayerInfo[targetid][pSQLID]);
							mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
							format(string, MAXO_TEXT, "LeadCMD: You have been warned by Leader %s, Reason: %s.", PlayerName(playerid), params);
							SendClientMessage(targetid, COLOR_LIGHTRED, string);
							format(string, MAXO_TEXT, "* You warned on %s, Reason: %s.", PlayerName(targetid), params);
							SendClientMessage(playerid, COLOR_LIGHTRED, string);
							new log[MAXO_TEXT2];
							format(log, MAXO_TEXT2, "%s was been warned by Leader %s, Reason: %s.", PlayerName(targetid), PlayerName(playerid), params);
							FactionsLog(targetid, log);
							if(PlayerInfo[targetid][pFWarn] > 2) {
								PlayerInfo[targetid][pFactiune] = FACT_CIVIL;
								PlayerInfo[targetid][pRank] = 0;
								PlayerInfo[targetid][pTeam] = FACT_CIVIL;
								PlayerInfo[targetid][pSkin] = 264;
								PlayerInfo[targetid][pFWarn] = 0;
								format(string, MAXO_TEXT2, "UPDATE players SET Faction = 0, Rank = 0, Team = 0, Skin = 264, FWarn = 0 WHERE ID = %d", PlayerInfo[targetid][pSQLID]);
								mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
                                SendClientMessage(targetid, COLOR_LIGHTBLUE, "* You have been fired because you acumulated 3 Faction Warn.");
                                SendClientMessage(targetid, COLOR_LIGHTBLUE, "* You are now a Civilian again.");
                                SendClientMessage(playerid, COLOR_YELLOW, "* Player fired with successful because of 3 Faction Warnings Points.");
								if(IsPlayerInInside(targetid))
									SafeResetPlayerInterior(targetid);
								if(GetPlayerVehicleID(targetid) != INVALID_VEHICLE_ID) {
									new Float:veh[3];
									GetVehiclePos(GetPlayerVehicleID(targetid), veh[0], veh[1], veh[2]);
									SafeSetPlayerPos(targetid, veh[0], veh[1], veh[2]);
								}
								SetPlayerSpawnInfo(targetid), SpawnPlayer(targetid);
								format(log, MAXO_TEXT2, "%s was fired from %s for the accumulation of 3 warnings.", PlayerName(targetid), FactionInfo[PlayerInfo[playerid][pFactiune]][fName]);
								FactionsLog(targetid, log);
							}
							PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
							clear.string(string);
							clear.string(log);
						} else SendClientMessage(playerid, COLOR_GRAD1, "This player not is from you faction.");
					} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "You can not use this command on youself.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/fwarn [playerid/PartOfName] [reason]");
	} else NotAuthorized();
	return true;
}

COMMAND:leaderchat(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(PlayerInfo[playerid][pLeader] > FACT_CIVIL) {
		if(!sscanf(params, "s[100]", params)) {
			if(strlen(params) < 100) {
				if(PlayerInfo[playerid][pMute])
					return IsPlayerSilent();
				format(string, MAXO_TEXT2, "(( * [%s] %s: %s * ))", FactionInfo[PlayerInfo[playerid][pFactiune]][fName], PlayerName(playerid), params);
				LBroadCast(COLOR_YELLOW, string);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/l(eader)c(hat) [message]");
	} else NotAuthorized();
	return true;
}

COMMAND:lc(playerid, params[]) {
	return cmd_leaderchat(playerid, params);
}

COMMAND:makeleader(playerid, params[]) {
	new
		string[MAXO_TEXT], targetid, fID;
	if(PlayerInfo[playerid][pAdmin] > 4) {
		if(!sscanf(params, "s[24]d", PartialName[playerid][nume_introdus], fID)) {
			CheckName(playerid, PartialName[playerid][nume_introdus]);
			targetid = PartialName[playerid][jucator_gasit];
			if(targetid != INVALID_PLAYER_ID) {
				if(ISBetween(fID, FACT_CIVIL, MAX_FACTIONS-1)) {
					if(PlayerInfo[targetid][pWlvl]) {
						PlayerInfo[targetid][pWlvl] = 0;
						SetPlayerWanted(targetid, INVALID_PLAYER_ID, 0);
						format(string, MAXO_TEXT, "UPDATE players SET Wanted = %d WHERE ID = %d", PlayerInfo[targetid][pWlvl], PlayerInfo[targetid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					}
					PlayerInfo[targetid][pLeader] = fID;
					PlayerInfo[targetid][pFactiune] = fID;
					if(fID == FACT_CIVIL) {
						PlayerInfo[targetid][pRank] = 0;
						PlayerInfo[targetid][pSkin] = 264;
						PlayerInfo[targetid][pFactionSpawn] = FACTIONSPAWN_PRIMARY;
						SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
						format(string, MAXO_TEXT2, "UPDATE players SET Skin = %d, FactionSpawn = %d WHERE ID = %d", PlayerInfo[targetid][pSkin], PlayerInfo[targetid][pFactionSpawn], PlayerInfo[targetid][pSQLID]);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					}
					else
						PlayerInfo[targetid][pRank] = 6;
					PlayerInfo[targetid][pTeam] = fID;
					SetPlayerFactionColor(targetid, PlayerInfo[targetid][pFactiune]);
					PlayerInfo[targetid][pFactionSpawn] = FACTIONSPAWN_PRIMARY;
					switch(PlayerInfo[targetid][pFactiune]) {
						case FACT_LSPD: PlayerInfo[targetid][pSkin] = 295, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
						case FACT_FBI: PlayerInfo[targetid][pSkin] = 286, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
						case FACT_MEDIC: PlayerInfo[targetid][pSkin] = 70, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
						case FACT_LCN: PlayerInfo[targetid][pSkin] = 127, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
						case FACT_YKZ: PlayerInfo[targetid][pSkin] = 120, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
						case FACT_HITMAN: PlayerInfo[targetid][pSkin] = 294, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
						case FACT_CNN: PlayerInfo[targetid][pSkin] = 227, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
						case FACT_TAXI: PlayerInfo[targetid][pSkin] = 61, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
						case FACT_BLOODS: PlayerInfo[targetid][pSkin] = 269, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
						case FACT_CRIPS: PlayerInfo[targetid][pSkin] = 271, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
						case FACT_FMA: PlayerInfo[targetid][pSkin] = 177, SetPlayerSkin(targetid, PlayerInfo[targetid][pSkin]);
					}
					format(string, MAXO_TEXT2, "UPDATE players SET Leader = %d, Faction = %d WHERE ID = %d", PlayerInfo[targetid][pLeader], PlayerInfo[targetid][pFactiune], PlayerInfo[targetid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					format(string, MAXO_TEXT2, "UPDATE players SET Rank = %d, Team = %d, Skin = %d WHERE ID = %d", PlayerInfo[targetid][pRank], PlayerInfo[targetid][pTeam], PlayerInfo[targetid][pSkin], PlayerInfo[targetid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					format(string, MAXO_TEXT, "UPDATE players SET FJoined = CURRENT_TIMESTAMP, FactionSpawn = %d WHERE ID = %d", PlayerInfo[targetid][pFactionSpawn], PlayerInfo[targetid][pSQLID]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", UPDATE_THREAD_ID);
					if(fID > FACT_CIVIL)
						format(string, MAXO_TEXT, "* You have been promoted as Leader in faction %s by Admin %s.", FactionInfo[fID][fName], PlayerName(playerid));
					else
						format(string, MAXO_TEXT, "* You have been kicked out from Leaders Team by Admin %s.", PlayerName(playerid)),
						SendClientMessage(targetid, COLOR_FAMILY, "* Now, you aren't member anymore in a faction, you are Civillian Person.");
					SendClientMessage(targetid, COLOR_FAMILY, string);
					if(fID > FACT_CIVIL)
						format(string, MAXO_TEXT, "* You promoted on %s as Leader in faction %s.", PlayerName(targetid), FactionInfo[fID][fName]);
					else
						format(string, MAXO_TEXT, "* You kicked out on %s from Leaders Team, now he are %s %s.", PlayerName(targetid), FactionInfo[fID][fName], FactionInfo[fID][fRank0]);
					SendClientMessage(playerid, COLOR_FAMILY, string);
					ResetPlayerWeapons(targetid);
					if(GetPlayerVehicleID(targetid) != INVALID_VEHICLE_ID) {
						new Float:veh[3];
						GetVehiclePos(GetPlayerVehicleID(targetid), veh[0], veh[1], veh[2]);
						SafeSetPlayerPos(targetid, veh[0], veh[1], veh[2]);
					}
					SetPlayerSpawnInfo(targetid);
					PartialName[playerid][jucator_gasit] = INVALID_PLAYER_ID;
					new log[MAXO_TEXT2];
					format(log, MAXO_TEXT2, "%s was been promoted as Leader at faction %s by %s", PlayerName(targetid), FactionInfo[fID][fName], PlayerName(playerid));
					FactionsLog(targetid, log);
					clear.string(string);
					clear.string(log);
				} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid faction.");
			}
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/makeleader [playerid/PartOfName] [faction ID]");
	} else NotAuthorized();
	return true;
}

COMMAND:createfaction(playerid, params[]) {
	new
		string[MAXO_TEXT];
	if(IsPlayerFounder(playerid)) {
		if(!sscanf(params, "s[30]", params)) {
			if(strlen(params) < 30) {
				format(string, MAXO_TEXT, "INSERT INTO factions (Name) VALUES ('%s')", params);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", FACTIONS_THREAD_ID);
				format(string, MAXO_TEXT, "AdmCmd: The faction %s was been created by Admin %s.", params, PlayerName(playerid));
				ABroadCast(COLOR_LIGHTRED, string, 1);
				format(string, MAXO_TEXT, "* You created the faction %s.", params);
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/createfaction [faction name]");
	} else NotAuthorized();
	return true;
}

COMMAND:cf(playerid, params[]) {
	return cmd_createfaction(playerid, params);
}

COMMAND:updatespawn(playerid, params[]) {
	new
		string[MAXO_TEXT], Float:pPos[4], fID;
	if(IsPlayerFounder(playerid)) {
		if(!sscanf(params, "d", fID)) {
			if(ISBetween(fID, FACT_CIVIL, MAX_FACTIONS)) {
				GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
				GetPlayerFacingAngle(playerid, pPos[3]);
				FactionInfo[fID][fSpawnx] = pPos[0];
				FactionInfo[fID][fSpawny] = pPos[1];
				FactionInfo[fID][fSpawnz] = pPos[2];
				FactionInfo[fID][fSpawnrot] = pPos[3];
				format(string, MAXO_TEXT, "UPDATE factions SET SpawnX = %f, SpawnY = %f, SpawnZ = %f, Rotation = %f WHERE ID = %d", FactionInfo[fID][fSpawnx], FactionInfo[fID][fSpawny], FactionInfo[fID][fSpawnz], FactionInfo[fID][fSpawnrot], FactionInfo[fID][fSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", FACTIONS_THREAD_ID);
				format(string, MAXO_TEXT, "AdmCmd: The spawn for faction %s, was beed changed by Admin %s.", FactionInfo[fID][fName], PlayerName(playerid));
				ABroadCast(COLOR_LIGHTRED, string, 1);
				format(string, MAXO_TEXT, "* You changed the spawn for faction %s.", FactionInfo[fID][fName]);
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid faction id.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/u(pdate)spawn [faction id]");
	} else NotAuthorized();
	return true;
}

COMMAND:uspawn(playerid, params[]) {
	return cmd_updatespawn(playerid, params);
}

COMMAND:updatespawn2(playerid, params[]) {
	new
		string[MAXO_TEXT], Float:pPos[4], fID;
	if(IsPlayerFounder(playerid)) {
		if(!sscanf(params, "d", fID)) {
			if(ISBetween(fID, FACT_CIVIL, MAX_FACTIONS)) {
				GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
				GetPlayerFacingAngle(playerid, pPos[3]);
				FactionInfo[fID][fSpawnx2] = pPos[0];
				FactionInfo[fID][fSpawny2] = pPos[1];
				FactionInfo[fID][fSpawnz2] = pPos[2];
				FactionInfo[fID][fSpawnrot2] = pPos[3];
				format(string, MAXO_TEXT, "UPDATE factions SET SpawnX2 = %f, SpawnY2 = %f, SpawnZ2 = %f, Rotation2 = %f WHERE ID = %d", FactionInfo[fID][fSpawnx2], FactionInfo[fID][fSpawny2], FactionInfo[fID][fSpawnz2], FactionInfo[fID][fSpawnrot2], FactionInfo[fID][fSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", FACTIONS_THREAD_ID);
				format(string, MAXO_TEXT, "AdmCmd: The spawn 2 for faction %s, was beed changed by Admin %s.", FactionInfo[fID][fName], PlayerName(playerid));
				ABroadCast(COLOR_LIGHTRED, string, 1);
				format(string, MAXO_TEXT, "* You changed the spawn secondary for faction %s.", FactionInfo[fID][fName]);
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid faction id.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/u(pdate)spawn2 [faction id]");
	} else NotAuthorized();
	return true;
}

COMMAND:uspawn2(playerid, params[]) {
	return cmd_updatespawn2(playerid, params);
}

COMMAND:updaterankname(playerid, params[]) {
	new
		string[MAXO_TEXT], fID, fRank;
	if(IsPlayerFounder(playerid)) {
		if(!sscanf(params, "dds[30]", fID, fRank, params)) {
			if(ISBetween(fID, FACT_LSPD, MAX_FACTIONS)) {
				if(ISBetween(fRank, 1, 6)) {
					if(strlen(params) < 30) {
						switch(fRank) {
							case 1: format(string, MAXO_TEXT, "UPDATE factions SET Rank1 = '%s' WHERE ID = %d", params, FactionInfo[fID][fSQLID]);
							case 2: format(string, MAXO_TEXT, "UPDATE factions SET Rank2 = '%s' WHERE ID = %d", params, FactionInfo[fID][fSQLID]);
							case 3: format(string, MAXO_TEXT, "UPDATE factions SET Rank3 = '%s' WHERE ID = %d", params, FactionInfo[fID][fSQLID]);
							case 4: format(string, MAXO_TEXT, "UPDATE factions SET Rank4 = '%s' WHERE ID = %d", params, FactionInfo[fID][fSQLID]);
							case 5: format(string, MAXO_TEXT, "UPDATE factions SET Rank5 = '%s' WHERE ID = %d", params, FactionInfo[fID][fSQLID]);
							case 6: format(string, MAXO_TEXT, "UPDATE factions SET Rank6 = '%s' WHERE ID = %d", params, FactionInfo[fID][fSQLID]);
						}
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", FACTIONS_THREAD_ID);
						format(string, MAXO_TEXT, "AdmCmd: The rank %d for faction %s was been changed by Admin %s.", fRank, FactionInfo[fID][fName], PlayerName(playerid));
						ABroadCast(COLOR_LIGHTRED, string, 1);
						format(string, MAXO_TEXT, "* You changed rank %d for faction %s.", fRank, FactionInfo[fID][fName]);
						SendClientMessage(playerid, COLOR_LIGHTRED, string);
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_YELLOW, "[AntiSpam] Line too long.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid rank id.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid faction id.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/updaterankname [faction id] [rank number] [name]");
	} else NotAuthorized();
	return true;
}

COMMAND:enterupdatehq(playerid, params[]) {
	new
		string[MAXO_TEXT], fID, Float:pPos[3];
	if(IsPlayerFounder(playerid)) {
		if(!sscanf(params, "d", fID)) {
			if(ISBetween(fID, FACT_LSPD, MAX_FACTIONS)) {
				GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
				FactionInfo[fID][fHQEnterx] = pPos[0];
				FactionInfo[fID][fHQEntery] = pPos[1];
				FactionInfo[fID][fHQEnterz] = pPos[2];
				#if defined _stream_pickups
					DestroyDynamicPickup(FactionInfo[fID][fPickupHQ]);
					FactionInfo[fID][fPickupHQ] = CreateDynamicPickup(FactionInfo[fID][fPickupModel], 23, FactionInfo[fID][fHQEnterx], FactionInfo[fID][fHQEntery], FactionInfo[fID][fHQEnterz]);
				#else
					DestroyPickup(FactionInfo[fID][fPickupHQ]);
					FactionInfo[fID][fPickupHQ] = CreatePickup(FactionInfo[fID][fPickupModel], 23, FactionInfo[fID][fHQEnterx], FactionInfo[fID][fHQEntery], FactionInfo[fID][fHQEnterz]);
				#endif
				format(string, MAXO_TEXT2, "UPDATE factions SET HQEnterX = %f, HQEnterY = %f, HQEnterZ = %f WHERE ID = %d", FactionInfo[fID][fHQEnterx], FactionInfo[fID][fHQEntery], FactionInfo[fID][fHQEnterz], FactionInfo[fID][fSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", FACTIONS_THREAD_ID);
				format(string, MAXO_TEXT, "AdmCmd: Admin %s has changed the enter in HQ for faction %s.", PlayerName(playerid), FactionInfo[fID][fName]);
				ABroadCast(COLOR_LIGHTRED, string, 1);
				format(string, MAXO_TEXT, "* You changed the enter in HQ for faction %s.", FactionInfo[fID][fName]);
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid faction ID.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/enterupdatehq [faction ID]");
	} else NotAuthorized();
	return true;
}

COMMAND:exitupdatehq(playerid, params[]) {
	new
		string[MAXO_TEXT], fID, Float:pPos[3], interior;
	if(IsPlayerFounder(playerid)) {
		if(!sscanf(params, "p<,>dfffd", fID, pPos[0], pPos[1], pPos[2], interior)) {
			if(ISBetween(fID, FACT_LSPD, MAX_FACTIONS)) {
				FactionInfo[fID][fHQExitx] = pPos[0];
				FactionInfo[fID][fHQExity] = pPos[1];
				FactionInfo[fID][fHQExitz] = pPos[2];
				FactionInfo[fID][fInterior] = interior;
				FactionInfo[fID][fVirtualWorld] = fID;
				format(string, MAXO_TEXT2, "UPDATE factions SET HQExitX = %f, HQExitY = %f, HQExitZ = %f WHERE ID = %d", FactionInfo[fID][fHQExitx], FactionInfo[fID][fHQExity], FactionInfo[fID][fHQExitz], FactionInfo[fID][fSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", FACTIONS_THREAD_ID);
				format(string, MAXO_TEXT2, "UPDATE factions SET Interior = %d, VirtualWorld = %d WHERE ID = %d", FactionInfo[fID][fInterior], FactionInfo[fID][fVirtualWorld], FactionInfo[fID][fSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", FACTIONS_THREAD_ID);
				format(string, MAXO_TEXT, "AdmCmd: Admin %s has changed the exit from HQ for faction %s.", PlayerName(playerid), FactionInfo[fID][fName]);
				ABroadCast(COLOR_LIGHTRED, string, 1);
				format(string, MAXO_TEXT, "* You changed the exit from HQ for faction %s.", FactionInfo[fID][fName]);
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid faction ID.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/exitupdatehq [faction ID] [ExitX] [ExitY] [ExitZ] [Interior]");
	} else NotAuthorized();
	return true;
}

COMMAND:enterupdatetr(playerid, params[]) {
	new
		string[MAXO_TEXT], fID, Float:pPos[3];
	if(IsPlayerFounder(playerid)) {
		if(!sscanf(params, "d", fID)) {
			if(ISBetween(fID, FACT_LSPD, MAX_FACTIONS)) {
				GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
				FactionInfo[fID][fTREnterx] = pPos[0];
				FactionInfo[fID][fTREntery] = pPos[1];
				FactionInfo[fID][fTREnterz] = pPos[2];
				#if defined _stream_pickups
					DestroyDynamicPickup(FactionInfo[fID][fPickupTR]);
					FactionInfo[fID][fPickupTR] = CreateDynamicPickup(FactionInfo[fID][fPickupModel], 23, FactionInfo[fID][fTREnterx], FactionInfo[fID][fTREntery], FactionInfo[fID][fTREnterz]);
				#else
					DestroyPickup(FactionInfo[fID][fPickupTR]);
					FactionInfo[fID][fPickupTR] = CreatePickup(FactionInfo[fID][fPickupModel], 23, FactionInfo[fID][fTREnterx], FactionInfo[fID][fTREntery], FactionInfo[fID][fTREnterz]);
				#endif
				format(string, MAXO_TEXT2, "UPDATE factions SET TREnterx = %f, TREntery = %f, TREnterz = %f WHERE ID = %d", FactionInfo[fID][fTREnterx], FactionInfo[fID][fTREntery], FactionInfo[fID][fTREnterz], FactionInfo[fID][fSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", FACTIONS_THREAD_ID);
				format(string, MAXO_TEXT, "AdmCmd: Admin %s has changed the enter in TR for faction %s.", PlayerName(playerid), FactionInfo[fID][fName]);
				ABroadCast(COLOR_LIGHTRED, string, 1);
				format(string, MAXO_TEXT, "* You changed the enter in TR for faction %s.", FactionInfo[fID][fName]);
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid faction ID.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/enterupdatetr [faction ID]");
	} else NotAuthorized();
	return true;
}

COMMAND:exitupdatetr(playerid, params[]) {
	new
		string[MAXO_TEXT], fID, Float:pPos[3], interior;
	if(IsPlayerFounder(playerid)) {
		if(!sscanf(params, "p<,>dfffd", fID, pPos[0], pPos[1], pPos[2], interior)) {
			if(ISBetween(fID, FACT_LSPD, MAX_FACTIONS)) {
				FactionInfo[fID][fTRExitx] = pPos[0];
				FactionInfo[fID][fTRExity] = pPos[1];
				FactionInfo[fID][fTRExitz] = pPos[2];
				FactionInfo[fID][fTRInterior] = interior;
				FactionInfo[fID][fVirtualWorld] = fID;
				format(string, MAXO_TEXT2, "UPDATE factions SET TRExitx = %f, TRExity = %f, TRExity = %f WHERE ID = %d", FactionInfo[fID][fHQExitx], FactionInfo[fID][fHQExity], FactionInfo[fID][fHQExitz], FactionInfo[fID][fSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", FACTIONS_THREAD_ID);
				format(string, MAXO_TEXT2, "UPDATE factions SET TRInterior = %d, VirtualWorld = %d WHERE ID = %d", FactionInfo[fID][fTRInterior], FactionInfo[fID][fVirtualWorld], FactionInfo[fID][fSQLID]);
				mysql_tquery(connectionHandle, string, "NoReturnThread", "d", FACTIONS_THREAD_ID);
				format(string, MAXO_TEXT, "AdmCmd: Admin %s has changed the exit from TR for faction %s.", PlayerName(playerid), FactionInfo[fID][fName]);
				ABroadCast(COLOR_LIGHTRED, string, 1);
				format(string, MAXO_TEXT, "* You changed the exit from TR for faction %s.", FactionInfo[fID][fName]);
				SendClientMessage(playerid, COLOR_LIGHTRED, string);
				clear.string(string);
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid faction ID.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/exitupdatetr [faction ID] [ExitX] [ExitY] [ExitZ] [Interior]");
	} else NotAuthorized();
	return true;
}

COMMAND:createsafe(playerid, params[]) {
	new
		string[MAXO_TEXT2], Float:pPos[3], fID, stype;
	if(IsPlayerFounder(playerid)) {
		if(!sscanf(params, "dd", fID, stype)) {
			if(ISBetween(fID, FACT_CIVIL, MAX_FACTIONS)) {
				if(ISBetween(stype, 0, 7)) {
					GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
					SafeInfo[fID][seifPos][0] = pPos[0];
					SafeInfo[fID][seifPos][1] = pPos[1];
					SafeInfo[fID][seifPos][2] = pPos[2];
					SafeInfo[fID][seifVW] = FactionInfo[fID][fVirtualWorld];
					SafeInfo[fID][seifType] = stype;
					#if defined _stream_pickups
						DestroyDynamicPickup(SafePickup);
						SafePickup = CreateDynamicPickup(1210, 23, SafeInfo[fID][seifPos][0], SafeInfo[fID][seifPos][1], SafeInfo[fID][seifPos][2], SafeInfo[fID][seifVW], FactionInfo[fID][fVirtualWorld], -1, 100.0);
					#else
						DestroyPickup(SafePickup);
						SafePickup = CreatePickup(1210, 23, SafeInfo[fID][seifPos][0], SafeInfo[fID][seifPos][1], SafeInfo[fID][seifPos][2], SafeInfo[fID][seifVW]);
					#endif
					format(string, sizeof(string), "INSERT INTO safes (PosX, PosY, PosZ, seifDrugs, seifMaterials, seifMoney, VirtualWorld, seifType) VALUES (%f, %f, %f, 0, 0, 0, %d, %d)", SafeInfo[fID][seifPos][0], SafeInfo[fID][seifPos][1], SafeInfo[fID][seifPos][2], SafeInfo[fID][seifVW], SafeInfo[fID][seifType]);
					mysql_tquery(connectionHandle, string, "NoReturnThread", "d", SAFE_THREAD_ID);
					format(string, sizeof(string), "AdmCmd: Admin %s has added an safe for faction %s.", PlayerName(playerid), FactionInfo[fID][fName]);
					ABroadCast(COLOR_LIGHTRED, string, 1);
					clear.string(string);
				} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid type.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid faction.");
		}
		else
		{
			SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/createsafe [faction] [type]");
			SendClientMessage(playerid, COLOR_GREY, "* 0 - Type None;");
			SendClientMessage(playerid, COLOR_GREY, "* 1 - Type Drugs;");
			SendClientMessage(playerid, COLOR_GREY, "* 2 - Type Materials;");
			SendClientMessage(playerid, COLOR_GREY, "* 3 - Type Money;");
			SendClientMessage(playerid, COLOR_GREY, "* 4 - Type Drugs & Materials;");
			SendClientMessage(playerid, COLOR_GREY, "* 5 - Type Drugs & Money;");
			SendClientMessage(playerid, COLOR_GREY, "* 6 - Type Materials & Money;");
			SendClientMessage(playerid, COLOR_GREY, "* 7 - Type All.");
		}
	} else NotAuthorized();
	return true;
}

COMMAND:updateexithouse(playerid, params[]) {
	new ID = PlayerInfo[playerid][pInHouseID], string[MAXO_TEXT];
	if(IsPlayerFounder(playerid)) {
		if(ID) {
			new Float:pPos[3];
			GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
			HouseInfo[ID][hExitx] = pPos[0];
			HouseInfo[ID][hExity] = pPos[1];
			HouseInfo[ID][hExitz] = pPos[2];
			format(string, MAXO_TEXT2, "UPDATE houses SET Exitx = %f, Exity = %f, Exitz = %f WHERE ID = %d", pPos[0], pPos[1], pPos[2], ID);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
			format(string, MAXO_TEXT, "AdmCmd: You changed the exit for the house SQLID %d.", ID);
			SendClientMessage(playerid, COLOR_LIGHTRED, string);
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in inside the house to use the command.");
	} else NotAuthorized();
	return true;
}

COMMAND:updatecpfromhouse(playerid, params[]) {
	new ID = PlayerInfo[playerid][pInHouseID], string[MAXO_TEXT];
	if(IsPlayerFounder(playerid)) {
		if(ID) {
			new Float:pPos[3];
			GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
			HouseInfo[ID][hCP][0] = pPos[0];
			HouseInfo[ID][hCP][1] = pPos[1];
			HouseInfo[ID][hCP][2] = pPos[2];
			DeleteCP(checkpointHouse, playerid);
			CreateCP(playerid,pPos[0], pPos[1], pPos[2],1.5,checkpointHouse,CP_HOUSE);
			format(string, MAXO_TEXT2, "UPDATE houses SET CPX = %f, CPY = %f, CPZ = %f WHERE ID = %d", pPos[0], pPos[1], pPos[2], ID);
			mysql_tquery(connectionHandle, string, "NoReturnThread", "d", HOUSE_THREAD_ID);
			format(string, MAXO_TEXT, "AdmCmd: You changed the checkpoint from the house SQLID %d.", ID);
			SendClientMessage(playerid, COLOR_LIGHTRED, string);
			clear.string(string);
		} else SendClientMessage(playerid, COLOR_GRAD1, "You must be in inside the house to use the command.");
	} else NotAuthorized();
	return true;
}

COMMAND:propertywipe(playerid, params[]) {
	new string[MAXO_TEXT], property_nr;
	if(IsPlayerFounder(playerid)) {
		if(!sscanf(params, "d", property_nr)) {
			switch(property_nr) {
				case 1: { // business
					for(new i; i < sizeof(BizInfo); i ++) {
						BizInfo[i][bTakings] = 0;
						strmid(BizInfo[i][bOwner], "The_State", 0, strlen("The_State"), 255);
						BizInfo[i][bEnterPrice] = 1;
						BizInfo[i][bProducts] = 100;
						BizInfo[i][bOwned] = 0;
						format(PropertyString, MAXO_TEXT2, "This biz is available to buy!\nOwner: %s\nLevel: %d, Price: $%s\nDescription: %s\nTo buy /buybiz", BizInfo[i][bOwner], BizInfo[i][bLevel], FormatNumber(BizInfo[i][bPrice], 0, '.'), BizInfo[i][bDescription]);
						Update3DTextLabelText(BizInfo[i][bLabel], COLOR_PROPERTY_NONE, PropertyString);
						format(string, MAXO_TEXT2, "UPDATE `bizz` SET `Takings` = '%d', `Owner` = '%s', `EnterPrice` = '%d', `Products` = '%d', `Owned` = '%d' WHERE `ID` = '%d'",
						BizInfo[i][bTakings], // resetam banii
						BizInfo[i][bOwner], // resetam proprietarul
						BizInfo[i][bEnterPrice], // resetam banii de la intrarea in business
						BizInfo[i][bProducts], // resetam numarul de produse
						BizInfo[i][bOwned], // resetam variabila care verifica daca business-ul este sau nu, detinut
						BizInfo[i][bSQLID]); // dupa ordinea ID-urilor SQL
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", BIZ_THREAD_ID);
						mysql_tquery(connectionHandle, "UPDATE `players` SET `Pbizkey` = '0' WHERE `Pbizkey` != '0'", "NoReturnThread", "d", UPDATE_THREAD_ID);
					}
					format(string, MAXO_TEXT, "AdmCmd: All business has been wiped by %s.", PlayerName(playerid));
					ABroadCast(COLOR_LIGHTRED, string, 1);
					foreach(Player, x) {
						PlayerInfo[x][pPhousekey] = 0;
						SendClientMessage(x, COLOR_LIGHTRED, "* You don't have a business anymore.");
					}
				}
				case 2: { // houses
					for(new h; h < sizeof(HouseInfo); h ++) {
						strmid(HouseInfo[h][hOwner], "The_State", 0, strlen("The_State"), 255);
						HouseInfo[h][hOwned] = 0;
						HouseInfo[h][hLocked] = 1;
						HouseInfo[h][hRentable] = 1;
						HouseInfo[h][hTakings] = 0;
						HouseInfo[h][hRentPrice] = 1;
						HouseInfo[h][hHeal] = 0;
						HouseInfo[h][hArmour] = 0;
						DestroyPickup(HouseInfo[h][hPickup]);
						HouseInfo[h][hPickup] = CreatePickup(1273, 23, HouseInfo[h][hEntrancex], HouseInfo[h][hEntrancey], HouseInfo[h][hEntrancez],-1);
						format(PropertyString, MAXO_TEXT2, "This house is available to buy!\nOwner: %s\nLevel: %d, Price: $%s\nDescription: %s\nTo buy /buyhouse", HouseInfo[h][hOwner], HouseInfo[h][hLevel], FormatNumber(HouseInfo[h][hPrice], 0, '.'), HouseInfo[h][hDescription]);
						Update3DTextLabelText(HouseInfo[h][hLabel], COLOR_PROPERTY_NONE, PropertyString);
						SalveazaCasele(h);
						mysql_tquery(connectionHandle, "UPDATE `players` SET `Phousekey` = '0' WHERE `Phousekey` != '0'", "NoReturnThread", "d", UPDATE_THREAD_ID);
					}
					format(string, MAXO_TEXT, "AdmCmd: All houses has been wiped by %s.", PlayerName(playerid));
					ABroadCast(COLOR_LIGHTRED, string, 1);
					foreach(Player, px) {
						PlayerInfo[px][pPhousekey] = 0;
						SendClientMessage(px, COLOR_LIGHTRED, "* You don't have a house anymore.");
					}
				}
				default: return SendClientMessage(playerid, COLOR_GRAD1, "Invalid option.");
			}
			clear.string(string);
			clear.string(PropertyString);
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/propertywipe [1 - business / 2 - houses]");
	} else NotAuthorized();
	return true;
}

COMMAND:gettickrateserver(playerid, params[]) {
	new string[MAXO_TEXT];
	if(!IsPlayerFounder(playerid))
		return NotAuthorized();
	format(string, MAXO_TEXT, "SERVER: The current server tick rate is: "ALB"%i", GetServerTickRate());
	SendClientMessage(playerid, COLOR_LIGHTRED, string);
    new stats[401];
    GetNetworkStats(stats, sizeof(stats)); 
    ShowPlayerDialog(playerid, DIALOGID_NO_ACTION, DIALOG_STYLE_MSGBOX, "Server Network Stats", stats, "Close", "");
	clear.string(string);
	clear.string(stats);
	return true;
}

// End Of File ...
