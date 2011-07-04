#include "view_file.h"
#include "view_universe.h"

using namespace View;

namespace
{
    const int ROLE_ID = Qt::UserRole + 1;
    const int ROLE_STREET = Qt::UserRole + 2;
    const int ROLE_CITY = Qt::UserRole + 3;
}

File::File(Universe &universe)
: m_universe(universe)
, m_ui(universe.getUi())
, m_customer(*this)
{
}

File::~File()
{
}

QWidget *File::getParentWindow()
{
    return &m_universe;
}

void File::clearPhysicianList()
{
    m_physicianList.clear();
    m_physicianList.sort(0);
    m_ui.m_customerPhysician->setModel(&m_physicianList);
    addPhysician(-1, "", "", "");
}

void File::addPhysician(int id, const QString &name, const QString &street, const QString &city)
{
    QStandardItem *item = new QStandardItem(name);
    Q_ASSERT(item);
    item->setData(QVariant(id), ROLE_ID);
    item->setData(QVariant(street), ROLE_STREET);
    item->setData(QVariant(city), ROLE_CITY);
    m_physicianList.appendRow(item);
    m_physicianList.sort(0);
}

void File::changePhysician(int id, const QString &name, const QString &street, const QString &city)
{
    for (int iRow = 0; iRow < m_physicianList.rowCount(); ++iRow)
    {
        QStandardItem *item = m_physicianList.item(iRow);
        if (item->data(ROLE_ID).toInt() == id)
        {
            item->setText(name);
            item->setData(QVariant(street), ROLE_STREET);
            item->setData(QVariant(city), ROLE_CITY);
            return;
        }
    }

    Q_ASSERT(false);
}

void File::clearInsuranceCompanyList()
{
    m_insuranceCompanyList.clear();
    m_insuranceCompanyList.sort(0);
    m_ui.m_customerInsurance->setModel(&m_insuranceCompanyList);
    addInsuranceCompany(-1, "");
}

void File::addInsuranceCompany(int id, const QString &name)
{
    QStandardItem *item = new QStandardItem(name);
    Q_ASSERT(item);
    item->setData(QVariant(id), ROLE_ID);
    m_insuranceCompanyList.appendRow(item);
    m_insuranceCompanyList.sort(0);
}

void File::changeInsruanceCompany(int id, const QString &name)
{
    for (int iRow = 0; iRow < m_insuranceCompanyList.rowCount(); ++iRow)
    {
        QStandardItem *item = m_insuranceCompanyList.item(iRow);
        if (item->data(ROLE_ID).toInt() == id)
        {
            item->setText(name);
            return;
        }
    }

    Q_ASSERT(false);
}

int File::getInsuranceCompany() const
{
    int index = m_ui.m_customerInsurance->currentIndex();
    return m_ui.m_customerInsurance->itemData(index, ROLE_ID).toInt();
}

QString File::getMemberNumber() const
{
    return m_ui.m_memberNr->text();
}

QString File::getPlaceAdjustment() const
{
    return m_ui.m_placeAdjustment->text();
}

int File::getPhysician() const
{
    int index = m_ui.m_customerPhysician->currentIndex();
    return m_ui.m_customerPhysician->itemData(index, ROLE_ID).toInt();
}

QString File::getRightHearingAidBrand() const
{
    return m_ui.m_rightHearingAidBrand->currentText();
}

QString File::getRightHearingAidType() const
{
    return m_ui.m_rightHearingAidType->currentText();
}

QString File::getRightHearingAidSerialNumber() const
{
    return m_ui.m_rightHearingAidSerialNr->text();
}

double File::getRightHearingAidPrice() const
{
    return m_ui.m_rightHearingAidPrice->text().toDouble();
}

QString File::getLeftHearingAidBrand() const
{
    return m_ui.m_leftHearingAidBrand->currentText();
}

QString File::getLeftHearingAidType() const
{
    return m_ui.m_leftHearingAidType->currentText();
}

QString File::getLeftHearingAidSerialNumber() const
{
    return m_ui.m_leftHearingAidSerialNr->text();
}

double File::getLeftHearingAidPrice() const
{
    return m_ui.m_leftHearingAidPrice->text().toDouble();
}


