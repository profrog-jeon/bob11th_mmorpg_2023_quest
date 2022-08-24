#include "pch.h"
#include "ProfrogQuest.h"
#include "MiniGame.h"

static ProfrogQuest g_QuestInfo;

ProfrogQuest::ProfrogQuest(void)
{
	ExportAPIEntry(this);
}

ProfrogQuest::~ProfrogQuest(void)
{
}

void ProfrogQuest::QueryNpcEx(std::vector<ST_QUEST_NPC_DATA>& vecNPC)
{
	ST_QUEST_NPC_DATA npc;
	npc.nNpcID = 201;
	npc.cPatch = 'P';		
	npc.Color = ST_COLOR(0x5F, 0x9E, 0xA0);	// ī�����

	npc.strTrack = TEXT("???");
	npc.strName = TEXT("� ������");
	npc.nAge = 25;
	npc.strMBTI = TEXT("UNKNOWN");
	npc.strMessage = TEXT("����...\n")
		TEXT("���� ���� ����������..\n")
		TEXT("�ι� �ٽ� ���Ұž�.");

	npc.strContents1 =
		TEXT("... ���ߴ� �Ф�\n")
		TEXT("���� ��Ե� �������.\n")
		;

	npc.strContents2 = 
		TEXT("��¼�ٺ��� �������� �Ź��ȳ�.\n")
		TEXT("�� ������ ������ �𸣴µ�?\n")
		TEXT("��¼��...? �̷���...?\n")
		TEXT("Ÿ�Ӹӽ��� ���峪��?\n")
		TEXT("�ƴ�...\n")
		TEXT("���� ���Ȱ����ϰ� �� ����̾�������.\n")
		TEXT("�׷��� �̷��� ���� �̰� ���忡 �ִ��� ����.\n")
		TEXT("���б� ������ �ȵ� �׷��� ���� �����.\n")
		TEXT("...\n")
		TEXT("����̵� ���� ���� ����.\n")
		TEXT("��� ���������� ����ɰ� �غ���.?\n")
		TEXT("���� �� ������Ʈ����?\n")
		TEXT("���� �´� ģ���� ��Ƽ� Ÿ�Ӹӽ��̳� ���ĺ��߰ڴ�.\n")
		TEXT("�ٵ� ���⼭ ���� ģ���� ���� �ִ���...\n")
		TEXT("...\n")
		TEXT("����\n")
		;
	npc.strContents3 =
		TEXT("����....\n")
		TEXT("��������....\n")
		TEXT("����������������....\n")
		TEXT("������������������������������������....\n")
		TEXT("����ɰ� �ߴ��� ��� ���ư� ��...\n")
		TEXT("Ư�� ������ ��ǥ �� �˽μ� �� ������...\n")
		TEXT("�ϱ� �����غ��� ��� ��ǥ�� ���� ���� ����.\n")
		TEXT("ȥ���⸸ �ϰ� ������.\n")
		TEXT("Ÿ�Ӹӽ� ��ġ�� ������ �߸���ҳ���.\n")
		TEXT("���Ǳ��� ���� ���߳�.. ����ü �� �ȵȰ���?\n")
		TEXT("(... ���ڱ� ��ã�� ���׸� �߰��Ѵ�.)\n")
		TEXT("�� �̰� ����. if�� ������ ��������?\n")
		TEXT("�ٽ� ��������.\n")
		TEXT("(�����...)\n")
		TEXT("�Ƴ�...\n")
		TEXT("�Ƴ�......\n")
		TEXT("�Ƴ�...............\n")
		TEXT("!@(%!(@&(#$*!@(*!@$*($@!*%&%!!\n")
		TEXT("Ÿ�Ӹӽ� �ߵ��µ�? ���� ���� �߸��Ѱ� �ƴϳ�!!\n")
		TEXT("�� ��ǥ �ﷷ��... ������ ��Ģ�� �ƴϾ�� ����...\n")
		TEXT("���� ���� ���ŷ� ��������?\n")
		TEXT("...\n")
		TEXT("......\n")
		TEXT("..........�Ƴ�\n")
		TEXT("��� ������� �°� ����� �ϰ���.\n")
		TEXT("3�� ������ �� ������ ��.\n")
		;
	npc.strContents4 = 
		TEXT("��...~~~~~~~ �� ����ִ°ǰ�?\n")
		TEXT("(�������� �չ��� ��¦�� ����������.)\n")
		TEXT("Ū... ���� ���� �� �ȵ��.\n")
		TEXT("���� �ʹ� ���� ������...\n")
		TEXT("���̰� �Ӹ��� �����ϸ� ����Ѵٰ�\n")
		TEXT("�̾��ϴ� �� ���� �Ф�\n")
		TEXT("...\n")
		TEXT("����?\n")
		TEXT("�ٵ� ���� �̻��ѵ�.\n")
		TEXT("���ڱ� �̰� ����? �ֺ��� ������ 0�� 1�� ���̱� ������\n")
		TEXT("�̰� ��Ʈ���� �׿��� �Ź����ǰ�?\n")
		TEXT("Ÿ�̸ӽ� ������ ���� ������ ���� �� ���� �� ������?\n")
		TEXT("�̰� BoB ������� ���ΰǰ�..!! �� ���� ��û �������� ����!!\n")
		TEXT("�� �̴�� �ٽ� ���ŷ� ���ư��ٸ� �� ���� �� �� �ְ���?\n")
		TEXT("�׷��� ������ �ٽ� ���߾��Ұž� �����...\n")
		TEXT("�� �� ������!! ���� ���߷� ���� 1�� 2�� 3�� ������!!\n")
		TEXT("(�̶� �ڿ��� �ڿ��� ġ�� ������ ����)\n")
		TEXT("(�� ���� ��������.. ������ ������...)\n")
		;
	vecNPC.push_back(npc);

	{
		ST_QUEST_NPC_DATA npc;
		npc.nNpcID = 202;
		npc.cPatch = 'L';
		npc.Color = ST_COLOR(0x5F, 0x9E, 0xA0);	// ī�����

		npc.strTrack = TEXT("���Ȱ���Ʈ�� �����");
		npc.strName = TEXT("10�� ��â��");
		npc.nAge = 25;
		npc.strMBTI = TEXT("UNKNOWN");
		npc.strMessage = TEXT("�� �����.");
		vecNPC.push_back(npc);
	}
}

