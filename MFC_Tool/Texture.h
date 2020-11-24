#pragma once
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

class CTexture abstract
{
public:
	explicit CTexture();
	virtual ~CTexture();
public:
	virtual const TEXINFO* Get_TexInfo(
		const wstring& wstrStateKey = L"",
		const int& iIndex = 0) PURE;
	//	파일경로, key?, 상태key?(multi), index(multi)
	virtual HRESULT Insert_Texture(
		const wstring& wstrFilePath,
		const wstring& wstrStateKey = L"",
		const int & iIndex = 0) PURE;
	// 앞으로 그림을 보관할 때 방법은 objectkey 안에 statekey가 존재합니다.
	// 단 이건 멀티 텍스쳐일 경우임
	// 싱글텍스쳐는 오브젝트키는 필요해도 그냥 한장이라 statekey는 필요가 없어요.

	virtual void Release_Texture() PURE;
};

#endif // !__TEXTURE_H__
