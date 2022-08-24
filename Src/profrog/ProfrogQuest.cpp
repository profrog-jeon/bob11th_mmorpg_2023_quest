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
	npc.Color = ST_COLOR(0x5F, 0x9E, 0xA0);	// 카뎃블루

	npc.strTrack = TEXT("???");
	npc.strName = TEXT("어린 전상현");
	npc.nAge = 25;
	npc.strMBTI = TEXT("UNKNOWN");
	npc.strMessage = TEXT("으으...\n")
		TEXT("게임 개발 지긋지긋해..\n")
		TEXT("두번 다시 안할거야.");

	npc.strContents1 =
		TEXT("... 망했다 ㅠㅠ\n")
		TEXT("여길 어떻게든 벗어나보자.\n")
		;

	npc.strContents2 = 
		TEXT("어쩌다보니 보안인이 돼버렸네.\n")
		TEXT("난 보안이 뭔지도 모르는데?\n")
		TEXT("어쩌다...? 이렇게...?\n")
		TEXT("타임머신이 고장나서?\n")
		TEXT("아니...\n")
		TEXT("원래 보안공부하게 될 운명이었나보다.\n")
		TEXT("그래서 미래의 내가 이곳 광장에 있는지 모르지.\n")
		TEXT("대학교 수업도 안들어서 그런지 정말 힘들다.\n")
		TEXT("...\n")
		TEXT("어떤일이든 쉬운 것은 없지.\n")
		TEXT("기왕 시작했으니 목숨걸고 해보자.?\n")
		TEXT("이제 팀 프로젝트랬나?\n")
		TEXT("맘에 맞는 친구들 모아서 타임머신이나 고쳐봐야겠다.\n")
		TEXT("근데 여기서 내가 친구가 누가 있더라...\n")
		TEXT("...\n")
		TEXT("없군\n")
		;
	npc.strContents3 =
		TEXT("헉헉....\n")
		TEXT("헉헉헉헉....\n")
		TEXT("헉헉헉헉헉헉헉헉....\n")
		TEXT("헉헉헉헉헉헉헉헉헉헉헉헉헉헉헉헉헉헉....\n")
		TEXT("목숨걸고 했더니 목숨 날아갈 뻔...\n")
		TEXT("특히 마지막 발표 때 똥싸서 영 찜찜해...\n")
		TEXT("하긴 생각해보면 모든 발표를 잘한 적이 없어.\n")
		TEXT("혼나기만 하고 어흑흑.\n")
		TEXT("타임머신 고치기 주제를 잘못잡았나봐.\n")
		TEXT("막판까지 데모를 못했네.. 도대체 왜 안된거지?\n")
		TEXT("(... 갑자기 못찾던 버그를 발견한다.)\n")
		TEXT("어 이거 뭐여. if문 조건이 뒤집혔네?\n")
		TEXT("다시 돌려보자.\n")
		TEXT("(잠시후...)\n")
		TEXT("아나...\n")
		TEXT("아나......\n")
		TEXT("아나...............\n")
		TEXT("!@(%!(@&(#$*!@(*!@$*($@!*%&%!!\n")
		TEXT("타임머신 잘도는데? 내가 완전 잘못한게 아니네!!\n")
		TEXT("아 발표 울렁증... 데모의 법칙만 아니었어도 으아...\n")
		TEXT("지금 당장 과거로 가버릴까?\n")
		TEXT("...\n")
		TEXT("......\n")
		TEXT("..........아냐\n")
		TEXT("기왕 여기까지 온거 수료는 하고가자.\n")
		TEXT("3차 교육은 좀 쉽겠지 머.\n")
		;
	npc.strContents4 = 
		TEXT("컥...~~~~~~~ 나 살아있는건가?\n")
		TEXT("(여기저기 손발을 살짝씩 움직여본다.)\n")
		TEXT("큭... 몸이 말을 잘 안듣네.\n")
		TEXT("날을 너무 많이 샜나봐...\n")
		TEXT("아이고 머리가 무식하면 고생한다고\n")
		TEXT("미안하다 내 몸아 ㅠㅠ\n")
		TEXT("...\n")
		TEXT("으응?\n")
		TEXT("근데 뭔가 이상한데.\n")
		TEXT("갑자기 이건 뭐지? 주변의 세상이 0과 1로 보이기 시작해\n")
		TEXT("이거 매트릭스 네오가 돼버린건가?\n")
		TEXT("타이머신 정도는 이제 가볍게 만들 수 있을 것 같은데?\n")
		TEXT("이게 BoB 수료생의 힘인건가..!! 나 뭔가 엄청 강해진것 같아!!\n")
		TEXT("와 이대로 다시 과거로 돌아간다면 난 편히 살 수 있겠지?\n")
		TEXT("그래도 게임은 다신 개발안할거야 우우우우...\n")
		TEXT("와 나 계탔어!! 이제 개발로 연봉 1억 2억 3억 받을래!!\n")
		TEXT("(이때 뒤에서 코웃음 치는 전상현 멘토)\n")
		TEXT("(흥 내가 저랬었지.. 하지만 현실은...)\n")
		;
	vecNPC.push_back(npc);

	{
		ST_QUEST_NPC_DATA npc;
		npc.nNpcID = 202;
		npc.cPatch = 'L';
		npc.Color = ST_COLOR(0x5F, 0x9E, 0xA0);	// 카뎃블루

		npc.strTrack = TEXT("보안개발트랙 수료생");
		npc.strName = TEXT("10기 임창현");
		npc.nAge = 25;
		npc.strMBTI = TEXT("UNKNOWN");
		npc.strMessage = TEXT("뽕 나줘라.");
		vecNPC.push_back(npc);
	}
}

