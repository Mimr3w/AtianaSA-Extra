/*
 * @version   : 1.1
 * @author    : willsuckformoney (FrosTiC)
 * @date      : September 4, 2010
 * @update    : September 30, 2010
 *
 * The basics and the Funcions/Uses.
 *
 * What can use?
 * CityCreateForPlayer(cityname[], playerid, Float:minx, Float:miny, Float:maxx, Float:maxy)		cityname[] = "NAME"     Create-A-City
 * CityCreate(cityname[], Float:minx, Float:miny, Float:maxx, Float:maxy)		cityname[] = "NAME"     Create-A-City
 * IsPlayerInCity(playerid, cityid);
 * DestroyCity(cityid);
 * GetPlayerCity(playerid);
 * |* REMOVED *|
 *
 * Callbacks
 *
 * OnPlayerEnterCity(playerid,cityid)
 * OnPlayerExitCity(playerid,cityid)
 * Those are needed in the script in order to compile.
*/

#include <a_samp>

#define MAX_CITIES 100 			//Max amount of Cities
#define INVALID_CITY -1

enum CInfo
{
	CName[45],
	Float:CminX,
	Float:CmaxX,
	Float:CminY,
	Float:CmaxY,
	Valid,
	CColor,
}
new CityInfo[MAX_CITIES][CInfo];

new CityTimer;
new PlayerInCity[MAX_PLAYERS];

forward OnPlayerEnterCity(playerid,cityid);
forward OnPlayerExitCity(playerid,cityid);
forward TimerVCity();

public TimerVCity()
{
	for(new i=0;i<MAX_PLAYERS;i++)
	{
	    if(IsPlayerConnected(i))
	    {
			if(PlayerInCity[i] == INVALID_CITY)
			{
			    for(new a=0;a<MAX_CITIES;a++)
			    {
					if(IsPlayerInCity(i,a))
					{
						PlayerInCity[i] = a;
						OnPlayerEnterCity(i, a);
					}
				}
			}
			else
			{
				if(!IsPlayerInCity(i,PlayerInCity[i]))
				{
					OnPlayerExitCity(i, PlayerInCity[i]);
					PlayerInCity[i] = INVALID_CITY;
				}
			}
		}
	}
	return 1;
}

stock CityCreateForPlayer(cityname[], playerid, Float:minx, Float:miny, Float:maxx, Float:maxy)
{
	if(IsPlayerConnected(playerid))
	{
		for(new c=0;c<MAX_CITIES;c++)
		{
		    if(CityInfo[c][Valid] == 0)
		    {
				CityInfo[c][CName] = cityname[45];
				CityInfo[c][CminX] = minx;
				CityInfo[c][CmaxX] = maxx;
				CityInfo[c][CminY] = miny;
				CityInfo[c][CmaxY] = maxy;
				CityInfo[c][Valid] = 1;
				CityInfo[c][CColor] = -1;
				return c;
			}
		}
	}
	return INVALID_CITY;
}

stock CityCreate(cityname[], Float:minx, Float:miny, Float:maxx, Float:maxy)
{
	for(new c=0;c<MAX_CITIES;c++)
	{
		if(CityInfo[c][Valid] == 0)
		{
			CityInfo[c][CName] = cityname[45];
			CityInfo[c][CminX] = minx;
			CityInfo[c][CmaxX] = maxx;
			CityInfo[c][CminY] = miny;
			CityInfo[c][CmaxY] = maxy;
			CityInfo[c][Valid] = 1;
			CityInfo[c][CColor] = -1;
			return c;
		}
	}
	return INVALID_CITY;
}

stock DestroyCity(cityid)
{
	if(cityid < 0 || cityid > MAX_CITIES) return false;
	if(CityInfo[cityid][Valid] == 1)
	{
		CityInfo[cityid][CminX] = 0;
		CityInfo[cityid][CmaxX] = 0;
		CityInfo[cityid][CminY] = 0;
		CityInfo[cityid][CmaxY] = 0;
		CityInfo[cityid][Valid] = 0;
		for(new i=0;i<MAX_PLAYERS;i++)
		{
		    if(IsPlayerConnected(i))
		    {
		        if(GetPlayerCity(i) == cityid)
		        {
		            PlayerInCity[i] = INVALID_CITY;
		        }
		    }
		}
		return true;
	}
	return false;
}


stock IsPlayerInCity(playerid, cityid)
{
    if(cityid < 0 || cityid > MAX_CITIES) return false;
	if(CityInfo[cityid][Valid] == 1)
	{
		new Float:x,Float:y,Float:z;
		GetPlayerPos(playerid, x,y,z);
		if (x > CityInfo[cityid][CminX] && x < CityInfo[cityid][CmaxX] && y > CityInfo[cityid][CminY] && y < CityInfo[cityid][CmaxY]) return true;
	}
	return false;
}

stock GetPlayerCity(playerid)
{
	return PlayerInCity[playerid];
}

//
stock C_Startup()
{
	CityTimer = SetTimer("TimerVCity",500,1);
	return 1;
}

stock C_End()
{
	KillTimer(CityTimer);
	return 1;
}

C_OnPlayerConnect(playerid)
{
	PlayerInCity[playerid] = INVALID_CITY;
	return 1;
}

C_OnPlayerDisconnect(playerid)
{
	PlayerInCity[playerid] = INVALID_CITY;
	return 1;
}