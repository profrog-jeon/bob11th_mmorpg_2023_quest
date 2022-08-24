#include "pch.h"
#include "ListUI.h"

CListUI::CListUI(void)
	: CUISuper()
	, m_nScrollPos(0)
	, m_nCursorIndex(0)
	, m_nAlignCol(1)
{
}

void CListUI::Clear(void)
{
	m_vecItems.clear();
	m_nScrollPos = 0;
	m_nCursorIndex = 0;
	m_nAlignCol = 1;
}

void CListUI::AddItem(std::string strValue, int nTag, const void* pContext)
{
	AddItem(unicode::WCSFromMBS(strValue), nTag, pContext);
}

void CListUI::AddItem(std::wstring strValue, int nTag, const void* pContext)
{
	ST_ITEM_DATA item;
	item.strValue = strValue;
	item.nTag = nTag;
	item.pContext = pContext;
	m_vecItems.push_back(item);
}

void CListUI::SetItemAlign(int nColCount)
{
	if (nColCount < 0)
	{
		size_t tMaxItemLen = 0;
		for (const ST_ITEM_DATA& item: m_vecItems)
		{
			if (tMaxItemLen < item.strValue.length())
				tMaxItemLen = item.strValue.length();
		}

		int nWidth = GetSize().cx;
		nColCount = nWidth / (int)(tMaxItemLen + 2);
	}

	if (nColCount == 0)
		nColCount = 1;

	m_nAlignCol = nColCount;
}

void CListUI::AdjustHeight(int nRowCount)
{
	if (nRowCount < 0)
		nRowCount = (int)m_vecItems.size();
	
	ST_SIZE size = GetClientRect().GetSize();
	size.cy = nRowCount;
	SetClientSize(size);
}

int CListUI::GetItemCount(void)
{
	return (int)m_vecItems.size();
}

std::wstring CListUI::GetItem(int nIndex)
{
	if (nIndex < (int)m_vecItems.size())
		return m_vecItems[nIndex].strValue;
	return L"";
}

int CListUI::GetItemTag(int nIndex)
{
	if (nIndex < (int)m_vecItems.size())
		return m_vecItems[nIndex].nTag;
	return 0;
}

const void* CListUI::GetItemContext(int nIndex)
{
	if (nIndex < (int)m_vecItems.size())
		return m_vecItems[nIndex].pContext;
	return nullptr;
}

int CListUI::GetCurPos(void)
{
	return m_nCursorIndex;
}

void CListUI::SetCurPos(int nIndex)
{
	m_nCursorIndex = nIndex;
}

void CListUI::MoveCurPos(int nOffsetX, int nOffsetY)
{
	m_nCursorIndex += nOffsetX + nOffsetY * m_nAlignCol;
	if (m_vecItems.size() <= m_nCursorIndex)
	{
		if (nOffsetY < 0)
		{
			m_nCursorIndex += (int)(m_vecItems.size() / m_nAlignCol + 1) * m_nAlignCol;
			if (m_vecItems.size() <= m_nCursorIndex)
				m_nCursorIndex = (int)m_vecItems.size() - 1;
		}
		else if (0 < nOffsetY)
			m_nCursorIndex = m_nCursorIndex % m_nAlignCol;
		else if (0 < nOffsetX)
			m_nCursorIndex = 0;
		else
			m_nCursorIndex = (int)m_vecItems.size() - 1;
	}

	int nListHeight = GetClientRect().GetSize().cy;
	int nMinShowingIndex = m_nScrollPos * m_nAlignCol + 1;
	int nMaxShowingIndex = (m_nScrollPos + nListHeight) * m_nAlignCol;
	if (m_nCursorIndex < nMinShowingIndex)
		m_nScrollPos = m_nCursorIndex / m_nAlignCol;
	if (nMaxShowingIndex <= m_nCursorIndex)
		m_nScrollPos = m_nCursorIndex / m_nAlignCol - (nListHeight - 1);
}

void CListUI::OnDrawUI(CDisplayBuffer& vecBuffer, CRect rtDrawArea)
{
	CPoint pos = rtDrawArea.GetPos();
	CSize size = rtDrawArea.GetSize();

	const int nCursorSize = 2;
	int nItemLength = (int)size.cx / m_nAlignCol;
	for (size_t i = m_nScrollPos * m_nAlignCol; i < m_vecItems.size(); i++)
	{
		int x = (int)i % m_nAlignCol;
		int y = (int)i / m_nAlignCol - m_nScrollPos;
		int nLeft = (int)pos.x + x * nItemLength + nCursorSize;
		int nTop = pos.y + y;
		if (nTop < 0)
			continue;

		if (vecBuffer.size() <= nTop)
			break;

		if ((int)size.cy <= y)
			break;

		int nLength = (int)size.cx / m_nAlignCol - nCursorSize;
		if (nLength < 1)
			continue;

		vecBuffer.DrawString(nLeft, nTop, m_vecItems[i].strValue, nLength);

		if ((int)i == m_nCursorIndex)
		{
			char szCursor[] = { 26, 0 };// 화살표 커서
			vecBuffer.DrawString(nLeft - 1, nTop, szCursor);
		}
	}
}
