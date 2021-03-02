// MainFrm.cpp : implementation of the CMainFrame class
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

#include "OneFieldDbDialog.h"
#include "SearchDialog.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_DB_ADD_INCIDENCIA, OnDbAddIncidencia)
	ON_COMMAND(ID_DB_OPERACIONES, OnDbOperaciones)
	ON_COMMAND(ID_DB_OPERARIOS, OnDbOperarios)
	ON_COMMAND(ID_DB_OPERARIOS_SOPORTE, OnDbOperariosSoporte)
	ON_COMMAND(ID_DB_PROVEEDORES, OnDbProveedores)
	ON_COMMAND(ID_REPORT_INCIDENCIA, OnReportIncidencia)
	ON_COMMAND(IDK_SELECT_COM_LIST_VIEW, OnKbSelectComListView)
	ON_COMMAND(IDK_SELECT_INC_FORM_VIEW, OnKbSelectIncFormView)
	ON_COMMAND(IDK_SELECT_INC_LIST_VIEW, OnKbSelectIncListView)
	ON_COMMAND(ID_RECORD_L, OnCmdRecordLast)
	ON_COMMAND(ID_RECORD_N, OnCmdRecordNext)
	ON_COMMAND(ID_RECORD_P, OnCmdRecordPrevious)
	ON_COMMAND(ID_RECORD_F, OnCmdRecordFirst)
	ON_COMMAND(ID_CMD_SEARCH_DLG, OnCmdSearchDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	for( int i=0;i< OFD_NUM_DLGS; i++)
		this->m_ofdDialogs[i] = NULL;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{


	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	CRect cr; 
	GetClientRect( &cr);

	m_wndSplitter.CreateStatic(this,2, 1);

	m_wndSplitterInc.CreateStatic (&m_wndSplitter, 1, 2, WS_CHILD|WS_VISIBLE, m_wndSplitter.IdFromRowCol(0, 0));
	m_wndSplitterInc.CreateView(0,0,RUNTIME_CLASS(CIncidenciasListView),CSize(((cr.Width()/4)*3)-5, 50), pContext);
	m_wndSplitterInc.CreateView(0,1,RUNTIME_CLASS(CIncidencias2View),CSize((cr.Width()/4)+5, 50), pContext);

	m_wndSplitter.CreateView(1,0,RUNTIME_CLASS(CComunicacionesView),CSize(cr.Width(), 50), pContext);
	m_wndSplitter.SetRowInfo( 0, 350, 10);
	m_wndSplitter.SetRowInfo( 1, 50, 10);

	return TRUE;
}

CIncidencias2View* CMainFrame::GetIncidenciasFormView()
{
	return (CIncidencias2View*) m_wndSplitterInc.GetPane(0,1);
}

CIncidenciasListView* CMainFrame::GetIncidenciasListView()
{
	return (CIncidenciasListView*) m_wndSplitterInc.GetPane(0,0);
}

CComunicacionesView* CMainFrame::GetComunicacionesListView()
{
	return (CComunicacionesView*) m_wndSplitter.GetPane(1,0);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::OnDbAddIncidencia() 
{
	CIncidencias2Set *pISet = &GetIncidenciasFormView()->GetDocument()->m_incidencias2Set;	
	CIncidencias2View *pIView = GetIncidenciasFormView();
	CIncidenciasListView *pILView = GetIncidenciasListView();
	SYSTEMTIME t;
	CListCtrl *pListCtrl;
	int items;

	pISet->AddNew();

	::GetSystemTime(&t);

	pISet->m_innom = "<NUEVA INCIDENCIA>";
	pISet->m_ifecini = t;
	pISet->m_opid = 1;
	pISet->m_opsid = 1;
	pISet->m_pid = 1;
	pISet->m_res = false;

	pISet->Update();

	pILView->UpdateView();
	pListCtrl = &pILView->GetListCtrl();

	if( (items = pListCtrl->GetItemCount()) > 0 ){
		pListCtrl->SetItemState(--items, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
		pListCtrl->SetSelectionMark(items) ;
	}

	pIView->m_EditDbSubjectCtrl.SetSel(0, -1, true);
	pIView->m_EditDbSubjectCtrl.SetFocus();
	pIView->SetEditing();
}

void CMainFrame::AddBlankIncidencia()
{
	this->OnDbAddIncidencia();
}

void CMainFrame::OnDbOperaciones() 
{
	COperacionesSet *pOSet = &GetIncidenciasFormView()->GetDocument()->m_operacionesSet;	
	COneFieldDbDialog *p_ofDlg;

	if( this->m_ofdDialogs[OFD_OPERACIONES_TYPE] == NULL ){
		p_ofDlg = new  COneFieldDbDialog(OFBD_DLG_TYPE_OPERACIONES, (CDaoRecordset*)pOSet),
		p_ofDlg->Create(p_ofDlg->IDD);
		p_ofDlg->ShowWindow(SW_SHOW);
	}else{
		m_ofdDialogs[OFD_OPERACIONES_TYPE]->FlashWindow(true);
		m_ofdDialogs[OFD_OPERACIONES_TYPE]->BringWindowToTop();
	}
}

void CMainFrame::OnDbOperarios() 
{
	COperariosSet *pOpSet = &GetIncidenciasFormView()->GetDocument()->m_operariosSet;	
	COneFieldDbDialog *p_ofDlg;
	if( this->m_ofdDialogs[OFD_OPERARIOS_TYPE] == NULL ){	
		p_ofDlg = new  COneFieldDbDialog(OFBD_DLG_TYPE_OPERARIOS, (CDaoRecordset*)pOpSet),
		p_ofDlg->Create(p_ofDlg->IDD);
		p_ofDlg->ShowWindow(SW_SHOW);
	}else{
		m_ofdDialogs[OFD_OPERARIOS_TYPE]->FlashWindow(true);
		m_ofdDialogs[OFD_OPERARIOS_TYPE]->BringWindowToTop();
	}
}

void CMainFrame::OnDbOperariosSoporte() 
{
	COperariosSoporteSet *pOpSopSet = &GetIncidenciasFormView()->GetDocument()->m_operariosSoporteSet;	
	COneFieldDbDialog *p_ofDlg;

	if( this->m_ofdDialogs[OFD_OPERARIOS_SOPORTE_TYPE] == NULL ){	
		p_ofDlg = new  COneFieldDbDialog(OFBD_DLG_TYPE_OPERARIOS_SOPORTE, (CDaoRecordset*)pOpSopSet),
		p_ofDlg->Create(p_ofDlg->IDD);
		p_ofDlg->ShowWindow(SW_SHOW);
	}else{
		m_ofdDialogs[OFD_OPERARIOS_SOPORTE_TYPE]->FlashWindow(true);
		m_ofdDialogs[OFD_OPERARIOS_SOPORTE_TYPE]->BringWindowToTop();
	}
}

void CMainFrame::OnDbProveedores() 
{
	CProveedoresSet *pProvSet = &GetIncidenciasFormView()->GetDocument()->m_proveedoreSet;
	COneFieldDbDialog *p_ofDlg;

	if( this->m_ofdDialogs[OFD_PROVEEDORES_TYPE] == NULL ){	
		p_ofDlg = new  COneFieldDbDialog(OFB_DLG_TYPE_PROVEEDORES, (CDaoRecordset*)pProvSet),
		p_ofDlg->Create(p_ofDlg->IDD);
		p_ofDlg->ShowWindow(SW_SHOW);
	}else{
		m_ofdDialogs[OFD_PROVEEDORES_TYPE]->FlashWindow(true);
		m_ofdDialogs[OFD_PROVEEDORES_TYPE]->BringWindowToTop();
	}
}


void CMainFrame::OnReportIncidencia() 
{
	CString str;
	char *dummy;
	long comunicaciones;

	CIncidencias2View* pIView =GetIncidenciasFormView();
	CIncidenciasListView* pLiView =GetIncidenciasListView();

	CComunicacionesSet* pCSet = &(pIView->GetDocument()->m_comunicacionesSet);
	COperariosSet* pOperariosSet = &(pIView->GetDocument()->m_operariosSet);
	COperariosSoporteSet* pOpSopSet = &(pIView->GetDocument()->m_operariosSoporteSet);
	COperacionesSet* pOperacionesSet = &(pIView->GetDocument()->m_operacionesSet);
	CProveedoresSet* pProveedoresSet = &(pIView->GetDocument()->m_proveedoreSet);
	CIncidencias2Set* pISet = &(pIView->GetDocument()->m_incidencias2Set);
	
	if( pLiView->m_lastInID == 0 ){
		str.Format("Por favor seleccione una incidencia\npara crear el informe.");
		AfxMessageBox(str.GetBuffer(0), MB_OK | MB_ICONINFORMATION, 0);
		return;
	}

	if( !pISet->QueryIncidencia(pLiView->m_lastInID) ){
		str.Format("La incidencia %i ya no existe\nPor favor seleccione otra incidencia");
		AfxMessageBox(str.GetBuffer(0), MB_OK | MB_ICONINFORMATION, 0);
		return;
	}

	CFile* pFile = new CFile("informe.html", CFile::modeCreate|CFile:: modeReadWrite); 

	dummy = pISet->m_innom.GetBuffer(0);

	//cabecera
	str.Format("<html>\n<meta http-equiv='Content-Type' content='text/html; charset=Cp1250'>\n\
<link rel='stylesheet' type='text/css' href='style.css'>\n\
<head>\n<title>%s</title>\n<body><h1>Incidencia: \"%s\"</h1><p><small>ID: %i</small></p>\n",
				dummy,
				dummy,
				pISet->m_inid);

	pFile->Write(str.GetBuffer(0), str.GetLength());

	if( pOperariosSet->QueryOperario(pISet->m_opid) ){
		dummy = pOperariosSet->m_opnom.GetBuffer(0);
	}else{
		dummy = "<sin asignar>";
	}

	// Asunto
	str.Format("<table width='770' border='1'>\n<tr><td>Asunto:</td><td><pre>%s</pre></td></tr>\n",
				pISet->m_indesc.GetBuffer(0));

	pFile->Write(str.GetBuffer(0), str.GetLength());

	// Abierta por y fecha
	str.Format("<tr><td>Abierta por:</td><td>%s</td></tr>\n\
<tr><td>Fecha apertura:</td><td>%s</td></tr>\n",
				dummy,
				pISet->m_ifecini.Format("%d/%m/%Y").GetBuffer(0));

	pFile->Write(str.GetBuffer(0), str.GetLength());

	// proveedor
	if( pProveedoresSet->QueryProveedor(pISet->m_pid) ){
		dummy = pProveedoresSet->m_pnom.GetBuffer(0);
	}else{
		dummy = "<sin asignar>";
	}

	str.Format("<tr><td>Proveedor:</td><td>%s</td></tr>\n",
				dummy);

	pFile->Write(str.GetBuffer(0), str.GetLength());

	// Concerniente a, resuelto y fecha resolucion
	if( pOperacionesSet->QueryOperacion(pISet->m_opsid) ){
		dummy = pOperacionesSet->m_opnom.GetBuffer(0);
	}else{
		dummy = "<sin asignar>";
	}

	str.Format("<tr><td>Concerniente a:</td><td>%s</td></tr>\n\
<tr><td>Resuelto:</td><td>%s</td></tr>\n\
<tr><td>Fecha resoluci&oacute;n:</td><td>%s</td></tr>\n",
				dummy,
				pISet->m_res?"si":"<span style='color:red'>no</span>",
				pISet->m_res?pISet->m_ifecres.Format("%d/%m/%Y").GetBuffer(0):"&nbsp;");

	pFile->Write(str.GetBuffer(0), str.GetLength());

	// comunicaciones
	if( pCSet->QueryComunicacionesDeIncidente(pISet->m_inid) ){
		comunicaciones = pCSet->GetRecordCount();
	}else{
		comunicaciones = 0;
	}
	
	if( comunicaciones == 0 ){
		str.Format("</table><p><b>0 comunicaciones.</b></p><hr size='1'>\n");
		pFile->Write(str.GetBuffer(0), str.GetLength());
	}else{
		pFile->Write("</table><hr size='1'>\n", 23);
	}

	if( comunicaciones > 0 ){		
		do{
			char *operario;
			char *operario_soporte;
			
			long index = pCSet->GetAbsolutePosition();

			if( pOperariosSet->QueryOperario(pCSet->m_opid) )
				operario = pOperariosSet->m_opnom.GetBuffer(0);
			else
				operario = "<sin asignar>";
			
			if( pOpSopSet->QueryOperarioSoporte(pCSet->m_opsid) )
				operario_soporte = pOpSopSet->m_opnom.GetBuffer(0);
			else
				operario_soporte = "<sin asignar>";

			str.Format("\n\n<p><b><u>Comunicación %i</u></b> <small>[ID %i]</small></p>\n",
						++index,
						pCSet->m_coid);

			pFile->Write(str.GetBuffer(0), str.GetLength());

			if( pCSet->m_orig )
				str.Format("\n\n<p><i>De operario</i> <b>%s</b> <i>a operario soporte</i> <b>%s</b> el <b>%s</b>:</p>\n<pre>%s</pre>\n",
						operario,
						operario_soporte,						
						pCSet->m_cofec.Format("%d/%m/%Y").GetBuffer(0),
						pCSet->m_codesc.GetBuffer(0));
			else
				str.Format("\n\n<p><i>De operario soporte</i> <b>%s</b> <i>a operario</i> <b>%s</b> el <b>%s</b>:</p>\n<pre>%s</pre>\n",
						operario_soporte,
						operario,						
						pCSet->m_cofec.Format("%d/%m/%Y").GetBuffer(0),
						pCSet->m_codesc.GetBuffer(0));

			pFile->Write(str.GetBuffer(0), str.GetLength());

			if( pCSet->m_cont ){
				str.Format("<p><i>Respuesta el</i> <b>%s</b>:</p>\n<pre>%s</pre>\n",
							pCSet->m_cofecresp.Format("%d/%m/%Y"),
							pCSet->m_resdesc.GetBuffer(0) );
			}else{
				str.Format("<p><span style='color:red'>No Contestado</span></p>\n");
			}


			pFile->Write(str.GetBuffer(0), str.GetLength());
			pFile->Write("<hr size='1'>\n", 13);

			pCSet->MoveNext();
		}while(!pCSet->IsEOF());
	}



	//cierre HTML
	str.Format("\n</body></html>\n" );

	pFile->Write(str.GetBuffer(0), str.GetLength());

	pFile->Flush();
	pFile->Close();

	::ShellExecute(this->m_hWnd, "open", "informe.html","","",SW_SHOW ); 
}

void CMainFrame::OnKbSelectComListView() 
{
	CListCtrl* pListCtrl = &GetComunicacionesListView()->GetListCtrl();
	pListCtrl->SetFocus();	

	if( pListCtrl->GetItemCount() > 0 ){		
		POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
		if( pos ) return;
		pListCtrl->SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
		pListCtrl->SetSelectionMark(0) ;
	}
}

void CMainFrame::OnKbSelectIncFormView() 
{
	GetIncidenciasFormView()->SetFocus();		
}

void CMainFrame::OnKbSelectIncListView() 
{
	CListCtrl* pListCtrl = &GetIncidenciasListView()->GetListCtrl();
	pListCtrl->SetFocus();

	if( pListCtrl->GetItemCount() > 0 ){		
		POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
		if( pos ) return;
		pListCtrl->SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
		pListCtrl->SetSelectionMark(0) ;
	}
}


// record buttons
void CMainFrame::OnCmdRecordLast() 
{
	CListCtrl* pListCtrl = &GetIncidenciasListView()->GetListCtrl();
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();

	int items = pListCtrl->GetItemCount();

	if( items == 0 ) return;

	pListCtrl->SetItemState(--items, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
	pListCtrl->SetSelectionMark(items) ;
	
}

void CMainFrame::OnCmdRecordNext() 
{
	CListCtrl* pListCtrl = &GetIncidenciasListView()->GetListCtrl();
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();

	int item;

	if( pListCtrl->GetItemCount() == 0 ) return;

	if(pos)
	{		 
		item = pListCtrl->GetNextSelectedItem(pos);
		if( pListCtrl->GetItemCount() <= item + 1 ) return;

		pListCtrl->SetItemState(item, LVIS_SELECTED | LVIS_FOCUSED, 0) ;
		
		pListCtrl->SetItemState(++item, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
		pListCtrl->SetSelectionMark(item) ;
	}else{
		pListCtrl->SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
		pListCtrl->SetSelectionMark(0) ;
	}	
	
}

void CMainFrame::OnCmdRecordPrevious() 
{
	CListCtrl* pListCtrl = &GetIncidenciasListView()->GetListCtrl();
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();

	int item;

	if( pListCtrl->GetItemCount() == 0 ) return;

	if(pos)
	{		 
		item = pListCtrl->GetNextSelectedItem(pos);

		if( item <= 0 ) return;

		pListCtrl->SetItemState(--item, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
		pListCtrl->SetSelectionMark(item) ;
	}	
}

void CMainFrame::OnCmdRecordFirst() 
{
	CListCtrl* pListCtrl = &GetIncidenciasListView()->GetListCtrl();
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();


	if( pListCtrl->GetItemCount() == 0 ) return;

	pListCtrl->SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
	pListCtrl->SetSelectionMark(0) ;
}

void CMainFrame::OnCmdSearchDlg() 
{
	CSearchDialog *pDlg = new CSearchDialog();

	pDlg->Create(pDlg->IDD);
	pDlg->ShowWindow(SW_SHOW);	
}
