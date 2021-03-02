#if !defined(AFX_PROVEEDORESSET_H__3730113F_D769_4F52_BDF4_4F664C82AFBD__INCLUDED_)
#define AFX_PROVEEDORESSET_H__3730113F_D769_4F52_BDF4_4F664C82AFBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProveedoresSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProveedoresSet DAO recordset

class CProveedoresSet : public CDaoRecordset
{
public:
	CProveedoresSet(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CProveedoresSet)

	bool QueryProveedor (UINT pid);
	bool QueryAllProveedores(void);
// Field/Param Data
	//{{AFX_FIELD(CProveedoresSet, CDaoRecordset)
	long	m_pid;
	CString	m_pnom;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProveedoresSet)
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

#endif // !defined(AFX_PROVEEDORESSET_H__3730113F_D769_4F52_BDF4_4F664C82AFBD__INCLUDED_)
