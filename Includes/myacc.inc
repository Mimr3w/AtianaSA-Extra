// MySQL
#undef MAX_PLAYERS
#define MAX_PLAYERS 200

#define mysql_host "localhost" // www.witgaming.tk/phpmyadmin
#define mysql_user "root"
#define mysql_password ""
#define mysql_database "local"

#define mysql_host1 "localhost" // www.witgaming.tk/phpmyadmin
#define mysql_user1 "root"
#define mysql_password1 ""
#define mysql_database1 "local"

new handle;
new gQuery[512];
new mysqlstatus = 0;
new MySQLSelect = 1;

forward MySQLConnect();

public MySQLConnect()
{
	new read[64];
	new File:file = fopen("startup.txt", io_read); 
	if(file) 
	{
		fread(file, read);
		fclose(file); 
		MySQLSelect = strval(read);
	}
	if(MySQLSelect == 0) handle = mysql_connect(mysql_host, mysql_user, mysql_database, mysql_password);
	else if(MySQLSelect == 1) handle = mysql_connect(mysql_host1, mysql_user1, mysql_database1, mysql_password1);
	return 1;
}


forward Update(playerid, type);

#define pLevelx				1
#define pAdminx				2
#define pHelperx			3
#define pCashx				4
#define pAccountx			5
#define pEmailx				6
#define pRegistredx			7
#define pTutorialx			8
#define pSexx				9
#define	pAgex				10
#define pPhoneNumberx		11
#define pPhoneBookx			12
#define pWalkieTalkiex		13
#define pLighterx			14
#define pCigarettesx		15
#define pPremiumAccountx	16
#define pRespectx	        17
#define pPayCheckx	        18
#define pPayDayx        	19
#define pPayDayHadx        	20
#define pHoursPlayedx	    21
#define pLeaderx			22
#define pMemberx			23
#define pRankx				24
#define pSkinx				25
#define pFWarnsx			26
#define pFPunishx			27
#define pWarnsx				28
#define pMutedx				29
#define pMuteTimex			30
#define pDrivingLicx		31
#define pFlyingLicx			32
#define pGunLicx			33
#define pSailLicx			34
#define pJobx				35
#define pStockPilex			36
#define pWantedx			37
#define pJailedx			38
#define pJailTimex			39
#define pBailx				40
#define pMatsx				41
#define pDrugsx				42
#define pHouseKeyx			43
#define pRentKeyx			44
#define pBizzKeyx			45
#define pHeadValuex			46
#define pContractedx		47
#define pContractx			48
#define pContractTimex		49
#define pTowPointsx			50
#define pSpawnChangex		51
#define pAJailedx			52
#define pAJailTimex			53
#define pReferralx			54
#define pRobx				55
#define pFreePointsx		56
#define pPlayerPickupsx		57
#define pCLeaderx			58
#define pCMemberx			59
#define pRegisteredDatex	60
#define pLastLoginx			61
#define pKillsx				62
#define pDeathsx			63
#define pCrimesx			64
#define pArrestsx			65
#define pWantedDeathsx		66
#define pVehicleSlotsx		67
#define pTruckerSkillx		68
#define pAchievementsx		69
#define pCoinsx             70
#define pGarbageSkillx      71
#define pRobSkillx      	72
#define pMoneyBoostx      	73
#define pRPBoostx      	    74
#define pMechanicSkillx     75
#define pFarmerSkillx     	76
#define pWoodSkillx     	77
#define pPizzaSkillx     	78
#define pCRankx     		79
#define pTutVehx     		80
#define pFuelx				81
#define pWantedLostx		82
#define pGiftx				83
#define pFishingLicx		84
#define pBiggestFishx		85
#define pLanguagex		85

enum pInfo
{
	pSQLID, pPassword[64], pLevel, pAdmin, pHelper, pCash, pAccount, pEmail[128], pRegistred, pTutorial, pSex, pAge, pPhoneNumber, pPhoneBook, pWalkieTalkie, pLighter, pCigarettes, pPremiumAccount, 
	pLeader, pMember, pRank, pSkin, pFWarns, pFPunish, pWarns, pMuted, pMuteTime, pDrivingLic, pFlyingLic, pGunLic, pSailLic, pFishingLic, pBiggestFish, pJob, pRespect, pHoursPlayed, pPayCheck, pPayDay, pPayDayHad, pStockPile, 
	pWanted, pJailed, pJailTime, pBail, pMats, pDrugs, pHouseKey, pRentKey, pBizzKey, pHeadValue, pContracted, pContract[25], pContractTime, pTowPoints, pSpawnChange, pAJailed, pAJailTime, pReferral, 
	pRob, pFreePoints, pCLeader, pCMember, pPlayerPickups[256], pRegisteredDate[128], pLastLogin[128], pKills, pDeaths, pCrimes, pArrests, pWantedDeaths, pVehicleSlots, pTruckerSkill, pAchievements[128],
	pCoins, pGarbageSkill, pRobSkill, pMoneyBoost, pRPBoost, pMechanicSkill, pFarmerSkill, pWoodSkill, pPizzaSkill, pCRank, pTutVeh, pFuel, pWantedLost, pGift, pLanguage
};

