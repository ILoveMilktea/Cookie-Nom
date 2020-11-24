#pragma once

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

template <typename T>
void Safe_Delete(T& _Dst)
{
	if (_Dst)
	{
		delete _Dst;
		_Dst = nullptr;
	}
}

#endif // !__FUNCTION_H__