void ProfrogQuest::QueryQuestObject(std::vector<ST_QUEST_OBJECT>& vecQuestObject)
{
	{
		ST_QUEST_OBJECT stObject;
		stObject.nQuestObjectId = 2001;
		stObject.strName = TEXT("��ü�Ҹ��� ���������");
		stObject.cPatch = TEXT('9');
		vecQuestObject.push_back(stObject);
	}
	{
		ST_QUEST_OBJECT stObject;
		stObject.nQuestObjectId = 2002;
		stObject.strName = TEXT("Ŀ�ٶ� ������");
		stObject.cPatch = TEXT('o');
		vecQuestObject.push_back(stObject);
	}
}

void ProfrogQuest::QueryQuestItem(std::vector<ST_QUEST_ITEM_DATA>& vecQuestItem)
{
    {
        ST_QUEST_ITEM_DATA item;
        item.dwId = 3001;
        item.nHP = 0;
        item.nMP = 0;
        item.strName = TEXT("��ȣȭ�� ����");
        item.strDesc = TEXT("������ ���� �˾ƺ� �� ����.");
        vecQuestItem.push_back(item);
    }
    {
        ST_QUEST_ITEM_DATA item;
        item.dwId = 3002;
        item.nHP = 0;
        item.nMP = 9999;
        item.strName = TEXT("�̷��� ȣ����");
        item.strDesc = TEXT("2046�⿡ ������� �ź��� ��ü�� ���ø� ���ŷ��� �ִ�ġ�� ȸ�����ش�.");
        vecQuestItem.push_back(item);
    }
	{
		ST_QUEST_ITEM_DATA item;
		item.dwId = 3003;
		item.nHP = 0;
		item.nMP = 0;
		item.strName = TEXT("�̷� �������� ����");
		item.strDesc = TEXT("2022�⿡ ���⸻ ȫ���� �߻��Ұž�. �� ���� �Ǹ� (-50, 23) ������ ���� �����غ�. ���ܵ� ��ġ�� �־�.");
		vecQuestItem.push_back(item);
	}
}

