#include "mainwindowimpl.h"
#include "aboutdialogimpl.h"
#include "etikettendialogimpl.h"
#include "instellingendialogimpl.h"
#include <QFileDialog>

MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f) 
	: QMainWindow(parent, f)
{
	setupUi(this);
	connect(actionEtiketten_afdrukken, SIGNAL(activated()), this, SLOT(printLabels()));
	connect(actionBackup_maken, SIGNAL(activated()), this, SLOT(backup()));
	connect(actionBackup_terugzetten, SIGNAL(activated()), this, SLOT(restore()));
	connect(actionInstellingen_wijzigen, SIGNAL(activated()), this, SLOT(settings()));
	connect(actionOmtrend, SIGNAL(activated()), this, SLOT(about()));
}

void MainWindowImpl::printLabels()
{
	EtikettenDialogImpl *etikettenDialog = new EtikettenDialogImpl(this);
	etikettenDialog->show();
}

void MainWindowImpl::backup()
{
	QStringList filters;
	filters << "XML files (*.xml)";
	QFileDialog dialog(this, "Backup maken");
	dialog.setNameFilters(filters);
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	dialog.setDefaultSuffix("xml");
	QString bestandsNaam = dialog.getSaveFileName();
	emit backupSignal(bestandsNaam);
}

void MainWindowImpl::restore()
{
	QStringList filters;
	filters << "XML files (*.xml)";
	QFileDialog dialog(this, "Backup terugzetten");
	dialog.setNameFilters(filters);
	dialog.setAcceptMode(QFileDialog::AcceptOpen);
	dialog.setDefaultSuffix("xml");
	QString bestandsNaam = dialog.getOpenFileName();
	emit restoreSignal(bestandsNaam);
}

void MainWindowImpl::settings()
{
	InstellingenDialogImpl *instellingenDialog = new InstellingenDialogImpl(this);
	instellingenDialog->show();
}

void MainWindowImpl::about()
{
	AboutDialogImpl *aboutDialog = new AboutDialogImpl(this);
	aboutDialog->show();
}
