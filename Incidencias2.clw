; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CIncidencias2View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Incidencias2.h"
LastPage=0

ClassCount=17
Class1=CIncidencias2App
Class2=CIncidencias2Doc
Class3=CIncidencias2View
Class4=CMainFrame
Class6=CAboutDlg

ResourceCount=7
Resource1=IDD_INCIDENCIAS2_FORM
Resource2=IDD_ABOUTBOX
Class5=CIncidencias2Set
Class7=CCalendarDialog
Resource3=IDD_CALENDAR_DIALOG
Class8=CComunicacionesDialog
Resource4=IDD_ONEFIELD_DB_EDIT
Class9=COperariosSet
Class10=CProveedoresSet
Class11=CComunicacionesSet
Class12=CComunicacionesView
Class13=CIncidenciasListView
Class14=COperacionesSet
Class15=COperariosSoporteSet
Resource5=IDR_MAINFRAME
Class16=COneFieldDbDialog
Resource6=IDD_DIALOG_COMUNICACION
Class17=CSearchDialog
Resource7=IDD_SEARCH_DLG

[CLS:CIncidencias2App]
Type=0
HeaderFile=Incidencias2.h
ImplementationFile=Incidencias2.cpp
Filter=N
LastObject=CIncidencias2App

[CLS:CIncidencias2Doc]
Type=0
HeaderFile=Incidencias2Doc.h
ImplementationFile=Incidencias2Doc.cpp
Filter=N
LastObject=CIncidencias2Doc

[CLS:CIncidencias2View]
Type=0
HeaderFile=Incidencias2View.h
ImplementationFile=Incidencias2View.cpp
Filter=D
LastObject=IDC_INC_FRM_BITMAP
BaseClass=CDaoRecordView
VirtualFilter=XRVWC


[CLS:CIncidencias2Set]
Type=0
HeaderFile=Incidencias2Set.h
ImplementationFile=Incidencias2Set.cpp
Filter=N
BaseClass=CDaoRecordset
VirtualFilter=x
LastObject=CIncidencias2Set

[DB:CIncidencias2Set]
DB=1
DBType=DAO
ColumnCount=9
Column1=[inid], 4, 4
Column2=[innom], 12, 50
Column3=[indesc], 12, 255
Column4=[pid], 4, 4
Column5=[res], -7, 1
Column6=[opid], 4, 4
Column7=[opsid], 4, 4
Column8=[ifecini], 11, 8
Column9=[ifecres], 11, 8


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=Incidencias2.cpp
ImplementationFile=Incidencias2.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_PRINT
Command2=ID_FILE_PRINT_PREVIEW
Command3=ID_FILE_PRINT_SETUP
Command4=ID_APP_EXIT
Command5=ID_DB_OPERARIOS
Command6=ID_DB_OPERARIOS_SOPORTE
Command7=ID_DB_PROVEEDORES
Command8=ID_DB_OPERACIONES
Command9=ID_REPORT_INCIDENCIA
Command10=ID_RECORD_F
Command11=ID_RECORD_P
Command12=ID_RECORD_N
Command13=ID_RECORD_L
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_WINDOW_SPLIT
Command17=ID_APP_ABOUT
CommandCount=17

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=IDK_SELECT_INC_LIST_VIEW
Command2=IDK_SELECT_INC_FORM_VIEW
Command3=IDK_SELECT_COM_LIST_VIEW
Command4=ID_EDIT_COPY
Command5=ID_FILE_NEW
Command6=ID_FILE_OPEN
Command7=ID_FILE_PRINT
Command8=ID_FILE_SAVE
Command9=ID_EDIT_PASTE
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_CUT
Command17=ID_EDIT_UNDO
CommandCount=17

