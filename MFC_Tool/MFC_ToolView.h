
// MFC_ToolView.h : CMFC_ToolView 클래스의 인터페이스
//

#pragma once

// === 클래스뷰 -> alt+enter 속성창 -> 메세지나 상속받는 함수 재정의 설정 가능할 수 있음
class CTerrain;
class CMFC_ToolView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFC_ToolView();
	DECLARE_DYNCREATE(CMFC_ToolView)

// 특성입니다.
public:
	CMFC_ToolDoc* GetDocument() const;

	int m_iR = 0;
	int m_iSpeed;
	float m_fAngle = 0.f;

	CTerrain* m_pTerrain;

// 작업입니다.
public:
	//CSingle_Texture* m_pSingle_Texture;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFC_ToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MFC_ToolView.cpp의 디버그 버전
inline CMFC_ToolDoc* CMFC_ToolView::GetDocument() const
   { return reinterpret_cast<CMFC_ToolDoc*>(m_pDocument); }
#endif

