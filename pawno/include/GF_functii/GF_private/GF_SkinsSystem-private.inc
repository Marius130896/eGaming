/*

		(c) 2020 Kurama - for Gaming Community - www.gamingsite.ro
			   	   !! private code -- do not distribute !!
*/
			   	   
#if defined GF_SkinsSystem_included
	#endinput
#else
	#define GF_SkinsSystem_included
#endif

forward OnPlayerModelSelection(playerid, response, listid, modelid);
forward OnPlayerModelSelectionEx(playerid, response, extraid, modelid);

// settings static lists
#define mS_TOTAL_ITEMS         	1000 // Max amount of items from all lists
#define mS_TOTAL_LISTS			20 // Max amount of lists
#define mS_TOTAL_ROT_ZOOM		100 // Max amount of items using extra information like zoom or rotations

// settings dynamic per player lists
#define mS_CUSTOM_MAX_ITEMS		100
new gCustomList[MAX_PLAYERS][mS_CUSTOM_MAX_ITEMS];

#define mS_INVALID_LISTID		mS_TOTAL_LISTS
#define mS_CUSTOM_LISTID		(mS_TOTAL_LISTS+1)

#define mS_NEXT_TEXT   "Next"
#define mS_PREV_TEXT   "Prev"
#define mS_CANCEL_TEXT   "Cancel"

#define mS_SELECTION_ITEMS 		21
#define mS_ITEMS_PER_LINE  		7
#define mS_DIALOG_BASE_X   	75.0
#define mS_DIALOG_BASE_Y   	130.0
#define mS_DIALOG_WIDTH    	550.0
#define mS_DIALOG_HEIGHT   	180.0
#define mS_SPRITE_DIM_X    	60.0
#define mS_SPRITE_DIM_Y    	70.0

new
	PlayerText:gCurrentPageTextDrawId[MAX_PLAYERS]=PlayerText:INVALID_TEXT_DRAW,
	PlayerText:gHeaderTextDrawId[MAX_PLAYERS]=PlayerText:INVALID_TEXT_DRAW,
	PlayerText:gBackgroundTextDrawId[MAX_PLAYERS]=PlayerText:INVALID_TEXT_DRAW,
	PlayerText:gNextButtonTextDrawId[MAX_PLAYERS]=PlayerText:INVALID_TEXT_DRAW,
	PlayerText:gPrevButtonTextDrawId[MAX_PLAYERS]=PlayerText:INVALID_TEXT_DRAW,
	PlayerText:gCancelButtonTextDrawId[MAX_PLAYERS]=PlayerText:INVALID_TEXT_DRAW,
	PlayerText:gSelectionItems[MAX_PLAYERS][mS_SELECTION_ITEMS]={PlayerText:INVALID_TEXT_DRAW,...};

new
	gSelectionItemsTag[MAX_PLAYERS][mS_SELECTION_ITEMS],
	gItemAt[MAX_PLAYERS];

#define mS_LIST_START			0
#define mS_LIST_END				1
new gLists[mS_TOTAL_LISTS][2]; // list information start/end index

#define mS_ITEM_MODEL			0
#define mS_ITEM_ROT_ZOOM_ID 	1
new gItemList[mS_TOTAL_ITEMS][2];

new Float:gRotZoom[mS_TOTAL_ROT_ZOOM][4]; // Array for saving rotation and zoom info
//new gItemAmount = 0; // Amount of items used
//new gListAmount = 0; // Amount of lists used
//new gRotZoomAmount = 0; // Amount of Rotation/Zoom informations used

//------------------------------------------------

stock mS_GetNumberOfPages(ListID)
{
	new ItemAmount = mS_GetAmountOfListItems(ListID);
	if((ItemAmount >= mS_SELECTION_ITEMS) && (ItemAmount % mS_SELECTION_ITEMS) == 0)
		return (ItemAmount / mS_SELECTION_ITEMS);
	else return (ItemAmount / mS_SELECTION_ITEMS) + 1;
}

