#pragma once

#include <map>
#include <string>
#include <vector>
#include <Windows.h>

namespace std
{
#ifdef UNICODE
    typedef std::wstring	tstring;
    typedef std::string	    ntstring;
#else
    typedef std::string	    tstring;
    typedef std::wstring	ntstring;
#endif
}

struct ST_POINT
{
    short x;
    short y;

    bool operator==(const ST_POINT& other);
    bool operator!=(const ST_POINT& other);
};

struct ST_SIZE
{
    short cx;
    short cy;

    bool operator==(const ST_SIZE& other);
    bool operator!=(const ST_SIZE& other);
};

struct ST_RECT
{
    short l;
    short t;
    short r;
    short b;

    bool operator==(const ST_RECT& other);
};

struct ST_POINT3
{
    union
    {
        unsigned long long int qwPos;
        struct {
            short x;
            short y;
            short z;
            short reserved;
        };
    };

    ST_POINT3(void)
        : qwPos(0)
    {}
};

struct ST_VECTOR
{
    double x;
    double y;

    ST_VECTOR(void)
        : x(0), y(0)
    {}

    ST_VECTOR(double inX, double inY)
        : x(inX), y(inY)
    {}

    ST_POINT MakePoint(void);
    ST_SIZE MakeSize(void);
    double GetScalar(void);
    void Interpolate(const ST_VECTOR& target, DWORD dwElapsedTick, double dFactor);

    ST_VECTOR operator+(const ST_VECTOR& other) const;
    ST_VECTOR operator-(const ST_VECTOR& other) const;
    ST_VECTOR operator*(double scalar) const;
    ST_VECTOR operator/(double scalar) const;
    ST_VECTOR& operator+=(const ST_VECTOR& other);
    ST_VECTOR& operator-=(const ST_VECTOR& other);

    bool operator==(const ST_VECTOR& other);
    bool operator!=(const ST_VECTOR& other);
};

struct ST_KEYSTATE
{
    int nVirtKey;
    short nID;
    bool bPressed;
    bool bShiftPressed;     // 7바이트를 8바이트로 유격을 채워주는 역할
};

enum E_GAME_OBJECT_DIR
{
    GAME_OBJECT_DIR_LEFT = 1,
    GAME_OBJECT_DIR_RIGHT,
    GAME_OBJECT_DIR_UP,
    GAME_OBJECT_DIR_DOWN,
};
