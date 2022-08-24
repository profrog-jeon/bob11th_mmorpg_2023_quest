#pragma once
#include <list>
#include "CAsciiCharSet.h"
#include "CHangulCharset.h"

enum E_CHARSET_TYPE
{
	CHARSET_ASCII,
	CHARSET_HANGUL
};

struct ST_KEYSTATE;
class CStringBuilder
{
	CHangulCharset CHangul;
	CAsciiCharSet CAscii;

	std::map<E_CHARSET_TYPE, CCharSetSuper*> m_mapCharset
	{
		{CHARSET_ASCII, &CHangul},
		{CHARSET_HANGUL, &CAscii}
	};

	ST_STRING_CONTEXT m_Context;
	CCharSetSuper* m_pCurCharset;

	bool bHangulFlag = false;

	std::wstring m_strContext;
	std::wstring m_strContextWithCursor;

public:
	CStringBuilder(void);
	void Clear();
	void BuildContext(std::list<ST_KEYSTATE> listKeys, bool bIsCpasLockEnabled);
	std::wstring GetContext(void);
	std::wstring GetContextWithCursor(void);
};
