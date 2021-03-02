// Incidencias2.h : main header file for the INCIDENCIAS2 application
//

#if !defined(AFX_INCIDENCIAS2_H__215E0D17_3658_43C3_91EE_E631FE5A163E__INCLUDED_)
#define AFX_INCIDENCIAS2_H__215E0D17_3658_43C3_91EE_E631FE5A163E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CIncidencias2App:
// See Incidencias2.cpp for the implementation of this class
//

class CIncidencias2App : public CWinApp
{
public:
	CIncidencias2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIncidencias2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CIncidencias2App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INCIDENCIAS2_H__215E0D17_3658_43C3_91EE_E631FE5A163E__INCLUDED_)
