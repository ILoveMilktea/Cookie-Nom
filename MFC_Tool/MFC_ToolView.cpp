
// MFC_ToolView.cpp : CMFC_ToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_Tool.h"
#endif

#include "MFC_ToolDoc.h"
#include "MFC_ToolView.h"
#include "Graphic_Device.h"
#include "Single_Texture.h"
#include "Texture_Manager.h"
#include "Terrain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_ToolView

HWND g_hWND;

IMPLEMENT_DYNCREATE(CMFC_ToolView, CView)

BEGIN_MESSAGE_MAP(CMFC_ToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMFC_ToolView 생성/소멸

CMFC_ToolView::CMFC_ToolView()
	:m_pTerrain(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFC_ToolView::~CMFC_ToolView()
{
	CGraphic_Device::Destroy_Instance();
	CTexture_Manager::Destroy_Instance();

	SAFE_DELETE(m_pTerrain);
}

BOOL CMFC_ToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFC_ToolView 그리기

void CMFC_ToolView::OnDraw(CDC* pDC)	// WM_PAINT 라는 메세지가 발생했을 때 동작하는 함수
{
	CMFC_ToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CGraphic_Device::Get_Instance()->Render_Begin();

	m_pTerrain->Render_Terrain();
	// 아래껀 수업시간에 했던 Cube그림, tile 한개 그리기
	{
		//for (int i = 0; i < 38; ++i)
		//{
		//	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", i);

		//	if (nullptr == pTexInfo)
		//	{
		//		return;
		//	}
		//	UINT iCenterX = pTexInfo->tImageInfo.Width >> 1;
		//	UINT iCenterY = pTexInfo->tImageInfo.Height >> 1;
		//	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
		//	D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.f);
		//	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
		//	D3DXMatrixTranslation(&matTrans, 60.f * (i % 5 + 1), 60.f * (i / 5 + 1), 0.f);
		//	matWorld = matScale * matRotZ * matTrans;

		//	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		//	//RECT rc = { 0, 0, 100, 100 }; 
		//	//CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, &rc, &D3DXVECTOR3(float(iCenterX), float(iCenterY), 0.f), &D3DXVECTOR3(400.f, 300.f, 0.f), D3DCOLOR_ARGB(255, 255, 255, 255));
		//	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr/*&rc*/, &D3DXVECTOR3(float(iCenterX), float(iCenterY), 0.f), nullptr/*&D3DXVECTOR3(400.f, 300.f, 0.f)*/, D3DCOLOR_ARGB(255, 255, 255, 255));

		//}
	}


	CGraphic_Device::Get_Instance()->Render_End();
}


// CMFC_ToolView 인쇄

BOOL CMFC_ToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFC_ToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFC_ToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFC_ToolView 진단

#ifdef _DEBUG
void CMFC_ToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_ToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_ToolDoc* CMFC_ToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_ToolDoc)));
	return (CMFC_ToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_ToolView 메시지 처리기


void CMFC_ToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	g_hWND = m_hWnd;
	if (FAILED(CGraphic_Device::Get_Instance()->Ready_Graphic_Device()))
	{
		ERR_MSG(L"Ready GraphicDevice Fail");
		return;
	}

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::SINGLE_TEX, L"../Texture/Cube.png", L"Cube")))
	{
		ERR_MSG(L"Insert_Single_Texture Failed");
		return;
	}

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Terrain/Tile/Tile%d.png", L"Terrain", L"Tile", 38)))
	{
		ERR_MSG(L"Insert_Multi_Texture Failed");
		return;
	}

	if (nullptr == m_pTerrain)
	{
		m_pTerrain = new CTerrain;
		m_pTerrain->Ready_Terrain();
	}


	//SetTimer();
	// CMFCToolView 클래스뷰에 속성창 보면 VM_TIMER를 설정한 시간마다 호출하게 됩니다.

}


void CMFC_ToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	TCHAR szBuf[MAX_PATH] = L"";
	swprintf_s(szBuf, L"X :%d, Y : %d", point.x, point.y);
	ERR_MSG(szBuf);
	CView::OnLButtonDown(nFlags, point);
}
