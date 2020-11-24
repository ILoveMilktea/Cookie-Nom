#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
//#include "Boss.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

bool CCollisionMgr::Check_Sphere(CObj* _Dst, CObj* _Src)
{
	float fX = abs(_Dst->Get_Info().vPos.x - _Src->Get_Info().vPos.x);
	float fY = _Dst->Get_Info().vPos.y - _Src->Get_Info().vPos.y;
	float fDia = sqrtf(fX * fX + fY * fY);

	float fDis = (float)((_Dst->Get_Info().vSize.x + _Src->Get_Info().vSize.x) * 0.5f);

	return fDia <= fDis;

	if (fDia <= fDis)
		return true;

	return false;
}

bool CCollisionMgr::Check_Rect(CObj* _Dst, CObj* _Src, float* _x, float* _y)
{
	float fDisX = abs(_Dst->Get_Info().vPos.x - _Src->Get_Info().vPos.x);
	float fDisY = abs(_Dst->Get_Info().vPos.y - _Src->Get_Info().vPos.y);

	float fCX = (float)((_Dst->Get_Info().vSize.x + _Src->Get_Info().vSize.x) * 0.5f);
	float fCY = (float)((_Dst->Get_Info().vSize.y + _Src->Get_Info().vSize.y) * 0.5f);

	if (fDisX < fCX && fDisY < fCY)
	{
		*_x = fCX - fDisX;
		*_y = fCY - fDisY;
		return true;
	}

	return false;
}

bool CCollisionMgr::Check_PointRect(CObj * _Dst, float _x, float _y)
{
	if (_x >= (float)_Dst->Get_Rect().left && _x <= (float)_Dst->Get_Rect().right)
	{
		if (_y >= (float)_Dst->Get_Rect().top && _y <= (float)_Dst->Get_Rect().bottom)
			return true;
	}

	return false;
}

void CCollisionMgr::Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &Dst->Get_Rect(), &Src->Get_Rect()))
			{
				Dst->Set_HP(50);
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_Dead(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &Dst->Get_Rect(), &Src->Get_Rect()))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_RectEx(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	float fX = 0.f, fY = 0.f;
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fX, &fY))
			{
				if (fX < fY)
				{
					if (Dst->Get_Info().vPos.x < Src->Get_Info().vPos.x)
						Src->Set_PosX(fX);
					else
						Src->Set_PosX(-fX);
				}
				else
				{
					if (Dst->Get_Info().vPos.y < Src->Get_Info().vPos.y)
						Src->Set_PosY(fY);
					else
						Src->Set_PosY(-fY);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Rock(list<CObj*>& _Dst, list<CObj*>& _Src)
{


	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_PointRect(Dst, (float)Src->Get_Rect().left, (float)Src->Get_Rect().top))
			{
				Dst->Set_Pause(-5.f, -5.f);
			}
			if (Check_PointRect(Dst, (float)Src->Get_Rect().left, (float)Src->Get_Rect().bottom))
			{
				Dst->Set_Pause(-5.f, 5.f);
			}
			if (Check_PointRect(Dst, (float)Src->Get_Rect().right, (float)Src->Get_Rect().top))
			{
				Dst->Set_Pause(5.f, -5.f);

			}
			if (Check_PointRect(Dst, (float)Src->Get_Rect().right, (float)Src->Get_Rect().bottom))
			{
				Dst->Set_Pause(5.f, 5.f);

			}
		}
	}
}


void CCollisionMgr::Collision_SphereDead(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_SphereDMG(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				Dst->Set_HP(50);
				Src->Set_Dead();
			}
		}
	}
}

