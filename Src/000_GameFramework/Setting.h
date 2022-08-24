#pragma once

#include "KeyInput.h"
#include "ConsoleOutput.h"
#include "Camera.h"

struct ST_GAME_DATA
{
	std::tstring strTitle;
	DWORD dwKeyRepeatInterval;

	DWORD dwFPS;
	short nConsoleW;
	short nConsoleH;
	short nBackBufferWidth;
	short nBackBufferHeight;

	CKeyInput input;
	CConsoleOutput output;

	ST_GAME_DATA(void);
};

extern ST_GAME_DATA* g_pGameData;
extern CCamera g_Camera;

extern DWORD g_dwFPS;
extern short g_nConsoleW;
extern short g_nConsoleH;
extern int g_nDeltaTick;
extern double g_dDeltaTime;

void InitGame(ST_GAME_DATA* pGameData);