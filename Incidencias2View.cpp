/*
Copyright 2006, Yago Rubio Sanfiz

Copying and distribution of this file, with or without modification,
are permited in any medium without royalty, provided the copyright
and this notice are preserved.This file is offered as - is without
any warranty.
*/

// Incidencias2View.cpp : implementation of the CIncidencias2View class
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

#include "CalendarDialog.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIncidencias2View

IMPLEMENT_DYNCREATE(CIncidencias2View, CDaoRecordView)

BEGIN_MESSAGE_MAP(CIncidencias2View, CDaoRecordView)
	//{{AFX_MSG_MAP(CIncidencias2View)
	ON_BN_CLICKED(IDC_BUTTON_CALMONTH, OnButtonCalmonth)
	ON_CBN_SELCHANGE(IDC_COMBO_PROVEEDOR, OnSelchangeComboProveedor)
	ON_EN_CHANGE(IDC_EDIT_DB_DESC, OnChangeEditDbDesc)
	ON_EN_CHANGE(IDC_EDIT_DBDATE_END, OnChangeEditDbdateEnd)
	ON_EN_CHANGE(IDC_EDIT_DBDATE_START, OnChangeEditDbdateStart)
	ON_EN_CHANGE(IDC_EDIT_DBID, OnChangeEditDbid)
	ON_EN_CHANGE(IDC_EDIT_DBSUBJECT, OnChangeEditDbsubject)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_INCIDENCIAS2_FORM, OnButtonSaveIncidenciaCliked)
	ON_BN_CLICKED(IDC_CHECK_FINISHED, OnCheckFinishedClicked)
	ON_BN_CLICKED(IDC_BUTTON_CALMONTH2, OnButtonCalmonth2)
	ON_CBN_SELCHANGE(IDC_COMBO_OPERACION, OnSelchangeComboOperacion)
	ON_CBN_SELCHANGE(IDC_COMBO_OPERARIO, OnSelchangeComboOperario)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CDaoRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CDaoRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CDaoRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIncidencias2View construction/destruction

CIncidencias2View::CIncidencias2View()
	: CDaoRecordView(CIncidencias2View::IDD)
{
	//{{AFX_DATA_INIT(CIncidencias2View)
	m_pSet = NULL;
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	m_bp = ::LoadBitmap(NULL, MAKEINTRESOURCE(OBM_CHECK));
}

CIncidencias2View::~CIncidencias2View()
{
	::DeleteObject(m_bp);
}

void CIncidencias2View::DoDataExchange(CDataExchange* pDX)
{
	CDaoRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIncidencias2View)
	DDX_Control(pDX, IDC_INC_FRM_BITMAP, m_pBitmap);
	DDX_Control(pDX, IDC_COMBO_OPERARIO, m_ComboOperario);
	DDX_Control(pDX, IDC_EDIT_DBDATE_START, m_EditDbDateStart);
	DDX_Control(pDX, IDC_EDIT_DBDATE_END, m_EditDbDateEnd);
	DDX_Control(pDX, IDC_EDIT_DBSUBJECT, m_EditDbSubjectCtrl);
	DDX_Control(pDX, IDC_EDIT_DB_DESC, m_EditDbDesctCtrl);
	DDX_Control(pDX, IDC_CHECK_FINISHED, m_CheckFinishedCtrl);
	DDX_Control(pDX, IDC_BUTTON_SAVE_INCIDENCIAS2_FORM, m_ButtonIncidenciasFormSave);
	DDX_Control(pDX, IDC_COMBO_PROVEEDOR, m_ComboProveedor);
	DDX_Control(pDX, IDC_COMBO_OPERACION, m_ComboOperacion);
	DDX_FieldCheck(pDX, IDC_CHECK_FINISHED, m_pSet->m_res, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_DBDATE_END, m_pSet->m_ifecres, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_DBDATE_START, m_pSet->m_ifecini, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_DB_DESC, m_pSet->m_indesc, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_DBSUBJECT, m_pSet->m_innom, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_DBID, m_pSet->m_inid, m_pSet);
	//}}AFX_DATA_MAP
}

BOOL CIncidencias2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CDaoRecordView::PreCreateWindow(cs);
}

void CIncidencias2View::OnInitialUpdate()
{
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	
	CIncidenciasListView *pLView = pFrame->GetIncidenciasListView();
	m_pSet = &GetDocument()->m_incidencias2Set;

	CDaoRecordView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	
	UpdateOperariosComboFromDb();
	UpdateOperationsComboFromDb();
	UpdateSuppliersComboFromDb();

	pLView->UpdateView();
	if(pLView->GetListCtrl().GetItemCount() > 0)
	{
		CString str = pLView->GetListCtrl().GetItemText(0,0);
		this->m_pSet->QueryIncidencia(atoi(str.GetBuffer(0)));
		UpdateAll();
	}
}

