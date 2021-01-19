//Made by lokii.
#include <streamer> //credits to incognito.

#define         SKIN_CHANGE_DELAY           1000 //tried 600 and 800 stil could see the skin changing :)

//credits to pottus for editing skin effect and object deletion

//v 1.2

/*
native SetPlayerSkin(playerid, skinid);
*/

static p_skin_obj[MAX_PLAYERS] = { -1, ... };
static p_skin_obj2[MAX_PLAYERS] = { -1, ... } ;

static DISTimer[MAX_PLAYERS];
static SkinTimer[MAX_PLAYERS];

forward DIS(playerid);
public DIS(playerid)
{
    TogglePlayerControllable(playerid, 1);
    DestroyDynamicObject(p_skin_obj[playerid]);
    return DestroyDynamicObject(p_skin_obj2[playerid]);
}

forward DelaySkinChange(playerid, skinid);
public DelaySkinChange(playerid, skinid)
{
	SetPlayerSkin(playerid, skinid);
	return 1;
}


static ResetSkinChange(playerid)
{
	// This NEEDS to be done like this otherwise you will continually destory objects
	if(p_skin_obj[playerid] > -1)
	{
	    DestroyDynamicObject(p_skin_obj[playerid]);
	    DestroyDynamicObject(p_skin_obj2[playerid]);
	    p_skin_obj[playerid] = -1;
	    p_skin_obj2[playerid] = -1;
	}

	KillTimer(DISTimer[playerid]);
	KillTimer(SkinTimer[playerid]);
}

public OnPlayerDisconnect(playerid, reason)
{
	ResetSkinChange(playerid);

    #if defined SE_OnPlayerDisconnect
        SE_OnPlayerDisconnect(playerid, reason);
    #endif
    return 1;
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect SE_OnPlayerDisconnect
#if defined SE_OnPlayerDisconnect
    forward SE_OnPlayerDisconnect(playerid, reason);
#endif

stock SetPlayerSkinEx(playerid, skinid)
{
	// Destory any created objects first
	ResetSkinChange(playerid);
    new Float:e_skin_x, Float:e_skin_y, Float:e_skin_z;
    GetPlayerPos(playerid, e_skin_x, e_skin_y, e_skin_z);
    TogglePlayerControllable(playerid, 0);
    p_skin_obj[playerid] = CreateDynamicObject(18671, e_skin_x, e_skin_y, e_skin_z-2.5, 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 100.0, STREAMER_OBJECT_DD, -1, 0);
    p_skin_obj2[playerid] = CreateDynamicObject(18728, e_skin_x, e_skin_y, e_skin_z-1.5, 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 100.0, STREAMER_OBJECT_DD, -1, 0);
    DISTimer[playerid] = SetTimerEx("DIS", 1200, false, "i", playerid);
    SkinTimer[playerid] = SetTimerEx("DelaySkinChange", SKIN_CHANGE_DELAY, false, "iii", playerid, skinid);
    Streamer_Update(playerid);
    return 1;
}

#if defined _ALS_SetPlayerSkin
    #undef SetPlayerSkin
#else
    #define _ALS_SetPlayerSkin
#endif
#define SetPlayerSkin SetPlayerSkinEx


//EOF.