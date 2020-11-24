#include "stdafx.h"
#include "MyEdit.h"


CMyEdit::CMyEdit()
	:m_iRow(0), m_iCol(0)
{
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize()
{
}

void CMyEdit::Update()
{
	Key_Check();
}

void CMyEdit::Late_Update()
{
}

void CMyEdit::Render(HDC _DC)
{
}

void CMyEdit::Release()
{
}

void CMyEdit::Insert_Map_Img()
{
}

void CMyEdit::Key_Check()
{

}
