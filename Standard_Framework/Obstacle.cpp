#include "stdafx.h"
#include "Obstacle.h"

#include "Obj.h"
#include "Texture_Manager.h"
#include "Graphic_Device.h"

#define LANDY 140

#define JP_SIZEY 80
#define DBJP_SIZEY 160
#define SD_SIZEY 460

#define OBS_SIZEX 20

CObstacle::CObstacle()
	:m_eType(END), m_wstrObjectKey(L""), m_wstrStateKey(L""), m_iIndex(0), m_dwFrameTime(0), m_iFrameCount(0)
{
}


CObstacle::~CObstacle()
{
	Release_GameObject();
}

HRESULT CObstacle::Ready_GameObject()
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(m_wstrObjectKey, m_wstrStateKey, m_iIndex);
	UINT iCenterY = pTexInfo->tImageInfo.Height >> 1;

	switch (m_eType)
	{
	case CObstacle::JUMP:
		m_tInfo.vPos.y = WINCY - LANDY - iCenterY;
		m_tInfo.vSize = { float(OBS_SIZEX),float(JP_SIZEY),0.f };
	case CObstacle::DOUBLEJUMP:
		m_tInfo.vPos.y = WINCY - LANDY - iCenterY;
		m_tInfo.vSize = { float(OBS_SIZEX),float(DBJP_SIZEY),0.f };
		break;
	case CObstacle::SLIDE:
		m_tInfo.vPos.y = iCenterY;
		m_tInfo.vSize = { float(OBS_SIZEX),float(SD_SIZEY),0.f };
		break;
	case CObstacle::END:
		break;
	default:
		break;
	}

	//D3DXMATRIX matScale;
	//D3DXMatrixScaling(&matScale, 2.f, 2.f, 0.f);
	//D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &matScale);
	//D3DXVec3TransformCoord(&m_tInfo.vSize, &m_tInfo.vSize, &matScale);
	// rect
	// юс╫ц╥н update_rect
	Update_Rect();

	return E_NOTIMPL;
}

int CObstacle::Update_GameObject()
{
	return 0;
}

void CObstacle::Late_Update_GameObject()
{
}

void CObstacle::Render_GameObject(/*HDC hDC*/)
{
	Update_Rect();

	if (m_dwFrameTime + 100 < GetTickCount())
	{
		++m_iIndex;
		if (m_iIndex >= m_iFrameCount)
			m_iIndex = 0;

		m_dwFrameTime = GetTickCount();
	}

	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(m_wstrObjectKey, m_wstrStateKey, m_iIndex);

	if (nullptr == pTexInfo)
	{
		return;
	}

	UINT iCenterX = pTexInfo->tImageInfo.Width >> 1;
	UINT iCenterY = pTexInfo->tImageInfo.Height >> 1;

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
	//D3DXMatrixScaling(&matScale, 2.f, 2.f, 0.f);
	//D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	matWorld = /*matScale * matRotZ * */ matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr/*Rect*/, &D3DXVECTOR3(float(iCenterX), float(iCenterY), 0.f)/*Center*/, nullptr/*Pos*/, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CObstacle::Release_GameObject()
{
}

void CObstacle::Set_TextureInfo(const wstring & wstrObjectKey, const wstring & wstrStateKey, int iIndex, int iFrameCount, TYPE eType)
{
	m_wstrObjectKey = wstrObjectKey;
	m_wstrStateKey = wstrStateKey;
	m_iIndex = iIndex;
	m_iFrameCount = iFrameCount;
	m_eType = eType;
}
