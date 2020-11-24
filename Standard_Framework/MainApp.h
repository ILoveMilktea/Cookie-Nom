#pragma once

#ifndef __MAINAPP_H__
#define __MAINAPP_H__

// final -> 상속의 마지막
// abstract -> 객체화하지 않는다.

class CObj;
class CMainApp final
{
public:
	explicit CMainApp();
	~CMainApp();

public:
	// HRESULT 실패, 성공을 판가름하는 정수형?
	// E_FAIL, S_OK만 써도 됩니다. 실패, 성공만 따져도 되거든요
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

