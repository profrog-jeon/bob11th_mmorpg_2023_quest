#pragma once

#include "../000_MultiLanguage/CStringBuilder.h"
#include "DlgSuper.h"
#include "TextUI.h"
#include "KeyInput.h"

class CEditBox : public CDlgSuper
{
	CTextUI m_TitleUI;
	CTextUI m_TextUI;
	CKeyInput m_KeyboardInput;

	std::tstring m_strTitle;
	std::tstring m_strContext;
	size_t m_tMaxLength;
	size_t m_tCursorPos;

	CStringBuilder m_StringBuilder;

public:
	CEditBox(CDlgSuper* pParent, std::tstring strTitle, size_t tMaxLength);
	~CEditBox(void);

	void OnDrawUI(CDisplayBuffer& vecBuffer, CRect rtDrawArea);

	std::tstring GetContext(void);
	static int Show(CDlgSuper* pParent, std::tstring strTitle, std::tstring& outText, size_t tMaxLength = (size_t)(g_nConsoleW * 0.8));

private:
	void OnCreate(void);
	void OnInput(std::list<ST_KEYSTATE>& listKeyState);
	void OnUpdate(DWORD dwCurrentTick, DWORD dwElapsedTick);

	void InsertChar(char cCharL, char cCharU);
};