new PlayerInfo[MAX_PLAYERS][pInfo];

public Update(playerid, type)
{
	if(IsPlayerConnected(playerid))
	{
		gQuery[0] = (EOS);
		{
			switch(type)
			{
				case pLevelx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Level`=%d WHERE `ID`=%d", PlayerInfo[playerid][pLevel], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pAdminx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `AdminLevel`=%d WHERE `ID`=%d", PlayerInfo[playerid][pAdmin], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pHelperx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `HelperLevel`=%d WHERE `ID`=%d", PlayerInfo[playerid][pHelper], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pCashx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Cash`=%d WHERE `ID`=%d", PlayerInfo[playerid][pCash], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pAccountx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Account`=%d WHERE `ID`=%d", PlayerInfo[playerid][pAccount], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pEmailx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Email`='%e' WHERE `ID`=%d", PlayerInfo[playerid][pEmail], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pRegistredx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Registred`=%d WHERE `ID`=%d", PlayerInfo[playerid][pRegistred], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pTutorialx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Tutorial`=%d WHERE `ID`=%d", PlayerInfo[playerid][pTutorial], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pSexx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Sex`=%d WHERE `ID`=%d", PlayerInfo[playerid][pSex], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pAgex:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Age`=%d WHERE `ID`=%d", PlayerInfo[playerid][pAge], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pPhoneNumberx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `PhoneNumber`=%d WHERE `ID`=%d", PlayerInfo[playerid][pPhoneNumber], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pPhoneBookx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `PhoneBook`=%d WHERE `ID`=%d", PlayerInfo[playerid][pPhoneBook], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pWalkieTalkiex:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `WalkieTalkie`=%d WHERE `ID`=%d", PlayerInfo[playerid][pWalkieTalkie], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pLighterx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Lighter`=%d WHERE `ID`=%d", PlayerInfo[playerid][pLighter], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pCigarettesx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Cigarettes`=%d WHERE `ID`=%d", PlayerInfo[playerid][pCigarettes], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pPremiumAccountx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `PremiumAccount`=%d WHERE `ID`=%d", PlayerInfo[playerid][pPremiumAccount], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pRespectx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Respect`=%d WHERE `ID`=%d", PlayerInfo[playerid][pRespect], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pPayCheckx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `PayCheck`=%d WHERE `ID`=%d", PlayerInfo[playerid][pPayCheck], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pPayDayx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `PayDay`=%d WHERE `ID`=%d", PlayerInfo[playerid][pPayDay], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pPayDayHadx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `PayDayHad`=%d WHERE `ID`=%d", PlayerInfo[playerid][pPayDayHad], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pHoursPlayedx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `HoursPlayed`=%d WHERE `ID`=%d", PlayerInfo[playerid][pHoursPlayed], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pLeaderx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Leader`=%d WHERE `ID`=%d", PlayerInfo[playerid][pLeader], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pMemberx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Member`=%d WHERE `ID`=%d", PlayerInfo[playerid][pMember], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pRankx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Rank`=%d WHERE `ID`=%d", PlayerInfo[playerid][pRank], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pSkinx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Skin`=%d WHERE `ID`=%d", PlayerInfo[playerid][pSkin], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				
				case pFWarnsx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `FWarns`=%d WHERE `ID`=%d", PlayerInfo[playerid][pFWarns], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pFPunishx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `FPunish`=%d WHERE `ID`=%d", PlayerInfo[playerid][pFPunish], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pWarnsx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Warns`=%d WHERE `ID`=%d", PlayerInfo[playerid][pWarns], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pMutedx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Muted`=%d WHERE `ID`=%d", PlayerInfo[playerid][pMuted], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pMuteTimex:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `MuteTime`=%d WHERE `ID`=%d", PlayerInfo[playerid][pMuteTime], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pDrivingLicx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `DrivingLic`=%d WHERE `ID`=%d", PlayerInfo[playerid][pDrivingLic], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pFlyingLicx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `FlyingLic`=%d WHERE `ID`=%d", PlayerInfo[playerid][pFlyingLic], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pGunLicx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `GunLic`=%d WHERE `ID`=%d", PlayerInfo[playerid][pGunLic], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pSailLicx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `SailLic`=%d WHERE `ID`=%d", PlayerInfo[playerid][pSailLic], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pFishingLicx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `FishingLic`= %d WHERE `ID`=%d", PlayerInfo[playerid][pFishingLic], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pJobx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Job`=%d WHERE `ID`=%d", PlayerInfo[playerid][pJob], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pStockPilex:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `StockPile`=%d WHERE `ID`=%d", PlayerInfo[playerid][pStockPile], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pWantedx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Wanted`=%d WHERE `ID`=%d", PlayerInfo[playerid][pWanted], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pJailedx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Jailed`=%d WHERE `ID`=%d", PlayerInfo[playerid][pJailed], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pJailTimex:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `JailTime`=%d WHERE `ID`=%d", PlayerInfo[playerid][pJailTime], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pBailx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Bail`=%d WHERE `ID`=%d", PlayerInfo[playerid][pBail], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pMatsx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Materials`=%d WHERE `ID`=%d", PlayerInfo[playerid][pMats], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pDrugsx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Drugs`=%d WHERE `ID`=%d", PlayerInfo[playerid][pDrugs], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pHouseKeyx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `HouseKey`=%d WHERE `ID`=%d", PlayerInfo[playerid][pHouseKey], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pRentKeyx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `RentKey`=%d WHERE `ID`=%d", PlayerInfo[playerid][pRentKey], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pBizzKeyx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `BizzKey`=%d WHERE `ID`=%d", PlayerInfo[playerid][pBizzKey], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pHeadValuex:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `HeadValue`=%d WHERE `ID`=%d", PlayerInfo[playerid][pHeadValue], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pContractedx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Contracted`=%d WHERE `ID`=%d", PlayerInfo[playerid][pContracted], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pContractx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Contract`='%e' WHERE `ID`=%d", PlayerInfo[playerid][pContract], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pContractTimex:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `ContractTime`=%d WHERE `ID`=%d", PlayerInfo[playerid][pContractTime], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pTowPointsx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `TowPoints`=%d WHERE `ID`=%d", PlayerInfo[playerid][pTowPoints], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pSpawnChangex:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `SpawnChange`=%d WHERE `ID`=%d", PlayerInfo[playerid][pSpawnChange], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pAJailedx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `AJailed`=%d WHERE `ID`=%d", PlayerInfo[playerid][pAJailed], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pAJailTimex:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `AJailTime`=%d WHERE `ID`=%d", PlayerInfo[playerid][pAJailTime], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pReferralx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Referral`=%d WHERE `ID`=%d", PlayerInfo[playerid][pReferral], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pRobx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Rob`=%d WHERE `ID`=%d", PlayerInfo[playerid][pRob], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pFreePointsx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `FreePoints`=%d WHERE `ID`=%d", PlayerInfo[playerid][pFreePoints], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}		
				case pCLeaderx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `CLeader`=%d WHERE `ID`=%d", PlayerInfo[playerid][pCLeader], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pCMemberx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `CMember`=%d WHERE `ID`=%d", PlayerInfo[playerid][pCMember], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pPlayerPickupsx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `PlayerPickups`= '%e' WHERE `ID`=%d", PlayerInfo[playerid][pPlayerPickups], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pRegisteredDatex:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `RegisteredDate`= '%e' WHERE `ID`=%d", PlayerInfo[playerid][pRegisteredDate], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pLastLoginx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `LastLogin`= '%e' WHERE `ID`=%d", PlayerInfo[playerid][pLastLogin], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pKillsx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Kills`= %d WHERE `ID`=%d", PlayerInfo[playerid][pKills], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pDeathsx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Deaths`= %d WHERE `ID`=%d", PlayerInfo[playerid][pDeaths], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pCrimesx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Crimes`= %d WHERE `ID`=%d", PlayerInfo[playerid][pCrimes], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pArrestsx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Arrests`= %d WHERE `ID`=%d", PlayerInfo[playerid][pArrests], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pWantedDeathsx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `WantedDeaths`= %d WHERE `ID`=%d", PlayerInfo[playerid][pWantedDeaths], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pVehicleSlotsx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `VehicleSlots`= %d WHERE `ID`=%d", PlayerInfo[playerid][pVehicleSlots], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pTruckerSkillx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `TruckerSkill`= %d WHERE `ID`=%d", PlayerInfo[playerid][pTruckerSkill], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pAchievementsx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Achievements`= '%e' WHERE `ID`=%d", PlayerInfo[playerid][pAchievements], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pCoinsx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Coins`= %d WHERE `ID`=%d", PlayerInfo[playerid][pCoins], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pGarbageSkillx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `GarbageSkill`= %d WHERE `ID`=%d", PlayerInfo[playerid][pGarbageSkill], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pRobSkillx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `RobSkill`= %d WHERE `ID`=%d", PlayerInfo[playerid][pRobSkill], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pMechanicSkillx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `MechanicSkill`= %d WHERE `ID`=%d", PlayerInfo[playerid][pMechanicSkill], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pFarmerSkillx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `FarmerSkill`= %d WHERE `ID`=%d", PlayerInfo[playerid][pFarmerSkill], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pWoodSkillx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `WoodSkill`= %d WHERE `ID`=%d", PlayerInfo[playerid][pWoodSkill], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pPizzaSkillx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `PizzaSkill`= %d WHERE `ID`=%d", PlayerInfo[playerid][pPizzaSkill], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pMoneyBoostx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `MoneyBoost`= %d WHERE `ID`=%d", PlayerInfo[playerid][pMoneyBoost], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pRPBoostx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `RPBoost`= %d WHERE `ID`=%d", PlayerInfo[playerid][pRPBoost], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pCRankx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `CRank`= %d WHERE `ID`=%d", PlayerInfo[playerid][pCRank], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pTutVehx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `TutVeh`= %d WHERE `ID`=%d", PlayerInfo[playerid][pTutVeh], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pFuelx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Fuel`= %d WHERE `ID`=%d", PlayerInfo[playerid][pFuel], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pWantedLostx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `WantedLost`= %d WHERE `ID`=%d", PlayerInfo[playerid][pWantedLost], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pGiftx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Gift`= %d WHERE `ID`=%d", PlayerInfo[playerid][pGift], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pBiggestFishx:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `BiggestFish`= %d WHERE `ID`=%d", PlayerInfo[playerid][pBiggestFish], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
				case pLanguagex:
				{
					mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `players` SET `Language`= %d WHERE `ID`=%d", PlayerInfo[playerid][pLanguage], PlayerInfo[playerid][pSQLID]);
					mysql_query(handle, gQuery);
				}
			}
		}
	}
	return 1;
}


