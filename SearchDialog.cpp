/*
Copyright 2006, Yago Rubio Sanfiz

Copying and distribution of this file, with or without modification,
are permited in any medium without royalty, provided the copyright
and this notice are preserved.This file is offered as - is without
any warranty.
*/

// SearchDialog.cpp : implementation file
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
#include "OneFieldDbDialog.h"

#include "MainFrm.h"

#include "SearchDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchDialog dialog


CSearchDialog::CSearchDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSearchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchDialog)
	DDX_Control(pDX, IDC_SEARCH_DLG_EDIT_SEARCH_TERM, m_pEditSearchTerm);
	DDX_Control(pDX, IDC_SEARCH_DLG_COMBO_TABLE, m_pTableCombo);
	DDX_Control(pDX, IDC_SEARCH_DLG_COMBO_OPERATOR, m_pOperatorCombo);
	DDX_Control(pDX, IDC_SEARCH_DLG_COMBO_FIELD, m_pFieldCombo);
	DDX_Control(pDX, IDC_LIST_SEARCH_DLG_RESULTS, m_pResultsListCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchDialog, CDialog)
	//{{AFX_MSG_MAP(CSearchDialog)
	ON_BN_CLICKED(ID_SEARCH_DLG_BUSCAR, OnSearchDlgBuscar)
	ON_CBN_SELCHANGE(IDC_SEARCH_DLG_COMBO_TABLE, OnSelchangeSearchDlgComboTable)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SEARCH_DLG_RESULTS, OnDblclkListSearchDlgResults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchDialog message handlers

BOOL CSearchDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int tables, numtable = 0;
	CDaoTableDefInfo info;
	
	m_pDB = new CDaoDatabase();

	m_pDB->Open("bd1.mdb");

	m_pSet = new CDaoRecordset();
	m_pSet->m_pDatabase = m_pDB;

	tables = m_pDB->GetTableDefCount();

	for(int i=0;i<tables;i++){
		m_pDB->GetTableDefInfo(i, info);
		if( info.m_strName.Find("MSys") != 0 ){			
			m_pTableCombo.InsertString(numtable, info.m_strName);
			m_pTableCombo.SetItemData(numtable, (DWORD)i);
			numtable++;
		}		
	}

	m_pResultsListCtrl.SetExtendedStyle(m_pResultsListCtrl.GetStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP);
	m_pResultsListCtrl.ModifyStyle(0, LVS_SINGLESEL|LVS_SHOWSELALWAYS);
	
	return TRUE;
}

bool IsNumber(const CString str)
{
	for(int i = 0; i < str.GetLength(); i++)
		if( str[i] < '0' || str[i] > '9' )	return false;
	return true;
}

