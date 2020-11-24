#pragma once

class CTexture;
class CTexture_Manager
{
public:
	static CTexture_Manager* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CTexture_Manager;
		}
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance) 
		{
			SAFE_DELETE(m_pInstance);
		}
	}

public:
	enum TEX_ID { SINGLE_TEX, MULTI_TEX };

private:
	CTexture_Manager();
	~CTexture_Manager();

public:
	void Initialize_Manager();
	const TEXINFO* Get_TexInfo(const wstring& wstrObjectKey, const wstring& wstrStateKey = L"", const int & iIndex = 0);
	HRESULT Insert_Texture_Manager(TEX_ID eTexID, const wstring& wstrFilePath, const wstring & wstrObjectKey, const wstring& wstrStateKey = L"", const int & iIndex = 0);
	void Release_Texture_Manager();

private:
	void Insert_Texture_Obstacle();
private:
	static CTexture_Manager* m_pInstance;

	map<wstring, CTexture*> m_mapTexture;
};

