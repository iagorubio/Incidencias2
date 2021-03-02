#if !defined(AFX_COMUNICACIONESSET_H__431EFC41_6057_4E13_862A_31B49B2F4164__INCLUDED_)
#define AFX_COMUNICACIONESSET_H__431EFC41_6057_4E13_862A_31B49B2F4164__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComunicacionesSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComunicacionesSet DAO recordset

class CComunicacionesSet : public CDaoRecordset
{
public:
	CComunicacionesSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CComunicacionesSet)

	bool QueryComunicacion(UINT comu);
	bool QueryComunicacionesDeIncidente(UINT incidente);
	bool QueryAllComunicaciones(void);
	bool QueryComunicacionesPorIndice(LPSTR iname, UINT in);
	bool QueryComunicacionesDelOperario(UINT opid);
	bool QueryComunicacionesDelOperarioSoporte(UINT opsid);

// Field/Param Data
	//{{AFX_FIELD(CComunicacionesSet, CDaoRecordset)
	long	m_coid;
	long	m_inid;
	long	m_opid;
	long	m_opsid;
	BOOL	m_cont;
	CString	m_codesc;
	CString	m_resdesc;
	COleDateTime	m_cofec;
	COleDateTime	m_cofecresp;
	BOOL	m_orig;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComunicacionesSet)
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

#endif // !defined(AFX_COMUNICACIONESET_H__431EFC41_6057_4E13_862A_31B49B2F4164__INCLUDED_)
