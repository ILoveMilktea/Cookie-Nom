#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{
}

CLine::CLine(LINEPOS _tLeftPos, LINEPOS _tRightPos)
	:m_tLineInfo(_tLeftPos, _tRightPos)
{
}


CLine::~CLine()
{
	Release_Line();
}

HRESULT CLine::Ready_Line()
{
	return S_OK;
}

void CLine::Render_Line(HDC _DC)
{
	MoveToEx(_DC, (int)m_tLineInfo.tLeftPos.fX, (int)m_tLineInfo.tLeftPos.fY, nullptr);
	LineTo(_DC, (int)m_tLineInfo.tRightPos.fX, (int)m_tLineInfo.tRightPos.fY);
}

void CLine::Release_Line()
{
}
