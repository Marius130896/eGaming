/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_AnimationsComm_included
	#endinput
#else
	#define GF_AnimationsComm_included
#endif

#define SPECIAL_ACTION_PISSING 68

COMMAND:loop(playerid, params[]) {
	if(IsPlayerConnected(playerid)) {
		if(!IsPlayerInAnyVehicle(playerid)) {
			ApplyAnimation(playerid, "BD_FIRE", "BD_Panic_Loop", 4.0, 1, 0, 0, 0, 0, 1);
			TextDrawShowForPlayer(playerid, Animation);
		} else SendClientMessage(playerid, COLOR_WHITE, "You can't use anims while in a vehicle.");
	}
	return true;

}

COMMAND:luck(playerid, params[]) {
	if(IsPlayerConnected(playerid)) {
		if(!IsPlayerInAnyVehicle(playerid)) {
			ApplyAnimation(playerid, "GANGS", "prtial_hndshk_biz_01", 4.0, 0, 0, 0, 0, 0, 1);
			TextDrawShowForPlayer(playerid, Animation);
		} else SendClientMessage(playerid, COLOR_WHITE, "You can't use anims while in a vehicle");
	}
	return true;
}

COMMAND:fixin(playerid, params[]) {
	if(IsPlayerConnected(playerid)) {
		if(!IsPlayerInAnyVehicle(playerid)) {
			ApplyAnimation(playerid, "CAR", "Fixn_Car_Loop", 4.0, 1, 0, 0, 1, 0, 1);
			TextDrawShowForPlayer(playerid, Animation);
		} else SendClientMessage(playerid, COLOR_WHITE, "You can't use anims while in a vehicle");
	}
	return true;
}

COMMAND:fixout(playerid, params[]) {
	if(IsPlayerConnected(playerid)) {
		if(!IsPlayerInAnyVehicle(playerid)) {
			ApplyAnimation(playerid, "CAR", "Fixn_Car_Out", 4.0, 0, 0, 0,0, 0, 1);
			TextDrawShowForPlayer(playerid, Animation);
		} SendClientMessage(playerid, COLOR_WHITE, "You can't use anims while in a vehicle");
	}
	return true;
}

COMMAND:startrace(playerid, params[]) {
	if(IsPlayerConnected(playerid)) {
		if(!IsPlayerInAnyVehicle(playerid)) {
			ApplyAnimation(playerid,"CAR","flag_drop",4.0,0,0,0,0,0,1);
			TextDrawShowForPlayer(playerid, Animation);
		} else SendClientMessage(playerid, COLOR_WHITE, "You can't use anims while in a vehicle");
	}
	return true;
}

COMMAND:oyeah(playerid, params[]) {
	if(IsPlayerConnected(playerid)) {
		if(!IsPlayerInAnyVehicle(playerid)) {
			ApplyAnimation(playerid,"CLOTHES","CLO_Buy",4.0,1,0,0,0,0,1);
			TextDrawShowForPlayer(playerid, Animation);
		} else SendClientMessage(playerid, COLOR_WHITE, "You can't use anims while in a vehicle");
	}
	return true;
}

COMMAND:animlist(playerid, params[]) {
	SendClientMessage(playerid, COLOR_GREEN, "________________________________________");
	SendClientMessage(playerid, COLOR_WHITE,"** {F97804}USAGE:{B4B5B7} {FFFFFF}/stopani for stopped animation or press enter. **");
	SendClientMessage(playerid, -1,"** ANIMATIONS ** /getarrest, /chairsit, /chat, /crack /dance, /drunk, /injured, /carlock, /bomb, /laugh, /elbow");
	SendClientMessage(playerid, -1,"** ANIMATIONS ** /lay, /lay2, /smoke, /kiss, /wave, /excited, /taichi, /carjack, /vomit, /medic, /funnywalk,");
	SendClientMessage(playerid, -1,"** ANIMATIONS ** /kickass, /beach, /gro, /fallbak, /fall, /rap, /knife, /basket, /reload, /aim, /lean,");
	SendClientMessage(playerid, -1,"** ANIMATIONS ** /strip, /crossarms, /slapass, /fucku, /sup, /spray, /headbut, /push, /box, /dealstance, /hide,");
	SendClientMessage(playerid, -1,"** ANIMATIONS ** /carjacked1, /carjacked2, /rcarjack1, /rcarjack2, /lcarjack1, /rcarjack2, /exhaust, /leftslap,");
	SendClientMessage(playerid, -1,"** ANIMATIONS ** /airkick, /gkick, /highthrow, /lowthrow, /lightcig, /walk, /gwalk, /dealstance, /pee, /fakepee.");
	SendClientMessage(playerid, COLOR_GREEN, "________________________________________");
	return true;
}

