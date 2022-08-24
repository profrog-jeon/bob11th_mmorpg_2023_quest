#include "pch.h"
#include "APIEntry.h"

static IQuestInfo* g_pQuestInfo;
void ExportAPIEntry(IQuestInfo* pIntance)
{
	g_pQuestInfo = pIntance;
}

DLL_API int InitMiniGame(ST_GAME_DATA* pGameData)
{
	InitGame(pGameData);
	return 0;
}

DLL_API void QueryNpcEx(std::vector<ST_QUEST_NPC_DATA>& vecNpcInfo)
{
	g_pQuestInfo->QueryNpcEx(vecNpcInfo);
}

DLL_API void QueryQuestObject(std::vector<ST_QUEST_OBJECT>& vecQuest)
{
	g_pQuestInfo->QueryQuestObject(vecQuest);
}

DLL_API void QueryQuestItem(std::vector<ST_QUEST_ITEM_DATA>& vecQuestItem)
{
	g_pQuestInfo->QueryQuestItem(vecQuestItem);
}

DLL_API void QueryQuest(std::vector<ST_QUEST_DATA>& vecQuest)
{
	g_pQuestInfo->QueryQuest(vecQuest);
}
