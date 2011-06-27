#include "view_insurancecompany.h"
#include "view_universe.h"

using namespace View;

InsuranceCompany::InsuranceCompany(Ui::Universe &universe)
: m_universum(universe)
{
}

InsuranceCompany::~InsuranceCompany()
{
}

QString InsuranceCompany::getName() const
{
	return m_universum.m_mutualiteitNaam->text();
}

QString InsuranceCompany::getStreet() const
{
	return m_universum.m_mutualiteitStraat->text();
}

int InsuranceCompany::getPostalCode() const
{
	return m_universum.m_mutualiteitPostcode->value();
}

QString InsuranceCompany::getCity() const
{
	return m_universum.m_mutualiteitGemeente->text();
}

QString InsuranceCompany::getTelephone() const
{
	return m_universum.m_mutualiteitTelefoon->text();
}

QString InsuranceCompany::getComments() const
{
	return m_universum.m_mutualiteitOpmerkingen->toPlainText();
}

void InsuranceCompany::setName(const QString &value)
{
	m_universum.m_mutualiteitNaam->setText(value);
}

void InsuranceCompany::setStreet(const QString &value)
{
	m_universum.m_mutualiteitStraat->setText(value);
}

void InsuranceCompany::setPostalCode(int value)
{
	m_universum.m_mutualiteitPostcode->setValue(value);
}

void InsuranceCompany::setCity(const QString &value)
{
	m_universum.m_mutualiteitGemeente->setText(value);
}

void InsuranceCompany::setTelephone(const QString &value)
{
	m_universum.m_mutualiteitTelefoon->setText(value);
}

void InsuranceCompany::setComments(const QString &value)
{
	m_universum.m_mutualiteitOpmerkingen->setPlainText(value);
}
