/*
Copyright 2006, Yago Rubio Sanfiz

Copying and distribution of this file, with or without modification,
are permited in any medium without royalty, provided the copyright
and this notice are preserved.This file is offered as - is without
any warranty.
*/

// OneFieldDbDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Incidencias2.h"

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

#include "OneFieldDbDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COneFieldDbDialog dialog


COneFieldDbDialog::COneFieldDbDialog(OfDbDialogType type, CDaoRecordset *pSet, CWnd* pParent /*=NULL*/)
	: CDialog(COneFieldDbDialog::IDD, pParent)
{
	m_pOpSet = NULL;
	m_pOpSopSet = NULL;
	m_pProSet = NULL;
	m_OperSet = NULL;

	m_Type = type;

	SetDataSet(pSet);
	//{{AFX_DATA_INIT(COneFieldDbDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void COneFieldDbDialog::SetDataSet( CDaoRecordset *pSet )
{
	this->m_pSet = pSet;

	switch( this->m_Type ){
		case OFBD_DLG_TYPE_OPERARIOS:
			this->m_pOpSet = (COperariosSet*) pSet;
			break;
		case OFBD_DLG_TYPE_OPERARIOS_SOPORTE:
			this->m_pOpSopSet = (COperariosSoporteSet*) pSet;
			break;
		case OFBD_DLG_TYPE_OPERACIONES:
			this->m_OperSet = (COperacionesSet*) pSet;
			break;
		case OFB_DLG_TYPE_PROVEEDORES:
			this->m_pProSet = (CProveedoresSet*) pSet;
			break;
		default:
			TRACE("Bad dialog type one OneFieldDlg, check your programming !");
	}
}

void COneFieldDbDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COneFieldDbDialog)
	DDX_Control(pDX, IDC_OFDLG_LIST_DB_ITEMS, m_OFDbList);
	DDX_Control(pDX, IDC_OFDLG_EDIT_NAME, m_OFDbNameEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COneFieldDbDialog, CDialog)
	//{{AFX_MSG_MAP(COneFieldDbDialog)
	ON_BN_CLICKED(IDC_OFDLG_DELETE_BTN, OnOfdlgDeleteBtn)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_OFDLG_LIST_DB_ITEMS, OnItemchangedOfdlgListDbItems)
	ON_BN_CLICKED(ID_OFDLG_ADD_BTN, OnOfdlgAddBtn)
	ON_BN_CLICKED(ID_OFDLG_SAVE_BTN, OnOfdlgSaveBtn)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COneFieldDbDialog message handlers

void COneFieldDbDialog::OnOfdlgDeleteBtn() 
{
	int item, id;
	CString str;
	POSITION pos = this->m_OFDbList.GetFirstSelectedItemPosition();
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();

	CIncidencias2View *pIView = pFrame->GetIncidenciasFormView();
	CIncidenciasListView *pLiView = pFrame->GetIncidenciasListView();
	CComunicacionesView *pCoView =  pFrame->GetComunicacionesListView();

	CIncidencias2Set *pISet= &pIView->GetDocument()->m_incidencias2Set;
	COperariosSoporteSet *pOpSopSet= &pIView->GetDocument()->m_operariosSoporteSet;
	COperariosSet *pOSet= &pIView->GetDocument()->m_operariosSet;
	COperacionesSet *pOperSet= &pIView->GetDocument()->m_operacionesSet;
	CProveedoresSet *pProvSet= &pIView->GetDocument()->m_proveedoreSet;
	CComunicacionesSet *pCoSet= &pIView->GetDocument()->m_comunicacionesSet;

	if( !pos ) return;

	item = m_OFDbList.GetNextSelectedItem(pos); 
	str = m_OFDbList.GetItemText(item, 0);
	id = atoi(str.GetBuffer(0));

	if( id == 1 ){
		AfxMessageBox("Este registro es usado por el\nsistema, por favor no lo borre.", MB_OK |MB_ICONINFORMATION, 0);
		return;
	}

	switch( this->m_Type ){
		case OFBD_DLG_TYPE_OPERARIOS:			 
			if( pOSet->QueryOperario(id) ){
				if( pISet->QueryIncidenciasDelOperario(id) ){
					do{
						pISet->Edit();
						pISet->m_opid = 1;
						pISet->Update();
						pISet->MoveNext();
					}while(!pISet->IsEOF());
				}
				if( pCoSet->QueryComunicacionesDelOperario(id) ){
					do{
						pCoSet->Edit();
						pCoSet->m_opid = 1;
						pCoSet->Update();
						pCoSet->MoveNext();
					}while(!pCoSet->IsEOF());
				}
				pOSet->Delete();
			}
			UpdateListFromOperariosData();
			UpdateOtherViewsControls();
			//m_OFDbList.SetSelectionMark(item);
			break;
		case OFBD_DLG_TYPE_OPERARIOS_SOPORTE:			 
			if( pOpSopSet->QueryOperarioSoporte(id) ){
				if( pISet->QueryIncidenciasDelOperarioSoporte(id) ){
					do{
						pISet->Edit();
						pISet->m_opsid = 1;
						pISet->Update();
						pISet->MoveNext();
					}while(!pISet->IsEOF());
				}
				if( pCoSet->QueryComunicacionesDelOperarioSoporte(id) ){
					do{
						pCoSet->Edit();
						pCoSet->m_opsid = 1;
						pCoSet->Update();
						pCoSet->MoveNext();
					}while(!pCoSet->IsEOF());
				}
				pOpSopSet->Delete();
			}
			UpdateListFromOperariosSoporteData();
			UpdateOtherViewsControls();
			break;
		case OFBD_DLG_TYPE_OPERACIONES:
			if( pOperSet->QueryOperacion(id) ){
				if( pISet->QueryIncidenciasPorOperacion(id) ){
					do{
						pISet->Edit();
						pISet->m_opsid = 1;
						pISet->Update();
						pISet->MoveNext();
					}while(!pISet->IsEOF());
				}
				pOperSet->Delete();
			}
			UpdateListFromOperacionesData();
			UpdateOtherViewsControls();
			break;
		case OFB_DLG_TYPE_PROVEEDORES:
			if( pProvSet->QueryProveedor(id) ){
				if( pISet->QueryIncidenciasDelProveedor(id) ){
					do{
						pISet->Edit();
						pISet->m_pid = 1;
						pISet->Update();
						pISet->MoveNext();
					}while(!pISet->IsEOF());
				}
				pProvSet->Delete();
			}
			UpdateListFromProveedoresData();
			UpdateOtherViewsControls();
			break;
		default:
			TRACE("Bad dialog type one OneFieldDlg, check your programming !");
	}	
}

