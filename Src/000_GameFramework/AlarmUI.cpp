#include "pch.h"
#include "AlarmUI.h"
#include "HelperFunc.h"
#include "Setting.h"
#include "HelperClass.h"

CAlarmUI::CAlarmUI(void)
	: CScrollTextUI()
	, m_dwTimeOutTick(0)
{
}

CAlarmUI::~CAlarmUI()
{
}

void CAlarmUI::Clear(void)
{
	__super::Clear();
	m_dwTimeOutTick = 0;
}

void CAlarmUI::Alarm(std::tstring strMsg, DWORD dwDuring)
{
	Clear();
	m_dwTimeOutTick = GetTickCount() + dwDuring;

	std::vector<std::wstring> vecMessage;
	vecMessage.clear();

	TokenizeMessage(strMsg, vecMessage, g_nConsoleW * 0.8);

	size_t tMaxTextLen = 10;
	for (std::wstring strLine : vecMessage)
	{
		if (tMaxTextLen < strLine.size())
			tMaxTextLen = strLine.size();
	}

	CPoint pos;
	pos.x = (g_nConsoleW - tMaxTextLen) / 2;
	pos.y = (g_nConsoleH - vecMessage.size()) / 2 - vecMessage.size();
	SetWindowPos(pos);
	SetWindowSize(CSize((int)tMaxTextLen, (int)vecMessage.size()));

	for (std::wstring strLine : vecMessage)
		AddText(strLine);
}

void CAlarmUI::OnCreate(void)
{
	__super::OnCreate();
}

void CAlarmUI::OnUpdate(DWORD dwCurrentTick, DWORD dwElapsedTick)
{
	__super::OnUpdate(dwCurrentTick, dwElapsedTick);
}

void CAlarmUI::OnDrawUI(CDisplayBuffer& vecBuffer, CRect rtDrawArea)
{
	if (m_dwTimeOutTick < GetTickCount())
		return;
	__super::OnDrawUI(vecBuffer, rtDrawArea);
}
