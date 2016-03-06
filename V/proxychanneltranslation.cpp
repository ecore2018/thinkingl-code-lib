#include "proxychanneltranslation.h"
#include <QTcpSocket>

ProxyChannelTranslation::ProxyChannelTranslation(QObject *parent, QTcpSocket* localSock, QTcpSocket* remoteSock)
	: QObject(parent)
	, m_localSock(localSock)
	, m_remoteSock(remoteSock)
{
	connect(localSock, SIGNAL(readyRead()), SLOT(OnReadyRead()));
}

ProxyChannelTranslation::~ProxyChannelTranslation()
{

}

void ProxyChannelTranslation::OnReadyRead()
{
	QByteArray data = m_localSock->readAll();

	// ���ܡ�

	// ���ͳ�ȥ��
	m_remoteSock->write( data );
}
