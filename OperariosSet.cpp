/*
Copyright 2006, Yago Rubio Sanfiz

Copying and distribution of this file, with or without modification,
are permited in any medium without royalty, provided the copyright
and this notice are preserved.This file is offered as - is without
any warranty.
*/

// OperariosSet.cpp : implementation file
//

#include "stdafx.h"
#include "OperariosSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COperariosSet

IMPLEMENT_DYNAMIC(COperariosSet, CDaoRecordset)

COperariosSet::COperariosSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(COperariosSet)
	m_opid = 0;
	m_opnom = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString COperariosSet::GetDefaultDBName()
{
	return _T("bd1.mdb");
}

CString COperariosSet::GetDefaultSQL()
{
	return _T("[operarios]");
}

bool COperariosSet::QueryOperario(UINT oper)
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

bool COperariosSet::QueryAllOperarios(void)
{
	CString strSQL;

	strSQL.Format("SELECT * FROM %s",
					GetDefaultSQL().GetBuffer(0) );

	if( IsOpen() ) Close();
	Open(m_nDefaultType, strSQL.GetBuffer(0));
	if( !IsOpen() ) return false;

	if( GetRecordCount() > 0 ) return true;

	Close();
	return false;
}

void COperariosSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(COperariosSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[opid]"), m_opid);
	DFX_Text(pFX, _T("[opnom]"), m_opnom);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// COperariosSet diagnostics

#ifdef _DEBUG
void COperariosSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void COperariosSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
