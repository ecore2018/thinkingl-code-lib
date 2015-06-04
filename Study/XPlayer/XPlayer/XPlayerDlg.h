
// XPlayerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include <dshow.h>

// CXPlayerDlg �Ի���
class CXPlayerDlg : public CDialogEx
{
// ����
public:
	CXPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_XPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	IGraphBuilder *m_pGraph;
	IMediaControl *m_pControl;
	IMediaEvent* m_pEvent;

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
	afx_msg void OnBnClickedPlay();
	CEdit m_eidtLog;
	afx_msg void OnBnClickedShowlog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStop();
};
