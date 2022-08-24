#include "pch.h"
#include "EditBox.h"
#include "Unicode.h"
#include "HelperClass.h"

CEditBox::CEditBox(CDlgSuper* pParent, std::tstring strTitle, size_t tMaxLength)
	:CDlgSuper(pParent)
	, m_strTitle(strTitle)
	, m_tMaxLength(tMaxLength)
	, m_tCursorPos(0)
	, m_StringBuilder()
{
}

CEditBox::~CEditBox(void)
{
}

void CEditBox::OnCreate(void)
{
	CPoint pos((g_nConsoleW - m_tMaxLength) / 2, g_nConsoleH / 2 - 2);
	SetWindowPos(pos);
	CSize size(m_tMaxLength + 2, 4);
	SetWindowSize(size.Inflate(1, 1));
	ModifyAttribute(UI_ATTRIBUTE_NO_BORDER, 0);

	if (!m_strTitle.empty())
	{
		m_TitleUI.Create(this, 0, 0, size.cx, 2, UI_ATTRIBUTE_NO_ANIMATION);
		m_TitleUI.SetText(m_strTitle);
	}
	m_TextUI.Create(this, 0, 2, size.cx, size.cy, UI_ATTRIBUTE_NO_ANIMATION);

	m_KeyboardInput = g_pGameData->input;
	m_KeyboardInput.Clear();

	// ¼ýÀÚ
	for (int i = 0x30; i < 0x40; i++)
		m_KeyboardInput.Register(i, i);

	// ¾ËÆÄ¹î
	for (int i = 0x41; i < 0x5B; i++)
		m_KeyboardInput.Register(i, i);

	m_KeyboardInput.Register(VK_DELETE, VK_DELETE);
	m_KeyboardInput.Register(VK_BACK, VK_BACK);
	m_KeyboardInput.Register(VK_RETURN, VK_RETURN);
	m_KeyboardInput.Register(VK_ESCAPE, VK_ESCAPE);
	m_KeyboardInput.Register(VK_LEFT, VK_LEFT);
	m_KeyboardInput.Register(VK_RIGHT, VK_RIGHT);
	m_KeyboardInput.Register(VK_UP, VK_UP);
	m_KeyboardInput.Register(VK_SPACE, ' ');
	m_KeyboardInput.Register(VK_DOWN, VK_DOWN);
	m_KeyboardInput.Register(VK_OEM_PLUS,	'=');
	m_KeyboardInput.Register(VK_OEM_COMMA,	',');
	m_KeyboardInput.Register(VK_OEM_MINUS,	'-');
	m_KeyboardInput.Register(VK_OEM_PERIOD, '.');
	m_KeyboardInput.Register(VK_OEM_1, ';');
	m_KeyboardInput.Register(VK_OEM_2, '/');
	m_KeyboardInput.Register(VK_OEM_3, '~');
	m_KeyboardInput.Register(VK_OEM_4, '[');
	m_KeyboardInput.Register(VK_OEM_5, '|');
	m_KeyboardInput.Register(VK_OEM_6, ']');
	m_KeyboardInput.Register(VK_OEM_7, '\'');
	m_KeyboardInput.Register(VK_HANGUL, VK_HANGUL);
	m_KeyboardInput.Register(VK_CAPITAL, VK_CAPITAL);

}

void CEditBox::OnInput(std::list<ST_KEYSTATE>& listKeyState)
{
	std::list<ST_KEYSTATE> listTyping;
	m_KeyboardInput.Query(listTyping);

	bool IsCpasLockEnabled = m_KeyboardInput.IsCpasLockEnabled();

	for (ST_KEYSTATE stKey : listTyping)
	{
		if (!stKey.bPressed)
			continue;

		if (VK_RETURN == stKey.nVirtKey)
			Close(0);

		if (VK_ESCAPE == stKey.nVirtKey)
			Close(-1);
	}

	m_StringBuilder.BuildContext(listTyping, IsCpasLockEnabled);
	m_strContext = m_StringBuilder.GetContext();
	m_TextUI.SetText(m_StringBuilder.GetContextWithCursor());
}

void CEditBox::OnUpdate(DWORD dwCurrentTick, DWORD dwElapsedTick)
{
	__super::OnUpdate(dwCurrentTick, dwElapsedTick);
}

void CEditBox::InsertChar(char cCharL, char cCharU)
{
	if (m_KeyboardInput.IsEnabledCapsLock())
		m_strContext.insert(m_tCursorPos, 1, cCharU);
	else
		m_strContext.insert(m_tCursorPos, 1, cCharL);
	m_tCursorPos++;
}

void CEditBox::OnDrawUI(CDisplayBuffer& vecBuffer, CRect rtDrawArea)
{
	__super::OnDrawUI(vecBuffer, rtDrawArea);
}

std::tstring CEditBox::GetContext(void)
{
	return m_strContext;
}

int CEditBox::Show(CDlgSuper* pParent, std::tstring strTitle, std::tstring& outText, size_t tMaxLength)
{
	CEditBox instance(pParent, strTitle, tMaxLength);
	int nRet = instance.DoModal();
	if (nRet)
		return nRet;

	outText = instance.GetContext();
	return 0;
}
