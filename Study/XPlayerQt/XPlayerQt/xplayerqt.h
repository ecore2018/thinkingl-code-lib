#ifndef XPLAYERQT_H
#define XPLAYERQT_H

#include <QtWidgets/QMainWindow>
#include "ui_xplayerqt.h"

#include <QMediaPlayer>

class XPlayerQt : public QMainWindow
{
	Q_OBJECT

public:
	XPlayerQt(QWidget *parent = 0);
	~XPlayerQt();

	// ��ʼ��.
	void InitPlayer();

	// �����ź�.
	void ConnectSignals();

private slots:
	// ���ļ�.
	void OnOpenFile();

private:
	Ui::XPlayerQtClass ui;

private:
	QMediaPlayer* m_pPlayer;
	QMediaPlaylist* m_pPlaylist;
	QVideoWidget* m_pVideoWidget;
};

#endif // XPLAYERQT_H
