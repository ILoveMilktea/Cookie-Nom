#pragma once

#ifndef __LINE_H__
#define __LINE_H__

class CLine final
{
public:
	CLine();
	CLine(LINEPOS _tLeftPos, LINEPOS _tRightPos);
	~CLine();

public:
	HRESULT Ready_Line();
	void	Render_Line(HDC _DC);
	void	Release_Line();

public:
	const LINEINFO& Get_LineInfo() { return m_tLineInfo; }

private:
	LINEINFO	m_tLineInfo;
};

#endif // !__LINE_H__
