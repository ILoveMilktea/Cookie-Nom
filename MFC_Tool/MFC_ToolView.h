
// MFC_ToolView.h : CMFC_ToolView Ŭ������ �������̽�
//

#pragma once

// === Ŭ������ -> alt+enter �Ӽ�â -> �޼����� ��ӹ޴� �Լ� ������ ���� ������ �� ����
class CTerrain;
class CMFC_ToolView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMFC_ToolView();
	DECLARE_DYNCREATE(CMFC_ToolView)

// Ư���Դϴ�.
public:
	CMFC_ToolDoc* GetDocument() const;

	int m_iR = 0;
	int m_iSpeed;
	float m_fAngle = 0.f;

	CTerrain* m_pTerrain;

// �۾��Դϴ�.
public:
	//CSingle_Texture* m_pSingle_Texture;

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMFC_ToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MFC_ToolView.cpp�� ����� ����
inline CMFC_ToolDoc* CMFC_ToolView::GetDocument() const
   { return reinterpret_cast<CMFC_ToolDoc*>(m_pDocument); }
#endif

