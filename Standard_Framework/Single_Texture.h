#pragma once
#ifndef __SINGLE_TEXTURE_H__
#define __SINGLE_TEXTURE_H__

#include "Texture.h"
class CSingle_Texture final:
	public CTexture
{
public:
	explicit CSingle_Texture();
	virtual ~CSingle_Texture();

public:

	// CTexture을(를) 통해 상속됨
	virtual const TEXINFO * Get_TexInfo(const wstring & wstrStateKey = L"", const int & iIndex = 0) override;
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey = L"", const int & iIndex = 0) override;
	virtual void Release_Texture() override;

private:
	TEXINFO m_tTexInfo;
};

#endif // !__SINGLE_TEXTURE_H__
