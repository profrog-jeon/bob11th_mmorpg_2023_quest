#pragma once
#include <map>
#include "CharSetSuper.h"

#define VOWEL 0x0001		//모음
#define CONSONANT 0x0002	//자음

#define UNICODE_BASE 44032		// 0xAC00, Unicode 기본 값
#define NUM_OF_CHOSEONG 19		// 초성 수
#define NUM_OF_JUNGSEONG 21		// 중성 수
#define NUM_OF_JONGSEONG 28		// 종성 수

#define CONSTRUCT_DEFAULT 99	// 구조체 default 값

enum E_CONSTRUCT_STATE
{
	BLANK = 0,					// 비어있는 상태
	ONLY_CHOSEONG,				// 초성만 있는 음절
	ONLY_JUNGSEONG,				// 중성만 있는 음절
	NO_JONGSEONG_COMB_ABLE_H,	// 받침 없는 조합가능 음절 "ㅗ"
	NO_JONGSEONG_COMB_ABLE_N,	// 받침 없는 조합가능 음절 "ㅜ"
	NO_JONGSEONG_COMB_ABLE_M,	// 받침 없는 조합가능 음절 "ㅡ"
	NO_JONGSEONG_COMB_UNABLE,	// 받침 없는 조합불가 음절
	ONE_JONGSEONG_COMB_ABLE_R,	// 홑받침 조합가능 음절 "ㄱ"
	ONE_JONGSEONG_COMB_ABLE_S,	// 홑받침 조합가능 음절 "ㄴ"
	ONE_JONGSEONG_COMB_ABLE_F,	// 홑받침 조합가능 음절 "ㄹ"
	ONE_JONGSEONG_COMB_ABLE_Q,	// 홑받침 조합가능 음절 "ㅂ"
	ONE_JONGSEONG_COMB_UNABLE,	// 홑밭침 조합불가 음절
	DOUBLE_JONGSEONG			// 쌍받침 음절
};

class CHangulCharset : public CCharSetSuper
{
private:
	E_CONSTRUCT_STATE state = BLANK;
	ST_CONSTRUCT stCurrentConstruct = { CONSTRUCT_DEFAULT, CONSTRUCT_DEFAULT, 0 };
	
	std::string StrFromVirtualKey(int nVirtualKey, bool bShiftPressed);
	int GetIndexNum(const char* chararray[], int SizeofArray, const char* c);
	int CheckStr(std::string c);
	int AssemUnicode(ST_CONSTRUCT stCurrentConstruct);
	void DeleteChar(int nVirtualKey, ST_STRING_CONTEXT& context);

public:
	void Update(int nVirtualKey, ST_STRING_CONTEXT& context, bool bShiftPressed);
};