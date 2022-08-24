#pragma once
#include "CharSetSuper.h"

class CAsciiCharSet : public CCharSetSuper
{
	void Update(int nVirtualKey, ST_STRING_CONTEXT& context, bool bShiftPressed);
};