//------------------------------------------------

stock mS_GetNumberOfPagesEx(playerid)
{
	new ItemAmount = mS_GetAmountOfListItemsEx(playerid);
	if((ItemAmount >= mS_SELECTION_ITEMS) && (ItemAmount % mS_SELECTION_ITEMS) == 0)
		return (ItemAmount / mS_SELECTION_ITEMS);
	else return (ItemAmount / mS_SELECTION_ITEMS) + 1;
}

//------------------------------------------------

stock mS_GetAmountOfListItems(ListID)
	return (gLists[ListID][mS_LIST_END] - gLists[ListID][mS_LIST_START])+1;

//------------------------------------------------

stock mS_GetAmountOfListItemsEx(playerid)
	return GetPVarInt(playerid, "mS_custom_item_amount");

//------------------------------------------------

stock mS_GetPlayerCurrentListID(playerid)
{
	if(GetPVarInt(playerid, "mS_list_active") == 1) return GetPVarInt(playerid, "mS_list_id");
	else return mS_INVALID_LISTID;
}

//------------------------------------------------

stock PlayerText:mS_CreateCurrentPageTextDraw(playerid, Float:Xpos, Float:Ypos)
{
	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDraw(playerid, Xpos, Ypos, "0/0");
   	PlayerTextDrawUseBox(playerid, txtInit, 0);
	PlayerTextDrawLetterSize(playerid, txtInit, 0.4, 1.1);
	PlayerTextDrawFont(playerid, txtInit, 1);
	PlayerTextDrawSetShadow(playerid, txtInit, 0);
    PlayerTextDrawSetOutline(playerid, txtInit, 1);
    PlayerTextDrawColor(playerid, txtInit, 0xACCBF1FF);
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}

//------------------------------------------------
// Creates a button textdraw and returns the textdraw ID.

stock PlayerText:mS_CreatePlayerDialogButton(playerid, Float:Xpos, Float:Ypos, Float:Width, Float:Height, button_text[])
{
 	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDraw(playerid, Xpos, Ypos, button_text);
   	PlayerTextDrawUseBox(playerid, txtInit, 1);
   	PlayerTextDrawBoxColor(playerid, txtInit, 0x000000FF);
   	PlayerTextDrawBackgroundColor(playerid, txtInit, 0x000000FF);
	PlayerTextDrawLetterSize(playerid, txtInit, 0.4, 1.1);
	PlayerTextDrawFont(playerid, txtInit, 1);
	PlayerTextDrawSetShadow(playerid, txtInit, 0); // no shadow
    PlayerTextDrawSetOutline(playerid, txtInit, 0);
    PlayerTextDrawColor(playerid, txtInit, 0x4A5A6BFF);
    PlayerTextDrawSetSelectable(playerid, txtInit, 1);
    PlayerTextDrawAlignment(playerid, txtInit, 2);
    PlayerTextDrawTextSize(playerid, txtInit, Height, Width); // The width and height are reversed for centering.. something the game does <g>
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}

//------------------------------------------------

stock PlayerText:mS_CreatePlayerHeaderTextDraw(playerid, Float:Xpos, Float:Ypos, header_text[])
{
	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDraw(playerid, Xpos, Ypos, header_text);
   	PlayerTextDrawUseBox(playerid, txtInit, 0);
	PlayerTextDrawLetterSize(playerid, txtInit, 1.25, 3.0);
	PlayerTextDrawFont(playerid, txtInit, 3);
	PlayerTextDrawSetShadow(playerid, txtInit, 0);
    PlayerTextDrawSetOutline(playerid, txtInit, 1);
    PlayerTextDrawColor(playerid, txtInit, 0x804040FF);
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}

//------------------------------------------------

