#pragma once
#include <map>
#include "CharSetSuper.h"

#define VOWEL 0x0001		//����
#define CONSONANT 0x0002	//����

#define UNICODE_BASE 44032		// 0xAC00, Unicode �⺻ ��
#define NUM_OF_CHOSEONG 19		// �ʼ� ��
#define NUM_OF_JUNGSEONG 21		// �߼� ��
#define NUM_OF_JONGSEONG 28		// ���� ��

#define CONSTRUCT_DEFAULT 99	// ����ü default ��

enum E_CONSTRUCT_STATE
{
	BLANK = 0,					// ����ִ� ����
	ONLY_CHOSEONG,				// �ʼ��� �ִ� ����
	ONLY_JUNGSEONG,				// �߼��� �ִ� ����
	NO_JONGSEONG_COMB_ABLE_H,	// ��ħ ���� ���հ��� ���� "��"
	NO_JONGSEONG_COMB_ABLE_N,	// ��ħ ���� ���հ��� ���� "��"
	NO_JONGSEONG_COMB_ABLE_M,	// ��ħ ���� ���հ��� ���� "��"
	NO_JONGSEONG_COMB_UNABLE,	// ��ħ ���� ���պҰ� ����
	ONE_JONGSEONG_COMB_ABLE_R,	// Ȭ��ħ ���հ��� ���� "��"
	ONE_JONGSEONG_COMB_ABLE_S,	// Ȭ��ħ ���հ��� ���� "��"
	ONE_JONGSEONG_COMB_ABLE_F,	// Ȭ��ħ ���հ��� ���� "��"
	ONE_JONGSEONG_COMB_ABLE_Q,	// Ȭ��ħ ���հ��� ���� "��"
	ONE_JONGSEONG_COMB_UNABLE,	// Ȭ��ħ ���պҰ� ����
	DOUBLE_JONGSEONG			// �ֹ�ħ ����
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