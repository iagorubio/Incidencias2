/*
Copyright 2006, Yago Rubio Sanfiz

Copying and distribution of this file, with or without modification,
are permited in any medium without royalty, provided the copyright
and this notice are preserved.This file is offered as - is without
any warranty.
*/

// Incidencias2Set.cpp : implementation of the CIncidencias2Set class
//

#include "stdafx.h"

#include "Incidencias2.h"

#include "Incidencias2Set.h"
#include "ComunicacionesSet.h"
#include "OperariosSet.h"
#include "OperacionesSet.h"
#include "OperariosSoporteSet.h"
#include "ProveedoresSet.h"

#include "Incidencias2Doc.h"

#include "Incidencias2View.h"
#include "ComunicacionesView.h"
#include "IncidenciasListView.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIncidencias2Set implementation

IMPLEMENT_DYNAMIC(CIncidencias2Set, CDaoRecordset)

CIncidencias2Set::CIncidencias2Set(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CIncidencias2Set)
	m_inid = 0;
	m_innom = _T("");
	m_indesc = _T("");
	m_pid = 0;
	m_res = FALSE;
	m_opid = 0;
	m_opsid = 0;
	m_ifecini = (DATE)0;
	m_ifecres = (DATE)0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}

CString CIncidencias2Set::GetDefaultDBName()
{
	return _T("bd1.mdb");
}


CString CIncidencias2Set::GetDefaultSQL()
{
	return _T("[incidencias]");
}


bool CIncidencias2Set::QueryIncidenciasPorIndice( LPSTR iname, UINT in)
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

bool CIncidencias2Set::QueryIncidencia(UINT inid)
{
	return QueryIncidenciasPorIndice("inid", inid);
}

bool CIncidencias2Set::QueryIncidenciasDelOperario(UINT opid)
{
	return QueryIncidenciasPorIndice("opid", opid);
}

bool CIncidencias2Set::QueryIncidenciasDelOperarioSoporte(UINT opsid)
{
	return QueryIncidenciasPorIndice("opsid", opsid);
}

bool CIncidencias2Set::QueryIncidenciasDelProveedor(UINT pid)
{
	return QueryIncidenciasPorIndice("pid", pid);
}

bool CIncidencias2Set::QueryIncidenciasPorOperacion(UINT opsid)
{
	return QueryIncidenciasPorIndice("opsid", opsid);
}

bool CIncidencias2Set::QueryAllIncidencias(void)
{
	CString strSQL;

	strSQL.Format("SELECT * FROM %s",
					GetDefaultSQL().GetBuffer(0));

	if( IsOpen() ) Close();
	Open(this->m_nDefaultType, strSQL.GetBuffer(0));
	if( !IsOpen() ) return false;

	if( GetRecordCount() > 0 ) return true;

	return false;
}

void CIncidencias2Set::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CIncidencias2Set)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[inid]"), m_inid);
	DFX_Text(pFX, _T("[innom]"), m_innom);
	DFX_Text(pFX, _T("[indesc]"), m_indesc);
	DFX_Long(pFX, _T("[pid]"), m_pid);
	DFX_Bool(pFX, _T("[res]"), m_res);
	DFX_Long(pFX, _T("[opid]"), m_opid);
	DFX_Long(pFX, _T("[opsid]"), m_opsid);
	DFX_DateTime(pFX, _T("[ifecini]"), m_ifecini);
	DFX_DateTime(pFX, _T("[ifecres]"), m_ifecres);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CIncidencias2Set diagnostics

#ifdef _DEBUG
void CIncidencias2Set::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CIncidencias2Set::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG

