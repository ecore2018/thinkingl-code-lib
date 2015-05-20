#ifndef PICSAVE_H
#define PICSAVE_H

#include <QtWidgets/QMainWindow>
#include "ui_picsave.h"
#include "picsaveconfig.h"
#include <QSystemTrayIcon>

class picsave : public QMainWindow
{
	Q_OBJECT

public:
	picsave(QWidget *parent = 0);
	~picsave();



public slots:
	// ȷ����ť
	void OnBtnOk();

	// ȡ����ť
	void OnBtnCancel();

	// ѡ���µı���λ��.
	void OnBtnChooseNewDir();
	// ��ͼƬ����Ŀ¼.
	void OnBtnOpenDir();

	// ��С��.

	// ϵͳ���̴���.
	void iconIsActived(QSystemTrayIcon::ActivationReason reason);
	// ��ʾ����.
	void OnTrayShow();
	// �˳�����.
	void OnTrayExit();

	void closeEvent(QCloseEvent *event);
private:
	// ��ȡ����,��ʾ��������.
	void ReadConfig();

private:
	Ui::picsaveClass ui;

	// ��������.
	CPicSaveConfig m_cfg;
};

#endif // PICSAVE_H
