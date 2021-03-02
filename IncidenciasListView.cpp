// IncidenciasListView.cpp : implementation file
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

#include "ComunicacionesDialog.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIncidenciasListView

IMPLEMENT_DYNCREATE(CIncidenciasListView, CListView)

CIncidenciasListView::CIncidenciasListView()
{
	this->m_lastInID = 0;
}

CIncidenciasListView::~CIncidenciasListView()
{
}


BEGIN_MESSAGE_MAP(CIncidenciasListView, CListView)
	//{{AFX_MSG_MAP(CIncidenciasListView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_DB_NEW_COMUNICACION, OnDbNewComunicacion)
	ON_COMMAND(ID_DB_DELETE_ACTIVE_REG, OnIListViewDbDeleteActiveReg)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_NOTIFY_REFLECT(NM_RETURN, OnReturn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIncidenciasListView drawing

void CIncidenciasListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CIncidenciasListView diagnostics

#ifdef _DEBUG
void CIncidenciasListView::AssertValid() const
{
	CListView::AssertValid();
}

void CIncidenciasListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIncidenciasListView message handlers

BOOL CIncidenciasListView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= LVS_REPORT;

	return CListView::PreCreateWindow(cs);
}

void CIncidenciasListView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	CListCtrl* p_ListCtrl = &GetListCtrl();

	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	CIncidenciasListView* pLIView = pFrame->GetIncidenciasListView();


	p_ListCtrl->SetExtendedStyle(p_ListCtrl->GetStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP);
	p_ListCtrl->ModifyStyle(0, LVS_SINGLESEL|LVS_SHOWSELALWAYS);
	p_ListCtrl->InsertColumn(0,"id",LVCFMT_LEFT,20,-1);
	p_ListCtrl->InsertColumn(1,"incidencia",LVCFMT_LEFT,250,0);
	p_ListCtrl->InsertColumn(2,"descripción",LVCFMT_LEFT,250,0);
	p_ListCtrl->InsertColumn(3,"proveedor",LVCFMT_LEFT,50,0);
	p_ListCtrl->InsertColumn(4,"res",LVCFMT_LEFT,50,0);
	p_ListCtrl->InsertColumn(5,"opsid",LVCFMT_LEFT,150,0);
	p_ListCtrl->InsertColumn(6,"ifecini",LVCFMT_LEFT,100,0);
	p_ListCtrl->InsertColumn(7,"ifecres",LVCFMT_LEFT,150,0);


/*
	pid // proveedor id
	res  // resuelta si/no
	opid  // operario que abrio la incidencia
	opsid // operaciones
	ifecini // fecha inicio
	ifecres // fecha resolucion
*/

	
}

void CIncidenciasListView::SelectIncidentById(int id)
{
	CString str;

	str.Format("%i", id);
	SelectIncidentBySzid(str.GetBuffer(0));
}

void CIncidenciasListView::SelectIncidentBySzid(char *szid)
{
	LVFINDINFO info;
	int index;

	info.flags = LVFI_STRING;
	info.psz = szid;
		
	index = GetListCtrl().FindItem(&info);

	if( index >= 0 ){
		GetListCtrl().EnsureVisible(index, false);
		GetListCtrl().SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
		GetListCtrl().SetSelectionMark(index) ;
	}
}

void CIncidenciasListView::UpdateView()
{
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();	
	CIncidencias2View *pIView = pFrame->GetIncidenciasFormView();
	CIncidencias2Set* pISet = &pIView->GetDocument()->m_incidencias2Set;

	CListCtrl* p_liListCtrl =  &GetListCtrl();
	p_liListCtrl->DeleteAllItems();

	if( pISet->QueryAllIncidencias() ){
		int i=0;
		CString strF;
		do{
			strF.Format("%i", pISet->m_inid);
			p_liListCtrl->InsertItem(i, strF.GetBuffer(0));
			p_liListCtrl->SetItemText(i,1,pISet->m_innom.GetBuffer(0));
			p_liListCtrl->SetItemText(i,2,pISet->m_indesc.GetBuffer(0));
			pISet->MoveNext();
			i++;
		}while(!pISet->IsEOF() );
	}
}


