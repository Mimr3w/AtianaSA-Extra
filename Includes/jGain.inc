 /************************************************
 *				gain effect v1.1				 *
 *						                         *
 *        (c) Copyright 2014, Jstylezzz          *
 *  		This file is provided as is.         *
 *												 *
 ************************************************/
 
#if defined _jgain_included
  #endinput
#endif
#define _jgain_included

//=== NEW'S ===//
new jb_gaintimer[MAX_PLAYERS];
new jb_gainCount[MAX_PLAYERS];
new Text:jb_gainDraw[MAX_PLAYERS];
new bjDrawCreated[MAX_PLAYERS];

//=== FORWARDS ===//

forward jb_getgainColor(playerid);

//=== PUBLICS ===//

public jb_getgainColor(playerid)
{
    TextDrawHideForPlayer(playerid,jb_gainDraw[playerid]);
	new newhex[128],endhex;
	if(jb_gainCount[playerid] < 10)
	{
		format(newhex,128,"0x00FF000%d",jb_gainCount[playerid]);
	}
	if(jb_gainCount[playerid] > 10)
	{
		format(newhex,128,"0x00FF00%d",jb_gainCount[playerid]);
	}
	sscanf(newhex, "x", endhex);
	TextDrawBoxColor(jb_gainDraw[playerid],endhex);
	jb_gainCount[playerid]--;
	TextDrawShowForPlayer(playerid,jb_gainDraw[playerid]);
	if(jb_gainCount[playerid]== 0) {KillTimer(jb_gaintimer[playerid]); TextDrawHideForPlayer(playerid,jb_gainDraw[playerid]);}
	return 1;
}

//=== STOCKS ===//
stock ShowGainScreen(playerid,Float:amount, shadetimer = 100)
{
		CheckbjDraw(playerid);
		KillTimer(jb_gaintimer[playerid]);
        TextDrawHideForPlayer(playerid,jb_gainDraw[playerid]);
		jb_gainCount[playerid] = floatround(amount);
		new newhex[128],endhex;
		if(jb_gainCount[playerid] < 10)
		{
			format(newhex,128,"0x00FF000%d",jb_gainCount[playerid]);
		}
		if(jb_gainCount[playerid] > 10)
		{
			format(newhex,128,"0x00FF00%d",jb_gainCount[playerid]);
		}
		sscanf(newhex, "x", endhex);
		TextDrawBoxColor(jb_gainDraw[playerid],endhex);
		TextDrawShowForPlayer(playerid,jb_gainDraw[playerid]);
		jb_gaintimer[playerid] = SetTimerEx("jb_getgainColor",shadetimer,1,"i",playerid);
}

stock CheckbjDraw(playerid) //Check if the textdraw is created, if not, create it
{
	if(bjDrawCreated[playerid] == 0)
	{
		jb_gainDraw[playerid] = TextDrawCreate(643.000000, 1.500000, "usebox");
		TextDrawLetterSize(jb_gainDraw[playerid], 0.000000, 49.396297);
		TextDrawTextSize(jb_gainDraw[playerid], -2.000000, 0.000000);
		TextDrawAlignment(jb_gainDraw[playerid], 1);
		TextDrawColor(jb_gainDraw[playerid], 0);
		TextDrawUseBox(jb_gainDraw[playerid], true);
		TextDrawBoxColor(jb_gainDraw[playerid], -16777166);
		TextDrawSetShadow(jb_gainDraw[playerid], 0);
		TextDrawSetOutline(jb_gainDraw[playerid], 0);
		TextDrawFont(jb_gainDraw[playerid], 0);
		bjDrawCreated[playerid] = 1;
	}
}