// ScreenWordServer.h : main header file for the SCREENWORDSERVER application
//

#if !defined(AFX_SCREENWORDSERVER_H__437AD3AF_214B_4DDC_9008_3DC03EAB8856__INCLUDED_)
#define AFX_SCREENWORDSERVER_H__437AD3AF_214B_4DDC_9008_3DC03EAB8856__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CScreenWordServerApp:
// See ScreenWordServer.cpp for the implementation of this class
//

class CScreenWordServerApp : public CWinApp
{
public:
	CScreenWordServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScreenWordServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CScreenWordServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREENWORDSERVER_H__437AD3AF_214B_4DDC_9008_3DC03EAB8856__INCLUDED_)