void CIncidenciasListView::OnLButtonDown(UINT nFlags, CPoint point) 
{

	CListView::OnLButtonDown(nFlags, point);
}

void CIncidenciasListView::OnDbNewComunicacion() 
{
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	CIncidenciasListView *pLIView = pFrame->GetIncidenciasListView();
	CListCtrl *pListCtrl = &pLIView->GetListCtrl();

	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if(pos)
	{
		int index = pListCtrl->GetNextSelectedItem(pos);
		CString  str = pListCtrl->GetItemText(index, 0);
		int inID = atoi(str.GetBuffer(0));
		
		CComunicacionesDialog *pDlg = new CComunicacionesDialog(NULL, COM_DLG_TYPE_NEW, inID);
		pDlg->Create(pDlg->IDD, NULL);
		pDlg->ShowWindow(SW_SHOW);
	}		
}

void CIncidenciasListView::OnIListViewDbDeleteActiveReg() 
{
	int item,id, count;
	char pcItem[256];
	POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	
	CIncidencias2View *pIView = pFrame->GetIncidenciasFormView();
	CIncidencias2Set *pISet = &pIView->GetDocument()->m_incidencias2Set;
	CComunicacionesSet *pCSet = &pIView->GetDocument()->m_comunicacionesSet;
	CListCtrl* pListCtrl = &GetListCtrl();

	if(!pos) return;

	item = GetListCtrl().GetNextSelectedItem(pos); 

	pListCtrl->GetItemText(item, 0, pcItem, 255);
	id = atoi(pcItem);

	if( pISet->QueryIncidencia(id) ){
		CString str;

		if( !pCSet->QueryComunicacionesDeIncidente(id) ){
			str.Format("¿ Quiere borrar la incidencia %i\npermanentemente ?", id);
			if( AfxMessageBox(str, MB_YESNO, 0) != IDYES ) return;
			pISet->Delete();
		}else{
			str.Format("¿ Quiere borrar la incidencia %i\npermanentemente ?\n\nSe borrarán a su vez todas las\ncomunicaciones de este incidente.", id);
			if( AfxMessageBox(str, MB_YESNO, 0) != IDYES ) return;
			do{
				pCSet->Delete();
				pCSet->MoveNext();
			}while( !pCSet->IsEOF() );
			pISet->Delete();
		}
		
		UpdateView();

		if( (count = pListCtrl->GetItemCount()) == 0 ){
			pFrame->AddBlankIncidencia();	
			return;
		}

		if( count > --item ){
			pListCtrl->SetItemState(item, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
			pListCtrl->SetSelectionMark(item) ;
		}else{
			pListCtrl->SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
			pListCtrl->SetSelectionMark(0); 
		}
	}	
}


void CIncidenciasListView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	
	CIncidencias2View *pIView = pFrame->GetIncidenciasFormView();
	CIncidencias2Set* pISet = &pIView->GetDocument()->m_incidencias2Set;
	CListCtrl* pListCtrl = &GetListCtrl();

	if(pos)
	{
		int item = GetListCtrl().GetNextSelectedItem(pos); 
		char pcItem[256];
		int id;
		
		CComunicacionesView* pCView = pFrame->GetComunicacionesListView();
		pListCtrl->GetItemText(item, 0, pcItem, 255);
		id = atoi(pcItem);
		pCView->UpdateViewForIncident(id);
		pISet->QueryIncidencia(id);
		pIView->UpdateAll();
		m_lastInID = id;
	}

	*pResult = 0;
}

void CIncidenciasListView::OnReturn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnItemchanged(pNMHDR, pResult);
}

