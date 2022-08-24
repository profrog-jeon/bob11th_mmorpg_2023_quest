#include "pch.h"
#include "HelperFunc.h"

void TokenizeMessage(std::string strContext, std::vector<std::wstring>& outMessages, size_t tMaxTextLen)
{
	TokenizeMessage(unicode::WCSFromMBS(strContext), outMessages, tMaxTextLen);
}

void TokenizeMessage(std::string strContext, std::vector<std::string>& outMessages, size_t tMaxTextLen)
{
	std::vector<std::wstring> vecTemp;
	TokenizeMessage(unicode::WCSFromMBS(strContext), vecTemp, tMaxTextLen);

	for (std::wstring strLine : vecTemp)
		outMessages.push_back(unicode::MBSFromWCS(strLine));
}

void TokenizeMessage(std::wstring strContext, std::vector<std::wstring>& outMessages, size_t tMaxTextLen)
{
	std::vector<std::wstring> vecLines;

	// �޽����� ĳ���� ���Ϻ��� �߶� vector�� �־��
	size_t tPos = 0;
	while (tPos < strContext.length())
	{
		size_t tIndex = strContext.find(TEXT('\n'), tPos);
		if (tIndex == std::string::npos)
		{
			vecLines.push_back(strContext.substr(tPos));
			break;
		}

		vecLines.push_back(strContext.substr(tPos, tIndex - tPos));
		tPos = tIndex + 1;
	}

	// ���� �ϳ��� ������ �ʹ� ��� ȭ�� ���̿� ���߾� ���� �ٷ� �ڸ�
	if (tMaxTextLen < 10)
		tMaxTextLen = 10;
	for (std::wstring strLine : vecLines)
	{
		for (size_t i = 0; i < strLine.size(); i += tMaxTextLen)
		{
			size_t tRemainedSize = strLine.size() - i;
			outMessages.push_back(strLine.substr(i, std::min<size_t>(tMaxTextLen, tRemainedSize)));
		}
	}

	// �޽����� ������ �ּ� �� ���� �����ǵ��� ������
	if (outMessages.empty())
		outMessages.push_back(TEXT("�޽����� �����ϴ�."));
}

std::wstring Replace(std::wstring strContext, std::wstring strTarget, std::wstring strReplace)
{
	size_t tPos = 0;
	while ((tPos = strContext.find(strTarget, tPos)) != std::string::npos)
	{
		strContext.replace(tPos, strTarget.length(), strReplace.c_str());
		tPos += strReplace.length();
	}

	return strContext;
}