[DLG:IDD_INCIDENCIAS2_FORM]
Type=1
Class=CIncidencias2View
ControlCount=21
Control1=IDC_EDIT_DBDATE_START,edit,1350631552
Control2=IDC_BUTTON_CALMONTH,button,1342242816
Control3=IDC_EDIT_DBSUBJECT,edit,1350631552
Control4=IDC_COMBO_OPERARIO,combobox,1344339970
Control5=IDC_COMBO_OPERACION,combobox,1344340035
Control6=IDC_COMBO_PROVEEDOR,combobox,1344339971
Control7=IDC_EDIT_DB_DESC,edit,1352732676
Control8=IDC_CHECK_FINISHED,button,1342242819
Control9=IDC_EDIT_DBDATE_END,edit,1350631552
Control10=IDC_BUTTON_CALMONTH2,button,1342242816
Control11=IDC_BUTTON_SAVE_INCIDENCIAS2_FORM,button,1476460545
Control12=IDC_EDIT_DBID,edit,1350633600
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_INC_FRM_BITMAP,static,1342177294

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_DB_OPERARIOS
Command2=ID_DB_OPERARIOS_SOPORTE
Command3=ID_DB_OPERACIONES
Command4=ID_DB_PROVEEDORES
Command5=ID_DB_ADD_INCIDENCIA
Command6=ID_DB_NEW_COMUNICACION
Command7=ID_DB_DELETE_ACTIVE_REG
Command8=ID_CMD_SEARCH_DLG
Command9=ID_FILE_PRINT
Command10=ID_RECORD_F
Command11=ID_RECORD_P
Command12=ID_RECORD_N
Command13=ID_RECORD_L
Command14=ID_APP_ABOUT
CommandCount=14

[DB:CComunicarionesSet]
DB=1
DBType=DAO
ColumnCount=9
Column1=[coid], 4, 4
Column2=[inid], 4, 4
Column3=[opid], 4, 4
Column4=[opsid], 4, 4
Column5=[cont], -7, 1
Column6=[codesc], 12, 50
Column7=[resdesc], 12, 50
Column8=[cofec], 11, 8
Column9=[cofecresp], 11, 8

[DLG:IDD_DIALOG_COMUNICACION]
Type=1
Class=CComunicacionesDialog
ControlCount=20
Control1=IDC_COMBO_INCIDENCIAS,combobox,1344339970
Control2=IDC_COMBO_OPERARIOS,combobox,1344339970
Control3=IDC_COMBO_OPERARIOS_SOPORTE,combobox,1344339970
Control4=IDC_EDIT_FECHA_INICIO,edit,1350631552
Control5=IDC_BUTTON_FECHA_INICIO,button,1342242816
Control6=IDC_CHECK_ORIGEN_AQUI,button,1342242819
Control7=IDC_EDIT_DESCRIPCION_COM,edit,1352732676
Control8=IDC_CHECK_CONTESTADO,button,1342242819
Control9=IDC_EDIT_FECHA_CONTESTACION,edit,1350631552
Control10=IDC_BUTTON_FECHA_CONTESTACION,button,1342242816
Control11=IDC_EDIT_DESCRIPCION_RESP,edit,1352732676
Control12=IDCANCEL,button,1342242816
Control13=IDOK,button,1342242817
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,button,1342177287
Control20=IDC_STATIC,button,1342177287

[CLS:CComunicacionesDialog]
Type=0
HeaderFile=ComunicacionesDialog.h
ImplementationFile=ComunicacionesDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CComunicacionesDialog
VirtualFilter=dWC

[CLS:CComunicacionesView]
Type=0
HeaderFile=comunicacionesview.h
ImplementationFile=comunicacionesview.cpp
BaseClass=CListView
LastObject=CComunicacionesView
Filter=C
VirtualFilter=VWC

[DLG:IDD_CALENDAR_DIALOG]
Type=1
Class=CCalendarDialog
ControlCount=4
Control1=IDC_CALDLG_BUTTON_OK,button,1342242816
Control2=IDC_CALDLGBOTTON_CANCEL,button,1342242816
Control3=IDC_MONTHCALENDAR,SysMonthCal32,1342242816
Control4=IDC_STATIC,button,1342177287

[CLS:CCalendarDialog]
Type=0
HeaderFile=CalendarDialog.h
ImplementationFile=CalendarDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CCalendarDialog
VirtualFilter=dWC

