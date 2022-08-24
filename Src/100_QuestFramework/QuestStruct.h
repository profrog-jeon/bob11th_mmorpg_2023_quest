#pragma once

#include <vector>
#include <string>
#include "../000_GameFramework/000_GameFramework.h"

#pragma pack(push, 1)

struct ST_FILTER
{
	int nTargetNpcId;
	unsigned short wCondition;
	unsigned short wReward;

	ST_FILTER(void)
		: nTargetNpcId(0)
		, wCondition(0)
		, wReward(0)
	{}
	ST_FILTER(int targetNpcId, unsigned short condition, unsigned short reward = 0)
		: nTargetNpcId(targetNpcId)
		, wCondition(condition)
		, wReward(reward)
	{}
};

struct ST_QUEST_OBJECT
{
	std::tstring strName;
	char cPatch;
	int nQuestObjectId;
};

struct ST_QUEST_BATTLE_INFO
{
	BYTE btMinPlayerCount;			// 1~6 ����
	std::vector<DWORD> vecMonster;	// ���͵� �ִ� 6������..
	ST_QUEST_BATTLE_INFO(void)
		: btMinPlayerCount(1)
	{}
};

struct ST_QUEST_DATA
{
	int nNpcId;
	ST_FILTER StartCondition;	
	ST_FILTER ClearCondition;
	std::vector<std::tstring> vecMessages;
	std::vector<DWORD> vecRewardItems;
	std::vector<DWORD> vecRewardEquip;
	CDlgSuper* pClearGame;
	ST_QUEST_BATTLE_INFO ClearBattle;
	ST_QUEST_DATA(void)
		: nNpcId(-1), StartCondition(), ClearCondition(), vecMessages(), vecRewardItems(), pClearGame(nullptr), ClearBattle()
	{}
};

struct ST_COLOR
{
	BYTE r;
	BYTE g;
	BYTE b;
	BYTE flag;
	ST_COLOR(void)
		: r(0), g(0), b(0), flag(0)
	{}
	ST_COLOR(BYTE R, BYTE G, BYTE B)
		: r(R), g(G), b(B), flag(0)
	{}
};

struct ST_QUEST_NPC_DATA
{
	int nNpcID;
	char cPatch;
	ST_COLOR Color;

	std::tstring strTrack;
	std::tstring strName;
	int nAge;
	std::tstring strMBTI;
	std::tstring strMessage;	// NPC�� �λ�޽���

	std::tstring strContents1;	// ��Ʈ�� �޽���
	std::tstring strContents2;	// �������� �� ������ �޽���
	std::tstring strContents3;	// 2�ܰ� ������Ʈ�� ��ģ �� ������ �޽���
	std::tstring strContents4;	// ���� �� ������ �޽���

	double CalcLevelOfCompletion(void) const;
};

enum E_JOB_TYPE
{
	JOB_TYPE_NOVICE = 0,		// ������
	JOB_TYPE_DEVELOPER,
	JOB_TYPE_INVESTIGATOR,
	JOB_TYPE_CONSULTANT,
	JOB_TYPE_ANALYST,
	JOB_TYPE_MASTER,		// �����
};

struct ST_QUEST_ITEM_DATA
{
	DWORD dwId;
	short nHP;
	short nMP;
	std::tstring strName;
	std::tstring strDesc;
	ST_QUEST_ITEM_DATA(void)
		: dwId(0), nHP(0), nMP(0)
	{}
};

struct ST_QUEST_MONSTER_DATA
{
	DWORD dwMonsterId;
	std::tstring strName;
	BYTE btLevel;			// ����. ū �ǹ̴� ���� ����̴�.
	short nHP;				// ü��
	BYTE btAttack;			// ���ݷ�.
	BYTE btDex;				// �ൿ�ӵ�. 1~7������ ��������.(������ 10������.)
	BYTE btVulnerability;	// � ������ ������� ��Ÿ����. 0:���Ӽ�, �ٷ��� E_JOB_TYPE ����.
	int nRewardMoney;		// ���� �ݾ�. ������ ��������2.
	int nRewardExp;		// ���� ����ġ. ������ ��������.
	std::vector<BYTE> vecRewardItems;	// ���� ������. ������ ��������3
};
#pragma pack(pop)