
// XPlayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XPlayer.h"
#include "XPlayerDlg.h"
#include "afxdialogex.h"
// �ĵ��μ� https://msdn.microsoft.com/en-us/library/windows/desktop/dd375454(v=vs.85).aspx

#include <dshow.h>

#pragma comment( lib, "Strmiids.lib")	// Exports class identifiers (CLSIDs) and interface identifiers (IIDs).
#pragma comment( lib, "Quartz.lib")		// Exports the AMGetErrorText function. If you do not call this function, this library is not required.

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CXPlayerDlg �Ի���



CXPlayerDlg::CXPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CXPlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CXPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_PLAY, &CXPlayerDlg::OnBnClickedPlay)
END_MESSAGE_MAP()


// CXPlayerDlg ��Ϣ�������

BOOL CXPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CXPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CXPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CXPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CXPlayerDlg::OnBnClickedPlay()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// CFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
	// 	LPCTSTR lpszDefExt = NULL,
	// 		LPCTSTR lpszFileName = NULL,
	// 		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	// 		LPCTSTR lpszFilter = NULL,
	// 		CWnd* pParentWnd = NULL,
	// 		DWORD dwSize = 0,
	// 		BOOL bVistaStyle = TRUE);
	HRESULT hr = CoInitialize(NULL);
	if ( FAILED( hr ) )
	{
		MessageBox(L"Initialize COM fail!");
		return;
	}

	IGraphBuilder *pGraph = NULL;
	IMediaControl *pControl = NULL;
	IMediaEvent* pEvent = NULL;

	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraph);
	if ( FAILED( hr ) )
	{
		MessageBox(L"Create the Filter Graph Manager fail!");
		return;
	}

	hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
	hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);


	CFileDialog dlg(TRUE, NULL, NULL, NULL, NULL, this);
	if (IDOK == dlg.DoModal())
	{
		CString filePath = dlg.GetPathName();

		hr = pGraph->RenderFile(filePath, NULL);
		if ( SUCCEEDED(hr))
		{
			// Run the graph
			hr = pControl->Run();
			if (SUCCEEDED(hr))
			{
				long evCode;
				pEvent->WaitForCompletion(INFINITE, &evCode);

			}
		}
	}

	pControl->Release();
	pEvent->Release();
	pGraph->Release();
	CoUninitialize();
}
