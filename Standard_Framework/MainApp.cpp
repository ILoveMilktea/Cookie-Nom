#include "stdafx.h"
#include "MainApp.h"
#include "Player.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"

#include "Graphic_Device.h"
#include "Texture_Manager.h"

#include "Obstacle.h"

CMainApp::CMainApp()
	:m_dwRespawn(0)
{
}

CMainApp::~CMainApp()
{
	Release_MainApp();
}

HRESULT CMainApp::Ready_MainApp()
{
	m_hDC = GetDC(g_hWND);
	// E_FAIL : 실패시 반환타입, 앞에 E는 음수를 뜻함
	CLineMgr::Get_Instance()->Initialize();

	CObj* pPlayer = CPlayer::Create();
	CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER, pPlayer);
	
	CTexture_Manager::Get_Instance()->Initialize_Manager();	// 텍스쳐 추가

	//obstacle test
	CObj* pObstacle = new CObstacle();
	static_cast<CObstacle*>(pObstacle)->Set_TextureInfo(L"Obstacle", L"jp_spike", 1, 1, CObstacle::JUMP);
	static_cast<CObstacle*>(pObstacle)->Set_PosX(200.f);
	static_cast<CObstacle*>(pObstacle)->Ready_GameObject();

	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObstacle);
	
	pObstacle = new CObstacle();
	static_cast<CObstacle*>(pObstacle)->Set_TextureInfo(L"Obstacle", L"dbjp_greenflask", 0, 3, CObstacle::DOUBLEJUMP);
	static_cast<CObstacle*>(pObstacle)->Set_PosX(400.f);
	static_cast<CObstacle*>(pObstacle)->Ready_GameObject();

	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObstacle);


	pObstacle = new CObstacle();
	static_cast<CObstacle*>(pObstacle)->Set_TextureInfo(L"Obstacle", L"sd_fork", 0, 1, CObstacle::SLIDE);
	static_cast<CObstacle*>(pObstacle)->Set_PosX(600.f);
	static_cast<CObstacle*>(pObstacle)->Ready_GameObject();

	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObstacle);
	
	return S_OK; // S_OK : Success OK, S붙으면 양수임, 성공시 반환하는 반환타입 / NOERROR;
}

void CMainApp::Update_MainApp()
{
	CObjMgr::Get_Instance()->Update();

}


void CMainApp::Late_Update_MainApp()
{
	CObjMgr::Get_Instance()->Late_Update();
	CKeyMgr::Get_Instance()->Key_Update();
}

void CMainApp::Render_MainApp()
{

	CGraphic_Device::Get_Instance()->Render_Begin();

	//TCHAR szBuf[MAX_PATH] = L"";
	//swprintf_s(szBuf, L"%d", iIndex);
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"background");
	UINT iCenterX = pTexInfo->tImageInfo.Width >> 1;
	UINT iCenterY = pTexInfo->tImageInfo.Height >> 1;

	RECT rc = { 0, 0, 860, 320 }; 

	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, 2.0f, 2.0f, 0.f);
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matScale);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, &rc, &D3DXVECTOR3(float(iCenterX), float(iCenterY), 0.f), &D3DXVECTOR3(iCenterX, iCenterY, 0.f), D3DCOLOR_ARGB(255, 255, 255, 255));
	
	CObjMgr::Get_Instance()->Render();

	CGraphic_Device::Get_Instance()->Render_End();

}

void CMainApp::Release_MainApp()
{
	CObjMgr::Get_Instance()->Release();

	ReleaseDC(g_hWND, m_hDC);
}
