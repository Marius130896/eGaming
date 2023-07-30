/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro

*/
		
#if defined GF_GunsFunc_included
	#endinput
#else
	#define GF_GunsFunc_included
#endif

#define MAX_ARME 47
#define MAX_GUN_NAME 32
#define MAX_ARME 47

enum pretArm {
	nrArma,
	nrGloante,
	maxGloante,
	pretArma
};
new PretArmeInfo[MAX_ARME][pretArm];

new GunNames[51][MAX_PLAYER_NAME] = {
	"Nothing",
	"Brass knuckles",
	"Golf Club",
	"Nite stick",
	"Knife",
	"Baseball Bat",
	"Shovel",
	"Pool Cue",
	"Katana",
	"Chainsaw",
	"Purple Dildo",
	"Short Vibrator",
	"Long Vibrator",
	"White Vibrator",
	"Flowers",
	"Cane",
	"Grenades",
	"Tear Gas",
	"Molotov Cocktail",
	"Vehicle Missile",
	"Hydra Flare",
	"Jetpack",
	"9mm Pistol",
	"Silenced Pistol",
	"Desert Eagle",
	"Shotgun",
	"Sawn Off Shotgun",
	"Combat Shotgun",
	"Micro UZI",
	"MP5",
	"AK 47",
	"M4",
	"Tec 9",
	"Country Rifle",
	"Sniper Rifle",
	"Rpg",
	"HSRocketLauncher",
	"Flamethrower",
	"Mini gun",
	"Satchel Charges",
	"Detonator",
	"Spray Can",
	"Fire Extinguisher",
	"Camera",
	"Night vision",
	"Thermal goggles",
	"Parachute",
	"Fake Pistol",
	"Materials",
	"Cocaine",
	"Money"
};

#tryinclude <GF_functii/GF_private/GF_GunsFunc-private>

#if !defined GF_GunsFuncPriv_included
	stock GetWeaponNameEx(id, name[], len) return format(name, len, "%s", GunNames[id]);

	stock LoadProdsGuns() {
		return true;
	}
	function InitPrArmThread() {
		return true;
	}
	stock PlayerBuyWeapon(playerid, weaponID) {
		return true;
	}
#endif

// End Of File ...
