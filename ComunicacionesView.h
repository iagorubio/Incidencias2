#if !defined(AFX_COMUNICACIONESVIEW_H__4A1566DD_A900_4B67_8125_3CF43C6B841B__INCLUDED_)
#define AFX_COMUNICACIONESVIEW_H__4A1566DD_A900_4B67_8125_3CF43C6B841B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComunicacionesView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComunicacionesView view
#include <afxcview.h>


#include "ComunicacionesSet.h"

class CComunicacionesView : public CListView
{
protected:
	CComunicacionesView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CComunicacionesView)

	void UpdateViewForIncident (UINT incident);
// Attributes
public:
	//CComunicacionesSet m_pSet;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComunicacionesView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CComunicacionesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CComunicacionesView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnComViewDbDeleteActiveReg();
	afx_msg void OnReturn(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMUNICACIONESVIEW_H__4A1566DD_A900_4B67_8125_3CF43C6B841B__INCLUDED_)