forward sUpdate(safe, type);

#define sMoneyx				1
#define sDrugsx				2
#define sMaterialsx			3
#define sNewsx				4

enum sInfo
{
	Float:sPosX,Float:sPosY,Float:sPosZ,sMoney,sDrugs,sMaterials,sNews[128]
};

new SafeInfo[12][sInfo];

public sUpdate(safe, type)
{
	gQuery[0] = (EOS);
	switch(type)
	{
		case sMoneyx:
		{
			mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `safes` SET `Money`=%d WHERE `ID`=%d", SafeInfo[safe][sMoney], safe);
			mysql_query(handle, gQuery);
		}
		case sDrugsx:
		{
			mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `safes` SET `Drugs`=%d WHERE `ID`=%d", SafeInfo[safe][sDrugs], safe);
			mysql_query(handle, gQuery);
		}
		case sMaterialsx:
		{
			mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `safes` SET `Materials`=%d WHERE `ID`=%d", SafeInfo[safe][sMaterials], safe);
			mysql_query(handle, gQuery);
		}
		case sNewsx:
		{
			mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `safes` SET `News`='%e' WHERE `ID`=%d", SafeInfo[safe][sNews], safe);
			mysql_query(handle, gQuery);
		}
	}
	return 1;
}


forward zUpdate(zone, type);

