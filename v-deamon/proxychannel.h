#ifndef PROXYCHANNEL_H
#define PROXYCHANNEL_H

#include <QObject>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>

class ProxyChannel : public QObject
{
	Q_OBJECT

public:
	ProxyChannel(QObject *parent);
	~ProxyChannel();

	// ��ʼ�� ����localPort�� ���յ������ݼ���/���ܺ���remoteAddr:port
	void Start(int localPort, const QString& remoteAddr, int remotePort);

	void Stop();

private slots:
	void OnNewConnection();
private:
	QTcpServer m_server;

	typedef QSet<QTcpSocket*> QSocketSet;
	QSocketSet m_localTcpSocketTable;

	QString m_remoteAddr;
	int m_remotePort;
};

#endif // PROXYCHANNEL_H
