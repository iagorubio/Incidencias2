// ComunicacionesDialog.cpp : implementation file
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

#include "ComunicacionesDialog.h"

#include "CalendarDialog.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComunicacionesDialog dialog



CComunicacionesDialog::CComunicacionesDialog(CWnd* pParent, ComDlgType type, int inId)
	: CDialog(CComunicacionesDialog::IDD, pParent)
{
	this->m_uType = type;
	this->m_comID = inId;
	this->m_pParent = pParent;
	//{{AFX_DATA_INIT(CComunicacionesDialog)
	//}}AFX_DATA_INIT
}


void CComunicacionesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComunicacionesDialog)
	DDX_Control(pDX, IDC_CHECK_ORIGEN_AQUI, m_CheckOrigenAquiCtrl);
	DDX_Control(pDX, IDC_EDIT_FECHA_INICIO, m_EditFechaComuCtrl);
	DDX_Control(pDX, IDC_EDIT_FECHA_CONTESTACION, m_EditFechaRespCtrl);
	DDX_Control(pDX, IDC_EDIT_DESCRIPCION_RESP, m_EditDescRespCtrl);
	DDX_Control(pDX, IDC_EDIT_DESCRIPCION_COM, m_EditDescComuCtrl);
	DDX_Control(pDX, IDC_COMBO_OPERARIOS_SOPORTE, m_ComboOperariosSoporteCtrl);
	DDX_Control(pDX, IDC_COMBO_OPERARIOS, m_ComboOperariosCtrl);
	DDX_Control(pDX, IDC_COMBO_INCIDENCIAS, m_ComboIncidenciasCtrl);
	DDX_Control(pDX, IDC_CHECK_CONTESTADO, m_CheckContestadoCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComunicacionesDialog, CDialog)
	//{{AFX_MSG_MAP(CComunicacionesDialog)
	ON_BN_CLICKED(IDC_BUTTON_FECHA_INICIO, OnButtonFechaInicioCliked)
	ON_BN_CLICKED(IDC_BUTTON_FECHA_CONTESTACION, OnButtonFechaContestacionClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void  CComunicacionesDialog::SetDialogType(ComDlgType type)
{
	this->m_uType = type;
}

void  CComunicacionesDialog::SetIncidenciaId( int recordid )
{
	this->m_comID = recordid;
}

/////////////////////////////////////////////////////////////////////////////
// CComunicacionesDialog message handlers

BOOL CComunicacionesDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();


	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	CIncidencias2View *pIView = pFrame->GetIncidenciasFormView();
	
	CIncidencias2Set* pISet = &pIView->GetDocument()->m_incidencias2Set;
	COperariosSet *pOSet =  &pIView->GetDocument()->m_operariosSet;
	COperariosSoporteSet *pOpSopSet =  &pIView->GetDocument()->m_operariosSoporteSet;
	CComunicacionesSet *pCSet = &pIView->GetDocument()->m_comunicacionesSet;

	// fill three combos
	// incidencias
	if( pISet->QueryAllIncidencias() ){
		int i = 0;
		m_ComboIncidenciasCtrl.ResetContent();
		do{			
			m_ComboIncidenciasCtrl.AddString(pISet->m_innom.GetBuffer(0));
			m_ComboIncidenciasCtrl.SetItemData(i++,(DWORD)pISet->m_inid);
			pISet->MoveNext();
		}while(!pISet->IsEOF());
	}
	// operarios
	if( pOSet->QueryAllOperarios() ){
		int i = 0;
		m_ComboOperariosCtrl.ResetContent();
		do{			
			m_ComboOperariosCtrl.AddString(pOSet->m_opnom.GetBuffer(0));
			m_ComboOperariosCtrl.SetItemData(i++,(DWORD)pOSet->m_opid);
			pOSet->MoveNext();
		}while(!pOSet->IsEOF());
	}

	// perarios soporte
	if( pOpSopSet->QueryAllOperariosSoporte() ){
		int i = 0;
		this->m_ComboOperariosSoporteCtrl.ResetContent();
		do{			
			m_ComboOperariosSoporteCtrl.AddString(pOpSopSet->m_opnom.GetBuffer(0));
			m_ComboOperariosSoporteCtrl.SetItemData(i++,(DWORD)pOpSopSet->m_opsid);
			pOpSopSet->MoveNext();
		}while(!pOpSopSet->IsEOF());
	}

	// if new, dejar el resto en blanco
	if( this->m_uType != COM_DLG_TYPE_NEW ){// edit existing
		//FILL ALL FIELDS
		if( pCSet->QueryComunicacion(this->m_comID) ){
			CString str;

			pISet->QueryIncidencia(pCSet->m_inid);

			m_ComboIncidenciasCtrl.SelectString(0, pISet->m_innom.GetBuffer(0));

			pOSet->QueryOperario(pCSet->m_opid);
			m_ComboOperariosCtrl.SelectString(0, pOSet->m_opnom.GetBuffer(0));
			
			pOpSopSet->QueryOperarioSoporte(pCSet->m_opsid);
			m_ComboOperariosSoporteCtrl.SelectString(0, pOpSopSet->m_opnom.GetBuffer(0));
			
			str = pCSet->m_cofec.Format("%d/%m/%Y");
			m_EditFechaComuCtrl.SetWindowText(str.GetBuffer(0));

			m_EditDescComuCtrl.SetWindowText(pCSet->m_codesc.GetBuffer(0));

			str = pCSet->m_cofecresp.Format("%d/%m/%Y");
			m_EditFechaRespCtrl.SetWindowText(str.GetBuffer(0));

			m_EditDescRespCtrl.SetWindowText(pCSet->m_resdesc.GetBuffer(0));

			m_CheckContestadoCtrl.SetCheck(pCSet->m_cont);

			m_CheckOrigenAquiCtrl.SetCheck(pCSet->m_orig);
		}
	}else{
		//FILL INCIDENCIA
		if( pISet->QueryIncidencia(this->m_comID) )
			m_ComboIncidenciasCtrl.SelectString(0, pISet->m_innom.GetBuffer(0));
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CComunicacionesDialog::OnOK() 
{
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	CIncidencias2View *pIView = pFrame->GetIncidenciasFormView();
	CIncidenciasListView *pLIView = pFrame->GetIncidenciasListView();
	CComunicacionesView *pCView = pFrame->GetComunicacionesListView();
	CComunicacionesSet *pCSet = &pIView->GetDocument()->m_comunicacionesSet;
	int inid;

	CString str;
	
	if( this->m_uType == COM_DLG_TYPE_NEW ){
		int id;
		CString str;
		COleDateTime oleDateTime;

		pCSet->AddNew();

		if( (id = m_ComboIncidenciasCtrl.GetCurSel()) != CB_ERR )
			pCSet->m_inid = (int)m_ComboIncidenciasCtrl.GetItemData(id);
		else
			pCSet->m_inid = 1;
		
		inid = pCSet->m_inid;

		if( (id = m_ComboOperariosCtrl.GetCurSel()) != CB_ERR )
			pCSet->m_opid = (int)m_ComboOperariosCtrl.GetItemData(id);
		else
			pCSet->m_opid = 1;

		if( (id = m_ComboOperariosSoporteCtrl.GetCurSel()) != CB_ERR )
			pCSet->m_opsid = (int)m_ComboOperariosSoporteCtrl.GetItemData(id);
		else
			pCSet->m_opsid = 1;

		m_EditDescComuCtrl.GetWindowText(str);
		pCSet->m_codesc = str;

		m_EditDescRespCtrl.GetWindowText(str);
		pCSet->m_resdesc = str;

		m_EditFechaComuCtrl.GetWindowText(str);
		if( str.GetLength() >0 && oleDateTime.ParseDateTime( str.GetBuffer(0) ,VAR_DATEVALUEONLY) )
			pCSet->m_cofec = oleDateTime;

		m_EditFechaRespCtrl.GetWindowText(str);
		if( str.GetLength() >0 && oleDateTime.ParseDateTime( str.GetBuffer(0) ,VAR_DATEVALUEONLY) )
			pCSet->m_cofecresp = oleDateTime;


		pCSet->m_cont = m_CheckContestadoCtrl.GetCheck();
		pCSet->m_orig = m_CheckOrigenAquiCtrl.GetCheck();

		pCSet->Update();
	}else{
		int id;
		CString str;
		COleDateTime oleDateTime;

		if( pCSet->QueryComunicacion(this->m_comID) ){

			inid = pCSet->m_inid;

			pCSet->Edit();

			if( (id = m_ComboIncidenciasCtrl.GetCurSel()) != CB_ERR )
				pCSet->m_inid = (long)m_ComboIncidenciasCtrl.GetItemData(id);			

			if( (id = m_ComboOperariosCtrl.GetCurSel()) != CB_ERR )
				pCSet->m_opid = (long)m_ComboOperariosCtrl.GetItemData(id);

			if( (id = m_ComboOperariosSoporteCtrl.GetCurSel()) != CB_ERR )
				pCSet->m_opsid = (long)m_ComboOperariosSoporteCtrl.GetItemData(id);

			m_EditDescComuCtrl.GetWindowText(str);
			pCSet->m_codesc = str;


			m_EditDescRespCtrl.GetWindowText(str);
			pCSet->m_resdesc = str;

			m_EditFechaComuCtrl.GetWindowText(str);
			if( str.GetLength() >0 && oleDateTime.ParseDateTime( str.GetBuffer(0) ,VAR_DATEVALUEONLY) )
				pCSet->m_cofec = oleDateTime;
			else if( str.GetLength() == 0 )
				pCSet->SetFieldValueNull("cofec");

			m_EditFechaRespCtrl.GetWindowText(str);
			if( str.GetLength() >0 && oleDateTime.ParseDateTime( str.GetBuffer(0) ,VAR_DATEVALUEONLY) )
				pCSet->m_cofecresp = oleDateTime;
			else if( str.GetLength() == 0 )
				pCSet->SetFieldValueNull("cofecresp");

			pCSet->m_cont = m_CheckContestadoCtrl.GetCheck();
			pCSet->m_orig = m_CheckOrigenAquiCtrl.GetCheck();

			pCSet->Update();
		}
	}

	pCView->UpdateViewForIncident(inid);
	CDialog::OnOK();
}

void CComunicacionesDialog::OnButtonFechaInicioCliked() 
{
	CCalendarDialog* pDlg = new CCalendarDialog();
	CTime time;

	if( pDlg->DoModal() == CDLG_CAL_CLOSE_OK )
		this->m_EditFechaComuCtrl.SetWindowText(pDlg->m_pMonthCalendarTime.Format("%d/%m/%Y"));
}

void CComunicacionesDialog::OnButtonFechaContestacionClicked() 
{
	CCalendarDialog* pDlg = new CCalendarDialog();
	CTime time;

	if( pDlg->DoModal() == CDLG_CAL_CLOSE_OK )
		this->m_EditFechaRespCtrl.SetWindowText(pDlg->m_pMonthCalendarTime.Format("%d/%m/%Y"));
}
