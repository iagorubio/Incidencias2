/*
Copyright 2006, Yago Rubio Sanfiz

Copying and distribution of this file, with or without modification,
are permited in any medium without royalty, provided the copyright
and this notice are preserved.This file is offered as - is without
any warranty.
*/

// ProveedoresSet.cpp : implementation file
//

#include "stdafx.h"
#include "ProveedoresSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProveedoresSet

IMPLEMENT_DYNAMIC(CProveedoresSet, CDaoRecordset)

CProveedoresSet::CProveedoresSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CProveedoresSet)
	m_pid = 0;
	m_pnom = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}

CString CProveedoresSet::GetDefaultDBName()
{
	return _T("bd1.mdb");
}

CString CProveedoresSet::GetDefaultSQL()
{
	return _T("[proveedores]");
}

bool CProveedoresSet::QueryProveedor (UINT pid)
{
	CString strSQL;

	strSQL.Format("SELECT * FROM %s WHERE [pid]=%i",
					GetDefaultSQL().GetBuffer(0),
					pid);

	if( IsOpen() ) Close();
	Open(m_nDefaultType, strSQL.GetBuffer(0));
	if( !IsOpen() ) return false;

	if( GetRecordCount() > 0 ) return true;

	return false;
}

bool CProveedoresSet::QueryAllProveedores(void)
{
	CString strSQL;

	strSQL.Format("SELECT * FROM %s",
					GetDefaultSQL().GetBuffer(0) );

	if( IsOpen() ) Close();
	Open(m_nDefaultType, strSQL.GetBuffer(0));
	if( !IsOpen() ) return false;

	if( GetRecordCount() > 0 ) return true;

	return false;
}

void CProveedoresSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CProveedoresSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[pid]"), m_pid);
	DFX_Text(pFX, _T("[pnom]"), m_pnom);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CProveedoresSet diagnostics

#ifdef _DEBUG
void CProveedoresSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CProveedoresSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
