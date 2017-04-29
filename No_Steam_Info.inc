#if defined _No_Steam_Info_included
  #endinput
#endif
#define _No_Steam_Info_included


/**
 *	Checking is player no steam.
 * @param iClient					Index Client.
 *	-
 * @return	Returns Player no steam.
 *	-
 * @error invalid iClient.
*/
native bool IsPlayerNoSteam(int iClient);




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
}
#endif