/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_FireMissionSystem_included
	#endinput
#else
	#define GF_FireMissionSystem_included
#endif

new
	FireObject[3] = {INVALID_OBJECT_ID, ...},
	NumarFoc,
	TimpIncendiu,
	FireCounter[MAX_PLAYERS char],
	NumarCase = 0;

#define OOBCheck(%0,%1)     (%0 < 0 || %0 >= sizeof %1)
#define PRESSED(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

#define MONEY_PART_1	(4500)
#define MONEY_PART_2	(5000)
#define MONEY_PART_3	(7000)
#define MONEY_PART_4	(7500)

strtok(const string[], &index) {
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' ')) {
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1))) {
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

stock ReturnUser(text[], playerid = INVALID_PLAYER_ID) {
    new pos = 0;
    while (text[pos] < 0x21) // Strip out leading spaces
    {
        if (text[pos] == 0) return INVALID_PLAYER_ID; // No passed text
        pos++;
    }
    new userid = INVALID_PLAYER_ID;
    if (isNumeric(text[pos])) // Check whole passed string
    {
        // If they have a numeric name you have a problem (although names are checked on id failure)
        userid = strval(text[pos]);
        if (userid >=0 && userid < MAX_PLAYERS)
        {
            if(!IsPlayerConnected(userid))
            {
                userid = INVALID_PLAYER_ID;
            }
            else
            {
                return userid; // A player was found
            }
        }
    }
    // They entered [part of] a name or the id search failed (check names just incase)
    new len = strlen(text[pos]);
    new count = 0;
    new name[MAX_PLAYER_NAME];
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i))
        {
            GetPlayerName(i, name, sizeof (name));
            if (strcmp(name, text[pos], true, len) == 0) // Check segment of name
            {
                if (len == strlen(name)) // Exact match
                {
                    return i; // Return the exact player on an exact match
                }
                else // Partial match
                {
                    count++;
                    userid = i;
                }
            }
        }
    }
    if (count != 1)
    {
        if (playerid != INVALID_PLAYER_ID)
        {
            if (count)
            {
                SendClientMessage(playerid, 0xFF0000AA, "Multiple users found, please narrow search.");
            }
            else
            {
                SendClientMessage(playerid, 0xFF0000AA, "No matching user found.");
            }
        }
        userid = INVALID_PLAYER_ID;
    }
    return userid; // INVALID_PLAYER_ID for bad return
}

stock Float:DistanceCameraTargetToLocation(Float:CamX, Float:CamY, Float:CamZ,   Float:ObjX, Float:ObjY, Float:ObjZ,   Float:FrX, Float:FrY, Float:FrZ) {

	new Float:TGTDistance;

	// aflarea distantei de la camera la tinta
	TGTDistance = floatsqroot((CamX - ObjX) * (CamX - ObjX) + (CamY - ObjY) * (CamY - ObjY) + (CamZ - ObjZ) * (CamZ - ObjZ));

	new Float:tmpX, Float:tmpY, Float:tmpZ;

	tmpX = FrX * TGTDistance + CamX;
	tmpY = FrY * TGTDistance + CamY;
	tmpZ = FrZ * TGTDistance + CamZ;

	return floatsqroot((tmpX - ObjX) * (tmpX - ObjX) + (tmpY - ObjY) * (tmpY - ObjY) + (tmpZ - ObjZ) * (tmpZ - ObjZ));
}


stock IsPlayerAimingAt(playerid, Float:x, Float:y, Float:z, Float:radius) {
	new Float:cx,Float:cy,Float:cz,Float:fx,Float:fy,Float:fz;
	GetPlayerCameraPos(playerid, cx, cy, cz);
	GetPlayerCameraFrontVector(playerid, fx, fy, fz);
	return (radius >= DistanceCameraTargetToLocation(cx, cy, cz, x, y, z, fx, fy, fz));
}

