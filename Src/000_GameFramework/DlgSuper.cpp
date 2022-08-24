#include "pch.h"
#include "DlgSuper.h"

CDlgSuper::CDlgSuper(CDlgSuper* pParent)
	: CUISuper()
	, m_pParent(pParent)
	, m_bIsCreated(false)
	, m_bIsClosed(false)
	, m_nExitCode(0)
{
}

CDlgSuper::~CDlgSuper(void)
{
	m_listUI.clear();
}

void CDlgSuper::Close(int nExitCode)
{
	if (m_bIsClosed)
		return;

	char szTest[20];
	sprintf_s(szTest, 20, "Close(%d)\n", nExitCode);
	OutputDebugStringA(szTest);
	
	m_bIsClosed = true;
	m_nExitCode = nExitCode;
}

void CDlgSuper::OnCreate(void)
{
	m_bIsCreated = true;
	m_bIsClosed = false;
}

void CDlgSuper::OnClose(void)
{
	m_bIsCreated = false;
	m_listUI.clear();
}

void CDlgSuper::AddUI(CUISuper* pChild)
{
	pChild->ModifyAttribute(UI_ATTRIBUTE_NO_ANIMATION, 0);
	m_listUI.push_back(pChild);
}

void CDlgSuper::SetParent(CDlgSuper* pParent)
{
	m_pParent = pParent;
}

int CDlgSuper::DoModal(void)
{
	OnCreate();

	CDisplayBuffer vecDisplayBuffer;
	vecDisplayBuffer.Create(101, 101);
	while (!m_bIsClosed)
	{
		const DWORD dwCurrentTick = GetTickCount();

		std::list<ST_KEYSTATE> listKeyState;
		g_pGameData->input.Query(listKeyState);
		OnInput(listKeyState);
		Update(dwCurrentTick, g_nDeltaTick);

		vecDisplayBuffer.Clear();
		DrawUI(vecDisplayBuffer);
		g_pGameData->output.Render(vecDisplayBuffer);

		{
			static DWORD dwLastUpdateTick = GetTickCount();
			if (dwCurrentTick < dwLastUpdateTick)
			{
				DWORD dwRemainedTick = dwLastUpdateTick - dwCurrentTick;
				Sleep(std::min<DWORD>(dwRemainedTick, g_nDeltaTick));
			}
			dwLastUpdateTick += g_nDeltaTick;
		}
	}

	OnClose();
	return m_nExitCode;
}

void CDlgSuper::Update(DWORD dwCurrentTick, DWORD dwElapsedTick)
{
	if (m_pParent)
		m_pParent->Update(dwCurrentTick, dwElapsedTick);
	OnUpdate(dwCurrentTick, dwElapsedTick);
}

void CDlgSuper::DrawUI(CDisplayBuffer& vecBuffer)
{
	if (m_pParent)
		m_pParent->DrawUI(vecBuffer);
	__super::DrawUI(vecBuffer);
}

void CDlgSuper::OnInput(std::list<ST_KEYSTATE>& listKeyState)
{
}

void CDlgSuper::OnUpdate(DWORD dwCurrentTick, DWORD dwElapsedTick)
{
	__super::OnUpdate(dwCurrentTick, dwElapsedTick);
	for (CUISuper* pUI : m_listUI)
		pUI->OnUpdate(dwCurrentTick, dwElapsedTick);
}

void CDlgSuper::OnDrawUI(CDisplayBuffer& vecBuffer, CRect rtDrawArea)
{
	ST_SIZE size = rtDrawArea.GetSize();

	CDisplayBuffer vecClientBuffer;
	vecClientBuffer.Create(size.cx, size.cy);

	for (CUISuper* pUI : m_listUI)
	{
		if (!pUI->IsVisible())
			continue;
		pUI->DrawUI(vecClientBuffer);
	}

	vecBuffer.BitBlt(rtDrawArea.l, rtDrawArea.t, vecClientBuffer);
}