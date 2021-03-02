/*
Copyright 2006, Yago Rubio Sanfiz

Copying and distribution of this file, with or without modification,
are permited in any medium without royalty, provided the copyright
and this notice are preserved.This file is offered as - is without
any warranty.
*/

// OperacionesSet.cpp : implementation file
//

#include "stdafx.h"
#include "OperacionesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COperacionesSet

IMPLEMENT_DYNAMIC(COperacionesSet, CDaoRecordset)

COperacionesSet::COperacionesSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(COperacionesSet)
	m_opid = 0;
	m_opnom = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString COperacionesSet::GetDefaultDBName()
{
	return _T("bd1.mdb");
}

CString COperacionesSet::GetDefaultSQL()
{
	return _T("[operaciones]");
}

bool COperacionesSet::QueryOperacion(UINT oper)
{
	CString strSQL;

	strSQL.Format("SELECT * FROM %s WHERE [opid]=%i",
					GetDefaultSQL().GetBuffer(0),
					oper);

	if( IsOpen() ) Close();
	Open(m_nDefaultType, strSQL.GetBuffer(0));
	if( !IsOpen() ) return false;

	if( GetRecordCount() > 0 ) return true;

	return false;
}

bool COperacionesSet::QueryAllOperaciones(void)
{
	CString strSQL;

	strSQL.Format("SELECT * FROM %s",
					GetDefaultSQL().GetBuffer(0));

	if( IsOpen() ) Close();
	Open(m_nDefaultType, strSQL.GetBuffer(0));
	if( !IsOpen() ) return false;

	if( GetRecordCount() > 0 ) return true;

	return false;
}

void COperacionesSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(COperacionesSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[opid]"), m_opid);
	DFX_Text(pFX, _T("[opnom]"), m_opnom);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// COperacionesSet diagnostics

#ifdef _DEBUG
void COperacionesSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void COperacionesSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