COMMAND:stopani(playerid, params[]) {
	if(IsPlayerInAnyVehicle(playerid))
		return SendClientMessage(playerid, COLOR_GRAD1, "You can't use this command from inside a vehicle!");
	if(IsPlayerConnected(playerid)) {
		ClearAnimations(playerid);
		TextDrawHideForPlayer(playerid, Animation);
	}
	return true;
}

COMMAND:dealstance(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"DEALER","DEALER_IDLE",4.0,1,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:elbow(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"FIGHT_D","FightD_3",4.0,0,1,1,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:highthrow(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"GRENADE","WEAPON_throw",4.0,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:lowthrow(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"GRENADE","WEAPON_throwu",3.0,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:gkick(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"FIGHT_D","FightD_G",4.0,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:exhaust(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PED","IDLE_tired",3.0,1,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:carjacked1(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PED","CAR_jackedLHS",4.0,0,1,1,1,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:carjacked2(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PED","CAR_jackedRHS",4.0,0,1,1,1,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:hide(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid, "ped", "cower", 3.0, 1, 0, 0, 0, 0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:lcarjack1(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PED","CAR_pulloutL_RHS",4.0,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:lcarjack2(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PED","CAR_pullout_RHS",4.0,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:rcarjack1(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PED","CAR_pulloutL_LHS",4.0,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:rcarjack2(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PED","CAR_pullout_LHS",4.0,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:airkick(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"FIGHT_C","FightC_M",4.0,0,1,1,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:carjack2(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PED","CAR_pullout_LHS",4.0,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:carjack1(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PED","CAR_pulloutL_RHS",4.0,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:leftslap(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PED","BIKE_elbowL",4.0,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:spray(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"GANGS","shake_cara",4.0,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:box(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"GYMNASIUM","GYMshadowbox",4.0,1,1,1,1,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:headbut(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"WAYFARER","WF_Fwd",4.0,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:push(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"SPRAYCAN","spraycan_full",4.0,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:gro(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"BEACH", "ParkSit_M_loop", 4.0, 1, 0, 0, 0, 0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:fall(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PED","KO_skid_front",4.1,0,1,1,1,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:fallback(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid, "PED","FLOOR_hit_f", 4.0, 1, 0, 0, 0, 0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:carlock(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PED","CAR_doorlocked_LHS",4.0,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:lay2(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"SUNBATHE","Lay_Bac_in",3.0,0,1,1,1,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:medic(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"MEDIC","CPR",4.1,0,1,1,1,1);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:laugh(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid, "RAPPING", "Laugh_01", 4.0, 0, 0, 0, 0, 0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:beach(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"BEACH","SitnWait_loop_W",4.1,0,1,1,1,1);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:funnywalk(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"WUZI","Wuzi_Walk",4.1,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:kickass(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"FIGHT_E","Hit_fightkick",4.1,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:carjack(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PED","CAR_jackedLHS",4.0,0,1,1,1,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:vomit(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:taichi(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PARK","Tai_Chi_Loop",4.0,1,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:excited(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PAULNMAC", "wank_loop", 1.800001, 1, 0, 0, 1, 600);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:bomb(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 1, 0, 0, 0, 0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:robman(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid, "SHOP", "ROB_Loop_Threat", 4.0, 1, 0, 0, 0, 0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:chat(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PED","IDLE_CHAT",4.1,1,1,1,1,1);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:pee(playerid, params[]) {
	if (GetPlayerState(playerid) == 1) {
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_PISSING);
	}
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:fakepee(playerid, params[]) {
	ApplyAnimation(playerid, "PAULNMAC", "Piss_in", 3.0, 0, 0, 0, 0, 0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:kiss(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid, "KISSING", "Playa_Kiss_02", 3.0, 1, 0, 0, 0, 0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:wave(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid, "ON_LOOKERS", "wave_loop", 4.0, 1, 0, 0, 0, 0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:getarrest(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation( playerid,"ped", "ARRESTgun", 4.0, 1, 0, 0, 0, 0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:chairsit(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid, "PED", "SEAT_idle", 4.0999, 1, 0, 0, 0, 0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:drunk(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PED", "WALK_DRUNK",4.0,1,1,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:crack(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"CRACK", "crckdeth2",4.1,1,1,1,1,10000);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:handsup(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	SetPlayerSpecialAction(playerid,SPECIAL_ACTION_HANDSUP);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:injured(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid, "SWEET", "Sweet_injuredloop", 4.0, 1, 0, 0, 0, 0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:slapass(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid, "SWEET", "sweet_ass_slap", 4.0, 0, 0, 0, 0, 0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:fucku(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"PED","fucku",4.0,0,0,0,0,0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:crossarms(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid, "COP_AMBIENT", "Coplook_loop", 4.0, 0, 1, 1, 1, -1);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:lay(playerid, params[])  {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"BEACH", "bather", 4.0, 1, 0, 0, 0, 0);
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:rap(playerid, params[]) {
    if(GetPlayerState(playerid) != 1)
		return SendClientMessage(playerid, COLOR_GRAD1, "You can only use this animation while on foot.");
   	new animid;
   	if(sscanf(params,"d",animid))
		return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/rap [1-3]");
	switch(animid) {
  		case 1: ApplyAnimation(playerid, "RAPPING", "RAP_A_Loop", 4.0, 1, 0, 0, 0, 0);
    	case 2: ApplyAnimation(playerid, "RAPPING", "RAP_B_Loop", 4.0, 1, 0, 0, 0, 0);
     	case 3: ApplyAnimation(playerid, "RAPPING", "RAP_C_Loop", 4.0, 1, 0, 0, 0, 0);
      	default: SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/rap [1-3]");
   	}
   	TextDrawShowForPlayer(playerid, Animation);
   	return true;
}

COMMAND:knife(playerid, params[]) {
    if(GetPlayerState(playerid) != 1)
		return SendClientMessage(playerid, COLOR_GRAD1, "You can only use this animation while on foot.");
   	new animid;
   	if(sscanf(params,"d",animid))
		return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/knife [1-4]");
	switch(animid) {
  		case '1': ApplyAnimation(playerid,"KNIFE","KILL_Knife_Ped_Damage",4.0,0,1,1,1,0);
        case '2': ApplyAnimation(playerid,"KNIFE","KILL_Knife_Ped_Die",4.0,0,1,1,1,0);
        case '3': ApplyAnimation(playerid,"KNIFE","KILL_Knife_Player",4.0,0,0,0,0,0);
        case '4': ApplyAnimation(playerid,"KNIFE","KILL_Partial",4.0,0,1,1,1,1);
      	default: SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/knife [1-4]");
   	}
   	TextDrawShowForPlayer(playerid, Animation);
   	return true;
}

COMMAND:basket(playerid, params[]) {
    if(GetPlayerState(playerid) != 1)
		return SendClientMessage(playerid, COLOR_GRAD1, "You can only use this animation while on foot.");
   	new animid;
   	if(sscanf(params,"d",animid))
		return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/basket [1-6]");
	switch(animid) {
  		case '1': ApplyAnimation(playerid,"BSKTBALL","BBALL_idleloop",4.0,1,0,0,0,0);
        case '2': ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
        case '3': ApplyAnimation(playerid,"BSKTBALL","BBALL_pickup",4.0,0,0,0,0,0);
        case '4': ApplyAnimation(playerid,"BSKTBALL","BBALL_run",4.1,1,1,1,1,1);
        case '5': ApplyAnimation(playerid,"BSKTBALL","BBALL_def_loop",4.0,1,0,0,0,0);
        case '6': ApplyAnimation(playerid,"BSKTBALL","BBALL_Dnk",4.0,1,0,0,0,0);
      	default: SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/basket [1-6]");
   	}
   	TextDrawShowForPlayer(playerid, Animation);
   	return true;
}

COMMAND:aim(playerid, params[]) {
    if(GetPlayerState(playerid) != 1)
		return SendClientMessage(playerid, COLOR_GRAD1, "You can only use this animation while on foot.");
   	new animid;
   	if(sscanf(params,"d",animid))
		return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/aim [1-3]");
	switch(animid) {
  		case '1': ApplyAnimation(playerid,"PED","gang_gunstand",4.0,1,1,1,1,1);
        case '2': ApplyAnimation(playerid,"PED","Driveby_L",4.0,0,1,1,1,1);
        case '3': ApplyAnimation(playerid,"PED","Driveby_R",4.0,0,1,1,1,1);
      	default: SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/aim [1-3]");
   	}
   	TextDrawShowForPlayer(playerid, Animation);
   	return true;
}

COMMAND:lean(playerid, params[]) {
    if(GetPlayerState(playerid) != 1)
		return SendClientMessage(playerid, COLOR_GRAD1, "You can only use this animation while on foot.");
   	new animid;
   	if(sscanf(params,"d",animid))
		return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/lean [1-2]");
	switch(animid) {
  		case '1': ApplyAnimation(playerid,"GANGS","leanIDLE",4.0,0,1,1,1,0);
        case '2': ApplyAnimation(playerid,"MISC","Plyrlean_loop",4.0,0,1,1,1,0);
      	default: SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/lean [1-2]");
   	}
   	TextDrawShowForPlayer(playerid, Animation);
   	return true;
}

COMMAND:botdance(playerid, params[]) {
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { return true; }
	ApplyAnimation(playerid,"STRIP", "strip_A", 4.1, 1, 1, 1, 1, 1 );
	TextDrawShowForPlayer(playerid, Animation);
	return true;
}

COMMAND:sup(playerid, params[]) {
    if(GetPlayerState(playerid) != 1)
		return SendClientMessage(playerid, COLOR_GRAD1, "You can only use this animation while on foot.");
   	new animid;
   	if(sscanf(params,"d",animid))
		return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/sup [1-2]");
	switch(animid) {
  		case '1': ApplyAnimation(playerid,"GANGS","hndshkba",4.0,0,0,0,0,0);
        case '2': ApplyAnimation(playerid,"GANGS","hndshkda",4.0,0,0,0,0,0);
        case '3': ApplyAnimation(playerid,"GANGS","hndshkfa_swt",4.0,0,0,0,0,0);
      	default: SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/sup [1-2]");
   	}
   	TextDrawShowForPlayer(playerid, Animation);
   	return true;
}

COMMAND:smoke(playerid, params[]) {
    if(GetPlayerState(playerid) != 1)
		return SendClientMessage(playerid, COLOR_GRAD1, "You can only use this animation while on foot.");
   	new animid;
   	if(sscanf(params,"d",animid))
		return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/smoke [1-4]");
	switch(animid) {
  		case '1': ApplyAnimation(playerid,"SMOKING", "M_smklean_loop", 4.0, 1, 0, 0, 0, 0);
        case '2': ApplyAnimation(playerid,"SMOKING", "F_smklean_loop", 4.0, 1, 0, 0, 0, 0);
        case '3': ApplyAnimation(playerid,"SMOKING","M_smkstnd_loop", 4.0, 1, 0, 0, 0, 0);
        case '4': ApplyAnimation(playerid,"SMOKING","M_smk_out", 4.0, 1, 0, 0, 0, 0);
      	default: SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/smoke [1-4]");
   	}
   	TextDrawShowForPlayer(playerid, Animation);
   	return true;
}

COMMAND:strip(playerid, params[]) {
    if(GetPlayerState(playerid) != 1)
		return SendClientMessage(playerid, COLOR_GRAD1, "You can only use this animation while on foot.");
   	new animid;
   	if(sscanf(params,"d",animid))
		return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/strip [A-G]");
	switch(animid) {
  		case 'a', 'A': ApplyAnimation(playerid,"STRIP", "strip_A", 4.1, 1, 1, 1, 1, 1 );
        case 'b', 'B': ApplyAnimation(playerid,"STRIP", "strip_B", 4.1, 1, 1, 1, 1, 1 );
        case 'c', 'C': ApplyAnimation(playerid,"STRIP", "strip_C", 4.1, 1, 1, 1, 1, 1 );
        case 'd', 'D': ApplyAnimation(playerid,"STRIP", "strip_D", 4.1, 1, 1, 1, 1, 1 );
        case 'e', 'E': ApplyAnimation(playerid,"STRIP", "strip_E", 4.1, 1, 1, 1, 1, 1 );
        case 'f', 'F': ApplyAnimation(playerid,"STRIP", "strip_F", 4.1, 1, 1, 1, 1, 1 );
      	default: SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/strip [A-G]");
   	}
   	TextDrawShowForPlayer(playerid, Animation);
   	return true;
}

COMMAND:reload(playerid, params[]) {
    if(GetPlayerState(playerid) != 1)
		return SendClientMessage(playerid, COLOR_GRAD1, "You can only use this animation while on foot.");
    new animid;
   	if(sscanf(params,"d",animid))
		return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/reload - 1 (Desert Eagle), 2 (SPAS12), 3 (UZI/AK-47/M4A1)");
	switch(animid) {
		case 1: ApplyAnimation(playerid, "PYTHON", "python_reload", 4.0, 0, 0, 0, 0, 0);
  		case 2: ApplyAnimation(playerid, "BUDDY", "buddy_reload", 4.0, 0, 0, 0, 0, 0);
 		case 3: ApplyAnimation(playerid, "UZI", "UZI_reload", 4.0,0,0,0,0,0);
		default: SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/reload - 1 (Desert Eagle), 2 (SPAS12), 3 (UZI/AK-47/M4A1)");
 	}
 	return true;
}

COMMAND:dance(playerid, params[]) {
    if(GetPlayerState(playerid) != 1)
		return SendClientMessage(playerid, COLOR_GRAD1, "You can only use this animation while on foot.");
    new animid;
   	if(sscanf(params,"d",animid))
		return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/dance [1-4]");
	switch(animid) {
  		case 1: SetPlayerSpecialAction(playerid, 5);
	    case 2: SetPlayerSpecialAction(playerid, 6);
        case 3: SetPlayerSpecialAction(playerid, 7);
	    case 4: SetPlayerSpecialAction(playerid, 8);
  		default: SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/dance [1-4]");
	}
	TextDrawShowForPlayer(playerid, Animation);
 	return true;
}

COMMAND:walk(playerid, params[]) {
    if(GetPlayerState(playerid) != 1)
		return SendClientMessage(playerid, COLOR_GRAD1, "You can only use this animation while on foot.");
    new animid;
   	if(sscanf(params,"d",animid))
		return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/walk [1-14]");
	switch(animid) {
  		case 1: ApplyAnimation(playerid,"PED","WALK_gang1",4.1,1,1,1,1,1,1);
	    case 2: ApplyAnimation(playerid,"PED","WALK_gang2",4.1,1,1,1,1,1,1);
        case 3: ApplyAnimation(playerid,"FAT","FatWalk",4.1,1,1,1,1,1,1);
	    case 4: ApplyAnimation(playerid,"WUZI","CS_Wuzi_pt1",4.1,1,1,1,1,1,1);
	    case 5: ApplyAnimation(playerid,"WUZI","Wuzi_walk",3.0,1,1,1,1,1,1);
	    case 6: ApplyAnimation(playerid,"POOL","Pool_walk",3.0,1,1,1,1,1,1);
	    case 7: ApplyAnimation(playerid,"PED","Walk_player",3.0,1,1,1,1,1,1);
	    case 8: ApplyAnimation(playerid,"PED","Walk_old",3.0,1,1,1,1,1,1);
	    case 9: ApplyAnimation(playerid,"PED","Walk_fatold",3.0,1,1,1,1,1,1);
	    case 10: ApplyAnimation(playerid,"PED","woman_walkfatold",3.0,1,1,1,1,1,1);
	    case 11: ApplyAnimation(playerid,"PED","woman_walknorm",3.0,1,1,1,1,1,1);
	    case 12: ApplyAnimation(playerid,"PED","woman_walkold",3.0,1,1,1,1,1,1);
	    case 13: ApplyAnimation(playerid,"PED","woman_walkpro",3.0,1,1,1,1,1,1);
		case 14: ApplyAnimation(playerid,"PED","woman_walkshop",3.0,1,1,1,1,1,1);
  		default: SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/walk [1-14]");
	}
	TextDrawShowForPlayer(playerid, Animation);
 	return true;
}

COMMAND:gwalk(playerid, params[]) {
    if(GetPlayerState(playerid) != 1)
		return SendClientMessage(playerid, COLOR_GRAD1, "You can only use this animation while on foot.");
    new animid;
   	if(sscanf(params,"d",animid))
		return SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/gwalk [1/2]");
	switch(animid) {
  		case 1: ApplyAnimation(playerid,"PED","WALK_gang1",4.1,1,1,1,1,1);
	    case 2: ApplyAnimation(playerid,"PED","WALK_gang2",4.1,1,1,1,1,1);
  		default: SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/gwalk [1/2]");
	}
	TextDrawShowForPlayer(playerid, Animation);
 	return true;
}

// End Of File ...
