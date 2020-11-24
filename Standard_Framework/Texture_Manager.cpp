#include "stdafx.h"
#include "Texture_Manager.h"
#include "Single_Texture.h"
#include "Multi_Texture.h"

CTexture_Manager* CTexture_Manager::m_pInstance = nullptr;

CTexture_Manager::CTexture_Manager()
{
}


CTexture_Manager::~CTexture_Manager()
{
	Release_Texture_Manager();
}

const TEXINFO * CTexture_Manager::Get_TexInfo(const wstring & wstrObjectKey, const wstring & wstrStateKey, const int & iIndex)
{
	auto& iter = m_mapTexture.find(wstrObjectKey);
	if (m_mapTexture.end() == iter)
		return nullptr;

	return iter->second->Get_TexInfo(wstrStateKey, iIndex);
}

HRESULT CTexture_Manager::Insert_Texture_Manager(TEX_ID eTexID, const wstring & wstrFilePath, const wstring & wstrObjectKey, const wstring & wstrStateKey, const int & iIndex)
{
	auto& iter = m_mapTexture.find(wstrObjectKey);

	CTexture* pTexture = nullptr;
	if (m_mapTexture.end() == iter)
	{
		switch (eTexID)
		{
		case CTexture_Manager::SINGLE_TEX:
			pTexture = new CSingle_Texture;
			break;
		case CTexture_Manager::MULTI_TEX:
			pTexture = new CMulti_Texture;
			break;
		default:
			break;
		}

		if (FAILED(pTexture->Insert_Texture(wstrFilePath, wstrStateKey, iIndex)))
		{
			ERR_MSG(L"TextureManager Insert Failed");
			return E_FAIL;
		}
		m_mapTexture.emplace(wstrObjectKey, pTexture);
	}
	else if (eTexID == MULTI_TEX)
	{
		if (FAILED(m_mapTexture[wstrObjectKey]->Insert_Texture(wstrFilePath, wstrStateKey, iIndex)))
		{
			ERR_MSG(L"TextureManager MultiTexture Insert Faield");
			return E_FAIL;
		}
	}

	return S_OK;
}


void CTexture_Manager::Release_Texture_Manager()
{
	for (auto& pair : m_mapTexture)
		Safe_Delete<CTexture*>(pair.second);

	m_mapTexture.clear();

}
