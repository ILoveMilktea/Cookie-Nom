#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f), m_bDead(false), m_fAngle(0.f), m_pTarget(nullptr), m_fAttackPoint(1.f), m_fBoomPoint(2.f), m_iLife(1), m_iMaxHP(100), m_iHP(m_iMaxHP), m_bStart(true)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
}


CObj::~CObj()
{
}

void CObj::Set_Dir(D3DXVECTOR3 _vDir)
{
	m_tInfo.vDir = _vDir;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	float fDia = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	float fRad = acosf(m_tInfo.vDir.x / fDia);
	m_fAngle = fRad * 180.f / PI;
}

void CObj::Update_Rect()
{
	m_tRect.left = (LONG)(m_tInfo.vPos.x - (m_tInfo.vSize.x * 0.5f));
	m_tRect.top = (LONG)(m_tInfo.vPos.y - (m_tInfo.vSize.y * 0.5f));
	m_tRect.right = (LONG)(m_tInfo.vPos.x + (m_tInfo.vSize.x * 0.5f));
	m_tRect.bottom = (LONG)(m_tInfo.vPos.y + (m_tInfo.vSize.y * 0.5f));
}
