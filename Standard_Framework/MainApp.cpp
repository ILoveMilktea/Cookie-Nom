#include "stdafx.h"
#include "MainApp.h"
#include "Player.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"

#include "Graphic_Device.h"
#include "Texture_Manager.h"

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
	// E_FAIL : ���н� ��ȯŸ��, �տ� E�� ������ ����
	CLineMgr::Get_Instance()->Initialize();

	CObj* pPlayer = CPlayer::Create();
	CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER, pPlayer);


	CTexture_Manager::Get_Instance()->Initialize_Manager();	// �ؽ��� �߰�
	
	return S_OK; // S_OK : Success OK, S������ �����, ������ ��ȯ�ϴ� ��ȯŸ�� / NOERROR;
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

	RECT rc = { 0, 0, WINCX, WINCY }; 
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, &rc, &D3DXVECTOR3(float(iCenterX), float(iCenterY), 0.f), &D3DXVECTOR3(iCenterX, iCenterY, 0.f), D3DCOLOR_ARGB(255, 255, 255, 255));

	CGraphic_Device::Get_Instance()->Render_End();

	
	// Multi texture �׸��°� MFC View -> Ondraw�Լ��� �ִ°� ����

	// ====== �Ʒ��� �÷��̾� �׸��� �ڵ� ====== 
	// DC���� ������ �����Ѱ� ���� ����Ἥ ���� DC �����


	//HDC backbuffer = CreateCompatibleDC(m_hDC);
	//HBITMAP hOldBmp = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	//hOldBmp = HBITMAP(SelectObject(backbuffer, hOldBmp));

	////Rectangle(backbuffer, 0, 0, WINCX, WINCY);


	////m_pPlayer->Render_GameObject(backbuffer);
	//CObjMgr::Get_Instance()->Render(backbuffer);

	//BitBlt(m_hDC, 0, 0, WINCX, WINCY, backbuffer, 0, 0, SRCCOPY);

	//CLineMgr::Get_Instance()->Render(m_hDC);

	//DeleteObject(SelectObject(backbuffer, hOldBmp));
	//DeleteDC(backbuffer);
}

void CMainApp::Release_MainApp()
{
	CObjMgr::Get_Instance()->Release();

	ReleaseDC(g_hWND, m_hDC);
}
