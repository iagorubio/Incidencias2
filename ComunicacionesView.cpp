// ComunicacionesView.cpp : implementation file
//

#include "stdafx.h"
#include <afxcview.h>

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

#include "ComunicacionesDialog.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComunicacionesView

IMPLEMENT_DYNCREATE(CComunicacionesView, CListView)

CComunicacionesView::CComunicacionesView()
{
}

CComunicacionesView::~CComunicacionesView()
{
}


BEGIN_MESSAGE_MAP(CComunicacionesView, CListView)
	//{{AFX_MSG_MAP(CComunicacionesView)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_DB_DELETE_ACTIVE_REG, OnComViewDbDeleteActiveReg)
	ON_NOTIFY_REFLECT(NM_RETURN, OnReturn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComunicacionesView drawing

void CComunicacionesView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();

	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CComunicacionesView diagnostics

#ifdef _DEBUG
void CComunicacionesView::AssertValid() const
{
	CListView::AssertValid();
}

void CComunicacionesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

void  CComunicacionesView::UpdateViewForIncident (UINT incident)
{
	
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();

	CIncidencias2View* pIView = pFrame->GetIncidenciasFormView();
	CComunicacionesSet* pCSet = &(pIView->GetDocument()->m_comunicacionesSet);
	COperariosSet* pOperariosSet = &(pIView->GetDocument()->m_operariosSet);
	COperariosSoporteSet* pOpSopSet = &(pIView->GetDocument()->m_operariosSoporteSet);
	CIncidencias2Set* pISet = &(pIView->GetDocument()->m_incidencias2Set);
	CListCtrl* pListCtrl = &GetListCtrl();

	pListCtrl->DeleteAllItems();

	if( !pCSet->QueryComunicacionesDeIncidente(incident) ) return;

	if( pCSet->GetRecordCount() > 0 ) {
		int i = 0;
		do{
			CString strF;
			strF.Format("%i", pCSet->m_coid);
			pListCtrl->InsertItem(i, strF.GetBuffer(0));

			if( pISet->QueryIncidencia(pCSet->m_inid) )
				pListCtrl->SetItemText(i,1,pISet->m_innom.GetBuffer(0));

			if( pOperariosSet->QueryOperario(pCSet->m_opid) )
				pListCtrl->SetItemText(i,2,pOperariosSet->m_opnom.GetBuffer(0));
			
			strF.Format("%s", pCSet->m_orig?"->":"<-");
			pListCtrl->SetItemText(i,3,strF.GetBuffer(0));
			
			if( pOpSopSet->QueryOperarioSoporte(pCSet->m_opsid))
				pListCtrl->SetItemText(i,4,pOpSopSet->m_opnom.GetBuffer(0));

			strF.Format("%s", pCSet->m_cont?"si":"no");
			pListCtrl->SetItemText(i,5,strF.GetBuffer(0));
			
			pListCtrl->SetItemText(i,6,pCSet->m_codesc.GetBuffer(0));
			pListCtrl->SetItemText(i,7,pCSet->m_cofec.Format("%d/%m/%Y"));

			pListCtrl->SetItemText(i,8,pCSet->m_resdesc.GetBuffer(0));
			pListCtrl->SetItemText(i,9,pCSet->m_cofecresp.Format("%d/%m/%Y"));

			++i;
			pCSet->MoveNext();
		}while(!pCSet->IsEOF());
	}
}

/////////////////////////////////////////////////////////////////////////////
// CComunicacionesView message handlers

void CComunicacionesView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	CListCtrl* p_ListCtrl = &GetListCtrl();

	p_ListCtrl->SetExtendedStyle(p_ListCtrl->GetStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP);
	p_ListCtrl->ModifyStyle(0, LVS_SINGLESEL|LVS_SHOWSELALWAYS);
	p_ListCtrl->InsertColumn(0,"id",LVCFMT_LEFT,20,-1);
	p_ListCtrl->InsertColumn(1,"incidencia",LVCFMT_LEFT,150,0);
	p_ListCtrl->InsertColumn(2,"operario",LVCFMT_LEFT,80,0);
	p_ListCtrl->InsertColumn(3,"", LVCFMT_CENTER, 30, 0);
	p_ListCtrl->InsertColumn(4,"op. soporte",LVCFMT_LEFT,80,0);
	p_ListCtrl->InsertColumn(5,"contestado",LVCFMT_CENTER,80,0);
	p_ListCtrl->InsertColumn(6,"descripción",LVCFMT_LEFT,250,0);
	p_ListCtrl->InsertColumn(7,"fecha",LVCFMT_LEFT,100,0);
	p_ListCtrl->InsertColumn(8,"respuesta",LVCFMT_LEFT,250,0);
	p_ListCtrl->InsertColumn(9,"fecha respuesta",LVCFMT_LEFT,150,0);
}

