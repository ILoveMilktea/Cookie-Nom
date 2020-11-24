#pragma once

#ifndef __OBJMGR_H__
#define __OBJMGR_H__

class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	void Add_Object(OBJID::ID _eID, CObj* _pObj);
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

public:
	const CObj* Get_Player() const { return m_listObj[OBJID::PLAYER].front(); }
	const CObj* Get_Boss() const { return m_listObj[OBJID::BOSS].front(); }
	const CObj* Get_Target(OBJID::ID _eID, CObj* _pObj);
	void Set_ABL(CObj* _player);

public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	list<CObj*>			m_listObj[OBJID::END];
	static CObjMgr*		m_pInstance;

};


#endif // !__OBJMGR_H__
