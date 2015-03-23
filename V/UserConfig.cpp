#include "UserConfig.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QtSql/QSqlError>

CUserConfig::CUserConfig(void)
{
}


CUserConfig::~CUserConfig(void)
{
}

bool CUserConfig::Init()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	//db.setHostName("VUserConfigDB");
	db.setDatabaseName("usercfg.db");


	bool bOk = db.open();
	Q_ASSERT( bOk );

	QStringList tList = db.tables();

	const QString tableNameDbInfo = "dbinfo";

	if( !tList.contains( tableNameDbInfo ) )
	{
		// �������ݱ�.
		// һ�����ݿⱾ����Ϣ�ı�.
		QSqlQuery sqlQuery(db);
		sqlQuery.prepare( "CREATE TABLE dbinfo(version TEXT PRIMARY KEY ASC);" );
		//	sqlQuery.bindValue( ":col1", "version" );
		bOk = sqlQuery.exec();

		// ����һ����¼,���ݿ�����ݰ汾.
		sqlQuery.exec( "INSERT INTO dbinfo(version) VALUES('1.0');" );

		if( !bOk )
		{
			QSqlError err = sqlQuery.lastError();
			QString strEr = err.text();
			Q_ASSERT( bOk );
		}
	}
	else
	{
		// ���°汾,�Ƿ���Ҫ
	}
	


	db.commit();

// 	db.setHostName("MyServer");
// 	db.setDatabaseName("C:\\test.gdb");

	return true;
}