stock PlayerText:mS_CreatePlayerBGTextDraw(playerid, Float:Xpos, Float:Ypos, Float:Width, Float:Height, bgcolor)
{
	new PlayerText:txtBackground = CreatePlayerTextDraw(playerid, Xpos, Ypos,"                                            ~n~"); // enough space for everyone
    PlayerTextDrawUseBox(playerid, txtBackground, 1);
    PlayerTextDrawBoxColor(playerid, txtBackground, bgcolor);
	PlayerTextDrawLetterSize(playerid, txtBackground, 5.0, 5.0);
	PlayerTextDrawFont(playerid, txtBackground, 0);
	PlayerTextDrawSetShadow(playerid, txtBackground, 0);
    PlayerTextDrawSetOutline(playerid, txtBackground, 0);
    PlayerTextDrawColor(playerid, txtBackground,0x000000FF);
    PlayerTextDrawTextSize(playerid, txtBackground, Width, Height);
   	PlayerTextDrawBackgroundColor(playerid, txtBackground, bgcolor);
    PlayerTextDrawShow(playerid, txtBackground);
    return txtBackground;
}

//------------------------------------------------
// Creates a model preview sprite

stock PlayerText:mS_CreateMPTextDraw(playerid, modelindex, Float:Xpos, Float:Ypos, Float:Xrot, Float:Yrot, Float:Zrot, Float:mZoom, Float:width, Float:height, bgcolor)
{
    new PlayerText:txtPlayerSprite = CreatePlayerTextDraw(playerid, Xpos, Ypos, ""); // it has to be set with SetText later
    PlayerTextDrawFont(playerid, txtPlayerSprite, TEXT_DRAW_FONT_MODEL_PREVIEW);
    PlayerTextDrawColor(playerid, txtPlayerSprite, 0xFFFFFFFF);
    PlayerTextDrawBackgroundColor(playerid, txtPlayerSprite, bgcolor);
    PlayerTextDrawTextSize(playerid, txtPlayerSprite, width, height); // Text size is the Width:Height
    PlayerTextDrawSetPreviewModel(playerid, txtPlayerSprite, modelindex);
    PlayerTextDrawSetPreviewRot(playerid,txtPlayerSprite, Xrot, Yrot, Zrot, mZoom);
    PlayerTextDrawSetSelectable(playerid, txtPlayerSprite, 1);
    PlayerTextDrawShow(playerid,txtPlayerSprite);
    return txtPlayerSprite;
}

//------------------------------------------------

