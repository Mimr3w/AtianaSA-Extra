#include a_samp// Anti-Slide bug include by RogueDrifter 2017-12-13

new slideremove[MAX_PLAYERS],slidecheck[MAX_PLAYERS];
new bool:possibleslide[MAX_PLAYERS];

forward RemoveSlideCheck(playerid);
forward CheckPlayerSlide(playerid);
forward OnPlayerConnectAS(playerid);
forward OnPlayerDisconnectAS(playerid,reason);
forward OnPlayerKeyStateChangeAS(playerid,newkeys,oldkeys);
public CheckPlayerSlide(playerid)
{
	if(GetPlayerOnFootSpeed(playerid) >15 && GetPlayerSurfingVehicleID(playerid) == INVALID_VEHICLE_ID && IsPAiming(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && possibleslide[playerid] && 22<=GetPlayerWeapon(playerid)<=38)
	{
		CallLocalFunction("OnPlayerSlide", "d", playerid);
		}
	return 1;
}
public RemoveSlideCheck(playerid)
{
	KillTimer(slideremove[playerid]);
	possibleslide[playerid] =false;
	return 1;
}
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if( (newkeys & 128) && ( newkeys & 8)  && (newkeys & 2))
	{
		possibleslide[playerid] =true;
		KillTimer(slideremove[playerid]);
		slideremove[playerid] =	SetTimerEx("RemoveSlideCheck",2000,false,"i",playerid);
		}
	#if defined OnPlayerKeyStateChangeAS
  	return OnPlayerKeyStateChangeAS(playerid, newkeys,oldkeys);
  	#else
  	return 1;
  	#endif
}
public OnPlayerConnect(playerid)
{
	slidecheck[playerid] = SetTimerEx("CheckPlayerSlide",1000,true,"d",playerid);
	#if defined OnPlayerConnectAS
  	return OnPlayerConnectAS(playerid);
  	#else
  	return 1;
  	#endif
}
public OnPlayerDisconnect(playerid,reason)
{
	possibleslide[playerid]=false;
	KillTimer(slidecheck[playerid]);
	#if defined OnPlayerDisconnectAS
  	return 	OnPlayerDisconnectAS(playerid,reason);
  	#else
  	return 1;
  	#endif
}

stock GetPlayerOnFootSpeed(playerid)
{
    new Float:ST[4];
    GetPlayerVelocity(playerid,ST[0],ST[1],ST[2]);
    ST[3] = floatsqroot(floatpower(floatabs(ST[0]), 2.0) + floatpower(floatabs(ST[1]), 2.0) + floatpower(floatabs(ST[2]), 2.0)) * 179.28625;
    return floatround(ST[3]);
}
stock IsPAiming(playerid)
{
	new playeranim = GetPlayerAnimationIndex(playerid);
	if (((playeranim >= 1160) && (playeranim <= 1163)) || (playeranim == 1167) || (playeranim == 1365) ||
	(playeranim == 1643) || (playeranim == 1453) || (playeranim == 220)) return 1;
 	return 0;
}

#if defined _ALS_OnPlayerKeyStateChange
  #undef OnPlayerKeyStateChange
#else
#define _ALS_OnPlayerKeyStateChange
#endif

#define OnPlayerKeyStateChange OnPlayerKeyStateChangeAS

#if defined _ALS_OnPlayerConnect
  #undef OnPlayerConnect
#else
#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect OnPlayerConnectAS

#if defined _ALS_OnPlayerDisconnect
  #undef OnPlayerDisconnect
#else
#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect OnPlayerDisconnectAS

#if defined OnPlayerSlide
forward OnPlayerSlide(playerid);
#else
forward OnPlayerSlide(playerid);
new playersliding[MAX_PLAYERS];//ON TOP OF YOUR SCRIPT ( for warnings ) 
public OnPlayerSlide(playerid)//ALL OF THE BELOW ANYWHERE IN UR SCRIPT 
{ 
    new pname[26],stringh[126]; 
    GetPlayerName(playerid, pname, sizeof(pname)); 
    if(playersliding[playerid] <=2) playersliding[playerid]++, 
    format(stringh, sizeof(stringh), ".:Server Has frozen %s WARNING %d , Reason: SLIDE-BUGGING:.", pname,playersliding[playerid]); 
    if(playersliding[playerid]==3) format(stringh, sizeof(stringh), ".:Server Has kicked %s , Reason: SLIDE-BUGGING :.", pname); 
    SendClientMessageToAll(-1,stringh); 
    TogglePlayerControllable(playerid,0);//freezing because slap can bug and warnings are safe & ban is too brutal for a bug. 
    SetTimerEx("CheckP",500,false,"d",playerid);//timer for kick/unfreeze 
    return 1; 
} 
forward CheckP(playerid); 
public CheckP(playerid) 
{ 
    if(playersliding[playerid] ==3) playersliding[playerid] =0, Kick(playerid);//reset & kick on 3rd warning 
    else TogglePlayerControllable(playerid,1);//unfreeze in the first 2 warnings. 
    return 1; 
}
#endif