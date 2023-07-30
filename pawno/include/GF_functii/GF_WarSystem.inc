/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/

#if defined GF_WarSystem_included
	#endinput
#else
	#define GF_WarSystem_included
#endif 

#define RivalWarsMoney 			25000		// premiu pentru cei ce cuceresc teritoriul
#define RivalWarsPMoney			10000 		// premiu pentru participantii la rival-war
#define RivalWarsKMoney			750			// premiu pentru cei ce omoara rivalii
#define RivalWarsDrugs			50			// premiu pentru cei ce cuceresc teritoriul
#define RivalWarsMaterials		15000		// premiu pentru cei ce cuceresc teritoriul

#define MIN_MEMBERS 			2			// numarul minim de membri pentru rival-war
#define DURATA_RIVALWAR 		60*6		// numarul de minute pentru un rival-war

#define WAR_PAUSE 				10*3		// numarul de secunde dintr-un war la altul
#define TURF_CMD_DELAY 			3600*3		// numarul de ore intre rival-waruri pe teritoriu
#define DURATA_WAR_SCORE_EGAL	60*3		// numarul de minute prelungite in caz ca iese scor egal
#define PAUSE_FOR_LAST_ATTACK 	3600*24		// numarul de ore de la ultimul atac al factiunii

#define COLOR_NODMZONE 0x00000096

#tryinclude <GF_functii/GF_private/GF_WarSystem-private>

#if !defined GF_WarSystemPriv_included
	stock StartRivalWarsBetweenPlayers(turfid, AtackTeam, DefendTeam) {
		return true;
	}
	stock GivePlayerAwardForWinRivalWars(AtackTeam, DefendTeam) {
		return true;
	}
	stock StopRivalWarsBetweenPlayers(turfid, AtackTeam, DefendTeam) {
		return true;
	}
#endif

stock IsAWarArea(zone) {
	if(zone != INVALID_TURF_ID) {
		switch(TurfInfo[zone][TurfOwner]) {
			case FACT_YKZ, FACT_LCN, FACT_BLOODS, FACT_CRIPS:
				return true;
		}
	}
	return false;
}

stock RivalFactions(playerid) {
	new inturf = GetPlayerTurfID(playerid), playerfactionID = PlayerInfo[playerid][pFactiune], zoneinfo = TurfInfo[inturf][TurfOwner];
	switch(playerfactionID)
	{
		case FACT_YKZ: if(zoneinfo == FACT_LCN) return 1;
		case FACT_LCN: if(zoneinfo == FACT_YKZ) return 1;
		case FACT_BLOODS: if(zoneinfo == FACT_CRIPS) return 1;
		case FACT_CRIPS: if(zoneinfo == FACT_BLOODS) return 1;
		default: return 0;
	}
	return 0;
}

// End Of File ...
