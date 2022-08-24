#pragma once

#include "Struct.h"

class CPoint : public ST_POINT
{
public:
	CPoint(void);
	CPoint(int inX, int inY);
	CPoint(ST_POINT pos);

	ST_VECTOR MakeVector(void) const;
	CPoint Move(int nOffsetX, int nOffsetY) const;

	CPoint operator+(const CPoint other);
	CPoint operator-(const CPoint other);
	CPoint operator*(int value);

	CPoint& operator+=(const CPoint other);
	CPoint& operator-=(const CPoint other);

	operator ST_POINT() const;
};

class CSize : public ST_SIZE
{
public:
	CSize(void);
	CSize(int inCX, int inCY);
	CSize(ST_SIZE size);
	CSize Inflate(int x, int y);
	CSize Deflate(int x, int y);
	ST_VECTOR MakeVector(void);

	operator ST_SIZE() const;
};

class CRect : public ST_RECT
{
public:
	CRect(void);
	CRect(int inLeft, int inTop, int inRight, int inBottom);
	CRect(const ST_POINT& pt, const ST_SIZE& sz);

	operator ST_RECT() const;

	CSize GetSize(void);
	CPoint GetPos(void);

	CRect Inflate(int left, int top, int right, int bottom);
	CRect Deflate(int left, int top, int right, int bottom);
};
