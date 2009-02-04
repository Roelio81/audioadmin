#include "mainwindowimpl.h"
#include "printlabeldialogimpl.h"

MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f) 
	: QMainWindow(parent, f)
{
	setupUi(this);
	connect(actionEtiketten_afdrukken, SIGNAL(activated()), this, SLOT(printLabels()));
}

void MainWindowImpl::printLabels()
{
	PrintLabelDialogImpl *printLabelDialog = new PrintLabelDialogImpl(this);
	printLabelDialog->show();
}
