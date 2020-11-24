#include "stdafx.h"
#include "Texture_Manager.h"
#include "Single_Texture.h"
#include "Multi_Texture.h"

#include "Graphic_Device.h"


CTexture_Manager* CTexture_Manager::m_pInstance = nullptr;

CTexture_Manager::CTexture_Manager()
{
}


CTexture_Manager::~CTexture_Manager()
{
	Release_Texture_Manager();
}

void CTexture_Manager::Initialize_Manager()
{
	if (FAILED(CGraphic_Device::Get_Instance()->Ready_Graphic_Device()))
	{
		ERR_MSG(L"Ready GraphicDevice Fail");
		return;
	}

	// Single Texture (���ȭ��)
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::SINGLE_TEX, L"../Texture/background.png", L"background")))
	{
		ERR_MSG(L"Insert_Single_Texture Failed");
		return;
	}

	Insert_Texture_Obstacle();

	// Multi Texture (player)
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Player/Walk/cookie0001_run0%d.png", L"Player", L"Player_Run", 4)))
	{
		ERR_MSG(L"Insert_Multi_Texture Failed");
		return;
	}

	// ���� ���⼭ �߰��ϰ���� �ؽ��ĵ��� API�� ��Ʈ�� �θ��°�ó�� �߰��س��� Key�� �θ��ø� �˴ϴ�.
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

void CTexture_Manager::Insert_Texture_Obstacle()
{

	// Multi Texture
	// 1. single jump
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Obstacle/jp_spike_%d.png", L"Obstacle", L"jp_spike", 2)))
	{
		ERR_MSG(L"Insert Spike Obstacle Failed");
		return;
	}
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Obstacle/jp_trap_%d.png", L"Obstacle", L"jp_trap", 2)))
	{
		ERR_MSG(L"Insert Trap Obstacle Failed");
		return;
	}
	// 2. double jump
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Obstacle/dbjp_fork_%d.png", L"Obstacle", L"dbjp_fork", 2)))
	{
		ERR_MSG(L"Insert Fork Obstacle Failed");
		return;
	}
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Obstacle/dbjp_greenflask_%d.png", L"Obstacle", L"dbjp_greenflask", 3)))
	{
		ERR_MSG(L"Insert Green Flask Obstacle Failed");
		return;
	}
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Obstacle/dbjp_pinkflask_%d.png", L"Obstacle", L"dbjp_pinkflask", 3)))
	{
		ERR_MSG(L"Insert Pink Flask Obstacle Failed");
		return;
	}
	// 3. slide
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Obstacle/sd_candy_%d.png", L"Obstacle", L"sd_candy", 2)))
	{
		ERR_MSG(L"Insert Candy Obstacle Failed");
		return;
	}
	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture_Manager(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Obstacle/sd_fork_%d.png", L"Obstacle", L"sd_fork", 2)))
	{
		ERR_MSG(L"Insert Slide Fork Obstacle Failed");
		return;
	}
}