void COneFieldDbDialog::OnItemchangedOfdlgListDbItems(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	POSITION pos = m_OFDbList.GetFirstSelectedItemPosition();

	if(pos)
	{
		int item = m_OFDbList.GetNextSelectedItem(pos); 
		char pcItem[256];
		m_OFDbList.GetItemText(item, 1, pcItem, 255);
		this->m_OFDbNameEdit.SetWindowText(pcItem);
	}
	*pResult = 0;
}

void COneFieldDbDialog::OnOfdlgAddBtn() 
{
	CString str;

	this->m_OFDbNameEdit.GetWindowText(str);

	if( str.GetLength() == 0 ){
		AfxMessageBox("Cubra el campo \"nombre\"\nantes de cotinuar", MB_OK |MB_ICONINFORMATION, 0);
		m_OFDbNameEdit.SetFocus();
		return;
	}

	this->m_pSet->AddNew();
	this->m_pSet->SetFieldValue(1, str.GetBuffer(0));
	this->m_pSet->Update();

	UpdateListFromDb();
	UpdateOtherViewsControls();
}

void COneFieldDbDialog::OnOfdlgSaveBtn() 
{
	int item, id;
	CString str;
	POSITION pos = this->m_OFDbList.GetFirstSelectedItemPosition();
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();

	CIncidencias2View *pIView = pFrame->GetIncidenciasFormView();
	CIncidenciasListView *pLiView = pFrame->GetIncidenciasListView();
	CComunicacionesView *pCoView =  pFrame->GetComunicacionesListView();

	CIncidencias2Set *pISet= &pIView->GetDocument()->m_incidencias2Set;
	COperariosSoporteSet *pOpSopSet= &pIView->GetDocument()->m_operariosSoporteSet;
	COperariosSet *pOSet= &pIView->GetDocument()->m_operariosSet;
	COperacionesSet *pOperSet= &pIView->GetDocument()->m_operacionesSet;
	CProveedoresSet *pProvSet= &pIView->GetDocument()->m_proveedoreSet;

	if(!pos){
		AfxMessageBox("Seleccione un registro en la lista.", MB_OK, 0);
		return;
	}

	item = m_OFDbList.GetNextSelectedItem(pos); 
	str = m_OFDbList.GetItemText(item, 0);
	id = atoi(str.GetBuffer(0));

	switch( this->m_Type ){
		case OFBD_DLG_TYPE_OPERARIOS:			 
			if( pOSet->QueryOperario(id) ){
				pOSet->Edit();
				m_OFDbNameEdit.GetWindowText(str);
				pOSet->m_opnom = str;
				pOSet->Update();
			}
			UpdateListFromOperariosData();
			UpdateOtherViewsControls();
			//m_OFDbList.SetSelectionMark(item);
			break;
		case OFBD_DLG_TYPE_OPERARIOS_SOPORTE:			 
			if( pOpSopSet->QueryOperarioSoporte(id) ){
				pOpSopSet->Edit();
				m_OFDbNameEdit.GetWindowText(str);
				pOpSopSet->m_opnom = str;
				pOpSopSet->Update();
			}
			UpdateListFromOperariosSoporteData();
			UpdateOtherViewsControls();
			break;
		case OFBD_DLG_TYPE_OPERACIONES:
			if( pOperSet->QueryOperacion(id) ){
				pOperSet->Edit();
				m_OFDbNameEdit.GetWindowText(str);
				pOperSet->m_opnom = str;
				pOperSet->Update();
			}
			UpdateListFromOperacionesData();
			UpdateOtherViewsControls();
			break;
		case OFB_DLG_TYPE_PROVEEDORES:
			if( pProvSet->QueryProveedor(id) ){
				pProvSet->Edit();
				m_OFDbNameEdit.GetWindowText(str);
				pProvSet->m_pnom = str;
				pProvSet->Update();
			}
			UpdateListFromProveedoresData();
			UpdateOtherViewsControls();
			break;
		default:
			TRACE("Bad dialog type one OneFieldDlg, check your programming !");
	}	
}