void CSearchDialog::OnSearchDlgBuscar() 
{
	CString str, strQuery;
	CDaoFieldInfo info;
	COleDateTime oDate;
	int row = 0;

	if( m_pTableCombo.GetCurSel() == CB_ERR ) return;
	if( m_pFieldCombo.GetCurSel() == CB_ERR ) return;
	if( m_pOperatorCombo.GetCurSel() == CB_ERR ) return;

	if( m_pSet->IsOpen() ) m_pSet->Close();
	

	m_pEditSearchTerm.GetWindowText(str);

	if( str.GetLength() == 0 ){
		m_pTableCombo.GetWindowText(str);
		strQuery.Format("SELECT * FROM [%s]", str.GetBuffer(0));
	}else{
		CString strTable, strField, strOper;

		m_nTable = m_pTableCombo.GetCurSel();
		m_nField = m_pFieldCombo.GetCurSel();

		m_pTableCombo.GetWindowText(strTable);
		m_pFieldCombo.GetWindowText(strField);
		m_pOperatorCombo.GetWindowText(strOper);


		strQuery = "SELECT * FROM [" + strTable + "]";		
		m_pSet->Open(dbOpenDynaset, strQuery.GetBuffer(0));
		m_pSet->GetFieldInfo(strField.GetBuffer(0), info);

		switch( info.m_nType ){
			case dbBoolean:
				if( str == "si" ) str = "TRUE";
				else if( str == "no" ) str = "FALSE";
				else{
					AfxMessageBox("Este campo es de tipo booleano\nel termino de busqueda debe ser \"si\" o \"no\"",MB_OK,0);
					return;
				}
				break;
			case dbByte:
			case dbInteger:
			case dbLong:
			case dbSingle:
			case dbDouble:
				if( !IsNumber(str)){
					AfxMessageBox("Este campo es de tipo numérico\nel termino de busqueda debe ser un número",MB_OK,0);
					return;
				}
				break;
			case dbCurrency:
				AfxMessageBox("El sistema aun no está preparado\npara manejar monedas\n\n¡ Lo siento !",MB_OK,0);
				return;
				break;
			case dbDate:
				if( !oDate.ParseDateTime(str, VAR_DATEVALUEONLY) ){
					AfxMessageBox("Este campo es de tipo fecha\nel termino de busqueda debe\nser DIA/MES/AÑO",MB_OK,0);
					return;
				}
				str.Insert(0, "#");
				str.Insert(str.GetLength(), "#");
				break;
			case dbText:
				if( strOper == "=" ) strOper = " LIKE ";
				str.Insert(0, "\"");
				str.Insert(str.GetLength(), "\"");
				break;
			case dbLongBinary:
			case dbMemo:
				AfxMessageBox("El sistema aun no está preparado\npara manejar binarios grandes.\n\n¡ Lo siento !",MB_OK,0);
				return;
				break;
		}

		strQuery += " WHERE [" + strField + "]" + strOper +  str ;
	}

	//AfxMessageBox(strQuery, MB_OK, 0);

	if( m_pSet->IsOpen() ) m_pSet->Close();
	m_pSet->Open(dbOpenDynaset, strQuery);

	m_pResultsListCtrl.DeleteAllItems();

	int nColumnCount = m_pResultsListCtrl.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i=0;i < nColumnCount;i++)
	{
		m_pResultsListCtrl.DeleteColumn(0);
	}
		

	if(m_pSet->GetRecordCount() == 0){
		AfxMessageBox("No hay resultados para la búsqueda", MB_OK, 0);
		return;
	}

	int numfields = m_pSet->GetFieldCount();

	for(int i=0;i<numfields;i++){
		int len;
		m_pSet->GetFieldInfo(i, info);
		switch ( info.m_nType ){
			case dbBoolean:	
			case dbByte:
			case dbInteger:
			case dbLong:
			case dbSingle:
			case dbDouble:
				len = 50;
				break;
			case dbCurrency:
			case dbDate:
				len = 90;
				break;
			case dbText:
			case dbLongBinary:
			case dbMemo:
				len = 150;
				break;
			default:
				len = 80;
		}

		this->m_pResultsListCtrl.InsertColumn(i,info.m_strName,LVCFMT_LEFT,len,-1);
	}

	do{
		m_pResultsListCtrl.InsertItem(row,"");

		for(int i=0;i<numfields;i++){
			COleVariant val;
			COleDateTime date;
			
			m_pSet->GetFieldInfo(i, info);
			switch ( info.m_nType ){
				case dbBoolean:	
					m_pSet->GetFieldValue(i, val);
					str.Format("%s", val.boolVal?"si":"no");
					m_pResultsListCtrl.SetItemText(row, i, str.GetBuffer(0));
					break;
				case dbByte:
				case dbInteger:
				case dbLong:
				case dbSingle:
				case dbDouble:
				case dbCurrency:
					m_pSet->GetFieldValue(i, val);
					str.Format("%i", val.intVal);
					m_pResultsListCtrl.SetItemText(row, i, str.GetBuffer(0));
					break;
				case dbDate:
					m_pSet->GetFieldValue(i, val);
					date.ParseDateTime("1/1/1900"); //FIXME ugly hack to avoid invalid dates
					if( val.date < date ) continue;
					date = val.date;
					str = date.Format("%d/%m/%Y");
					m_pResultsListCtrl.SetItemText(row, i, str.GetBuffer(0));
					break;
				case dbText:
					m_pSet->GetFieldValue(i, val);
					if( val.bstrVal == NULL ) continue;
					str.Format("%s", val.bstrVal);
					m_pResultsListCtrl.SetItemText(row, i, str.GetBuffer(0));
					break;
				case dbLongBinary:
				case dbMemo:
					break;
			}
		}
		m_pSet->MoveNext();
		++row;
	}while( !m_pSet->IsEOF() );
}


