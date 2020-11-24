#include "stdafx.h"
#include "Player.h"

#include "Obj.h"
#include "KeyMgr.h"
#include "LineMgr.h"
#include "Texture_Manager.h"
#include "Graphic_Device.h"

CPlayer::CPlayer()
	:m_bJump(false), m_fJumpPower(0.f), m_fJumpTime(0.f), m_fJumpY(0.f)
	,m_dwFrameTime(0),m_iFrame(0)
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

void CPlayer::Render_GameObject(/*HDC hDC*/)
{
	Update_Rect();
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);


	if (m_dwFrameTime + 100 < GetTickCount())
	{
		++m_iFrame;
		if (m_iFrame >= 4)
			m_iFrame = 0;

		m_dwFrameTime = GetTickCount();
	}

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"Player_Run", m_iFrame);

	if (nullptr == pTexInfo)
	{
		return;
	}
	UINT iCenterX = pTexInfo->tImageInfo.Width >> 1;
	UINT iCenterY = pTexInfo->tImageInfo.Height >> 1;
	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 2.f, 2.f, 0.f);
	//D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	//D3DXMatrixTranslation(&matTrans, 60.f * (i % 5 + 1), 60.f * (i / 5 + 1), 0.f);
	matWorld = matScale/* * matRotZ * matTrans*/;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	//RECT rc = { 0, 0, 100, 100 }; 
	//CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, &rc, &D3DXVECTOR3(float(iCenterX), float(iCenterY), 0.f), &D3DXVECTOR3(400.f, 300.f, 0.f), D3DCOLOR_ARGB(255, 255, 255, 255));
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr/*&rc*/, &D3DXVECTOR3(float(iCenterX), float(iCenterY), 0.f), nullptr/*&D3DXVECTOR3(400.f, 300.f, 0.f)*/, D3DCOLOR_ARGB(255, 255, 255, 255));


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