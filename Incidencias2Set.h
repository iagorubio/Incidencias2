/*
Copyright 2006, Yago Rubio Sanfiz

Copying and distribution of this file, with or without modification,
are permited in any medium without royalty, provided the copyright
and this notice are preserved.This file is offered as - is without
any warranty.
*/
// Incidencias2Set.h : interface of the CIncidencias2Set class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INCIDENCIAS2SET_H__410387A8_C3C0_4A3A_8EB7_125CE3A9E157__INCLUDED_)
#define AFX_INCIDENCIAS2SET_H__410387A8_C3C0_4A3A_8EB7_125CE3A9E157__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIncidencias2Set : public CDaoRecordset
{
public:
	CIncidencias2Set(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CIncidencias2Set)

	bool QueryIncidencia(UINT in);
	bool QueryAllIncidencias(void);
	bool QueryIncidenciasPorIndice( LPSTR iname, UINT in);
	bool QueryIncidenciasDelOperario(UINT opid);
	bool QueryIncidenciasDelOperarioSoporte(UINT opsid);
	bool QueryIncidenciasDelProveedor(UINT pid);
	bool QueryIncidenciasPorOperacion(UINT opsid);
// Field/Param Data
	//{{AFX_FIELD(CIncidencias2Set, CDaoRecordset)
	long	m_inid;
	CString	m_innom;
	CString	m_indesc;
	long	m_pid;
	BOOL	m_res;
	long	m_opid;
	long	m_opsid;
	COleDateTime	m_ifecini;
	COleDateTime	m_ifecres;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIncidencias2Set)
	public:
	virtual CString GetDefaultDBName();		// REVIEW:  Get a comment here
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);	// RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INCIDENCIAS2SET_H__410387A8_C3C0_4A3A_8EB7_125CE3A9E157__INCLUDED_)

