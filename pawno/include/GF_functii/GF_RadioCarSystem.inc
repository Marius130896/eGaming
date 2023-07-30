/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_RadioCarSystem_included
	#endinput
#else
	#define GF_RadioCarSystem_included
#endif

#define NONE_RADIO                      (-1)
#define RADIO_TARAF                     0
#define RADIO_HITZ                      1
#define RADIO_PROFM                     2
#define RADIO_BANDIT            	    3
#define RADIO_GREUDEDIFUZAT            	4
#define RADIO_FANPARAZITII            	5
#define RADIO_GANGSTAMANELE         	6
#define RADIO_INFERNO            	    7
#define RADIO_ROMANIAHIPHOP            	8
#define RADIO_HOTROMANIA            	9
#define RADIO_GANGSTADANCE            	10
#define RADIO_DUBSTEP            	    11
#define RADIO_CLUBMIXROMANIA            12
#define RADIO_TEQUILAHIPHOP             13

#define RADIO_TARAF_URL "http://live.radiotaraf.com:8181"
#define RADIO_HITZ_URL "http://7619.live.streamtheworld.com:80/977_HITS_SC"
#define RADIO_PROFM_URL "http://stream.profm.ro:8012/profm.mp3"
#define RADIO_BANDIT_URL "http://www.radiobandit.ro/radiobandit.pls"
#define RADIO_GREUDEDIFUZAT_URL "http://radio.voceastrazii.net:8012/;stream.mp3"
#define RADIO_FANPARAZITII_URL "http://86.105.88.167:8002/listen.pls"
#define RADIO_GANGSTAMANELE_URL "http://live.radiogangsta.ro:8800"
#define RADIO_INFERNO_URL "http://radioinferno-dance.no-ip.biz:7200"
#define RADIO_ROMANIAHIPHOP_URL "http://89.39.189.61:8400/listen.pls"
#define RADIO_HOTROMANIA_URL "http://live.radiohot.ro:8000/"
#define RADIO_GANGSTADANCE_URL "http://dance.radiogangsta.ro:8800"
#define RADIO_DUBSTEP_URL "http://dubstep.fm/128.pls"
#define RADIO_CLUBMIXROMANIA_URL "http://live.radioclubmix.ro:9999"
#define RADIO_TEQUILAHIPHOP_URL "http://www.radiotequila.ro/hiphop.m3u"

new
	RadioCars[MAX_VEHICLES];

