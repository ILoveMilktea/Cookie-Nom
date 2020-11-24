#include "stdafx.h"
#include "Graphic_Device.h"

CGraphic_Device* CGraphic_Device::m_pInstance = nullptr;

CGraphic_Device::CGraphic_Device()
{
}


CGraphic_Device::~CGraphic_Device()
{
	Release_Graphic_Device();
}

HRESULT CGraphic_Device::Ready_Graphic_Device()
{
	// 1. 장치 지원수준을 조사해서 데이터를 보관할 구조체
	D3DCAPS9 DeviceCap;
	ZeroMemory(&DeviceCap, sizeof(D3DCAPS9));
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	// HAL : hardware abstract layer 그래픽카드 구분하는거?
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,&DeviceCap)))	// 현재 끼워져있는 그래픽카드 수준을 조사, MS가 멍청하게 다른 그래픽카드라고 지원 안하지는 않겠죠?
	{
		ERR_MSG(L"Create SDK Failed");	// mfc에서는 afx가 붙어요 
		return E_FAIL;
	}

	DWORD vp = 0;	// vertex processing, 1이면 hardware에서 처리하고, 0이면 software에서 내가합니다.
	if (DeviceCap.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)	// TRANSFORM, LIGHT 처리를 하겟습니다.
	{
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		// 사실상 else타는 경우가 없어요!
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	// d3dpp parameter 채워줍시다
	d3dpp.BackBufferWidth			= WINCX;
	d3dpp.BackBufferHeight			= WINCY;
	d3dpp.BackBufferFormat			= D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount			= 1;						// 1은 총 2개의 백버퍼 사용하겠다, default로 한개 생깁니다.

	d3dpp.MultiSampleType			= D3DMULTISAMPLE_NONE;		// 모서리 픽셀을 뭉개가지고 부드럽게 보여줍니다
	d3dpp.MultiSampleQuality		= 0;

	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// DISCARD	: 스왑체인 전면, 후면 버퍼 만들고 후면에 그린 후 다 그리면 두개를 바꿉니다. 계속 반복
																// FLIP		: ?
																// COPY		: 더블버퍼링, 뒤에 그리고 복사해서 부담이 커요
	d3dpp.hDeviceWindow				= g_hWND; // 너가 그림을 그리는 대상
	d3dpp.Windowed					= TRUE;	// FALSE 전체, TRUE 창
	d3dpp.EnableAutoDepthStencil	= TRUE;	
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8; // depth 24 bit, stencil 8 bit
	//d3dpp.Flags					= ;

	/* FullScreen_RefreshRateInHz must be zero for Windowed mode */
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWND, vp, &d3dpp, &m_pDevice)))
	{
		ERR_MSG(L"Device Creating Failed");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		ERR_MSG(L"Sprite Creating Failed");
		return E_FAIL;
	}

	D3DXFONT_DESCW tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));
	tFontInfo.Height = 20;
	tFontInfo.Width = 10;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"맑은 고딕");

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		ERR_MSG(L"Font Creating Failed");
		return E_FAIL;
	}

	return S_OK;
}

void CGraphic_Device::Release_Graphic_Device()
{
	if (m_pFont)
		m_pFont->Release();
	if (m_pSprite)
		m_pSprite->Release();
	if (m_pDevice)
		m_pDevice->Release();
	if (m_pSDK)
		m_pSDK->Release();

	//지우는 순서가 중요해요
	// 레퍼런스 카운터를 사용한다고 하는데
	// 댕글링 포인터를 방지하기 위한 기법중에 하나라고 합니다.
	// 여러 객체에서 하나의 graphic device를 참조하고 있을 때 reference counter로 관리하는겁니다.
	// 참조하는 애들이 전부 사라지면 그제서야 graphic device를 지우는거죠
	// device 안에서 내부적으로 LPDIRECT3D9 참조해서 사용하고 있기 때문에 device 먼저 제거하고 LPDIRECT3D9를 제거합시다.
}

void CGraphic_Device::Render_Begin()
{
	// 1. 후면 버퍼를 지움
	m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	// 2. 후면 버퍼에 그림
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

}

void CGraphic_Device::Render_End()
{
	m_pSprite->End();
	m_pDevice->EndScene();
	// 3. 전면 버퍼와 교체
	// 4. 시연
	m_pDevice->Present(nullptr, nullptr, nullptr, nullptr);	// 3번째가 바꿀 수 있는 인자입니다.
}
