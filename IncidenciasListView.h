#if !defined(AFX_INCIDENCIASLISTVIEW_H__8FB9E2E2_1393_4667_8341_1A349EE48738__INCLUDED_)
#define AFX_INCIDENCIASLISTVIEW_H__8FB9E2E2_1393_4667_8341_1A349EE48738__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IncidenciasListView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIncidenciasListView view
#include <afxcview.h>

class CIncidenciasListView : public CListView
{
protected:
	CIncidenciasListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CIncidenciasListView)


// Attributes
public:
	int m_lastInID;
// Operations
public:
	void UpdateView(void);
	void SelectIncidentBySzid(char *szid);
	void SelectIncidentById(int id);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIncidenciasListView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
// Implementation
protected:
	virtual ~CIncidenciasListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CIncidenciasListView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDbNewComunicacion();
	afx_msg void OnIListViewDbDeleteActiveReg();
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReturn(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INCIDENCIASLISTVIEW_H__8FB9E2E2_1393_4667_8341_1A349EE48738__INCLUDED_)