[CLS:CComunicacionesSet]
Type=0
HeaderFile=comunicacionesset.h
ImplementationFile=comunicacionesset.cpp
BaseClass=CDaoRecordset
LastObject=CComunicacionesSet
Filter=N
VirtualFilter=x

[DB:CComunicacionesSet]
DB=1
DBType=DAO
ColumnCount=10
Column1=[coid], 4, 4
Column2=[inid], 4, 4
Column3=[opid], 4, 4
Column4=[opsid], 4, 4
Column5=[cont], -7, 1
Column6=[codesc], 12, 255
Column7=[resdesc], 12, 255
Column8=[cofec], 11, 8
Column9=[cofecresp], 11, 8
Column10=[coorig], -7, 1

[CLS:COperariosSet]
Type=0
HeaderFile=OperariosSet.h
ImplementationFile=OperariosSet.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x
LastObject=COperariosSet

[DB:COperariosSet]
DB=1
DBType=DAO
ColumnCount=2
Column1=[opid], 4, 4
Column2=[opnom], 12, 50

[CLS:CIncidenciasListView]
Type=0
HeaderFile=IncidenciasListView.h
ImplementationFile=IncidenciasListView.cpp
BaseClass=CListView
Filter=C
LastObject=CIncidenciasListView
VirtualFilter=VWC

[CLS:COperacionesSet]
Type=0
HeaderFile=OperacionesSet.h
ImplementationFile=OperacionesSet.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x
LastObject=COperacionesSet

[DB:COperacionesSet]
DB=1
DBType=DAO
ColumnCount=2
Column1=[opid], 4, 4
Column2=[opnom], 12, 50

[CLS:COperariosSoporteSet]
Type=0
HeaderFile=OperariosSoporteSet.h
ImplementationFile=OperariosSoporteSet.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x
LastObject=COperariosSoporteSet

[DB:COperariosSoporteSet]
DB=1
DBType=DAO
ColumnCount=2
Column1=[opsid], 4, 4
Column2=[opnom], 12, 50

[CLS:CProveedoresSet]
Type=0
HeaderFile=ProveedoresSet.h
ImplementationFile=ProveedoresSet.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x
LastObject=CProveedoresSet

[DB:CProveedoresSet]
DB=1
DBType=DAO
ColumnCount=2
Column1=[pid], 4, 4
Column2=[pnom], 12, 50

[DLG:IDD_ONEFIELD_DB_EDIT]
Type=1
Class=COneFieldDbDialog
ControlCount=7
Control1=IDC_OFDLG_EDIT_NAME,edit,1350631552
Control2=ID_OFDLG_ADD_BTN,button,1342242816
Control3=ID_OFDLG_SAVE_BTN,button,1342242816
Control4=IDC_OFDLG_LIST_DB_ITEMS,SysListView32,1350631433
Control5=IDC_OFDLG_DELETE_BTN,button,1342242816
Control6=IDOK,button,1342242817
Control7=IDC_STATIC,static,1342308352

[CLS:COneFieldDbDialog]
Type=0
HeaderFile=OneFieldDbDialog.h
ImplementationFile=OneFieldDbDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[DLG:IDD_SEARCH_DLG]
Type=1
Class=CSearchDialog
ControlCount=9
Control1=ID_SEARCH_DLG_BUSCAR,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SEARCH_DLG_COMBO_TABLE,combobox,1344339971
Control5=IDC_STATIC,static,1342308352
Control6=IDC_SEARCH_DLG_COMBO_FIELD,combobox,1344339971
Control7=IDC_SEARCH_DLG_COMBO_OPERATOR,combobox,1344339971
Control8=IDC_SEARCH_DLG_EDIT_SEARCH_TERM,edit,1350631552
Control9=IDC_LIST_SEARCH_DLG_RESULTS,SysListView32,1350631433

[CLS:CSearchDialog]
Type=0
HeaderFile=SearchDialog.h
ImplementationFile=SearchDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST_SEARCH_DLG_RESULTS

