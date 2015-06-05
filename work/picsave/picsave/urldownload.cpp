
#include "urldownload.h"
#include <QObject>
#include <QEventLoop>
#include <QFileInfo>
#include <QTextCodec>
#include <QDebug>
#include <QStringList>


Download::Download(int index, QObject *pParent)
	: QObject(pParent), m_Index(index)
{

	m_HaveDoneBytes = 0;
	m_StartPoint = 0;
	m_EndPoint = 0;
	m_File = NULL;
	m_Reply = NULL;
}
void Download::StartDownload(const QUrl &url, QFile *file, qint64 startPoint/* =0 */, qint64 endPoint/* =-1 */)
{
	if( NULL == file )
		return;
	m_HaveDoneBytes = 0;
	m_StartPoint = startPoint;
	m_EndPoint = endPoint;
	m_File = file;
	//����HTTPЭ�飬д��RANGEͷ����˵�������ļ��ķ�Χ
	// ������ֶ��ұ��� m_Qnam.get(QNetworkRequest(url)); ����д���Ż��������������ھ�����д�ˣ�����֧�ֶ��߳�����
	
	/*QNetworkRequest qheader(url);
	QString range;
	range.sprintf("bytes=%lld-%lld", m_StartPoint, m_EndPoint);	
	qheader.setRawHeader("Range", range.toAscii());	
	//��ʼ����
	qDebug() << "Part " << m_Index << " start download from "<<m_StartPoint<<" to "<<m_EndPoint;	
	*/
	m_Reply = m_Qnam.get(QNetworkRequest(url));
	QNetworkReply::NetworkError ne = m_Reply->error();
	if (m_Reply && QNetworkReply::NoError == ne)
	{
		connect(m_Reply, SIGNAL(readyRead()), this, SLOT(HttpReadyRead()));
		connect(m_Reply, SIGNAL(finished()), this, SLOT(FinishedSlot()));		
	}
	else
	{
		qDebug() << "m_Reply failed!, error ="<<ne;
	}

}
void Download::StopDownload()
{
	if (m_Reply)
	{
		m_Reply->abort();
	}
}
//���ؽ���
void Download::FinishedSlot()
{   
	if (m_File != NULL)
	{
		m_File->flush();
		m_File = NULL;//���ֻ�Ǹ����棬����ֱ����NULL����	
	}
	if (m_Reply != NULL)
	{
		m_Reply->deleteLater();
		m_Reply = NULL;
	}
	
	//��Ϊm_HaveDoneBytesʵ��Ϊ (m_EndPoint-m_StartPoint+1)�����ԱȽ�ʱҪ��1
	bool bComplete =  (m_StartPoint+m_HaveDoneBytes-1==m_EndPoint);
	qDebug() << "Part " << m_Index << " download "<<m_HaveDoneBytes<<" bytes, complete = "<<bComplete;
	emit PartFinished(m_Index, bComplete);
}

void Download::HttpReadyRead()
{
	if (!m_File || !m_Reply)
	{
		emit PartFinished(m_Index, false);
		return;
	}
	if (QNetworkReply::NoError != m_Reply->error())
	{
		emit PartFinished(m_Index, false);
		return;
	}
	//����������Ϣд���ļ�
	QByteArray buffer = m_Reply->readAll();	
	m_File->seek( m_StartPoint + m_HaveDoneBytes );
	m_File->write(buffer);
	int nSize = buffer.size();
	m_HaveDoneBytes += nSize;
	emit PartProgress(m_Index, nSize);
}

DownloadControl::DownloadControl(QObject *pParent)
	: QObject(pParent)
{
	m_bFailed = false;
	m_ndlThreadCount = 0;
	m_nFinishedThreadNum = 0;
	m_nReqFileSize = 0;
	m_nDoneBytes = 0;
	m_pFileSave = NULL;
	m_strUrl = "";
	m_bStopDownload = false;

	qRegisterMetaType<emDownLoadErrorType>("emDownLoadErrorType");

}
DownloadControl::~DownloadControl()
{
	StopDownload();
}

