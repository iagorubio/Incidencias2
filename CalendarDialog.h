#if !defined(AFX_CALENDARDIALOG_H__900AD9D2_4F38_4291_89B3_9E7181F4C4E3__INCLUDED_)
#define AFX_CALENDARDIALOG_H__900AD9D2_4F38_4291_89B3_9E7181F4C4E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalendarDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalendarDialog dialog
enum { // close type
	CDLG_CAL_CLOSE_OK,
	CDLG_CAL_CLOSE_CANCEL
};

class CCalendarDialog : public CDialog
{
// Construction
public:
	CCalendarDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCalendarDialog)
	enum { IDD = IDD_CALENDAR_DIALOG };
	CMonthCalCtrl	m_pCalendarCtrl;
	CTime	m_pMonthCalendarTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarDialog)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalendarDialog)
	afx_msg void OnSelchangeMonthcalendar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCaldlgButtonOk();
	afx_msg void OnCaldlgButtonCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARDIALOG_H__900AD9D2_4F38_4291_89B3_9E7181F4C4E3__INCLUDED_)