void ProfrogQuest::QueryQuest(std::vector<ST_QUEST_DATA>& vecQuest)
{
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 201;
		stQuest.StartCondition = ST_FILTER(201, 0x0000, 0x0001);
		stQuest.vecMessages.push_back(TEXT("��"));
		stQuest.vecMessages.push_back(TEXT("....."));
		stQuest.vecMessages.push_back(TEXT("�Ͼ�....."));
		stQuest.vecMessages.push_back(TEXT("�Ͼ�.....�Ͼƾ�......"));
		stQuest.vecMessages.push_back(TEXT("(������)"));
		stQuest.vecMessages.push_back(TEXT("(�Ѽ��� �ʹ� Ŀ�� ���� ������)"));
		stQuest.vecMessages.push_back(TEXT("���� ���� ������."));
		stQuest.vecMessages.push_back(TEXT("�ٵ� �� ��¼�� �� ���ŷ� �°ɱ�?"));
		stQuest.vecMessages.push_back(TEXT("�ٽ� ���� ���� ���ϱ�� ������"));
		stQuest.vecMessages.push_back(TEXT("�Ǵٽ� BoB���� ���Ӱ����� �ϰ� �ֱ�."));
		stQuest.vecMessages.push_back(TEXT("9���� MMORPG 2021"));
		stQuest.vecMessages.push_back(TEXT("10���� MMORPG 2022"));
		stQuest.vecMessages.push_back(TEXT("�׸��� �Ǵٽ� ���ŷ� �ͼ�..."));
		stQuest.vecMessages.push_back(TEXT("11�� MMORPG 2023!!!"));
		stQuest.vecMessages.push_back(TEXT("������ ����!! ���� ���� ������~~~"));
		stQuest.vecMessages.push_back(TEXT("(�� �� ���ڱ� �տ��� ���� ����̰� ��������.)"));
		stQuest.ClearCondition = ST_FILTER(201, 0x0003);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 2001;
		stQuest.StartCondition = ST_FILTER(201, 0x0001, 0x0003);
		stQuest.vecMessages.push_back(TEXT("�̾�ȣ.."));
		stQuest.vecMessages.push_back(TEXT("..."));
		stQuest.vecMessages.push_back(TEXT("�̾�ȣ.... �̾�ȣ...."));
		stQuest.vecMessages.push_back(TEXT("(���� ����̰� �������� ��� �ִ�. ��ġ � ���������� �Ҹ��� �ִµ� �ϴ�.)"));
		stQuest.ClearCondition = ST_FILTER(201, 0x0007);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 201;
		stQuest.StartCondition = ST_FILTER(201, 0x0003, 0x0007);
		stQuest.vecMessages.push_back(TEXT("�� �� �༮��?"));
		stQuest.vecMessages.push_back(TEXT("��ȣ~~"));
		stQuest.vecMessages.push_back(TEXT("��ȣ~~ ��ȣ~~"));
		stQuest.vecMessages.push_back(TEXT("��? (���ڱ� 10�� ���ؼ��� ����Ѵ�.)"));
		stQuest.vecMessages.push_back(TEXT("�Ƹ´�. �� �г��� ��ȣ��."));
		stQuest.vecMessages.push_back(TEXT("�� ����"));
		stQuest.vecMessages.push_back(TEXT("�̾߿�~~ ��� ������~"));
		stQuest.vecMessages.push_back(TEXT("�� �׷�����."));
		stQuest.vecMessages.push_back(TEXT("����̰� �ڱ� �ֺ��� ������ ȣ������ �����غ���"));
		stQuest.ClearCondition = ST_FILTER(201, 0x000F);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 2002;
		stQuest.StartCondition = ST_FILTER(201, 0x0007, 0x000F);
		stQuest.vecMessages.push_back(TEXT("������ ���ڴٸ� ȣ����ó�� ���δ�."));
		stQuest.vecMessages.push_back(TEXT("� ���������� ��������."));		
		stQuest.ClearCondition = ST_FILTER(201, 0x001F);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 201;
		stQuest.StartCondition = ST_FILTER(201, 0x000F, 0x001F);
		stQuest.vecMessages.push_back(TEXT("�� �̰��� ����Ʈ ������ �Ƴ�?"));
		stQuest.vecMessages.push_back(TEXT("���� �ֵ��� �̰� ���ٵ�."));
		stQuest.vecMessages.push_back(TEXT("�� �� �츮�� �꽺 �� ������ ������ �ʰ� �������� ä���԰� �߾���."));
		stQuest.vecMessages.push_back(TEXT("�ȱ׷��� �񸻶��µ� �ߵƴ�."));
		stQuest.vecMessages.push_back(TEXT("�y~(�Ѳ� ���� �Ҹ�)"));
		stQuest.vecMessages.push_back(TEXT("�ñ�ñ�ñ�..."));
		stQuest.vecMessages.push_back(TEXT("(�̾߿�!!!! �̾�!! �̾�~~!!!)"));
		stQuest.vecMessages.push_back(TEXT("(�ؼ�)�׸� �ĸԾ�!! ���� ������ �ȵ�!!"));
		stQuest.vecMessages.push_back(TEXT("�ʹ� ���� ���� �����𸣰� ���Ź��ȳ�. ����"));
		stQuest.vecMessages.push_back(TEXT("(��½!)"));
		stQuest.vecMessages.push_back(TEXT("��??"));
		stQuest.vecMessages.push_back(TEXT("(��½!!!)"));
		stQuest.vecMessages.push_back(TEXT("����! ������!!"));
		stQuest.vecMessages.push_back(TEXT("(��½)"));
		stQuest.vecMessages.push_back(TEXT("(��½��½��½)"));
		stQuest.vecMessages.push_back(TEXT("(��)")); 
		stQuest.vecMessages.push_back(TEXT("(� �������� �������, �װ� ���Ѻ��� ���� �����...)"));
		stQuest.ClearCondition = ST_FILTER(201, 0x003F);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 2001;
		stQuest.StartCondition = ST_FILTER(201, 0x001F, 0x003F);
		stQuest.vecMessages.push_back(TEXT("�ɳɾ�:��û�� �༮ ������."));
		stQuest.vecMessages.push_back(TEXT("�ɳɾ�:���ŷ� ���ư��� �����̶�� ��������� �װ� �׳� �� ó�Գ�"));
		stQuest.vecMessages.push_back(TEXT("�ɳɾ�:MMORPG 2023 �������� ���� ���������"));
		stQuest.vecMessages.push_back(TEXT("�ɳɾ�:������ MMORPG�� ���°ǰ�?"));
		stQuest.vecMessages.push_back(TEXT("�ɳɾ�:11�� ��Ƽ���� ������������."));
		stQuest.vecMessages.push_back(TEXT("�ɳɾ�:..."));
		stQuest.vecMessages.push_back(TEXT("�ɳɾ�:�ٵ� �� ��� ���ư���?"));
		stQuest.vecMessages.push_back(TEXT("�̶�, � �������� �ִ� �ڸ��� �ٽ� ��½�Ÿ���."));
		stQuest.ClearCondition = ST_FILTER(201, 0x007F);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 201;
		stQuest.StartCondition = ST_FILTER(201, 0x003F, 0x007F);
		stQuest.vecMessages.push_back(TEXT("��½"));
		stQuest.vecMessages.push_back(TEXT("��½��½��½"));
		stQuest.vecMessages.push_back(TEXT("ǿ-------!"));
		stQuest.vecMessages.push_back(TEXT("¥��!"));
		stQuest.vecMessages.push_back(TEXT("���� ���� �ɳɾ ���˾Ƶ���ھ�?"));
		stQuest.vecMessages.push_back(TEXT("����Ʈ ���� �ʹ� Ŀ�� ���� �ɷ� �ٲ�Դٱ�!!"));
		stQuest.vecMessages.push_back(TEXT("2022�⵵���� ���� ��Ʈ������ ��� �ٴϱ� ���� ���´� ������."));
		stQuest.vecMessages.push_back(TEXT("��� ���ŷ� ���¾��� �� ����� ���� �°Ŷ�."));
		stQuest.vecMessages.push_back(TEXT("(���� �������̾�!!!)"));
		stQuest.vecMessages.push_back(TEXT("���ڱ� 10�� ��â���� �Ҹ�������."));
		stQuest.ClearCondition = ST_FILTER(201, 0x00FF);  
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 202;
		stQuest.StartCondition = ST_FILTER(201, 0x007F, 0x00FF);
		stQuest.vecMessages.push_back(TEXT("�� ���� �� �� �˾ƿ�?"));
		stQuest.vecMessages.push_back(TEXT("�ƴ��� ���� ������ ��ϱ� �ݸ��ؾ���"));
		stQuest.vecMessages.push_back(TEXT("��..!!"));
		stQuest.vecMessages.push_back(TEXT("��ġ�Ϸ��� ���ƿ°���?"));
		stQuest.vecMessages.push_back(TEXT("(� �������� ��ĩ�Ѵ�.)"));
		stQuest.vecMessages.push_back(TEXT("����..."));
		stQuest.vecMessages.push_back(TEXT("�ϱ� ������ �ڸ��߰� �� ����."));
		stQuest.vecMessages.push_back(TEXT("���� �̷��� �� ������! ������ �ڷ��� �ִ���."));
		stQuest.vecMessages.push_back(TEXT("���� �ó�?"));
		stQuest.vecMessages.push_back(TEXT("\"�������� ����\"���"));
		stQuest.vecMessages.push_back(TEXT("(�ڿ� �ִ� 10�� ���ؼ��� ���͸� ���.)"));
		stQuest.vecMessages.push_back(TEXT("���� �㿡�� ���� ��ٸ���."));
		stQuest.vecMessages.push_back(TEXT("����ض�, �� 11�ô�."));
		stQuest.vecMessages.push_back(TEXT("(� �������� �ϰ� ���� ���� �ִ� �� ����.)"));
		stQuest.ClearCondition = ST_FILTER(201, 0x01FF);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 201;
		stQuest.StartCondition = ST_FILTER(201, 0x00FF, 0x01FF);
		stQuest.vecMessages.push_back(TEXT("ĩ..!"));
		stQuest.vecMessages.push_back(TEXT("�����ʿ��� �ڷ��� �ʼ��� ��¿ �� ����"));
		stQuest.vecMessages.push_back(TEXT("�װ� �׷���"));
		stQuest.vecMessages.push_back(TEXT("�� �׷�..."));
		stQuest.vecMessages.push_back(TEXT("�����---! (���ڱ� ������ ���س���.)"));
		stQuest.vecMessages.push_back(TEXT("(�÷�...)"));
		stQuest.vecMessages.push_back(TEXT("(�÷ղ÷�...)"));
		stQuest.vecMessages.push_back(TEXT("(�÷ղ÷ղ÷�...)"));
		stQuest.vecMessages.push_back(TEXT("(���� ��Ʈ���� �Ʊ���� ���ŷ� ���� ���� ����)"));
		stQuest.vecMessages.push_back(TEXT("�� ������ ��Ʈ���� ���� ä����"));
		stQuest.vecMessages.push_back(TEXT("���� �ٽ� ���� �����ؾ��ؼ� �̸�..!"));
		stQuest.vecMessages.push_back(TEXT("���� ����̿� �̴ϰ����� ���̸� ������ �ϳ� �ٰž�."));
		stQuest.vecMessages.push_back(TEXT("�װ� ���� �ٽ� ��."));
		stQuest.vecMessages.push_back(TEXT("���� ��û �ٻ����� �ص����ٰ�."));
		stQuest.ClearCondition = ST_FILTER(201, 0x03FF);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 2001;
		stQuest.StartCondition = ST_FILTER(201, 0x01FF, 0x03FF);
		stQuest.vecMessages.push_back(TEXT("�̾�ȣ~ Helloworld�� �޾ƶ�(ESC�� â�� �ݾƺ���.)"));
		stQuest.pClearGame = new CMiniGame();
		stQuest.ClearCondition = ST_FILTER(201, 0x07FF);
		stQuest.vecRewardItems.push_back(3001);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 201;
		stQuest.StartCondition = ST_FILTER(201, 0x07FF, 0x0FFF);
		stQuest.vecMessages.push_back(TEXT("��.. ���� �����Ա�."));
		stQuest.vecMessages.push_back(TEXT("(������ �޾Ƶ��.)"));
		stQuest.vecMessages.push_back(TEXT("ȣ.. �̰� ����?"));
		stQuest.vecMessages.push_back(TEXT("�پ��� �����ڵ�� ���ڵ��Ǿ��ݾ�?"));
		stQuest.vecMessages.push_back(TEXT("�� ���� �ص��ϴ°ž� ���� �� �Ա���."));
		stQuest.vecMessages.push_back(TEXT("(11�� �������� ������ Copy and paste �Ͽ� Ǯ���)"));
		stQuest.vecMessages.push_back(TEXT("���� �̰��� �ű��ϱ���."));
		stQuest.vecMessages.push_back(TEXT("�������� ������ ���� �ڲ� ������ ��Ʈ���� �� ����� ���� ���� ����."));
		stQuest.vecMessages.push_back(TEXT("�ɽ��ϸ� �о����."));
		stQuest.vecMessages.push_back(TEXT("��, ��� ���� ���Ѻ� ��!!"));
		stQuest.vecMessages.push_back(TEXT("�� ���ƺ��� ����~ ���� �ʸ���."));
		stQuest.vecMessages.push_back(TEXT("�� ��Ʈ���� ����̸� �װ� �ñ��!"));
		stQuest.vecMessages.push_back(TEXT("��� ����Ʈ�� ��ġ�� ����̸� �ٽ� ���ŷ� �����ٿ�"));
		stQuest.vecMessages.push_back(TEXT("�������� [�̷� ������]���� �����غ���."));
		stQuest.ClearCondition = ST_FILTER(201, 0xFFFF);
		stQuest.vecRewardItems.push_back(3002);
		stQuest.vecRewardItems.push_back(3003);
		vecQuest.push_back(stQuest);
	}
}
