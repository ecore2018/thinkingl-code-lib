#include "vmainwin.h"
#include "dlgadduserbyaddress.h"
#include "cdlglogin.h"
#include <qevent.h>

CVMainWin::CVMainWin(CVModel* pModel, QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	, m_pModel( pModel )
{
	ui.setupUi(this);

	// ���Ӳ˵�/��������action.
	connect( ui.actionAddUserByAddress, SIGNAL(triggered()), this, SLOT( ConnectUserByAddress() ) );	// ����һ���û�.
}

CVMainWin::~CVMainWin()
{

}

void CVMainWin::ConnectUserByAddress()
{
	CDlgAddUserByAddress dlg( m_pModel, this );
	if( QDialog::Accepted == dlg.exec() )
	{
		
	}
}

void CVMainWin::closeEvent(QCloseEvent* event)
{
	event->accept();

	//this->quit();
}

void CVMainWin::Login()
{
	
}