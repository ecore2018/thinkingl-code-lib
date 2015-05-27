#pragma once
/**
*	����������ļ�.
*	+by lizhixing@2015-05-19
*/
#include <QString>
#include <QSettings>

class CPicSaveConfig
{
public:
	CPicSaveConfig();
	~CPicSaveConfig();

	// ��������ַ.
	const QString GetServerAddr() const;
	void SetServerAddr(const QString& addr);

	// ���ر���Ŀ¼.
	const QString GetPicSaveDir() const;
	void SetPicSaveDir(const QString& dir);

	// ץ��ʱ����.
	const int GetElapseSec() const;
	void SetElapse(int timeElapseSecs);

	// ���һ��ץ��ͼƬ��·��.
	void SetPicPath( const QString& devId, int chnId, const QString& path );
	QString GetPicPath(const QString& devId, int chnId);

	// ץ��ʱ�������.
	void SetTimeRange( const QTime& start, const QTime& end );
	void GetTimeRange(QTime& start, QTime& end);

private:
	// ƴ��ͼƬץ��·����Key.
	QString MakePicPathKey(const QString& devId, int chnId);
private:
	QSettings* m_pSetting;
};

