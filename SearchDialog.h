/*
Copyright 2006, Yago Rubio Sanfiz

Copying and distribution of this file, with or without modification,
are permited in any medium without royalty, provided the copyright
and this notice are preserved.This file is offered as - is without
any warranty.
*/

#if !defined(AFX_SEARCHDIALOG_H__E064AF45_9D6A_4DEB_9E05_4A87FB0DD432__INCLUDED_)
#define AFX_SEARCHDIALOG_H__E064AF45_9D6A_4DEB_9E05_4A87FB0DD432__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchDialog dialog

class CSearchDialog : public CDialog
{
// Construction
public:
	CSearchDialog(CWnd* pParent = NULL);   // standard constructor


// Dialog Dataro
	//{{AFX_DATA(CSearchDialog)
	enum { IDD = IDD_SEARCH_DLG };
	CEdit	m_pEditSearchTerm;
	CComboBox	m_pTableCombo;
	CComboBox	m_pOperatorCombo;
	CComboBox	m_pFieldCombo;
	CListCtrl	m_pResultsListCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDaoDatabase* m_pDB;
	CDaoRecordset* m_pSet;

	int m_nTable;
	int m_nField;

	// Generated message map functions
	//{{AFX_MSG(CSearchDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSearchDlgBuscar();
	afx_msg void OnSelchangeSearchDlgComboTable();
	afx_msg void OnDblclkListSearchDlgResults(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHDIALOG_H__E064AF45_9D6A_4DEB_9E05_4A87FB0DD432__INCLUDED_)
