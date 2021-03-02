// Incidencias2Doc.cpp : implementation of the CIncidencias2Doc class
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
#include "IncidenciasListView.h"
#include "ComunicacionesView.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIncidencias2Doc

IMPLEMENT_DYNCREATE(CIncidencias2Doc, CDocument)

BEGIN_MESSAGE_MAP(CIncidencias2Doc, CDocument)
	//{{AFX_MSG_MAP(CIncidencias2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIncidencias2Doc construction/destruction

CIncidencias2Doc::CIncidencias2Doc()
{
	// TODO: add one-time construction code here
}

CIncidencias2Doc::~CIncidencias2Doc()
{
}

BOOL CIncidencias2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	this->SetTitle("Registro de incidencias y comunicaciónes");

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CIncidencias2Doc serialization

void CIncidencias2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CIncidencias2Doc diagnostics

#ifdef _DEBUG
void CIncidencias2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIncidencias2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIncidencias2Doc commands
