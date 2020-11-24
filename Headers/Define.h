#pragma once

#define WINCX 800
#define WINCY 600

#define TILECX	130
#define TILECY	68
#define TILEX	20
#define TILEY	30

#define Vec3 D3DXVECTOR3

#ifdef _AFX
#define ERR_MSG(msg) AfxMessageBox(msg)
#else
#define ERR_MSG(msg) MessageBox(nullptr, msg, L"System_Error", MB_OK)
#endif // _AFX



#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

#define OBJ_NOEVENT 0
#define OBJ_DEAD 1

#define PI 3.141592f

#define VK_MAX	0xFF