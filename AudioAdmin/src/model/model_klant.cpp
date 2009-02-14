#include "model_klant.h"

#include <QDomElement>

using namespace Model;

Klant::Klant()
{
}

Klant::~Klant()
{
}

void Klant::fromDomElement(const QDomElement &e)
{
	for (QDomElement element = e.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
	{
		if (element.tagName() == "aanspreektitel")
		{
			m_aanspreektitel = element.text();
		}
		else if (element.tagName() == "voornaam")
		{
			m_voornaam = element.text();
		}
		else if (element.tagName() == "aanpassing")
		{
			m_plaatsAanpassing = element.text();
		}
		else if (element.tagName() == "mutualiteit")
		{
			m_mutualiteit = element.attributeNode("id").value().toInt();
			m_aansluitingsnummer = element.attributeNode("aansluitingsnummer").value();
		}
	}

	Entiteit::fromDomElement(e);
}

QDomElement Klant::toDomElement() const
{
	return Entiteit::toDomElement();
}

QString Klant::getAanspreektitel() const
{
	return m_aanspreektitel;
}

QString Klant::getVoornaam() const
{
	return m_voornaam;
}

QDate Klant::getGeboorteDatum() const
{
	return m_geboorteDatum;
}

int Klant::getMutualiteit() const
{
	return m_mutualiteit;
}

QString Klant::getAansluitingsnummer() const
{
	return m_aansluitingsnummer;
}

QString Klant::getPlaatsAanpassing() const
{
	return m_plaatsAanpassing;
}

void Klant::setAanspreektitel(const QString &value)
{
	m_aanspreektitel = value;
}

void Klant::setVoornaam(const QString &value)
{
	m_voornaam = value;
}

void Klant::setGeboorteDatum(const QDate &value)
{
	m_geboorteDatum = value;
}

void Klant::setMutualiteit(int value)
{
	m_mutualiteit = value;
}

void Klant::setAansluitingsnummer(const QString &value)
{
	m_aansluitingsnummer = value;
}

void Klant::setPlaatsAanpassing(const QString &value)
{
	m_plaatsAanpassing = value;
}
