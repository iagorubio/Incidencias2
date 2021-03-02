#if !defined(AFX_ONEFIELDDBDIALOG_H__A1F3DFD1_E195_48C0_B40A_C5917D3C83C8__INCLUDED_)
#define AFX_ONEFIELDDBDIALOG_H__A1F3DFD1_E195_48C0_B40A_C5917D3C83C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OneFieldDbDialog.h : header file
//


typedef enum {
	OFBD_DLG_TYPE_OPERARIOS,
	OFBD_DLG_TYPE_OPERARIOS_SOPORTE,
	OFBD_DLG_TYPE_OPERACIONES,
	OFB_DLG_TYPE_PROVEEDORES
} OfDbDialogType;
/////////////////////////////////////////////////////////////////////////////
// COneFieldDbDialog dialog

class COneFieldDbDialog : public CDialog
{
// Construction
public:
	COneFieldDbDialog(OfDbDialogType type, CDaoRecordset *pSet, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COneFieldDbDialog)
	enum { IDD = IDD_ONEFIELD_DB_EDIT };
	CListCtrl	m_OFDbList;
	CEdit	m_OFDbNameEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COneFieldDbDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	COperariosSet *m_pOpSet;
	COperariosSoporteSet *m_pOpSopSet;
	CProveedoresSet *m_pProSet;
	COperacionesSet *m_OperSet;

	CDaoRecordset *m_pSet; //pointer to the current recordset

	OfDbDialogType m_Type;
	// Generated message map functions
	//{{AFX_MSG(COneFieldDbDialog)
	afx_msg void OnOfdlgDeleteBtn();
	afx_msg void OnItemchangedOfdlgListDbItems(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOfdlgAddBtn();
	afx_msg void OnOfdlgSaveBtn();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	void SetDataSet( CDaoRecordset *pSet );
	void UpdateListFromOperacionesData(void);
	void UpdateListFromOperariosData(void);
	void UpdateListFromOperariosSoporteData(void);
	void UpdateListFromProveedoresData(void);
	void UpdateListFromDb(void);
	void UpdateOtherViewsControls(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONEFIELDDBDIALOG_H__A1F3DFD1_E195_48C0_B40A_C5917D3C83C8__INCLUDED_)