BOOL CComunicacionesView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= LVS_REPORT;

	return CListView::PreCreateWindow(cs);
}

void CComunicacionesView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{


	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	CIncidencias2View *pIView = pFrame->GetIncidenciasFormView();	
	
	CListCtrl* pListCtrl = &GetListCtrl();
	UINT uFlags = 0;
	int nHitItem = pListCtrl->HitTest(point, &uFlags);


	CListView::OnLButtonDblClk(nFlags, point);

	if (uFlags & LVHT_ONITEM)
	{
		char item[256];
		int id;
		CComunicacionesDialog *pDlg;

		pListCtrl->GetItemText(nHitItem, 0, item, 255);
		id = atoi(item);
		pDlg = new CComunicacionesDialog(NULL, COM_DLG_TYPE_EDIT, id);
		pDlg->Create(pDlg->IDD, NULL);
		pDlg->ShowWindow(SW_SHOW);
	}
	else {
		char item[256];
		int id;
		CComunicacionesDialog* pDlg;
		CIncidenciasListView* pLIView = pFrame->GetIncidenciasListView();

		pListCtrl = &(pLIView->GetListCtrl());
		POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
		nHitItem = pListCtrl->GetNextSelectedItem(pos);
		pListCtrl->GetItemText(nHitItem, 0, item, 255);

		pDlg = new CComunicacionesDialog(NULL, COM_DLG_TYPE_NEW);
		id = atoi(item);
		pDlg->SetIncidenciaId(id);
		pDlg->Create(pDlg->IDD, NULL);
		pDlg->ShowWindow(SW_SHOW);
	}
}

void CComunicacionesView::OnComViewDbDeleteActiveReg() 
{
	POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	
	CIncidencias2View *pIView = pFrame->GetIncidenciasFormView();
	CIncidenciasListView *pIListView = pFrame->GetIncidenciasListView();
	CComunicacionesSet* pCSet = &pIView->GetDocument()->m_comunicacionesSet;
	CListCtrl* pListCtrl = &GetListCtrl();

	if(pos)
	{
		int item = GetListCtrl().GetNextSelectedItem(pos); 
		char pcItem[256];
		int id;

		pListCtrl->GetItemText(item, 0, pcItem, 255);
		id = atoi(pcItem);

		if( pCSet->QueryComunicacion(id) ){
			CString str;

			str.Format("¿ Quiere borrar la comunicación %i\npermanentemente ?", id);
			if( AfxMessageBox(str, MB_YESNO, 0) != IDYES ) return;
			pCSet->Delete();
			UpdateViewForIncident(pIListView->m_lastInID);
		}
	}	
}

void CComunicacionesView::OnReturn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();

	if(pos)
	{
		int item = GetListCtrl().GetNextSelectedItem(pos); 
		char itemStr[256];
		int id;
		CComunicacionesDialog *pDlg;

		GetListCtrl().GetItemText(item, 0, itemStr, 255);
		id = atoi(itemStr);
		pDlg = new CComunicacionesDialog(NULL, COM_DLG_TYPE_EDIT, id);
		pDlg->Create(pDlg->IDD, NULL);
		pDlg->ShowWindow(SW_SHOW);
	}

	*pResult = 0;
}
