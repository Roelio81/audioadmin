#include "view_universum.h"
#include "view_toevoegenarts.h"
#include "view_toevoegenklant.h"
#include "view_toevoegenmutualiteit.h"

#include <QCloseEvent>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

using namespace View;

namespace
{
    QDate ongeldigeDatum(1900, 1, 1);
}

Universum::Universum(::QWidget *parent, Qt::WFlags f)
: QMainWindow(parent, f)
, m_arts(*this)
, m_dossier(*this)
, m_mutualiteit(*this)
, m_instellingen(this)
, m_huidigeTab(0)
{
    setupUi(this);
    connect(actionBewaren, SIGNAL(triggered()), this, SLOT(bewaren()));
    connect(actionEtikettenAfdrukken, SIGNAL(triggered()), this, SLOT(etikettenAfdrukken()));
    connect(actionInstellingen_wijzigen, SIGNAL(triggered()), this, SLOT(instellingen()));
    connect(actionOmtrent, SIGNAL(triggered()), this, SLOT(omtrent()));
    connect(m_artsenLijst, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(selecteerArts(int, int, int, int)));
    connect(m_klantenLijst, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(selecteerKlant(int, int, int, int)));
    connect(m_mutualiteitenLijst, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(selecteerMutualiteit(int, int, int, int)));
    connect(b_artsToevoegen, SIGNAL(clicked()), this, SLOT(toevoegenArts()));
    connect(b_artsVerwijderen, SIGNAL(clicked()), this, SLOT(verwijderenArts()));
    connect(b_artsZoeken, SIGNAL(clicked()), this, SLOT(zoekenArts()));
    connect(b_dossierToevoegen, SIGNAL(clicked()), this, SLOT(toevoegenDossier()));
    connect(b_dossierVerwijderen, SIGNAL(clicked()), this, SLOT(verwijderenDossier()));
    connect(b_dossierZoeken, SIGNAL(clicked()), this, SLOT(zoekenDossier()));
    connect(b_mutualiteitToevoegen, SIGNAL(clicked()), this, SLOT(toevoegenMutualiteit()));
    connect(b_mutualiteitVerwijderen, SIGNAL(clicked()), this, SLOT(verwijderenMutualiteit()));
    connect(b_mutualiteitZoeken, SIGNAL(clicked()), this, SLOT(zoekenMutualiteit()));
    connect(m_rechterHoorapparaatMerk, SIGNAL(currentIndexChanged(int)), &m_dossier, SLOT(refreshRechterHoorapparaatLijst(int)));
    connect(m_linkerHoorapparaatMerk, SIGNAL(currentIndexChanged(int)), &m_dossier, SLOT(refreshLinkerHoorapparaatLijst(int)));
    connect(m_klantArts, SIGNAL(currentIndexChanged(int)), &m_dossier, SLOT(toonArts(int)));
    connect(m_klantMutualiteit, SIGNAL(currentIndexChanged(int)), &m_dossier, SLOT(toonMutualiteit(int)));
    connect(b_artsBrief, SIGNAL(clicked()), &m_dossier, SLOT(toonBriefArts()));
    connect(b_klantBrief, SIGNAL(clicked()), &m_dossier, SLOT(toonBriefKlant()));
    connect(b_mutualiteitBrief, SIGNAL(clicked()), &m_dossier, SLOT(toonBriefMutualiteit()));
    connect(b_factuur, SIGNAL(clicked()), &m_dossier, SLOT(toonFactuur()));
    connect(b_meetgegevens, SIGNAL(clicked()), &m_dossier, SLOT(toonMeetgegevens()));
    connect(m_tabs, SIGNAL(currentChanged(int)), this, SLOT(tabVeranderd(int)));

    // De kolombreedtes wat aanpassen
    m_artsenLijst->setColumnWidth(0, 50);
    m_artsenLijst->setColumnWidth(1, 300);
    m_artsenLijst->setColumnWidth(2, 300);
    m_artsenLijst->setColumnWidth(3, 100);
    m_artsenLijst->setColumnWidth(4, 200);
    m_artsenLijst->hideColumn(0);
    m_klantenLijst->setColumnWidth(0, 50);
    m_klantenLijst->setColumnWidth(1, 300);
    m_klantenLijst->setColumnWidth(2, 300);
    m_klantenLijst->setColumnWidth(3, 100);
    m_klantenLijst->setColumnWidth(4, 200);
    m_klantenLijst->hideColumn(0);
    m_mutualiteitenLijst->setColumnWidth(0, 50);
    m_mutualiteitenLijst->setColumnWidth(1, 300);
    m_mutualiteitenLijst->setColumnWidth(2, 300);
    m_mutualiteitenLijst->setColumnWidth(3, 100);
    m_mutualiteitenLijst->setColumnWidth(4, 200);
    m_mutualiteitenLijst->hideColumn(0);
}

