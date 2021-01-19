//Made by lokii.

#if !defined MAX_COPS
	#define MAX_COPS (50)
#endif

#define cops_version 10

/*
native Natives();
native
native CreateCop(skinid, name[], Float:detection_area, Float:health, Float:x, Float:y, Float:z, Float:angle, weapon, Float:accuracy);
native IsCopDead(cop_id);
native IsCopInvulnerable(cop_id);
native IsCopMoving(cop_id);
native IsCopValid(cop_id);
native GetCopHealth(cop_id);
native GetCopTarget(cop_id);
native GetClosestPlayerToCop(cop_id);
native GetCopDetectionArea(cop_id);
native GetCopPos(cop_id, &Float:x, &Float:y, &Float:z);
native GetCopAngle(cop_id, &Float:angle);
native GetCopCreationPos(cop_id, &Float:x, &Float:y, &Float:z);
native GetCopCreationAngle(cop_id, &Float:angle);
native GetCopInterior(cop_id);
native GetCopVirtualWorld(cop_id);
native GetCopSkin(cop_id);
native GetCopCustomSkin(cop_id);
native GetCopWeapon(cop_id);
native SetCopWeapon(cop_id, weaponid);
native SetCopInvulnerable(cop_id, bool:invulnerable);
native SetCopSkin(cop_id, skinid);
native SetCopInterior(cop_id, interiorid);
native SetCopVirtualWorld(cop_id, worldid);
native SetCopHealth(cop_id, Float:health);
native RespawnCop(cop_id);
native DestroyCop(cop_id);
native DestroyAllCops();
native
native Callbacks();
native
native OnCopDeath(cop_id, killerid, weaponid);
native OnCopTakeDamage(cop_id, damagerid, weaponid, bodypart, Float:health_loss);
native OnCopKillPlayer(cop_id, playerid);
native OnCrimeHappenNearCop(playerid, crime);
*/

#define CRIME_KILL 0
#define CRIME_SHOOT 1
#define CRIME_DAMAGE 2

static g_CopReferences[MAX_PLAYERS] = { -1, ... };

enum ee_cops
{
	bool:cop_exist,
	cop_time,
	copid,
	cop_target,
	Float:cop_detection,
	Float:cop_pos_x,
	Float:cop_pos_y,
	Float:cop_pos_z,
	Float:cop_angle
}
static e_cops[MAX_COPS][ee_cops];

stock SetCopInterior(cop_id, interiorid)
{
	if(IsCopValid(cop_id))
	{
        FCNPC_SetInterior(e_cops[cop_id][copid], interiorid);
        return 1;
	}
	return 0;
}

stock GetCopInterior(cop_id)
{
	if(IsCopValid(cop_id))
	{
        return FCNPC_GetInterior(e_cops[cop_id][copid]);
	}
	return 0;
}

stock SetCopVirtualWorld(cop_id, worldid)
{
	if(IsCopValid(cop_id))
	{
        FCNPC_SetVirtualWorld(e_cops[cop_id][copid], worldid);
        return 1;
	}
	return 0;
}

stock GetCopVirtualWorld(cop_id)
{
	if(IsCopValid(cop_id))
	{
        return FCNPC_GetVirtualWorld(e_cops[cop_id][copid]);
	}
	return 0;
}

stock GetCopCreationPos(cop_id, &Float:x, &Float:y, &Float:z)
{
	if(IsCopValid(cop_id))
	{
		x = e_cops[cop_id][cop_pos_x];
		y = e_cops[cop_id][cop_pos_y];
		z = e_cops[cop_id][cop_pos_z];
		return 1;
	}
	return 0;
}

stock GetCopCreationAngle(cop_id, &Float:angle)
{
	if(IsCopValid(cop_id))
	{
		angle = e_cops[cop_id][cop_angle];
		return 1;
	}
	return 0;
}

