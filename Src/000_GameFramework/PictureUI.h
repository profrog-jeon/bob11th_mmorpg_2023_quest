#pragma once

#include "UISuper.h"

class CPictureUI : public CUISuper
{
	CDisplayBuffer m_vecImageData;

public:
	CPictureUI(void);
	~CPictureUI(void);

	void SetImage(std::vector<std::tstring> vecImage);
	void SetImage(CDisplayBuffer vecImage);

	void OnDrawUI(CDisplayBuffer& vecBuffer, CRect rtDrawArea);
};

