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
    m_ui.m_klantArts->setModel(&m_physicianList);
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
    m_ui.m_klantMutualiteit->setModel(&m_insuranceCompanyList);
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
    int index = m_ui.m_klantMutualiteit->currentIndex();
    return m_ui.m_klantMutualiteit->itemData(index, ROLE_ID).toInt();
}

QString File::getMemberNumber() const
{
    return m_ui.m_aansluitingsnummer->text();
}

QString File::getPlaceAdjustment() const
{
    return m_ui.m_plaatsAanpassing->text();
}

int File::getPhysician() const
{
    int index = m_ui.m_klantArts->currentIndex();
    return m_ui.m_klantArts->itemData(index, ROLE_ID).toInt();
}

QString File::getRightHearingAidBrand() const
{
    return m_ui.m_rechterHoorapparaatMerk->currentText();
}

QString File::getRightHearingAidType() const
{
    return m_ui.m_rechterHoorapparaatType->currentText();
}

QString File::getRightHearingAidSerialNumber() const
{
    return m_ui.m_rechterHoorapparaatSerienummer->text();
}

double File::getRightHearingAidPrice() const
{
    return m_ui.m_rechterHoorapparaatPrijs->text().toDouble();
}

QString File::getLeftHearingAidBrand() const
{
    return m_ui.m_linkerHoorapparaatMerk->currentText();
}

QString File::getLeftHearingAidType() const
{
    return m_ui.m_linkerHoorapparaatType->currentText();
}

QString File::getLeftHearingAidSerialNumber() const
{
    return m_ui.m_linkerHoorapparaatSerienummer->text();
}

double File::getLeftHearingAidPrice() const
{
    return m_ui.m_linkerHoorapparaatPrijs->text().toDouble();
}


QDate File::getTestDate() const
{
    return m_ui.m_datumOnderzoek->date();
}

QDate File::getTrialDate() const
{
    return m_ui.m_datumProef->date();
}

QDate File::getPhysicianReportDate() const
{
    return m_ui.m_datumNKO->date();
}

QDate File::getPhysicianAdviceDate() const
{
    return m_ui.m_datumAdviseur->date();
}

QDate File::getInsuranceAgreementDate() const
{
    return m_ui.m_datumMutualiteit->date();
}

QDate File::getPaymentDate() const
{
    return m_ui.m_datumBetaling->date();
}

QDate File::getDeliveryDate() const
{
    return m_ui.m_datumAflevering->date();
}

QDate File::getExchangeDate() const
{
    return m_ui.m_datumWissel->date();
}

QDate File::getMaintenanceContractDate() const
{
    return m_ui.m_datumOnderhoudsContract->date();
}

void File::setInsuranceCompany(int id)
{
    for (int iRow = 0; iRow < m_insuranceCompanyList.rowCount(); ++iRow)
    {
        if (id == m_ui.m_klantMutualiteit->itemData(iRow, ROLE_ID).toInt())
        {
            m_ui.m_klantMutualiteit->setCurrentIndex(iRow);
            m_ui.b_mutualiteitBrief->setEnabled(true);
            return;
        }
    }

    m_ui.m_klantMutualiteit->setCurrentIndex(0);
    m_ui.b_mutualiteitBrief->setEnabled(false);
}

void File::setMemberNumber(const QString &value)
{
    m_ui.m_aansluitingsnummer->setText(value);
}

void File::setPlaceAdjustment(const QString &value)
{
    m_ui.m_plaatsAanpassing->setText(value);
}

void File::setPhysician(int id)
{
    for (int iRow = 0; iRow < m_physicianList.rowCount(); ++iRow)
    {
        if (id == m_ui.m_klantArts->itemData(iRow, ROLE_ID).toInt())
        {
            m_ui.m_klantArts->setCurrentIndex(iRow);
            m_ui.b_artsBrief->setEnabled(true);
            return;
        }
    }

    m_ui.m_klantArts->setCurrentIndex(0);
    m_ui.b_artsBrief->setEnabled(false);
}

void File::setRightHearingAidBrand(const QString &value)
{
    QSet<QString> merken = m_universe.getMerkHoorapparaten();
    m_ui.m_rechterHoorapparaatMerk->clear();
    int index = 0;
    bool itemGevonden = false;
    for (QSet<QString>::iterator itMerk = merken.begin(); itMerk != merken.end(); ++itMerk, ++index)
    {
        m_ui.m_rechterHoorapparaatMerk->addItem(*itMerk);
        if (*itMerk == value)
        {
            m_ui.m_rechterHoorapparaatMerk->setCurrentIndex(index);
            itemGevonden = true;
        }
    }
    if (! itemGevonden)
    {
        m_ui.m_rechterHoorapparaatMerk->addItem(value);
        m_ui.m_rechterHoorapparaatMerk->setCurrentIndex(index);
    }
}

void File::setRightHearingAidType(const QString &value)
{
    QString merk = getRightHearingAidBrand();
    QSet<QString> types = m_universe.getTypeHoorapparaten(merk);
    m_ui.m_rechterHoorapparaatType->setEditText(value);
    int index = 0;
    bool itemGevonden = false;
    for (QSet<QString>::iterator itType = types.begin(); itType != types.end(); ++itType, ++index)
    {
        m_ui.m_rechterHoorapparaatType->addItem(*itType);
        if (*itType == value)
        {
            m_ui.m_rechterHoorapparaatType->setCurrentIndex(index);
            itemGevonden = true;
        }
    }
    if (! itemGevonden)
    {
        m_ui.m_rechterHoorapparaatType->addItem(value);
        m_ui.m_rechterHoorapparaatType->setCurrentIndex(index);
    }
}

