#ifndef PICSAVE_H
#define PICSAVE_H

#include <QtWidgets/QMainWindow>
#include "ui_picsave.h"
#include "picsaveconfig.h"
#include <QSystemTrayIcon>
#include "urldownload.h"
#include <QString>
#include <QDomNode>

class CPicInfo
{
public:
	QString m_deviceId;
	int m_chnId;
	QString m_deviceName;
	QString m_picUrl;
};
typedef QList<CPicInfo> CPicInfoList;

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

	// �����Զ�����.
	void OnCheckAutoRun(int qtCheckBoxState);

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
	void OnDownloadFinished(QString url, emDownLoadErrorType code, QDateTime fileLastModified );
	// ���ؽ���.
	void OnDownloadProgress(QString url, qint64 cur, qint64 total);

	// ��ʱ����������ͼƬ��ʱ��.
	void OnCheckPicTimer();

	void RecreateDownloader();

	// ���ͼƬʱ��,�Ƿ���Ҫ����.
	void OnCheckPic();

	

private:
	// ��ȡ����,��ʾ��������.
	void ReadConfig();

	// ƴ���������ص�����URL.
	QString NormalizeUrl(const QString& serverAddr, const QString urlDir);

	// �������������ϵ�ͼƬ������Ϣ.
	CPicInfoList ParsePicInfo( QString xmlFileName );

	// ��ȡһ��XML�ڵ���ָ�����Ƶ��ӽڵ��ֵ.
	QString GetDomNodeValue(const QDomNode& node, const QString& tagName);
	
	// ���ͼƬ�Ƿ���Ҫ����.
	bool IsPicExpired(const QString& picPath);

	// ��ʼ����һ��ͼƬ.
	void StartDownloadPic(const CPicInfo& picInfo);

	// ƴ�ձ���ͼƬ.
	QString GetPicPath( const CPicInfo& picInfo );

	// ��������.
	void ResetAll();

	// �����Ƿ��Զ�������.
	bool IsAppAutoRun();

	// ���ó��򿪻����Զ�����.
	bool SetAppAutoRun( bool autoRun );

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

	// �ȴ�ץ�ĵ�ͼƬ
	CPicInfoList m_waittingPicList;

	QSystemTrayIcon* m_pTray;
};

#endif // PICSAVE_H

