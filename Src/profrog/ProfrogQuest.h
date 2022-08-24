#pragma once

#include <vector>
#include <string>

class ProfrogQuest : public IQuestInfo
{
public:
	ProfrogQuest(void);
	~ProfrogQuest(void);

	void QueryNpcEx(std::vector<ST_QUEST_NPC_DATA>& vecNPC);
	void QueryQuestObject(std::vector<ST_QUEST_OBJECT>& vecQuestObject);
	void QueryQuestItem(std::vector< ST_QUEST_ITEM_DATA>& vecQuestItem);
	void QueryQuest(std::vector<ST_QUEST_DATA>& vecQuest);
};