void ProfrogQuest::QueryQuestObject(std::vector<ST_QUEST_OBJECT>& vecQuestObject)
{
	{
		ST_QUEST_OBJECT stObject;
		stObject.nQuestObjectId = 2001;
		stObject.strName = TEXT("정체불명의 새끼고양이");
		stObject.cPatch = TEXT('9');
		vecQuestObject.push_back(stObject);
	}
	{
		ST_QUEST_OBJECT stObject;
		stObject.nQuestObjectId = 2002;
		stObject.strName = TEXT("커다란 유리병");
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
        item.strName = TEXT("암호화된 쪽지");
        item.strDesc = TEXT("내용을 전혀 알아볼 수 없다.");
        vecQuestItem.push_back(item);
    }
    {
        ST_QUEST_ITEM_DATA item;
        item.dwId = 3002;
        item.nHP = 0;
        item.nMP = 9999;
        item.strName = TEXT("미래의 호리병");
        item.strDesc = TEXT("2046년에 만들어진 신비한 액체로 마시면 정신력을 최대치로 회복해준다.");
        vecQuestItem.push_back(item);
    }
	{
		ST_QUEST_ITEM_DATA item;
		item.dwId = 3003;
		item.nHP = 0;
		item.nMP = 0;
		item.strName = TEXT("미래 전상현의 쪽지");
		item.strDesc = TEXT("2022년에 세기말 홍수가 발생할거야. 그 때가 되면 (-50, 23) 지점의 땅을 조사해봐. 숨겨둔 장치가 있어.");
		vecQuestItem.push_back(item);
	}
}

