#pragma once
#include <string>

struct ST_STRING_CONTEXT
{
	// ���� Ŀ�� ��ġ
	int nCursorPos; 

	// ������� �Ϸ�� ���ڿ�
	std::wstring strContext;

	// ���� �������� ����
	std::wstring strUnderConstruct;
};

struct ST_CONSTRUCT
{
public:
	// �ʼ� �ε��� ��ȣ
	int choseong;

	// �߼� �ε��� ��ȣ
	int jungseong;

	// ���� �ε��� ��ȣ
	int jongseong;
	void clear();
};