#include "view_universe.h"
#include "view_adddialog.h"

#include <QCloseEvent>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

using namespace View;

Universe::Universe(QWidget *parent, Qt::WFlags f)
: QMainWindow(parent, f)
, m_physician(m_ui)
, m_file(*this)
, m_insuranceCompany(m_ui)
, m_labels(this)
, m_settings(this)
, m_currentTab(0)
{
    m_ui.setupUi(this);
    connect(m_ui.actionSave, SIGNAL(triggered()), this, SIGNAL(saveSignal()));
    connect(m_ui.actionLabels, SIGNAL(triggered()), this, SIGNAL(openLabels()));
    connect(m_ui.actionSettings, SIGNAL(triggered()), this, SIGNAL(openSettings()));
    connect(m_ui.actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(m_ui.m_physicianList, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(selectPhysician(int, int, int, int)));
    connect(m_ui.m_customerList, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(selectCustomer(int, int, int, int)));
    connect(m_ui.m_insuranceCompanyList, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(selectInsuranceCompany(int, int, int, int)));
    connect(m_ui.b_physicianAdd, SIGNAL(clicked()), this, SLOT(addPhysician()));
    connect(m_ui.b_physicianRemove, SIGNAL(clicked()), this, SLOT(removePhysician()));
    connect(m_ui.b_physicianFind, SIGNAL(clicked()), this, SLOT(findPhysician()));
    connect(m_ui.b_fileAdd, SIGNAL(clicked()), this, SLOT(addFile()));
    connect(m_ui.b_fileRemove, SIGNAL(clicked()), this, SLOT(removeFile()));
    connect(m_ui.b_fileFind, SIGNAL(clicked()), this, SLOT(findFile()));
    connect(m_ui.b_insuranceCompanyAdd, SIGNAL(clicked()), this, SLOT(addInsuranceCompany()));
    connect(m_ui.b_insuranceCompanyRemove, SIGNAL(clicked()), this, SLOT(removeInsuranceCompany()));
    connect(m_ui.b_insuranceCompanyFind, SIGNAL(clicked()), this, SLOT(findInsuranceCompany()));
    connect(m_ui.m_rightHearingAidBrand, SIGNAL(currentIndexChanged(int)), &m_file, SLOT(refreshRechterHoorapparaatLijst(int)));
    connect(m_ui.m_leftHearingAidBrand, SIGNAL(currentIndexChanged(int)), &m_file, SLOT(refreshLinkerHoorapparaatLijst(int)));
    connect(m_ui.m_customerPhysician, SIGNAL(currentIndexChanged(int)), &m_file, SLOT(showPhysician(int)));
    connect(m_ui.m_customerInsurance, SIGNAL(currentIndexChanged(int)), &m_file, SLOT(showInsuranceCompany(int)));
    connect(m_ui.b_letterCustomer, SIGNAL(clicked()), &m_file, SIGNAL(showLetterCustomer()));
    connect(m_ui.b_letterPhysician, SIGNAL(clicked()), &m_file, SIGNAL(showLetterPhysician()));
    connect(m_ui.b_letterInsurance, SIGNAL(clicked()), &m_file, SIGNAL(showLetterInsuranceCompany()));
    connect(m_ui.b_invoice, SIGNAL(clicked()), &m_file, SIGNAL(showInvoice()));
    connect(m_ui.b_measurements, SIGNAL(clicked()), &m_file, SIGNAL(showMeasurements()));
    connect(m_ui.m_tabs, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));

    // Change some column widths in the table views
    m_ui.m_physicianList->setColumnWidth(0, 50);
    m_ui.m_physicianList->setColumnWidth(1, 300);
    m_ui.m_physicianList->setColumnWidth(2, 300);
    m_ui.m_physicianList->setColumnWidth(3, 100);
    m_ui.m_physicianList->setColumnWidth(4, 200);
    m_ui.m_physicianList->hideColumn(0);
    m_ui.m_customerList->setColumnWidth(0, 50);
    m_ui.m_customerList->setColumnWidth(1, 300);
    m_ui.m_customerList->setColumnWidth(2, 300);
    m_ui.m_customerList->setColumnWidth(3, 100);
    m_ui.m_customerList->setColumnWidth(4, 200);
    m_ui.m_customerList->hideColumn(0);
    m_ui.m_insuranceCompanyList->setColumnWidth(0, 50);
    m_ui.m_insuranceCompanyList->setColumnWidth(1, 300);
    m_ui.m_insuranceCompanyList->setColumnWidth(2, 300);
    m_ui.m_insuranceCompanyList->setColumnWidth(3, 100);
    m_ui.m_insuranceCompanyList->setColumnWidth(4, 200);
    m_ui.m_insuranceCompanyList->hideColumn(0);
}

