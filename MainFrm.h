/*
Copyright 2006, Yago Rubio Sanfiz

Copying and distribution of this file, with or without modification,
are permited in any medium without royalty, provided the copyright
and this notice are preserved.This file is offered as - is without
any warranty.
*/

// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__FA39D43C_EB75_46F3_9063_2469EF4AD36B__INCLUDED_)
#define AFX_MAINFRM_H__FA39D43C_EB75_46F3_9063_2469EF4AD36B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum {
	OFD_OPERARIOS_TYPE,
	OFD_OPERARIOS_SOPORTE_TYPE,
	OFD_PROVEEDORES_TYPE,
	OFD_OPERACIONES_TYPE,
	OFD_NUM_DLGS
}OneFieldDlgType;

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)


// Attributes
protected:

public:
	CSplitterWnd m_wndSplitter;
	CSplitterWnd m_wndSplitterInc;

	CDialog* m_ofdDialogs[OFD_NUM_DLGS];

// Operations
public:
	virtual CIncidencias2View* GetIncidenciasFormView();
	virtual CIncidenciasListView* GetIncidenciasListView();
	virtual CComunicacionesView* GetComunicacionesListView();
	virtual void AddBlankIncidencia();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDbAddIncidencia();
	afx_msg void OnDbOperaciones();
	afx_msg void OnDbOperarios();
	afx_msg void OnDbOperariosSoporte();
	afx_msg void OnDbProveedores();
	afx_msg void OnReportIncidencia();
	afx_msg void OnKbSelectComListView();
	afx_msg void OnKbSelectIncFormView();
	afx_msg void OnKbSelectIncListView();
	afx_msg void OnCmdRecordLast();
	afx_msg void OnCmdRecordNext();
	afx_msg void OnCmdRecordPrevious();
	afx_msg void OnCmdRecordFirst();
	afx_msg void OnCmdSearchDlg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__FA39D43C_EB75_46F3_9063_2469EF4AD36B__INCLUDED_)
