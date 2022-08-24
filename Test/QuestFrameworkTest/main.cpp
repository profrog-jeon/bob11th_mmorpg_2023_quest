#include "stdafx.h"
#include <locale.h>

void PrintImage(std::vector<std::tstring> buffer)
{
	for (auto line : buffer)
		_tprintf(TEXT("%s\n"), line.c_str());
}

void RunMiniGame(HMODULE hModule, CDlgSuper* pDlg)
{
	FP_InitMiniGame fpInitMiniGame = (FP_InitMiniGame)GetProcAddress(hModule, "InitMiniGame");
	if (nullptr == fpInitMiniGame)
	{
		_tprintf(TEXT("미니게임을 초기화할 수 없습니다.(InitMiniGame을 찾을 수 없음)\n"));
		return;
	}

	system("cls");

	ST_GAME_DATA GameData;
	GameData.dwFPS = 30;
	GameData.nConsoleW = 80;
	GameData.nConsoleH = 40;
	GameData.nBackBufferWidth = 78;
	GameData.nBackBufferHeight = 26;
	GameData.input.Register(VK_LEFT, GAMEKEY_LEFT);
	GameData.input.Register(VK_RIGHT, GAMEKEY_RIGHT);
	GameData.input.Register(VK_UP, GAMEKEY_UP);
	GameData.input.Register(VK_DOWN, GAMEKEY_DOWN);
	GameData.input.Register(VK_SPACE, GAMEKEY_SELECT);
	GameData.input.Register(VK_RETURN, GAMEKEY_MENU);
	GameData.input.Register(VK_OEM_3, GAMEKEY_CHAT);
	GameData.input.Register(VK_ESCAPE, GAMEKEY_ESC);
	GameData.strTitle = TEXT("미니게임 테스트");
	GameData.dwKeyRepeatInterval = 200;
	InitGame(&GameData);

	fpInitMiniGame(g_pGameData);

	pDlg->DoModal();
}

int main()
{
	setlocale(LC_ALL, "ko-KR");

	WIN32_FIND_DATA stFindData;

	HANDLE hFind = FindFirstFile(TEXT("*.dll"), &stFindData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		_tprintf(TEXT("Quest DLL is not found.\n"));
		return -1;
	}

	do
	{ 
		_tprintf(TEXT("---------- %s\n"), stFindData.cFileName);

		HMODULE hModule = LoadLibrary(stFindData.cFileName);
		if (INVALID_HANDLE_VALUE == hModule)
		{
			_tprintf(TEXT("LoadLibrary failure.\n"));
			continue;
		}

		FP_QueryNpcEx fpQueryNpcEx = (FP_QueryNpcEx)GetProcAddress(hModule, "QueryNpcEx");
		if (nullptr == fpQueryNpcEx)
		{
			_tprintf(TEXT("QueryNpcEx 함수가 없음.\n"));
			continue;
		}

		std::vector<ST_QUEST_NPC_DATA> vecNpcInfo;
		fpQueryNpcEx(vecNpcInfo);

		if (vecNpcInfo.empty())
			_tprintf(TEXT("Npc가 하나도 없네 :(\n"));

		for (ST_QUEST_NPC_DATA& npc : vecNpcInfo)
		{
			_tprintf(TEXT("[%s] 완성도: %.1lf%%\n"), npc.strName.c_str(), npc.CalcLevelOfCompletion());
				
			_tprintf(TEXT("이름:%s\n"), npc.strName.c_str());
			if (npc.strName.empty())
				_tprintf(TEXT("  ->> 없군요 ㅠㅠ\n"));

			_tprintf(TEXT("트랙:%s\n"), npc.strTrack.c_str());
			if (npc.strTrack.empty())
				_tprintf(TEXT("  ->> 없군요 ㅠㅠ\n"));

			_tprintf(TEXT("MBTI:%s\n"), npc.strMBTI.c_str());
			if (npc.strMBTI.empty())
				_tprintf(TEXT("  ->> 없군요 ㅠㅠ\n"));

			_tprintf(TEXT("인사말:%s\n"), npc.strMessage.c_str());
			if (npc.strMessage.empty())
				_tprintf(TEXT("  ->> 없군요 ㅠㅠ\n"));

			_tprintf(TEXT("화면상 문자:%c\n"), npc.cPatch);
			if (npc.cPatch < 'A' || 'Z' < npc.cPatch)
				_tprintf(TEXT("  ->> 가급적 대문자로 만들어주세요~\n"));

			_tprintf(TEXT("시나리오 대사1\n"));
			if (npc.strContents1.empty())
				_tprintf(TEXT("  ->> 없군요 ㅠㅠ 게임 시작시 인트로멘트로 보여줍니다.\n"));

			_tprintf(TEXT("시나리오 대사2\n"));
			if (npc.strContents2.empty())
				_tprintf(TEXT("  ->> 없군요 ㅠㅠ 전직 후로 보여줍니다.\n"));

			_tprintf(TEXT("시나리오 대사3\n"));
			if (npc.strContents3.empty())
				_tprintf(TEXT("  ->> 없군요 ㅠㅠ 팀 프로젝트 이후로 보여줍니다.\n"));

			_tprintf(TEXT("시나리오 대사4\n"));
			if (npc.strContents4.empty())
				_tprintf(TEXT("  ->> 없군요 ㅠㅠ 엔딩시에 보여줍니다.\n"));

			_tprintf(TEXT("===============================\n\n"));
		}

		FP_QueryQuest fpQueryQuest = (FP_QueryQuest)GetProcAddress(hModule, "QueryQuest");
		if (nullptr == fpQueryQuest)
		{
			_tprintf(TEXT("fpQueryQuest 함수가 없음.\n"));
			continue;
		}

		std::vector<ST_QUEST_DATA> vecQuestData;
		fpQueryQuest(vecQuestData);

		_tprintf(TEXT("퀘스트 데이터\n"));
		if (vecQuestData.empty())
		{
			_tprintf(TEXT("  ->> 없군요 ㅠㅠ 캐릭터의 퀘스트를 만들어봅시다.\n"));
		}

		for (ST_QUEST_DATA quest : vecQuestData)
		{
			_tprintf(TEXT("--------------\n"));
			for (std::tstring strMsg : quest.vecMessages)
				_tprintf(TEXT("퀘스트 대사: %s\n"), strMsg.c_str());
			if (quest.pClearGame && IDYES == ::MessageBox(nullptr, TEXT("미니게임을 실행하겠습니까?"), TEXT("걍 궁금"), MB_YESNO))
				RunMiniGame(hModule, quest.pClearGame);
		}

		FreeLibrary(hModule);
	} while (FindNextFile(hFind, &stFindData));

	FindClose(hFind);
	return 0;
}
