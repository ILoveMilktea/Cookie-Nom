
// MFC_ToolView.cpp : CMFC_ToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMFC_ToolView ����/�Ҹ�

CMFC_ToolView::CMFC_ToolView()
	:m_pTerrain(nullptr)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMFC_ToolView::~CMFC_ToolView()
{
	CGraphic_Device::Destroy_Instance();
	CTexture_Manager::Destroy_Instance();

	SAFE_DELETE(m_pTerrain);
}

BOOL CMFC_ToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMFC_ToolView �׸���

void CMFC_ToolView::OnDraw(CDC* pDC)	// WM_PAINT ��� �޼����� �߻����� �� �����ϴ� �Լ�
{
	CMFC_ToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	CGraphic_Device::Get_Instance()->Render_Begin();

	m_pTerrain->Render_Terrain();
	// �Ʒ��� �����ð��� �ߴ� Cube�׸�, tile �Ѱ� �׸���
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


// CMFC_ToolView �μ�

BOOL CMFC_ToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFC_ToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFC_ToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMFC_ToolView ����

#ifdef _DEBUG
void CMFC_ToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMFC_ToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC_ToolDoc* CMFC_ToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC_ToolDoc)));
	return (CMFC_ToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFC_ToolView �޽��� ó����


void CMFC_ToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
	// CMFCToolView Ŭ�����信 �Ӽ�â ���� VM_TIMER�� ������ �ð����� ȣ���ϰ� �˴ϴ�.

}


void CMFC_ToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	TCHAR szBuf[MAX_PATH] = L"";
	swprintf_s(szBuf, L"X :%d, Y : %d", point.x, point.y);
	ERR_MSG(szBuf);
	CView::OnLButtonDown(nFlags, point);
}
