; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CScreenWordServerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ScreenWordServer.h"

ClassCount=4
Class1=CScreenWordServerApp
Class2=CScreenWordServerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SCREENWORDSERVER_DIALOG

[CLS:CScreenWordServerApp]
Type=0
HeaderFile=ScreenWordServer.h
ImplementationFile=ScreenWordServer.cpp
Filter=N

[CLS:CScreenWordServerDlg]
Type=0
HeaderFile=ScreenWordServerDlg.h
ImplementationFile=ScreenWordServerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ScreenWordServerDlg.h
ImplementationFile=ScreenWordServerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SCREENWORDSERVER_DIALOG]
Type=1
Class=CScreenWordServerDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STARTSERVER,button,1342242816
Control4=IDC_ENDSERVER,button,1342242816
Control5=IDC_PID,edit,1350631552
Control6=IDC_OUTPUT,edit,1350633600

