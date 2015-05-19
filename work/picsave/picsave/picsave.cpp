#include "picsave.h"

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
	m_cfg;
}

void picsave::OnBtnCancel()
{
	this->close();
}

void picsave::OnBtnChooseNewDir()
{

}

void picsave::OnBtnOpenDir()
{

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
	ui.lineEditElapse->setText(QString::number(elapse));

	// �����Զ�����.

}