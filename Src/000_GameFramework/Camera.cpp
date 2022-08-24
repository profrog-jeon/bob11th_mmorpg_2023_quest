#include "pch.h"
#include "Camera.h"

CCamera::CCamera(void)
{
    m_OffsetStack.push(ST_POINT{ 0, });
}

CCamera::~CCamera(void)
{
}

void CCamera::CenterOffset(ST_POINT ptCenterOffset)
{
    m_OffsetStack.push(ptCenterOffset);
}

void CCamera::PushCenterOffset(ST_POINT ptCenterOffset)
{
    m_OffsetStack.push(ptCenterOffset);
}

void CCamera::PopCenterOffset(void)
{
    if (1 < m_OffsetStack.size())
        m_OffsetStack.pop();
}

void CCamera::SetViewPos(int x, int y, bool bForcely)
{
    m_TargetPos.x = x - m_OffsetStack.top().x;
    m_TargetPos.y = y - m_OffsetStack.top().y;
    if (bForcely)
        m_Pos = m_TargetPos;
}

void CCamera::SetViewPos(ST_POINT pos, bool bForcely)
{
    m_TargetPos.x = pos.x - m_OffsetStack.top().x;
    m_TargetPos.y = pos.y - m_OffsetStack.top().y;
    if (bForcely)
        m_Pos = m_TargetPos;
}

void CCamera::SetViewPos(ST_POINT3 pos, bool bForcely)
{
    m_TargetPos.x = pos.x - m_OffsetStack.top().x;
    m_TargetPos.y = pos.y - m_OffsetStack.top().y;
    if (bForcely)
        m_Pos = m_TargetPos;
}

void CCamera::SetViewPos(const ST_VECTOR& pos, bool bForcely)
{
    m_TargetPos = pos;
    m_TargetPos.x -= m_OffsetStack.top().x;
    m_TargetPos.y -= m_OffsetStack.top().y;
    if (bForcely)
        m_Pos = m_TargetPos;
}

void CCamera::Update(double dElapsedTime)
{
    m_Pos += (m_TargetPos - m_Pos) * dElapsedTime * 0.5;
}

ST_VECTOR CCamera::GetViewPos(void)
{
    return m_Pos;
}
