#include "stdafx.h"
#include "LineMgr.h"
#include "Line.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;
CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
	LINEPOS Temp[4] = { { 0.f, 500.f },{ 800.f, 500.f } };

	m_listLine.emplace_back(new CLine(Temp[0], Temp[1]));
}

void CLineMgr::Render(HDC _DC)
{
	for (auto& pLine : m_listLine)
		pLine->Render_Line(_DC);
}

void CLineMgr::Release()
{
	for_each(m_listLine.begin(), m_listLine.end(), Safe_Delete<CLine*>);
	m_listLine.clear();
}

bool CLineMgr::Collision_Line(float _x, float * _y)
{
	CLine* pTarget = nullptr;

	for (auto& pLine : m_listLine)
	{
		if (pLine->Get_LineInfo().tLeftPos.fX < _x
			&& pLine->Get_LineInfo().tRightPos.fX > _x)
		{
			pTarget = pLine;
			break;
		}
	}

	if (!pTarget)
		return false;

	float x1 = pTarget->Get_LineInfo().tLeftPos.fX;
	float y1 = pTarget->Get_LineInfo().tLeftPos.fY;
	float x2 = pTarget->Get_LineInfo().tRightPos.fX;
	float y2 = pTarget->Get_LineInfo().tRightPos.fY;

	*_y = ((y2 - y1) / (x2 - x1)) * (_x - x1) + y1;

	return true;
}

