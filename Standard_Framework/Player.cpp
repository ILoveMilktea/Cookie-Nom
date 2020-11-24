#include "stdafx.h"
#include "Player.h"

#include "Obj.h"
#include "KeyMgr.h"
#include "LineMgr.h"

CPlayer::CPlayer()
	:m_bJump(false), m_fJumpPower(0.f), m_fJumpTime(0.f), m_fJumpY(0.f)
{
}


HRESULT CPlayer::Ready_GameObject()
{
	m_tInfo.vPos	= D3DXVECTOR3(float(WINCX >> 1), float(WINCY >> 1), 0.f);
	m_tInfo.vSize	= D3DXVECTOR3(100.f, 100.f, 0.f);
	m_tInfo.vDir	= D3DXVECTOR3(0.f, 1.f, 0.f);

	m_vP[0] = { -m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[1] = { m_tInfo.vSize.x * 0.5f, -m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[2] = { m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };
	m_vP[3] = { -m_tInfo.vSize.x * 0.5f, m_tInfo.vSize.y * 0.5f, 0.f };

	m_fSpeed = 5.f;
	m_fAngle = 0.f;

	m_fJumpPower = 50.f;
	return S_OK;
}

int CPlayer::Update_GameObject()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		m_tInfo.vPos.x -= m_fSpeed;
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		m_tInfo.vPos.x += m_fSpeed;
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		if (!m_bJump)
		{
			m_bJump = true;
			m_fJumpY = m_tInfo.vPos.y;
		}
	}

	//D3DXMATRIX matScale, matRotZ, matTrans;
	//D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	//D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	//D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	//m_tInfo.matWorld = matScale * matRotZ * matTrans;

	//for (int i = 0; i < 4; ++i)
	//	D3DXVec3TransformCoord(&m_vQ[i], &m_vP[i], &m_tInfo.matWorld);
	
	Jumping();


	return OBJ_NOEVENT;
}

/*
D3DXVec3TransformNormal()		-> w = 0 이라서 위치값이 배제됩니다.(방향벡터가 나옴)
D3DXVec3TransformCoord()		-> w = 1, 위치벡터를 얻어낼 수 있어요
*/


void CPlayer::Late_Update_GameObject()
{
}

void CPlayer::Render_GameObject(HDC hDC)
{
	Update_Rect();
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release_GameObject()
{
	Free();
}


CObj * CPlayer::Create()
{
	CObj* pInstance = new CPlayer;

	if (FAILED(pInstance->Ready_GameObject()))
	{
		MessageBox(nullptr, L"Create Failed - Player.cpp", L"SystemError", MB_OK);
		delete pInstance;
		pInstance = nullptr;
		return pInstance;
	}

	return pInstance;
}

void CPlayer::Free()
{
	Release_GameObject();

	delete this;
}

void CPlayer::Jumping()
{
	float fY = 0.f;
	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.vPos.x, &fY);

	if (m_bJump)
	{
		m_tInfo.vPos.y = m_fJumpY - (m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f);
		m_fJumpTime += 0.2f;

		if (bLineCol && fY < m_tInfo.vPos.y)
		{
			m_bJump = false;
			m_tInfo.vPos.y = fY;
			m_fJumpTime = 0.f;
		}
	}
	else if (bLineCol)
		m_tInfo.vPos.y = fY;
}