void CSearchDialog::OnSelchangeSearchDlgComboTable() 
{
	int sel, numfields = 0;
	CString str;
	CDaoFieldInfo info;

	if( (sel = m_pTableCombo.GetCurSel()) == CB_ERR ) return;

	m_pTableCombo.GetWindowText(str);

	str.Insert(0, "SELECT * FROM [");
	str.Insert(str.GetLength(),"]"); 

	//AfxMessageBox(str, MB_OK,0 );

	if( m_pSet->IsOpen() ) m_pSet->Close();
	m_pSet->Open(dbOpenDynaset, str);
	
	numfields = m_pSet->GetFieldCount();

	m_pFieldCombo.ResetContent();

	for(int i=0;i<numfields;i++){
		m_pSet->GetFieldInfo(i, info);
		m_pFieldCombo.InsertString(i, info.m_strName);
		m_pFieldCombo.SetItemData(i, (DWORD)i);
	}
}


int SearchColumnOnListCtrl (CListCtrl *pListCtrl, int col, char* str)
{

	int nCount = pListCtrl->GetItemCount();
	int nItem = -1;

	for( int i = 0; i < nCount; i++ )	{
		if ( pListCtrl->GetItemText(i, col) == str )
		{
			nItem = i;
			break;
		}
	}

	return nItem;
}

