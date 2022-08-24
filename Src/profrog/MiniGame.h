#pragma once

class CMiniGame : public CDlgSuper
{
	CTextUI m_TextUI;

public:
	CMiniGame(void);
	~CMiniGame(void);

	void OnCreate(void);
	void OnClose(void);
	void OnInput(std::list<ST_KEYSTATE>& listKeyState);
	void OnUpdate(DWORD dwCurrentTick, DWORD dwElapsedTick);
};

