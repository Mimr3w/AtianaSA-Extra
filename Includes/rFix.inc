/*OnPlayerWeaponShot Bug fix by RogueDrifter
Created on Feb the 4th 2018
Bug Describton according to SA-MP Wiki:
    *************************************************************************************************************
    * It is called as BULLET_HIT_TYPE_VEHICLE with the correct hitid (the hit player's vehicleid)               *
    * if you are shooting a player which is in a vehicle. It won't be called as BULLET_HIT_TYPE_PLAYER at all.  *
    *************************************************************************************************************
    
This include will:
******************
    Call the OPWS callback only once for hittype BULLET_HIT_TYPE_PLAYER if it does damage the player and
    Call it BULLET_HIT_TYPE_VEHICLE if it doesn't damage the player. BUT due to paused players not getting
    Damage, this adds a new hittype #5 which is called if a player shoots a vehicle that has a player who
    is paused, you can either do this one on your own or exclude it from your anti cheat for false positives.
    *****************************************************************/
 
#if defined _EOpwsFix_included
    #endinput
#endif
#define _EOpwsFix_included
 
#include <a_samp>
 
enum E_eFix_OPWS_INFO
{
    eFixPauseTicks,
 
    bool:eFixPlayerDamaged,
    bool:eFixDesyncPassg,
    bool:eFixDoubleCFix,
    bool:eFixJustShot,
 
    Float:eFixShotX,
    Float:eFixShotY,
    Float:eFixShotZ,
 
    Float:eFixATypeHealth,
    Float:eFixBTypeHealth,
 
    Float:eFixATypeArmour,
    Float:eFixBTypeArmour
};
 
new
    eFix_Player[MAX_PLAYERS][E_eFix_OPWS_INFO];
 
#if defined eFix_OnPlayerWeaponShot
    forward eFix_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif
 
#if defined eFix_OnPlayerUpdate
    forward eFix_OnPlayerUpdate(playerid);
#endif
 
#if defined eFix_OnPlayerSpawn
    forward eFix_OnPlayerSpawn(playerid);
#endif
 
#if defined eFix_OnPlayerStateChange
    forward eFix_OnPlayerStateChange(playerid, newstate, oldstate);
#endif
 
#if defined eFix_OnPlayerConnect
    forward eFix_OnPlayerConnect(playerid);
#endif
 
#if defined eFix_OnPlayerDeath
    forward eFix_OnPlayerDeath(playerid, killerid, reason);
#endif
 
forward eFix_SetPlayerArmour(playerid, Float:amount);
forward eFix_SetPlayerHealth(playerid, Float:amount);
forward eFix_OpwsCheck(playerid, weaponid, vehicleid, Float:x, Float:y, Float:z, shooterid);
 
forward eFix_ResetShot(playerid);
forward eFix_FixOpu(playerid);
forward eFix_DesyncP(playerid,  weaponid, vehicleid, Float:x, Float:y, Float:z, shooterid);
forward eFix_ResetDamage(playerid);
forward eFix_ResetDoubleCFix(playerid);
 
public OnPlayerConnect(playerid)
{
    eFix_Player[playerid][eFixPlayerDamaged] = false;
    eFix_Player[playerid][eFixDoubleCFix] = false;
    eFix_Player[playerid][eFixDesyncPassg] = false;
    eFix_Player[playerid][eFixJustShot] = false;
 
        #if defined eFix_OnPlayerConnect
    return eFix_OnPlayerConnect(playerid);
        #else
    return 1;
        #endif
}
 
public OnPlayerSpawn(playerid)
{
    eFix_Player[playerid][eFixDesyncPassg] = false;
        #if defined eFix_OnPlayerSpawn
    return eFix_OnPlayerSpawn(playerid);
        #else
    return 1;
        #endif
}      
 
public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
    if(hittype == BULLET_HIT_TYPE_VEHICLE)
    {
        if(!eFix_Player[playerid][eFixJustShot]) SetTimerEx("eFix_ResetShot", 650, false, "d", playerid);
        eFix_Player[playerid][eFixShotX]=fX;
        eFix_Player[playerid][eFixShotY]=fY;
        eFix_Player[playerid][eFixShotZ]=fZ;
        eFix_Player[playerid][eFixJustShot] = true;
 
 
        for(new i, j = GetPlayerPoolSize(); i <= j; i++)
        {
            if(GetPlayerVehicleID(i) == hitid && !eFix_Player[i][eFixDoubleCFix])
            {
                return SetTimerEx("eFix_OpwsCheck", 285, false, "dddfffd", i, weaponid, hitid, Float:fX, Float:fY, Float:fZ, playerid);
                }
            }
        }
            #if defined eFix_OnPlayerWeaponShot
    return eFix_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
        #else
    return 1;
        #endif
}
 
