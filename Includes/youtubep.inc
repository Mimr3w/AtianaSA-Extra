//==============================================================================
//                Youtube Stream Function By 4nDrEi95
//==============================================================================
#pragma tabsize 0
stock CustomStream(playerid, vlink[])
{
	new videoid[128], mp3link[128];
	if(strfind(vlink,"v=") != -1)
	{
		strmid(videoid,vlink,strfind(vlink,"v=")+2,strfind(vlink,"v=")+15);
		format(mp3link,128,"http://youtubeplaylist-mp3.com/download/index/%s",videoid);
		PlayAudioStreamForPlayer(playerid, mp3link);
	}
	else PlayAudioStreamForPlayer(playerid, vlink);
	return 1;
}