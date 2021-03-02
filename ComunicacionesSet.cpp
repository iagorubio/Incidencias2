// ComunicacionesSet.cpp : implementation file
//

#include "stdafx.h"
#include "ComunicacionesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComunicacionesSet

IMPLEMENT_DYNAMIC(CComunicacionesSet, CDaoRecordset)

CComunicacionesSet::CComunicacionesSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CComunicacionesSet)
	m_coid = 0;
	m_inid = 0;
	m_opid = 0;
	m_opsid = 0;
	m_cont = FALSE;
	m_codesc = _T("");
	m_resdesc = _T("");
	m_cofec = (DATE)0;
	m_cofecresp = (DATE)0;
	m_orig = FALSE;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CComunicacionesSet::GetDefaultDBName()
{
	return _T("bd1.mdb");
}

CString CComunicacionesSet::GetDefaultSQL()
{
	return _T("[comunicaciones]");
}

bool CComunicacionesSet::QueryComunicacionesPorIndice( LPSTR iname, UINT in)
{
	CString strSQL;

	strSQL.Format("SELECT * FROM %s WHERE [%s]=%i",
					GetDefaultSQL().GetBuffer(0),
					iname,
					in);

	if( IsOpen() ) Close();
	Open(this->m_nDefaultType, strSQL.GetBuffer(0));
	if( !IsOpen() ) return false;

	if( GetRecordCount() > 0 ) return true;

	return false;
}

bool CComunicacionesSet::QueryComunicacion(UINT coid)
{
	return QueryComunicacionesPorIndice("coid", coid);
}

bool CComunicacionesSet::QueryComunicacionesDelOperario(UINT opid)
{
	return QueryComunicacionesPorIndice("opid", opid);
}

bool CComunicacionesSet::QueryComunicacionesDelOperarioSoporte(UINT opsid)
{
	return QueryComunicacionesPorIndice("opsid", opsid);
}

bool CComunicacionesSet::QueryComunicacionesDeIncidente(UINT incidente)
{
	return QueryComunicacionesPorIndice("inid", incidente);
}

bool CComunicacionesSet::QueryAllComunicaciones(void)
{
	CString strSQL;

	strSQL.Format("SELECT * FROM %s",
					GetDefaultSQL().GetBuffer(0) );

	if( IsOpen() ) Close();
	Open(m_nDefaultType, strSQL.GetBuffer(0));
	if( !IsOpen() ) return false;

	if( GetRecordCount() > 0 ) return true;

	//Close();
	return false;
}

void CComunicacionesSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CComunicacionesSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[coid]"), m_coid);
	DFX_Long(pFX, _T("[inid]"), m_inid);
	DFX_Long(pFX, _T("[opid]"), m_opid);
	DFX_Long(pFX, _T("[opsid]"), m_opsid);
	DFX_Bool(pFX, _T("[cont]"), m_cont);
	DFX_Text(pFX, _T("[codesc]"), m_codesc);
	DFX_Text(pFX, _T("[resdesc]"), m_resdesc);
	DFX_DateTime(pFX, _T("[cofec]"), m_cofec);
	DFX_DateTime(pFX, _T("[cofecresp]"), m_cofecresp);
	DFX_Bool(pFX, _T("[coorig]"), m_orig);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CComunicacionesSet diagnostics

#ifdef _DEBUG
void CComunicacionesSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CComunicacionesSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
