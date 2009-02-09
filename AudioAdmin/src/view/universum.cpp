#include "universum.h"
#include "etiketten.h"
#include "instellingen.h"
#include "meetgegevens.h"

#include <QFileDialog>
#include <QMessageBox>

using namespace View;

Universum::Universum(::QWidget *parent, Qt::WFlags f)
: ::QMainWindow(parent, f)
{
	setupUi(this);
	connect(actionEtiketten_afdrukken, SIGNAL(activated()), this, SLOT(printLabels()));
	connect(actionBackup_maken, SIGNAL(activated()), this, SLOT(backup()));
	connect(actionBackup_terugzetten, SIGNAL(activated()), this, SLOT(restore()));
	connect(actionInstellingen_wijzigen, SIGNAL(activated()), this, SLOT(instellingen()));
	connect(actionOmtrend, SIGNAL(activated()), this, SLOT(omtrent()));
	connect(meetgegevensButton, SIGNAL(clicked()), this, SLOT(toonMeetgegevens()));
}

Universum::~Universum()
{
}

void Universum::toonMeetgegevens()
{
	Meetgegevens *meetgegevens = new Meetgegevens(this);
	meetgegevens->show();
}

void Universum::printLabels()
{
	Etiketten *etiketten = new Etiketten(this);
	etiketten->show();
}

void Universum::backup()
{
	::QStringList filters;
	filters << "XML files (*.xml)";
	::QFileDialog dialog(this, "Backup maken");
	dialog.setNameFilters(filters);
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	dialog.setDefaultSuffix("xml");
	::QString bestandsNaam = dialog.getSaveFileName();
	emit backupSignal(bestandsNaam);
}

void Universum::restore()
{
	::QStringList filters;
	filters << "XML files (*.xml)";
	::QFileDialog dialog(this, "Backup terugzetten");
	dialog.setNameFilters(filters);
	dialog.setAcceptMode(QFileDialog::AcceptOpen);
	dialog.setDefaultSuffix("xml");
	::QString bestandsNaam = dialog.getOpenFileName();
	emit restoreSignal(bestandsNaam);
}

void Universum::instellingen()
{
	Instellingen *instellingen = new Instellingen(this);
	instellingen->show();
}

void Universum::omtrent()
{
	::QMessageBox::about(this, "Omtrent AudioAdmin", "<p>AudioAdmin 2.0</p>"
		"<p>Vrijgegeven onder de GPL licentie, versie 3</p>"
		"<p>Februari 2009</p>");

}