stock StartCarRadio(vID, radio, type, playerid) {
	if(vID != INVALID_VEHICLE_ID) {
		switch(radio) {
			case RADIO_TARAF: {
				switch(type) {
					case 0:
					{
						RadioCars[vID] = RADIO_TARAF;
						foreach(Player, i)
						{
							if(GetPlayerVehicleID(i) == vID) {
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, RADIO_TARAF_URL);
								GameTextForPlayer(i, "~y~CAR RADIO ~g~ON", 1500, 1);
							}
						}
					}
					case 1:
					{
						PlayAudioStreamForPlayer(playerid, RADIO_TARAF_URL);
					}
				}
			}
			case RADIO_HITZ:
			{
				switch(type) {
					case 0:
					{
						RadioCars[vID] = RADIO_HITZ;
						foreach(Player, i) {
							if(GetPlayerVehicleID(i) == vID) {
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, RADIO_HITZ_URL);
								GameTextForPlayer(i, "~y~CAR RADIO ~g~ON", 1500, 1);
							}
						}
					}
					case 1:
					{
						PlayAudioStreamForPlayer(playerid, RADIO_HITZ_URL);
					}
				}
			}
			case RADIO_PROFM:
			{
				switch(type) {
					case 0:
					{
						RadioCars[vID] = RADIO_PROFM;
						foreach(Player, i) {
							if(GetPlayerVehicleID(i) == vID) {
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, RADIO_PROFM_URL);
								GameTextForPlayer(i, "~y~CAR RADIO ~g~ON", 1500, 1);
							}
						}
					}
					case 1:
					{
						PlayAudioStreamForPlayer(playerid, RADIO_PROFM_URL);
					}
				}
			}
			case RADIO_BANDIT:
			{
				switch(type) {
					case 0:
					{
						RadioCars[vID] = RADIO_BANDIT;
						foreach(Player, i) {
							if(GetPlayerVehicleID(i) == vID) {
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, RADIO_BANDIT_URL);
								GameTextForPlayer(i, "~y~CAR RADIO ~g~ON", 1500, 1);
							}
						}
					}
					case 1:
					{
						PlayAudioStreamForPlayer(playerid, RADIO_BANDIT_URL);
					}
				}
			}
			case RADIO_GREUDEDIFUZAT:
			{
				switch(type) {
					case 0:
					{
						RadioCars[vID] = RADIO_GREUDEDIFUZAT;
						foreach(Player, i) {
							if(GetPlayerVehicleID(i) == vID)
							{
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, RADIO_GREUDEDIFUZAT_URL);
								GameTextForPlayer(i, "~y~CAR RADIO ~g~ON", 1500, 1);
							}
						}
					}
					case 1:
					{
						PlayAudioStreamForPlayer(playerid, RADIO_GREUDEDIFUZAT_URL);
					}
				}
			}
			case RADIO_FANPARAZITII:
			{
				switch(type) {
					case 0:
					{
						RadioCars[vID] = RADIO_FANPARAZITII;
						foreach(Player, i) {
							if(GetPlayerVehicleID(i) == vID) {
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, RADIO_FANPARAZITII_URL);
								GameTextForPlayer(i, "~y~CAR RADIO ~g~ON", 1500, 1);
							}
						}
					}
					case 1:
					{
						PlayAudioStreamForPlayer(playerid, RADIO_FANPARAZITII_URL);
					}
				}
			}
			case RADIO_GANGSTAMANELE:
			{
				switch(type) {
					case 0:
					{
						RadioCars[vID] = RADIO_GANGSTAMANELE;
						foreach(Player, i) {
							if(GetPlayerVehicleID(i) == vID) {
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, RADIO_GANGSTAMANELE_URL);
								GameTextForPlayer(i, "~y~CAR RADIO ~g~ON", 1500, 1);
							}
						}
					}
					case 1:
					{
						PlayAudioStreamForPlayer(playerid, RADIO_GANGSTAMANELE_URL);
					}
				}
			}
			case RADIO_INFERNO:
			{
				switch(type) {
					case 0:
					{
						RadioCars[vID] = RADIO_INFERNO;
						foreach(Player, i) {
							if(GetPlayerVehicleID(i) == vID) {
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, RADIO_INFERNO_URL);
								GameTextForPlayer(i, "~y~CAR RADIO ~g~ON", 1500, 1);
							}
						}
					}
					case 1:
					{
						PlayAudioStreamForPlayer(playerid, RADIO_INFERNO_URL);
					}
				}
			}
			case RADIO_ROMANIAHIPHOP:
			{
				switch(type) {
					case 0:
					{
						RadioCars[vID] = RADIO_ROMANIAHIPHOP;
						foreach(Player, i) {
							if(GetPlayerVehicleID(i) == vID) {
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, RADIO_ROMANIAHIPHOP_URL);
								GameTextForPlayer(i, "~y~CAR RADIO ~g~ON", 1500, 1);
							}
						}
					}
					case 1:
					{
						PlayAudioStreamForPlayer(playerid, RADIO_ROMANIAHIPHOP_URL);
					}
				}
			}
			case RADIO_HOTROMANIA:
			{
				switch(type) {
					case 0:
					{
						RadioCars[vID] = RADIO_HOTROMANIA;
						foreach(Player, i) {
							if(GetPlayerVehicleID(i) == vID) {
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, RADIO_HOTROMANIA_URL);
								GameTextForPlayer(i, "~y~CAR RADIO ~g~ON", 1500, 1);
							}
						}
					}
					case 1:
					{
						PlayAudioStreamForPlayer(playerid, RADIO_HOTROMANIA_URL);
					}
				}
			}
			case RADIO_GANGSTADANCE:
			{
				switch(type) {
					case 0:
					{
						RadioCars[vID] = RADIO_GANGSTADANCE;
						foreach(Player, i) {
							if(GetPlayerVehicleID(i) == vID) {
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, RADIO_GANGSTADANCE_URL);
								GameTextForPlayer(i, "~y~CAR RADIO ~g~ON", 1500, 1);
							}
						}
					}
					case 1:
					{
						PlayAudioStreamForPlayer(playerid, RADIO_GANGSTADANCE_URL);
					}
				}
			}
			case RADIO_DUBSTEP:
			{
				switch(type) {
					case 0:
					{
						RadioCars[vID] = RADIO_DUBSTEP;
						foreach(Player, i) {
							if(GetPlayerVehicleID(i) == vID) {
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, RADIO_DUBSTEP_URL);
								GameTextForPlayer(i, "~y~CAR RADIO ~g~ON", 1500, 1);
							}
						}
					}
					case 1:
					{
						PlayAudioStreamForPlayer(playerid, RADIO_DUBSTEP_URL);
					}
				}
			}
			case RADIO_CLUBMIXROMANIA:
			{
				switch(type) {
					case 0:
					{
						RadioCars[vID] = RADIO_CLUBMIXROMANIA;
						foreach(Player, i) {
							if(GetPlayerVehicleID(i) == vID) {
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, RADIO_CLUBMIXROMANIA_URL);
								GameTextForPlayer(i, "~y~CAR RADIO ~g~ON", 1500, 1);
							}
						}
					}
					case 1:
					{
						PlayAudioStreamForPlayer(playerid, RADIO_CLUBMIXROMANIA_URL);
					}
				}
			}
			case RADIO_TEQUILAHIPHOP:
			{
				switch(type){
					case 0:
					{
						RadioCars[vID] = RADIO_TEQUILAHIPHOP;
						foreach(Player, i) {
							if(GetPlayerVehicleID(i) == vID) {
								StopAudioStreamForPlayer(i);
								PlayAudioStreamForPlayer(i, RADIO_TEQUILAHIPHOP_URL);
								GameTextForPlayer(i, "~y~CAR RADIO ~g~ON", 1500, 1);
							}
						}
					}
					case 1:
					{
						PlayAudioStreamForPlayer(playerid, RADIO_TEQUILAHIPHOP_URL);
					}
				}
			}
		}
	}
	return 1;
}

stock StopCarRadio(vID) {
	if(vID != INVALID_VEHICLE_ID) {
		RadioCars[vID] = NONE_RADIO;
		foreach(Player, i) {
			if(GetPlayerVehicleID(i) == vID) {
				StopAudioStreamForPlayer(i);
				GameTextForPlayer(i, "~y~CAR RADIO ~r~OFF", 1500, 1);
			}
		}
	}
	return 1;
}

COMMAND:carradio(playerid, params[])  {
	new
		vID = GetPlayerVehicleID(playerid);
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) {
		if(RadioCars[vID] == NONE_RADIO)
			ShowPlayerDialog(playerid, DIALOGID_CAR_RADIO, DIALOG_STYLE_LIST, "Radio List", "Taraf\nHitz Station\nPro FM\nBandit\nGreu de Difuzat\nFan Parazitii\nManele\nInferno\nRomania Hip-Hop\nHot Romania\nGangsta Dance\nDubstep FM\nClub Mix Romania\nTequila Romania Hip Hop", "Play", "Cancel");
		else
			StopCarRadio(vID);
	} else SendClientMessage(playerid, COLOR_GRAD1, "You must be the driver to use this command.");
	return true;
}

// End Of File ...
