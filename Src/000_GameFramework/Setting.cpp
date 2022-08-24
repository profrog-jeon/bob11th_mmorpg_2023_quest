#include "pch.h"
#include "Setting.h"

DWORD g_dwFPS = 30;
short g_nConsoleW = 80;
short g_nConsoleH = 40;
int g_nDeltaTick = 1000 / g_dwFPS;
double g_dDeltaTime = 1.0 / g_dwFPS;

ST_GAME_DATA* g_pGameData = nullptr;
CCamera g_Camera;

ST_GAME_DATA::ST_GAME_DATA(void)
	: strTitle()
	, dwKeyRepeatInterval(200)
	, dwFPS(30)
	, nConsoleW(80)
	, nConsoleH(40)
	, nBackBufferWidth(80)
	, nBackBufferHeight(40)
	, input()
	, output()
{
}

void InitGame(ST_GAME_DATA* pGameData)
{
	g_dwFPS = pGameData->dwFPS;
	g_nConsoleW = pGameData->nConsoleW;
	g_nConsoleH = pGameData->nConsoleH;
	g_nDeltaTick = 1000 / pGameData->dwFPS;
	g_dDeltaTime = 1.0 / pGameData->dwFPS;

	g_pGameData = pGameData;

	pGameData->input.SetRepeatTick(pGameData->dwKeyRepeatInterval);
	pGameData->output.InitConsole(pGameData->strTitle, (g_nConsoleW + 1) * 2, g_nConsoleH + 1);
	pGameData->output.InitBackBuffer(pGameData->nBackBufferWidth * 2 + 1, pGameData->nBackBufferHeight + 1);
	pGameData->output.SetViewPort(g_nConsoleW+1, g_nConsoleH+1);
}