void CIncidencias2View::SetOperationOnCombo(UINT opid)
{
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	COperacionesSet* pOperacionesSet = &(GetDocument()->m_operacionesSet);

	// rellena el combo con todos los proveedores
	if( pOperacionesSet->QueryOperacion(opid) ){	
		m_ComboOperacion.SelectString(0, pOperacionesSet->m_opnom.GetBuffer(0));
	}
}


void CIncidencias2View::SetOperarioOnCombo(UINT opid)
{
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	COperariosSet* pOperariosSet = &(GetDocument()->m_operariosSet);

	// rellena el combo con todos los proveedores
	if( pOperariosSet->QueryOperario(opid) ){	
		m_ComboOperario.SelectString(0, pOperariosSet->m_opnom.GetBuffer(0));
	}
}

void CIncidencias2View::UpdateOperationsComboFromDb(void)
{
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	COperacionesSet* pOperacionesSet = &(GetDocument()->m_operacionesSet);

	// rellena el combo operaciones con todas las operaciones
	if( pOperacionesSet->QueryAllOperaciones() ){
		int i = 0;
		m_ComboOperacion.ResetContent();
		do{			
			m_ComboOperacion.AddString(pOperacionesSet->m_opnom.GetBuffer(0));
			m_ComboOperacion.SetItemData(i,(DWORD)pOperacionesSet->m_opid);
			pOperacionesSet->MoveNext();
			i++;
		}while(!pOperacionesSet->IsEOF());
	}
}


void CIncidencias2View::UpdateOperariosComboFromDb(void)
{
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	COperariosSet* pOperariosSet = &(GetDocument()->m_operariosSet);

	// rellena el combo operarios con todos los operarios
	if( pOperariosSet->QueryAllOperarios() ){
		int i = 0;
		this->m_ComboOperario.ResetContent();
		do{			
			m_ComboOperario.AddString(pOperariosSet->m_opnom.GetBuffer(0));
			m_ComboOperario.SetItemData(i,(DWORD)pOperariosSet->m_opid);
			pOperariosSet->MoveNext();
			i++;
		}while(!pOperariosSet->IsEOF());
	}
}


void CIncidencias2View::SetSupplierOnCombo(UINT sid)
{
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	CProveedoresSet* pProveedoresSet = &(GetDocument()->m_proveedoreSet);

	// rellena el combo con todos los proveedores
	if( pProveedoresSet->QueryProveedor(sid) ){	
		m_ComboProveedor.SelectString(0, pProveedoresSet->m_pnom.GetBuffer(0));
	}
}

void CIncidencias2View::UpdateSuppliersComboFromDb(void)
{
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	CProveedoresSet* pProveedoresSet = &(GetDocument()->m_proveedoreSet);

	// rellena el combo con todos los proveedores
	if( pProveedoresSet->QueryAllProveedores() ){
		int i = 0;
		m_ComboProveedor.ResetContent();
		do{			
			m_ComboProveedor.AddString(pProveedoresSet->m_pnom.GetBuffer(0));
			m_ComboProveedor.SetItemData(i,(DWORD)pProveedoresSet->m_pid);
			pProveedoresSet->MoveNext();
			i++;
		}while(!pProveedoresSet->IsEOF());
		//pOperacionesSet->Close();
	}
}


void CIncidencias2View::UpdateAll(void)
{
	UpdateData(false);

	SetSupplierOnCombo(m_pSet->m_pid);
	SetOperationOnCombo(m_pSet->m_opsid);
	SetOperarioOnCombo(m_pSet->m_opid);

	SetEditing(false);
}

/////////////////////////////////////////////////////////////////////////////
// CIncidencias2View printing

BOOL CIncidencias2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIncidencias2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIncidencias2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CIncidencias2View diagnostics

#ifdef _DEBUG
void CIncidencias2View::AssertValid() const
{
	CDaoRecordView::AssertValid();
}

void CIncidencias2View::Dump(CDumpContext& dc) const
{
	CDaoRecordView::Dump(dc);
}

