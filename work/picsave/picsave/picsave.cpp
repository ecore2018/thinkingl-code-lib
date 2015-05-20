#include <windows.h>
#include <process.h>
#include "picsave.h"
#include <string>
#include <QDir>

using namespace std;

picsave::picsave(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// ��ȡ����.
	ReadConfig();

	// ��ť���źŰ�.
	connect(ui.pushButtonOK, SIGNAL(clicked()), SLOT(OnBtnOK()));	// OK
	connect(ui.pushButtonCancel, SIGNAL(clicked()), SLOT(OnBtnCancel()));	// ȡ��.
	connect(ui.pushButtonChooseNewDir, SIGNAL(clicked()), SLOT(OnBtnChooseNewDir()));	// ѡ����Ŀ¼.
	connect(ui.pushButtonOpenDir, SIGNAL(clicked()), SLOT(OnBtnOpenDir()));	// ��Ŀ¼.


}

picsave::~picsave()
{

}

void picsave::OnBtnOk()
{
	// ��������.

	// ��������ַ.
	QString addr = ui.lineEditServerAddr->text();
	m_cfg.SetServerAddr(addr);

	// ͼƬ����Ŀ¼.
	QString dir = ui.lineEditPicDir->text();
	m_cfg.SetPicSaveDir(dir);

	// ץ�ļ��
	int elapseMin = ui.lineEditPicDir->text().toInt();
	m_cfg.SetElapse(elapseMin * 60);

	// �����Զ�����.
	m_cfg;
}

void picsave::OnBtnCancel()
{
	this->close();
}

void picsave::OnBtnChooseNewDir()
{

}


// bool LocationFileInExplorer(IN CStringUtf8& filePath)
// {
// 	if (!IsFileExist(filePath))
// 	{
// 		assert(false && "�ļ�������!");
// 		return false;
// 	}
// 
// 	StringAnsi cmd = "Explorer /e,/select, ";
// 	cmd += Utf8ToAnsi(filePath);
// 
// 	UINT ret = WinExec(cmd.c_str(), SW_SHOWNORMAL);
// 	LOGLOW() << cmd << "\tret:" << ret;
// 	return ret > 31;
// }

void picsave::OnBtnOpenDir()
{
	QString dir = m_cfg.GetPicSaveDir();

	dir.replace('/', '\\');

	QDir().mkpath(dir);

	wstring cmd = L" /e, ";
	cmd += dir.toStdWString();
	ShellExecute(
		NULL,
		(L"open"),
		//NULL,
		(L"Explorer.exe"),
		cmd.c_str(), // (L"/e, d:\\pics"),
		NULL,
		SW_SHOWDEFAULT);
}

void picsave::ReadConfig()
{
	// ��������ַ.
	QString addr = m_cfg.GetServerAddr();
	ui.lineEditServerAddr->setText(addr);

	// ͼƬ����Ŀ¼.
	QString dir = m_cfg.GetPicSaveDir();
	ui.lineEditPicDir->setText(dir);

	// ץ�ļ��.
	int elapse = m_cfg.GetElapse();
	ui.lineEditElapse->setText(QString::number(elapse/60));

	// �����Զ�����.

}