// ConfigDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XPlayer.h"
#include "ConfigDialog.h"
#include "afxdialogex.h"


// CConfigDialog �Ի���

IMPLEMENT_DYNAMIC(CConfigDialog, CDialogEx)

CConfigDialog::CConfigDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfigDialog::IDD, pParent)
{

}

CConfigDialog::~CConfigDialog()
{
}

void CConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConfigDialog, CDialogEx)
END_MESSAGE_MAP()


// CConfigDialog ��Ϣ�������
