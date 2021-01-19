/*
 *  s_actors.inc version no YSI.
 *  Create actors unlimitedly!
 *
 *  Thanks for the base include:
 *    Emmet_,
 *    Abagail,
 *    Kar,
 *    kvanningsen,
 *    ziggi.
 *
 *  LatinZ: Restructuring of the entire code and new features added.
 *
 *  Created on April 30, 2015 @ 7:21 AM.
 *  Last updated on 06/07/2016 9:40 PM.
*/

// Maximum amount of allocated slots.
#if !defined MAX_DYNAMIC_ACTORS
	#define MAX_DYNAMIC_ACTORS (2000)
#endif

// Maximum stream distance.
#if !defined MAX_ACTOR_STREAM_DISTANCE
	#define MAX_ACTOR_STREAM_DISTANCE (50.0) // Distance which the actor is removed recommend 50 meters and it is not so far and so close.
#endif

// " task " for check actor's.
#if !defined ACTOR_STREAM_TICK_RATE
	#define ACTOR_STREAM_TICK_RATE (250) // 250 miliseconds. 
#endif

// Maximum actor's per area

#if !defined MAX_ACTORS_AREA
	#define MAX_ACTORS_AREA (50) // 50 actors per area, Not exceed 50 or emerge bug's strange.
#endif

// Height of label NAME.

#if !defined HEIGHT_LABEL_NAME
	#define HEIGHT_LABEL_NAME (1.1) // Recommended 1.1, default height of the players.
#endif

// Viewing distance to the label name.

#if !defined VIEWING_DISTANCE_LABEL_NAME
	#define VIEWING_DISTANCE_LABEL_NAME (15.0) // 15 meters, change to taste.
#endif

// Height of label " say ".

#if !defined HEIGHT_LABEL_SAY
	#define HEIGHT_LABEL_SAY (1.2) // Recommended 1.2, change to taste.
#endif

// Viewing distance to the label " say ".

#if !defined VIEWING_DISTANCE_LABEL_SAY
	#define VIEWING_DISTANCE_LABEL_SAY (20.0) // 20 meters, change to taste.
#endif

// Viewing distance to the label " say ".

#if !defined TIME_HIDE_LABEL_SAY
	#define TIME_HIDE_LABEL_SAY (5000) // 5 seconds... change to taste.
#endif

// Time of spawn (function SpawnDynamicActor)

#if !defined TIME_DEFAULT_SPAWN
	#define TIME_DEFAULT_SPAWN (4000) // 4 seconds... change to taste.
#endif

// Internal defines

#define MAX_DYNAMIC_ACTOR_ANIM_LIB_NAME (32)
#define MAX_DYNAMIC_ACTOR_ANIM_NAME (32)

enum e_DynamicActors {
	e_iName[MAX_PLAYER_NAME],
	e_iColor,
	e_iActorModel,
	e_iActorWorld,
	e_iActorID,
	e_iTimer,
	bool:e_iSlotUsed,
	bool:e_Destroy,
	bool:e_bInvulnerable,
	Float:e_fActorX,
	Float:e_fActorY,
	Float:e_fActorZ,
	Float:e_fActorA,
	Float:e_fActorHealth,
	Float:e_fOffSetLabel[3],
	STREAMER_TAG_3D_TEXT_LABEL e_iLabel,
	STREAMER_TAG_3D_TEXT_LABEL e_iLabelText,
	STREAMER_TAG_3D_TEXT_LABEL e_iLabelName,
};

enum e_AnimationInfo {
	e_sAnimLibrary[MAX_DYNAMIC_ACTOR_ANIM_LIB_NAME char],
	e_sAnimName[MAX_DYNAMIC_ACTOR_ANIM_NAME char],
	e_iAnimLockX,
	e_iAnimLockY,
	e_iAnimFreeze,
	e_iAnimTime,
	bool:e_bAnimation,
	Float:e_fAnimDelta,
};

static
	s_DynamicActors[MAX_DYNAMIC_ACTORS][e_DynamicActors],
	s_ActorAnimation[MAX_DYNAMIC_ACTORS][e_AnimationInfo];

new
	_actors_amount;

// Loop of actor's

#define _Search_Slot(%0) \
	for(new %0 = 0; %0 < MAX_DYNAMIC_ACTORS; %0 ++)

#define Loop_Only_Dynamic_Actors(%0) \
	for(new %0 = 0; %0 <= _actors_amount; %0 ++)	

forward OnDynamicActorStreamIn(actorid, forplayerid);
forward OnDynamicActorStreamOut(actorid, forplayerid);
forward OnPlayerGiveDamageDynamicActor(playerid, actorid, Float:amount, weaponid, bodypart);
forward OnDynamicActorDeath(actorid, killerid, weaponid);
forward OnDynamicActorSpawn(actorid);

public OnFilterScriptExit()
{
	Loop_Only_Dynamic_Actors(i) {
		if(s_DynamicActors[i][e_iSlotUsed]) DestroyDynamicActor(i);
	}

	#if defined AS_OnFilterScriptExit
		return AS_OnFilterScriptExit();
	#else
		return true;
	#endif
}

public OnGameModeExit()
{
	Loop_Only_Dynamic_Actors(i) {
		if(s_DynamicActors[i][e_iSlotUsed]) DestroyDynamicActor(i);
	}

	#if defined AS_OnGameModeExit
		return AS_OnGameModeExit();
	#else
		return true;
	#endif
}

stock CreateDynamicActor(name[MAX_PLAYER_NAME], modelid, Float:x, Float:y, Float:z, Float:angle, worldid = 0, bool:invulnerable = true, Float:health = 100.0)
{
	new amount = 0;
	#if defined _inc_foreach
		foreach (new i : Player) {
	#else
		for (new i = GetPlayerPoolSize(); i != -1; i--) {
			if (!IsPlayerConnected(i) || IsPlayerNPC(i)) {
				continue;
			}
	#endif
			Loop_Only_Dynamic_Actors(a) {
				if(IsDynamicActorInStreamRange(a, i)) amount++;
				if(amount == MAX_ACTORS_AREA) return printf("It has reached the maximum of actors in area: X: %f Y: %f Z: %f", x, y, z);
			}
		}
		new slot = INVALID_ACTOR_ID;
		_Search_Slot(i) {
			if(!s_DynamicActors[i][e_iSlotUsed]) {
				slot = i;
				break;
			}
		}
		new _name = GetDynamicActorID(name);
		if(slot > 0 && _name >= 0) return false;
		if(slot == INVALID_ACTOR_ID) return false;
	   	s_DynamicActors[slot][e_iName] = name;
		s_DynamicActors[slot][e_iColor] = -1;
		s_DynamicActors[slot][e_iLabelName] = CreateDynamic3DTextLabel(name, -1, x, y, z + HEIGHT_LABEL_NAME, VIEWING_DISTANCE_LABEL_NAME);
		s_DynamicActors[slot][e_iSlotUsed] = true;
		s_DynamicActors[slot][e_iActorModel] = modelid;
		s_DynamicActors[slot][e_fActorX] = x;
		s_DynamicActors[slot][e_fActorY] = y;
		s_DynamicActors[slot][e_fActorZ] = z;
		s_DynamicActors[slot][e_fActorA] = angle;
		s_DynamicActors[slot][e_iActorWorld] = worldid;
		s_DynamicActors[slot][e_bInvulnerable] = invulnerable;
		s_DynamicActors[slot][e_fActorHealth] = health;
		s_DynamicActors[slot][e_iActorID] = CreateActor(s_DynamicActors[slot][e_iActorModel], s_DynamicActors[slot][e_fActorX], s_DynamicActors[slot][e_fActorY], s_DynamicActors[slot][e_fActorZ], s_DynamicActors[slot][e_fActorA]);
		s_DynamicActors[slot][e_Destroy] = false;
		_actors_amount++;
		SetActorVirtualWorld(s_DynamicActors[slot][e_iActorID], worldid);
		SetActorHealth(s_DynamicActors[slot][e_iActorID], health);
		SetActorInvulnerable(s_DynamicActors[slot][e_iActorID], invulnerable);
		s_DynamicActors[slot][e_iTimer] = SetTimerEx("UpdateActorStream", ACTOR_STREAM_TICK_RATE, true, "i", slot);
		return slot;
}

stock IsValidDynamicActor(actorid)
{
	if(actorid < 0 || actorid > MAX_DYNAMIC_ACTORS || !s_DynamicActors[actorid][e_iSlotUsed] || s_DynamicActors[actorid][e_iActorID] == INVALID_ACTOR_ID) return false;
	return true;
}

stock DestroyDynamicActor(actorid)
{
	if(!IsValidDynamicActor(actorid)) return false;
	DestroyActor(s_DynamicActors[actorid][e_iActorID]);
	ClearDynamicActorAnimations(actorid);
	DeleteDynamicActor3DTextLabel(actorid);
	s_DynamicActors[actorid][e_iName] = -1;
	s_DynamicActors[actorid][e_iColor] = -1;
	s_DynamicActors[actorid][e_iSlotUsed] = false;
	s_DynamicActors[actorid][e_iActorModel] = -1;
	s_DynamicActors[actorid][e_fActorX] = -1;
	s_DynamicActors[actorid][e_fActorY] = -1;
	s_DynamicActors[actorid][e_fActorZ] = -1;
	s_DynamicActors[actorid][e_fActorA] = -1;
	s_DynamicActors[actorid][e_iActorWorld] = -1;
	s_DynamicActors[actorid][e_bInvulnerable] = false;
	s_DynamicActors[actorid][e_fActorHealth] = -1;
	s_DynamicActors[actorid][e_iActorID] = INVALID_ACTOR_ID;
	KillTimer(s_DynamicActors[actorid][e_iTimer]);
	_actors_amount--;
	return true;
}

stock IsDynamicActorStreamedIn(actorid, forplayerid)
{
	if(!IsValidDynamicActor(actorid)) return false;
	return IsActorStreamedIn(s_DynamicActors[actorid][e_iActorID], forplayerid);
}

stock IsDynamicActorInStreamRange(actorid, forplayerid)
{
	if(!IsValidDynamicActor(actorid)) return false;
	if(s_DynamicActors[actorid][e_iActorWorld] != GetPlayerVirtualWorld(forplayerid)) return false;
	if(IsPlayerInRangeOfPoint(forplayerid, MAX_ACTOR_STREAM_DISTANCE, s_DynamicActors[actorid][e_fActorX], s_DynamicActors[actorid][e_fActorY], s_DynamicActors[actorid][e_fActorZ])) return true;
	return false;
}

stock SetDynamicActorVirtualWorld(actorid, worldid)
{
	if(!IsValidDynamicActor(actorid) || IsDynamicActorDead(actorid)) return false;
	s_DynamicActors[actorid][e_iActorWorld] = worldid;
	SetActorVirtualWorld(s_DynamicActors[actorid][e_iActorID], worldid);
	return true;
}

stock GetDynamicActorVirtualWorld(actorid)
{
	if(!IsValidDynamicActor(actorid)) return false;
	return s_DynamicActors[actorid][e_iActorWorld];
}

stock ApplyDynamicActorAnimation(actorid, animlib[], animname[], Float:fDelta, loop, lockx, locky, freeze, time)
{
	if(!IsValidDynamicActor(actorid) || IsDynamicActorDead(actorid)) return false;
	if(loop) {
		strpack(s_ActorAnimation[actorid][e_sAnimLibrary], animlib, MAX_DYNAMIC_ACTOR_ANIM_LIB_NAME);
		strpack(s_ActorAnimation[actorid][e_sAnimName], animname, MAX_DYNAMIC_ACTOR_ANIM_NAME);
		s_ActorAnimation[actorid][e_bAnimation] = true;
		s_ActorAnimation[actorid][e_fAnimDelta] = fDelta;
		s_ActorAnimation[actorid][e_iAnimLockX] = lockx;
		s_ActorAnimation[actorid][e_iAnimLockY] = locky;
		s_ActorAnimation[actorid][e_iAnimFreeze] = freeze;
		s_ActorAnimation[actorid][e_iAnimTime] = time;
		ApplyActorAnimation(s_DynamicActors[actorid][e_iActorID], animlib, animname, fDelta, loop, lockx, locky, freeze, time);
	}
	return ApplyActorAnimation(s_DynamicActors[actorid][e_iActorID], animlib, animname, fDelta, loop, lockx, locky, freeze, time);
}

stock ClearDynamicActorAnimations(actorid)
{
	if(!IsValidDynamicActor(actorid)) return false;
	if(s_ActorAnimation[actorid][e_bAnimation]) 
	{
		s_ActorAnimation[actorid][e_bAnimation] = false;
		s_ActorAnimation[actorid][e_fAnimDelta] = 0.0;
		s_ActorAnimation[actorid][e_iAnimLockX] = 0;
		s_ActorAnimation[actorid][e_iAnimLockY] = 0;
		s_ActorAnimation[actorid][e_iAnimFreeze] = 0;
		s_ActorAnimation[actorid][e_iAnimTime] = 0;
	}
	return ClearActorAnimations(s_DynamicActors[actorid][e_iActorID]);
}

stock SetDynamicActorPos(actorid, Float:x, Float:y, Float:z)
{
	if(!IsValidDynamicActor(actorid) || IsDynamicActorDead(actorid)) return false;
	s_DynamicActors[actorid][e_fActorX] = x;
	s_DynamicActors[actorid][e_fActorY] = y;
	s_DynamicActors[actorid][e_fActorZ] = z;
	s_DynamicActors[actorid][e_fOffSetLabel][0] = s_DynamicActors[actorid][e_fOffSetLabel][0] + x;
	s_DynamicActors[actorid][e_fOffSetLabel][1] = s_DynamicActors[actorid][e_fOffSetLabel][1] + y;
	s_DynamicActors[actorid][e_fOffSetLabel][2] = s_DynamicActors[actorid][e_fOffSetLabel][2] + z;
	if(IsValidDynamic3DTextLabel(s_DynamicActors[actorid][e_iLabel])) SetDynamic3DTextPos(s_DynamicActors[actorid][e_iLabel], s_DynamicActors[actorid][e_fOffSetLabel][0], s_DynamicActors[actorid][e_fOffSetLabel][1], s_DynamicActors[actorid][e_fOffSetLabel][2]);
	if(IsValidDynamic3DTextLabel(s_DynamicActors[actorid][e_iLabelName])) SetDynamic3DTextPos(s_DynamicActors[actorid][e_iLabelName], x, y, z + HEIGHT_LABEL_NAME);
	return SetActorPos(s_DynamicActors[actorid][e_iActorID], x, y, z);
}

stock GetDynamicActorPos(actorid, &Float:x, &Float:y, &Float:z)
{
	if(!IsValidDynamicActor(actorid)) return false;
	x = s_DynamicActors[actorid][e_fActorX];
	y = s_DynamicActors[actorid][e_fActorY];
	z = s_DynamicActors[actorid][e_fActorZ];
	return true;
}

stock SetDynamicActorFacingAngle(actorid, Float:angle)
{
	if(!IsValidDynamicActor(actorid) || IsDynamicActorDead(actorid)) return false;
	s_DynamicActors[actorid][e_fActorA] = angle;
	return _Debug();
}

stock GetDynamicActorFacingAngle(actorid, &Float:angle)
{
	if(!IsValidDynamicActor(actorid)) return false;
	angle = s_DynamicActors[actorid][e_fActorA];
	return true;
}

stock SetDynamicActorSkin(actorid, skinid)
{
	if(!IsValidDynamicActor(actorid) || IsDynamicActorDead(actorid)) return false;
	s_DynamicActors[actorid][e_iActorModel] = skinid;
	return _Debug();
}

stock GetDynamicActorSkin(actorid)
{
	if(!IsValidDynamicActor(actorid)) return false;
	return s_DynamicActors[actorid][e_iActorModel];
}

stock IsDynamicActorDead(actorid)
{
	if(!IsValidDynamicActor(actorid) || s_DynamicActors[actorid][e_fActorHealth] > 0) return false;
	return true;
}

stock SetDynamicActorHealth(actorid, Float:health)
{
	if(!IsValidDynamicActor(actorid) || s_DynamicActors[actorid][e_bInvulnerable]) return false;
	s_DynamicActors[actorid][e_fActorHealth] = health;
	if(s_DynamicActors[actorid][e_fActorHealth] < 1)
	{
		SetActorHealth(actorid, 0.0);
		s_DynamicActors[actorid][e_fActorHealth] = 0.0;
		return CallLocalFunction("OnPlayerGiveDamageActor", "i", actorid);
	}
	return SetActorHealth(s_DynamicActors[actorid][e_iActorID], health);
}

stock GetDynamicActorHealth(actorid, &Float:health)
{
	if(!IsValidDynamicActor(actorid)) return false;
	return GetActorHealth(s_DynamicActors[actorid][e_iActorID], s_DynamicActors[actorid][e_fActorHealth]);
}

stock SetDynamicActorInvulnerable(actorid, bool:invulnerable = true)
{
	if(!IsValidDynamicActor(actorid) || IsDynamicActorDead(actorid)) return false;
	s_DynamicActors[actorid][e_bInvulnerable] = invulnerable;
	return SetActorInvulnerable(actorid, invulnerable);
}

stock IsDynamicActorInvulnerable(actorid)
{
	if(!IsValidDynamicActor(actorid)) return false;
	if(!s_DynamicActors[actorid][e_bInvulnerable]) return false;
	return true;
}

stock AttachDynamicActor3DTextLabel(actorid, text[], color, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:distance = VIEWING_DISTANCE_LABEL_NAME)
{
    if(!IsValidDynamicActor(actorid) || IsValidDynamic3DTextLabel(s_DynamicActors[actorid][e_iLabel])) return false;
    new Float:pos3D[3];
    GetDynamicActorPos(actorid, pos3D[0], pos3D[1], pos3D[2]);
    s_DynamicActors[actorid][e_fOffSetLabel][0] = fOffsetX;
    s_DynamicActors[actorid][e_fOffSetLabel][1] = fOffsetY;
    s_DynamicActors[actorid][e_fOffSetLabel][2] = (0.8) + fOffsetZ;
    s_DynamicActors[actorid][e_iLabel] = CreateDynamic3DTextLabel(text, color, pos3D[0] + fOffsetX, pos3D[1] + fOffsetY, (pos3D[2] + 0.8) + fOffsetZ, distance); 
    return true; 
}

stock UpdateDynamicActor3DTextLabel(actorid, color, text[])
{
    if(!IsValidDynamicActor(actorid) || !IsValidDynamic3DTextLabel(s_DynamicActors[actorid][e_iLabel])) return false;
    return UpdateDynamic3DTextLabelText(s_DynamicActors[actorid][e_iLabel], color, text);
}

stock DeleteDynamicActor3DTextLabel(actorid)
{
    if(!IsValidDynamicActor(actorid) || !IsValidDynamic3DTextLabel(s_DynamicActors[actorid][e_iLabel])) return false;
    return DestroyDynamic3DTextLabel(s_DynamicActors[actorid][e_iLabel]);
}

stock SetDynamicActorName(actorid, name[MAX_PLAYER_NAME])
{
    if(!IsValidDynamicActor(actorid)) return false;
    s_DynamicActors[actorid][e_iName] = name;
    return UpdateDynamic3DTextLabelText(s_DynamicActors[actorid][e_iLabelName], s_DynamicActors[actorid][e_iColor], name);
}

stock SetDynamicActorColor(actorid, color)
{
    if(!IsValidDynamicActor(actorid)) return false;
    s_DynamicActors[actorid][e_iColor] = color;
    return UpdateDynamic3DTextLabelText(s_DynamicActors[actorid][e_iLabelName], color, s_DynamicActors[actorid][e_iName]);
}

stock GetDynamicActorInternalID(actorid)
{
	if(!IsValidDynamicActor(actorid)) return false;
	return s_DynamicActors[actorid][e_iActorID];
}

stock GetDynamicActorName(actorid)
{
	//if(!IsValidDynamicActor(actorid)) return false;
	new _name[MAX_PLAYER_NAME];
	format(_name, sizeof(_name), "%s", s_DynamicActors[actorid][e_iName]);
	return _name;
}

stock GetDynamicActorID(name[MAX_PLAYER_NAME])
{
	Loop_Only_Dynamic_Actors(a) {
		if(IsValidDynamicActor(a)) {
			if(strcmp(name, s_DynamicActors[a][e_iName], true) == 0) return a;
		}
	}
	return -1;
}

stock IsPlayerInRangeOfDynamicActor(playerid, actorid, Float:range = 7.0)
{
	if(!IsValidDynamicActor(actorid) || s_DynamicActors[actorid][e_iActorWorld] != GetPlayerVirtualWorld(playerid)) return false;
	if(IsPlayerInRangeOfPoint(playerid, range, s_DynamicActors[actorid][e_fActorX], s_DynamicActors[actorid][e_fActorY], s_DynamicActors[actorid][e_fActorZ])) return true;
	return false;
}

stock DynamicActorSay(actorid, text[], color, Float:distance = VIEWING_DISTANCE_LABEL_SAY)
{
    if(!IsValidDynamicActor(actorid) || IsValidDynamic3DTextLabel(s_DynamicActors[actorid][e_iLabelText]) || IsDynamicActorDead(actorid)) return false;
    new Float:pos3D[3];
    GetDynamicActorPos(actorid, pos3D[0], pos3D[1], pos3D[2]);
    s_DynamicActors[actorid][e_iLabelText] = CreateDynamic3DTextLabel(text, color, pos3D[0], pos3D[1], (pos3D[2] + HEIGHT_LABEL_SAY), distance); 
    return SetTimerEx("DeleteDynamicActorSay", TIME_HIDE_LABEL_SAY, false, "i", s_DynamicActors[actorid][e_iActorID]);
}

stock SpawnDynamicActor(actorid, skinid, Float:x, Float:y, Float:z, Float:angle, worldid = 0, bool:invulnerable = true, Float:health = 100.0)
{
	if(!IsValidDynamicActor(actorid)) return false;
 	s_DynamicActors[actorid][e_iActorModel] = skinid;
	s_DynamicActors[actorid][e_fActorX] = x;
	s_DynamicActors[actorid][e_fActorY] = y;
	s_DynamicActors[actorid][e_fActorZ] = z;
	s_DynamicActors[actorid][e_fActorA] = angle;
	s_DynamicActors[actorid][e_iActorWorld] = worldid;
	s_DynamicActors[actorid][e_bInvulnerable] = invulnerable;
	s_DynamicActors[actorid][e_fActorHealth] = health;
	s_DynamicActors[actorid][e_fOffSetLabel][0] = s_DynamicActors[actorid][e_fOffSetLabel][0] + x;
	s_DynamicActors[actorid][e_fOffSetLabel][1] = s_DynamicActors[actorid][e_fOffSetLabel][1] + y;
	s_DynamicActors[actorid][e_fOffSetLabel][2] = s_DynamicActors[actorid][e_fOffSetLabel][2] + z;
 	return SetTimerEx("_SpawnDynamicActor", TIME_DEFAULT_SPAWN, false, "i", s_DynamicActors[actorid][e_iActorID]);
}

stock SetDynamic3DTextPos(Text3D:id,Float:x,Float:y,Float:z) {
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,id,E_STREAMER_X,x);
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,id,E_STREAMER_Y,y);
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,id,E_STREAMER_Z,z);
}

