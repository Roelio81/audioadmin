#include "view_insurancecompany.h"
#include "view_universe.h"

using namespace View;

InsuranceCompany::InsuranceCompany(Ui::Universe &universe)
: m_universe(universe)
{
}

InsuranceCompany::~InsuranceCompany()
{
}

QString InsuranceCompany::getName() const
{
        return m_universe.m_insuranceCompanyName->text();
}

QString InsuranceCompany::getStreet() const
{
        return m_universe.m_insuranceCompanyStreet->text();
}

int InsuranceCompany::getPostalCode() const
{
        return m_universe.m_insuranceCompanyPostalCode->value();
}

QString InsuranceCompany::getCity() const
{
        return m_universe.m_insuranceCompanyCity->text();
}

QString InsuranceCompany::getTelephone() const
{
        return m_universe.m_insuranceCompanyTelephone->text();
}

QString InsuranceCompany::getComments() const
{
        return m_universe.m_insuranceCompanyComments->toPlainText();
}

void InsuranceCompany::setName(const QString &value)
{
        m_universe.m_insuranceCompanyName->setText(value);
}

void InsuranceCompany::setStreet(const QString &value)
{
        m_universe.m_insuranceCompanyStreet->setText(value);
}

void InsuranceCompany::setPostalCode(int value)
{
        m_universe.m_insuranceCompanyPostalCode->setValue(value);
}

void InsuranceCompany::setCity(const QString &value)
{
        m_universe.m_insuranceCompanyCity->setText(value);
}

void InsuranceCompany::setTelephone(const QString &value)
{
        m_universe.m_insuranceCompanyTelephone->setText(value);
}

void InsuranceCompany::setComments(const QString &value)
{
        m_universe.m_insuranceCompanyComments->setPlainText(value);
}
