// CalendarDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Incidencias2.h"
#include "CalendarDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalendarDialog dialog


CCalendarDialog::CCalendarDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCalendarDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalendarDialog)
	m_pMonthCalendarTime = 0;
	//}}AFX_DATA_INIT
}


void CCalendarDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalendarDialog)
	DDX_Control(pDX, IDC_MONTHCALENDAR, m_pCalendarCtrl);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR, m_pMonthCalendarTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalendarDialog, CDialog)
	//{{AFX_MSG_MAP(CCalendarDialog)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR, OnSelchangeMonthcalendar)
	ON_BN_CLICKED(IDC_CALDLG_BUTTON_OK, OnCaldlgButtonOk)
	ON_BN_CLICKED(IDC_CALDLGBOTTON_CANCEL, OnCaldlgButtonCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarDialog message handlers

void CCalendarDialog::OnSelchangeMonthcalendar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	this->UpdateData(TRUE);

	*pResult = 0;
}

void CCalendarDialog::OnCaldlgButtonOk() 
{
	// TODO: Add your control notification handler code here
	this->EndDialog(CDLG_CAL_CLOSE_OK);
}

void CCalendarDialog::OnCaldlgButtonCancel() 
{
	// TODO: Add your control notification handler code here
	this->EndDialog(CDLG_CAL_CLOSE_CANCEL);	
}

int CCalendarDialog::DoModal() 
{

	return CDialog::DoModal();
}

BOOL CCalendarDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SYSTEMTIME t;

	::GetLocalTime(&t);

	this->m_pCalendarCtrl.SetCurSel(&t); 
	this->m_pCalendarCtrl.SetToday(&t);

	this->m_pCalendarCtrl.SetColor(MCSC_BACKGROUND, ::GetSysColor(COLOR_MENU) );
	this->m_pCalendarCtrl.SetColor(MCSC_MONTHBK, ::GetSysColor(COLOR_MENU) );
	this->m_pCalendarCtrl.SetColor(MCSC_TITLEBK,::GetSysColor(COLOR_ACTIVECAPTION));

	this->UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
              // EXCEPTION: OCX Property Pages should return FALSE
}
