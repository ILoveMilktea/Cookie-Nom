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
	//	���ϰ��, key?, ����key?(multi), index(multi)
	virtual HRESULT Insert_Texture(
		const wstring& wstrFilePath,
		const wstring& wstrStateKey = L"",
		const int & iIndex = 0) PURE;
	// ������ �׸��� ������ �� ����� objectkey �ȿ� statekey�� �����մϴ�.
	// �� �̰� ��Ƽ �ؽ����� �����
	// �̱��ؽ��Ĵ� ������ƮŰ�� �ʿ��ص� �׳� �����̶� statekey�� �ʿ䰡 �����.

	virtual void Release_Texture() PURE;
};

#endif // !__TEXTURE_H__
