#include "pch.h"
#include "HelperClass.h"

CPoint::CPoint(void)
	: ST_POINT{ 0, }
{
}

CPoint::CPoint(int inX, int inY)
	: ST_POINT{ (short)inX, (short)inY }
{
}

CPoint::CPoint(ST_POINT pos)
	: ST_POINT{ pos.x, pos.y }
{
}

ST_VECTOR CPoint::MakeVector(void) const
{
	return ST_VECTOR(x, y);
}

CPoint CPoint::Move(int nOffsetX, int nOffsetY) const
{
	return CPoint(x + nOffsetX, y + nOffsetY);
}

CPoint CPoint::operator+(const CPoint other)
{
	return CPoint(x + other.x, y + other.y);
}

CPoint CPoint::operator-(const CPoint other)
{
	return CPoint(x - other.x, y - other.y);

}

CPoint CPoint::operator*(int value)
{
	return CPoint(x * value, y * value);

}

CPoint& CPoint::operator+=(const CPoint other)
{
	x += other.x;
	y += other.y;
	return *this;
}

CPoint& CPoint::operator-=(const CPoint other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

CPoint::operator ST_POINT() const
{
	return *(ST_POINT*)this;
}

CSize::CSize(void)
	: ST_SIZE{ 0, }
{
}

CSize::CSize(int inCX, int inCY)
	: ST_SIZE{ (short)inCX, (short)inCY}
{
}

CSize::CSize(ST_SIZE size)
	: ST_SIZE{ size.cx, size.cy}
{
}

CSize CSize::Inflate(int x, int y)
{
	return CSize(cx + x, cy + y);
}

CSize CSize::Deflate(int x, int y)
{
	return CSize(cx - x, cy - y);
}

ST_VECTOR CSize::MakeVector(void)
{
	return ST_VECTOR(cx, cy);
}

CSize::operator ST_SIZE() const
{
	return *(ST_SIZE*)this;
}

CRect::CRect(void)
	: ST_RECT()
{
}

CRect::CRect(int inLeft, int inTop, int inRight, int inBottom)
	: ST_RECT{ (short)inLeft, (short)inTop, (short)inRight, (short)inBottom }
{
}

CRect::CRect(const ST_POINT& pt, const ST_SIZE& sz)
	: ST_RECT{ (pt.x), (pt.y), (pt.x + sz.cx - 1), (pt.y + sz.cy - 1) }
{}

CRect::operator ST_RECT() const
{
	return *(ST_RECT*)this;
}

CSize CRect::GetSize(void)
{
	return CSize(r - l + 1, b - t + 1);
}

CPoint CRect::GetPos(void)
{
	return CPoint(l, t);
}

CRect CRect::Inflate(int left, int top, int right, int bottom)
{
	return CRect(l - left, t - top, r + right, b + bottom);
}

CRect CRect::Deflate(int left, int top, int right, int bottom)
{
	return CRect(l + left, t + top, r - right, b - bottom);
}