stock GetCopAngle(cop_id, &Float:angle)
{
	if(IsCopValid(cop_id))
	{
		angle = FCNPC_GetAngle(e_cops[cop_id][copid]);
		return 1;
	}
	return 0;
}

stock bool:IsCopMoving(cop_id)
{
	if(IsCopValid(cop_id))
	{
	    return FCNPC_IsMoving(e_cops[cop_id][copid]);
	}
	return false;
}

Float:GetCopDetectionArea(cop_id)
{
	if(IsCopValid(cop_id))
	{
	    return e_cops[cop_id][cop_detection];
	}
	return 0.0;
}

IsCopValid(cop_id)
{
	if(cop_id < 0 || cop_id >= MAX_COPS) return 0;
	return e_cops[cop_id][cop_exist];
}

stock CreateCop(skinid, name[], Float:detection_area, Float:health, Float:x, Float:y, Float:z, Float:angle, weapon, Float:accuracy)
{
	new id;
    for(new i = 0; i < MAX_COPS; i++)
    {
        if(IsCopValid(i)) continue;
        id = FCNPC_Create(name);
        if(FCNPC_IsValid(id))
        {
	        e_cops[i][copid] = id;
	        g_CopReferences[e_cops[i][copid]] = i;
	        FCNPC_Spawn(e_cops[i][copid], skinid, x, y, z);
	        FCNPC_SetHealth(e_cops[i][copid], health);
	        FCNPC_SetAngle(e_cops[i][copid], angle);
	        FCNPC_SetWeaponAccuracy(e_cops[i][copid], weapon, accuracy);
	        FCNPC_SetWeapon(e_cops[i][copid], weapon);
	        FCNPC_UseInfiniteAmmo(e_cops[i][copid], true);
	        e_cops[i][cop_pos_x] = x;
	        e_cops[i][cop_pos_y] = y;
	        e_cops[i][cop_pos_z] = z;
	        e_cops[i][cop_angle] = angle;
	        e_cops[i][cop_detection] = detection_area;
	        e_cops[i][cop_target] = 0xFFFF;
	        e_cops[i][cop_exist] = true;
			return i;
		}
    }
	return 0xFFFF;
}

stock SetCopWeapon(cop_id, weaponid)
{
	if(IsCopValid(cop_id))
	{
	    FCNPC_SetWeapon(e_cops[cop_id][copid], weaponid);
	    return 1;
	}
	return 0;
}

stock GetCopWeapon(cop_id)
{
	if(IsCopValid(cop_id))
	{
	    return FCNPC_GetWeapon(e_cops[cop_id][copid]);
	}
	return 0;
}

stock GetCopPos(cop_id, &Float:x, &Float:y, &Float:z)
{
	if(IsCopValid(cop_id))
	{
	    FCNPC_GetPosition(e_cops[cop_id][copid], x, y, z);
	    return 1;
	}
	return 0;
}

stock Float:GetCopHealth(cop_id)
{
	if(IsCopValid(cop_id))
	{
	    return FCNPC_GetHealth(e_cops[cop_id][copid]);
	}
	return 0.0;
}

stock bool:IsCopDead(cop_id)
{
	if(IsCopValid(cop_id))
	{
	    return FCNPC_IsDead(e_cops[cop_id][copid]);
	}
	return false;
}

stock RespawnCop(cop_id)
{
	if(IsCopValid(cop_id))
	{
    	FCNPC_Respawn(e_cops[cop_id][copid]);
    	FCNPC_SetPosition(e_cops[cop_id][copid], e_cops[cop_id][cop_pos_x], e_cops[cop_id][cop_pos_y], e_cops[cop_id][cop_pos_z]);
    	FCNPC_SetAngle(e_cops[cop_id][copid], e_cops[cop_id][cop_angle]);
		return 1;
	}
	return 0;
}

