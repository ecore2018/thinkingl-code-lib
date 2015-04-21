#include "vmainwin.h"
#include <QApplication>

#include "UserConfig.h"
#include "cdlglogin.h"
#include <qdialog.h>
#include <qtextcodec.h>

int main(int argc, char *argv[])
{
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));

	CUserConfig::Init();

	QApplication a(argc, argv);

	QTextCodec* locale = QTextCodec::codecForLocale();
	QString kkk = locale->name();
	//QTextCodec::setCodecForLocale(locale);
	//QTextCodec::(QTextCodec::codecForLocale());
	

	// ������¼����.
	CDlgLogin dlgLogin;
	int ret = dlgLogin.exec();
	if (ret == QDialog::Accepted)
	{
		// �����¼.

		CVMainWin w;
		w.show();
		ret = a.exec();
	}
	else
	{
		// �˳�����.
	}
//	CUserConfig::DestroyInstance();
	return ret;
}
