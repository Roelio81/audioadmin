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
, m_arts(*this)
, m_dossier(*this)
, m_mutualiteit(*this)
, m_instellingen(this)
{
	setupUi(this);
	connect(actionEtiketten_afdrukken, SIGNAL(activated()), this, SLOT(printLabels()));
	connect(actionBackup_maken, SIGNAL(activated()), this, SLOT(backup()));
	connect(actionBackup_terugzetten, SIGNAL(activated()), this, SLOT(restore()));
	connect(actionInstellingen_wijzigen, SIGNAL(activated()), this, SLOT(instellingen()));
	connect(actionOmtrent, SIGNAL(activated()), this, SLOT(omtrent()));
	connect(meetgegevensButton, SIGNAL(clicked()), this, SLOT(meetgegevens()));
	connect(m_artsenLijst, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(selecteerArts(int, int, int, int)));
	connect(m_klantenLijst, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(selecteerKlant(int, int, int, int)));
	connect(m_mutualiteitenLijst, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(selecteerMutualiteit(int, int, int, int)));
	connect(b_artsBewaren, SIGNAL(clicked()), this, SLOT(bewarenArts()));
	connect(b_artsToevoegen, SIGNAL(clicked()), this, SLOT(toevoegenArts()));
	connect(b_artsVerwijderen, SIGNAL(clicked()), this, SLOT(verwijderenArts()));
	connect(b_artsZoeken, SIGNAL(clicked()), this, SLOT(zoekenArts()));
	connect(b_dossierBewaren, SIGNAL(clicked()), this, SLOT(bewarenDossier()));
	connect(b_dossierToevoegen, SIGNAL(clicked()), this, SLOT(toevoegenDossier()));
	connect(b_dossierVerwijderen, SIGNAL(clicked()), this, SLOT(verwijderenDossier()));
	connect(b_dossierZoeken, SIGNAL(clicked()), this, SLOT(zoekenDossier()));
	connect(b_mutualiteitBewaren, SIGNAL(clicked()), this, SLOT(bewarenMutualiteit()));
	connect(b_mutualiteitToevoegen, SIGNAL(clicked()), this, SLOT(toevoegenMutualiteit()));
	connect(b_mutualiteitVerwijderen, SIGNAL(clicked()), this, SLOT(verwijderenMutualiteit()));
	connect(b_mutualiteitZoeken, SIGNAL(clicked()), this, SLOT(zoekenMutualiteit()));
	connect(m_klantArts, SIGNAL(currentIndexChanged(int)), &m_dossier, SLOT(toonArtsAdres(int)));
	connect(b_artsBrief, SIGNAL(clicked()), &m_dossier, SLOT(toonBriefArts()));
	connect(b_klantBrief, SIGNAL(clicked()), &m_dossier, SLOT(toonBriefKlant()));
	connect(b_mutualiteitBrief, SIGNAL(clicked()), &m_dossier, SLOT(toonBriefMutualiteit()));
	connect(b_factuur, SIGNAL(clicked()), &m_dossier, SLOT(toonFactuur()));

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

Arts &Universum::getArts()
{
	return m_arts;
}

Dossier &Universum::getDossier()
{
	return m_dossier;
}

Mutualiteit &Universum::getMutualiteit()
{
	return m_mutualiteit;
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
	m_artsIdToIndex.clear();
	m_artsIndexToId.clear();
	m_dossier.leegArtsenLijst();
}

void Universum::toevoegenArts(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
	int index = m_artsenLijst->rowCount();
	m_artsIdToIndex[id] = index;
	m_artsIndexToId[index] = id;
	m_artsenLijst->insertRow(index);
	m_artsenLijst->setCellWidget(index, 0, new QLabel(naam));
	m_artsenLijst->setCellWidget(index, 1, new QLabel(straat));
	m_artsenLijst->setCellWidget(index, 2, new QLabel(QString::number(postcode)));
	m_artsenLijst->setCellWidget(index, 3, new QLabel(gemeente));
	m_artsenLijst->resizeRowToContents(index);
	m_dossier.toevoegenArts(id, naam, straat, QString::number(postcode) + " " + gemeente);
}

void Universum::leegKlantenLijst()
{
	m_klantenLijst->clearContents();
	m_klantIdToIndex.clear();
	m_klantIndexToId.clear();
}

void Universum::toevoegenKlant(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
	int index = m_klantenLijst->rowCount();
	m_klantIdToIndex[id] = index;
	m_klantIndexToId[index] = id;
	m_klantenLijst->insertRow(index);
	m_klantenLijst->setCellWidget(index, 0, new QLabel(naam));
	m_klantenLijst->setCellWidget(index, 1, new QLabel(straat));
	m_klantenLijst->setCellWidget(index, 2, new QLabel(QString::number(postcode)));
	m_klantenLijst->setCellWidget(index, 3, new QLabel(gemeente));
	m_klantenLijst->resizeRowToContents(index);
}

void Universum::leegMutualiteitenLijst()
{
	m_mutualiteitenLijst->clearContents();
	m_mutualiteitIdToIndex.clear();
	m_mutualiteitIndexToId.clear();
	m_klantMutualiteit->clear();
	m_klantMutualiteit->addItem("");
}

void Universum::toevoegenMutualiteit(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
	int index = m_mutualiteitenLijst->rowCount();
	m_mutualiteitIdToIndex[id] = index;
	m_mutualiteitIndexToId[index] = id;
	m_mutualiteitenLijst->insertRow(index);
	m_mutualiteitenLijst->setCellWidget(index, 0, new QLabel(naam));
	m_mutualiteitenLijst->setCellWidget(index, 1, new QLabel(straat));
	m_mutualiteitenLijst->setCellWidget(index, 2, new QLabel(QString::number(postcode)));
	m_mutualiteitenLijst->setCellWidget(index, 3, new QLabel(gemeente));
	m_mutualiteitenLijst->resizeRowToContents(index);
	m_klantMutualiteit->addItem(naam);
}

int Universum::artsIndexToId(int index) const
{
	return m_artsIndexToId.value(index, -1);
}

int Universum::artsIdToIndex(int id) const
{
	return m_artsIdToIndex.value(id, -1);
}

int Universum::mutualiteitIndexToId(int index) const
{
	return m_mutualiteitIndexToId.value(index, -1);
}

int Universum::mutualiteitIdToIndex(int id) const
{
	return m_mutualiteitIdToIndex.value(id, -1);
}

void Universum::selecteerArts(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	if (currentRow != previousRow)
	{
		emit artsSelectieSignal(m_artsIndexToId.value(currentRow, -1));
	}
}

void Universum::selecteerKlant(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	if (currentRow != previousRow)
	{
		emit klantSelectieSignal(m_klantIndexToId.value(currentRow, -1));
	}
}

void Universum::selecteerMutualiteit(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	if (currentRow != previousRow)
	{
		emit mutualiteitSelectieSignal(m_mutualiteitIndexToId.value(currentRow, -1));
	}
}

void Universum::bewarenArts()
{
}

void Universum::toevoegenArts()
{
}

void Universum::verwijderenArts()
{
}

void Universum::zoekenArts()
{
}

void Universum::bewarenDossier()
{
}

void Universum::toevoegenDossier()
{
}

void Universum::verwijderenDossier()
{
}

void Universum::zoekenDossier()
{
}

void Universum::bewarenMutualiteit()
{
}

void Universum::toevoegenMutualiteit()
{
}

void Universum::verwijderenMutualiteit()
{
}

void Universum::zoekenMutualiteit()
{
}