stock mS_DestroyPlayerMPs(playerid)
{
	new x;
	while(x != mS_SELECTION_ITEMS) {
	    if(gSelectionItems[playerid][x] != PlayerText:INVALID_TEXT_DRAW) {
			PlayerTextDrawDestroy(playerid, gSelectionItems[playerid][x]);
			gSelectionItems[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
		}
		x++;
	}
}

//------------------------------------------------

stock mS_ShowPlayerMPs(playerid)
{
	new bgcolor = GetPVarInt(playerid, "mS_previewBGcolor");
    new x;
	new Float:BaseX = mS_DIALOG_BASE_X;
	new Float:BaseY = mS_DIALOG_BASE_Y - (mS_SPRITE_DIM_Y * 0.33); // down a bit
	new linetracker;

	new mS_listID = mS_GetPlayerCurrentListID(playerid);
	if(mS_listID == mS_CUSTOM_LISTID)
	{
		new itemat = (GetPVarInt(playerid, "mS_list_page") * mS_SELECTION_ITEMS);
		new Float:rotzoom[4];
		rotzoom[0] = GetPVarFloat(playerid, "mS_custom_Xrot");
		rotzoom[1] = GetPVarFloat(playerid, "mS_custom_Yrot");
		rotzoom[2] = GetPVarFloat(playerid, "mS_custom_Zrot");
		rotzoom[3] = GetPVarFloat(playerid, "mS_custom_Zoom");
		new itemamount = mS_GetAmountOfListItemsEx(playerid);
		// Destroy any previous ones created
		mS_DestroyPlayerMPs(playerid);

		while(x != mS_SELECTION_ITEMS && itemat < (itemamount)) {
			if(linetracker == 0) {
				BaseX = mS_DIALOG_BASE_X + 25.0; // in a bit from the box
				BaseY += mS_SPRITE_DIM_Y + 1.0; // move on the Y for the next line
			}
			gSelectionItems[playerid][x] = mS_CreateMPTextDraw(playerid, gCustomList[playerid][itemat], BaseX, BaseY, rotzoom[0], rotzoom[1], rotzoom[2], rotzoom[3], mS_SPRITE_DIM_X, mS_SPRITE_DIM_Y, bgcolor);
			gSelectionItemsTag[playerid][x] = gCustomList[playerid][itemat];
			BaseX += mS_SPRITE_DIM_X + 1.0; // move on the X for the next sprite
			linetracker++;
			if(linetracker == mS_ITEMS_PER_LINE) linetracker = 0;
			itemat++;
			x++;
		}
	}
	else
	{
		new itemat = (gLists[mS_listID][mS_LIST_START] + (GetPVarInt(playerid, "mS_list_page") * mS_SELECTION_ITEMS));

		// Destroy any previous ones created
		mS_DestroyPlayerMPs(playerid);

		while(x != mS_SELECTION_ITEMS && itemat < (gLists[mS_listID][mS_LIST_END]+1)) {
			if(linetracker == 0) {
				BaseX = mS_DIALOG_BASE_X + 25.0; // in a bit from the box
				BaseY += mS_SPRITE_DIM_Y + 1.0; // move on the Y for the next line
			}
			new rzID = gItemList[itemat][mS_ITEM_ROT_ZOOM_ID]; // avoid long line
			if(rzID > -1) gSelectionItems[playerid][x] = mS_CreateMPTextDraw(playerid, gItemList[itemat][mS_ITEM_MODEL], BaseX, BaseY, gRotZoom[rzID][0], gRotZoom[rzID][1], gRotZoom[rzID][2], gRotZoom[rzID][3], mS_SPRITE_DIM_X, mS_SPRITE_DIM_Y, bgcolor);
			else gSelectionItems[playerid][x] = mS_CreateMPTextDraw(playerid, gItemList[itemat][mS_ITEM_MODEL], BaseX, BaseY, 0.0, 0.0, 0.0, 1.0, mS_SPRITE_DIM_X, mS_SPRITE_DIM_Y, bgcolor);
			gSelectionItemsTag[playerid][x] = gItemList[itemat][mS_ITEM_MODEL];
			BaseX += mS_SPRITE_DIM_X + 1.0; // move on the X for the next sprite
			linetracker++;
			if(linetracker == mS_ITEMS_PER_LINE) linetracker = 0;
			itemat++;
			x++;
		}
	}
}

//------------------------------------------------

stock mS_UpdatePageTextDraw(playerid)
{
	new PageText[MAXO_TEXT1+1],
		listID = mS_GetPlayerCurrentListID(playerid);
	if(listID == mS_CUSTOM_LISTID)
		format(PageText, sizeof(PageText), "%d/%d", GetPVarInt(playerid,"mS_list_page") + 1, mS_GetNumberOfPagesEx(playerid));
	else
		format(PageText, sizeof(PageText), "%d/%d", GetPVarInt(playerid,"mS_list_page") + 1, mS_GetNumberOfPages(listID));
	PlayerTextDrawSetString(playerid, gCurrentPageTextDrawId[playerid], PageText);
}

//------------------------------------------------

stock ShowModelSelectionMenu(playerid, ListID, header_text[], dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899 , tdSelectionColor = 0xFFFF00AA)
{
	if(!(0 <= ListID < mS_TOTAL_LISTS && gLists[ListID][mS_LIST_START] != gLists[ListID][mS_LIST_END])) return 0;
	mS_DestroySelectionMenu(playerid);
	SetPVarInt(playerid, "mS_list_page", 0);
	SetPVarInt(playerid, "mS_list_id", ListID);
	SetPVarInt(playerid, "mS_list_active", 1);
	SetPVarInt(playerid, "mS_list_time", GetTickCount());

    gBackgroundTextDrawId[playerid] = mS_CreatePlayerBGTextDraw(playerid, mS_DIALOG_BASE_X, mS_DIALOG_BASE_Y + 20.0, mS_DIALOG_WIDTH, mS_DIALOG_HEIGHT, dialogBGcolor);
    gHeaderTextDrawId[playerid] = mS_CreatePlayerHeaderTextDraw(playerid, mS_DIALOG_BASE_X, mS_DIALOG_BASE_Y, header_text);
    gCurrentPageTextDrawId[playerid] = mS_CreateCurrentPageTextDraw(playerid, mS_DIALOG_WIDTH - 30.0, mS_DIALOG_BASE_Y + 15.0);
    gNextButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 30.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT+100.0, 50.0, 16.0, mS_NEXT_TEXT);
    gPrevButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 90.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT+100.0, 50.0, 16.0, mS_PREV_TEXT);
    gCancelButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 150.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT+100.0, 50.0, 16.0, mS_CANCEL_TEXT);

	SetPVarInt(playerid, "mS_previewBGcolor", previewBGcolor);
    mS_ShowPlayerMPs(playerid);
    mS_UpdatePageTextDraw(playerid);

	SelectTextDraw(playerid, tdSelectionColor);
	return 1;
}

