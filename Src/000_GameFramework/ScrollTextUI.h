#pragma once
#include "UISuper.h"

class CScrollTextUI : public CUISuper
{
	int m_nViewPos;
	std::vector<std::wstring> m_vecText;

public:
	CScrollTextUI(void);
	virtual ~CScrollTextUI(void);

	virtual void Clear(void);
	virtual void SetViewPos(int nPos = -1);
	virtual void AddText(std::string strText);
	virtual void AddText(std::wstring strText);
	size_t GetLineCount(void);

	virtual void OnSize(void);
	virtual void OnDrawUI(CDisplayBuffer& vecBuffer, CRect rtDrawArea);

private:
	// 못쓰게 막음
	virtual void SetText(std::string strText);
	virtual void SetText(std::wstring strText);
};

