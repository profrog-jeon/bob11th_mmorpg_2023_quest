#pragma once

#include <string>
#include <Windows.h>
#include <exception>
#include <errors.h>

class CConsole
{
	HANDLE m_hConsole[2];
	int m_nIndex;

	int m_nWidth;
	int m_nHeight;

public:
	CConsole(void);
	~CConsole(void);

	int Create(int w, int h);
	void Destroy(void);

	void Clear(void);
	void Print(int x, int y, std::string strContext);
	void Render(void);
};

