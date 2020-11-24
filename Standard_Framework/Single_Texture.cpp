#include "stdafx.h"
#include "Single_Texture.h"

#include "Graphic_Device.h"

CSingle_Texture::CSingle_Texture()
{
	ZeroMemory(&m_tTexInfo, sizeof(TEXINFO));
}


CSingle_Texture::~CSingle_Texture()
{
	Release_Texture();
}

const TEXINFO * CSingle_Texture::Get_TexInfo(const wstring & wstrStateKey, const int & iIndex)
{
	return &m_tTexInfo;
}

HRESULT CSingle_Texture::Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey, const int & iIndex)
{
	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_tTexInfo.tImageInfo)))
	{
		ERR_MSG(L"Loading ImageInfo Failed");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFileEx(
		CGraphic_Device::Get_Instance()->Get_Device(),
		wstrFilePath.c_str(),
		m_tTexInfo.tImageInfo.Width, m_tTexInfo.tImageInfo.Height,
		m_tTexInfo.tImageInfo.MipLevels,	// mipmap
		0,
		m_tTexInfo.tImageInfo.Format,
		D3DPOOL_MANAGED,		// 니가 그림을 불러와서 어디에 저장할꺼니? DEFAULT : ONLY GPU RAM(그래픽카드 용량 부족하면 그림을 버림), MANAGED : 기본 GPU 부족하면 SYSTEMMEM을 사용, SYSTEMMEM : RAM에 저장(속도가 느림)
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,	//뺴고싶은 색상?
		nullptr,
		nullptr, // 팔레트? 안씀
		&m_tTexInfo.pTexture)
	))
	{
		wstring wstrErr = wstrFilePath + L"Loading Failed";
		ERR_MSG(wstrErr.c_str());
		return E_FAIL;
	}

	return S_OK;
}

void CSingle_Texture::Release_Texture()
{
	if (m_tTexInfo.pTexture)
	{
		m_tTexInfo.pTexture->Release();
	}
}