void CSearchDialog::OnDblclkListSearchDlgResults(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos = m_pResultsListCtrl.GetFirstSelectedItemPosition();
	CMainFrame * pFrame = (CMainFrame*)AfxGetMainWnd();
	LVFINDINFO info;

	CIncidencias2View *pIView = pFrame->GetIncidenciasFormView();
	CComunicacionesView *pCView = pFrame->GetComunicacionesListView();
	
	CIncidenciasListView *pLiView = pFrame->GetIncidenciasListView();
	CIncidencias2Set* pISet = &pIView->GetDocument()->m_incidencias2Set;

	*pResult = 0;

	if(pos)
	{
		int item = m_pResultsListCtrl.GetNextSelectedItem(pos); 
		char pcItem[256];
		int id, index;
		CString str;

		m_pTableCombo.GetWindowText(str);

		// TABLA INCIDENCIAS
		if( str == "incidencias" ){
			m_pResultsListCtrl.GetItemText(item, 0, pcItem, 255);
			id = atoi(pcItem);

			info.flags = LVFI_STRING;
			info.psz = pcItem;
			
			index = pLiView->GetListCtrl().FindItem(&info);

			if( index >= 0 ){
				pLiView->GetListCtrl().EnsureVisible(index, false);
				pLiView->GetListCtrl().SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
				pLiView->GetListCtrl().SetSelectionMark(index) ;
			}else{
				AfxMessageBox("La incidencia debe haber sido eliminada.\n\nPor favor, refresque la búsqueda.", MB_OK | MB_ICONINFORMATION, 0);
			}
		}else if( str == "comunicaciones" ){ // TABLA COMUNICACIONES
			// id comunicacion
			m_pResultsListCtrl.GetItemText(item, 1, pcItem, 255);
			id = atoi(pcItem);

			info.flags = LVFI_STRING;
			info.psz = pcItem;
			
			index = pLiView->GetListCtrl().FindItem(&info);

			if( index >= 0 ){
				pLiView->GetListCtrl().EnsureVisible(index, false);
				pLiView->GetListCtrl().SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
				pLiView->GetListCtrl().SetSelectionMark(index) ;
			}else{
				AfxMessageBox("La incidencia debe haber sido eliminada.\n\nPor favor, refresque la búsqueda.", MB_OK | MB_ICONINFORMATION, 0);
				*pResult = 0;
				return;
			}

			// id incidencia
			m_pResultsListCtrl.GetItemText(item, 0, pcItem, 255);
			id = atoi(pcItem);

			info.flags = LVFI_STRING;
			info.psz = pcItem;

			index = pCView->GetListCtrl().FindItem(&info);

			if( index >= 0 ){
				pCView->GetListCtrl().SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
				pCView->GetListCtrl().SetSelectionMark(index) ;
			}else{
				AfxMessageBox("La comunicación debe haber sido eliminada.\n\nPor favor, refresque la búsqueda.", MB_OK | MB_ICONINFORMATION, 0);
				*pResult = 0;
				return;
			}
		}else if( str == "operarios" ){ // TABLA OPERARIOS
			COneFieldDbDialog *p_ofDlg;

			COperariosSet *pOpSet = &pIView->GetDocument()->m_operariosSet;	
			m_pResultsListCtrl.GetItemText(item, 0, pcItem, 255);
			id = atoi(pcItem);

			if( !pOpSet->QueryOperario(id) ){
				AfxMessageBox("El operario debe haber sido eliminado.\n\nPor favor, refresque la búsqueda.", MB_OK | MB_ICONINFORMATION, 0);
				return;
			}
			
			info.flags = LVFI_STRING;
			info.psz = pcItem;

			if( pFrame->m_ofdDialogs[OFD_OPERARIOS_TYPE] == NULL ){	
				p_ofDlg = new  COneFieldDbDialog(OFBD_DLG_TYPE_OPERARIOS, (CDaoRecordset*)pOpSet),
				p_ofDlg->Create(p_ofDlg->IDD);
				p_ofDlg->ShowWindow(SW_SHOW);
			}else{
				p_ofDlg = (COneFieldDbDialog*)pFrame->m_ofdDialogs[OFD_OPERARIOS_TYPE];
				p_ofDlg->FlashWindow(true);
				p_ofDlg->BringWindowToTop();
			}

			index = p_ofDlg->m_OFDbList.FindItem(&info);

			if( index >= 0 ){
				p_ofDlg->m_OFDbList.EnsureVisible(index, false);
				p_ofDlg->m_OFDbList.SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
				p_ofDlg->m_OFDbList.SetSelectionMark(index) ;
			}

		}else if( str == "operarios_soporte" ){ // TABLA OPERARIOS SOPORTE
			COneFieldDbDialog *p_ofDlg;

			COperariosSoporteSet *pOpSopSet = &pIView->GetDocument()->m_operariosSoporteSet;	
			m_pResultsListCtrl.GetItemText(item, 0, pcItem, 255);
			id = atoi(pcItem);

			if( !pOpSopSet->QueryOperarioSoporte(id) ){
				AfxMessageBox("El operario de soporte debe haber sido eliminado.\n\nPor favor, refresque la búsqueda.", MB_OK | MB_ICONINFORMATION, 0);
				return;
			}	

			info.flags = LVFI_STRING;
			info.psz = pcItem;

			if( pFrame->m_ofdDialogs[OFD_OPERARIOS_SOPORTE_TYPE] == NULL ){	
				p_ofDlg = new  COneFieldDbDialog(OFBD_DLG_TYPE_OPERARIOS_SOPORTE, (CDaoRecordset*)pOpSopSet),
				p_ofDlg->Create(p_ofDlg->IDD);
				p_ofDlg->ShowWindow(SW_SHOW);
			}else{
				p_ofDlg = (COneFieldDbDialog*)pFrame->m_ofdDialogs[OFD_OPERARIOS_SOPORTE_TYPE];
				p_ofDlg->FlashWindow(true);
				p_ofDlg->BringWindowToTop();
			}

			index = p_ofDlg->m_OFDbList.FindItem(&info);

			if( index >= 0 ){
				p_ofDlg->m_OFDbList.EnsureVisible(index, false);
				p_ofDlg->m_OFDbList.SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
				p_ofDlg->m_OFDbList.SetSelectionMark(index) ;
			}
		}else if( str == "proveedores" ){ // TABLA PROVEEDORES
			COneFieldDbDialog *p_ofDlg;

			CProveedoresSet *pProvSet = &pIView->GetDocument()->m_proveedoreSet;	
			m_pResultsListCtrl.GetItemText(item, 0, pcItem, 255);
			id = atoi(pcItem);

			if( !pProvSet->QueryProveedor(id) ){
				AfxMessageBox("El proveedor debe haber sido eliminado.\n\nPor favor, refresque la búsqueda.", MB_OK | MB_ICONINFORMATION, 0);
				return;
			}	

			info.flags = LVFI_STRING;
			info.psz = pcItem;

			if( pFrame->m_ofdDialogs[OFD_PROVEEDORES_TYPE] == NULL ){	
				p_ofDlg = new  COneFieldDbDialog(OFB_DLG_TYPE_PROVEEDORES, (CDaoRecordset*)pProvSet),
				p_ofDlg->Create(p_ofDlg->IDD);
				p_ofDlg->ShowWindow(SW_SHOW);
			}else{
				p_ofDlg = (COneFieldDbDialog*)pFrame->m_ofdDialogs[OFD_PROVEEDORES_TYPE];
				p_ofDlg->FlashWindow(true);
				p_ofDlg->BringWindowToTop();
			}

			index = p_ofDlg->m_OFDbList.FindItem(&info);

			if( index >= 0 ){
				p_ofDlg->m_OFDbList.EnsureVisible(index, false);
				p_ofDlg->m_OFDbList.SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
				p_ofDlg->m_OFDbList.SetSelectionMark(index) ;
			}
		}else if( str == "operaciones" ){ // TABLA PROVEEDORES
			COneFieldDbDialog *p_ofDlg;

			COperacionesSet *pOpSet = &pIView->GetDocument()->m_operacionesSet;	
			m_pResultsListCtrl.GetItemText(item, 0, pcItem, 255);
			id = atoi(pcItem);

			if( !pOpSet->QueryOperacion(id) ){
				AfxMessageBox("La operación debe haber sido eliminada.\n\nPor favor, refresque la búsqueda.", MB_OK | MB_ICONINFORMATION, 0);
				return;
			}

			info.flags = LVFI_STRING;
			info.psz = pcItem;

			if( pFrame->m_ofdDialogs[OFD_OPERACIONES_TYPE] == NULL ){	
				p_ofDlg = new  COneFieldDbDialog(OFBD_DLG_TYPE_OPERACIONES, (CDaoRecordset*)pOpSet),
				p_ofDlg->Create(p_ofDlg->IDD);
				p_ofDlg->ShowWindow(SW_SHOW);
			}else{
				p_ofDlg = (COneFieldDbDialog*)pFrame->m_ofdDialogs[OFD_OPERACIONES_TYPE];
				p_ofDlg->FlashWindow(true);
				p_ofDlg->BringWindowToTop();
			}

			index = p_ofDlg->m_OFDbList.FindItem(&info);

			if( index >= 0 ){
				p_ofDlg->m_OFDbList.EnsureVisible(index, false);
				p_ofDlg->m_OFDbList.SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED) ;
				p_ofDlg->m_OFDbList.SetSelectionMark(index) ;
			}
		}
		// end
	}
}
