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

	// 메시지를 캐리지 리턴별로 잘라서 vector에 넣어둠
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

	// 만일 하나의 라인이 너무 길면 화면 길이에 맞추어 여러 줄로 자름
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

	// 메시지가 없으면 최소 한 줄은 유지되도록 수정함
	if (outMessages.empty())
		outMessages.push_back(TEXT("메시지가 없습니다."));
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