CIncidencias2Doc* CIncidencias2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIncidencias2Doc)));
	return (CIncidencias2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIncidencias2View database support
CDaoRecordset* CIncidencias2View::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CIncidencias2View message handlers

void CIncidencias2View::OnButtonCalmonth() 
{
	CCalendarDialog* pDlg = new CCalendarDialog();
	CTime time;
	//CEdit *pDateCtrl;

	if( pDlg->DoModal() == CDLG_CAL_CLOSE_OK ){
		//pDateCtrl = (CEdit*)this->GetDlgItem(IDC_EDIT_DBDATE_START);
		this->m_EditDbDateStart.SetWindowText(pDlg->m_pMonthCalendarTime.Format("%d/%m/%Y"));
	}	
}

void CIncidencias2View::OnButtonCalmonth2() 
{
	CCalendarDialog* pDlg = new CCalendarDialog();
	CTime time;

	if( pDlg->DoModal() == CDLG_CAL_CLOSE_OK ){
		this->m_EditDbDateEnd.SetWindowText(pDlg->m_pMonthCalendarTime.Format("%d/%m/%Y"));
	}	
}

void CIncidencias2View::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	CString strOut = "Aqui ira el informe";

	pDC->TextOut(10, 0, strOut);

	CDaoRecordView::OnPrint(pDC, pInfo);
}


void CIncidencias2View::OnSelchangeComboProveedor() 
{
	SetEditing();
}


void CIncidencias2View::OnSelchangeComboOperario() 
{
	SetEditing();
}

void CIncidencias2View::OnChangeEditDbDesc() 
{
	SetEditing();
}

void CIncidencias2View::OnChangeEditDbdateEnd() 
{
	SetEditing();
}

void CIncidencias2View::OnChangeEditDbdateStart() 
{
	SetEditing();	
}

void CIncidencias2View::OnChangeEditDbid() 
{
	SetEditing();	
}

void CIncidencias2View::OnChangeEditDbsubject() 
{
	SetEditing();
}

void CIncidencias2View::OnCheckFinishedClicked() 
{
	SetEditing();		
}

void CIncidencias2View::OnSelchangeComboOperacion() 
{
	SetEditing();
}

void CIncidencias2View::OnButtonSaveIncidenciaCliked() 
{
	int id = this->m_pSet->m_inid;
	CIncidenciasListView *pListView;
	CMainFrame * pFrame;
	COleDateTime oleDateTime;
	CString str;
	int sel;

	if( m_pSet->QueryIncidencia(id) )
	{
		m_pSet->Edit();
		
		m_pSet->m_res = (m_CheckFinishedCtrl.GetState() & 0x0003);
		
		m_EditDbDesctCtrl.GetWindowText(str);
		m_pSet->m_indesc = str;

		m_EditDbSubjectCtrl.GetWindowText(str);
		m_pSet->m_innom = str;
		
		m_EditDbDateStart.GetWindowText(str);
		if( str.GetLength() >0 && oleDateTime.ParseDateTime( str.GetBuffer(0) ,VAR_DATEVALUEONLY) )
			m_pSet->m_ifecini = oleDateTime;
		else if( str.GetLength() == 0 )
			m_pSet->SetFieldValueNull("ifecini");

		m_EditDbDateEnd.GetWindowText(str);
		if( str.GetLength() >0 && oleDateTime.ParseDateTime( str.GetBuffer(0) ,VAR_DATEVALUEONLY) )
			m_pSet->m_ifecres = oleDateTime;
		else if( str.GetLength() == 0 )
			m_pSet->SetFieldValueNull("ifecres");

		if( (sel = m_ComboOperacion.GetCurSel()) != CB_ERR )
			m_pSet->m_opsid = (long) m_ComboOperacion.GetItemData(sel);
		
		if( (sel = m_ComboProveedor.GetCurSel()) != CB_ERR )
			m_pSet->m_pid = (long) m_ComboProveedor.GetItemData(sel);
		
		if( (sel = m_ComboOperario.GetCurSel()) != CB_ERR )
			m_pSet->m_opid = (long) m_ComboOperario.GetItemData(sel);
		
		m_pSet->Update();
		m_pSet->Requery();

		UpdateAll();

		pFrame = (CMainFrame*)AfxGetMainWnd();

		pListView = pFrame->GetIncidenciasListView();
		pListView->UpdateView();
		pFrame->GetComunicacionesListView()->UpdateViewForIncident(pListView->m_lastInID);
	}

	SetEditing(false);
}


HBRUSH CIncidencias2View::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDaoRecordView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	//if(m_ButtonIncidenciasFormSave.IsWindowEnabled() && nCtlColor == CTLCOLOR_DLG)
	//{
    //      hbr = ::CreateSolidBrush (RGB(230,230,230));
	//}

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CIncidencias2View::SetEditing(BOOL editing)
{

	m_ButtonIncidenciasFormSave.EnableWindow(editing);
	if( editing ) this->m_pBitmap.SetBitmap(this->m_bp);
	else this->m_pBitmap.SetBitmap(NULL);

	//this->Invalidate();

}
