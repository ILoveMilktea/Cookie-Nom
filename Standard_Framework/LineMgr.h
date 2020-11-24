#pragma once

#ifndef __LINEMGR_H__
#define __LINEMGR_H__

class CLine;
class CLineMgr
{
public:
	static CLineMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;
		return m_pInstance;
	}
	static void Destory_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	CLineMgr();
	~CLineMgr();

public:
	void Initialize();
	void Render(HDC _DC);
	void Release();

public:
	bool Collision_Line(float _x, float* _y);

private:
	list<CLine*>		 m_listLine;
	static CLineMgr*	 m_pInstance;
};

#endif // !__LINEMGR_H__
