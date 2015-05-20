/**
 **ʵ��ʹ�õ�ʱ��ֻ��Ҫʹ�� DownloadControl �༴�ɣ�Download��ֻ��һ�������̣߳���DownloadControl�ڲ�ʹ��
 **/
#ifndef urldownload_2013_2_27_h__
#define urldownload_2013_2_27_h__

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

enum emDownLoadErrorType
{
    LOG_TYPE_TRUE = 0,              //���سɹ�
    LOG_TYPE_NOTFOUNDFILE,          //û���ҵ��ļ�����������ʧ��
    LOG_TYPE_OPENFILEFAILED,        //���ļ�д��ʧ��
    LOG_TYPE_THREADSDOWNDFAILED,    //���߳�����ʧ��
	LOG_TYPE_TRANSCODECFAILED       //�ļ���ʽת��ʧ��
};

//���߳����ص��߳���������QT���ڴӹ��������ļ����������ε�bug��ԭ��δ֪��������Ŀǰֻ���õ��߳����أ���Ҫ�޸����ֵ zsy 20141016
const int PointCount = 1;
//���������ļ������ļ���һ���֣�
class Download : public QObject
{
	Q_OBJECT
private:
	QNetworkAccessManager m_Qnam;
	QNetworkReply *m_Reply;
	QFile *m_File;
	const int m_Index;
	qint64 m_HaveDoneBytes;
	qint64 m_StartPoint;
	qint64 m_EndPoint;
public:
	Download(int index, QObject *parent = 0);	
	void StartDownload(const QUrl &url, QFile *file, qint64 startPoint=0, qint64 endPoint=-1); 
	void StopDownload();
signals:
	void PartFinished(int nIndex, bool bSucessful);
	//�ϱ������յ����ֽ���
	void PartProgress(int nIndex, qint64 nCurRcvBytes);
public slots:
	void FinishedSlot();
	void HttpReadyRead();
};
//���ڹ����ļ�������
class DownloadControl : public QObject
{
	Q_OBJECT
protected:
	int m_ndlThreadCount;
	int m_nFinishedThreadNum;
	int m_nReqFileSize;
	int m_nDoneBytes;
	QUrl m_Url;
	QFile *m_pFileSave;
	bool m_bFailed;//�Ƿ��Ѿ���������ı��
	QString m_strUrl;//���ڱ�ʾ��ǰ���ض���
	QList<Download *> m_lsDownloadThreads;//�����߳�
	bool m_bStopDownload; //ֹͣ����
public:
	DownloadControl(QObject *parent = 0);
	virtual ~DownloadControl();
	bool StartFileDownload(const QString &url, const QString &saveFile, int count = PointCount);
	qint64 GetReqFileSize();//�����������ļ��ڷ������ϵĴ�С
	QString GetDownloadFile();//�������ص��ļ���
	void StopDownload();//ֹͣ����
private:
	qint64 GetFileSize(QUrl url);
signals:
	////���سɹ�֪ͨ����ʧ��֪ͨ��
    //@yu 2013.2.4 �޸� ��������ʾ�����룩
	//void SignalDownloadFinished(bool bSucessful);
    void SignalDownloadFinished(QString strUrl, emDownLoadErrorType emErrorType);

	//����֪ͨ���Ѿ�����ֽ���/���ֽ���
	void SignalProgress(QString strUrl, qint64 nDoneBytes, qint64 nTotalBytes);
public slots:
	virtual void PriSlotOnPartFinished(int nIndex, bool bSucessful);
	virtual void PriSlotOnPartProgress(int nIndex, qint64 nCurRcvBytes);
};

//������־�ļ�
class CLogFileDownloadControl : public DownloadControl
{
	Q_OBJECT
public:
	CLogFileDownloadControl(QObject* pParent = 0);
	virtual ~CLogFileDownloadControl();
public slots:
	virtual void PriSlotOnPartFinished(int nIndex, bool bSucessful);
private:
	bool TranslateFileToLocalCodec(QString strSrcFile,QString strDestFile,QString strSrcCodecName);
	bool TranslateLogFileCodec(QString strSrcLogFile,QString strSrcCodecName);
};

#endif // urldownload_2013_2_27_h__