QDate File::getTestDate() const
{
    return m_ui.m_dateTest->date();
}

QDate File::getTrialDate() const
{
    return m_ui.m_dateTrial->date();
}

QDate File::getPhysicianReportDate() const
{
    return m_ui.m_dateReport->date();
}

QDate File::getPhysicianAdviceDate() const
{
    return m_ui.m_dateAdvice->date();
}

QDate File::getInsuranceAgreementDate() const
{
    return m_ui.m_dateInsurance->date();
}

QDate File::getPaymentDate() const
{
    return m_ui.m_datePayment->date();
}

QDate File::getDeliveryDate() const
{
    return m_ui.m_dateDelivery->date();
}

QDate File::getExchangeDate() const
{
    return m_ui.m_dateExchange->date();
}

QDate File::getMaintenanceContractDate() const
{
    return m_ui.m_dateMaintenance->date();
}

void File::setInsuranceCompany(int id)
{
    for (int iRow = 0; iRow < m_insuranceCompanyList.rowCount(); ++iRow)
    {
        if (id == m_ui.m_customerInsurance->itemData(iRow, ROLE_ID).toInt())
        {
            m_ui.m_customerInsurance->setCurrentIndex(iRow);
            m_ui.b_letterInsurance->setEnabled(true);
            return;
        }
    }

    m_ui.m_customerInsurance->setCurrentIndex(0);
    m_ui.b_letterInsurance->setEnabled(false);
}

void File::setMemberNumber(const QString &value)
{
    m_ui.m_memberNr->setText(value);
}

void File::setPlaceAdjustment(const QString &value)
{
    m_ui.m_placeAdjustment->setText(value);
}

void File::setPhysician(int id)
{
    for (int iRow = 0; iRow < m_physicianList.rowCount(); ++iRow)
    {
        if (id == m_ui.m_customerPhysician->itemData(iRow, ROLE_ID).toInt())
        {
            m_ui.m_customerPhysician->setCurrentIndex(iRow);
            m_ui.b_letterPhysician->setEnabled(true);
            return;
        }
    }

    m_ui.m_customerPhysician->setCurrentIndex(0);
    m_ui.b_letterPhysician->setEnabled(false);
}

void File::setRightHearingAidBrand(const QString &value)
{
    QSet<QString> brands = m_universe.getHearingAidBrands();
    m_ui.m_rightHearingAidBrand->clear();
    int index = 0;
    bool itemFound = false;
    for (QSet<QString>::iterator it = brands.begin(); it != brands.end(); ++it, ++index)
    {
        m_ui.m_rightHearingAidBrand->addItem(*it);
        if (*it == value)
        {
            m_ui.m_rightHearingAidBrand->setCurrentIndex(index);
            itemFound = true;
        }
    }
    if (! itemFound)
    {
        m_ui.m_rightHearingAidBrand->addItem(value);
        m_ui.m_rightHearingAidBrand->setCurrentIndex(index);
    }
}

void File::setRightHearingAidType(const QString &value)
{
    QString brand = getRightHearingAidBrand();
    QSet<QString> types = m_universe.getHearingAidTypes(brand);
    m_ui.m_rightHearingAidType->setEditText(value);
    int index = 0;
    bool itemFound = false;
    for (QSet<QString>::iterator it = types.begin(); it != types.end(); ++it, ++index)
    {
        m_ui.m_rightHearingAidType->addItem(*it);
        if (*it == value)
        {
            m_ui.m_rightHearingAidType->setCurrentIndex(index);
            itemFound = true;
        }
    }
    if (! itemFound)
    {
        m_ui.m_rightHearingAidType->addItem(value);
        m_ui.m_rightHearingAidType->setCurrentIndex(index);
    }
}

void File::setRightHearingAidSerialNumber(const QString &value)
{
    m_ui.m_rightHearingAidSerialNr->setText(value);
}

void File::setRightHearingAidPrice(double value)
{
    m_ui.m_rightHearingAidPrice->setText(value > 0.0 ? QString::number(value) : "");
}