//------------------------------------------------------------

stock ShowModelSelectionMenuEx(playerid, items_array[], item_amount, header_text[], extraid, Float:Xrot = 0.0, Float:Yrot = 0.0, Float:Zrot = 0.0, Float:mZoom = 1.0, dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899 , tdSelectionColor = 0xFFFF00AA)
{
	mS_DestroySelectionMenu(playerid);
	if(item_amount > mS_CUSTOM_MAX_ITEMS)
	{
		item_amount = mS_CUSTOM_MAX_ITEMS;
		print("-mSelection- WARNING: Too many items given to \"ShowModelSelectionMenuEx\", increase \"mS_CUSTOM_MAX_ITEMS\" to fix this");
	}
	if(item_amount > 0)
	{
		for(new i;i<item_amount;i++)
			gCustomList[playerid][i] = items_array[i];
		SetPVarInt(playerid, "mS_list_page", 0);
		SetPVarInt(playerid, "mS_list_id", mS_CUSTOM_LISTID);
		SetPVarInt(playerid, "mS_list_active", 1);
		SetPVarInt(playerid, "mS_list_time", GetTickCount());

		SetPVarInt(playerid, "mS_custom_item_amount", item_amount);
		SetPVarFloat(playerid, "mS_custom_Xrot", Xrot);
		SetPVarFloat(playerid, "mS_custom_Yrot", Yrot);
		SetPVarFloat(playerid, "mS_custom_Zrot", Zrot);
		SetPVarFloat(playerid, "mS_custom_Zoom", mZoom);
		SetPVarInt(playerid, "mS_custom_extraid", extraid);


		gBackgroundTextDrawId[playerid] = mS_CreatePlayerBGTextDraw(playerid, mS_DIALOG_BASE_X, mS_DIALOG_BASE_Y + 20.0, mS_DIALOG_WIDTH, mS_DIALOG_HEIGHT, dialogBGcolor);
		gHeaderTextDrawId[playerid] = mS_CreatePlayerHeaderTextDraw(playerid, mS_DIALOG_BASE_X, mS_DIALOG_BASE_Y, header_text);
		gCurrentPageTextDrawId[playerid] = mS_CreateCurrentPageTextDraw(playerid, mS_DIALOG_WIDTH - 30.0, mS_DIALOG_BASE_Y + 15.0);
		gNextButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 30.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT+100.0, 50.0, 16.0, mS_NEXT_TEXT);
		gPrevButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 90.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT+100.0, 50.0, 16.0, mS_PREV_TEXT);
		gCancelButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 150.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT+100.0, 50.0, 16.0, mS_CANCEL_TEXT);

		SetPVarInt(playerid, "mS_previewBGcolor", previewBGcolor);
		mS_ShowPlayerMPs(playerid);
		mS_UpdatePageTextDraw(playerid);

		SelectTextDraw(playerid, tdSelectionColor);
		return 1;
	}
	return 0;
}

