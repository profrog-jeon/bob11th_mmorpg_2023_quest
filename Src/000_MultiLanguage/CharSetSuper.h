#pragma once
#include "Struct.h"

class CCharSetSuper
{
public:
	virtual void Update(int nVirtualKey, ST_STRING_CONTEXT& context, bool bShiftPressed);
	virtual void Flush(void);
};
