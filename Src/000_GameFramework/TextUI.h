#pragma once

#include "UISuper.h"

class CTextUI : public CUISuper
{
public:
	CTextUI(void);
	virtual ~CTextUI(void);

	virtual void OnDrawUI(CDisplayBuffer& vecBuffer, CRect rtDrawArea);
};

