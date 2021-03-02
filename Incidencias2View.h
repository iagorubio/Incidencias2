/*
Copyright 2006, Yago Rubio Sanfiz

Copying and distribution of this file, with or without modification,
are permited in any medium without royalty, provided the copyright
and this notice are preserved.This file is offered as - is without
any warranty.
*/

// Incidencias2View.h : interface of the CIncidencias2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INCIDENCIAS2VIEW_H__4798F5DE_A288_4200_A401_8AB267D17590__INCLUDED_)
#define AFX_INCIDENCIAS2VIEW_H__4798F5DE_A288_4200_A401_8AB267D17590__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIncidencias2Set;

class CIncidencias2View : public CDaoRecordView
{
protected: // create from serialization only
	CIncidencias2View();
	DECLARE_DYNCREATE(CIncidencias2View)

	void UpdateOperationsComboFromDb(void);
	void UpdateSuppliersComboFromDb(void);
	void UpdateOperariosComboFromDb(void);
	void SetSupplierOnCombo(UINT sid);
	void SetOperationOnCombo(UINT opid);
	void SetOperarioOnCombo(UINT opid);
	void UpdateAll();

	HBITMAP m_bp;
public:
	//{{AFX_DATA(CIncidencias2View)
	enum { IDD = IDD_INCIDENCIAS2_FORM };
	CStatic	m_pBitmap;
	CComboBox	m_ComboOperario;
	CEdit	m_EditDbDateStart;
	CEdit	m_EditDbDateEnd;
	CEdit	m_EditDbSubjectCtrl;
	CEdit	m_EditDbDesctCtrl;
	CButton	m_CheckFinishedCtrl;
	CButton	m_ButtonIncidenciasFormSave;
	CComboBox	m_ComboProveedor;
	CComboBox	m_ComboOperacion;
	CIncidencias2Set* m_pSet;
	//}}AFX_DATA

// Attributes
public:
	CIncidencias2Doc* GetDocument();
	void SetEditing(BOOL editing = true);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIncidencias2View)
	public:
	virtual CDaoRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIncidencias2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CIncidencias2View)
	afx_msg void OnButtonCalmonth();
	afx_msg void OnSelchangeComboProveedor();
	afx_msg void OnChangeEditDbDesc();
	afx_msg void OnChangeEditDbdateEnd();
	afx_msg void OnChangeEditDbdateStart();
	afx_msg void OnChangeEditDbid();
	afx_msg void OnChangeEditDbsubject();
	afx_msg void OnButtonSaveIncidenciaCliked();
	afx_msg void OnCheckFinishedClicked();
	afx_msg void OnButtonCalmonth2();
	afx_msg void OnSelchangeComboOperacion();
	afx_msg void OnSelchangeComboOperario();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Incidencias2View.cpp
inline CIncidencias2Doc* CIncidencias2View::GetDocument()
   { return (CIncidencias2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INCIDENCIAS2VIEW_H__4798F5DE_A288_4200_A401_8AB267D17590__INCLUDED_)
