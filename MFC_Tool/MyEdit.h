#pragma once

class CMyEdit
{
public:
	CMyEdit();
	~CMyEdit();

public:
	// CScene��(��) ���� ��ӵ�
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

private:
	void Insert_Map_Img();
	void Key_Check();

	int m_iRow;
	int m_iCol;

};

