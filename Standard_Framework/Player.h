#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Obj.h"

class CPlayer final
	: public CObj
{
private:
	explicit CPlayer();
	~CPlayer() = default;

public:
	virtual HRESULT Ready_GameObject();
	virtual int Update_GameObject();
	virtual void Late_Update_GameObject();
	virtual void Render_GameObject(HDC hDC);
	virtual void Release_GameObject();

public:
	static CObj* Create();
	void Free();

public:
	bool	Get_Jump() { return m_bJump; }

private:
	void	Jumping();

private:
	bool	m_bJump;
	float	m_fJumpPower;
	float	m_fJumpTime;
	float	m_fJumpY;

private:
	D3DXVECTOR3 m_vP[4];
	D3DXVECTOR3 m_vQ[4]; 
};



#endif // !__PLAYER_H__

