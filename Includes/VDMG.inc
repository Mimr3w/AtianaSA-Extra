//Made by lokii.
 
/*
native ToggleVehicleDamageable(vehicleid, status);
*/
 
static Float:weapon_vdmg[] =
{
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1000.0, 0.0, 1000.0, 0.0, 0.0, 0.0, 15.0, 15.0, 25.0, 120.0, 120.0, 120.0,
    35.0, 35.0, 100.0, 100.0, 35.0, 200.0, 200.0, 1000.0, 1000.0,
    1000.0, 100.0, 1000.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
};
 
static vdmg_prev[MAX_PLAYERS] = {0, ...};
static vdmg_bps[MAX_VEHICLES] = {0, ...};
static vdmg_bp[MAX_VEHICLES] = {0, ...};
 
stock ToggleVehicleDamageable(vehicleid, status)
{
    if(vehicleid == INVALID_VEHICLE_ID) return 0;
    CallRemoteFunction("VDMG_CALL", "ii", vehicleid, status);
    return 1;
}
 
forward VDMG_CALL(vehicleid, status);
 
public VDMG_CALL(vehicleid, status)
{
    return vdmg_bp[vehicleid] = status;
}
 
public OnPlayerStateChange(playerid, newstate, oldstate)
{
    switch(newstate)
    {
        case PLAYER_STATE_DRIVER:
        {
            vdmg_prev[playerid] = GetPlayerVehicleID(playerid);
            vdmg_bps[GetPlayerVehicleID(playerid)] ++;
        }
    }
    if(oldstate == PLAYER_STATE_DRIVER && newstate != PLAYER_STATE_DRIVER)
    {
        vdmg_bps[vdmg_prev[playerid]] --;
        vdmg_prev[playerid] = INVALID_VEHICLE_ID;
    }
 
    #if defined afk_OnPlayerConnect
        vdmg_OnPlayerStateChange(playerid, newstate, oldstate);
    #endif
    return 1;
}
#if defined _ALS_OnPlayerStateChange
    #undef OnPlayerStateChange
#else
    #define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange vdmg_OnPlayerStateChange
#if defined vdmg_OnPlayerStateChange
    forward vdmg_OnPlayerStateChange(playerid, newstate, oldstate);
#endif
 
public OnPlayerConnect(playerid)
{
    vdmg_prev[playerid] = INVALID_VEHICLE_ID;
 
    #if defined afk_OnPlayerConnect
        vdmg_OnPlayerConnect(playerid);
    #endif
    return 1;
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect vdmg_OnPlayerConnect
#if defined vdmg_OnPlayerConnect
    forward vdmg_OnPlayerConnect(playerid);
#endif
 
public OnPlayerDisconnect(playerid, reason)
{
    vdmg_bps[vdmg_prev[playerid]] --;
    vdmg_prev[playerid] = INVALID_VEHICLE_ID;
 
    #if defined afk_OnPlayerConnect
        vdmg_OnPlayerDisconnect(playerid, reason);
    #endif
    return 1;
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect vdmg_OnPlayerDisconnect
#if defined vdmg_OnPlayerDisconnect
    forward vdmg_OnPlayerDisconnect(playerid, reason);
#endif
 
public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
    new Float:vhp;
    switch(hittype)
    {
        case 2:
        {
            if(hitid == INVALID_VEHICLE_ID || vdmg_bps[hitid] > 0 || vdmg_bp[hitid] != 0) return 1;
            GetVehicleHealth(hitid, vhp);
            SetVehicleHealth(hitid, vhp - weapon_vdmg[weaponid]);
        }
    }
 
    #if defined afk_OnPlayerConnect
        vdmg_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
    #endif
    return 1;
}
#if defined _ALS_OnPlayerWeaponShot
    #undef OnPlayerWeaponShot
#else
    #define _ALS_OnPlayerWeaponShot
#endif
#define OnPlayerWeaponShot vdmg_OnPlayerWeaponShot
#if defined vdmg_OnPlayerWeaponShot
    forward vdmg_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif
 
 
 
//EOF.