//------------------------------------------------

stock HideModelSelectionMenu(playerid)
{
	mS_DestroySelectionMenu(playerid);
	SetPVarInt(playerid, "mS_ignore_next_esc", 1);
	CancelSelectTextDraw(playerid);
	return 1;
}

//------------------------------------------------

stock mS_DestroySelectionMenu(playerid)
{
	if(GetPVarInt(playerid, "mS_list_active") == 1)
	{
		if(mS_GetPlayerCurrentListID(playerid) == mS_CUSTOM_LISTID)
		{
			DeletePVar(playerid, "mS_custom_Xrot");
			DeletePVar(playerid, "mS_custom_Yrot");
			DeletePVar(playerid, "mS_custom_Zrot");
			DeletePVar(playerid, "mS_custom_Zoom");
			DeletePVar(playerid, "mS_custom_extraid");
			DeletePVar(playerid, "mS_custom_item_amount");
		}
		DeletePVar(playerid, "mS_list_time");
		SetPVarInt(playerid, "mS_list_active", 0);
		mS_DestroyPlayerMPs(playerid);

		PlayerTextDrawDestroy(playerid, gHeaderTextDrawId[playerid]);
		PlayerTextDrawDestroy(playerid, gBackgroundTextDrawId[playerid]);
		PlayerTextDrawDestroy(playerid, gCurrentPageTextDrawId[playerid]);
		PlayerTextDrawDestroy(playerid, gNextButtonTextDrawId[playerid]);
		PlayerTextDrawDestroy(playerid, gPrevButtonTextDrawId[playerid]);
		PlayerTextDrawDestroy(playerid, gCancelButtonTextDrawId[playerid]);

		gHeaderTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
		gBackgroundTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
		gCurrentPageTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
		gNextButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
		gPrevButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
		gCancelButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}
}

stock mS_strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
		index++;

	new offset = index,
		result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}


/*#define MAX_SKINS 312

stock LoadSkins() {
	mysql_tquery(connectionHandle, "SELECT * FROM skins", "LoadSkinsThread", "d", SKINS_THREAD_ID);
	return true;
}

function LoadSkinsThread() {
	cache_get_data(rows, fields);
	if(rows) {
		new
			SkinModel, Float:SkinPos[4], SkinWeapon[3], SkinAmmo[3];
		for(new i = 0; i < MAX_SKINS; i ++) {
			SkinModel = cache_get_row_int(i, 1);
			SkinPos[0] = cache_get_row_float(i, 2);
			SkinPos[1] = cache_get_row_float(i, 3);
			SkinPos[2] = cache_get_row_float(i, 4);
			SkinPos[3] = cache_get_row_float(i, 5);
			SkinWeapon[0] = cache_get_row_int(i, 6);
			SkinAmmo[0] = cache_get_row_int(i, 7);
			SkinWeapon[1] = cache_get_row_int(i, 8);
			SkinAmmo[1] = cache_get_row_int(i, 9);
			SkinWeapon[2] = cache_get_row_int(i, 10);
			SkinAmmo[2] = cache_get_row_int(i, 11);

			AddPlayerClass(SkinModel, SkinPos[0], SkinPos[1], SkinPos[2], SkinPos[3], SkinWeapon[0], SkinAmmo[0], SkinWeapon[1], SkinAmmo[1], SkinWeapon[2], SkinAmmo[2]);
		}
		printf("LoadSkinsThread() - called (%d skins loaded).", rows);
	}
	return true;
}*/

#define MAX_SKIN_ID 400
#define CUSTOM_SKINS_MENU 1

