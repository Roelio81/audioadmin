#include "mainwindowimpl.h"
#include "etikettendialogimpl.h"

MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f) 
	: QMainWindow(parent, f)
{
	setupUi(this);
	connect(actionEtiketten_afdrukken, SIGNAL(activated()), this, SLOT(printLabels()));
}

void MainWindowImpl::printLabels()
{
	EtikettenDialogImpl *etikettenDialog = new EtikettenDialogImpl(this);
	etikettenDialog->show();
}
