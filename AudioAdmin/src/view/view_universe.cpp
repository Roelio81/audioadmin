#include "view_universe.h"
#include "view_adddialog.h"

#include <QCloseEvent>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

using namespace View;

Universe::Universe(QWidget *parent, Qt::WFlags f)
: QMainWindow(parent, f)
, m_arts(m_ui)
, m_file(*this)
, m_mutualiteit(m_ui)
, m_etiketten(this)
, m_instellingen(this)
, m_huidigeTab(0)
{
    m_ui.setupUi(this);
    connect(m_ui.actionBewaren, SIGNAL(triggered()), this, SLOT(bewaren()));
    connect(m_ui.actionEtikettenAfdrukken, SIGNAL(triggered()), this, SLOT(etikettenAfdrukken()));
    connect(m_ui.actionInstellingen_wijzigen, SIGNAL(triggered()), this, SLOT(settings()));
    connect(m_ui.actionOmtrent, SIGNAL(triggered()), this, SLOT(omtrent()));
    connect(m_ui.m_artsenLijst, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(selectPhysician(int, int, int, int)));
    connect(m_ui.m_klantenLijst, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(selectCustomer(int, int, int, int)));
    connect(m_ui.m_mutualiteitenLijst, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(selectInsuranceCompany(int, int, int, int)));
    connect(m_ui.b_artsToevoegen, SIGNAL(clicked()), this, SLOT(addPhysician()));
    connect(m_ui.b_artsVerwijderen, SIGNAL(clicked()), this, SLOT(removePhysician()));
    connect(m_ui.b_artsZoeken, SIGNAL(clicked()), this, SLOT(findPhysician()));
    connect(m_ui.b_dossierToevoegen, SIGNAL(clicked()), this, SLOT(addFile()));
    connect(m_ui.b_dossierVerwijderen, SIGNAL(clicked()), this, SLOT(removeFile()));
    connect(m_ui.b_dossierZoeken, SIGNAL(clicked()), this, SLOT(findFile()));
    connect(m_ui.b_mutualiteitToevoegen, SIGNAL(clicked()), this, SLOT(addInsuranceCompany()));
    connect(m_ui.b_mutualiteitVerwijderen, SIGNAL(clicked()), this, SLOT(removeInsuranceCompany()));
    connect(m_ui.b_mutualiteitZoeken, SIGNAL(clicked()), this, SLOT(findInsuranceCompany()));
    connect(m_ui.m_rechterHoorapparaatMerk, SIGNAL(currentIndexChanged(int)), &m_file, SLOT(refreshRechterHoorapparaatLijst(int)));
    connect(m_ui.m_linkerHoorapparaatMerk, SIGNAL(currentIndexChanged(int)), &m_file, SLOT(refreshLinkerHoorapparaatLijst(int)));
    connect(m_ui.m_klantArts, SIGNAL(currentIndexChanged(int)), &m_file, SLOT(showPhysician(int)));
    connect(m_ui.m_klantMutualiteit, SIGNAL(currentIndexChanged(int)), &m_file, SLOT(toonMutualiteit(int)));
    connect(m_ui.b_artsBrief, SIGNAL(clicked()), &m_file, SLOT(toonBriefArts()));
    connect(m_ui.b_klantBrief, SIGNAL(clicked()), &m_file, SLOT(toonBriefKlant()));
    connect(m_ui.b_mutualiteitBrief, SIGNAL(clicked()), &m_file, SLOT(toonBriefMutualiteit()));
    connect(m_ui.b_factuur, SIGNAL(clicked()), &m_file, SLOT(toonFactuur()));
    connect(m_ui.b_meetgegevens, SIGNAL(clicked()), &m_file, SLOT(toonMeetgegevens()));
    connect(m_ui.m_tabs, SIGNAL(currentChanged(int)), this, SLOT(tabVeranderd(int)));

    // De kolombreedtes wat aanpassen
    m_ui.m_artsenLijst->setColumnWidth(0, 50);
    m_ui.m_artsenLijst->setColumnWidth(1, 300);
    m_ui.m_artsenLijst->setColumnWidth(2, 300);
    m_ui.m_artsenLijst->setColumnWidth(3, 100);
    m_ui.m_artsenLijst->setColumnWidth(4, 200);
    m_ui.m_artsenLijst->hideColumn(0);
    m_ui.m_klantenLijst->setColumnWidth(0, 50);
    m_ui.m_klantenLijst->setColumnWidth(1, 300);
    m_ui.m_klantenLijst->setColumnWidth(2, 300);
    m_ui.m_klantenLijst->setColumnWidth(3, 100);
    m_ui.m_klantenLijst->setColumnWidth(4, 200);
    m_ui.m_klantenLijst->hideColumn(0);
    m_ui.m_mutualiteitenLijst->setColumnWidth(0, 50);
    m_ui.m_mutualiteitenLijst->setColumnWidth(1, 300);
    m_ui.m_mutualiteitenLijst->setColumnWidth(2, 300);
    m_ui.m_mutualiteitenLijst->setColumnWidth(3, 100);
    m_ui.m_mutualiteitenLijst->setColumnWidth(4, 200);
    m_ui.m_mutualiteitenLijst->hideColumn(0);
}

