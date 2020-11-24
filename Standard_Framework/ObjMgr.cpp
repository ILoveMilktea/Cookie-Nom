#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "CollisionMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Add_Object(OBJID::ID _eID, CObj* _pObj)
{
	m_listObj[_eID].emplace_back(_pObj);
}

void CObjMgr::Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& iter = m_listObj[i].begin(); iter != m_listObj[i].end();)
		{
			int iEvent = (*iter)->Update_GameObject();
			if (OBJ_DEAD == iEvent)
			{
				SAFE_DELETE(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
		}
	}




}

void CObjMgr::Late_Update()
{
	// 데미지판정
	//CCollisionMgr::Collision_SphereDMG(m_listObj[OBJID::MONSTER], m_listObj[OBJID::BULLET]);
	//CCollisionMgr::Collision_SphereDMG(m_listObj[OBJID::PLAYER], m_listObj[OBJID::ENEMYBULLET]);

	//CCollisionMgr::Collision_SphereDMG(m_listObj[OBJID::PLAYER], m_listObj[OBJID::ENEMYMISSILE]);
	//CCollisionMgr::Collision_SphereDMG(m_listObj[OBJID::BOSS], m_listObj[OBJID::BULLET]);


	// 충돌판정
	//CCollisionMgr::Collision_RectEx(m_listObj[OBJID::BOSS], m_listObj[OBJID::MONSTER]);


	// 즉사판정
	//CCollisionMgr::Collision_SphereDead(m_listObj[OBJID::MONSTER], m_listObj[OBJID::PLAYER]);
	//CCollisionMgr::Collision_SphereDead(m_listObj[OBJID::BOSS], m_listObj[OBJID::PLAYER]);




	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
			pObj->Late_Update_GameObject();
	}
}

void CObjMgr::Render(/*HDC _DC*/)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& pObj : m_listObj[i])
			pObj->Render_GameObject();
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CObj*>);
		m_listObj[i].clear();
	}
}

const CObj* CObjMgr::Get_Target(OBJID::ID _eID, CObj* _pObj)
{
	CObj*	pTarget = nullptr;
	float	fDis = 0.f;

	for (auto& pObj : m_listObj[_eID])
	{
		float fX = pObj->Get_Info().vPos.x - _pObj->Get_Info().vPos.x;
		float fY = pObj->Get_Info().vPos.y - _pObj->Get_Info().vPos.y;
		float fDia = sqrtf(fX * fX + fY * fY);

		if (fDis > fDia || !pTarget)
		{
			fDis = fDia;
			pTarget = pObj;
		}
	}

	return pTarget;
}

void CObjMgr::Set_ABL(CObj * _player)
{
}
