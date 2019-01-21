#if defined _No_Steam_Info_included
  #endinput
#endif
#define _No_Steam_Info_included

enum RevEmu_PlayerType
{
	ErrorGet = -1, //Failed determine PlayerType
	SteamLegitUser = 0,
	SteamCrackedUser,
	RevEmuUser,
	RevEmuUserOld,
	SettiSRCScanBot,
	RevEmuUserV74,
	RevEmuUserVeryOld,
	UnknownUser,
	Steam2Legit,
	Steam2Cracked
};

/**
 * Checking if player is no-steam.
 * @param iClient	Index player.
 * -
 * @return			True if no-steam.
 * -
 * @error			Invalid player index or player not in game or player is a bot.
*/
#pragma deprecated Use RevEmu_GetPlayerType instead
native bool IsPlayerNoSteam(int iClient);

/**
 * Get the type of player
 * @param iClient	Index player.
 * -
 * @return			Returns RevEmu_PlayerType value.
 * -
 * @error			Invalid player index or player not in game or player is bot.
*/
native RevEmu_PlayerType RevEmu_GetPlayerType(int iClient);


public Extension __ext_No_Steam_Info = 
{
	name = "No_Steam_Info",
	file = "No_Steam_Info.ext",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif
};

#if !defined REQUIRE_EXTENSIONS
public __ext_No_Steam_Info_SetNTVOptional()
{
	MarkNativeAsOptional("IsPlayerNoSteam");
	MarkNativeAsOptional("RevEmu_GetPlayerType");
}
#endif