stock IncarcaSkinSelector(playerid) {
	new query[MAXO_TEXT];
	mysql_format(connectionHandle, query, sizeof(query), "SELECT * FROM faction_skins WHERE Faction = %d AND Rank = %d", PlayerInfo[playerid][pFactiune], PlayerInfo[playerid][pRank]);
	mysql_tquery(connectionHandle, query, "LoadModelSelectionMenu", "d", playerid);
	clear.string(query);
	return true;
}

function LoadModelSelectionMenu(extraid) {
	rows = cache_num_rows();
	new SkinSelectorArray[MAX_SKIN_ID];
	if(extraid != INVALID_PLAYER_ID) {
		if(rows) {
			for(new r; r < rows; r++) SkinSelectorArray[r] = cache_get_row_int(r, 3);
			ShowModelSelectionMenuEx(extraid, SkinSelectorArray, rows, "Available Skin", CUSTOM_SKINS_MENU, 0.0, 0.0, 0.0);
		} else SendClientMessage(extraid, COLOR_GRAD1, "No skins to show for you.");
	}
	return true;
}

COMMAND:addskin(playerid, params[]) {
	new string[MAXO_TEXT], skinID, factionID, rankID;
	if(PlayerInfo[playerid][pAdmin] >= 1337) {
		if(!sscanf(params, "ddd", factionID, rankID, skinID)) {
			if(ISBetween(factionID, FACT_CIVIL, MAX_FACTIONS-1)) {
				if(ISBetween(rankID, 0, 6)) {
					if(ISBetween(skinID, 0, 311)) {
						format(string, MAXO_TEXT, "INSERT INTO faction_skins (Faction, Rank, Skin) VALUES (%d, %d, %d)", factionID, rankID, skinID);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", SKINS_THREAD_ID);
						format(string, MAXO_TEXT, "AdmCmd: Admin %s has added a new one skin (%d) rank %d for faction %s.", PlayerName(playerid), skinID, rankID, FactionInfo[factionID][fName]);
						ABroadCast(COLOR_LIGHTRED, string, 1);
						format(string, MAXO_TEXT, "* You added a new one skin (%d) rank %d for faction %s.", skinID, rankID, FactionInfo[factionID][fName]);
						SendClientMessage(playerid, COLOR_LIGHTRED, string);
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid skin ID.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid rank ID.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid faction ID.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/addskin [factionID] [rankID] [skinID]");
	} else NotAuthorized();
	return true;
}

COMMAND:updateskin(playerid, params[]) {
	new string[MAXO_TEXT], skinID, factionID, rankID;
	if(PlayerInfo[playerid][pAdmin] >= 1337) {
		if(!sscanf(params, "ddd", factionID, rankID, skinID)) {
			if(ISBetween(factionID, FACT_CIVIL, MAX_FACTIONS-1)) {
				if(ISBetween(rankID, 0, 6)) {
					if(ISBetween(skinID, 0, 311)) {
						format(string, MAXO_TEXT, "UPDATE faction_skins SET Skin = %d WHERE Faction = %d AND Rank = %d", skinID, factionID, rankID);
						mysql_tquery(connectionHandle, string, "NoReturnThread", "d", SKINS_THREAD_ID);
						format(string, MAXO_TEXT, "AdmCmd: Admin %s has modified a skin %d from %s rank %d.", PlayerName(playerid), skinID, FactionInfo[factionID][fName], rankID);
						ABroadCast(COLOR_LIGHTRED, string, 1);
						format(string, MAXO_TEXT, "* You modified a skin (%d) rank %d for faction %s.", skinID, rankID, FactionInfo[factionID][fName]);
						SendClientMessage(playerid, COLOR_LIGHTRED, string);
						clear.string(string);
					} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid skin ID.");
				} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid rank ID.");
			} else SendClientMessage(playerid, COLOR_GRAD1, "Invalid faction ID.");
		} else SendClientMessage(playerid, COLOR_ORANGE, "USAGE: {FFFFFF}/updateskin [factionID] [rankID] [skinID]");
	} else NotAuthorized();
	return true;
}

// End Of File ...