stock GenFireMission() {
	if(FireObject[0] == INVALID_OBJECT_ID && FireObject[1] == INVALID_OBJECT_ID && FireObject[2] == INVALID_OBJECT_ID) {
		NumarCase = RandomEx(1, MAX_HOUSES-1);
		if(!OOBCheck(NumarCase, HouseInfo)) {
			new string[MAXO_TEXT];
			NumarFoc = 3;
			#if defined _srv_test
			TimpIncendiu = 60;
			#else
			TimpIncendiu = 700;
			#endif
			FFCheck();
			format(string, MAXO_TEXT, "%s's house has started on fire. The location is show by a red marker on your map.", HouseInfo[NumarCase][hOwner]);
			foreach(Player, i) {
				if(PlayerInfo[i][pFactiune] == FACT_MEDIC) {
					SetPlayerMapIcon(i, MAPICON_FIREPLACE,  HouseInfo[NumarCase][hEntrancex], HouseInfo[NumarCase][hEntrancey], HouseInfo[NumarCase][hEntrancez], 20, 0, MAPICON_GLOBAL_CHECKPOINT);
					SendClientMessage(i, COLOR_GRAD1, string);
					SendClientMessage(i, COLOR_GRAD1, "Get into the fire vehicle and go extinguish the flames.");
				}
				if(PlayerInfo[i][pInHouseID] == NumarCase && PlayerInfo[i][pVirtualWorld] == 1000+NumarCase) {
					SetPlayerHealth(i, 0);
					SendClientMessage(i, COLOR_GRAD1, "You died because the house you were on, started on fire.");
				}
			}
			#if defined _stream_objects
			FireObject[0] = CreateDynamicObject(18715, HouseInfo[NumarCase][hEntrancex],   HouseInfo[NumarCase][hEntrancey],   HouseInfo[NumarCase][hEntrancez]-2.61, 0.0, 0.0, 0.0);
			FireObject[1] = CreateDynamicObject(18682, HouseInfo[NumarCase][hEntrancex],   HouseInfo[NumarCase][hEntrancey]+1, HouseInfo[NumarCase][hEntrancez]-2.61, 0.0, 0.0, 0.0);
			FireObject[2] = CreateDynamicObject(18691, HouseInfo[NumarCase][hEntrancex]+1, HouseInfo[NumarCase][hEntrancey],   HouseInfo[NumarCase][hEntrancez]-2.61, 0.0, 0.0, 0.0);
			#else
			FireObject[0] = CreateObject(18715, HouseInfo[NumarCase][hEntrancex],   HouseInfo[NumarCase][hEntrancey],   HouseInfo[NumarCase][hEntrancez]-2.61, 0.0, 0.0, 0.0);
			FireObject[1] = CreateObject(18682, HouseInfo[NumarCase][hEntrancex],   HouseInfo[NumarCase][hEntrancey]+1, HouseInfo[NumarCase][hEntrancez]-2.61, 0.0, 0.0, 0.0);
			FireObject[2] = CreateObject(18691, HouseInfo[NumarCase][hEntrancex]+1, HouseInfo[NumarCase][hEntrancey],   HouseInfo[NumarCase][hEntrancez]-2.61, 0.0, 0.0, 0.0);
			#endif
			clear.string(string);
		}
	}
	return true;
}

stock StopFireMission() return KillfireMission(INVALID_PLAYER_ID);

stock KillfireMission(player) {
	#if defined _stream_objects
	if(FireObject[0] != INVALID_OBJECT_ID) {
		DestroyDynamicObject(FireObject[0]);
		FireObject[0] = INVALID_OBJECT_ID;
	}
	if(FireObject[1] != INVALID_OBJECT_ID) {
		DestroyDynamicObject(FireObject[1]);
		FireObject[1] = INVALID_OBJECT_ID;
	}
	if(FireObject[2] != INVALID_OBJECT_ID) {
		DestroyDynamicObject(FireObject[2]);
		FireObject[2] = INVALID_OBJECT_ID;
	}
	#else
	if(FireObject[0] != INVALID_OBJECT_ID) {
		DestroyObject(FireObject[0]);
		FireObject[0] = INVALID_OBJECT_ID;
	}
	if(FireObject[1] != INVALID_OBJECT_ID) {
		DestroyObject(FireObject[1]);
		FireObject[1] = INVALID_OBJECT_ID;
	}
	if(FireObject[2] != INVALID_OBJECT_ID) {
		DestroyObject(FireObject[2]);
		FireObject[2] = INVALID_OBJECT_ID;
	}
	#endif
	NumarFoc = 0;
	TimpIncendiu = 0;
	new sql[MAXO_TEXT];
	if(player != INVALID_PLAYER_ID) {
		format(sql, sizeof(sql), "~r~%s's house saved by %s~w~", HouseInfo[NumarCase][hOwner], PlayerName(player));
	}
	foreach(Player, i) {
		if(PlayerInfo[i][pFactiune] == FACT_MEDIC) {
			RemovePlayerMapIcon(i, MAPICON_FIREPLACE);
			if(player != INVALID_PLAYER_ID) {
				SendClientMessage(i, COLOR_GRAD1,"Your department has confirmed that the fire is out.");
				SendClientMessage(i, COLOR_GRAD1,"Mission accomplished.");
				ShowPlayerInformation(i, "~w~Success!", sql);
			}
			else {
				SendClientMessage(i, COLOR_GRAD1, "You and your team failed to put out the fire.");
				HidePlayerInformation(i);
			}
		}
	}
	NumarCase = 0;
	clear.string(sql);
	return true;
}

