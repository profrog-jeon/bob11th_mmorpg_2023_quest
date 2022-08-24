#include "pch.h"
#include "UISuper.h"
#include "DlgSuper.h"
#include "HelperClass.h"

CUISuper::CUISuper(void)
	: m_Pos()
	, m_Size()
	, m_TargetPos()
	, m_TargetSize()
	, m_dwAttribute(0)
{
}

CUISuper::~CUISuper(void)
{
}

void CUISuper::Create(CDlgSuper* pParent, short l, short t, short r, short b, DWORD dwAttribute)
{
	Create(pParent, CPoint(l, t), CSize(r - l + 1, b - t + 1), dwAttribute);
}

void CUISuper::Create(CDlgSuper* pParent, ST_POINT pos, ST_SIZE size, DWORD dwAttribute)
{
	m_dwAttribute = dwAttribute;
	if (pParent)
		pParent->AddUI(this);
	SetWindowPos(pos);
	SetWindowSize(size);

	if (UI_ATTRIBUTE_NO_ANIMATION & m_dwAttribute)
	{
		m_Pos.x = pos.x;
		m_Pos.y = pos.y;
		m_Size.x = size.cx;
		m_Size.y = size.cy;
	}
	else
	{
		int nCenterX = (g_nConsoleW - size.cx) / 2;
		int nCenterY = (g_nConsoleH - size.cy) / 2;

		if (pos.x < 0)
			m_Pos.x = g_nConsoleW;
		else if ((pos.x + size.cx) < (g_nConsoleW / 2))
			m_Pos.x = -size.cx;
		else
			m_Pos.x = nCenterX;

		if (pos.y < 0)
			m_Pos.y = g_nConsoleH;
		else if ((pos.y + size.cy) < (g_nConsoleH / 2))
			m_Pos.y = -size.cy;
		else
			m_Pos.y = nCenterY;
	}
	OnCreate();
}

void CUISuper::Create(CDlgSuper* pParent, ST_RECT rt, DWORD dwAttribute)
{
	Create(pParent, CPoint(rt.l, rt.t), CSize(rt.r - rt.l, rt.b - rt.t + 1), dwAttribute);
}

void CUISuper::SetText(std::string strText)
{
	m_strText = unicode::WCSFromMBS(strText);
}

void CUISuper::SetText(std::wstring strText)
{
	m_strText = strText;
}

void CUISuper::SetWindowPos(CPoint pos, bool bNoAnimate)
{
	m_TargetPos.x = pos.x < 0 ? g_nConsoleW + pos.x : pos.x;
	m_TargetPos.y = pos.y < 0 ? g_nConsoleH + pos.y : pos.y;
	if (bNoAnimate)
		m_Pos = m_TargetPos;
}

void CUISuper::SetWindowSize(CSize size, bool bNoAnimate)
{
	m_TargetSize.x = size.cx;
	m_TargetSize.y = size.cy;
	if (bNoAnimate)
		m_Size = m_TargetSize;
	OnSize();
}

void CUISuper::SetWindowRect(int l, int t, int r, int b)
{
	SetWindowRect(CRect(l, t, r, b));
}

void CUISuper::SetWindowRect(CRect rt)
{
	m_TargetPos = rt.GetPos().MakeVector();
	m_TargetSize = rt.GetSize().MakeVector();
	OnSize();
}

void CUISuper::SetClientPos(CPoint pos, bool bNoAnimate)
{
	if (m_dwAttribute & UI_ATTRIBUTE_NO_BORDER)
	{
		m_TargetPos = pos.MakeVector();
	}
	else
	{
		pos.x -= 1;
		pos.y -= 1;
		m_TargetPos = pos.MakeVector();
	}
	if (bNoAnimate)
		m_Pos = m_TargetPos;
}

void CUISuper::SetClientSize(CSize size, bool bNoAnimate)
{
	if (m_dwAttribute & UI_ATTRIBUTE_NO_BORDER)
	{
		m_TargetSize = size.MakeVector();
	}
	else
	{
		size.cx += 2;
		size.cy += 2;
		m_TargetSize = size.MakeVector();
	}
	if (bNoAnimate)
		m_Size = m_TargetSize;
}

void CUISuper::SetClientRect(int l, int t, int r, int b)
{
	SetClientRect(CRect(l, t, r, b));
}

void CUISuper::SetClientRect(CRect rt)
{
	if (m_dwAttribute & UI_ATTRIBUTE_NO_BORDER)
	{
		m_TargetPos = rt.GetPos().MakeVector();
		m_TargetSize = rt.GetSize().MakeVector();
	}
	else
	{
		rt = rt.Inflate(1, 1, 1, 1);
		m_TargetPos = rt.GetPos().MakeVector();
		m_TargetSize = rt.GetSize().MakeVector();
	}
	OnSize();
}

void CUISuper::SetVisible(bool bVisible)
{
	if (bVisible)
		m_dwAttribute &= ~UI_ATTRIBUTE_INVISIBLE; 
	else
		m_dwAttribute |= UI_ATTRIBUTE_INVISIBLE;
}

void CUISuper::ModifyAttribute(DWORD dwAdd, DWORD dwRemove)
{
	m_dwAttribute |= dwAdd;
	m_dwAttribute &= ~dwRemove;
}

bool CUISuper::IsVisible(void)
{
	return 0 == (m_dwAttribute & UI_ATTRIBUTE_INVISIBLE);
}

std::wstring CUISuper::GetText(void)
{
	return m_strText;
}

void CUISuper::DrawUI(CDisplayBuffer& vecBuffer)
{
	if (m_Size.x < 1 || m_Size.y < 1)
		return;

	CRect stDrawArea = CRect(m_Pos.MakePoint(), m_Size.MakeSize());
	if (0 == (m_dwAttribute & UI_ATTRIBUTE_NO_BORDER))
	{
		vecBuffer.DrawRectangle(stDrawArea);
		stDrawArea.l++;
		stDrawArea.t++;
		stDrawArea.r--;
		stDrawArea.b--;
	}

	CSize stDrawAreaSize = stDrawArea.GetSize();
	if (stDrawAreaSize.cx < 1 || stDrawAreaSize.cy < 1)
		return;

	OnDrawUI(vecBuffer, stDrawArea);
}

ST_POINT CUISuper::GetPos(void)
{
	return m_TargetPos.MakePoint();
}

ST_SIZE CUISuper::GetSize(void)
{
	ST_SIZE size = m_TargetSize.MakeSize();
	if (0 == (m_dwAttribute & UI_ATTRIBUTE_NO_BORDER))
		size.cx -= 2;
	return size;
}

CRect CUISuper::GetWindowRect(void)
{
	return CRect(m_TargetPos.MakePoint(), m_TargetSize.MakeSize());
}

CRect CUISuper::GetClientRect(void)
{
	CRect WindowRect(m_TargetPos.MakePoint(), m_TargetSize.MakeSize());
	if (m_dwAttribute & UI_ATTRIBUTE_NO_BORDER)
		return WindowRect;

	return WindowRect.Deflate(1, 1, 1, 1);
}

void CUISuper::OnCreate(void)
{
}

void CUISuper::OnSize(void)
{
}

void CUISuper::OnUpdate(DWORD dwCurrentTick, DWORD dwElapsedTick)
{
	double dElapsedTime = dwElapsedTick * 0.001;
	ST_VECTOR stPosDiff = m_TargetPos - m_Pos;
	if (std::abs(stPosDiff.y) < 0.5)
		m_Pos = m_TargetPos;
	else
		m_Pos += stPosDiff * dElapsedTime * 3;

	ST_VECTOR stSizeDiff = m_TargetSize - m_Size;
	if (std::abs(stSizeDiff.y) < 0.5)
		m_Size = m_TargetSize;
	else
		m_Size += stSizeDiff * dElapsedTime * 15;

}

void CUISuper::OnDrawWorld(CDisplayBuffer& vecBuffer)
{
}
