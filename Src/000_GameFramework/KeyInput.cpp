#include "pch.h"
#include "KeyInput.h"

CKeyInput::CKeyInput(void)
	: m_dwFirstRepeatTick(400)
	, m_dwRepeatTick(100)
{
}

void CKeyInput::Clear(void)
{
	m_mapRegisteredKey.clear();
}

void CKeyInput::Register(int nVirtKey, int nID)
{
	m_mapRegisteredKey.insert(std::make_pair(nVirtKey, nID));
	if( 0 == m_mapKeyPressTime[nVirtKey])
		m_mapKeyPressTime[nVirtKey] = 0xFFFFFFFF;
}

void CKeyInput::Query(std::list<ST_KEYSTATE>& outState)
{
#ifndef _DEBUG
	HWND hConsole = ::GetConsoleWindow();
	HWND hFocus = ::GetForegroundWindow();
	if (hConsole != hFocus)
		return;
#endif
	m_bCapsLockEnabled = GetKeyState(VK_CAPITAL) & 0x01;
	m_bShiftPressed = (GetKeyState(VK_LSHIFT) & 0x8000) || (GetKeyState(VK_RSHIFT) & 0x8000);

	std::list<ST_KEYSTATE> tempState;
	for (auto iter : m_mapRegisteredKey)
	{
		short nPreState = m_mapLastKeyState[iter.first];
		short nCurState = GetKeyState(iter.first);
		m_mapLastKeyState[iter.first] = nCurState;

		short nDiff = nCurState ^ nPreState;
		if (0 == (nDiff & 0x8000))		// 키가 눌리지 않았다면
			continue;

		ST_KEYSTATE KeyState;
		KeyState.nVirtKey = iter.first;
		KeyState.nID = iter.second;
		KeyState.bPressed = (nCurState & 0x8000)? true : false;
		KeyState.bShiftPressed = m_bShiftPressed;
		tempState.push_back(KeyState);
	}

	GenerateRepeatKey(tempState, outState);
}

void CKeyInput::GenerateRepeatKey(std::list<ST_KEYSTATE>& inState, std::list<ST_KEYSTATE>& outRepeatState)
{
	const DWORD dwCurrentTick = GetTickCount();
	for (ST_KEYSTATE key : inState)
	{
		if (key.bPressed)
			m_mapKeyPressTime[key.nVirtKey] = dwCurrentTick + m_dwFirstRepeatTick;
		else
			m_mapKeyPressTime[key.nVirtKey] = 0xFFFFFFFF;
	}

	outRepeatState = inState;
	for (auto iter : m_mapRegisteredKey)
	{
		if (VK_HANGUL == iter.first)
			continue;

		bool bIsKeyPressed = m_mapLastKeyState[iter.first] & 0x8000;
		if (!bIsKeyPressed)
			continue;
		if (dwCurrentTick < m_mapKeyPressTime[iter.first])
			continue;

		m_mapKeyPressTime[iter.first] = dwCurrentTick + m_dwRepeatTick;

		ST_KEYSTATE stRepeatKey;
		stRepeatKey.nVirtKey = iter.first;
		stRepeatKey.nID = iter.second;
		stRepeatKey.bPressed = true;
		stRepeatKey.bShiftPressed = m_bShiftPressed;
		outRepeatState.push_back(stRepeatKey);
	}
}

bool CKeyInput::IsEnabledCapsLock(void)
{
	return m_bCapsLockEnabled xor m_bShiftPressed;
}

bool CKeyInput::IsCpasLockEnabled(void)
{
	return m_bCapsLockEnabled;
}

void CKeyInput::SetRepeatTick(DWORD dwRepeatTick)
{
	m_dwRepeatTick = dwRepeatTick;
}