void File::setRightHearingAidSerialNumber(const QString &value)
{
    m_ui.m_rechterHoorapparaatSerienummer->setText(value);
}

void File::setRightHearingAidPrice(double value)
{
    m_ui.m_rechterHoorapparaatPrijs->setText(value > 0.0 ? QString::number(value) : "");
}

void File::setLeftHearingAidBrand(const QString &value)
{
    QSet<QString> merken = m_universe.getMerkHoorapparaten();
    m_ui.m_linkerHoorapparaatMerk->clear();
    int index = 0;
    bool itemGevonden = false;
    for (QSet<QString>::iterator itMerk = merken.begin(); itMerk != merken.end(); ++itMerk, ++index)
    {
        m_ui.m_linkerHoorapparaatMerk->addItem(*itMerk);
        if (*itMerk == value)
        {
            m_ui.m_linkerHoorapparaatMerk->setCurrentIndex(index);
            itemGevonden = true;
        }
    }
    if (! itemGevonden)
    {
        m_ui.m_linkerHoorapparaatMerk->addItem(value);
        m_ui.m_linkerHoorapparaatMerk->setCurrentIndex(index);
    }
}

void File::setLeftHearingAidType(const QString &value)
{
    QString merk = getLeftHearingAidBrand();
    QSet<QString> types = m_universe.getTypeHoorapparaten(merk);
    m_ui.m_linkerHoorapparaatType->setEditText(value);
    int index = 0;
    bool itemGevonden = false;
    for (QSet<QString>::iterator itType = types.begin(); itType != types.end(); ++itType, ++index)
    {
        m_ui.m_linkerHoorapparaatType->addItem(*itType);
        if (*itType == value)
        {
            m_ui.m_linkerHoorapparaatType->setCurrentIndex(index);
            itemGevonden = true;
        }
    }
    if (! itemGevonden)
    {
        m_ui.m_linkerHoorapparaatType->addItem(value);
        m_ui.m_linkerHoorapparaatType->setCurrentIndex(index);
    }
}

void File::setLeftHearingAidSerialNumber(const QString &value)
{
    m_ui.m_linkerHoorapparaatSerienummer->setText(value);
}

void File::setLeftHearingAidPrice(double value)
{
    m_ui.m_linkerHoorapparaatPrijs->setText(value > 0.0 ? QString::number(value) : "");
}

void File::setTestDate(const QDate &value)
{
    m_ui.m_datumOnderzoek->setDate(value);
}

void File::setTrialDate(const QDate &value)
{
    m_ui.m_datumProef->setDate(value);
}

void File::setPhysicianReportDate(const QDate &value)
{
    m_ui.m_datumNKO->setDate(value);
}

void File::setPhysicianAdviceDate(const QDate &value)
{
    m_ui.m_datumAdviseur->setDate(value);
}

void File::setInsuranceAgreementDate(const QDate &value)
{
    m_ui.m_datumMutualiteit->setDate(value);
}

void File::setPaymentDate(const QDate &value)
{
    m_ui.m_datumBetaling->setDate(value);
}

void File::setDeliveryDate(const QDate &value)
{
    m_ui.m_datumAflevering->setDate(value);
}

void File::setExchangeDate(const QDate &value)
{
    m_ui.m_datumWissel->setDate(value);
}

void File::setMaintenanceContractDate(const QDate &value)
{
    m_ui.m_datumOnderhoudsContract->setDate(value);
}

void File::showPhysician(int index)
{
    m_ui.l_klantArtsStraat->setText(m_ui.m_klantArts->itemData(index, ROLE_STREET).toString());
    m_ui.l_klantArtsGemeente->setText(m_ui.m_klantArts->itemData(index, ROLE_CITY).toString());
    m_ui.b_artsBrief->setEnabled(m_ui.m_klantArts->itemData(index, ROLE_ID).toInt() >= 0);
}

void File::showInsuranceCompany(int value)
{
    m_ui.b_mutualiteitBrief->setEnabled(value > 0);
}

void File::refreshRechterHoorapparaatLijst(int indexMerk)
{
    QString merk = m_ui.m_rechterHoorapparaatMerk->itemText(indexMerk);
    QSet<QString> types = m_universe.getTypeHoorapparaten(merk);
    m_ui.m_rechterHoorapparaatType->clear();
    for (QSet<QString>::iterator itType = types.begin(); itType != types.end(); ++itType)
        m_ui.m_rechterHoorapparaatType->addItem(*itType);
}

void File::refreshLinkerHoorapparaatLijst(int indexMerk)
{
    QString merk = m_ui.m_linkerHoorapparaatMerk->itemText(indexMerk);
    QSet<QString> types = m_universe.getTypeHoorapparaten(merk);
    m_ui.m_linkerHoorapparaatType->clear();
    for (QSet<QString>::iterator itType = types.begin(); itType != types.end(); ++itType)
        m_ui.m_linkerHoorapparaatType->addItem(*itType);
}
