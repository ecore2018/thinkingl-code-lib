#pragma once

/**
*	����ҵ��ģ����. ͬUI����.
*	+by lizhixing@2014-11-23
*/

#include "friend.h"

#include <string>
using namespace std;

#include <QRunnable>
#include <QObject>
#include <QtNetwork/QTcpServer>

class CVModel : public QObject
{
	Q_OBJECT
public:
	CVModel(void);
	~CVModel(void);

public:
	// �û���¼.
	bool Login(const QString& email, const QString& password);

	// ���һ���û�.
	bool AddUser( const string& ipAddr, int port );

	// ��ȡ�û�.
//	bool GetUser( int userInternalId, CUser& userInfo );

	// �������ض˿�,�ȴ������û�������.
	bool StartTcpService();
private slots:
	// ��ʱ����,�����û��б�.
	void PollFriendsList();



	//////////////////////////////////////////////////////////////////////////
	// ���û�������.
	void OnUserConnect();
	// �����������ݿ��Զ���.
	//void OnUserConnectReadyRead();
private:
	// ��ȡһ�������û���Task.
	//QRunnable* GetUserConnectTask();

private:
	// �û��б�.
	CFriendList m_userList;

	// ���յ�������, ��Ӧ���û�.
	CFriendList m_inConnectingUserList;

	// �ۼӵ��û��ڲ�ID.
	int m_maxUserInternalId;

	// �����û��б��õĵ�ǰ�α�.
	int m_curUserListPollIndex;

	// �������ط���˿ڵ�TCP Server����.
	QTcpServer m_tcpServer;
};