public OnPlayerUpdate(playerid)
{
    eFix_Player[playerid][eFixPauseTicks] = GetTickCount();
    new E_State = GetPlayerState(playerid);
    if(E_State == 3 || E_State == 2 )
    {
        GetPlayerHealth(playerid, eFix_Player[playerid][eFixBTypeHealth]);
        GetPlayerArmour(playerid, eFix_Player[playerid][eFixBTypeArmour]);
        if(eFix_Player[playerid][eFixATypeHealth] > eFix_Player[playerid][eFixBTypeHealth] && !eFix_Player[playerid][eFixPlayerDamaged]
        && eFix_Player[playerid][eFixBTypeArmour] == 0.0)
        {
            eFix_Player[playerid][eFixATypeHealth] = eFix_Player[playerid][eFixBTypeHealth];
            eFix_Player[playerid][eFixPlayerDamaged] = true;
            SetTimerEx("eFix_ResetDamage", 490, false, "i", playerid);
            }
        else if(eFix_Player[playerid][eFixBTypeHealth] <= 0.0)
        {
            eFix_Player[playerid][eFixATypeHealth] = eFix_Player[playerid][eFixBTypeHealth];
            eFix_Player[playerid][eFixPlayerDamaged] = true;
            SetTimerEx("eFix_ResetDamage", 490, false, "i", playerid);
            }
        else if(eFix_Player[playerid][eFixBTypeArmour] > 0.0)
        {
            if(eFix_Player[playerid][eFixATypeArmour] > eFix_Player[playerid][eFixBTypeArmour]
            && !eFix_Player[playerid][eFixPlayerDamaged])
            {
                eFix_Player[playerid][eFixATypeArmour] = eFix_Player[playerid][eFixBTypeArmour];
                eFix_Player[playerid][eFixPlayerDamaged] = true;
                SetTimerEx("eFix_ResetDamage", 490, false, "i", playerid);
                }
            }
        }
            #if defined eFix_OnPlayerUpdate
    return eFix_OnPlayerUpdate(playerid);
        #else
    return 1;
        #endif
}
 
public OnPlayerDeath(playerid, killerid, reason)
{
    eFix_Player[playerid][eFixDesyncPassg] = true;
 
        #if defined eFix_OnPlayerDeath
    return eFixOnPlayerDeath(playerid, killerid, reason);
        #else
    return 1;
        #endif
}
 
public OnPlayerStateChange(playerid, newstate, oldstate)
{
        if(newstate == 3 || newstate == 2 )
        {
            GetPlayerHealth(playerid, eFix_Player[playerid][eFixBTypeHealth]);
            GetPlayerArmour(playerid, eFix_Player[playerid][eFixBTypeArmour]);
            GetPlayerHealth(playerid, eFix_Player[playerid][eFixATypeHealth]);
            GetPlayerArmour(playerid, eFix_Player[playerid][eFixATypeArmour]);
            }
 
        #if defined eFix_OnPlayerStateChange
    return eFix_OnPlayerStateChange(playerid, newstate, oldstate)
        #else
    return 1;
        #endif
}
 
public eFix_SetPlayerArmour(playerid, Float:amount)
{
    eFix_Player[playerid][eFixATypeArmour] = amount;
    SetPlayerArmour(playerid, amount); 
 
    return 1;
}

public eFix_SetPlayerHealth(playerid, Float:amount)
{
    eFix_Player[playerid][eFixATypeHealth] = amount;
    SetPlayerHealth(playerid, amount); 
 
    return 1;
}

public eFix_ResetShot(playerid) return eFix_Player[playerid][eFixJustShot]  = false;
 
public eFix_ResetDamage(playerid) return eFix_Player[playerid][eFixPlayerDamaged] = false;
 
public eFix_ResetDoubleCFix(playerid) return eFix_Player[playerid][eFixDoubleCFix]= false;
 