Universe::~Universe()
{
}

Physician &Universe::getArts()
{
    return m_arts;
}

File &Universe::getDossier()
{
    return m_file;
}

InsuranceCompany &Universe::getMutualiteit()
{
    return m_mutualiteit;
}

Etiketten &Universe::getEtiketten()
{
    return m_etiketten;
}

Settings &Universe::getInstellingen()
{
    return m_instellingen;
}

void Universe::bewaren()
{
    emit bewarenSignal();
}

void Universe::etikettenAfdrukken()
{
    emit etikettenSignal();
}

void Universe::tabVeranderd(int nieuweTab)
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

void Universe::settings()
{
    emit openSettings();
}

void Universe::omtrent()
{
    QMessageBox::about(this, tr("About AudioAdmin"), tr("<p>AudioAdmin 2.0</p>"
                       "<p>Released under the GNU General Public License v3.0</p>"
                       "<p>June 2011</p>"));
}

void Universe::bewarenBijAfsluiten()
{
    QMessageBox msgBox(this);
    msgBox.setText(tr("Not all changes were saved"));
    msgBox.setInformativeText(tr("Do you want to save your pending changes?"));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
    msgBox.button(QMessageBox::Save)->setText(tr("Save"));
    msgBox.button(QMessageBox::Discard)->setText(tr("Exit without Save"));
    msgBox.setDefaultButton(QMessageBox::Save);
    if (msgBox.exec() == QMessageBox::Save)
        bewaren();
}

void Universe::clearPhysicianList()
{
    m_ui.m_artsenLijst->clearContents();
    m_file.clearPhysicianList();
}

void Universe::addPhysician(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
    m_file.addPhysician(id, naam, straat, QString::number(postcode) + " " + gemeente);

    int index = m_ui.m_artsenLijst->rowCount();
    m_ui.m_artsenLijst->insertRow(index);
    m_ui.m_artsenLijst->setItem(index, 0, new QTableWidgetItem(QString::number(id)));
    m_ui.m_artsenLijst->item(index, 0)->setFlags(Qt::ItemIsSelectable);
    changePhysician(id, naam, straat, postcode, gemeente);
}

