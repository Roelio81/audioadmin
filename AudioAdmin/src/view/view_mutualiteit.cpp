#include "view_mutualiteit.h"
#include "view_universum.h"

using namespace View;

Mutualiteit::Mutualiteit(Universum &universum)
: m_universum(universum)
{
}

Mutualiteit::~Mutualiteit()
{
}

QString Mutualiteit::getNaam() const
{
	return m_universum.m_mutualiteitNaam->text();
}

QString Mutualiteit::getStraat() const
{
	return m_universum.m_mutualiteitStraat->text();
}

int Mutualiteit::getPostcode() const
{
	return m_universum.m_mutualiteitPostcode->value();
}

QString Mutualiteit::getGemeente() const
{
	return m_universum.m_mutualiteitGemeente->text();
}

QString Mutualiteit::getTelefoon() const
{
	return m_universum.m_mutualiteitTelefoon->text();
}

QString Mutualiteit::getOpmerkingen() const
{
	return m_universum.m_mutualiteitOpmerkingen->toPlainText();
}

void Mutualiteit::setNaam(const QString &value)
{
	m_universum.m_mutualiteitNaam->setText(value);
}

void Mutualiteit::setStraat(const QString &value)
{
	m_universum.m_mutualiteitStraat->setText(value);
}

void Mutualiteit::setPostcode(int value)
{
	m_universum.m_mutualiteitPostcode->setValue(value);
}

void Mutualiteit::setGemeente(const QString &value)
{
	m_universum.m_mutualiteitGemeente->setText(value);
}

void Mutualiteit::setTelefoon(const QString &value)
{
	m_universum.m_mutualiteitTelefoon->setText(value);
}

void Mutualiteit::setOpmerkingen(const QString &value)
{
	m_universum.m_mutualiteitOpmerkingen->setPlainText(value);
}
