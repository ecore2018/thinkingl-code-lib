#ifndef PICSAVE_H
#define PICSAVE_H

#include <QtWidgets/QMainWindow>
#include "ui_picsave.h"
#include "picsaveconfig.h"
#include <QSystemTrayIcon>
#include "urldownload.h"

class picsave : public QMainWindow
{
	Q_OBJECT

public:
	picsave(QWidget *parent = 0);
	~picsave();



public slots:
	// ȷ����ť
	void OnBtnOk();

	// ȡ����ť
	void OnBtnCancel();

	// ѡ���µı���λ��.
	void OnBtnChooseNewDir();
	// ��ͼƬ����Ŀ¼.
	void OnBtnOpenDir();

	// ��С��.

	// ϵͳ���̴���.
	void iconIsActived(QSystemTrayIcon::ActivationReason reason);
	// ��ʾ����.
	void OnTrayShow();
	// �˳�����.
	void OnTrayExit();

	// ���عر�,��Ϊ���ش���.
	void closeEvent(QCloseEvent *event);

	// �������.
	void OnDownloadFinished(QString url, emDownLoadErrorType code );
	// ���ؽ���.
	void OnDownloadProgress(QString url, qint64 cur, qint64 total);
private:
	// ��ȡ����,��ʾ��������.
	void ReadConfig();

	// ��ʱ����������ͼƬ��ʱ��.
	void OnCheckPicTimer();
private:
	Ui::picsaveClass ui;

	// ��������.
	CPicSaveConfig m_cfg;

	// ���ؿؼ�
	DownloadControl* m_pDownloader;

	// ��ʱ��, ��ʱ���ץ��ͼƬ.
	QTimer* m_pTimer;

	enum EWorkState
	{
		StateIdle,			// ��ʼ״̬.
		StateDownloadXML,	// ��������XML�ļ�.
		StateDownloadPic,	// ��������ͼƬ.
	};

	EWorkState m_curState;
};

#endif // PICSAVE_H
