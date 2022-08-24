#include "pch.h"
#include "PictureUI.h"
#include "HelperFunc.h"

CPictureUI::CPictureUI(void)
	: CUISuper()
{
}

CPictureUI::~CPictureUI(void)
{
}

void CPictureUI::SetImage(std::vector<std::tstring> vecImage)
{
	CDisplayBuffer vecTempImage;
	for(std::tstring& strLine : vecImage)
		vecTempImage.push_back(strLine);

	SetImage(vecTempImage);
}

void CPictureUI::SetImage(CDisplayBuffer vecImage)
{
	m_vecImageData.clear();
	for (std::wstring& strLine : vecImage)
	{
		Replace(strLine, TEXT("\t"), TEXT("    "));
		m_vecImageData.push_back(strLine);
	}
}

void CPictureUI::OnDrawUI(CDisplayBuffer& vecBuffer, CRect rtDrawArea)
{
	ST_POINT pos = rtDrawArea.GetPos();
	ST_SIZE size = rtDrawArea.GetSize();

	for (size_t i=0; i<m_vecImageData.size(); i++)
	{
		const std::wstring& strSrcLine = m_vecImageData[i];
		if (size.cy <= i)
			return;

		int y = pos.y + (int)i;
		if (vecBuffer.size() <= y)
			return;

		vecBuffer.DrawString(pos.x, y, strSrcLine, (size_t)size.cx);
	}
}
