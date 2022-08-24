#include "pch.h"
#include "Console.h"

CConsole::CConsole(void)
	: m_hConsole { nullptr, }
	, m_nIndex(0)
{

}

CConsole::~CConsole(void)
{

}

int CConsole::Create(int w, int h)
{
	m_nWidth = w;
	m_nHeight = h;
	try
	{
		for (int i = 0; i < 2; i++)
		{
			HANDLE& hConsole = m_hConsole[i];

			hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
			if (nullptr == hConsole)
				throw std::runtime_error("CreateConsoleScreenBuffer error");

			CONSOLE_SCREEN_BUFFER_INFOEX stBufferInfo;
			stBufferInfo.cbSize = sizeof(stBufferInfo);
			if (!GetConsoleScreenBufferInfoEx(hConsole, &stBufferInfo))
				throw std::runtime_error("Failed to GetConsoleScreenBufferInfoEx");

			stBufferInfo.dwSize.X = w + 1;
			stBufferInfo.dwSize.Y = h + 1;
			stBufferInfo.dwMaximumWindowSize.X = w + 1;
			stBufferInfo.dwMaximumWindowSize.Y = h + 1;
			if (!SetConsoleScreenBufferInfoEx(hConsole, &stBufferInfo))
				throw std::runtime_error("Failed to SetConsoleScreenBufferInfoEx");

			SMALL_RECT stDisplayArea = { 0, 0, w, h };
			if (!SetConsoleWindowInfo(hConsole, TRUE, &stDisplayArea))
				throw std::runtime_error("Failed to SetConsoleWindowInfo");

			// 콘솔 커서 없애기
			CONSOLE_CURSOR_INFO cursorInfo = { 0, };
			cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
			cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
			SetConsoleCursorInfo(hConsole, &cursorInfo);
		}

		m_nIndex = 0;
		SetConsoleActiveScreenBuffer(m_hConsole[m_nIndex]);
	}
	catch (const std::exception& e)
	{
		printf("%s\n", e.what());
		Destroy();
		return -1;
	}
	return 0;
}

void CConsole::Destroy(void)
{
	if(m_hConsole[0])
		CloseHandle(m_hConsole[0]);
	if (m_hConsole[1])
		CloseHandle(m_hConsole[1]);
}

void CConsole::Clear(void)
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(m_hConsole[m_nIndex], ' ', m_nWidth * m_nHeight, Coor, &dw);
}

void CConsole::Print(int x, int y, std::string strContext)
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(m_hConsole[m_nIndex], CursorPosition);
	WriteFile(m_hConsole[m_nIndex], strContext.c_str(), strContext.length(), &dw, NULL);
}

void CConsole::Render(void)
{
	SetConsoleActiveScreenBuffer(m_hConsole[m_nIndex]);
	m_nIndex = (m_nIndex + 1) & 0x01;
}