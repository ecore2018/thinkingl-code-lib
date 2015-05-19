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
	const int GetElapse() const;
	void SetElapse(int timeElapseSecs);

private:
	QSettings* m_pSetting;
};

