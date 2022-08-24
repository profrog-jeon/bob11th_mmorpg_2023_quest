#include "pch.h"
#include "ConsoleOutput.h"
#include "HelperFunc.h"
#include "Setting.h"

CConsoleOutput::CConsoleOutput(void)
    : CConsole()
    , m_BackBuffer()
    , m_nViewWidth(0)
    , m_nViewHeight(0)
{
}

bool CConsoleOutput::InitConsole(std::tstring strTitle, int w, int h)
{
    try
    {
        SetConsoleTitle(strTitle.c_str());
        __super::Create(w, h);
    }
    catch (const std::exception& e)
    {
        printf("%s\n", e.what());
        return false;
    }
    
    return true;
}

void CConsoleOutput::InitBackBuffer(int w, int h)
{
    m_BackBuffer.resize(h + 1);
    for (auto& strLine : m_BackBuffer)
        strLine.resize(w + 1, ' ');
}

void CConsoleOutput::SetViewPort(int w, int h)
{
    m_nViewWidth = w;
    m_nViewHeight = h;
}

void CConsoleOutput::Flip(const ST_VECTOR& pos, CDisplayBuffer& vecDisplayBuffer)
{
    vecDisplayBuffer.resize(m_nViewHeight);

    int nLeft = (int)pos.x - (m_nViewWidth) / 2;
    int nRight = (int)pos.x + (m_nViewWidth) / 2;
    int nTop = (int)pos.y - (m_nViewHeight) / 2;
    int nBottom = (int)pos.y + (m_nViewHeight) / 2;

    for (std::wstring& strLine : vecDisplayBuffer)
        strLine.resize(m_nViewWidth, TEXT(' '));

    const int nMaxHeight = std::min<int>(std::min<int>(m_nViewHeight + nTop, nBottom), (int)m_BackBuffer.size());
    for (int y = std::max<int>(nTop, 0); y < nMaxHeight; y++)
    {
        const int nScreenY = y - nTop;
        const int nMaxWidth = std::min<int>(std::min<int>(nRight, (int)m_BackBuffer[y].size()), nLeft + vecDisplayBuffer[nScreenY].size());
        for (int x = std::max<int>(nLeft, 0); x < nMaxWidth; x++)
        {
            const int nScreenX = x - nLeft;
            vecDisplayBuffer[nScreenY][nScreenX] = m_BackBuffer[y][x];
        }
    }

    m_BackBuffer.Clear();
}

struct ST_PROFILE
{
    DWORD dwStartTick;
    ST_PROFILE(void)
    {
        dwStartTick = GetTickCount();
    }
    ~ST_PROFILE(void)
    {
        DWORD dwElapsedTick = GetTickCount() - dwStartTick;
        char szBuffer[101] = { 0, };
        sprintf_s(szBuffer, 100, "ElapsedTick:%u\n", dwElapsedTick);
        OutputDebugStringA(szBuffer);
    }
};

void CConsoleOutput::Render(const CDisplayBuffer& vecDisplayBuffer)
{    
    for (size_t y = 0; y<vecDisplayBuffer.size(); y++)
    {
        const std::wstring& strLineW = vecDisplayBuffer[y];

        size_t tPos = 0;
        std::string strOutput;
        strOutput.resize(strLineW.length() * 2);
        std::string strLine = unicode::MBSFromWCS(strLineW);
        for(size_t i=0; i<strLine.size(); i++)
        {
            char w = strLine.at(i);
            if (w == 2 || w == 4 || w == 6)   // UI 외곽선만 연결함
            {
                strOutput[tPos++] = 6;
                strOutput[tPos++] = w;
            }
            else if (w == 1 || w == 3 || w == 5)   // UI 외곽선: 세로선
            {
                strOutput[tPos++] = ' ';
                strOutput[tPos++] = w;
            }
            else if (0 < w)
            {
                strOutput[tPos++] = w;
                strOutput[tPos++] = ' ';
            }
            else if (w < 0)
            {
                // 다국어 문자 처리
                strOutput[tPos++] = w;
                if (i + 1 < strLine.size())
                    strOutput[tPos++] = strLine.at(i + 1);
                else
                    strOutput[tPos++] = ' ';
                i++;
            }
        }
        strOutput.resize(tPos);
        __super::Print(0, y, strOutput);
    }
    
    {   // FPS 표기
        static std::list<DWORD> s_FrameTick;
        DWORD dwCurrentTick = GetTickCount();
        s_FrameTick.push_back(dwCurrentTick);
        while (s_FrameTick.front() + 1000 < dwCurrentTick)
            s_FrameTick.pop_front();

        char szBuffer[101];
        sprintf_s(szBuffer, 100, "%uFPS", (DWORD)s_FrameTick.size());
        __super::Print(0, 0, szBuffer);
    }
    __super::Render();
}

