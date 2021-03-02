/*
Copyright 2006, Yago Rubio Sanfiz

Copying and distribution of this file, with or without modification,
are permited in any medium without royalty, provided the copyright
and this notice are preserved.This file is offered as - is without
any warranty.
*/

#if !defined(AFX_OPERACIONESSET_H__2A657425_DDD2_4343_9051_25B943F6256E__INCLUDED_)
#define AFX_OPERACIONESSET_H__2A657425_DDD2_4343_9051_25B943F6256E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OperacionesSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COperacionesSet DAO recordset

class COperacionesSet : public CDaoRecordset
{
public:
	COperacionesSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(COperacionesSet)

	bool QueryOperacion(UINT oper);
	bool QueryAllOperaciones(void);
// Field/Param Data
	//{{AFX_FIELD(COperacionesSet, CDaoRecordset)
	long	m_opid;
	CString	m_opnom;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COperacionesSet)
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

#endif // !defined(AFX_OPERACIONESSET_H__2A657425_DDD2_4343_9051_25B943F6256E__INCLUDED_)
