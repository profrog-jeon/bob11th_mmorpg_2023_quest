#pragma once

#include "Struct.h"
#include <stack>

class CCamera
{
	ST_VECTOR m_TargetPos;
	ST_VECTOR m_Pos;

	std::stack<ST_POINT> m_OffsetStack;

public:
	CCamera(void);
	~CCamera(void);

	void CenterOffset(ST_POINT ptCenterOffset);
	void PushCenterOffset(ST_POINT ptCenterOffset);
	void PopCenterOffset(void);
	void SetViewPos(int x, int y, bool bForcely = false);
	void SetViewPos(ST_POINT pos, bool bForcely = false);
	void SetViewPos(ST_POINT3 pos, bool bForcely = false);
	void SetViewPos(const ST_VECTOR& pos, bool bForcely = false);
	void Update(double dElapsedTime);
	ST_VECTOR GetViewPos(void);
};