//�������ķ�ʽ��ȡ�����ļ��ĳ���
void DownloadControl::GetFileInfo(QUrl url, qint64& fileLen, QDateTime& lastmodifiedTime )
{
	QNetworkAccessManager manager;	
	qDebug() << "Getting the file size...";
	QEventLoop loop;
	//�������󣬻�ȡĿ���ַ��ͷ����Ϣ
	QNetworkReply *pReply = manager.head(QNetworkRequest(url));
	if ( pReply == 0 )
	{
		fileLen = 0;
		return;
	}
	QObject::connect(pReply, SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);
	loop.exec();
	QVariant var = pReply->header(QNetworkRequest::ContentLengthHeader);
	QVariant varLastmodified = pReply->header(QNetworkRequest::LastModifiedHeader);
	
	pReply->deleteLater();
	pReply = NULL;
	Q_UNUSED(pReply);
	fileLen = var.toLongLong();
	qDebug() << "The file size is: " << fileLen;

	if ( !varLastmodified.isNull() )
	{
		lastmodifiedTime = varLastmodified.toDateTime();
	}
	qDebug() << "File last modifyed: " << lastmodifiedTime.toLocalTime().toString("yyyy/MM/dd hh:mm:ss");

}
qint64 DownloadControl::GetReqFileSize()
{
	return m_nReqFileSize;
}
QDateTime DownloadControl::GetFileLastModified()
{
	return m_fileLastModified;
}
QString DownloadControl::GetDownloadFile()//�������ص��ļ���
{
	if (m_pFileSave)
	{
		return m_pFileSave->fileName();
	}
	return "";
}
void DownloadControl::StopDownload()
{   
	m_bStopDownload = true;

	foreach (Download *pDLThread, m_lsDownloadThreads)
	{
		if (pDLThread)
		{
			pDLThread->StopDownload();
		}
	}
	m_lsDownloadThreads.clear();
	if (m_pFileSave)
	{
		m_pFileSave->close();
		m_pFileSave = NULL;
	}
}
bool DownloadControl::StartFileDownload(const QString &url, const QString &saveFile, int nCount)
{   
	m_bStopDownload = false;
	m_bFailed = false;
	m_ndlThreadCount = nCount;
	m_nFinishedThreadNum = 0;
	m_strUrl = url;
	//����ļ���Сʱȥ���������·��
	QStringList strl = url.split("/");
	QString tmpUrl = url;
	foreach(QString str, strl)
	{
		if(str == "proxy")
		{
			QString subStr = "/proxy/" + strl.value(strl.indexOf(str) + 1);
			tmpUrl.remove(subStr);
		}
	}
	m_Url = QUrl(tmpUrl);	
	m_nDoneBytes = 0;
	//m_nReqFileSize = static_cast<int>(GetFileSize(m_Url));
	GetFileInfo(m_Url, m_nReqFileSize, m_fileLastModified);
	if (m_nReqFileSize == 0)
	{
		m_bFailed = true;
		emit SignalDownloadFinished(m_strUrl, LOG_TYPE_NOTFOUNDFILE, m_fileLastModified);

		qDebug()<<"http file not found!";
		return false;
	}
	//�Ȼ���ļ�������
	//QFileInfo fileInfo(m_Url.path());
	QString fileName = saveFile;
	if (!m_pFileSave)
	{
		m_pFileSave = new QFile(this);
	}
	m_pFileSave->setFileName(fileName);
	//���ļ�
	if (!m_pFileSave->open(QIODevice::WriteOnly))
	{
		m_bFailed = true;		        
		emit SignalDownloadFinished(m_strUrl, LOG_TYPE_OPENFILEFAILED, m_fileLastModified);

		qDebug()<<"open file "<<fileName<<" for write failed";
		return false;
	}
	Download *tempDownload = NULL;
	//���ļ��ֳ�PointCount�Σ����첽�ķ�ʽ����
	qDebug() << "Start download file from " << url;
	int nPartBytes = m_nReqFileSize/m_ndlThreadCount;
	int nCurPos = 0;
	m_lsDownloadThreads.clear();
	for(int i=0; i<m_ndlThreadCount; i++)
	{
		//�����ÿ�εĿ�ͷ�ͽ�β��HTTPЭ������Ҫ����Ϣ��
		int nStart = nCurPos;		
		int nEnd = nStart + nPartBytes;	
		nCurPos = nEnd + 1;
		if (i == m_ndlThreadCount-1)
		{
			nEnd = m_nReqFileSize-1;//endҲ��λ�ã����ǳ��ȣ����������ļ������һ��λ���� m_nReqFileSize-1
		}
		//�ֶ����ظ��ļ�
		tempDownload = new Download(i+1, this);
		connect(tempDownload, SIGNAL(PartProgress(int, qint64)), this, SLOT(PriSlotOnPartProgress(int, qint64)));
		connect(tempDownload, SIGNAL(PartFinished(int, bool)), this, SLOT(PriSlotOnPartFinished(int, bool)));
		//connect(tempDownload, SIGNAL(DownloadFinished(int, bool)), tempDownload, SLOT(deleteLater()));
		tempDownload->StartDownload(m_Url, m_pFileSave, nStart, nEnd);
		m_lsDownloadThreads.push_back(tempDownload);
	}
	return true;
}
void DownloadControl::PriSlotOnPartFinished(int nIndex, bool bSucessful)
{
	if (m_bFailed)
	{
		return;
	}
	if (!bSucessful)
	{		
		m_bFailed = true;		        
		emit SignalDownloadFinished(m_strUrl, LOG_TYPE_THREADSDOWNDFAILED, m_fileLastModified);

		qDebug() << "some threads download failed";	
		return;
	}

	m_nFinishedThreadNum++;
	//�������������ļ���������˵���ļ�������ϣ��ر��ļ��������ź�
	if( m_nFinishedThreadNum == m_ndlThreadCount )
	{  
		if (m_pFileSave != NULL)
		{
			m_pFileSave->close();		
			SAFE_DELETE(m_pFileSave);
		}
		qDebug() << "Download finished";
		emit SignalDownloadFinished(m_strUrl, LOG_TYPE_TRUE, m_fileLastModified);
	}
}

