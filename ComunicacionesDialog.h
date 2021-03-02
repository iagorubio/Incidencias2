#if !defined(AFX_COMUNICACIONESDIALOG_H__278269F4_10A8_4EEE_A5CD_7EFCB3AF76F4__INCLUDED_)
#define AFX_COMUNICACIONESDIALOG_H__278269F4_10A8_4EEE_A5CD_7EFCB3AF76F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComunicacionesDialog.h : header file
//


typedef enum {
	COM_DLG_TYPE_NEW,
	COM_DLG_TYPE_EDIT
} ComDlgType;

/////////////////////////////////////////////////////////////////////////////
// CComunicacionesDialog dialog

class CComunicacionesDialog : public CDialog
{
// Construction
public:
	CComunicacionesDialog(CWnd* pParent = NULL, ComDlgType type = COM_DLG_TYPE_NEW, int inId = 0);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CComunicacionesDialog)
	enum { IDD = IDD_DIALOG_COMUNICACION };
	CButton	m_CheckOrigenAquiCtrl;
	CEdit	m_EditFechaComuCtrl;
	CEdit	m_EditFechaRespCtrl;
	CEdit	m_EditDescRespCtrl;
	CEdit	m_EditDescComuCtrl;
	CComboBox	m_ComboOperariosSoporteCtrl;
	CComboBox	m_ComboOperariosCtrl;
	CComboBox	m_ComboIncidenciasCtrl;
	CButton	m_CheckContestadoCtrl;
	CWnd* m_pParent;
	//}}AFX_DATA
	
	int m_comID;
	ComDlgType m_uType;

	void SetIncidenciaId(int recordid);
	void SetDialogType(ComDlgType type);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComunicacionesDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CComunicacionesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonFechaInicioCliked();
	afx_msg void OnButtonFechaContestacionClicked();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMUNICACIONESDIALOG_H__278269F4_10A8_4EEE_A5CD_7EFCB3AF76F4__INCLUDED_)
