#pragma once

#include "UISuper.h"

class CListUI : public CUISuper
{
	int m_nScrollPos;
	int m_nCursorIndex;
	int m_nAlignCol;

	struct ST_ITEM_DATA
	{
		std::wstring strValue;
		int nTag;
		const void* pContext;
	};
	std::vector<ST_ITEM_DATA> m_vecItems;

public:
	CListUI(void);

	void Clear(void);
	void AddItem(std::string strValue, int nTag = 0, const void* pContext = nullptr);
	void AddItem(std::wstring strValue, int nTag = 0, const void* pContext = nullptr);
	void SetItemAlign(int nColCount = -1);		// -1은 항목 길이에 따라 자동 조절
	void AdjustHeight(int nRowCount = -1);

	int GetItemCount(void);
	std::wstring GetItem(int nIndex);
	int GetItemTag(int nIndex);
	const void* GetItemContext(int nIndex);

	int GetCurPos(void);
	void SetCurPos(int nIndex);
	void MoveCurPos(int nOffsetX, int nOffsetY);

	void OnDrawUI(CDisplayBuffer& vecBuffer, CRect rtDrawArea);
};