Universe::~Universe()
{
}

Physician &Universe::getPhysician()
{
    return m_physician;
}

File &Universe::getFile()
{
    return m_file;
}

InsuranceCompany &Universe::getInsuranceCompany()
{
    return m_insuranceCompany;
}

Labels &Universe::getLabels()
{
    return m_labels;
}

Settings &Universe::getSettings()
{
    return m_settings;
}

void Universe::tabChanged(int newTab)
{
    switch (m_currentTab)
    {
    case 0: emit closeFileTab(); break;
    case 1: emit closePhysicianTab(); break;
    case 2: emit closeInsuranceCompanyTab(); break;
    }

    m_currentTab = newTab;

    switch (m_currentTab)
    {
    case 0: emit openDossierTab(); break;
    case 1: emit openArtsTab(); break;
    case 2: emit openMutualiteitTab(); break;
    }
}

void Universe::about()
{
    QMessageBox::about(this, tr("About AudioAdmin"), tr("<p>AudioAdmin 2.0</p>"
                       "<p>Released under the GNU General Public License v3.0</p>"
                       "<p>June 2011</p>"));
}

void Universe::saveAtExit()
{
    QMessageBox msgBox(this);
    msgBox.setText(tr("Not all changes were saved"));
    msgBox.setInformativeText(tr("Do you want to save your pending changes?"));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
    msgBox.button(QMessageBox::Save)->setText(tr("Save"));
    msgBox.button(QMessageBox::Discard)->setText(tr("Exit without Save"));
    msgBox.setDefaultButton(QMessageBox::Save);
    if (msgBox.exec() == QMessageBox::Save)
        emit saveSignal();
}

void Universe::clearPhysicianList()
{
    m_ui.m_physicianList->clearContents();
    m_file.clearPhysicianList();
}

void Universe::addPhysician(int id, const QString &name, const QString &street, int postalCode, const QString &city)
{
    m_file.addPhysician(id, name, street, QString::number(postalCode) + " " + city);

    int index = m_ui.m_physicianList->rowCount();
    m_ui.m_physicianList->insertRow(index);
    m_ui.m_physicianList->setItem(index, 0, new QTableWidgetItem(QString::number(id)));
    m_ui.m_physicianList->item(index, 0)->setFlags(Qt::ItemIsSelectable);
    changePhysician(id, name, street, postalCode, city);
}