void File::setLeftHearingAidBrand(const QString &value)
{
    QSet<QString> brands = m_universe.getHearingAidBrands();
    m_ui.m_leftHearingAidBrand->clear();
    int index = 0;
    bool itemFound = false;
    for (QSet<QString>::iterator it = brands.begin(); it != brands.end(); ++it, ++index)
    {
        m_ui.m_leftHearingAidBrand->addItem(*it);
        if (*it == value)
        {
            m_ui.m_leftHearingAidBrand->setCurrentIndex(index);
            itemFound = true;
        }
    }
    if (! itemFound)
    {
        m_ui.m_leftHearingAidBrand->addItem(value);
        m_ui.m_leftHearingAidBrand->setCurrentIndex(index);
    }
}

void File::setLeftHearingAidType(const QString &value)
{
    QString brand = getLeftHearingAidBrand();
    QSet<QString> types = m_universe.getHearingAidTypes(brand);
    m_ui.m_leftHearingAidType->setEditText(value);
    int index = 0;
    bool itemFound = false;
    for (QSet<QString>::iterator it = types.begin(); it != types.end(); ++it, ++index)
    {
        m_ui.m_leftHearingAidType->addItem(*it);
        if (*it == value)
        {
            m_ui.m_leftHearingAidType->setCurrentIndex(index);
            itemFound = true;
        }
    }
    if (! itemFound)
    {
        m_ui.m_leftHearingAidType->addItem(value);
        m_ui.m_leftHearingAidType->setCurrentIndex(index);
    }
}

void File::setLeftHearingAidSerialNumber(const QString &value)
{
    m_ui.m_leftHearingAidSerialNr->setText(value);
}

void File::setLeftHearingAidPrice(double value)
{
    m_ui.m_leftHearingAidPrice->setText(value > 0.0 ? QString::number(value) : "");
}

void File::setTestDate(const QDate &value)
{
    m_ui.m_dateTest->setDate(value);
}

void File::setTrialDate(const QDate &value)
{
    m_ui.m_dateTrial->setDate(value);
}

void File::setPhysicianReportDate(const QDate &value)
{
    m_ui.m_dateReport->setDate(value);
}

void File::setPhysicianAdviceDate(const QDate &value)
{
    m_ui.m_dateAdvice->setDate(value);
}

void File::setInsuranceAgreementDate(const QDate &value)
{
    m_ui.m_dateInsurance->setDate(value);
}

void File::setPaymentDate(const QDate &value)
{
    m_ui.m_datePayment->setDate(value);
}

void File::setDeliveryDate(const QDate &value)
{
    m_ui.m_dateDelivery->setDate(value);
}

void File::setExchangeDate(const QDate &value)
{
    m_ui.m_dateExchange->setDate(value);
}

void File::setMaintenanceContractDate(const QDate &value)
{
    m_ui.m_dateMaintenance->setDate(value);
}

void File::showPhysician(int index)
{
    m_ui.l_customerPhysicianStreet->setText(m_ui.m_customerPhysician->itemData(index, ROLE_STREET).toString());
    m_ui.l_customerPhysicianCity->setText(m_ui.m_customerPhysician->itemData(index, ROLE_CITY).toString());
    m_ui.b_letterPhysician->setEnabled(m_ui.m_customerPhysician->itemData(index, ROLE_ID).toInt() >= 0);
}

void File::showInsuranceCompany(int value)
{
    m_ui.b_letterInsurance->setEnabled(value > 0);
}

void File::refreshRechterHoorapparaatLijst(int index)
{
    QString brand = m_ui.m_rightHearingAidBrand->itemText(index);
    QSet<QString> types = m_universe.getHearingAidTypes(brand);
    m_ui.m_rightHearingAidType->clear();
    for (QSet<QString>::iterator it = types.begin(); it != types.end(); ++it)
        m_ui.m_rightHearingAidType->addItem(*it);
}

void File::refreshLinkerHoorapparaatLijst(int index)
{
    QString brand = m_ui.m_leftHearingAidBrand->itemText(index);
    QSet<QString> types = m_universe.getHearingAidTypes(brand);
    m_ui.m_leftHearingAidType->clear();
    for (QSet<QString>::iterator it = types.begin(); it != types.end(); ++it)
        m_ui.m_leftHearingAidType->addItem(*it);
}
