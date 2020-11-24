#pragma once

#ifndef __COLLISIONMGR_H__
#define __COLLISIONMGR_H__


class CObj;
class CBoss;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static bool Check_Sphere(CObj* _Dst, CObj* _Src);
	static bool Check_Rect(CObj* _Dst, CObj* _Src, float* _x, float* _y);

	static bool Check_PointRect(CObj* _Dst, float _x, float _y);


public:
	static void Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Dead(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_RectEx(list<CObj*>& _Dst, list<CObj*>& _Src);

	static void Collision_Rock(list<CObj*>& _Dst, list<CObj*>& _Src);

	static void Collision_SphereDead(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_SphereDMG(list<CObj*>& _Dst, list<CObj*>& _Src);
};


#endif // !__COLLISIONMGR_H__
