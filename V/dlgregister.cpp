#include "dlgregister.h"
#include <QMessageBox>
#include "UserConfig.h"

CDlgRegister::CDlgRegister(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.buttonRegister, SIGNAL(clicked()), SLOT(OnButtonRegister()));
}

CDlgRegister::~CDlgRegister()
{

}


void CDlgRegister::OnButtonRegister()
{
	QString email = ui.lineEditEmail->text();
	if (email.isEmpty())
	{
		QMessageBox::critical(this, tr("ע��ʧ��"), tr("Email����Ϊ��!"), QMessageBox::Ok);
		ui.lineEditEmail->setFocus();
		return;
	}

	QString name = ui.lineEditName->text();
	if (name.isEmpty())
	{
		QMessageBox::critical(this, tr("ע��ʧ��"), tr("��������Ϊ��"), QMessageBox::Ok);
		ui.lineEditName->setFocus();
		return;
	}

	QString password = ui.lineEditPassword->text();
	if (password.isEmpty())
	{
		QMessageBox::critical(this, tr("ע��ʧ��"), tr("���벻��Ϊ��"), QMessageBox::Ok);
		ui.lineEditPassword->setFocus();
		return;
	}

	// ����ע��.
	bool bOk = CUserConfig::RegisterUser(email, name, password);

	if (bOk)
	{
		// �ر�ע�ᴰ��.
		this->close();
	}
}