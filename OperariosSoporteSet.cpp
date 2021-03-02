// OperariosSoporteSet.cpp : implementation file
//

#include "stdafx.h"
#include "OperariosSoporteSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COperariosSoporteSet

IMPLEMENT_DYNAMIC(COperariosSoporteSet, CDaoRecordset)

COperariosSoporteSet::COperariosSoporteSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(COperariosSoporteSet)
	m_opsid = 0;
	m_opnom = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString COperariosSoporteSet::GetDefaultDBName()
{
	return _T("bd1.mdb");
}

CString COperariosSoporteSet::GetDefaultSQL()
{
	return _T("[operarios_soporte]");
}

bool COperariosSoporteSet::QueryOperarioSoporte(UINT oper)
{
	CString strSQL;

	strSQL.Format("SELECT * FROM %s WHERE [opsid]=%i",
					GetDefaultSQL().GetBuffer(0),
					oper);

	if( IsOpen() ) Close();
	Open(m_nDefaultType, strSQL.GetBuffer(0));
	if( !IsOpen() ) return false;

	if( GetRecordCount() > 0 ) return true;
	return false;
}

bool COperariosSoporteSet::QueryAllOperariosSoporte(void)
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


void COperariosSoporteSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(COperariosSoporteSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[opsid]"), m_opsid);
	DFX_Text(pFX, _T("[opnom]"), m_opnom);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// COperariosSoporteSet diagnostics

#ifdef _DEBUG
void COperariosSoporteSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void COperariosSoporteSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
