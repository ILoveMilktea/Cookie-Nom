#include "stdafx.h"
#include "Terrain.h"

#include "Graphic_Device.h"
#include "Texture_Manager.h"

CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release_Terrain();
}

void CTerrain::TileChange(const D3DXVECTOR3 & vMousePos, const BYTE & byDrawID, const BYTE & byOption)
{
}

HRESULT CTerrain::Ready_Terrain()
{
	float fX = 0.f, fY = 0.f;
	TILE* pTile = nullptr;
	m_vecTile.reserve(TILEX * TILEY);

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			pTile = new TILE;
			pTile->vSize = { 1.f, 1.f, 0.f };
			pTile->byDrawID = 2;
			pTile->byOption = 0;
			
			fX = (float)((j * TILECX) + (i % 2) * (TILECX >> 1));
			fY = (float)(i * (TILECY >> 1));

			pTile->vPos = { fX, fY, 0.f };
			m_vecTile.emplace_back(pTile);
		}
	}
	return S_OK;
}

void CTerrain::Render_Terrain()
{
	int iIndex = 0;
	TCHAR szBuf[MAX_PATH] = L"";
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			iIndex = j + (i*TILEX);
			swprintf_s(szBuf, L"%d", iIndex);
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", m_vecTile[iIndex]->byDrawID);
			if (nullptr == pTexInfo)
				return;

			float fCenterX = (float)(pTexInfo->tImageInfo.Width >> 1);
			float fCenterY = (float)(pTexInfo->tImageInfo.Height >> 1);

			D3DXMATRIX matScale, matTrans, matWorld;
			D3DXMatrixScaling(&matScale, m_vecTile[iIndex]->vSize.x, m_vecTile[iIndex]->vSize.y, m_vecTile[iIndex]->vSize.z);
			D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y, m_vecTile[iIndex]->vPos.z);
			matWorld = matScale * matTrans;

			// 타일 위치 세팅
			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
			// 타일 그리기
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
			// 타일 위에 index 추가
			CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
		}
	}
}

void CTerrain::Release_Terrain()
{
	for (auto& pTile : m_vecTile)
	{
		Safe_Delete(pTile);
	}
	m_vecTile.clear();
	m_vecTile.swap(vector<TILE*>());
}
