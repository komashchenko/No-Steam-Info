#include "extension.h"

NSI g_NSI;
SMEXT_LINK(&g_NSI);
 
CDetour *g_pIsRevEmuUser;

const sp_nativeinfo_t g_ExtensionNatives[] =
{
	{ "IsPlayerNoSteam",									IsPlayerNoSteam },
	{ NULL,													NULL }
};

bool RevEmuUser;
bool RevEmuUsers[MAXPLAYERS];
int userid[MAXPLAYERS];

DETOUR_DECL_MEMBER2(DETOUR_IsRevEmuUser, bool, const void *, void0, uint, uint0)
{
	RevEmuUser = DETOUR_MEMBER_CALL(DETOUR_IsRevEmuUser)(void0, uint0);
	return RevEmuUser;
}

void NSI::OnClientConnected(int client)
{
	int usrid = playerhelpers->GetGamePlayer(client)->GetUserId();
	if(userid[client] != usrid)
	{
		RevEmuUsers[client] = RevEmuUser;
		userid[client] = usrid;
	}
}

bool NSI::SDK_OnLoad(char *error, size_t maxlength, bool late)
{
	CDetourManager::Init(g_pSM->GetScriptingEngine(), 0);
	
	void * tier0 = dlopen("steamclient.so", RTLD_NOW);
	
	void * fn = dlsym(tier0, "_ZN10GameServer5Users5CUser12IsRevEmuUserEPKvj");
	
	if(!fn)
	{
		snprintf(error, maxlength, "RevEmu not installed");
		return false;
	}
	
	g_pIsRevEmuUser = DETOUR_CREATE_MEMBER(DETOUR_IsRevEmuUser, fn);
	if (!g_pIsRevEmuUser)
	{
		snprintf(error, maxlength, "Detour failed IsRevEmuUser");
		return false;
	}
	else g_pIsRevEmuUser->EnableDetour();
	
	playerhelpers->AddClientListener(&g_NSI);
	
	sharesys->AddNatives(myself, g_ExtensionNatives);
	sharesys->RegisterLibrary(myself, "No_Steam_Info");
	
	return true;
}

static cell_t IsPlayerNoSteam(IPluginContext *pContext, const cell_t *params)
{
	int client = params[1];
	IGamePlayer *pPlayer = playerhelpers->GetGamePlayer(client);
	if (!pPlayer || !pPlayer->IsConnected())
	{
		return pContext->ThrowNativeError("Client index %d is invalid", client);
	}
	
	return RevEmuUsers[client];
}

void NSI::SDK_OnUnload()
{
	g_pIsRevEmuUser->Destroy();
}