#include "view_universum.h"
#include "view_etiketten.h"
#include "view_instellingen.h"
#include "view_meetgegevens.h"

#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

using namespace View;

Universum::Universum(::QWidget *parent, Qt::WFlags f)
: QMainWindow(parent, f)
, m_dossier(*this)
, m_instellingen(this)
{
	setupUi(this);
	connect(actionEtiketten_afdrukken, SIGNAL(activated()), this, SLOT(printLabels()));
	connect(actionBackup_maken, SIGNAL(activated()), this, SLOT(backup()));
	connect(actionBackup_terugzetten, SIGNAL(activated()), this, SLOT(restore()));
	connect(actionInstellingen_wijzigen, SIGNAL(activated()), this, SLOT(instellingen()));
	connect(actionOmtrent, SIGNAL(activated()), this, SLOT(omtrent()));
	connect(meetgegevensButton, SIGNAL(clicked()), this, SLOT(meetgegevens()));
	connect(m_artsenLijst, SIGNAL(itemSelectionChanged(int, int, int, int)), this, SLOT(selecteerArts(int, int, int, int)));
	connect(m_klantenLijst, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(selecteerKlant(int, int, int, int)));
	connect(m_mutualiteitenLijst, SIGNAL(itemSelectionChanged(int, int, int, int)), this, SLOT(selecteerMutualiteit(int, int, int, int)));
	
	// De kolombreedtes wat aanpassen
	m_artsenLijst->setColumnWidth(0, 200);
	m_artsenLijst->setColumnWidth(1, 300);
	m_artsenLijst->setColumnWidth(2, 100);
	m_artsenLijst->setColumnWidth(3, 200);
	m_klantenLijst->setColumnWidth(0, 200);
	m_klantenLijst->setColumnWidth(1, 300);
	m_klantenLijst->setColumnWidth(2, 100);
	m_klantenLijst->setColumnWidth(3, 200);
	m_mutualiteitenLijst->setColumnWidth(0, 200);
	m_mutualiteitenLijst->setColumnWidth(1, 300);
	m_mutualiteitenLijst->setColumnWidth(2, 100);
	m_mutualiteitenLijst->setColumnWidth(3, 200);
}

Universum::~Universum()
{
}

Instellingen &Universum::getInstellingen()
{
	return m_instellingen;
}

Dossier &Universum::getDossier()
{
	return m_dossier;
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
	emit instellingenSignal();
}

void Universum::omtrent()
{
	::QMessageBox::about(this, "Omtrent AudioAdmin", "<p>AudioAdmin 2.0</p>"
		"<p>Vrijgegeven onder de GPL licentie, versie 3</p>"
		"<p>Februari 2009</p>");

}

void Universum::meetgegevens()
{
	Meetgegevens *meetgegevens = new Meetgegevens(this);
	meetgegevens->show();
}

void Universum::leegArtsenLijst()
{
	m_artsenLijst->clearContents();
}

void Universum::toevoegenArts(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
	m_artsenLijst->insertRow(id);
	m_artsenLijst->setCellWidget(id, 0, new QLabel(naam));
	m_artsenLijst->setCellWidget(id, 1, new QLabel(straat));
	m_artsenLijst->setCellWidget(id, 2, new QLabel(QString::number(postcode)));
	m_artsenLijst->setCellWidget(id, 3, new QLabel(gemeente));
	m_artsenLijst->resizeRowToContents(id);
}

void Universum::leegKlantenLijst()
{
	m_klantenLijst->clearContents();
}

void Universum::toevoegenKlant(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
	m_klantenLijst->insertRow(id);
	m_klantenLijst->setCellWidget(id, 0, new QLabel(naam));
	m_klantenLijst->setCellWidget(id, 1, new QLabel(straat));
	m_klantenLijst->setCellWidget(id, 2, new QLabel(QString::number(postcode)));
	m_klantenLijst->setCellWidget(id, 3, new QLabel(gemeente));
	m_klantenLijst->resizeRowToContents(id);
}

void Universum::leegMutualiteitenLijst()
{
	m_mutualiteitenLijst->clearContents();
}

void Universum::toevoegenMutualiteit(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
	m_mutualiteitenLijst->insertRow(id);
	m_mutualiteitenLijst->setCellWidget(id, 0, new QLabel(naam));
	m_mutualiteitenLijst->setCellWidget(id, 1, new QLabel(straat));
	m_mutualiteitenLijst->setCellWidget(id, 2, new QLabel(QString::number(postcode)));
	m_mutualiteitenLijst->setCellWidget(id, 3, new QLabel(gemeente));
	m_mutualiteitenLijst->resizeRowToContents(id);
}

void Universum::selecteerArts(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	if (currentRow != previousRow)
	{
		artsSelectieSignal(currentRow);
	}
}

void Universum::selecteerKlant(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	if (currentRow != previousRow)
	{
		klantSelectieSignal(currentRow);
	}
}

void Universum::selecteerMutualiteit(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	if (currentRow != previousRow)
	{
		mutualiteitSelectieSignal(currentRow);
	}
}