void COneFieldDbDialog::UpdateOtherViewsControls(void)
{
	int  index;
	long id;
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	CIncidencias2View *pIView = pFrame->GetIncidenciasFormView();
	CComunicacionesView *pCView = pFrame->GetComunicacionesListView();
	CIncidenciasListView *pLiView = pFrame->GetIncidenciasListView();
	CIncidencias2Set *pISet = &pIView->GetDocument()->m_incidencias2Set;
	
	COperariosSet* pOperariosSet = &(pIView->GetDocument()->m_operariosSet);
	COperacionesSet* pOperacionesSet = &(pIView->GetDocument()->m_operacionesSet);
	CProveedoresSet* pProvSet = &(pIView->GetDocument()->m_proveedoreSet);

	switch( this->m_Type ){
		case OFBD_DLG_TYPE_OPERARIOS:
			if( (index = pIView->m_ComboOperario.GetCurSel()) != CB_ERR ){
				id =  pIView->m_ComboOperario.GetItemData(index);
				pIView->UpdateOperariosComboFromDb();
				if( pOperariosSet->QueryOperario(id) ) pIView->SetOperarioOnCombo(id);
				else pIView->SetOperarioOnCombo(1);
			}
			break;
		case OFBD_DLG_TYPE_OPERACIONES:
			if( (index = pIView->m_ComboOperacion.GetCurSel()) != CB_ERR ){
				id =  pIView->m_ComboOperacion.GetItemData(index);
				pIView->UpdateOperationsComboFromDb();
				if( pOperacionesSet->QueryOperacion(id) ) pIView->SetOperationOnCombo(id);
				else pIView->SetOperationOnCombo(1);
			}
			break;
		case OFB_DLG_TYPE_PROVEEDORES:
			if( (index = pIView->m_ComboProveedor.GetCurSel()) != CB_ERR ){
				pIView->UpdateSuppliersComboFromDb();
				id =  pIView->m_ComboProveedor.GetItemData(index);
				if( pProvSet->QueryProveedor(id) ) pIView->UpdateSuppliersComboFromDb();
				pIView->SetSupplierOnCombo(id);
			}
			break;
		default:
			TRACE("Bad dialog type one OneFieldDlg, check your programming !");
	}

	if( pLiView->m_lastInID > 0 ){
		pCView->UpdateViewForIncident(pLiView->m_lastInID);
		if( pISet->QueryIncidencia(pLiView->m_lastInID) ){
			pLiView->UpdateView();
			pLiView->SelectIncidentById(pLiView->m_lastInID);
		}

	}
}

void COneFieldDbDialog::UpdateListFromOperacionesData(void)
{
	m_OFDbList.DeleteAllItems();
	if( m_OperSet != NULL && m_OperSet->QueryAllOperaciones() ){
		int i=0;
		CString strF;
		do{
			strF.Format("%i", m_OperSet->m_opid);
			m_OFDbList.InsertItem(i, strF.GetBuffer(0));
			m_OFDbList.SetItemText(i,1,m_OperSet->m_opnom.GetBuffer(0));
			m_OperSet->MoveNext();
			i++;
		}while(!m_OperSet->IsEOF() );
	}
}

void COneFieldDbDialog::UpdateListFromOperariosData(void)
{
	m_OFDbList.DeleteAllItems();
	if( m_pOpSet != NULL && m_pOpSet->QueryAllOperarios() ){
		int i=0;
		CString strF;
		do{
			strF.Format("%i", m_pOpSet->m_opid);
			m_OFDbList.InsertItem(i, strF.GetBuffer(0));
			m_OFDbList.SetItemText(i,1,m_pOpSet->m_opnom.GetBuffer(0));
			m_pOpSet->MoveNext();
			i++;
		}while(!m_pOpSet->IsEOF() );
	}
}

