/*
Copyright 2006, Yago Rubio Sanfiz

Copying and distribution of this file, with or without modification,
are permited in any medium without royalty, provided the copyright
and this notice are preserved.This file is offered as - is without
any warranty.
*/

#if !defined(AFX_OPERARIOSSOPORTESET_H__95B7D221_0C3A_4C2A_A167_F001EC558E35__INCLUDED_)
#define AFX_OPERARIOSSOPORTESET_H__95B7D221_0C3A_4C2A_A167_F001EC558E35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OperariosSoporteSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COperariosSoporteSet DAO recordset

class COperariosSoporteSet : public CDaoRecordset
{
public:
	COperariosSoporteSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(COperariosSoporteSet)

	bool QueryOperarioSoporte(UINT oper);
	bool QueryAllOperariosSoporte(void);
// Field/Param Data
	//{{AFX_FIELD(COperariosSoporteSet, CDaoRecordset)
	long	m_opsid;
	CString	m_opnom;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COperariosSoporteSet)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPERARIOSSOPORTESET_H__95B7D221_0C3A_4C2A_A167_F001EC558E35__INCLUDED_)
