#include "pch.h"
#include "CAsciiCharSet.h"

void CAsciiCharSet::Update(int nVirtualKey, ST_STRING_CONTEXT& context, bool bShiftPressed)
{
	__super::Update(nVirtualKey, context, bShiftPressed);

	if (nVirtualKey == VK_BACK)
	{
		std::wstring strPreContext = context.strContext.substr(0, context.nCursorPos);
		std::wstring strPosContext = context.strContext.substr(context.nCursorPos);

		if (context.nCursorPos != 0)
		{
			strPreContext.pop_back();
			context.nCursorPos--;
		}
		context.strContext = strPreContext + strPosContext;

		return;
	}

	if ('A' <= nVirtualKey && nVirtualKey <= 'Z')
	{
		if (!bShiftPressed)
			nVirtualKey += 0x20;

		std::wstring strPreContext = context.strContext.substr(0, context.nCursorPos);
		std::wstring strPosContext = context.strContext.substr(context.nCursorPos);

		wchar_t szNewContext[2] = { (char)nVirtualKey, 0 };

		context.strContext = strPreContext + szNewContext + strPosContext;
		context.nCursorPos++;
	}
}