public eFix_DesyncP(playerid,  weaponid, vehicleid, Float:x, Float:y, Float:z, shooterid)
{
    if(eFix_Player[playerid][eFixDesyncPassg])
    {
        return OnPlayerWeaponShot(shooterid, weaponid, 1, playerid, x, y, z);
        }
    else if(!eFix_Player[playerid][eFixDesyncPassg])
    {
        new Float:xx, Float:yy, Float:zz;
        GetPlayerPos(playerid, xx,yy,zz);
        for(new i, j = GetPlayerPoolSize(); i <= j; i++)
        {
            new eWep = GetPlayerWeapon(i);
            if(!IsPlayerConnected(i)) continue;
            if(IsAmmoable(eWep) && eFix_Player[i][eFixJustShot] && IsPlayerInRangeOfPoint(i, 50.0, xx, yy, zz)
            && IsPlayerInRangeOfPoint(playerid, 2.0, eFix_Player[i][eFixShotX], eFix_Player[i][eFixShotY], eFix_Player[i][eFixShotZ])
            && IsPAiming(i)) return OnPlayerWeaponShot(i, eWep, 5, playerid, eFix_Player[i][eFixShotX], eFix_Player[i][eFixShotY], eFix_Player[i][eFixShotZ]);
            }
        }

    return 1;
}
 
public eFix_OpwsCheck(playerid, weaponid, vehicleid, Float:x, Float:y, Float:z, shooterid)
{
    new Float:Health;
    GetPlayerHealth(playerid, Health);
 
    if(eFix_Player[playerid][eFixDesyncPassg]) return OnPlayerWeaponShot(shooterid, weaponid, 1, playerid, x, y, z);
 
    if(GetTickCount() > eFix_Player[playerid][eFixPauseTicks]+800)
    {
        if(GetPlayerState(playerid) == 3 ) return SetTimerEx("eFix_DesyncP", 150, false, "d", playerid,  weaponid, vehicleid, Float:x, Float:y, Float:z, shooterid);
        return OnPlayerWeaponShot(shooterid, weaponid, 5, playerid, x, y, z);
        }
    else
    {
        if(eFix_Player[playerid][eFixPlayerDamaged] || Health <= 0.0)
        {
            return OnPlayerWeaponShot(shooterid, weaponid, 1, playerid, x, y, z);
            }
        else if(!eFix_Player[playerid][eFixPlayerDamaged])
        {
            return
            eFix_Player[playerid][eFixDoubleCFix] = true,
            OnPlayerWeaponShot(shooterid, weaponid, 2, vehicleid, x, y, z),
            SetTimerEx("eFix_ResetDoubleCFix", 20, false, "i", playerid);
            }
        }

    return 1;
}
 
stock static IsAmmoable(weaponid)
{
    if(22 <= weaponid <= 34 || weaponid == 38) return 1;
    else return 0;
}
 
stock IsPAiming(playerid)
{
    new playeranim = GetPlayerAnimationIndex(playerid);
 
    if (((playeranim >= 1160) && (playeranim <= 1163)) || (playeranim == 1167) || (playeranim == 1365) ||
    (playeranim == 1643) || (playeranim == 1453) || (playeranim == 220)) return 1;
    return 0;
}
 
#if defined _ALS_OnPlayerSpawn
  #undef OnPlayerSpawn
#else
    #define _ALS_OnPlayerSpawn
#endif
 
#define OnPlayerSpawn OnPlayerSpawn
 
#if defined _ALS_OnPlayerUpdate
  #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif
 
#define OnPlayerUpdate eFix_OnPlayerUpdate
 
#if defined _ALS_OnPlayerWeaponShot
  #undef OnPlayerWeaponShot
#else
    #define _ALS_OnPlayerWeaponShot
#endif
 
#define OnPlayerWeaponShot eFix_OnPlayerWeaponShot
 
#if defined _ALS_OnPlayerConnect
  #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
 
#define OnPlayerConnect eFix_OnPlayerConnect
 
#if defined _ALS_OnPlayerDeath
  #undef OnPlayerDeath
#else
    #define _ALS_OnPlayerDeath
#endif
 
#define OnPlayerDeath eFix_OnPlayerDeath
 
#if defined _ALS_OnPlayerSpawn
  #undef OnPlayerSpawn
#else
    #define _ALS_OnPlayerSpawn
#endif
 
#define OnPlayerSpawn eFix_OnPlayerSpawn
 
#if defined _ALS_SetPlayerArmour
  #undef SetPlayerArmour
#else
    #define _ALS_SetPlayerArmour
#endif
 
#define SetPlayerArmour eFix_SetPlayerArmour

#if defined _ALS_SetPlayerHealth
  #undef SetPlayerHealth
#else
    #define _ALS_SetPlayerHealth
#endif
 
#define SetPlayerHealth eFix_SetPlayerHealth