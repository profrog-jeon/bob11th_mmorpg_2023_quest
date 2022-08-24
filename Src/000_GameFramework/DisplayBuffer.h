#pragma once

#include "Struct.h"
#include "HelperClass.h"

enum E_ALIGN_TYPE
{
	ALIGN_TYPE_LEFT,
	ALIGN_TYPE_RIGHT,
	ALIGN_TYPE_CENTER,
};

class CDisplayBuffer : public std::vector<std::wstring>
{
public:
	CDisplayBuffer(void);
	virtual ~CDisplayBuffer(void);

	void Create(size_t w, size_t h);
	void Clear(void);
	void DrawRectangle(CRect rect);
	void DrawRectangle(ST_POINT pos, ST_SIZE size);
	void DrawRectangle(int nLeft, int nTop, int nRight, int nBottom);
	void DrawString(ST_POINT pos, std::string strText, size_t tLength = -1);
	void DrawString(int x, int y, std::string strText, size_t tLength = -1);
	void DrawString(ST_POINT pos, std::wstring strText, size_t tLength = -1);
	void DrawString(int x, int y, std::wstring strText, size_t tLength = -1);
	void DrawAlignedString(ST_POINT pos, std::string strText, size_t tLength, E_ALIGN_TYPE nAlign);
	void DrawAlignedString(ST_POINT pos, std::wstring strText, size_t tLength, E_ALIGN_TYPE nAlign);
	void DrawStringOnCenter(ST_POINT pos, std::string strText);
	void DrawStringOnCenter(ST_POINT pos, std::wstring strText);
	void BitBlt(short x, short y, const CDisplayBuffer& buffer);
	void BitBlt(ST_POINT pos, const CDisplayBuffer& buffer);
};