#define zTeamx				1
#define zHoursx				2

enum zInfo
{
	Float:zMinX,Float:zMinY,Float:zMaxX,Float:zMaxY,zTeam,zHours
};


#define NUMDIS 40.0
#define MAX_GANGZONES 24

new ZoneInfo[25][zInfo];
new Zone[25];
new ZoneArea[25];
new Border[4][25];
new Number1[25][5];
new Number2[25][5];
new TakeON[25];
new PickupHealth1[2048];
new PickupWeapon1[2048];
new PickupHealth2[2048];
new PickupWeapon2[2048];

public zUpdate(zone, type)
{
	gQuery[0] = (EOS);
	switch(type)
	{
		case zTeamx:
		{
			mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `zones` SET `Team`=%d WHERE `ID`=%d", ZoneInfo[zone][zTeam], zone);
			mysql_query(handle, gQuery);
		}
		case zHoursx:
		{
			mysql_format(handle, gQuery, sizeof(gQuery), "UPDATE `zones` SET `Hours`=%d WHERE `ID`=%d", ZoneInfo[zone][zHours], zone);
			mysql_query(handle, gQuery);
		}
	}
	return 1;
}

forward hUpdate(houseid, type);

#define hEntranceXx 		1
#define hEntranceYx 		2
#define hEntranceZx 		3
#define hExitXx		 		4
#define hExitYx 			5
#define hExitZx				6
#define hOwnerx				7
#define hValuex 			8
#define hIntx 				9
#define hLockx 				10
#define hOwnedx 			11
#define hRentx 				12
#define hRentablex 			13
#define hSafex 				14
#define hLevelx 			15
#define hWorldx 			16
#define hSellPricex			17

enum hInfo
{
	Float:hEntranceX,
	Float:hEntranceY,
	Float:hEntranceZ,
	Float:hExitX,
	Float:hExitY,
	Float:hExitZ,
	hOwner[MAX_PLAYER_NAME],
	hValue,
	hInt,
	hLock,
	hOwned,
	hRent,
	hRentable,
	hSafe,
	hLevel,
	hWorld,
	hSellPrice,
	Text3D:hTextInfo,
	hPickup,
	hMapIcon
};

