/*
Copyright 2006, Yago Rubio Sanfiz

Copying and distribution of this file, with or without modification,
are permited in any medium without royalty, provided the copyright
and this notice are preserved.This file is offered as - is without
any warranty.
*/
// Incidencias2Doc.h : interface of the CIncidencias2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INCIDENCIAS2DOC_H__DD5710A3_B8F3_4478_AD7E_20E447B1F9B7__INCLUDED_)
#define AFX_INCIDENCIAS2DOC_H__DD5710A3_B8F3_4478_AD7E_20E447B1F9B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CIncidencias2Doc : public CDocument
{
protected: // create from serialization only
	CIncidencias2Doc();
	DECLARE_DYNCREATE(CIncidencias2Doc)

// Attributes
public:
	CIncidencias2Set m_incidencias2Set;
	CComunicacionesSet m_comunicacionesSet;
	COperariosSet m_operariosSet;
	COperacionesSet m_operacionesSet;
	COperariosSoporteSet m_operariosSoporteSet;
	CProveedoresSet m_proveedoreSet;
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIncidencias2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIncidencias2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CIncidencias2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INCIDENCIAS2DOC_H__DD5710A3_B8F3_4478_AD7E_20E447B1F9B7__INCLUDED_)
