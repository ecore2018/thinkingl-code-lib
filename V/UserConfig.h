#pragma once

#include <QStringList>
#include <QtSql/QSqlDatabase>
#include "Friend.h"

/** 
*	�����û���������Ϣ,ÿ���û������Լ�������.
*	+by lizhixing@2015-02-19
*/

class CUserConfig
{
public:
	CUserConfig( const QString& userId );
	~CUserConfig(void);

	//static CUserConfig* GetInstance();
	//static void DestroyInstance();

	// ��ʼ��.
	static bool Init();

	// ��ȡ�û����б�,��������Щ�û������ñ�����.
	static QStringList GetAllUserId();

	// ע��һ���û�. �����û���uuid.
	static bool RegisterUser( const QString& email, const QString& userName, const QString& password );


	// ͨ��uuid����ȡ.
	//static CUserConfig* GetUserConfig( const QString& userId );

	// ����û�����.
	static bool CheckUserPassword( const QString& email, const QString& password );

	// �û�ID.
	QString GetUserId();

	// �û�����.
	QString GetUserPassword();

	// �û���.
	QString GetUserName();

	// �û�EMAIL.
	QString GetUserEmail();

	//////////////////////////////////////////////////////////////////////////
	// �û��������ݵĴ洢.
	CFriendList GetAllFriends();

	// ���һ������.
	bool AddFriend( const CFriend& f);
	// ɾ��һ������.
	bool DelFriend( const QString& friendUuid );
	// ����һ�����ѵ���Ϣ.
	bool UpdateFriend(const CFriend& f);
	//////////////////////////////////////////////////////////////////////////

private:

	// �û�uuid.
	QString m_userId;
private:
	// ���ݿ����.
	static QSqlDatabase s_database;

	// ��������.
	static CUserConfig* s_instance;
};