void Universe::changePhysician(int id, const QString &name, const QString &street, int postalCode, const QString &city)
{
    m_file.changePhysician(id, name, street, QString::number(postalCode) + " " + city);

    int index = physicianIdToIndex(id);
    m_ui.m_physicianList->setItem(index, 1, new QTableWidgetItem(name));
    m_ui.m_physicianList->setItem(index, 2, new QTableWidgetItem(street));
    m_ui.m_physicianList->setItem(index, 3, new QTableWidgetItem(QString::number(postalCode)));
    m_ui.m_physicianList->setItem(index, 4, new QTableWidgetItem(city));
    m_ui.m_physicianList->item(index, 1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_physicianList->item(index, 2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_physicianList->item(index, 3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_physicianList->item(index, 4)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_physicianList->resizeRowToContents(index);
}

void Universe::clearHearingAidList()
{
    m_hearingAidBrandToTypes.clear();
}

void Universe::addHearingAid(const QString &brand, const QString &type, double price, const QDate &datePrice)
{
    PriceDatePair info(price, datePrice);
    if (m_hearingAidBrandToTypes[brand].find(type) != m_hearingAidBrandToTypes[brand].end())
    {
        if (m_hearingAidBrandToTypes[brand][type].second >= info.second)
            info = m_hearingAidBrandToTypes[brand][type];
    }
    m_hearingAidBrandToTypes[brand][type] = info;
}

void Universe::clearCustomerList()
{
    m_ui.m_customerList->clearContents();
    m_ui.m_customerList->setRowCount(0);
}

void Universe::addCustomer(int id, const QString &name, const QString &street, int postalCode, const QString &city)
{
    int index = m_ui.m_customerList->rowCount();
    m_ui.m_customerList->insertRow(index);
    m_ui.m_customerList->setItem(index, 0, new QTableWidgetItem(QString::number(id)));
    m_ui.m_customerList->item(index, 0)->setFlags(Qt::ItemIsSelectable);
    changeCustomer(id, name, street, postalCode, city);
}

void Universe::changeCustomer(int id, const QString &name, const QString &street, int postalCode, const QString &city)
{
    int index = customerIdToIndex(id);
    m_ui.m_customerList->setItem(index, 1, new QTableWidgetItem(name));
    m_ui.m_customerList->setItem(index, 2, new QTableWidgetItem(street));
    m_ui.m_customerList->setItem(index, 3, new QTableWidgetItem(QString::number(postalCode)));
    m_ui.m_customerList->setItem(index, 4, new QTableWidgetItem(city));
    m_ui.m_customerList->item(index, 1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_customerList->item(index, 2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_customerList->item(index, 3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_customerList->item(index, 4)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_customerList->resizeRowToContents(index);
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
    m_ui.m_insuranceCompanyList->clearContents();
    m_file.clearInsuranceCompanyList();
}

void Universe::addInsuranceCompany(int id, const QString &name, const QString &street, int postalCode, const QString &city)
{
    m_file.addInsuranceCompany(id, name);

    int index = m_ui.m_insuranceCompanyList->rowCount();
    m_ui.m_insuranceCompanyList->insertRow(index);
    m_ui.m_insuranceCompanyList->setItem(index, 0, new QTableWidgetItem(QString::number(id)));
    m_ui.m_insuranceCompanyList->item(index, 0)->setFlags(Qt::ItemIsSelectable);
    changeInsuranceCompany(id, name, street, postalCode, city);
}

void Universe::changeInsuranceCompany(int id, const QString &name, const QString &street, int postalCode, const QString &city)
{
    m_file.changeInsruanceCompany(id, name);

    int index = insuranceCompanyIdToIndex(id);
    m_ui.m_insuranceCompanyList->setItem(index, 1, new QTableWidgetItem(name));
    m_ui.m_insuranceCompanyList->setItem(index, 2, new QTableWidgetItem(street));
    m_ui.m_insuranceCompanyList->setItem(index, 3, new QTableWidgetItem(QString::number(postalCode)));
    m_ui.m_insuranceCompanyList->setItem(index, 4, new QTableWidgetItem(city));
    m_ui.m_insuranceCompanyList->item(index, 1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_insuranceCompanyList->item(index, 2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_insuranceCompanyList->item(index, 3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_insuranceCompanyList->item(index, 4)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_ui.m_insuranceCompanyList->resizeRowToContents(index);
}

int Universe::physicianIndexToId(int index) const
{
    if (index > m_ui.m_physicianList->rowCount() || index < 0)
        return -1;
    return m_ui.m_physicianList->item(index, 0)->text().toInt();
}

int Universe::physicianIdToIndex(int id) const
{
    for (int index = 0; index < m_ui.m_physicianList->rowCount(); ++index)
    {
        if (physicianIndexToId(index) == id)
            return index;
    }
    return -1;
}

int Universe::customerIndexToId(int index) const
{
    if (index > m_ui.m_customerList->rowCount() || index < 0)
        return -1;
    return m_ui.m_customerList->item(index, 0)->text().toInt();
}

int Universe::customerIdToIndex(int id) const
{
    for (int index = 0; index < m_ui.m_customerList->rowCount(); ++index)
    {
        if (customerIndexToId(index) == id)
            return index;
    }
    return -1;
}

int Universe::insuranceCompanyIndexToId(int index) const
{
    if (index > m_ui.m_insuranceCompanyList->rowCount() || index < 0)
        return -1;
    return m_ui.m_insuranceCompanyList->item(index, 0)->text().toInt();
}

int Universe::insuranceCompanyIdToIndex(int id) const
{
    for (int index = 0; index < m_ui.m_insuranceCompanyList->rowCount(); ++index)
    {
        if (insuranceCompanyIndexToId(index) == id)
            return index;
    }
    return -1;
}

QSet<QString> Universe::getHearingAidBrands() const
{
    return m_hearingAidBrandToTypes.keys().toSet();
}

QSet<QString> Universe::getHearingAidTypes(const QString &merk) const
{
    return m_hearingAidBrandToTypes[merk].keys().toSet();
}

void Universe::selectPhysician(int id)
{
    m_ui.m_physicianList->setCurrentCell(physicianIdToIndex(id), 1);
}

void Universe::selectCustomer(int id)
{
    m_ui.m_customerList->setCurrentCell(customerIdToIndex(id), 1);
}

void Universe::selectInsuranceCompany(int id)
{
    m_ui.m_insuranceCompanyList->setCurrentCell(insuranceCompanyIdToIndex(id), 1);
}

void Universe::selectPhysician(int currentRow, int, int previousRow, int)
{
    if (currentRow != previousRow)
        emit artsSelectieSignal(physicianIndexToId(currentRow));

    enableWidgetsForPhysician();
}

void Universe::selectCustomer(int currentRow, int, int previousRow, int)
{
    if (currentRow != previousRow)
        emit klantSelectieSignal(customerIndexToId(currentRow));

    enableWidgetsForCustomer();
}

void Universe::selectInsuranceCompany(int currentRow, int, int previousRow, int)
{
    if (currentRow != previousRow)
        emit mutualiteitSelectieSignal(insuranceCompanyIndexToId(currentRow));

    enableWidgetsForInsuranceCompany();
}

void Universe::enableWidgetsForPhysician()
{
    bool selectedPhysician = !(m_ui.m_physicianList->selectionModel()->selectedIndexes().empty());

    m_ui.b_physicianRemove->setEnabled(selectedPhysician);
    m_ui.g_physicianData->setEnabled(selectedPhysician);
}

void Universe::enableWidgetsForCustomer()
{
    bool selectedCustomer = !(m_ui.m_customerList->selectionModel()->selectedIndexes().empty());

    m_ui.b_fileRemove->setEnabled(selectedCustomer);
    m_ui.g_customerData->setEnabled(selectedCustomer);
    m_ui.g_dates->setEnabled(selectedCustomer);
    m_ui.g_letters->setEnabled(selectedCustomer);
    m_ui.g_hearingAids->setEnabled(selectedCustomer);
    m_ui.g_measurements->setEnabled(selectedCustomer);
    m_ui.g_customerPhysician->setEnabled(selectedCustomer);
}

void Universe::enableWidgetsForInsuranceCompany()
{
    bool selectedInsuranceCompany = !(m_ui.m_insuranceCompanyList->selectionModel()->selectedIndexes().empty());

    m_ui.b_insuranceCompanyRemove->setEnabled(selectedInsuranceCompany);
    m_ui.g_insuranceCompanyData->setEnabled(selectedInsuranceCompany);
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
        int row = m_ui.m_physicianList->currentRow();
        int column = m_ui.m_physicianList->currentColumn();
        int id = physicianIndexToId(m_ui.m_physicianList->currentRow());
        emit artsVerwijderenSignal(id);
        m_ui.m_physicianList->removeRow(row);
        if (row >= m_ui.m_physicianList->rowCount())
            --row;
        m_ui.m_physicianList->setCurrentCell(row, column);
        emit artsSelectieSignal(physicianIndexToId(row));
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
        int nofRows = m_ui.m_physicianList->rowCount();
        int currentRow = m_ui.m_physicianList->currentRow();
        for (int i = 0; i < nofRows; ++i)
        {
            int row =(i + currentRow + 1) % nofRows;
            QTableWidgetItem *nameCell = m_ui.m_physicianList->item(row, 1);
            Q_ASSERT(nameCell);
            if (nameCell->text().contains(name, Qt::CaseInsensitive))
            {
                m_ui.m_physicianList->setCurrentCell(row, 1, QItemSelectionModel::ClearAndSelect);
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
        int row = m_ui.m_customerList->currentRow();
        int column = m_ui.m_customerList->currentColumn();
        int id = customerIndexToId(m_ui.m_customerList->currentRow());
        emit klantVerwijderenSignal(id);
        m_ui.m_customerList->removeRow(row);
        if (row >= m_ui.m_customerList->rowCount())
            --row;
        m_ui.m_customerList->setCurrentCell(row, column);
        emit klantSelectieSignal(customerIndexToId(row));
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
        int nofRows = m_ui.m_customerList->rowCount();
        int currentRow = m_ui.m_customerList->currentRow();
        for (int i = 0; i < nofRows; ++i)
        {
            int row =(i + currentRow + 1) % nofRows;
            QTableWidgetItem *nameCell = m_ui.m_customerList->item(row, 1);
            Q_ASSERT(nameCell);
            if (nameCell->text().contains(name, Qt::CaseInsensitive))
            {
                m_ui.m_customerList->setCurrentCell(row, 1, QItemSelectionModel::ClearAndSelect);
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
        int row = m_ui.m_insuranceCompanyList->currentRow();
        int column = m_ui.m_insuranceCompanyList->currentColumn();
        int id = insuranceCompanyIndexToId(m_ui.m_insuranceCompanyList->currentRow());
        emit mutualiteitVerwijderenSignal(id);
        m_ui.m_insuranceCompanyList->removeRow(row);
        if (row >= m_ui.m_insuranceCompanyList->rowCount())
            --row;
        m_ui.m_insuranceCompanyList->setCurrentCell(row, column);
        emit mutualiteitSelectieSignal(insuranceCompanyIndexToId(row));
    }
}

void Universe::findInsuranceCompany()
{
    static QString vorigeWaarde = "";
    bool ok = false;
    QString name = QInputDialog::getText(this, tr("Find Insurance Company"), tr("Name:"), QLineEdit::Normal, vorigeWaarde, &ok);
    if (ok && !name.isEmpty())
    {
        vorigeWaarde = name;
        int nofRows = m_ui.m_insuranceCompanyList->rowCount();
        int currentRow = m_ui.m_insuranceCompanyList->currentRow();
        for (int i = 0; i < nofRows; ++i)
        {
            int row =(i + currentRow + 1) % nofRows;
            QTableWidgetItem *cellName = m_ui.m_insuranceCompanyList->item(row, 1);
            Q_ASSERT(cellName);
            if (cellName->text().contains(name, Qt::CaseInsensitive))
            {
                m_ui.m_insuranceCompanyList->setCurrentCell(row, 1, QItemSelectionModel::ClearAndSelect);
                return;
            }
        }
    }
}

void Universe::closeEvent(QCloseEvent *event)
{
    emit exitSignal();
    event->accept();
}


void Universe::cleanupTabPhysician()
{
    m_ui.m_physicianName->setText("");
    m_ui.m_physicianFirstName->setText("");
    m_ui.m_physicianStreet->setText("");
    m_ui.m_physicianPostalCode->setValue(1000);
    m_ui.m_physicianCity->setText("");
    m_ui.m_physicianTelephone->setText("");
    m_ui.m_physicianEmail->setText("");
    m_ui.m_physicianComments->setText("");
    m_ui.g_physicianData->setEnabled(false);
    m_ui.b_physicianRemove->setEnabled(false);
}

void Universe::cleanupTabFile(const QDate &invalidDate)
{
    m_ui.m_customerTitle->setCurrentIndex(-1);
    m_ui.m_customerName->setText("");
    m_ui.m_customerFirstName->setText("");
    m_ui.m_customerStreet->setText("");
    m_ui.m_customerPostalCode->setValue(1000);
    m_ui.m_customerCity->setText("");
    m_ui.m_customerTelephone->setText("");
    m_ui.m_customerDateOfBirth->setDate(invalidDate);
    m_ui.m_customerInsurance->setCurrentIndex(-1);
    m_ui.m_memberNr->setText("");
    m_ui.m_placeAdjustment->setText("");
    m_ui.m_customerComments->setText("");
    m_ui.m_dateTest->setDate(invalidDate);
    m_ui.m_dateTrial->setDate(invalidDate);
    m_ui.m_dateReport->setDate(invalidDate);
    m_ui.m_dateAdvice->setDate(invalidDate);
    m_ui.m_dateInsurance->setDate(invalidDate);
    m_ui.m_datePayment->setDate(invalidDate);
    m_ui.m_dateDelivery->setDate(invalidDate);
    m_ui.m_dateExchange->setDate(invalidDate);
    m_ui.m_dateMaintenance->setDate(invalidDate);
    m_ui.m_customerPhysician->setCurrentIndex(-1);
    m_ui.m_leftHearingAidBrand->setCurrentIndex(-1);
    m_ui.m_leftHearingAidType->setCurrentIndex(-1);
    m_ui.m_leftHearingAidSerialNr->setText("");
    m_ui.m_leftHearingAidPrice->setText("");
    m_ui.m_rightHearingAidBrand->setCurrentIndex(-1);
    m_ui.m_rightHearingAidType->setCurrentIndex(-1);
    m_ui.m_rightHearingAidSerialNr->setText("");
    m_ui.m_rightHearingAidPrice->setText("");
    m_ui.g_customerData->setEnabled(false);
    m_ui.g_dates->setEnabled(false);
    m_ui.g_letters->setEnabled(false);
    m_ui.g_hearingAids->setEnabled(false);
    m_ui.g_measurements->setEnabled(false);
    m_ui.g_customerPhysician->setEnabled(false);
    m_ui.b_fileRemove->setEnabled(false);
}

void Universe::cleanupTabInsuranceCompany()
{
    m_ui.m_insuranceCompanyName->setText("");
    m_ui.m_insuranceCompanyStreet->setText("");
    m_ui.m_insuranceCompanyPostalCode->setValue(1000);
    m_ui.m_insuranceCompanyCity->setText("");
    m_ui.m_insuranceCompanyTelephone->setText("");
    m_ui.m_insuranceCompanyEmail->setText("");
    m_ui.m_insuranceCompanyComments->setText("");
    m_ui.g_insuranceCompanyData->setEnabled(false);
    m_ui.b_insuranceCompanyRemove->setEnabled(false);
}

void Universe::markTabChanged(int tabIndex, bool changed)
{
    QString tabText = m_ui.m_tabs->tabText(tabIndex).remove('*');
    if (changed)
        tabText += "*";
    m_ui.m_tabs->setTabText(tabIndex, tabText);

}
