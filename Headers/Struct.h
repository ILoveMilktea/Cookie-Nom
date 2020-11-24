#pragma once

typedef struct tagInfo
{
	tagInfo() {
		ZeroMemory(this, sizeof(tagInfo));
	}

	D3DXVECTOR3		vPos;		// ���� ��ġ
	D3DXVECTOR3		vSize;		// ũ��
	D3DXVECTOR3		vDir;		// ���ư����� ����
	D3DXVECTOR3		vLook; // - �ܼ� ����
	D3DXMATRIX		matWorld;
}INFO;

typedef struct tagTexInfo
{
	LPDIRECT3DTEXTURE9 pTexture;	//HBITMAP�� ������ ����, �׸� �� ���� �����ϱ� ���� �İ�ü
	D3DXIMAGE_INFO tImageInfo;		// �̹����� ������ ���Ͽ� �о�� ������ ����ü
}TEXINFO;


typedef struct tagTile
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vSize;
	BYTE			byDrawID;
	BYTE			byOption;
}TILE;

typedef struct tagLinePos
{
	float fX;
	float fY;
}LINEPOS;

typedef struct tagLineInfo
{
	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOS _tLeftPos, LINEPOS _tRightPos)
		: tLeftPos(_tLeftPos), tRightPos(_tRightPos) {}
	LINEPOS tLeftPos;
	LINEPOS tRightPos;
}LINEINFO;