new HouseInfo[150][hInfo];
new HouseEntered[MAX_PLAYERS];
new Total_House_Created = 0;

public hUpdate(houseid, type)
{
	gQuery[0] = (EOS);
	switch(type)
	{
		case hEntranceXx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `EntranceX`=%f WHERE `ID`=%d",HouseInfo[houseid][hEntranceX],houseid);
			mysql_query(handle, gQuery);
	    }
		case hEntranceYx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `EntranceY`=%f WHERE `ID`=%d",HouseInfo[houseid][hEntranceY],houseid);
			mysql_query(handle, gQuery);
	    }
		case hEntranceZx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `EntranceZ`=%f WHERE `ID`=%d",HouseInfo[houseid][hEntranceZ],houseid);
			mysql_query(handle, gQuery);
	    }
		case hExitXx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `ExitX`=%f WHERE `ID`=%d",HouseInfo[houseid][hExitX],houseid);
			mysql_query(handle, gQuery);
	    }
		case hExitYx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `ExitY`=%f WHERE `ID`=%d",HouseInfo[houseid][hExitY],houseid);
			mysql_query(handle, gQuery);
	    }
		case hExitZx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `ExitZ`=%f WHERE `ID`=%d",HouseInfo[houseid][hExitZ],houseid);
			mysql_query(handle, gQuery);
	    }
		case hOwnerx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `Owner`='%e' WHERE `ID`=%d",HouseInfo[houseid][hOwner],houseid);
			mysql_query(handle, gQuery);
	    }
		case hValuex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `Value`=%d WHERE `ID`=%d",HouseInfo[houseid][hValue],houseid);
			mysql_query(handle, gQuery);
	    }
		case hIntx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `Interior`=%d WHERE `ID`=%d",HouseInfo[houseid][hInt],houseid);
			mysql_query(handle, gQuery);
	    }
		case hLockx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `Lock`=%d WHERE `ID`=%d",HouseInfo[houseid][hLock],houseid);
			mysql_query(handle, gQuery);
	    }
		case hOwnedx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `Owned`=%d WHERE `ID`=%d",HouseInfo[houseid][hOwned],houseid);
			mysql_query(handle, gQuery);
	    }
		case hRentx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `Rent`=%d WHERE `ID`=%d",HouseInfo[houseid][hRent],houseid);
			mysql_query(handle, gQuery);
	    }
		case hRentablex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `Rentable`=%d WHERE `ID`=%d",HouseInfo[houseid][hRentable],houseid);
			mysql_query(handle, gQuery);
	    }
		case hSafex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `Safe`=%d WHERE `ID`=%d",HouseInfo[houseid][hSafe],houseid);
			mysql_query(handle, gQuery);
	    }
		case hLevelx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `Level`=%d WHERE `ID`=%d",HouseInfo[houseid][hLevel],houseid);
			mysql_query(handle, gQuery);
	    }
		case hWorldx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `World`=%d WHERE `ID`=%d",HouseInfo[houseid][hWorld],houseid);
			mysql_query(handle, gQuery);
	    }
		case hSellPricex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `houses` SET `SellPrice`=%d WHERE `ID`=%d",HouseInfo[houseid][hSellPrice],houseid);
			mysql_query(handle, gQuery);
	    }
	}
	return 1;
}

forward bUpdate(bizzid, type);

#define bEntranceXx 		1
#define bEntranceYx 		2
#define bEntranceZx 		3
#define bExitXx		 		4
#define bExitYx 			5
#define bExitZx				6
#define bIntx				7
#define bOwnedx	 			8
#define bOwnerx 			9
#define bNamex 				10
#define bLevelx 			11
#define bPricex 			12
#define bEntranceCostx 		13
#define bItemPricex 		14
#define bSafex 			    15
#define bLockedx 			16

enum bInfo
{
	Float:bEntranceX,
	Float:bEntranceY,
	Float:bEntranceZ,
	Float:bExitX,
	Float:bExitY,
	Float:bExitZ,
	bInt,
	bOwned,
	bOwner[MAX_PLAYER_NAME],
	bName[48],
	bLevel,
	bPrice,
	bEntranceCost,
	bItemPrice,
	bSafe,
	bLocked,
	Text3D:bTextInfo,
	bPickup,
	bSBiz,
	bMapIcon,
	bVirtual
};

new BizzInfo[50][bInfo];
new BizzEntered[MAX_PLAYERS];