stock DestroyCop(cop_id)
{
	if(IsCopValid(cop_id))
	{
    	FCNPC_Destroy(e_cops[cop_id][copid]);
    	e_cops[cop_id][cop_pos_x] = 0.0;
        e_cops[cop_id][cop_pos_y] = 0.0;
        e_cops[cop_id][cop_pos_z] = 0.0;
        e_cops[cop_id][cop_angle] = 0.0;
        e_cops[cop_id][cop_detection] = 0.0;
        e_cops[cop_id][cop_target] = 0xFFFF;
        g_CopReferences[cop_id] = -1;
    	e_cops[cop_id][cop_exist] = false;
		return 1;
	}
	return 0;
}

CopAttackPlayer(cop_id, playerid)
{
	if(IsCopValid(cop_id) && IsPlayerConnected(playerid))
	{
	    FCNPC_AimAtPlayer(e_cops[cop_id][copid], playerid, true, -1, true, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	    e_cops[cop_id][cop_target] = playerid;
	    return playerid;
	}
	return 0xFFFF;
}

stock SetCopHealth(cop_id, Float:health)
{
	if(IsCopValid(cop_id))
	{
	    FCNPC_SetHealth(e_cops[cop_id][copid], health);
		return 1;
	}
	return 0;
}

GetCopTarget(cop_id)
{
	if(cop_id < 0 || cop_id >= MAX_COPS) return 0xFFFF;
	if(IsCopValid(cop_id))
	{
	    return e_cops[cop_id][cop_target];
	}
	return 0xFFFF;
}

forward OnCopDeath(cop_id, killerid, weaponid);

public FCNPC_OnDeath(npcid, killerid, reason)
{
    if(g_CopReferences[npcid] != -1 && killerid != 0xFFFF)
    CallLocalFunction("OnCopDeath", "iii", g_CopReferences[npcid], killerid, reason);

	#if defined cops_FCNPC_OnDeath
		return cops_FCNPC_OnDeath(npcid, killerid, weaponid);
	#else
		return 1;
	#endif
}
#if defined _ALS_FCNPC_OnDeath
	#undef FCNPC_OnDeath
#else
	#define _ALS_FCNPC_OnDeath
#endif
#define FCNPC_OnDeath cops_FCNPC_OnDeath
#if defined cops_FCNPC_OnDeath
	forward cops_FCNPC_OnDeath(npcid, killerid, weaponid);
#endif

stock GetClosestPlayerToCop(cop_id)
{
	new id = -1, Float:tmp, Float:last = 99999, Float:x, Float:y, Float:z;
	if(IsCopValid(cop_id))
	{
	    FCNPC_GetPosition(e_cops[copid][copid], x, y, z);
	    for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
	    {
	        if(!IsPlayerConnected(i) || IsPlayerNPC(i)) continue;
	        tmp = GetPlayerDistanceFromPoint(i, x, y, z);
			if(tmp >= last) continue;
			last = tmp;
    		id = i;
	    }
	}
	return id;
}

public FCNPC_OnUpdate(npcid)
{
	new Float:x, Float:y, Float:z;
	if(g_CopReferences[npcid] != -1)
	{
		if(e_cops[g_CopReferences[npcid]][cop_time] != gettime())
		{
		    FCNPC_GetPosition(e_cops[g_CopReferences[npcid]][copid], x, y, z);
			for(new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
			{
			    if(!IsPlayerConnected(i) || IsPlayerNPC(i) || GetPlayerInterior(i) != GetCopInterior(g_CopReferences[npcid]) || GetPlayerVirtualWorld(i) != GetCopVirtualWorld(g_CopReferences[npcid])) continue;
				if(GetCopTarget(g_CopReferences[npcid]) == i && GetPlayerWantedLevel(i) == 0 || GetCopTarget(g_CopReferences[npcid]) == i && GetPlayerDistanceFromPoint(i, x, y, z) > GetCopDetectionArea(g_CopReferences[npcid]))
				{
				    FCNPC_Stop(e_cops[g_CopReferences[npcid]][copid]);
			        FCNPC_StopAim(e_cops[g_CopReferences[npcid]][copid]);
			        e_cops[g_CopReferences[npcid]][cop_target] = 0xFFFF;
			        e_cops[g_CopReferences[npcid]][cop_time] = gettime();
			    }
			    else
			    {
			        if(GetPlayerWantedLevel(i) >= 1 && GetPlayerDistanceFromPoint(i, x, y, z) <= GetCopDetectionArea(g_CopReferences[npcid]))
			        {
			    		CopAttackPlayer(g_CopReferences[npcid], i);
			    		if(GetPlayerDistanceFromPoint(i, x, y, z) >= GetCopDetectionArea(g_CopReferences[npcid])/2)
			    		{
			    			FCNPC_GoToPlayer(e_cops[g_CopReferences[npcid]][copid], i, FCNPC_MOVE_TYPE_AUTO, FCNPC_MOVE_SPEED_AUTO, FCNPC_MOVE_MODE_COLANDREAS, FCNPC_MOVE_PATHFINDING_RAYCAST, 5.0, true, 3.0, 1.5, 250);
			    			e_cops[g_CopReferences[npcid]][cop_time] = gettime();
			    		}
		    			e_cops[g_CopReferences[npcid]][cop_time] = gettime();
					}
				}
			}
		}
	}

	#if defined cops_FCNPC_OnUpdate
		return cops_FCNPC_OnUpdate(npcid);
	#else
		return 1;
	#endif
}
#if defined _ALS_FCNPC_OnUpdate
	#undef FCNPC_OnUpdate
#else
	#define _ALS_FCNPC_OnUpdate
#endif
#define FCNPC_OnUpdate cops_FCNPC_OnUpdate
#if defined cops_FCNPC_OnUpdate
	forward cops_FCNPC_OnUpdate(npcid);
#endif

forward OnCopTakeDamage(cop_id, damagerid, weaponid, bodypart, Float:health_loss);

public FCNPC_OnTakeDamage(npcid, issuerid, Float:amount, weaponid, bodypart)
{
	if(issuerid == 0xFFFF) return 1;
    if(g_CopReferences[npcid] != -1)
    {
		CallLocalFunction("OnCopTakeDamage", "iiiif", g_CopReferences[npcid], issuerid, weaponid, bodypart, amount);
	}

	#if defined cops_FCNPC_OnTakeDamage
		return cops_FCNPC_OnTakeDamage(npcid, issuerid, Float:amount, weaponid, bodypart);
	#else
		return 1;
	#endif
}
#if defined _ALS_FCNPC_OnTakeDamage
	#undef FCNPC_OnTakeDamage
#else
	#define _ALS_FCNPC_OnTakeDamage
#endif
#define FCNPC_OnTakeDamage cops_FCNPC_OnTakeDamage
#if defined cops_FCNPC_OnTakeDamage
	forward cops_FCNPC_OnTakeDamage(npcid, issuerid, Float:amount, weaponid, bodypart);
#endif

forward OnCopKillPlayer(cop_id, playerid);

public OnPlayerDeath(playerid, killerid, reason)
{
    new Float:x, Float:y, Float:z;
	if(killerid == 0xFFFF) return 1;
	for(new i = 0; i < MAX_COPS; i ++)
	{
	    if(!IsCopValid(i)) continue;
	    if(!IsPlayerNPC(killerid))
	    {
	    	GetCopPos(i, x, y, z);
	    	if(!IsPlayerInRangeOfPoint(playerid, GetCopDetectionArea(i), x, y, z)) continue;
	    	CallLocalFunction("OnCrimeHappenNearCop", "ii", killerid, CRIME_KILL);
	    	break;
		}
		if(IsPlayerNPC(killerid))
		{
		    CallLocalFunction("OnCopKillPlayer", "ii", i, playerid);
		    break;
		}
	}

	#if defined cops_OnPlayerDeath
		return cops_OnPlayerDeath(playerid, killerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath cops_OnPlayerDeath
#if defined cops_OnPlayerDeath
	forward cops_OnPlayerDeath(playerid, killerid, reason);
#endif

forward OnCrimeHappenNearCop(playerid, crime);

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	new Float:x, Float:y, Float:z;
	for(new i = 0; i < MAX_COPS; i ++)
	{
	    if(!IsCopValid(i)) continue;
	    GetCopPos(i, x, y, z);
	    if(!IsPlayerInRangeOfPoint(playerid, GetCopDetectionArea(i), x, y, z)) continue;
	    CallLocalFunction("OnCrimeHappenNearCop", "ii", playerid, CRIME_SHOOT);
	    break;
	}

	#if defined cops_OnPlayerWeaponShot
		return cops_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerWeaponShot
	#undef OnPlayerWeaponShot
#else
	#define _ALS_OnPlayerWeaponShot
#endif
#define OnPlayerWeaponShot cops_OnPlayerWeaponShot
#if defined cops_OnPlayerWeaponShot
	forward cops_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
    new Float:x, Float:y, Float:z;
	if(issuerid == 0xFFFF || IsPlayerNPC(issuerid)) return 0;
	for(new i = 0; i < MAX_COPS; i ++)
	{
	    if(!IsCopValid(i)) continue;
	    GetCopPos(i, x, y, z);
	    if(!IsPlayerInRangeOfPoint(playerid, GetCopDetectionArea(i), x, y, z)) continue;
	    CallLocalFunction("OnCrimeHappenNearCop", "ii", issuerid, CRIME_DAMAGE);
	    break;
	}

	#if defined cops_OnPlayerTakeDamage
		return cops_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart);
	#else
		return 0;
	#endif
}
#if defined _ALS_OnPlayerTakeDamage
	#undef OnPlayerTakeDamage
#else
	#define _ALS_OnPlayerTakeDamage
#endif
#define OnPlayerTakeDamage cops_OnPlayerTakeDamage
#if defined cops_OnPlayerTakeDamage
	forward cops_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart);
#endif

DestroyAllCops()
{
    for(new i = 0; i < MAX_COPS; i++)
	{
	    if(!IsCopValid(i)) continue;
		DestroyCop(i);
	}
	return 1;
}

stock SetCopInvulnerable(cop_id, bool:invulnerable)
{
	if(IsCopValid(cop_id))
	{
		FCNPC_SetInvulnerable(e_cops[cop_id][copid], invulnerable);
		return 1;
	}
	return 0;
}

stock bool:IsCopInvulnerable(cop_id)
{
    if(IsCopValid(cop_id))
	{
		return FCNPC_IsInvulnerable(e_cops[cop_id][copid]);
	}
	return false;
}

stock SetCopSkin(cop_id, skinid)
{
	if(IsCopValid(cop_id))
	{
	    FCNPC_SetSkin(e_cops[cop_id][copid], skinid);
	    return 1;
	}
	return 0;
}

stock GetCopSkin(cop_id)
{
    if(IsCopValid(cop_id))
	{
	    return FCNPC_GetSkin(e_cops[cop_id][copid]);
	}
	return -1;
}

stock GetCopCustomSkin(cop_id)
{
	if(IsCopValid(cop_id))
	{
	    return FCNPC_GetCustomSkin(e_cops[cop_id][copid]);
	}
	return -1;
}

#if defined FILTERSCRIPT

public OnFilterScriptExit()
{
	DestroyAllCops();

	#if defined cops_OnFilterScriptExit
		return cops_OnFilterScriptExit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit cops_OnFilterScriptExit
#if defined cops_OnFilterScriptExit
	forward cops_OnFilterScriptExit();
#endif

#else

public OnGameModeExit()
{
	DestroyAllCops();

	#if defined cops_OnGameModeExit
		return cops_OnGameModeExit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit cops_OnGameModeExit
#if defined cops_OnGameModeExit
	forward cops_OnGameModeExit();
#endif

#endif


//EOF.