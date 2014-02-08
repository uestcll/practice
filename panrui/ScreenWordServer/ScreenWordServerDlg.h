// ScreenWordServerDlg.h : header file
//

#if !defined(AFX_SCREENWORDSERVERDLG_H__E1FED59A_6E49_4791_A753_24D2294BDE3C__INCLUDED_)
#define AFX_SCREENWORDSERVERDLG_H__E1FED59A_6E49_4791_A753_24D2294BDE3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PIPE_NAME L"\\\\.\\Pipe\\screenword"
/////////////////////////////////////////////////////////////////////////////
// CScreenWordServerDlg dialog

class CScreenWordServerDlg : public CDialog
{
// Construction
public:
	CScreenWordServerDlg(CWnd* pParent = NULL);	// standard constructor
	~CScreenWordServerDlg();
	HANDLE m_hPipe;
// Dialog Data
	//{{AFX_DATA(CScreenWordServerDlg)
	enum { IDD = IDD_SCREENWORDSERVER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScreenWordServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CScreenWordServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStartserver();
	afx_msg void OnEndserver();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	BOOL	m_continueFlag;
	CWinThread * m_observer;
	static	UINT MessageObserver(LPVOID pParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREENWORDSERVERDLG_H__E1FED59A_6E49_4791_A753_24D2294BDE3C__INCLUDED_)
