// ScreenWordServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenWordServer.h"
#include "ScreenWordServerDlg.h"
#include "Tool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_BUFF 1024
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScreenWordServerDlg dialog

CScreenWordServerDlg::CScreenWordServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScreenWordServerDlg::IDD, pParent),m_continueFlag(TRUE)
{
	//{{AFX_DATA_INIT(CScreenWordServerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_observer = AfxBeginThread(MessageObserver,this,0,0);

}

CScreenWordServerDlg::~CScreenWordServerDlg()
{
	m_continueFlag = false;
	::WaitForSingleObject(m_observer->m_hThread,INFINITE);
}

void CScreenWordServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScreenWordServerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScreenWordServerDlg, CDialog)
	//{{AFX_MSG_MAP(CScreenWordServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STARTSERVER, OnStartserver)
	ON_BN_CLICKED(IDC_ENDSERVER, OnEndserver)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScreenWordServerDlg message handlers

BOOL CScreenWordServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScreenWordServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CScreenWordServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CScreenWordServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CScreenWordServerDlg::OnStartserver() 
{
	DWORD pid = 0;
	pid = GetDlgItemInt(IDC_PID);
	if(!InjectLibW(pid,_T("C:\\PROJECT\\ScreenWordServer\\ScreenWordHooker\\Debug\\ScreenWordHooker.dll")))
	{
		AfxMessageBox(_T("Start failed"));
	}
}

void CScreenWordServerDlg::OnEndserver() 
{
	DWORD pid = 0;
	pid = GetDlgItemInt(IDC_PID);	
	if(!EjectLibW(pid,_T("C:\\PROJECT\\ScreenWordServer\\ScreenWordHooker\\Debug\\ScreenWordHooker.dll")))	
	{
		AfxMessageBox(_T("End failed"));	
	}
}



UINT CScreenWordServerDlg::MessageObserver(LPVOID pParam)
{
	TCHAR buffer[MAX_BUFF] = {0};
	UINT ReadNum = 0;
	CScreenWordServerDlg * pDlg = (CScreenWordServerDlg *)pParam;

	pDlg->m_hPipe = CreateNamedPipe(PIPE_NAME, PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE|PIPE_READMODE_BYTE , 1, 0, 0, 1000, NULL);  
	
    if(pDlg->m_hPipe == INVALID_HANDLE_VALUE)  
    {  
		AfxMessageBox(L"Start Server error: cannot open pipe"); 
		exit(-1);
    }  	
	if(ConnectNamedPipe(pDlg->m_hPipe, NULL) == FALSE)
	{
		AfxMessageBox(L"error in connect");
	}
	while(pDlg->m_continueFlag)
	{
        if(ReadFile(pDlg->m_hPipe, buffer, sizeof(buffer), (unsigned long *)&ReadNum, NULL) == FALSE)  
        {  
			if(ConnectNamedPipe(pDlg->m_hPipe, NULL) == FALSE)
			{
				AfxMessageBox(L"error in connect");
			}
            if(ReadFile(pDlg->m_hPipe, buffer, sizeof(buffer), (unsigned long *)&ReadNum, NULL) == FALSE)
			{
				break;
			}
  
		}  
		
		buffer[ReadNum/2] = 0; 
		pDlg->SetDlgItemText(IDC_OUTPUT,buffer);

	}

	if(pDlg->m_hPipe != INVALID_HANDLE_VALUE)  
    {  
		CloseHandle(pDlg->m_hPipe);
    }  	

	AfxEndThread(0);
	return 0;
}