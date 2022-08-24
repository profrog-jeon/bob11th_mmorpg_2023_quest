#pragma once

#include <vector>
#include <string>
#include "Struct.h"
#include "DisplayBuffer.h"
#include "Console.h"

class CConsoleOutput : private CConsole
{
    CDisplayBuffer m_BackBuffer;
    int m_nViewWidth;
    int m_nViewHeight;

public:
    CConsoleOutput(void);

    bool InitConsole(std::tstring strTitle, int w, int h);
    void InitBackBuffer(int w, int h);
    void SetViewPort(int w, int h);

    CDisplayBuffer& GetBackBuffer(void)    {    return m_BackBuffer;    }

    void Flip(const ST_VECTOR& pos, CDisplayBuffer& vecDisplayBuffer);
    void Render(const CDisplayBuffer& vecDisplayBuffer);
};
