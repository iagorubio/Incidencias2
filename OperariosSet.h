/*
Copyright 2006, Yago Rubio Sanfiz

Copying and distribution of this file, with or without modification,
are permited in any medium without royalty, provided the copyright
and this notice are preserved.This file is offered as - is without
any warranty.
*/

#if !defined(AFX_OPERARIOSSET_H__808E850D_9E85_47F4_949C_C30568947C9D__INCLUDED_)
#define AFX_OPERARIOSSET_H__808E850D_9E85_47F4_949C_C30568947C9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OperariosSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COperariosSet DAO recordset

class COperariosSet : public CDaoRecordset
{
public:
	COperariosSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(COperariosSet)

	bool QueryOperario(UINT oper);
	bool QueryAllOperarios(void);
// Field/Param Data
	//{{AFX_FIELD(COperariosSet, CDaoRecordset)
	long	m_opid;
	CString	m_opnom;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COperariosSet)
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

#endif // !defined(AFX_OPERARIOSSET_H__808E850D_9E85_47F4_949C_C30568947C9D__INCLUDED_)
