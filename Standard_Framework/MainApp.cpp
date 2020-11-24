#include "stdafx.h"
#include "MainApp.h"
#include "Player.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"

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
	HDC backbuffer = CreateCompatibleDC(m_hDC);
	HBITMAP hOldBmp = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	hOldBmp = HBITMAP(SelectObject(backbuffer, hOldBmp));

	Rectangle(backbuffer, 0, 0, WINCX, WINCY);
	//m_pPlayer->Render_GameObject(backbuffer);
	CObjMgr::Get_Instance()->Render(backbuffer);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, backbuffer, 0, 0, SRCCOPY);

	CLineMgr::Get_Instance()->Render(m_hDC);

	DeleteObject(SelectObject(backbuffer, hOldBmp));
	DeleteDC(backbuffer);
}

void CMainApp::Release_MainApp()
{
	CObjMgr::Get_Instance()->Release();

	ReleaseDC(g_hWND, m_hDC);
}
