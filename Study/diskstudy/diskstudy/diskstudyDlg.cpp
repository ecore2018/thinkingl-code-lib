
// diskstudyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "diskstudy.h"
#include "diskstudyDlg.h"
#include "afxdialogex.h"

#include "DiskHelper.h"
#include <sstream>

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


// CDiskStudyDlg �Ի���



CDiskStudyDlg::CDiskStudyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiskStudyDlg::IDD, pParent)
	, m_curPhysicalDriveName(_T(""))
	, m_strDiskInfo(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDiskStudyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LOGICAL_VOL_LIST, m_combLogicalVolList);
	DDX_Text(pDX, IDC_EDIT_PHYSICAL_DRIVE, m_curPhysicalDriveName);
	DDX_Text(pDX, IDC_EDIT_DISK_INFO, m_strDiskInfo);
}

BEGIN_MESSAGE_MAP(CDiskStudyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDiskStudyDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_LOGICAL_VOL_LIST, &CDiskStudyDlg::OnCbnSelchangeComboLogicalVolList)
END_MESSAGE_MAP()


// CDiskStudyDlg ��Ϣ�������

BOOL CDiskStudyDlg::OnInitDialog()
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

	// ��ȡ�����б�, ��䵽�б���.
	CLogicalVolList volList;
	::GetLogicalVolList(volList);
	for (size_t i = 0; i < volList.size(); ++i)
	{
		m_combLogicalVolList.AddString(volList[i].c_str());
	}
	m_combLogicalVolList.SetCurSel(0);

	// ����һ��.
	OnCbnSelchangeComboLogicalVolList();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDiskStudyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDiskStudyDlg::OnPaint()
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
HCURSOR CDiskStudyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDiskStudyDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CDiskStudyDlg::OnCbnSelchangeComboLogicalVolList()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	int curSel = m_combLogicalVolList.GetCurSel();

	CString curVol;
	m_combLogicalVolList.GetLBText(curSel, curVol);

	int physicalNum = ::GetPhysicalDriveNumberByLogicalVolName((LPCTSTR)curVol);
	if (physicalNum != -1)
	{
		m_curPhysicalDriveName = GetPhysicalDriveName(physicalNum).c_str();
	}
	else
	{
		m_curPhysicalDriveName = L"����Ӳ��!";
	}

	UpdateData(FALSE);

	this->UpdateDiskInfo();
}

void CDiskStudyDlg::UpdateDiskInfo()
{
	TDiskInfo diskInfo;
	bool bOk = ::GetDiskInfo((LPCTSTR)m_curPhysicalDriveName, diskInfo);

	if (!bOk)
	{
		m_strDiskInfo = L"��ȡ������Ϣʧ��!";
		UpdateData(FALSE);
		return;
	}

	std::wstringstream ss;
	ss << L"���̴�С:\t" << (long long)diskInfo.m_diskSize << L"\r\n";
	ss << L"������(Cylinders):\t" << diskInfo.m_cylinders << "\r\n";
	ss << L"ÿ�ŵ�������(Sectors Per Track):\t" << diskInfo.m_sectorsPerTrack << "\r\n";
	ss << L"������С(Bytes Per Sector):\t" << diskInfo.m_bytesPerSector << "\r\n";

	ss << L"ý������:\t";
	switch (diskInfo.m_mediaType)
	{
	case DiskMediaTypeFixHardDisk:
		ss << L"�̶�Ӳ��\r\n";
		break;
	case DiskMediaTypeRemovableMedia:
		ss << L"���ƶ�Ӳ��\r\n";
		break;
	default:
		ss << L"δ֪������:\t" << diskInfo.m_mediaTypeRaw << "\r\n";
		break;
	}

	// SMART Version��Ϣ.
	ss << L"IDE Devcie Map Raw(IDE��Ϣԭʼֵ):\t" << (void*)diskInfo.bIDEDeviceMap << "\r\n";
	ss << L"Capabilities Raw(������ԭʼֵ):\t" << (void*)diskInfo.fCapabilities << "\r\n";

	m_strDiskInfo = ss.str().c_str();

	UpdateData(FALSE);
}
