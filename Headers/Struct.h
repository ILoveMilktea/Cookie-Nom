#pragma once

typedef struct tagInfo
{
	tagInfo() {
		ZeroMemory(this, sizeof(tagInfo));
	}

	D3DXVECTOR3		vPos;		// 현재 위치
	D3DXVECTOR3		vSize;		// 크기
	D3DXVECTOR3		vDir;		// 나아가려는 방향
	D3DXVECTOR3		vLook; // - 단순 기준
	D3DXMATRIX		matWorld;
}INFO;

typedef struct tagTexInfo
{
	LPDIRECT3DTEXTURE9 pTexture;	//HBITMAP과 동일한 역할, 그림 한 장을 제어하기 위한 컴객체
	D3DXIMAGE_INFO tImageInfo;		// 이미지의 정보를 파일에 읽어와 보관할 구조체
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

