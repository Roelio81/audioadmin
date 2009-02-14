#include "view_arts.h"
#include "view_universum.h"

using namespace View;

Arts::Arts(Universum &universum)
: m_universum(universum)
{
}

Arts::~Arts()
{
}

QString Arts::getNaam() const
{
	return m_universum.m_artsNaam->text();
}

QString Arts::getVoornaam() const
{
	return m_universum.m_artsVoornaam->text();
}

QString Arts::getStraat() const
{
	return m_universum.m_artsStraat->text();
}

int Arts::getPostcode() const
{
	return m_universum.m_artsPostcode->value();
}

QString Arts::getGemeente() const
{
	return m_universum.m_artsGemeente->text();
}

QString Arts::getTelefoon() const
{
	return m_universum.m_artsTelefoon->text();
}

QString Arts::getOpmerkingen() const
{
	return m_universum.m_artsOpmerkingen->toPlainText();
}

void Arts::setNaam(const QString &value)
{
	m_universum.m_artsNaam->setText(value);
}

void Arts::setVoornaam(const QString &value)
{
	m_universum.m_artsVoornaam->setText(value);
}

void Arts::setStraat(const QString &value)
{
	m_universum.m_artsStraat->setText(value);
}

void Arts::setPostcode(int value)
{
	m_universum.m_artsPostcode->setValue(value);
}

void Arts::setGemeente(const QString &value)
{
	m_universum.m_artsGemeente->setText(value);
}

void Arts::setTelefoon(const QString &value)
{
	m_universum.m_artsTelefoon->setText(value);
}

void Arts::setOpmerkingen(const QString &value)
{
	m_universum.m_artsOpmerkingen->setPlainText(value);
}
