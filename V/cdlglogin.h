#ifndef CDLGLOGIN_H
#define CDLGLOGIN_H

#include <QDialog>
#include "ui_cdlglogin.h"

class CVModel;
class CDlgLogin : public QDialog
{
	Q_OBJECT

public:
	CDlgLogin( CVModel* pModel, QWidget *parent = 0);
	~CDlgLogin();

private slots:

	// ע��.
	void OnButtonRegister();

	// ��¼.
	void OnButtonLogin();

private:
	// ˢ���û��б�.
	void UpdateUserList();

private:
	CVModel* m_pModel;
private:
	Ui::CDlgLogin ui;
};

#endif // CDLGLOGIN_H