void COneFieldDbDialog::UpdateListFromOperariosSoporteData(void)
{
	m_OFDbList.DeleteAllItems();
	if( m_pOpSopSet != NULL && m_pOpSopSet->QueryAllOperariosSoporte() ){
		int i=0;
		CString strF;
		do{
			strF.Format("%i", m_pOpSopSet->m_opsid);
			m_OFDbList.InsertItem(i, strF.GetBuffer(0));
			m_OFDbList.SetItemText(i,1,m_pOpSopSet->m_opnom.GetBuffer(0));
			m_pOpSopSet->MoveNext();
			i++;
		}while(!m_pOpSopSet->IsEOF() );
	}
}

void COneFieldDbDialog::UpdateListFromProveedoresData(void)
{
	m_OFDbList.DeleteAllItems();
	if( m_pProSet != NULL && m_pProSet->QueryAllProveedores() ){
		int i=0;
		CString strF;
		do{
			strF.Format("%i", m_pProSet->m_pid);
			m_OFDbList.InsertItem(i, strF.GetBuffer(0));
			m_OFDbList.SetItemText(i,1,m_pProSet->m_pnom.GetBuffer(0));
			m_pProSet->MoveNext();
			i++;
		}while(!m_pProSet->IsEOF() );
	}
}

void COneFieldDbDialog::UpdateListFromDb()
{
	switch( this->m_Type ){
		case OFBD_DLG_TYPE_OPERARIOS:
			UpdateListFromOperariosData();
			break;
		case OFBD_DLG_TYPE_OPERARIOS_SOPORTE:
			UpdateListFromOperariosSoporteData();
			break;
		case OFBD_DLG_TYPE_OPERACIONES:
			UpdateListFromOperacionesData();
			break;
		case OFB_DLG_TYPE_PROVEEDORES:
			UpdateListFromProveedoresData();
			break;
		default:
			TRACE("Bad dialog type one OneFieldDlg, check your programming !");
	}
}

BOOL COneFieldDbDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	CIncidenciasListView* pLIView = pFrame->GetIncidenciasListView();


	m_OFDbList.SetExtendedStyle(m_OFDbList.GetStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_OFDbList.InsertColumn(0,"id",LVCFMT_LEFT,20,-1);
	m_OFDbList.InsertColumn(1,"nombre",LVCFMT_LEFT,350,0);


	switch( this->m_Type ){
		case  OFBD_DLG_TYPE_OPERARIOS:
			SetWindowText("Editar Operarios");
			UpdateListFromOperariosData();
			pFrame->m_ofdDialogs[OFD_OPERARIOS_TYPE] = (CDialog*)this;
			break;
		case OFBD_DLG_TYPE_OPERARIOS_SOPORTE:
			SetWindowText("Editar Operarios de soporte");
			UpdateListFromOperariosSoporteData();
			pFrame->m_ofdDialogs[OFD_OPERARIOS_SOPORTE_TYPE] = (CDialog*)this;
			break;
		case OFBD_DLG_TYPE_OPERACIONES:
			SetWindowText("Editar Operaciones");
			UpdateListFromOperacionesData();
			pFrame->m_ofdDialogs[OFD_OPERACIONES_TYPE] = (CDialog*)this;
			break;
		case OFB_DLG_TYPE_PROVEEDORES:
			SetWindowText("Editar Proveedores");
			UpdateListFromProveedoresData();
			pFrame->m_ofdDialogs[OFD_PROVEEDORES_TYPE] = (CDialog*)this;
			break;
		default:
			TRACE("Bad dialog type one OneFieldDlg, check your programming !");
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COneFieldDbDialog::OnClose() 
{
	
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();

	switch( this->m_Type ){
		case  OFBD_DLG_TYPE_OPERARIOS:
			pFrame->m_ofdDialogs[OFD_OPERARIOS_TYPE] = NULL;
			break;
		case OFBD_DLG_TYPE_OPERARIOS_SOPORTE:
			pFrame->m_ofdDialogs[OFD_OPERARIOS_SOPORTE_TYPE] = NULL;
			break;
		case OFBD_DLG_TYPE_OPERACIONES:
			pFrame->m_ofdDialogs[OFD_OPERACIONES_TYPE] = NULL;
			break;
		case OFB_DLG_TYPE_PROVEEDORES:
			pFrame->m_ofdDialogs[OFD_PROVEEDORES_TYPE] = NULL;
			break;
		default:
			TRACE("Bad dialog type one OneFieldDlg, check your programming !");
	}
	
	CDialog::OnClose();
}

void COneFieldDbDialog::OnOK() 
{
	OnClose();
	
	CDialog::OnOK();
}