void Universe::changePhysician(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
    m_file.changePhysician(id, naam, straat, QString::number(postcode) + " " + gemeente);

    int index = artsIdToIndex(id);
    m_ui.m_artsenLijst->setItem(index, 1, new QTableWidgetItem(naam));
    m_ui.m_artsenLijst->setItem(index, 2, new QTableWidgetItem(straat));
    m_ui.m_artsenLijst->setItem(index, 3, new QTableWidgetItem(QString::number(postcode)));
    m_ui.m_artsenLijst->setItem(index, 4, new QTableWidgetItem(gemeente));
    m_ui.m_artsenLijst->item(index, 1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_artsenLijst->item(index, 2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_artsenLijst->item(index, 3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_artsenLijst->item(index, 4)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_artsenLijst->resizeRowToContents(index);
}

void Universe::leegHoorapparatenLijst()
{
    m_hoorapparaatMerkToTypes.clear();
}

void Universe::toevoegenHoorapparaat(const QString &merk, const QString &type, double prijs, const QDate &datumPrijs)
{
    PrijsDatumInfo info(prijs, datumPrijs);
    if (m_hoorapparaatMerkToTypes[merk].find(type) != m_hoorapparaatMerkToTypes[merk].end())
    {
        if (m_hoorapparaatMerkToTypes[merk][type].second >= info.second)
            info = m_hoorapparaatMerkToTypes[merk][type];
    }
    m_hoorapparaatMerkToTypes[merk][type] = info;
}

void Universe::leegKlantenLijst()
{
    m_ui.m_klantenLijst->clearContents();
    m_ui.m_klantenLijst->setRowCount(0);
}

void Universe::addCustomer(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
    int index = m_ui.m_klantenLijst->rowCount();
    m_ui.m_klantenLijst->insertRow(index);
    m_ui.m_klantenLijst->setItem(index, 0, new QTableWidgetItem(QString::number(id)));
    m_ui.m_klantenLijst->item(index, 0)->setFlags(Qt::ItemIsSelectable);
    changeCustomer(id, naam, straat, postcode, gemeente);
}

void Universe::changeCustomer(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
    int index = klantIdToIndex(id);
    m_ui.m_klantenLijst->setItem(index, 1, new QTableWidgetItem(naam));
    m_ui.m_klantenLijst->setItem(index, 2, new QTableWidgetItem(straat));
    m_ui.m_klantenLijst->setItem(index, 3, new QTableWidgetItem(QString::number(postcode)));
    m_ui.m_klantenLijst->setItem(index, 4, new QTableWidgetItem(gemeente));
    m_ui.m_klantenLijst->item(index, 1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_klantenLijst->item(index, 2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_klantenLijst->item(index, 3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_klantenLijst->item(index, 4)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_klantenLijst->resizeRowToContents(index);
}

void Universe::setPhysicianListChanged(bool changed)
{
    markTabChanged(1, changed);
}

void Universe::setFileListChanged(bool changed)
{
    markTabChanged(0, changed);
}

void Universe::setInsuranceCompanyListChanged(bool changed)
{
    markTabChanged(2, changed);
}

void Universe::clearInsuranceCompanyList()
{
    m_ui.m_mutualiteitenLijst->clearContents();
    m_file.clearInsuranceCompanyList();
}

void Universe::addInsuranceCompany(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
    m_file.addInsuranceCompany(id, naam);

    int index = m_ui.m_mutualiteitenLijst->rowCount();
    m_ui.m_mutualiteitenLijst->insertRow(index);
    m_ui.m_mutualiteitenLijst->setItem(index, 0, new QTableWidgetItem(QString::number(id)));
    m_ui.m_mutualiteitenLijst->item(index, 0)->setFlags(Qt::ItemIsSelectable);
    wijzigenMutualiteit(id, naam, straat, postcode, gemeente);
}

void Universe::wijzigenMutualiteit(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente)
{
    m_file.changeInsruanceCompany(id, naam);

    int index = mutualiteitIdToIndex(id);
    m_ui.m_mutualiteitenLijst->setItem(index, 1, new QTableWidgetItem(naam));
    m_ui.m_mutualiteitenLijst->setItem(index, 2, new QTableWidgetItem(straat));
    m_ui.m_mutualiteitenLijst->setItem(index, 3, new QTableWidgetItem(QString::number(postcode)));
    m_ui.m_mutualiteitenLijst->setItem(index, 4, new QTableWidgetItem(gemeente));
    m_ui.m_mutualiteitenLijst->item(index, 1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_mutualiteitenLijst->item(index, 2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_mutualiteitenLijst->item(index, 3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_mutualiteitenLijst->item(index, 4)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_mutualiteitenLijst->resizeRowToContents(index);
}

int Universe::artsIndexToId(int index) const
{
    if (index > m_ui.m_artsenLijst->rowCount() || index < 0)
        return -1;
    return m_ui.m_artsenLijst->item(index, 0)->text().toInt();
}

int Universe::artsIdToIndex(int id) const
{
    for (int index = 0; index < m_ui.m_artsenLijst->rowCount(); ++index)
    {
        if (artsIndexToId(index) == id)
            return index;
    }
    return -1;
}

int Universe::klantIndexToId(int index) const
{
    if (index > m_ui.m_klantenLijst->rowCount() || index < 0)
        return -1;
    return m_ui.m_klantenLijst->item(index, 0)->text().toInt();
}

int Universe::klantIdToIndex(int id) const
{
    for (int index = 0; index < m_ui.m_klantenLijst->rowCount(); ++index)
    {
        if (klantIndexToId(index) == id)
            return index;
    }
    return -1;
}

int Universe::mutualiteitIndexToId(int index) const
{
    if (index > m_ui.m_mutualiteitenLijst->rowCount() || index < 0)
        return -1;
    return m_ui.m_mutualiteitenLijst->item(index, 0)->text().toInt();
}

int Universe::mutualiteitIdToIndex(int id) const
{
    for (int index = 0; index < m_ui.m_mutualiteitenLijst->rowCount(); ++index)
    {
        if (mutualiteitIndexToId(index) == id)
            return index;
    }
    return -1;
}

QSet<QString> Universe::getMerkHoorapparaten() const
{
    return m_hoorapparaatMerkToTypes.keys().toSet();
}

QSet<QString> Universe::getTypeHoorapparaten(const QString &merk) const
{
    return m_hoorapparaatMerkToTypes[merk].keys().toSet();
}

void Universe::selectPhysician(int id)
{
    m_ui.m_artsenLijst->setCurrentCell(artsIdToIndex(id), 1);
}

void Universe::selectCustomer(int id)
{
    m_ui.m_klantenLijst->setCurrentCell(klantIdToIndex(id), 1);
}

void Universe::selectInsuranceCompany(int id)
{
    m_ui.m_mutualiteitenLijst->setCurrentCell(mutualiteitIdToIndex(id), 1);
}

void Universe::selectPhysician(int currentRow, int, int previousRow, int)
{
    if (currentRow != previousRow)
        emit artsSelectieSignal(artsIndexToId(currentRow));

    enableWidgetsForPhysician();
}

void Universe::selectCustomer(int currentRow, int, int previousRow, int)
{
    if (currentRow != previousRow)
        emit klantSelectieSignal(klantIndexToId(currentRow));

    enableWidgetsForCustomer();
}

void Universe::selectInsuranceCompany(int currentRow, int, int previousRow, int)
{
    if (currentRow != previousRow)
        emit mutualiteitSelectieSignal(mutualiteitIndexToId(currentRow));

    enableWidgetsForInsuranceCompany();
}

void Universe::enableWidgetsForPhysician()
{
    bool selectedPhysician = !(m_ui.m_artsenLijst->selectionModel()->selectedIndexes().empty());

    m_ui.b_artsVerwijderen->setEnabled(selectedPhysician);
    m_ui.g_artsgegevens->setEnabled(selectedPhysician);
}

void Universe::enableWidgetsForCustomer()
{
    bool selectedCustomer = !(m_ui.m_klantenLijst->selectionModel()->selectedIndexes().empty());

    m_ui.b_dossierVerwijderen->setEnabled(selectedCustomer);
    m_ui.g_klantgegevens->setEnabled(selectedCustomer);
    m_ui.g_datums->setEnabled(selectedCustomer);
    m_ui.g_brieven->setEnabled(selectedCustomer);
    m_ui.g_hoorapparaten->setEnabled(selectedCustomer);
    m_ui.g_meetgegevens->setEnabled(selectedCustomer);
    m_ui.g_klantArts->setEnabled(selectedCustomer);
}

void Universe::enableWidgetsForInsuranceCompany()
{
    bool selectedInsuranceCompany = !(m_ui.m_mutualiteitenLijst->selectionModel()->selectedIndexes().empty());

    m_ui.b_mutualiteitVerwijderen->setEnabled(selectedInsuranceCompany);
    m_ui.g_mutualiteitsgegevens->setEnabled(selectedInsuranceCompany);
}

void Universe::addPhysician()
{
    AddDialog dialog(true, this);
    dialog.setWindowTitle(tr("Add Physician"));
    if (dialog.exec() == QDialog::Accepted)
        emit artsToevoegenSignal(dialog.getFirstName(), dialog.getName());
}

void Universe::removePhysician()
{
    QMessageBox warning(this);
    warning.addButton(QMessageBox::Yes);
    warning.addButton(QMessageBox::No);
    warning.button(QMessageBox::Yes)->setText(tr("Yes"));
    warning.button(QMessageBox::No)->setText(tr("No"));
    warning.setDefaultButton(QMessageBox::No);
    warning.setText(tr("Are you sure you want to remove the selected physician?"));
    warning.setWindowTitle(tr("Remove Physician"));
    warning.setIcon(QMessageBox::Warning);
    warning.exec();
    if (warning.clickedButton() == warning.button(QMessageBox::Yes))
    {
        int row = m_ui.m_artsenLijst->currentRow();
        int column = m_ui.m_artsenLijst->currentColumn();
        int id = artsIndexToId(m_ui.m_artsenLijst->currentRow());
        emit artsVerwijderenSignal(id);
        m_ui.m_artsenLijst->removeRow(row);
        if (row >= m_ui.m_artsenLijst->rowCount())
            --row;
        m_ui.m_artsenLijst->setCurrentCell(row, column);
        emit artsSelectieSignal(artsIndexToId(row));
    }
}

void Universe::findPhysician()
{
    static QString previousValue = "";
    bool ok = false;
    QString name = QInputDialog::getText(this, tr("Find Physician"), tr("Name:"), QLineEdit::Normal, previousValue, &ok);
    if (ok && !name.isEmpty())
    {
        previousValue = name;
        int nofRows = m_ui.m_artsenLijst->rowCount();
        int currentRow = m_ui.m_artsenLijst->currentRow();
        for (int i = 0; i < nofRows; ++i)
        {
            int row =(i + currentRow + 1) % nofRows;
            QTableWidgetItem *nameCell = m_ui.m_artsenLijst->item(row, 1);
            Q_ASSERT(nameCell);
            if (nameCell->text().contains(name, Qt::CaseInsensitive))
            {
                m_ui.m_artsenLijst->setCurrentCell(row, 1, QItemSelectionModel::ClearAndSelect);
                return;
            }
        }
    }
}

void Universe::addFile()
{
    AddDialog dialog(true, this);
    dialog.setWindowTitle(tr("Add File"));
    if (dialog.exec() == QDialog::Accepted)
        emit klantToevoegenSignal(dialog.getFirstName(), dialog.getName());
}

void Universe::removeFile()
{
    QMessageBox warning(this);
    warning.addButton(QMessageBox::Yes);
    warning.addButton(QMessageBox::No);
    warning.button(QMessageBox::Yes)->setText(tr("Yes"));
    warning.button(QMessageBox::No)->setText(tr("No"));
    warning.setDefaultButton(QMessageBox::No);
    warning.setText(tr("Are you sure you want to remove the selected file?"));
    warning.setWindowTitle(tr("Remove File"));
    warning.setIcon(QMessageBox::Warning);
    warning.exec();
    if (warning.clickedButton() == warning.button(QMessageBox::Yes))
    {
        int row = m_ui.m_klantenLijst->currentRow();
        int column = m_ui.m_klantenLijst->currentColumn();
        int id = klantIndexToId(m_ui.m_klantenLijst->currentRow());
        emit klantVerwijderenSignal(id);
        m_ui.m_klantenLijst->removeRow(row);
        if (row >= m_ui.m_klantenLijst->rowCount())
            --row;
        m_ui.m_klantenLijst->setCurrentCell(row, column);
        emit klantSelectieSignal(klantIndexToId(row));
    }
}

void Universe::findFile()
{
    static QString previousValue = "";
    bool ok = false;
    QString name = QInputDialog::getText(this, tr("Find Customer"), tr("Name:"), QLineEdit::Normal, previousValue, &ok);
    if (ok && !name.isEmpty())
    {
        previousValue = name;
        int nofRows = m_ui.m_klantenLijst->rowCount();
        int currentRow = m_ui.m_klantenLijst->currentRow();
        for (int i = 0; i < nofRows; ++i)
        {
            int row =(i + currentRow + 1) % nofRows;
            QTableWidgetItem *nameCell = m_ui.m_klantenLijst->item(row, 1);
            Q_ASSERT(nameCell);
            if (nameCell->text().contains(name, Qt::CaseInsensitive))
            {
                m_ui.m_klantenLijst->setCurrentCell(row, 1, QItemSelectionModel::ClearAndSelect);
                return;
            }
        }
    }
}

void Universe::addInsuranceCompany()
{
    AddDialog dialog(false, this);
    dialog.setWindowTitle(tr("Add Insurance Company"));
    if (dialog.exec() == QDialog::Accepted)
        emit mutualiteitToevoegenSignal(dialog.getName());
}

void Universe::removeInsuranceCompany()
{
    QMessageBox warning(this);
    warning.addButton(QMessageBox::Yes);
    warning.addButton(QMessageBox::No);
    warning.button(QMessageBox::Yes)->setText(tr("Yes"));
    warning.button(QMessageBox::No)->setText(tr("No"));
    warning.setDefaultButton(QMessageBox::No);
    warning.setText(tr("Are you sure you want to remove the selected insurance company?"));
    warning.setWindowTitle(tr("Remove Insurance Company"));
    warning.setIcon(QMessageBox::Warning);
    warning.exec();
    if (warning.clickedButton() == warning.button(QMessageBox::Yes))
    {
        int row = m_ui.m_mutualiteitenLijst->currentRow();
        int column = m_ui.m_mutualiteitenLijst->currentColumn();
        int id = mutualiteitIndexToId(m_ui.m_mutualiteitenLijst->currentRow());
        emit mutualiteitVerwijderenSignal(id);
        m_ui.m_mutualiteitenLijst->removeRow(row);
        if (row >= m_ui.m_mutualiteitenLijst->rowCount())
            --row;
        m_ui.m_mutualiteitenLijst->setCurrentCell(row, column);
        emit mutualiteitSelectieSignal(mutualiteitIndexToId(row));
    }
}

void Universe::findInsuranceCompany()
{
    static QString vorigeWaarde = "";
    bool ok = false;
    QString naam = QInputDialog::getText(this, tr("Find Insurance Company"), tr("Name:"), QLineEdit::Normal, vorigeWaarde, &ok);
    if (ok && !naam.isEmpty())
    {
        vorigeWaarde = naam;
        int nofRows = m_ui.m_mutualiteitenLijst->rowCount();
        int currentRow = m_ui.m_mutualiteitenLijst->currentRow();
        for (int i = 0; i < nofRows; ++i)
        {
            int row =(i + currentRow + 1) % nofRows;
            QTableWidgetItem *naamCell = m_ui.m_mutualiteitenLijst->item(row, 1);
            Q_ASSERT(naamCell);
            if (naamCell->text().contains(naam, Qt::CaseInsensitive))
            {
                m_ui.m_mutualiteitenLijst->setCurrentCell(row, 1, QItemSelectionModel::ClearAndSelect);
                return;
            }
        }
    }
}

void Universe::closeEvent(QCloseEvent *event)
{
    emit afsluitenSignal();
    event->accept();
}


void Universe::cleanupTabPhysician()
{
    m_ui.m_artsNaam->setText("");
    m_ui.m_artsVoornaam->setText("");
    m_ui.m_artsStraat->setText("");
    m_ui.m_artsPostcode->setValue(1000);
    m_ui.m_artsGemeente->setText("");
    m_ui.m_artsTelefoon->setText("");
    m_ui.m_artsEmail->setText("");
    m_ui.m_artsOpmerkingen->setText("");
    m_ui.g_artsgegevens->setEnabled(false);
    m_ui.b_artsVerwijderen->setEnabled(false);
}

void Universe::cleanupTabFile(const QDate &invalidDate)
{
    m_ui.m_aanspreektitel->setCurrentIndex(-1);
    m_ui.m_klantNaam->setText("");
    m_ui.m_klantVoornaam->setText("");
    m_ui.m_klantStraat->setText("");
    m_ui.m_klantPostcode->setValue(1000);
    m_ui.m_klantGemeente->setText("");
    m_ui.m_klantTelefoon->setText("");
    m_ui.m_klantGeboorteDatum->setDate(invalidDate);
    m_ui.m_klantMutualiteit->setCurrentIndex(-1);
    m_ui.m_aansluitingsnummer->setText("");
    m_ui.m_plaatsAanpassing->setText("");
    m_ui.m_klantOpmerkingen->setText("");
    m_ui.m_datumProef->setDate(invalidDate);
    m_ui.m_datumNKO->setDate(invalidDate);
    m_ui.m_datumAdviseur->setDate(invalidDate);
    m_ui.m_datumMutualiteit->setDate(invalidDate);
    m_ui.m_datumBetaling->setDate(invalidDate);
    m_ui.m_datumAflevering->setDate(invalidDate);
    m_ui.m_datumWissel->setDate(invalidDate);
    m_ui.m_datumOnderhoudsContract->setDate(invalidDate);
    m_ui.m_datumOnderzoek->setDate(invalidDate);
    m_ui.m_klantArts->setCurrentIndex(-1);
    m_ui.m_linkerHoorapparaatMerk->setCurrentIndex(-1);
    m_ui.m_linkerHoorapparaatType->setCurrentIndex(-1);
    m_ui.m_linkerHoorapparaatSerienummer->setText("");
    m_ui.m_linkerHoorapparaatPrijs->setText("");
    m_ui.m_rechterHoorapparaatMerk->setCurrentIndex(-1);
    m_ui.m_rechterHoorapparaatType->setCurrentIndex(-1);
    m_ui.m_rechterHoorapparaatSerienummer->setText("");
    m_ui.m_rechterHoorapparaatPrijs->setText("");
    m_ui.g_klantgegevens->setEnabled(false);
    m_ui.g_datums->setEnabled(false);
    m_ui.g_brieven->setEnabled(false);
    m_ui.g_hoorapparaten->setEnabled(false);
    m_ui.g_meetgegevens->setEnabled(false);
    m_ui.g_klantArts->setEnabled(false);
    m_ui.b_dossierVerwijderen->setEnabled(false);
}

void Universe::cleanupTabInsuranceCompany()
{
    m_ui.m_mutualiteitNaam->setText("");
    m_ui.m_mutualiteitStraat->setText("");
    m_ui.m_mutualiteitPostcode->setValue(1000);
    m_ui.m_mutualiteitGemeente->setText("");
    m_ui.m_mutualiteitTelefoon->setText("");
    m_ui.m_mutualiteitEmail->setText("");
    m_ui.m_mutualiteitOpmerkingen->setText("");
    m_ui.g_mutualiteitsgegevens->setEnabled(false);
    m_ui.b_mutualiteitVerwijderen->setEnabled(false);
}

void Universe::markTabChanged(int tabIndex, bool changed)
{
    QString tabText = m_ui.m_tabs->tabText(tabIndex).remove('*');
    if (changed)
        tabText += "*";
    m_ui.m_tabs->setTabText(tabIndex, tabText);

}
