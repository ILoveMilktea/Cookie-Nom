
// MFC_Tool.h : MFC_Tool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFC_ToolApp:
// �� Ŭ������ ������ ���ؼ��� MFC_Tool.cpp�� �����Ͻʽÿ�.
//

class CMFC_ToolApp : public CWinApp
{
public:
	CMFC_ToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFC_ToolApp theApp;
