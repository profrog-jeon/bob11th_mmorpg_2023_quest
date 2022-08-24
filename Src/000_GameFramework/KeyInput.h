#pragma once

#include <map>
#include <list>
#include "Struct.h"

enum E_GAMEKEY
{
    GAMEKEY_LEFT = GAME_OBJECT_DIR_LEFT,
    GAMEKEY_RIGHT,
    GAMEKEY_UP,
    GAMEKEY_DOWN,
    GAMEKEY_SELECT,
    GAMEKEY_MENU,
    GAMEKEY_CHAT,
    GAMEKEY_ESC,
};

class CKeyInput
{
    std::map<int, int> m_mapRegisteredKey;      // (virt, id)
    std::map<int, short> m_mapLastKeyState;
    std::map<int, DWORD> m_mapKeyPressTime;
    bool m_bCapsLockEnabled;
    bool m_bShiftPressed;
    DWORD m_dwFirstRepeatTick;
    DWORD m_dwRepeatTick;

public:
    CKeyInput(void);

    void Clear(void);
    void Register(int nVirtKey, int nID);
    void Query(std::list<ST_KEYSTATE>& outState);

    bool IsEnabledCapsLock(void);
    bool IsCpasLockEnabled(void); // юс╫ц

    void SetRepeatTick(DWORD dwRepeatTick = 200);

private:
    void GenerateRepeatKey(std::list<ST_KEYSTATE>& inState, std::list<ST_KEYSTATE>& outRepeatState);
};
