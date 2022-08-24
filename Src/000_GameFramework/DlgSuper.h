#pragma once

#include "Setting.h"
#include "UISuper.h"
#include "KeyInput.h"
#include "Camera.h"
#include "ConsoleOutput.h"

class CDlgSuper : public CUISuper
{
protected:
	CDlgSuper* m_pParent;
	std::list<CUISuper*> m_listUI;

	bool m_bIsCreated;
	bool m_bIsClosed;
	int m_nExitCode;

	CDlgSuper(CDlgSuper* pParent = nullptr);
	virtual ~CDlgSuper(void);

	virtual void OnCreate(void);
	virtual void OnClose(void);
	virtual void OnInput(std::list<ST_KEYSTATE>& listKeyState);
	virtual void OnUpdate(DWORD dwCurrentTick, DWORD dwElapsedTick);
	virtual void OnDrawUI(CDisplayBuffer& vecBuffer, CRect rtDrawArea);

public:
	virtual int DoModal(void);
	virtual void Close(int nExitCode);

	virtual void SetParent(CDlgSuper* pParent);
	virtual void Update(DWORD dwCurrentTick, DWORD dwElapsedTick);
	virtual void DrawUI(CDisplayBuffer& vecBuffer);

protected:
	friend class CUISuper;
	virtual void AddUI(CUISuper* pChild);
};

