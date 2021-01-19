/*
             Prohibido TOTALMENTE el Robo de Créditos o la
              Publicación de este INCLUDE sin Mi Permiso.

                     FULLY spaces Theft Credit or
           Publication of this INCLUDE without my permission.

	SIMPLE INCLUDE --> Campfire in SA-MP 'Object'
	CREDITOS: OTACON ;)
	NOTA: Menos Creditos para los que me los critican.. JO'PUTAS! :D xD ;)
	
native CreateObjectCampfire(&slots, &Float:x, &Float:y, &Float:z, &Float:a); //to create the object of the campfire.
native DestroyObjectCampfire(&slots); //to destroy the object of the campfire.
native IsPlayerInRangeOfFire(playerid, &Float:distance); //to see if the player is close to the object of the campfire.
*/
// ========== [ -|- FUNCTION -|- ] ==========
#define MAX_SLOTS (50)
new ObjectCampfire[MAX_SLOTS][8];
stock DestroyObjectCampfire(slots) {
	DestroyObject(ObjectCampfire[slots][0]);
	DestroyObject(ObjectCampfire[slots][1]);
	DestroyObject(ObjectCampfire[slots][2]);
	DestroyObject(ObjectCampfire[slots][3]);
	DestroyObject(ObjectCampfire[slots][4]);
	DestroyObject(ObjectCampfire[slots][5]);
	DestroyObject(ObjectCampfire[slots][6]);
	DestroyObject(ObjectCampfire[slots][7]);
}
stock CreateObjectCampfire(slots, Float:x, Float:y, Float:z, Float:a) {
	ObjectCampfire[slots][0]=CreateObject(841, x, y, z-1, 0.000, 0.000, a);
	ObjectCampfire[slots][1]=CreateObject(841, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	ObjectCampfire[slots][2]=CreateObject(841, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	ObjectCampfire[slots][3]=CreateObject(18688, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	ObjectCampfire[slots][4]=CreateObject(18688, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	ObjectCampfire[slots][5]=CreateObject(18688, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	ObjectCampfire[slots][6]=CreateObject(18688, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	ObjectCampfire[slots][7]=CreateObject(18688, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
    AttachObjectToObject(ObjectCampfire[slots][1], ObjectCampfire[slots][0], 0, -0.5, 0, 0, 0, 0, 1);
    AttachObjectToObject(ObjectCampfire[slots][2], ObjectCampfire[slots][0], 0, -0.5, 0, 0, 0, 90, 1);
    AttachObjectToObject(ObjectCampfire[slots][3], ObjectCampfire[slots][0], 0.5, -0.5, -2, 0, 0, 0, 1);
    AttachObjectToObject(ObjectCampfire[slots][4], ObjectCampfire[slots][0], -0.5, -0.5, -2, 0, 0, 0, 1);
    AttachObjectToObject(ObjectCampfire[slots][5], ObjectCampfire[slots][0], 0, -0.5, -2, 0, 0, 0, 1);
    AttachObjectToObject(ObjectCampfire[slots][6], ObjectCampfire[slots][0], 0, -0.5, -2, 0, 0, 0, 1);
    AttachObjectToObject(ObjectCampfire[slots][7], ObjectCampfire[slots][0], 0, -0.5, -2, 0, 0, 0, 1);
}
stock IsPlayerInRangeOfFire(playerid, Float:distance) {
    new Float:posfire[4], Float:playerfire[3];
    for(new slots=0; slots<MAX_SLOTS; slots++) {
        if(!IsValidObject(ObjectCampfire[slots][0])) continue;
        GetPlayerPos(playerid, playerfire[0], playerfire[1], playerfire[2]);
        GetObjectPos(ObjectCampfire[slots][0],posfire[0],posfire[1],posfire[2]);
        posfire[3] = floatsqroot(floatpower(floatabs(floatsub(playerfire[0],posfire[0])),2)+ floatpower(floatabs(floatsub(playerfire[1],posfire[1])),2)+ floatpower(floatabs(floatsub(playerfire[2],posfire[2])),2));
        if(posfire[3] < distance) return true;
    } return false;
}
// ========== [ -|- FUNCTION -|- ] ==========
/*
	#include <a_samp>
	#include <zcmd>
	#include <a_Campfire>

	public OnFilterScriptInit() {
		print("\n**************************************");
		print("       Campfire in SA-MP 'Object'       ");
		print("           Date: 16/07/2013             ");
		print("            Author: OTACON              ");
		print("     --* Loaded with Success!!. *--     ");
		print("***************************************\n");

		CreateObjectCampfire(0, 664.4656,-1903.3425,3.1809,353.5751);
		return true;
	}
	public OnFilterScriptExit() {
		print("\n**************************************");
		print("       Campfire in SA-MP 'Object'       ");
		print("           Date: 16/07/2013             ");
		print("            Author: OTACON              ");
		print("   --* Downloaded with Success!!. *--   ");
		print("***************************************\n");

		DestroyObjectCampfire(0);
		return true;
	}
	COMMAND:fire(playerid, params[]) {
	    if(!IsPlayerConnected(playerid)) return true;
		if(IsPlayerInRangeOfFire(playerid, 3.0)) SendClientMessage(playerid, -1, "    [ ! ] you are near a campfire.!.");
		else SendClientMessage(playerid, -1, "    [ ! ] you are not near a campfire!.");
	    return true;
	}
*/
/*
             Prohibido TOTALMENTE el Robo de Créditos o la
              Publicación de este INCLUDE sin Mi Permiso.

                     FULLY spaces Theft Credit or
           Publication of this INCLUDE without my permission.

	SIMPLE INCLUDE --> Campfire in SA-MP 'Object'
	CREDITOS: OTACON ;)
	NOTA: Menos Creditos para los que me los critican.. JO'PUTAS! :D xD ;)
*/
