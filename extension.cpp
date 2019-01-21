#include "extension.h"
#include "RevEmu.h"

NSI g_NSI;
SMEXT_LINK(&g_NSI);

pRev_BGetPlayerInfoBySteamID Rev_BGetPlayerInfoBySteamID;

const sp_nativeinfo_t g_ExtensionNatives[] =
{
	{ "IsPlayerNoSteam",		IsPlayerNoSteam },
	{ "RevEmu_GetPlayerType",	RevEmu_GetPlayerType },
	{ NULL,						NULL }
};

bool NSI::SDK_OnLoad(char *error, size_t maxlength, bool late)
{
	const char *pLibSteamclientPath = NULL;
	#if defined POSIX
		pLibSteamclientPath = "./bin/steamclient.so";
	#elif defined WIN32_LEAN_AND_MEAN
		pLibSteamclientPath = "./bin/steamclient.dll";
	#endif
	
	ILibrary *pLibrary = libsys->OpenLibrary(pLibSteamclientPath, NULL, 0);
	if (pLibrary != NULL)
	{
		Rev_BGetPlayerInfoBySteamID = (pRev_BGetPlayerInfoBySteamID)pLibrary->GetSymbolAddress("Rev_BGetPlayerInfoBySteamID");
		pLibrary->CloseLibrary();
		
		if(Rev_BGetPlayerInfoBySteamID == NULL)
		{
			snprintf(error, maxlength, "RevEmu not installed");
			return false;
		}
	}
	else
	{
		snprintf(error, maxlength, "Could not open library '%s'", pLibSteamclientPath);
		return false;
	}
	
	sharesys->AddNatives(myself, g_ExtensionNatives);
	sharesys->RegisterLibrary(myself, "No_Steam_Info");
	
	return true;
}

static cell_t IsPlayerNoSteam(IPluginContext *pContext, const cell_t *params)
{
	IGamePlayer *pPlayer = playerhelpers->GetGamePlayer(params[1]);
	if (pPlayer == NULL)
	{
		return pContext->ThrowNativeError("Client index %d is invalid", params[1]);
	}
	else if (!pPlayer->IsConnected())
	{
		return pContext->ThrowNativeError("Client %d is not connected", params[1]);
	}
	else if (pPlayer->IsFakeClient())
	{
		return pContext->ThrowNativeError("Client %d is a bot", params[1]);
	}
	
	PlayerInfo_t PlayerInfo;
	if(!Rev_BGetPlayerInfoBySteamID(pPlayer->GetSteamId64(), &PlayerInfo))
	{
		return pContext->ThrowNativeError("Failed get information on client %d with RevEmu", params[1]);
	}
	
	return PlayerInfo.m_ePlayerType != k_eSteamLegitUser;
}

static cell_t RevEmu_GetPlayerType(IPluginContext *pContext, const cell_t *params)
{
	IGamePlayer *pPlayer = playerhelpers->GetGamePlayer(params[1]);
	if (pPlayer == NULL)
	{
		return pContext->ThrowNativeError("Client index %d is invalid", params[1]);
	}
	else if (!pPlayer->IsConnected())
	{
		return pContext->ThrowNativeError("Client %d is not connected", params[1]);
	}
	else if (pPlayer->IsFakeClient())
	{
		return pContext->ThrowNativeError("Client %d is a bot", params[1]);
	}
	
	PlayerInfo_t PlayerInfo;
	if(!Rev_BGetPlayerInfoBySteamID(pPlayer->GetSteamId64(), &PlayerInfo))
	{
		return -1;
	}
	
	return PlayerInfo.m_ePlayerType;
}