function FFCheck() {
	if(TimpIncendiu) {
		if(TimpIncendiu == 1 && NumarFoc) return StopFireMission();
		SetTimer("FFCheck", 1000, 0);
		TimpIncendiu --;
		new tmp[100], tmp2[MAXO_TEXT1];
		foreach(Player, i) {
			if(PlayerInfo[i][pFactiune] == FACT_MEDIC) {
				format(tmp, sizeof(tmp), "~w~Remaining: ~b~%d~w~ Seconds", TimpIncendiu);
				format(tmp2, sizeof(tmp2), "~r~%s's house is on fire", HouseInfo[NumarCase][hOwner]);
				ShowPlayerInformation(i, tmp2, tmp);
				FireCounter{i} ++;
				if(FireCounter{i} == 3) {
					FireCounter{i} = 0;
					if(GetPlayerState(i) == PLAYER_STATE_DRIVER && GetVehicleModel(GetPlayerVehicleID(i)) == 407 || GetPlayerState(i) == PLAYER_STATE_ONFOOT && GetPlayerWeapon(i) == WEAPON_FIREEXTINGUISHER) {
						new newkeys, oldkeys, ud, lr;
						GetPlayerKeys(i, newkeys, ud, lr);
						if(PRESSED(KEY_FIRE)) {
							if(IsPlayerAimingAt(i, HouseInfo[NumarCase][hEntrancex], HouseInfo[NumarCase][hEntrancey], HouseInfo[NumarCase][hEntrancez], 5.0)) {
								switch(NumarFoc) {
									case 3: {
										#if defined _stream_objects
										DestroyDynamicObject(FireObject[0]);
										#else
										DestroyObject(FireObject[0]);
										#endif
										FireObject[0] = INVALID_OBJECT_ID;
										SendClientMessage(i,COLOR_GRAD1,"Fire is beginning to extinct.");
										format(tmp2, sizeof(tmp2), "~y~+~g~$~y~%s", FormatNumber( MONEY_PART_1, 0, ',' ));
										GameTextForPlayer(i, tmp2, 2000, 1);
										SafeGivePlayerMoney(i, MONEY_PART_1);
										NumarFoc --;
									}
									case 2: {
										#if defined _stream_objects
										DestroyDynamicObject(FireObject[1]);
										#else
										DestroyObject(FireObject[1]);
										#endif
										FireObject[1] = INVALID_OBJECT_ID;
										SendClientMessage(i,COLOR_GRAD1,"Fire is almost extinguished.");
										format(tmp2, sizeof(tmp2), "~y~+~g~$~y~%s", FormatNumber( MONEY_PART_2, 0, ',' ));
										GameTextForPlayer(i, tmp2, 2000, 1);
										SafeGivePlayerMoney(i, MONEY_PART_2);
										NumarFoc--;
									}
									case 1: {
										#if defined _stream_objects
										DestroyDynamicObject(FireObject[2]);
										#else
										DestroyObject(FireObject[2]);
										#endif
										FireObject[2] = INVALID_OBJECT_ID;
										SendClientMessage(i, COLOR_GRAD1,"Fire is slowly dying.");
										SafeGivePlayerMoney(i, MONEY_PART_3);
										format(tmp2, sizeof(tmp2), "~y~+~g~$~y~%s", FormatNumber( MONEY_PART_3, 0, ',' ));
										GameTextForPlayer(i, tmp2, 2000, 1);
										NumarFoc --;
									}
									case 0: {
										SafeGivePlayerMoney(i, MONEY_PART_4);
										format(tmp2, sizeof(tmp2), "~y~+~g~$~y~%s", FormatNumber( MONEY_PART_4, 0, ',' ));
										GameTextForPlayer(i, tmp2, 2000, 1);
										KillfireMission(i);
									}
								}
								ConsumingMoney[i] = 1;
							}
						}
					}
				}
			}
			else
				RemovePlayerMapIcon(i, MAPICON_FIREPLACE),
				HidePlayerInformation(i);
		}
		clear.string(tmp);
		clear.string(tmp2);
	}
	return true;
}

// End Of File ...
