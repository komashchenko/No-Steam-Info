#ifndef _INCLUDE_RevEmu_PROPER_H_
#define _INCLUDE_RevEmu_PROPER_H_

typedef uint64_t CSteamID;

enum EUserType
{
   k_eSteamLegitUser = 0,
   k_eSteamCrackedUser,
   k_eRevEmuUser,
   k_eRevEmuUserOld,
   k_eSettiSRCScanBot,
   k_eRevEmuUserV74,
   k_eRevEmuUserVeryOld,
   k_eUnknownUser,
   k_eSteam2Legit,
   k_eSteam2Cracked
};

struct PlayerInfo_t
{
   unsigned int m_unUserID;
   CSteamID m_steamIDPlayer;
   EUserType m_ePlayerType;
   unsigned int m_unIP;
};


typedef bool (*pRev_BGetPlayerInfoBySteamID) (CSteamID steamID, PlayerInfo_t* pPlayerInfo);


#endif // _INCLUDE_RevEmu_PROPER_H_