void ProfrogQuest::QueryQuest(std::vector<ST_QUEST_DATA>& vecQuest)
{
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 201;
		stQuest.StartCondition = ST_FILTER(201, 0x0000, 0x0001);
		stQuest.vecMessages.push_back(TEXT("하"));
		stQuest.vecMessages.push_back(TEXT("....."));
		stQuest.vecMessages.push_back(TEXT("하아....."));
		stQuest.vecMessages.push_back(TEXT("하아.....하아아......"));
		stQuest.vecMessages.push_back(TEXT("(쿠르르릉)"));
		stQuest.vecMessages.push_back(TEXT("(한숨이 너무 커서 땅이 꺼졌다)"));
		stQuest.vecMessages.push_back(TEXT("게임 연출 지리네."));
		stQuest.vecMessages.push_back(TEXT("근데 난 어쩌다 또 과거로 온걸까?"));
		stQuest.vecMessages.push_back(TEXT("다신 게임 개발 안하기로 했지만"));
		stQuest.vecMessages.push_back(TEXT("또다시 BoB에서 게임개발을 하고 있군."));
		stQuest.vecMessages.push_back(TEXT("9기의 MMORPG 2021"));
		stQuest.vecMessages.push_back(TEXT("10기의 MMORPG 2022"));
		stQuest.vecMessages.push_back(TEXT("그리고 또다시 과거로 와서..."));
		stQuest.vecMessages.push_back(TEXT("11기 MMORPG 2023!!!"));
		stQuest.vecMessages.push_back(TEXT("무한의 굴레!! 누가 나좀 구해줘~~~"));
		stQuest.vecMessages.push_back(TEXT("(이 때 갑자기 앞에서 새끼 고양이가 지나간다.)"));
		stQuest.ClearCondition = ST_FILTER(201, 0x0003);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 2001;
		stQuest.StartCondition = ST_FILTER(201, 0x0001, 0x0003);
		stQuest.vecMessages.push_back(TEXT("미야호.."));
		stQuest.vecMessages.push_back(TEXT("..."));
		stQuest.vecMessages.push_back(TEXT("미야호.... 미야호...."));
		stQuest.vecMessages.push_back(TEXT("(새끼 고양이가 구슬프게 울고 있다. 마치 어린 전상현에게 할말이 있는듯 하다.)"));
		stQuest.ClearCondition = ST_FILTER(201, 0x0007);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 201;
		stQuest.StartCondition = ST_FILTER(201, 0x0003, 0x0007);
		stQuest.vecMessages.push_back(TEXT("엇 저 녀석은?"));
		stQuest.vecMessages.push_back(TEXT("미호~~"));
		stQuest.vecMessages.push_back(TEXT("미호~~ 미호~~"));
		stQuest.vecMessages.push_back(TEXT("네? (갑자기 10기 이준성이 대답한다.)"));
		stQuest.vecMessages.push_back(TEXT("아맞다. 너 닉네임 미호지."));
		stQuest.vecMessages.push_back(TEXT("너 말고"));
		stQuest.vecMessages.push_back(TEXT("미야우~~ 우우 미유웅~"));
		stQuest.vecMessages.push_back(TEXT("음 그렇구나."));
		stQuest.vecMessages.push_back(TEXT("고양이가 자기 주변에 떨어진 호리병을 조사해보래"));
		stQuest.ClearCondition = ST_FILTER(201, 0x000F);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 2002;
		stQuest.StartCondition = ST_FILTER(201, 0x0007, 0x000F);
		stQuest.vecMessages.push_back(TEXT("오래된 구닥다리 호리병처럼 보인다."));
		stQuest.vecMessages.push_back(TEXT("어린 전상현에게 갖다주자."));		
		stQuest.ClearCondition = ST_FILTER(201, 0x001F);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 201;
		stQuest.StartCondition = ST_FILTER(201, 0x000F, 0x001F);
		stQuest.vecMessages.push_back(TEXT("엇 이것은 델몬트 유리병 아냐?"));
		stQuest.vecMessages.push_back(TEXT("요즘 애들은 이거 모를텐데."));
		stQuest.vecMessages.push_back(TEXT("한 때 우리는 쥬스 다 먹으면 버리지 않고 보리차를 채워먹곤 했었지."));
		stQuest.vecMessages.push_back(TEXT("안그래도 목말랐는데 잘됐다."));
		stQuest.vecMessages.push_back(TEXT("푱~(뚜껑 여는 소리)"));
		stQuest.vecMessages.push_back(TEXT("꼴깍꼴깍꼴깍..."));
		stQuest.vecMessages.push_back(TEXT("(미야용!!!! 미야!! 미야~~!!!)"));
		stQuest.vecMessages.push_back(TEXT("(해석)그만 쳐먹어!! 지금 먹으면 안돼!!"));
		stQuest.vecMessages.push_back(TEXT("너무 목이 말라서 나도모르게 마셔버렸네. 헤헷"));
		stQuest.vecMessages.push_back(TEXT("(번쩍!)"));
		stQuest.vecMessages.push_back(TEXT("응??"));
		stQuest.vecMessages.push_back(TEXT("(번쩍!!!)"));
		stQuest.vecMessages.push_back(TEXT("으악! 내몸이!!"));
		stQuest.vecMessages.push_back(TEXT("(번쩍)"));
		stQuest.vecMessages.push_back(TEXT("(번쩍번쩍번쩍)"));
		stQuest.vecMessages.push_back(TEXT("(퓹)")); 
		stQuest.vecMessages.push_back(TEXT("(어린 전상현은 사라졌고, 그걸 지켜보는 새끼 고양이...)"));
		stQuest.ClearCondition = ST_FILTER(201, 0x003F);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 2001;
		stQuest.StartCondition = ST_FILTER(201, 0x001F, 0x003F);
		stQuest.vecMessages.push_back(TEXT("냥냥어:멍청한 녀석 같으니."));
		stQuest.vecMessages.push_back(TEXT("냥냥어:과거로 돌아가는 물약이라고 말해줬더니 그걸 그냥 다 처먹네"));
		stQuest.vecMessages.push_back(TEXT("냥냥어:MMORPG 2023 만들어야할 놈이 사라졌으니"));
		stQuest.vecMessages.push_back(TEXT("냥냥어:올해의 MMORPG는 없는건가?"));
		stQuest.vecMessages.push_back(TEXT("냥냥어:11기 멘티들이 서운해할지도."));
		stQuest.vecMessages.push_back(TEXT("냥냥어:..."));
		stQuest.vecMessages.push_back(TEXT("냥냥어:근데 난 어떻게 돌아가지?"));
		stQuest.vecMessages.push_back(TEXT("이때, 어린 전상현이 있던 자리가 다시 번쩍거린다."));
		stQuest.ClearCondition = ST_FILTER(201, 0x007F);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 201;
		stQuest.StartCondition = ST_FILTER(201, 0x003F, 0x007F);
		stQuest.vecMessages.push_back(TEXT("뻔쩍"));
		stQuest.vecMessages.push_back(TEXT("뻔쩍뻔쩍뻔쩍"));
		stQuest.vecMessages.push_back(TEXT("퓻-------!"));
		stQuest.vecMessages.push_back(TEXT("짜잔!"));
		stQuest.vecMessages.push_back(TEXT("설마 내가 냥냥어를 못알아들었겠어?"));
		stQuest.vecMessages.push_back(TEXT("델몬트 병이 너무 커서 작은 걸로 바꿔왔다구!!"));
		stQuest.vecMessages.push_back(TEXT("2022년도에는 작은 페트병으로 들고 다니기 쉽게 나온단 말이지."));
		stQuest.vecMessages.push_back(TEXT("잠시 과거로 가는약이 잘 드는지 보고 온거라구."));
		stQuest.vecMessages.push_back(TEXT("(저건 거짓말이야!!!)"));
		stQuest.vecMessages.push_back(TEXT("갑자기 10기 임창현이 소리지른다."));
		stQuest.ClearCondition = ST_FILTER(201, 0x00FF);  
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 202;
		stQuest.StartCondition = ST_FILTER(201, 0x007F, 0x00FF);
		stQuest.vecMessages.push_back(TEXT("훗 제가 모를 줄 알아요?"));
		stQuest.vecMessages.push_back(TEXT("아니지 이젠 나보다 어리니까 반말해야지"));
		stQuest.vecMessages.push_back(TEXT("너..!!"));
		stQuest.vecMessages.push_back(TEXT("옵치하려고 돌아온거지?"));
		stQuest.vecMessages.push_back(TEXT("(어린 전상현이 흠칫한다.)"));
		stQuest.vecMessages.push_back(TEXT("역시..."));
		stQuest.vecMessages.push_back(TEXT("하긴 나만한 자리야가 또 없지."));
		stQuest.vecMessages.push_back(TEXT("과거 미래를 다 뒤져봐! 나같은 자랴가 있는지."));
		stQuest.vecMessages.push_back(TEXT("들어는 봤나?"));
		stQuest.vecMessages.push_back(TEXT("\"광물구간 깡패\"라고"));
		stQuest.vecMessages.push_back(TEXT("(뒤에 있던 10기 이준성이 콧방귀를 뀐다.)"));
		stQuest.vecMessages.push_back(TEXT("오늘 밤에도 접속 기다린다."));
		stQuest.vecMessages.push_back(TEXT("기억해라, 밤 11시다."));
		stQuest.vecMessages.push_back(TEXT("(어린 전상현이 하고 싶은 말이 있는 것 같다.)"));
		stQuest.ClearCondition = ST_FILTER(201, 0x01FF);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 201;
		stQuest.StartCondition = ST_FILTER(201, 0x00FF, 0x01FF);
		stQuest.vecMessages.push_back(TEXT("칫..!"));
		stQuest.vecMessages.push_back(TEXT("메인탱에게 자랴는 필수라 어쩔 수 없지"));
		stQuest.vecMessages.push_back(TEXT("그건 그렇고"));
		stQuest.vecMessages.push_back(TEXT("자 그럼..."));
		stQuest.vecMessages.push_back(TEXT("우우웩---! (갑자기 뭔가를 토해낸다.)"));
		stQuest.vecMessages.push_back(TEXT("(꼴롱...)"));
		stQuest.vecMessages.push_back(TEXT("(꼴롱꼴롱...)"));
		stQuest.vecMessages.push_back(TEXT("(꼴롱꼴롱꼴롱...)"));
		stQuest.vecMessages.push_back(TEXT("(작은 패트병에 아까먹은 과거로 가는 약을 뱉어낸다)"));
		stQuest.vecMessages.push_back(TEXT("휴 간신히 페트병에 가득 채웠군"));
		stQuest.vecMessages.push_back(TEXT("나는 다시 게임 개발해야해서 이만..!"));
		stQuest.vecMessages.push_back(TEXT("아참 고양이와 미니게임을 벌이면 쪽지를 하나 줄거야."));
		stQuest.vecMessages.push_back(TEXT("그걸 갖고 다시 와."));
		stQuest.vecMessages.push_back(TEXT("내가 엄청 바쁘지만 해독해줄게."));
		stQuest.ClearCondition = ST_FILTER(201, 0x03FF);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 2001;
		stQuest.StartCondition = ST_FILTER(201, 0x01FF, 0x03FF);
		stQuest.vecMessages.push_back(TEXT("미야호~ Helloworld를 받아랏(ESC로 창을 닫아본다.)"));
		stQuest.pClearGame = new CMiniGame();
		stQuest.ClearCondition = ST_FILTER(201, 0x07FF);
		stQuest.vecRewardItems.push_back(3001);
		vecQuest.push_back(stQuest);
	}
	{
		ST_QUEST_DATA stQuest;
		stQuest.nNpcId = 201;
		stQuest.StartCondition = ST_FILTER(201, 0x07FF, 0x0FFF);
		stQuest.vecMessages.push_back(TEXT("흠.. 역시 가져왔군."));
		stQuest.vecMessages.push_back(TEXT("(쪽지를 받아든다.)"));
		stQuest.vecMessages.push_back(TEXT("호.. 이게 뭐야?"));
		stQuest.vecMessages.push_back(TEXT("다양한 유니코드로 인코딩되었잖아?"));
		stQuest.vecMessages.push_back(TEXT("이 정도 해독하는거야 식은 죽 먹기지."));
		stQuest.vecMessages.push_back(TEXT("(11기 박은규의 과제를 Copy and paste 하여 풀어낸다)"));
		stQuest.vecMessages.push_back(TEXT("어허 이것참 신기하구만."));
		stQuest.vecMessages.push_back(TEXT("누군지는 모르지만 나를 자꾸 굴레에 빠트리는 그 사람이 적은 쪽지 같아."));
		stQuest.vecMessages.push_back(TEXT("심심하면 읽어보던가."));
		stQuest.vecMessages.push_back(TEXT("자, 모든 것을 지켜본 너!!"));
		stQuest.vecMessages.push_back(TEXT("뒤 돌아보지 말구~ 유저 너말야."));
		stQuest.vecMessages.push_back(TEXT("이 페트병과 고양이를 네게 맡긴다!"));
		stQuest.vecMessages.push_back(TEXT("모든 퀘스트를 마치고 고양이를 다시 과거로 보내다오"));
		stQuest.vecMessages.push_back(TEXT("다음번엔 [미래 전상현]으로 게임해보자."));
		stQuest.ClearCondition = ST_FILTER(201, 0xFFFF);
		stQuest.vecRewardItems.push_back(3002);
		stQuest.vecRewardItems.push_back(3003);
		vecQuest.push_back(stQuest);
	}
}
