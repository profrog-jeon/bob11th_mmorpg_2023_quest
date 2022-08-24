#include "pch.h"
#include "CharSetSuper.h"

std::map<int, std::wstring> mStrSetLower
{
	{ 0x30, L"0" },
	{ 0x31, L"1" },
	{ 0x32, L"2" },
	{ 0x33, L"3" },
	{ 0x34, L"4" },
	{ 0x35, L"5" },
	{ 0x36, L"6" },
	{ 0x37, L"7" },
	{ 0x38, L"8" },
	{ 0x39, L"9" },
	{ VK_OEM_PLUS, L"=" },
	{ VK_OEM_COMMA, L"," },
	{ VK_OEM_MINUS, L"-" },
	{ VK_OEM_PERIOD, L"." },
	{ VK_OEM_1, L";" },
	{ VK_OEM_2, L"/" },
	{ VK_OEM_3, L"`" },
	{ VK_OEM_4, L"[" },
	{ VK_OEM_5, L"\\" },
	{ VK_OEM_6, L"]" },
	{ VK_OEM_7, L"\'" }
};

std::map<int, std::wstring> mStrSetUpper
{
	{ 0x30, L")" },
	{ 0x31, L"!" },
	{ 0x32, L"@" },
	{ 0x33, L"#" },
	{ 0x34, L"$" },
	{ 0x35, L"%" },
	{ 0x36, L"^" },
	{ 0x37, L"&" },
	{ 0x38, L"*" },
	{ 0x39, L"(" },
	{ VK_OEM_PLUS, L"+" },
	{ VK_OEM_COMMA, L"<" },
	{ VK_OEM_MINUS, L"_" },
	{ VK_OEM_PERIOD, L">" },
	{ VK_OEM_1, L":" },
	{ VK_OEM_2, L"?" },
	{ VK_OEM_3, L"~" },
	{ VK_OEM_4, L"{" },
	{ VK_OEM_5, L"|" },
	{ VK_OEM_6, L"}" },
	{ VK_OEM_7, L"\"" }
};

void CCharSetSuper::Update(int nVirtualKey, ST_STRING_CONTEXT& context, bool bShiftPressed)
{
	if (nVirtualKey == VK_DELETE)
	{
		std::wstring strPreContext = context.strContext.substr(0, context.nCursorPos);
		std::wstring strPosContext = context.strContext.substr(context.nCursorPos);

		strPosContext.erase(0, 1);

		context.strContext = strPreContext + strPosContext;
	}

	if (nVirtualKey == VK_SPACE)
	{
		std::wstring a(L" ");
		context.strContext.insert(context.nCursorPos, a);
		context.nCursorPos++;
		return;
	}

	if (nVirtualKey == VK_LEFT)
	{
		if (context.nCursorPos == 0) return;
		context.nCursorPos--;
		return;
	}

	if (nVirtualKey == VK_RIGHT)
	{
		if (context.nCursorPos == context.strContext.size()) return;
		context.nCursorPos++;
		return;
	}

	if ( (0x30 <= nVirtualKey && nVirtualKey <= 0x39) ||
		(VK_OEM_1 <= nVirtualKey && nVirtualKey <= VK_OEM_7))
	{
		std::wstring strPreContext = context.strContext.substr(0, context.nCursorPos);
		std::wstring strPosContext = context.strContext.substr(context.nCursorPos);

		std::wstring strNewContext;
		if (bShiftPressed)
			strNewContext = mStrSetUpper[nVirtualKey];
		else
			strNewContext = mStrSetLower[nVirtualKey];

		context.strContext = strPreContext + strNewContext + strPosContext;
		context.nCursorPos++;
	}
}

void CCharSetSuper::Flush(void)
{
}
