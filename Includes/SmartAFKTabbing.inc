/*
			+-----------------------------------------------------------+
			|                     Smart AFK Tabbing                     |
			|                       by varthshenon                      |
			|                        <<<<<<>>>>>>                       |
			|                             V1                            |
			|http://forum.sa-mp.com/showthread.php?t=281590             |
			|Stay tuned folks                                           |
			+-----------------------------------------------------------+
																					*/
#if defined _SmartAFKTabbing
	#endinput
#endif
#define _SmartAFKTabbing

#include <a_samp>

#if !defined AltTabbing
	#define AltTabbing 500
#endif

#if !defined AFKing
	#define AFKing 600000
#endif

#if !defined Range
	#define Range 20
#endif

new bool:IsPlayerAltTabbing[MAX_PLAYERS char],
	bool:IsPlayerAFKing[MAX_PLAYERS char],
	bool:IsPlayerMacroing[MAX_PLAYERS char],
	SAFKTTimer[MAX_PLAYERS][3],
	SAFKTCount[MAX_PLAYERS char],
	Float:SAFKTFloat[MAX_PLAYERS][3],
	Float:SAFKTFloats[3];

forward AltTabber(playerid);
forward AFKer(playerid);
forward Macroer(playerid);

#if !defined FILTERSCRIPT
public OnGameModeInit()
{
	print( "       +-----------------------------------------------------------+       " );
	print( "       |                     Smart AFK Tabbing                     |       " );
	print( "       |                       by varthshenon                      |       " );
	print( "       |                        <<<<<<>>>>>>                       |       " );
	print( "       |                             V1                            |       " );
	print( "       |http://forum.sa-mp.com/showthread.php?t=281590             |       " );
	print( "       |Stay tuned folks                                           |       " );
	print( "       |Thanks to Y_Less for his foreach and y_ini                 |       " );
	print( "       +-----------------------------------------------------------+       " );
	return CallLocalFunction("SAT_OnGameModeInit","");
}

public OnGameModeExit()
{
	print( "       +-----------------------------------------------------------+       " );
	print( "       |                     Smart AFK Tabbing                     |       " );
	print( "       +-----------------------------------------------------------+       " );
	return CallLocalFunction("SAT_OnGameModeExit","");
}
#else
public OnFilterScriptInit()
{
	print( "       +-----------------------------------------------------------+       " );
	print( "       |                     Smart AFK Tabbing                     |       " );
	print( "       |                       by varthshenon                      |       " );
	print( "       |                        <<<<<<>>>>>>                       |       " );
	print( "       |                             V1                            |       " );
	print( "       |http://forum.sa-mp.com/showthread.php?t=281590             |       " );
	print( "       |Stay tuned folks                                           |       " );
	print( "       |Thanks to Y_Less for his foreach and y_ini                 |       " );
	print( "       +-----------------------------------------------------------+       " );
	return CallLocalFunction("SAT_OnFilterScriptInit","");
}

public OnFilterScriptExit()
{
	print( "       +-----------------------------------------------------------+       " );
	print( "       |                     Smart AFK Tabbing                     |       " );
	print( "       +-----------------------------------------------------------+       " );
	return CallLocalFunction("SAT_OnFilterScriptExit","");
}
#endif

public OnPlayerConnect(playerid)
{
	SAFKTTimer[playerid][0] = SetTimerEx("AltTabber",AltTabbing,1,"d",playerid);
	SAFKTTimer[playerid][1] = SetTimerEx("AFKer",AFKing/10,1,"d",playerid);
	return CallLocalFunction("SAT_OnPlayerConnect","d",playerid);
}

public OnPlayerDisconnect(playerid,reason)
{
	KillTimer(SAFKTTimer[playerid][0]);
	KillTimer(SAFKTTimer[playerid][1]);
	KillTimer(SAFKTTimer[playerid][2]);
	return CallLocalFunction("SAT_OnPlayerDisconnect","dd",playerid,reason);
}

public OnPlayerUpdate(playerid)
{
	IsPlayerAltTabbing{playerid} = false;
	return CallLocalFunction("SAT_OnPlayerUpdate","d",playerid);
}

public AltTabber(playerid)
{
	IsPlayerAltTabbing{playerid} = true;
	return 1;
}

public AFKer(playerid)
{
	if(IsPlayerAltTabbing{playerid})
	{
		IsPlayerAFKing{playerid} = false;
		return 1;
	}
	GetPlayerPos(playerid,SAFKTFloats[0],SAFKTFloats[1],SAFKTFloats[2]);
	if(SAFKTFloat[playerid][0] == SAFKTFloats[0] && SAFKTFloat[playerid][1] == SAFKTFloats[1] && SAFKTFloat[playerid][2] == SAFKTFloats[2])
	{
		SAFKTCount{playerid}++;
		if(SAFKTCount{playerid} == 10 && IsPlayerAltTabbing{playerid} == false) IsPlayerAFKing{playerid} = true;
	}
	else
	{
		SAFKTTimer[playerid][2] = SetTimerEx("Macroer",AFKing - 1000,0,"d",playerid);
		IsPlayerAFKing{playerid} = false;
		SAFKTCount{playerid} = 0;
	}
	SAFKTFloat[playerid][0] = SAFKTFloats[0];
	SAFKTFloat[playerid][1] = SAFKTFloats[1];
	SAFKTFloat[playerid][2] = SAFKTFloats[2];
	return 1;
}

public Macroer(playerid)
{
	IsPlayerMacroing{playerid} = (IsPlayerInRangeOfPoint(playerid,Range,SAFKTFloat[playerid][0],SAFKTFloat[playerid][1] = SAFKTFloats[1],SAFKTFloat[playerid][2] = SAFKTFloats[2])) ? true : false;
	return 1;
}

#if !defined FILTERSCRIPT
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit SAT_OnGameModeInit
forward OnGameModeInit();

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit SAT_OnGameModeExit
forward OnGameModeExit();
#else
#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit SAT_OnFilterScriptInit
forward OnFilterScriptInit();

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit SAT_OnFilterScriptExit
forward OnFilterScriptExit();
#endif

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect SAT_OnPlayerConnect
forward OnPlayerConnect(playerid);

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect SAT_OnPlayerDisconnect
forward OnPlayerDisconnect(playerid,reason);

#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate SAT_OnPlayerUpdate
forward OnPlayerUpdate(playerid);