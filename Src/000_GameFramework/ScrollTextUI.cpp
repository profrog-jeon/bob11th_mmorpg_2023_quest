#include "pch.h"
#include "ScrollTextUI.h"
#include "HelperFunc.h"
#include "HelperClass.h"

CScrollTextUI::CScrollTextUI(void)
	: CUISuper()
	, m_nViewPos(-1)
{
}

CScrollTextUI::~CScrollTextUI(void)
{
}

void CScrollTextUI::Clear(void)
{
	m_nViewPos = -1;
	m_vecText.clear();
}

void CScrollTextUI::SetViewPos(int nPos)
{
	m_nViewPos = nPos;
}

void CScrollTextUI::SetText(std::string strText)
{
	__super::SetText(strText);
}

void CScrollTextUI::SetText(std::wstring strText)
{
	__super::SetText(strText);
}

void CScrollTextUI::AddText(std::string strText)
{
	AddText(unicode::WCSFromMBS(strText));
}

void CScrollTextUI::AddText(std::wstring strText)
{
	size_t tPos = 0;
	while (true)
	{
		size_t tIndex = strText.find(TEXT('\n'), tPos);
		if (std::tstring::npos == tIndex)
		{
			std::wstring strItem = strText.substr(tPos);
			if(!strItem.empty())
				m_vecText.push_back(strItem);
			break;
		}
		
		std::wstring strItem = strText.substr(tPos, tIndex - tPos);
		if (!strItem.empty())
			m_vecText.push_back(strItem);
		tPos = tIndex + 1;
	}
}

size_t CScrollTextUI::GetLineCount(void)
{
	return m_vecText.size();
}

void CScrollTextUI::OnSize(void)
{
}

void CScrollTextUI::OnDrawUI(CDisplayBuffer& vecBuffer, CRect rtDrawArea)
{
	ST_SIZE size = rtDrawArea.GetSize();

	std::vector<std::wstring> vecMultiLine;
	for (int i = 0; i < (int)m_vecText.size(); i++)
		TokenizeMessage(m_vecText[i], vecMultiLine, size.cx);

	int nViewPos = m_nViewPos;
	if (m_nViewPos < 0)
	{
		nViewPos = (int)vecMultiLine.size() - size.cy;
		if (nViewPos < 0)
			nViewPos = 0;
	}

	int y = rtDrawArea.t;
	for (int i = nViewPos; i < (int)vecMultiLine.size(); i++)
	{
		if (rtDrawArea.b < y)
			return;

		vecBuffer.DrawString(rtDrawArea.l, y++, vecMultiLine[i], (size_t)size.cx);
	}
}
