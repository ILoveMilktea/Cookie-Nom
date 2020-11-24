#pragma once

#ifndef __OBJ_H__
#define __OBJ_H__

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual HRESULT Ready_GameObject() PURE;
	virtual int Update_GameObject() PURE;
	virtual void Late_Update_GameObject() PURE;
	virtual void Render_GameObject(HDC hDC) PURE;
	virtual void Release_GameObject() PURE;

public:
	void Set_Pos(float _x, float _y) { m_tInfo.vPos.x = _x; m_tInfo.vPos.y = _y; }
	//void Set_Pos(Vec3 _v) { m_tInfo.vPos = _v; }
	void Set_Dead() { m_bDead = true; }
	void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	void Set_PosX(float _x) { m_tInfo.vPos.x += _x; }
	void Set_PosY(float _y) { m_tInfo.vPos.y += _y; }
	//	void Set_BulletSizeUP(float _x, float _y) { m_tInfo.iCX += _x, m_tInfo.iCY += _y; }


public:
	const INFO& Get_Info() const { return m_tInfo; }
	const RECT& Get_Rect() const { return m_tRect; }

	int Set_HP(int _iDmg) { return (m_iHP -= _iDmg); }
	const float Get_ATK() const { return m_fAttackPoint; }
	const int Get_HP() const { return m_iHP; }
	const float Get_BoomPoint() const { return m_fBoomPoint; }
	const int	Get_Life() const { return m_iLife; }
	const bool Get_Dead() const {
		if (m_bDead)
			return true;
		return false;
	}

	const bool BossAppear() const {
		if (m_bBossAppear)
			return true;
		return false;
	}


	void Set_Pause(float _x, float _y)
	{
		m_tInfo.vPos.x += _x, m_tInfo.vPos.y += _y;
	}

	//---------------Ãß°¡

public:
	void Set_Dir(D3DXVECTOR3 _vDir);


protected:
	void Update_Rect();

protected:
	Vec3	m_vVertex[4];
	Vec3	m_vVertex_Trans[4];

	INFO	m_tInfo;
	RECT	m_tRect;
	float	m_fSpeed;
	float	m_fAngle;
	bool	m_bDead;
	bool	m_bBossAppear;

	const CObj*	m_pTarget;


	DWORD	dw_ShotDelay;
	DWORD	dw_MissileDelay;

	bool	m_bStart;



	float	m_fAttackPoint;
	float	m_fBoomPoint;
	int		m_iLife;


	int		m_iHP;
	int		m_iMaxHP;
};

#endif // !__OBJ_H__
