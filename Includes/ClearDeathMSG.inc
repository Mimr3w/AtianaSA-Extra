// clear death message after x seconds
#define 	CLEAR_AFTER		15

// end of settings

#include <a_samp>
#include <YSI\y_hooks>
#include <foreach>

new clear_time[MAX_PLAYERS];

hook OnGameModeInit()
{
	SetTimer("cdm_timer", 1000, true);
    return 1;
}

hook OnPlayerConnect(playerid)
{
	clear_time[playerid] = 0;
}

stock cdm_SendDeathMessage(killer, killee, weapon)
{
	foreach(Player, playerid)
	{
		clear_time[playerid] = gettime() + CLEAR_AFTER;
		SendDeathMessage(killer, killee, weapon);
	}
    return 1;
}

#if defined _ALS_SendDeathMessage
    #undef SendDeathMessage
#else
    #define _ALS_SendDeathMessage
#endif
#define SendDeathMessage cdm_SendDeathMessage

stock cdm_SendDeathMessageToPlayer(playerid, killer, killee, weapon)
{
	clear_time[playerid] = gettime() + CLEAR_AFTER;
	SendDeathMessageToPlayer(playerid, killer, killee, weapon);

    return 1;
}

#if defined _ALS_SendDeathMessageToPlayer
    #undef SendDeathMessageToPlayer
#else
    #define _ALS_SendDeathMessageToPlayer
#endif
#define SendDeathMessageToPlayer cdm_SendDeathMessageToPlayer



forward cdm_timer();
public cdm_timer()
{
	foreach(Player, playerid)
	{
		if(clear_time[playerid] != 0 && clear_time[playerid] < gettime())
		{
			for(new i = 0; i < 5; i++)
			{
				SendDeathMessageToPlayer(playerid, 1001, 1001, 200);
			}
		}
	}
}