#pragma once

class CTerrain
{
public:
	CTerrain();
	~CTerrain();

public:
	void TileChange(const D3DXVECTOR3& vMousePos, const BYTE& byDrawID, const BYTE& byOption = 0);

public:
	HRESULT	Ready_Terrain();
	void	Render_Terrain();
	void	Release_Terrain();

private:
	vector<TILE*> m_vecTile;
};

