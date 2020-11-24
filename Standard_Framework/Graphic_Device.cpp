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
	// 1. ��ġ ���������� �����ؼ� �����͸� ������ ����ü
	D3DCAPS9 DeviceCap;
	ZeroMemory(&DeviceCap, sizeof(D3DCAPS9));
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	// HAL : hardware abstract layer �׷���ī�� �����ϴ°�?
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,&DeviceCap)))	// ���� �������ִ� �׷���ī�� ������ ����, MS�� ��û�ϰ� �ٸ� �׷���ī���� ���� �������� �ʰ���?
	{
		ERR_MSG(L"Create SDK Failed");	// mfc������ afx�� �پ�� 
		return E_FAIL;
	}

	DWORD vp = 0;	// vertex processing, 1�̸� hardware���� ó���ϰ�, 0�̸� software���� �����մϴ�.
	if (DeviceCap.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)	// TRANSFORM, LIGHT ó���� �ϰٽ��ϴ�.
	{
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		// ��ǻ� elseŸ�� ��찡 �����!
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	// d3dpp parameter ä���ݽô�
	d3dpp.BackBufferWidth			= WINCX;
	d3dpp.BackBufferHeight			= WINCY;
	d3dpp.BackBufferFormat			= D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount			= 1;						// 1�� �� 2���� ����� ����ϰڴ�, default�� �Ѱ� ����ϴ�.

	d3dpp.MultiSampleType			= D3DMULTISAMPLE_NONE;		// �𼭸� �ȼ��� ���������� �ε巴�� �����ݴϴ�
	d3dpp.MultiSampleQuality		= 0;

	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// DISCARD	: ����ü�� ����, �ĸ� ���� ����� �ĸ鿡 �׸� �� �� �׸��� �ΰ��� �ٲߴϴ�. ��� �ݺ�
																// FLIP		: ?
																// COPY		: ������۸�, �ڿ� �׸��� �����ؼ� �δ��� Ŀ��
	d3dpp.hDeviceWindow				= g_hWND; // �ʰ� �׸��� �׸��� ���
	d3dpp.Windowed					= TRUE;	// FALSE ��ü, TRUE â
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
	lstrcpy(tFontInfo.FaceName, L"���� ���");

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

	//����� ������ �߿��ؿ�
	// ���۷��� ī���͸� ����Ѵٰ� �ϴµ�
	// ��۸� �����͸� �����ϱ� ���� ����߿� �ϳ���� �մϴ�.
	// ���� ��ü���� �ϳ��� graphic device�� �����ϰ� ���� �� reference counter�� �����ϴ°̴ϴ�.
	// �����ϴ� �ֵ��� ���� ������� �������� graphic device�� ����°���
	// device �ȿ��� ���������� LPDIRECT3D9 �����ؼ� ����ϰ� �ֱ� ������ device ���� �����ϰ� LPDIRECT3D9�� �����սô�.
}

void CGraphic_Device::Render_Begin()
{
	// 1. �ĸ� ���۸� ����
	m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	// 2. �ĸ� ���ۿ� �׸�
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

}

void CGraphic_Device::Render_End()
{
	m_pSprite->End();
	m_pDevice->EndScene();
	// 3. ���� ���ۿ� ��ü
	// 4. �ÿ�
	m_pDevice->Present(nullptr, nullptr, nullptr, nullptr);	// 3��°�� �ٲ� �� �ִ� �����Դϴ�.
}
