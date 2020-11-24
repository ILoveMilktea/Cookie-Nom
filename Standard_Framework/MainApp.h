#pragma once

#ifndef __MAINAPP_H__
#define __MAINAPP_H__

// final -> ����� ������
// abstract -> ��üȭ���� �ʴ´�.

class CObj;
class CMainApp final
{
public:
	explicit CMainApp();
	~CMainApp();

public:
	// HRESULT ����, ������ �ǰ����ϴ� ������?
	// E_FAIL, S_OK�� �ᵵ �˴ϴ�. ����, ������ ������ �ǰŵ��
	HRESULT Ready_MainApp();
	void Update_MainApp();
	void Late_Update_MainApp();
	void Render_MainApp();
	void Release_MainApp();


private:
	DWORD m_dwRespawn;

private:
	HDC			m_hDC;
};


#endif // !__MAINAPP_H__