forward UpdateActorStream(actorid);
public UpdateActorStream(actorid)
{
	if(IsValidDynamicActor(actorid)) {
		#if defined _inc_foreach
			foreach (new i : Player) {
		#else
			for (new i = GetPlayerPoolSize(); i != -1; i--) {
				if (!IsPlayerConnected(i) || IsPlayerNPC(i)) {
					continue;
				}
		#endif
			if(!IsDynamicActorInStreamRange(actorid, i)) {
				DestroyActor(s_DynamicActors[actorid][e_iActorID]);
				s_DynamicActors[actorid][e_Destroy] = true;
			}
		}
			if(s_DynamicActors[actorid][e_Destroy] == false) return false;
			_CreateActor(s_DynamicActors[actorid][e_iActorID], s_DynamicActors[actorid][e_iActorModel], s_DynamicActors[actorid][e_fActorA]);
	}
	return true;
}

forward _CreateActor(actorid, skinid, Float:angle);
public _CreateActor(actorid, skinid, Float:angle)
{
	new internal_actor;
	internal_actor = CreateActor(skinid, s_DynamicActors[actorid][e_fActorX], s_DynamicActors[actorid][e_fActorY], s_DynamicActors[actorid][e_fActorZ], angle);
	if(internal_actor == INVALID_ACTOR_ID) return printf("[Error] Could not stream dynamic actor %d. The SA-MP limit has been reached.", actorid);
	if (s_DynamicActors[actorid][e_iActorWorld] != -1) SetActorVirtualWorld(internal_actor, s_DynamicActors[actorid][e_iActorWorld]);
	if(s_ActorAnimation[actorid][e_bAnimation]) {
		ApplyActorAnimation(internal_actor, s_ActorAnimation[actorid][e_sAnimLibrary], s_ActorAnimation[actorid][e_sAnimName], s_ActorAnimation[actorid][e_fAnimDelta], true, s_ActorAnimation[actorid][e_iAnimLockX], s_ActorAnimation[actorid][e_iAnimLockY], s_ActorAnimation[actorid][e_iAnimFreeze], s_ActorAnimation[actorid][e_iAnimTime]);
	}
	else ApplyActorAnimation(internal_actor, s_ActorAnimation[actorid][e_sAnimLibrary], s_ActorAnimation[actorid][e_sAnimName], s_ActorAnimation[actorid][e_fAnimDelta], false, s_ActorAnimation[actorid][e_iAnimLockX], s_ActorAnimation[actorid][e_iAnimLockY], s_ActorAnimation[actorid][e_iAnimFreeze], s_ActorAnimation[actorid][e_iAnimTime]);
	SetActorInvulnerable(internal_actor, s_DynamicActors[actorid][e_bInvulnerable]);
	SetActorHealth(internal_actor, s_DynamicActors[actorid][e_fActorHealth]);
	return s_DynamicActors[actorid][e_Destroy] = false;
}

public OnActorStreamIn(actorid, forplayerid)
{

	if(IsValidDynamicActor(actorid) && s_DynamicActors[actorid][e_iActorID] == actorid) {
		CallLocalFunction("OnDynamicActorStreamIn", "ii", actorid, forplayerid);
	}

	#if defined AS_OnActorStreamIn
		return AS_OnActorStreamIn(actorid, playerid);
	#else
		return true;
	#endif
}

public OnActorStreamOut(actorid, forplayerid)
{

	if(IsValidDynamicActor(actorid) && s_DynamicActors[actorid][e_iActorID] == actorid) {
		CallLocalFunction("OnDynamicActorStreamOut", "ii", actorid, forplayerid);
	}

	#if defined AS_OnActorStreamOut
		return AS_OnActorStreamOut(actorid, playerid);
	#else
		return true;
	#endif
}

public OnPlayerGiveDamageActor(playerid, damaged_actorid, Float:amount, weaponid, bodypart)
{
	if(s_DynamicActors[damaged_actorid][e_bInvulnerable]) return false;
	s_DynamicActors[damaged_actorid][e_fActorHealth] = s_DynamicActors[damaged_actorid][e_fActorHealth] - amount;
	SetActorHealth(s_DynamicActors[damaged_actorid][e_iActorID], s_DynamicActors[damaged_actorid][e_fActorHealth]);
	if(s_DynamicActors[damaged_actorid][e_fActorHealth] < 1)
	{
		ClearDynamicActorAnimations(s_DynamicActors[damaged_actorid][e_iActorID]);
		DeleteDynamicActor3DTextLabel(s_DynamicActors[damaged_actorid][e_iActorID]);
		DeleteDynamicActorSay(s_DynamicActors[damaged_actorid][e_iActorID]);
		SetActorHealth(s_DynamicActors[damaged_actorid][e_iActorID], 0.0);
		s_DynamicActors[damaged_actorid][e_fActorHealth] = 0.0;
		return CallLocalFunction("OnDynamicActorDeath", "iii", damaged_actorid, playerid, weaponid);
	}
	if(IsValidDynamicActor(damaged_actorid) && s_DynamicActors[damaged_actorid][e_iActorID] == damaged_actorid) {
		CallLocalFunction("OnPlayerGiveDamageDynamicActor", "iifii", playerid, damaged_actorid, amount, weaponid, bodypart);
	}

	#if defined AS_OnPlayerGiveDamageActor
		return AS_OnPlayerGiveDamageActor(playerid, damaged_actorid, amount, weaponid, bodypart);
	#else
		return true;
	#endif
}

forward DeleteDynamicActorSay(actorid);
public DeleteDynamicActorSay(actorid)
{
    if(!IsValidDynamicActor(actorid) || !IsValidDynamic3DTextLabel(s_DynamicActors[actorid][e_iLabelText]) || s_DynamicActors[actorid][e_iActorID] == INVALID_ACTOR_ID) return false;
    return DestroyDynamic3DTextLabel(s_DynamicActors[actorid][e_iLabelText]);
}

forward _SpawnDynamicActor(actorid);
public _SpawnDynamicActor(actorid)
{
	if(!IsValidDynamicActor(actorid)) return false;
	if(IsValidDynamic3DTextLabel(s_DynamicActors[actorid][e_iLabel])) SetDynamic3DTextPos(s_DynamicActors[actorid][e_iLabel], s_DynamicActors[actorid][e_fOffSetLabel][0], s_DynamicActors[actorid][e_fOffSetLabel][1], s_DynamicActors[actorid][e_fOffSetLabel][2]);
	if(IsValidDynamic3DTextLabel(s_DynamicActors[actorid][e_iLabelName])) SetDynamic3DTextPos(s_DynamicActors[actorid][e_iLabelName], s_DynamicActors[actorid][e_fActorX], s_DynamicActors[actorid][e_fActorY], s_DynamicActors[actorid][e_fActorZ] + HEIGHT_LABEL_NAME);
	_Debug();
	return CallLocalFunction("OnDynamicActorSpawn", "i", actorid);
}

stock _Debug()
{
	Loop_Only_Dynamic_Actors(actorid) {
		if(IsValidDynamicActor(actorid)) {
			DestroyActor(s_DynamicActors[actorid][e_iActorID]);
			s_DynamicActors[actorid][e_Destroy] = true;
		}
	}
	return true;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif

#define OnFilterScriptExit AS_OnFilterScriptExit

#if defined AS_OnFilterScriptExit
	forward AS_OnFilterScriptExit();
#endif

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif

#define OnGameModeExit AS_OnGameModeExit

#if defined AS_OnGameModeExit
	forward AS_OnGameModeExit();
#endif

#if defined _ALS_OnActorStreamIn
	#undef OnActorStreamIn
#else
	#define _ALS_OnActorStreamIn
#endif

#define OnActorStreamIn AS_OnActorStreamIn

#if defined AS_OnActorStreamIn
	forward AS_OnActorStreamIn(actorid, playerid);
#endif

#if defined _ALS_OnActorStreamOut
	#undef OnActorStreamOut
#else
	#define _ALS_OnActorStreamOut
#endif

#define OnActorStreamOut AS_OnActorStreamOut

#if defined AS_OnActorStreamOut
	forward AS_OnActorStreamOut(actorid, playerid);
#endif

#if defined _ALS_OnPlayerGiveDamageActor
	#undef OnPlayerGiveDamageActor
#else
	#define _ALS_OnPlayerGiveDamageActor
#endif

#define OnPlayerGiveDamageActor AS_OnPlayerGiveDamageActor

#if defined AS_OnPlayerGiveDamageActor
	forward AS_OnPlayerGiveDamageActor(playerid, damaged_actorid, Float:amount, weaponid, bodypart);
#endif