public bUpdate(bizzid, type)
{
	gQuery[0] = (EOS);
	switch(type)
	{
		case bEntranceXx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `business` SET `EntranceX`=%f WHERE `ID`=%d",BizzInfo[bizzid][bEntranceX],bizzid);
			mysql_query(handle, gQuery);
	    }
		case bEntranceYx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `business` SET `EntranceY`=%f WHERE `ID`=%d",BizzInfo[bizzid][bEntranceY],bizzid);
			mysql_query(handle, gQuery);
	    }
		case bEntranceZx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `business` SET `EntranceZ`=%f WHERE `ID`=%d",BizzInfo[bizzid][bEntranceZ],bizzid);
			mysql_query(handle, gQuery);
	    }
		case bExitXx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `business` SET `ExitX`=%f WHERE `ID`=%d",BizzInfo[bizzid][bExitX],bizzid);
			mysql_query(handle, gQuery);
	    }
		case bExitYx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `business` SET `ExitY`=%f WHERE `ID`=%d",BizzInfo[bizzid][bExitY],bizzid);
			mysql_query(handle, gQuery);
	    }
		case bExitZx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `business` SET `ExitZ`=%f WHERE `ID`=%d",BizzInfo[bizzid][bExitZ],bizzid);
			mysql_query(handle, gQuery);
	    }
		case bIntx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `business` SET `Interior`=%d WHERE `ID`=%d",BizzInfo[bizzid][bInt],bizzid);
			mysql_query(handle, gQuery);
	    }
		case bOwnedx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `business` SET `Owned`=%d WHERE `ID`=%d",BizzInfo[bizzid][bOwned],bizzid);
			mysql_query(handle, gQuery);
	    }
		case bOwnerx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `business` SET `Owner`='%e' WHERE `ID`=%d",BizzInfo[bizzid][bOwner],bizzid);
			mysql_query(handle, gQuery);
	    }
		case bNamex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `business` SET `ID`=%d WHERE `ID`=%d",BizzInfo[bizzid][bName],bizzid);
			mysql_query(handle, gQuery);
	    }
		case bLevelx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `business` SET `Level`=%d WHERE `ID`=%d",BizzInfo[bizzid][bLevel],bizzid);
			mysql_query(handle, gQuery);
	    }
		case bPricex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `business` SET `Price`=%d WHERE `ID`=%d",BizzInfo[bizzid][bPrice],bizzid);
			mysql_query(handle, gQuery);
	    }
		case bEntranceCostx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `business` SET `EntranceCost`=%d WHERE `ID`=%d",BizzInfo[bizzid][bEntranceCost],bizzid);
			mysql_query(handle, gQuery);
	    }
		case bItemPricex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `business` SET `ItemPrice`=%d WHERE `ID`=%d",BizzInfo[bizzid][bItemPrice],bizzid);
			mysql_query(handle, gQuery);
	    }
		case bSafex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `business` SET `Safe`=%d WHERE `ID`=%d",BizzInfo[bizzid][bSafe],bizzid);
			mysql_query(handle, gQuery);
	    }
		case bLockedx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `business` SET `Locked`=%d WHERE `ID`=%d",BizzInfo[bizzid][bLocked],bizzid);
			mysql_query(handle, gQuery);
	    }
	}
	return 1;
}

forward vUpdate(vehicleid, type);

#define vCarIDx 				1
#define vColor1x 				2
#define vColor2x 				3
#define vPricex 				4
#define vOwnerx 				5
#define vPosXx 					6
#define vPosYx 					7
#define vPosZx 					8
#define vPosAx	 				9
#define vPlatex 				10
#define vPaintJx 				11
#define vLockedx 				12
#define vSpawnedx 				13
#define vDestroyedx 			14
#define vKmx 				    15
#define vNeonx 				    16
#define vFuelx 				    17
#define vModsx 					18
#define vModelx 				19
#define vTypex 				    20

#define OwnedVeh(%0) 		ivCreated[%0]
#define MAX_BUYABLE_VEH 	10000  // Change to the ammount of vehicles

enum _VINFO
{
	vCarID,
	vModel,
	vColor1,
	vColor2,
	vPrice,
	vOwner[MAX_PLAYER_NAME],
	Float:vPosX,
	Float:vPosY,
	Float:vPosZ,
	Float:vPosA,
	vPlate[32],
	vPaintJ,
	vLocked,
	vSpawned,
	vDestroyed,
	Float:vKm,
	vNeon,
	vFuel,
	vType,
	mod1,
	mod2,
	mod3,
	mod4,
	mod5,
	mod6,
	mod7,
	mod8,
	mod9,
	mod10,
	mod11,
	mod12,
	mod13,
	mod14,
	mod15,
	mod16,
	mod17
}
new
	vInfo[MAX_BUYABLE_VEH][_VINFO],
	ivCreated[MAX_VEHICLES],
	Total_Veh_Created;