Universum::~Universum()
{
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

Etiketten &Universum::getEtiketten()
{
    return m_etiketten;
}

Instellingen &Universum::getInstellingen()
{
    return m_instellingen;
}

void Universum::bewaren()
{
    emit bewarenSignal();
}

void Universum::etikettenAfdrukken()
{
    emit etikettenSignal();
}

void Universum::tabVeranderd(int nieuweTab)
{
    switch (m_huidigeTab)
    {
    case 0: emit sluitDossierTab(); break;
    case 1: emit sluitArtsTab(); break;
    case 2: emit sluitMutualiteitTab(); break;
    }

    m_huidigeTab = nieuweTab;

    switch (m_huidigeTab)
    {
    case 0: emit openDossierTab(); break;
    case 1: emit openArtsTab(); break;
    case 2: emit openMutualiteitTab(); break;
    }
}

void Universum::instellingen()
{
    emit instellingenSignal();
}

void Universum::omtrent()
{
    QMessageBox::about(this, "Omtrent AudioAdmin", "<p>AudioAdmin 2.0</p>"
        "<p>Vrijgegeven onder de GPL licentie, versie 3</p>"
        "<p>Januari 2011</p>");
}

void Universum::bewarenBijAfsluiten()
{
    QMessageBox msgBox;
    msgBox.setLocale(QLocale(QLocale::Dutch, QLocale::Belgium));
    msgBox.setText("Niet alle wijzigingen zijn reeds bewaard");
    msgBox.setInformativeText("Wenst u uw wijzigingen te bewaren?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
    msgBox.button(QMessageBox::Save)->setText("Bewaren");
    msgBox.button(QMessageBox::Discard)->setText("Afsluiten zonder bewaren");
    msgBox.setDefaultButton(QMessageBox::Save);
    if (msgBox.exec() == QMessageBox::Save)
        bewaren();
}

void Universum::markeerArtsenLijstStatus(bool wijzigingen)
{
    if (wijzigingen)
        m_tabs->setTabText(1, "Artsen*");
    else
        m_tabs->setTabText(1, "Artsen");
}

void Universum::leegArtsenLijst()
{
    m_artsenLijst->clearContents();
    m_dossier.leegArtsenLijst();
}

void Universum::toevoegenArts(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
    m_dossier.toevoegenArts(id, naam, straat, QString::number(postcode) + " " + gemeente);

    int index = m_artsenLijst->rowCount();
    m_artsenLijst->insertRow(index);
    m_artsenLijst->setItem(index, 0, new QTableWidgetItem(QString::number(id)));
    m_artsenLijst->item(index, 0)->setFlags(Qt::ItemIsSelectable);
    wijzigenArts(id, naam, straat, postcode, gemeente);
}

void Universum::wijzigenArts(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
    m_dossier.wijzigenArts(id, naam, straat, QString::number(postcode) + " " + gemeente);

    int index = artsIdToIndex(id);
    m_artsenLijst->setItem(index, 1, new QTableWidgetItem(naam));
    m_artsenLijst->setItem(index, 2, new QTableWidgetItem(straat));
    m_artsenLijst->setItem(index, 3, new QTableWidgetItem(QString::number(postcode)));
    m_artsenLijst->setItem(index, 4, new QTableWidgetItem(gemeente));
    m_artsenLijst->item(index, 1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_artsenLijst->item(index, 2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_artsenLijst->item(index, 3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_artsenLijst->item(index, 4)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_artsenLijst->resizeRowToContents(index);
}

void Universum::leegHoorapparatenLijst()
{
    m_hoorapparaatMerkToTypes.clear();
}

void Universum::toevoegenHoorapparaat(const QString &merk, const QString &type, double prijs, const QDate &datumPrijs)
{
    PrijsDatumInfo info(prijs, datumPrijs);
    if (m_hoorapparaatMerkToTypes[merk].find(type) != m_hoorapparaatMerkToTypes[merk].end())
    {
        if (m_hoorapparaatMerkToTypes[merk][type].second >= info.second)
            info = m_hoorapparaatMerkToTypes[merk][type];
    }
    m_hoorapparaatMerkToTypes[merk][type] = info;
}

void Universum::markeerKlantenLijstStatus(bool wijzigingen)
{
    if (wijzigingen)
        m_tabs->setTabText(0, "Dossiers*");
    else
        m_tabs->setTabText(0, "Dossiers");
}

void Universum::leegKlantenLijst()
{
    m_klantenLijst->clearContents();
    m_klantenLijst->setRowCount(0);
}

void Universum::toevoegenKlant(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
    int index = m_klantenLijst->rowCount();
    m_klantenLijst->insertRow(index);
    m_klantenLijst->setItem(index, 0, new QTableWidgetItem(QString::number(id)));
    m_klantenLijst->item(index, 0)->setFlags(Qt::ItemIsSelectable);
    wijzigenKlant(id, naam, straat, postcode, gemeente);
}

void Universum::wijzigenKlant(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
    int index = klantIdToIndex(id);
    m_klantenLijst->setItem(index, 1, new QTableWidgetItem(naam));
    m_klantenLijst->setItem(index, 2, new QTableWidgetItem(straat));
    m_klantenLijst->setItem(index, 3, new QTableWidgetItem(QString::number(postcode)));
    m_klantenLijst->setItem(index, 4, new QTableWidgetItem(gemeente));
    m_klantenLijst->item(index, 1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_klantenLijst->item(index, 2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_klantenLijst->item(index, 3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_klantenLijst->item(index, 4)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_klantenLijst->resizeRowToContents(index);
}

void Universum::markeerMutualiteitenLijstStatus(bool wijzigingen)
{
    if (wijzigingen)
        m_tabs->setTabText(2, "Mutualiteiten*");
    else
        m_tabs->setTabText(2, "Mutualiteiten");
}

void Universum::leegMutualiteitenLijst()
{
    m_mutualiteitenLijst->clearContents();
    m_klantMutualiteit->clear();
    m_klantMutualiteit->addItem("", QVariant(-1));
}

void Universum::toevoegenMutualiteit(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
    m_dossier.toevoegenMutualiteit(id, naam);

    int index = m_mutualiteitenLijst->rowCount();
    m_mutualiteitenLijst->insertRow(index);
    m_mutualiteitenLijst->setItem(index, 0, new QTableWidgetItem(QString::number(id)));
    m_mutualiteitenLijst->item(index, 0)->setFlags(Qt::ItemIsSelectable);
    wijzigenMutualiteit(id, naam, straat, postcode, gemeente);
}

void Universum::wijzigenMutualiteit(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
    m_dossier.wijzigenMutualiteit(id, naam);

    int index = mutualiteitIdToIndex(id);
    m_mutualiteitenLijst->setItem(index, 1, new QTableWidgetItem(naam));
    m_mutualiteitenLijst->setItem(index, 2, new QTableWidgetItem(straat));
    m_mutualiteitenLijst->setItem(index, 3, new QTableWidgetItem(QString::number(postcode)));
    m_mutualiteitenLijst->setItem(index, 4, new QTableWidgetItem(gemeente));
    m_mutualiteitenLijst->item(index, 1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_mutualiteitenLijst->item(index, 2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_mutualiteitenLijst->item(index, 3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_mutualiteitenLijst->item(index, 4)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_mutualiteitenLijst->resizeRowToContents(index);
}

int Universum::artsIndexToId(int index) const
{
    return m_artsenLijst->item(index, 0)->text().toInt();
}

int Universum::artsIdToIndex(int id) const
{
    for (int index = 0; index < m_artsenLijst->rowCount(); ++index)
    {
        if (artsIndexToId(index) == id)
            return index;
    }
    return -1;
}

int Universum::klantIndexToId(int index) const
{
    return m_klantenLijst->item(index, 0)->text().toInt();
}

int Universum::klantIdToIndex(int id) const
{
    for (int index = 0; index < m_klantenLijst->rowCount(); ++index)
    {
        if (klantIndexToId(index) == id)
            return index;
    }
    return -1;
}

int Universum::mutualiteitIndexToId(int index) const
{
    return m_mutualiteitenLijst->item(index, 0)->text().toInt();
}

int Universum::mutualiteitIdToIndex(int id) const
{
    for (int index = 0; index < m_mutualiteitenLijst->rowCount(); ++index)
    {
        if (mutualiteitIndexToId(index) == id)
            return index;
    }
    return -1;
}

QSet<QString> Universum::getMerkHoorapparaten() const
{
    return m_hoorapparaatMerkToTypes.keys().toSet();
}

QSet<QString> Universum::getTypeHoorapparaten(const QString &merk) const
{
    return m_hoorapparaatMerkToTypes[merk].keys().toSet();
}

void Universum::selecteerArts(int id)
{
    m_artsenLijst->setCurrentCell(artsIdToIndex(id), 1);
}

void Universum::selecteerKlant(int id)
{
    m_klantenLijst->setCurrentCell(klantIdToIndex(id), 1);
}

void Universum::selecteerMutualiteit(int id)
{
    m_mutualiteitenLijst->setCurrentCell(mutualiteitIdToIndex(id), 1);
}

void Universum::selecteerArts(int currentRow, int, int previousRow, int)
{
    b_artsVerwijderen->setEnabled(true);
    if (currentRow != previousRow)
    {
        emit artsSelectieSignal(artsIndexToId(currentRow));
    }
}

void Universum::selecteerKlant(int currentRow, int, int previousRow, int)
{
    b_dossierVerwijderen->setEnabled(true);
    if (currentRow != previousRow)
    {
        emit klantSelectieSignal(klantIndexToId(currentRow));
    }
}

void Universum::selecteerMutualiteit(int currentRow, int, int previousRow, int)
{
    b_mutualiteitVerwijderen->setEnabled(true);
    if (currentRow != previousRow)
    {
        emit mutualiteitSelectieSignal(mutualiteitIndexToId(currentRow));
    }
}

void Universum::toevoegenArts()
{
    ToevoegenArts dialog(this);
    if (dialog.exec() == QDialog::Accepted)
        emit artsToevoegenSignal(dialog.getVoornaam(), dialog.getNaam());
}

void Universum::verwijderenArts()
{
    int row = m_artsenLijst->currentRow();
    int column = m_artsenLijst->currentColumn();
    int id = artsIndexToId(m_artsenLijst->currentRow());
    emit artsVerwijderenSignal(id);
    m_artsenLijst->removeRow(row);
    if (row >= m_artsenLijst->rowCount())
        --row;
    m_artsenLijst->setCurrentCell(row, column);
    emit artsSelectieSignal(artsIndexToId(row));
}

void Universum::zoekenArts()
{
    static QString vorigeWaarde = "";
    bool ok = false;
    QString naam = QInputDialog::getText(this, "Zoek arts", "Naam:", QLineEdit::Normal, vorigeWaarde, &ok);
    if (ok && !naam.isEmpty())
    {
        vorigeWaarde = naam;
        int nofRows = m_artsenLijst->rowCount();
        int currentRow = m_artsenLijst->currentRow();
        for (int i = 0; i < nofRows; ++i)
        {
            int row =(i + currentRow + 1) % nofRows;
            QTableWidgetItem *naamCell = m_artsenLijst->item(row, 1);
            Q_ASSERT(naamCell);
            if (naamCell->text().contains(naam, Qt::CaseInsensitive))
            {
                m_artsenLijst->setCurrentCell(row, 1, QItemSelectionModel::ClearAndSelect);
                return;
            }
        }
    }
}

void Universum::toevoegenDossier()
{
    ToevoegenKlant dialog(this);
    if (dialog.exec() == QDialog::Accepted)
        emit klantToevoegenSignal(dialog.getVoornaam(), dialog.getNaam());
}

void Universum::verwijderenDossier()
{
    int row = m_klantenLijst->currentRow();
    int column = m_klantenLijst->currentColumn();
    int id = klantIndexToId(m_klantenLijst->currentRow());
    emit klantVerwijderenSignal(id);
    m_klantenLijst->removeRow(row);
    if (row >= m_klantenLijst->rowCount())
        --row;
    m_klantenLijst->setCurrentCell(row, column);
    emit klantSelectieSignal(klantIndexToId(row));
}

void Universum::zoekenDossier()
{
    static QString vorigeWaarde = "";
    bool ok = false;
    QString naam = QInputDialog::getText(this, "Zoek klant", "Naam:", QLineEdit::Normal, vorigeWaarde, &ok);
    if (ok && !naam.isEmpty())
    {
        vorigeWaarde = naam;
        int nofRows = m_klantenLijst->rowCount();
        int currentRow = m_klantenLijst->currentRow();
        for (int i = 0; i < nofRows; ++i)
        {
            int row =(i + currentRow + 1) % nofRows;
            QTableWidgetItem *naamCell = m_klantenLijst->item(row, 1);
            Q_ASSERT(naamCell);
            if (naamCell->text().contains(naam, Qt::CaseInsensitive))
            {
                m_klantenLijst->setCurrentCell(row, 1, QItemSelectionModel::ClearAndSelect);
                return;
            }
        }
    }
}

void Universum::toevoegenMutualiteit()
{
    ToevoegenMutualiteit dialog(this);
    if (dialog.exec() == QDialog::Accepted)
        emit mutualiteitToevoegenSignal(dialog.getNaam());
}

void Universum::verwijderenMutualiteit()
{
    int row = m_mutualiteitenLijst->currentRow();
    int column = m_mutualiteitenLijst->currentColumn();
    int id = mutualiteitIndexToId(m_mutualiteitenLijst->currentRow());
    emit mutualiteitVerwijderenSignal(id);
    m_mutualiteitenLijst->removeRow(row);
    if (row >= m_mutualiteitenLijst->rowCount())
        --row;
    m_mutualiteitenLijst->setCurrentCell(row, column);
    emit mutualiteitSelectieSignal(mutualiteitIndexToId(row));
}

void Universum::zoekenMutualiteit()
{
    static QString vorigeWaarde = "";
    bool ok = false;
    QString naam = QInputDialog::getText(this, "Zoek mutualiteit", "Naam:", QLineEdit::Normal, vorigeWaarde, &ok);
    if (ok && !naam.isEmpty())
    {
        vorigeWaarde = naam;
        int nofRows = m_mutualiteitenLijst->rowCount();
        int currentRow = m_mutualiteitenLijst->currentRow();
        for (int i = 0; i < nofRows; ++i)
        {
            int row =(i + currentRow + 1) % nofRows;
            QTableWidgetItem *naamCell = m_mutualiteitenLijst->item(row, 1);
            Q_ASSERT(naamCell);
            if (naamCell->text().contains(naam, Qt::CaseInsensitive))
            {
                m_mutualiteitenLijst->setCurrentCell(row, 1, QItemSelectionModel::ClearAndSelect);
                return;
            }
        }
    }
}

void Universum::closeEvent(QCloseEvent *event)
{
    emit afsluitenSignal();
    event->accept();
}
