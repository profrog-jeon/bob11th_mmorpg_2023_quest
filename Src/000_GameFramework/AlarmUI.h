#pragma once

#include "UISuper.h"
#include "ScrollTextUI.h"

class CAlarmUI : public CScrollTextUI
{
	DWORD m_dwTimeOutTick;

public:
	CAlarmUI(void);
	~CAlarmUI(void);

	void Clear(void);
	void Alarm(std::tstring strMsg, DWORD dwDuring = 1000);

private:
	void OnCreate(void);
	void OnUpdate(DWORD dwCurrentTick, DWORD dwElapsedTick);
	void OnDrawUI(CDisplayBuffer& vecBuffer, CRect rtDrawArea);
};