void DownloadControl::PriSlotOnPartProgress(int nIndex, qint64 nCurRcvBytes)
{
	qDebug()<<"thread"<<nIndex<<" recv "<<nCurRcvBytes<<" Bytes";
	m_nDoneBytes += static_cast<int>(nCurRcvBytes);
	emit SignalProgress(m_strUrl, m_nDoneBytes, m_nReqFileSize);
	if (m_nDoneBytes >= m_nReqFileSize)
	{        
        //emit SignalDownloadFinished(m_strUrl, LOG_TYPE_TRUE);
	}
}


CLogFileDownloadControl::CLogFileDownloadControl(QObject* pParent /* = 0 */):
DownloadControl(pParent)
{

}

CLogFileDownloadControl::~CLogFileDownloadControl()
{

}

void CLogFileDownloadControl::PriSlotOnPartFinished(int nIndex, bool bSucessful)
{   
	if (m_bFailed)
	{
		return;
	}
	if (!bSucessful)
	{		
		m_bFailed = true;		        
		emit SignalDownloadFinished(m_strUrl, LOG_TYPE_THREADSDOWNDFAILED, m_fileLastModified);

		qDebug() << "some threads download failed";	
		return;
	}

	m_nFinishedThreadNum++;

	//�������������ļ���������˵���ļ�������ϣ��ر��ļ��������ź�
	if(m_nFinishedThreadNum == m_ndlThreadCount )
	{  
		if (m_pFileSave != NULL)
		{   
			QString strLogFile = m_pFileSave->fileName();
			m_pFileSave->close();		
			SAFE_DELETE(m_pFileSave);

			if (TranslateLogFileCodec(strLogFile,"utf8"))
			{
				qDebug() << "Download finished";
				emit SignalDownloadFinished(m_strUrl, LOG_TYPE_TRUE, m_fileLastModified);
			}
			else
			{
				emit SignalDownloadFinished(m_strUrl, LOG_TYPE_TRANSCODECFAILED, m_fileLastModified);
			}
		}
		else
		{
			emit SignalDownloadFinished(m_strUrl, LOG_TYPE_OPENFILEFAILED, m_fileLastModified);
		}
	}
}

bool CLogFileDownloadControl::TranslateLogFileCodec(QString strSrcLogFile,QString strSrcCodecName)
{
	QString strFileName = QFileInfo(strSrcLogFile).fileName(); //��־�ļ���
	QString strFileDir = QFileInfo(strSrcLogFile).absolutePath(); //��־�ļ�����Ŀ¼
	QString strDestLogFile = strFileDir + "_" + strFileName; //ת�������־�ļ�������ԭ�ļ��������ϼ��ַ�'_'

	bool bRst = false;
	if (TranslateFileToLocalCodec(strSrcLogFile,strDestLogFile,strSrcCodecName))
	{    
		//ת���ɹ���ɾ��ԭ��־�ļ�
		QFile::remove(strSrcLogFile);
		bRst = QFile::rename(strDestLogFile,strSrcLogFile);
	}
	else
	{   
		//ת��ʧ�ܺ�ɾ�����в�������ʱ�ļ�
		QFile::remove(strSrcLogFile);
		QFile::remove(strDestLogFile);
		bRst = false;
	}

	return bRst;
}

bool CLogFileDownloadControl::TranslateFileToLocalCodec(QString strSrcFile,QString strDestFile,QString strSrcCodecName)
{   
	QFile srcFile(strSrcFile);
	if (!srcFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return false;
	}

	QFile destFile(strDestFile);
	if (!destFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
	{
		return false;
	}

	QTextCodec* pSrcCodec = QTextCodec::codecForName(strSrcCodecName.toLocal8Bit().constData());
	QTextCodec* pLocalCodec = QTextCodec::codecForLocale();

	//���Դ�ļ������뱾��Ĭ�ϱ�����ͬ������ת��
	if (pSrcCodec != NULL &&
		pLocalCodec != NULL &&
		pSrcCodec->name() == pLocalCodec->name())
	{
		return true;
	}

	//Դ�ļ���,���ַ�������strSrcCodecNameָ��
	QTextStream srcTxtStream(&srcFile);
	srcTxtStream.setCodec(pSrcCodec);

	//ת�����Ŀ���ļ�����Ĭ��ʹ�õ�ǰϵͳ����
	QTextStream destTxtStream(&destFile);

	//ÿ�ν��б���ת�����ļ����С
	const int nTransBlockSize = 1024;

	QString strContent = "";
	while (!srcTxtStream.atEnd() && !m_bStopDownload)
	{
		strContent = srcTxtStream.read(nTransBlockSize);
		destTxtStream << strContent;
	}

	return true;
}
