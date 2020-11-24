#pragma once
#include "Obj.h"
class CObstacle :
	public CObj
{
public:
	enum TYPE { JUMP, DOUBLEJUMP, SLIDE, END };
public:
	CObstacle();
	virtual ~CObstacle();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject(/*HDC hDC*/) override;
	virtual void Release_GameObject() override;

public:
	void Set_ObjectKey(const wstring& wstrObjectKey) { m_wstrObjectKey = wstrObjectKey; }
	void Set_StateKey(const wstring& wstrStateKey) { m_wstrStateKey = wstrStateKey; }
	void Set_BeginIndex(int iIndex) { m_iIndex = iIndex; }
	void Set_FrameCount(int iFrameCount) { m_iFrameCount = iFrameCount; }

	void Set_TextureInfo(const wstring& wstrObjectKey, const wstring& wstrStateKey, int iIndex, int iFrameCount, TYPE eType);


private:
	TYPE		m_eType;

	wstring		m_wstrObjectKey;
	wstring		m_wstrStateKey;
	int			m_iIndex;

	DWORD		m_dwFrameTime;
	int			m_iFrameCount;
};

