
// diskstudyDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CDiskStudyDlg �Ի���
class CDiskStudyDlg : public CDialogEx
{
// ����
public:
	CDiskStudyDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DISKSTUDY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	// ���´�����Ϣ.
	void UpdateDiskInfo();


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CComboBox m_combLogicalVolList;
	afx_msg void OnCbnSelchangeComboLogicalVolList();
	CString m_curPhysicalDriveName;
	CString m_strDiskInfo;
};
