#pragma once

#include "Struct.h"
#include "HelperClass.h"
#include "DisplayBuffer.h"

enum E_UI_ATTRIBUTE
{
	UI_ATTRIBUTE_NO_BORDER = 0x01 << 0,
	UI_ATTRIBUTE_INVISIBLE = 0x01 << 1,
	UI_ATTRIBUTE_NO_ANIMATION = 0x01 << 2,
};

class CDlgSuper;
class CUISuper
{
	ST_VECTOR m_Pos;
	ST_VECTOR m_Size;
	ST_VECTOR m_TargetPos;
	ST_VECTOR m_TargetSize;
	DWORD m_dwAttribute;

	std::wstring m_strText;

protected:
	CUISuper(void);
	virtual ~CUISuper(void);

public:
	virtual void Create(CDlgSuper* pParent, short l, short t, short r, short b, DWORD dwAttribute = 0);
	virtual void Create(CDlgSuper* pParent, ST_POINT pos, ST_SIZE size, DWORD dwAttribute = 0);
	virtual void Create(CDlgSuper* pParent, ST_RECT rt, DWORD dwAttribute = 0);
	virtual void SetText(std::string strText);
	virtual void SetText(std::wstring strText);
	virtual void SetWindowPos(CPoint pos, bool bNoAnimate = false);
	virtual void SetWindowSize(CSize size, bool bNoAnimate = false);
	virtual void SetWindowRect(int l, int t, int r, int b);
	virtual void SetWindowRect(CRect rt);
	virtual void SetClientPos(CPoint pos, bool bNoAnimate = false);
	virtual void SetClientSize(CSize size, bool bNoAnimate = false);
	virtual void SetClientRect(int l, int t, int r, int b);
	virtual void SetClientRect(CRect rt);
	virtual void SetVisible(bool bVisible);
	virtual void ModifyAttribute(DWORD dwAdd, DWORD dwRemove);
	virtual bool IsVisible(void);

	virtual std::wstring GetText(void);

	virtual void DrawUI(CDisplayBuffer& vecBuffer);

	virtual ST_POINT GetPos(void);
	virtual ST_SIZE GetSize(void);
	virtual CRect GetWindowRect(void);
	virtual CRect GetClientRect(void);

	virtual void OnCreate(void);
	virtual void OnSize(void);
	virtual void OnUpdate(DWORD dwCurrentTick, DWORD dwElapsedTick);
	virtual void OnDrawWorld(CDisplayBuffer& vecBuffer);
	virtual void OnDrawUI(CDisplayBuffer& vecBuffer, CRect rtDrawArea) = 0;
};

