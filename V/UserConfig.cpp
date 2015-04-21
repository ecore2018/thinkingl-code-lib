#include "UserConfig.h"
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QtSql/QSqlError>
#include <QtCore/qdebug.h>
#include <QtCore/QUuid>

CUserConfig* CUserConfig::s_instance = 0;
QSqlDatabase CUserConfig::s_database;

//CUserConfig* CUserConfig::GetInstance()
//{
//	if (0 == s_instance)
//	{
//		s_instance = new CUserConfig();
//	}
//	return s_instance;
//}
//
//void CUserConfig::DestroyInstance()
//{
//	if (s_instance)
//	{
//		delete s_instance;
//		s_instance = 0;
//	}
//}

CUserConfig::CUserConfig( const QString& userId )
	:m_userId( userId )
{
}


CUserConfig::~CUserConfig(void)
{
}

bool CUserConfig::Init()
{
	s_database = QSqlDatabase::addDatabase("QSQLITE");
	//s_database.setHostName("VUserConfigDB");
	s_database.setDatabaseName("usercfg.db");


	bool bOk = s_database.open();
	Q_ASSERT( bOk );

	QStringList tList = s_database.tables();

	const QString tableNameDbInfo = "dbinfo";

	if( !tList.contains( tableNameDbInfo ) )
	{
		// �������ݱ�.
		// һ�����ݿⱾ����Ϣ�ı�.
		// ���ݿⱾ�����Ϣ��Ƚϼ�,ֻ��һ���ֶ�, �汾.
		QSqlQuery sqlQuery(s_database);
		sqlQuery.prepare( "CREATE TABLE dbinfo(version TEXT PRIMARY KEY ASC);" );
		//	sqlQuery.bindValue( ":col1", "version" );
		bOk = sqlQuery.exec();

		// ����һ����¼,���ݿ�����ݰ汾.
		if (bOk)
		{
			bOk = sqlQuery.exec("INSERT INTO dbinfo(version) VALUES('1.0');");
		}

		if( !bOk )
		{
			QSqlError err = sqlQuery.lastError();
			QString strEr = err.text();
			qDebug() << "db operation fail! er: " << strEr;
			Q_ASSERT( bOk );
		}
		s_database.commit();
	}
	else
	{
		// ���°汾,�Ƿ���Ҫ����.
		// to be continued.
	}

	// �û���Ϣ��.
	const QString tableNameUser = "user";
	if (!tList.contains(tableNameUser))
	{
		// �����û���Ϣ��.
		// �ֶ�: �û�UUID ; �û���; �û�����; 
		QSqlQuery sqlCreateUserTable(s_database);
		bool bOk = sqlCreateUserTable.exec("CREATE TABLE user( uuid TEXT PRIMARY KEY, name TEXT, email TEXT UNIQUE, password TEXT);");
		if (!bOk)
		{
			qDebug() << "db operation fail! er: " << sqlCreateUserTable.lastError();
			Q_ASSERT(bOk);
		}
	}


// 	db.setHostName("MyServer");
// 	db.setDatabaseName("C:\\test.gdb");

	return true;
}

QString CUserConfig::GetUserId()
{
	Q_ASSERT(s_database.isValid());
	QSqlQuery sqlQuery(s_database);
	
	return "";
}

QStringList CUserConfig::GetAllUserId()
{
	Q_ASSERT(s_database.isValid());

	QStringList allUserId;
	QSqlQuery sqlQuery(s_database);
	sqlQuery.exec("select uuid from user;");
	while (sqlQuery.next())
	{
		QString userId = sqlQuery.value(0).toString();
		allUserId.push_back(userId);
	}
	return allUserId;
}

bool CUserConfig::RegisterUser(const QString& email, const QString& userName, const QString& password)
{
	QUuid uuid = QUuid::createUuid();

	QSqlQuery sqlQuery(s_database);
	sqlQuery.prepare("INSERT INTO user(uuid, email, name, password) VALUES(:uuid,:email,:name,:password);");
	sqlQuery.bindValue(":uuid", uuid.toString());
	sqlQuery.bindValue(":email", email);
	sqlQuery.bindValue(":name", userName);
	sqlQuery.bindValue(":password", password);
	bool bOk = sqlQuery.exec();
	if ( !bOk )
	{
		qDebug() << "Register user fail! er:" << sqlQuery.lastError().text();
	}
	return bOk;
}

bool CUserConfig::CheckUserPassword(const QString& email, const QString& password)
{
	QSqlQuery sqlQuery(s_database);
	sqlQuery.prepare("SELECT COUNT(0) from user where email=:email AND password=:password");
	sqlQuery.bindValue(":email", email);
	sqlQuery.bindValue(":password", password);
	bool bOk = sqlQuery.exec();
	if ( !bOk )
	{
		qDebug() << "Check user password sql error: " << sqlQuery.lastError().text();
	}

	if ( sqlQuery.next() )
	{
		int count = sqlQuery.value(0).toInt();
		return count > 0;
	}


	return bOk;
}

QString CUserConfig::GetUserEmail()
{
	QSqlQuery sqlQuery(s_database);
	sqlQuery.prepare("SELECT email from user where uuid=:uuid");
	sqlQuery.bindValue(":uuid", m_userId);
	bool bOk = sqlQuery.exec();
	if ( !bOk )
	{
		qDebug() << "sql: " << sqlQuery.lastQuery() << " er: " << sqlQuery.lastError().text();
		return "";
	}
	else
	{
		sqlQuery.next();
		QString email = sqlQuery.value(0).toString();
		return email;
	}
}

// CUserConfig* CUserConfig::GetUserConfig(const QString& userId)
// {
// 
// 	CUserConfig* pCfg = new CUserConfig( userId );
// 	return pCfg;
// }
