#pragma once

#ifndef __FUNCTOR_H__
#define __FUNCTOR_H__

class CStrCmp
{
public:
	CStrCmp(const TCHAR* _pStr) : m_pStr(_pStr) {}

public:
	template <typename T>
	bool operator()(T& _Dst)
	{
		return !lstrcmp(m_pStr, _Dst.first);
	}

private:
	const TCHAR* m_pStr;
};

#endif // !__FUNCTOR_H__