public vUpdate(vehicleid, type)
{
	gQuery[0] = (EOS);
	switch(type)
	{
	    case vCarIDx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `CarID`=%d WHERE `CarID`=%d",vInfo[vehicleid][vCarID],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
		case vModelx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `Model`=%d WHERE `CarID`=%d",vInfo[vehicleid][vModel],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
	    case vColor1x:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `Color1`=%d WHERE `CarID`=%d",vInfo[vehicleid][vColor1],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
	    case vColor2x:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `Color2`=%d WHERE `CarID`=%d",vInfo[vehicleid][vColor2],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
	    case vPricex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `Price`=%d WHERE `CarID`=%d",vInfo[vehicleid][vPrice],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
	    case vOwnerx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `Owner`='%e' WHERE `CarID`=%d",vInfo[vehicleid][vOwner],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
	    case vPosXx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `vPosX`='%.2f' WHERE `CarID`=%d",vInfo[vehicleid][vPosX],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
	    case vPosYx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `vPosY`='%.2f' WHERE `CarID`=%d",vInfo[vehicleid][vPosY],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
	    case vPosZx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `vPosZ`='%.2f' WHERE `CarID`=%d",vInfo[vehicleid][vPosZ],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
	    case vPosAx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `vPosA`='%.2f' WHERE `CarID`=%d",vInfo[vehicleid][vPosA],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
	    case vPlatex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `Plate`='%e' WHERE `CarID`=%d",vInfo[vehicleid][vPlate],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
	    case vPaintJx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `PaintJ`=%d WHERE `CarID`=%d",vInfo[vehicleid][vPaintJ],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
	    case vLockedx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `Locked`=%d WHERE `CarID`=%d",vInfo[vehicleid][vLocked],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
	    case vSpawnedx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `Spawned`=%d WHERE `CarID`=%d",vInfo[vehicleid][vSpawned],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
		case vDestroyedx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `Destroyed`=%d WHERE `CarID`=%d",vInfo[vehicleid][vDestroyed],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
		case vKmx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `Km`='%.2f' WHERE `CarID`=%d",vInfo[vehicleid][vKm],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
		case vNeonx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `Neon`=%d WHERE `CarID`=%d",vInfo[vehicleid][vNeon],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
		case vFuelx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `Fuel`=%d WHERE `CarID`=%d",vInfo[vehicleid][vFuel],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
		case vTypex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `Type`=%d WHERE `CarID`=%d",vInfo[vehicleid][vType],vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
	    case vModsx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `vehicles` SET `vMod1`=%d,`vMod2`=%d,`vMod3`=%d,`vMod4`=%d,`vMod5`=%d,`vMod6`=%d,`vMod7`=%d,`vMod8`=%d,`vMod9`=%d,`vMod10`=%d,`vMod11`=%d,`vMod12`=%d,`vMod13`=%d,`vMod14`=%d,`vMod15`=%d,`vMod16`=%d,`vMod17`=%d WHERE `CarID`=%d",
			vInfo[vehicleid][mod1],
			vInfo[vehicleid][mod2],
			vInfo[vehicleid][mod3],
			vInfo[vehicleid][mod4],
			vInfo[vehicleid][mod5],
			vInfo[vehicleid][mod6],
			vInfo[vehicleid][mod7],
			vInfo[vehicleid][mod8],
			vInfo[vehicleid][mod9],
			vInfo[vehicleid][mod10],
			vInfo[vehicleid][mod11],
			vInfo[vehicleid][mod12],
			vInfo[vehicleid][mod13],
			vInfo[vehicleid][mod14],
			vInfo[vehicleid][mod15],
			vInfo[vehicleid][mod16],
			vInfo[vehicleid][mod17],
			vInfo[vehicleid][vCarID]);
			mysql_query(handle, gQuery);
	    }
	}
	return 1;
}

forward d1Update(id, type);

#define d1Pricex 				1
#define d1Stockx 				2

enum dInfo1
{
	d1Model,
	d1Price,
	d1Stock
}
new D1Info[50][dInfo1];

public d1Update(id, type)
{
	gQuery[0] = (EOS);
	switch(type)
	{
	    case d1Pricex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `dealer1` SET `Price`=%d WHERE `Model`=%d",D1Info[id][d1Price],D1Info[id][d1Model]);
			mysql_query(handle, gQuery);
	    }
		case d1Stockx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `dealer1` SET `Stock`=%d WHERE `Model`=%d",D1Info[id][d1Stock],D1Info[id][d1Model]);
			mysql_query(handle, gQuery);
	    }
	}
	return 1;
}


forward d2Update(id, type);

#define d2Pricex 				1
#define d2Stockx 				2

enum dInfo2
{
	d2Model,
	d2Price,
	d2Stock
}
new D2Info[50][dInfo2];

public d2Update(id, type)
{
	gQuery[0] = (EOS);
	switch(type)
	{
	    case d2Pricex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `dealer2` SET `Price`=%d WHERE `Model`=%d",D2Info[id][d2Price],D2Info[id][d2Model]);
			mysql_query(handle, gQuery);
	    }
		case d2Stockx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `dealer2` SET `Stock`=%d WHERE `Model`=%d",D2Info[id][d2Stock],D2Info[id][d2Model]);
			mysql_query(handle, gQuery);
	    }
	}
	return 1;
}

