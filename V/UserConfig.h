#pragma once

#include <QStringList>
#include <QtSql/QSqlDatabase>

/** 
*	�����û���������Ϣ,ÿ���û������Լ�������.
*	+by lizhixing@2015-02-19
*/

class CUserConfig
{
public:
	CUserConfig(void);
	~CUserConfig(void);

	//static CUserConfig* GetInstance();
	//static void DestroyInstance();

	// ��ʼ��.
	static bool Init();

	// ��ȡ�û����б�,��������Щ�û������ñ�����.
	static QStringList GetAllUserId();

	// ע��һ���û�. �����û���uuid.
	static bool RegisterUser( const QString& email, const QString& userName, const QString& password );


	// ͨ������������ȡ.
	static CUserConfig* GetUserConfig( const QString& userId );

	// �û�ID.
	QString GetUserId();

	// �û�����.
	QString GetUserPassword();

	// �û���.
	QString GetUserName();

	// �û�EMAIL.
	QString GetUserEmail();

private:


private:
	// ���ݿ����.
	static QSqlDatabase s_database;

	// ��������.
	static CUserConfig* s_instance;
};

