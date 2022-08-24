#include "pch.h"
#include "TextUI.h"
#include "HelperFunc.h"
#include "HelperClass.h"

CTextUI::CTextUI(void)
	: CUISuper()
{
}

CTextUI::~CTextUI(void)
{
}

void CTextUI::OnDrawUI(CDisplayBuffer& vecBuffer, CRect rtDrawArea)
{
	ST_SIZE size = rtDrawArea.GetSize();
	vecBuffer.DrawString(rtDrawArea.GetPos(), GetText(), size.cx);
}