forward d3Update(id, type);

#define d3Pricex 				1
#define d3Stockx 				2

enum dInfo3
{
	d3Model,
	d3Price,
	d3Stock
}
new D3Info[50][dInfo3];

public d3Update(id, type)
{
	gQuery[0] = (EOS);
	switch(type)
	{
	    case d3Pricex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `dealer3` SET `Price`=%d WHERE `Model`=%d",D3Info[id][d3Price],D3Info[id][d3Model]);
			mysql_query(handle, gQuery);
	    }
		case d3Stockx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `dealer3` SET `Stock`=%d WHERE `Model`=%d",D3Info[id][d3Stock],D3Info[id][d3Model]);
			mysql_query(handle, gQuery);
	    }
	}
	return 1;
}


forward d4Update(id, type);

#define d4Pricex 				1
#define d4Stockx 				2

enum dInfo4
{
	d4Model,
	d4Price,
	d4Stock
}
new D4Info[50][dInfo4];

public d4Update(id, type)
{
	gQuery[0] = (EOS);
	switch(type)
	{
	    case d4Pricex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `dealer4` SET `Price`=%d WHERE `Model`=%d",D4Info[id][d4Price],D4Info[id][d4Model]);
			mysql_query(handle, gQuery);
	    }
		case d4Stockx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `dealer4` SET `Stock`=%d WHERE `Model`=%d",D4Info[id][d4Stock],D4Info[id][d4Model]);
			mysql_query(handle, gQuery);
	    }
	}
	return 1;
}

forward d5Update(id, type);

#define d5Pricex 				1
#define d5Stockx 				2

enum dInfo5
{
	d5Model,
	d5Price,
	d5Stock
}
new D5Info[50][dInfo5];

public d5Update(id, type)
{
	gQuery[0] = (EOS);
	switch(type)
	{
	    case d5Pricex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `dealer5` SET `Price`=%d WHERE `Model`=%d",D5Info[id][d5Price],D5Info[id][d5Model]);
			mysql_query(handle, gQuery);
	    }
		case d5Stockx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `dealer5` SET `Stock`=%d WHERE `Model`=%d",D5Info[id][d5Stock],D5Info[id][d5Model]);
			mysql_query(handle, gQuery);
	    }
	}
	return 1;
}

forward cUpdate(id, type);

#define cNamex 					1
#define cTagx 					2
#define cTagTypex 				3
#define cSlotsx 			 	4
#define cHQTypex 			 	5
#define cHouseHQx 			 	6
#define cNewsx 			 		7
#define cWWarsx 				8
#define cBestx					9

enum cInfo
{
	cID,
	cName[32],
	cTag[10],
	cTagType,
	cSlots,
	cHQType,
	cHouseHQ,
	cNews[128],
	cWWars,
	cBest
}
new ClanInfo[100][cInfo];
new TotalClans;

public cUpdate(id, type)
{
	gQuery[0] = (EOS);
	switch(type)
	{
	    case cNamex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `clans` SET `Name`='%e' WHERE `ID`=%d",ClanInfo[id][cName], id);
			mysql_query(handle, gQuery);
	    }
		case cTagx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `clans` SET `Tag`='%e' WHERE `ID`=%d",ClanInfo[id][cTag], id);
			mysql_query(handle, gQuery);
	    }
		case cTagTypex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `clans` SET `TagType`=%d WHERE `ID`=%d",ClanInfo[id][cTagType], id);
			mysql_query(handle, gQuery);
	    }
		case cSlotsx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `clans` SET `Slots`=%d WHERE `ID`=%d",ClanInfo[id][cSlots], id);
			mysql_query(handle, gQuery);
	    }
		case cHQTypex:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `clans` SET `HQType`=%d WHERE `ID`=%d",ClanInfo[id][cHQType], id);
			mysql_query(handle, gQuery);
	    }
		case cHouseHQx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `clans` SET `HouseHQ`=%d WHERE `ID`=%d",ClanInfo[id][cHouseHQ], id);
			mysql_query(handle, gQuery);
	    }
		case cNewsx:
	    {
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `clans` SET `News`='%e' WHERE `ID`=%d",ClanInfo[id][cNews],id);
			mysql_query(handle, gQuery);
	    }
		case cWWarsx:
		{
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `clans` SET `WWars`=%d WHERE `ID`=%d",ClanInfo[id][cWWars],id);
			mysql_query(handle, gQuery);		
		}
		case cBestx:
		{
	        mysql_format(handle, gQuery, sizeof(gQuery),"UPDATE `clans` SET `Best`=%d WHERE `ID`=%d",ClanInfo[id][cBest],id);
			mysql_query(handle, gQuery);		
		}
	}
	return 1;
}
