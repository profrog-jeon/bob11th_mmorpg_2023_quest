#include "pch.h"
#include "MiniGame.h"

CMiniGame::CMiniGame(void)
	: CDlgSuper()
{
}

CMiniGame::~CMiniGame(void)
{
}

void CMiniGame::OnCreate(void)
{
	__super::OnCreate();

	ST_SIZE stWindowSize = { g_nConsoleW, g_nConsoleH };
	ST_POINT stCenterPos = { (g_nConsoleW - stWindowSize.cx) / 2,  (g_nConsoleH - stWindowSize.cy) / 2 };
	SetWindowPos(stCenterPos);
	SetWindowSize(stWindowSize);

	m_TextUI.Create(this, ST_POINT{ 0, 0 }, ST_SIZE{ 20, 3 });
	m_TextUI.SetText("Hello world!!");
}

void CMiniGame::OnClose(void)
{
}

void CMiniGame::OnInput(std::list<ST_KEYSTATE>& listKeyState)
{
	for (ST_KEYSTATE key : listKeyState)
	{
		if (key.bPressed && key.nID == GAMEKEY_SELECT)
			Close(-1);	// 0 �̿��� ������ ������ ����

		if (key.bPressed && key.nID == GAMEKEY_ESC)
			Close(0); // 0���� ������ ����

		if (key.bPressed && key.nID == GAMEKEY_MENU)
		{
			std::tstring strMsg;
			if (0 == CEditBox::Show(this, TEXT("�ؽ�Ʈ�� �Է��ϼ���"), strMsg))
				m_TextUI.SetText(strMsg);

			//int nAnswer = CMessageBox::Show(this, "�޽��� �ڽ� �׽�Ʈ", MB_YESNO);
		}
	}
}

void CMiniGame::OnUpdate(DWORD dwCurrentTick, DWORD dwElapsedTick)
{
	__super::OnUpdate(dwCurrentTick, dwElapsedTick);
}

