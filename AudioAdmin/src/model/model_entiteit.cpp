#include "model_entiteit.h"

#include <QDomElement>

using namespace Model;

Entiteit::Entiteit()
{
}

Entiteit::~Entiteit()
{
}

void Entiteit::fromDomElement(const QDomElement &e)
{
	for (QDomElement element = e.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
	{
		if (element.tagName() == "naam")
		{
			m_naam = element.text();
		}
		else if (element.tagName() == "adres")
		{
			for (QDomElement subelement = element.firstChildElement(); !subelement.isNull(); subelement = subelement.nextSiblingElement())
			{
				if (subelement.tagName() == "straat")
				{
					m_straat = subelement.text();
				}
				else if (subelement.tagName() == "gemeente")
				{
					m_gemeente = subelement.text();
					m_postcode = subelement.attributeNode("postcode").value().toInt();
				}
			}
		}
		else if (element.tagName() == "telefoon")
		{
			m_telefoon = element.text();
		}
		else if (element.tagName() == "opmerkingen")
		{
			m_opmerkingen = element.text();
		}
	}
}

QDomElement Entiteit::toDomElement() const
{
	return QDomElement();
}

QString Entiteit::getNaam() const
{
	return m_naam;
}

QString Entiteit::getStraat() const
{
	return m_straat;
}

int Entiteit::getPostcode() const
{
	return m_postcode;
}

QString Entiteit::getGemeente() const
{
	return m_gemeente;
}

QString Entiteit::getTelefoon() const
{
	return m_telefoon;
}

QString Entiteit::getOpmerkingen() const
{
	return m_opmerkingen;
}

void Entiteit::setNaam(const QString &value)
{
	m_naam = value;
}

void Entiteit::setStraat(const QString &value)
{
	m_straat = value;
}

void Entiteit::setPostcode(int value)
{
	m_postcode = value;
}

void Entiteit::setGemeente(const QString &value)
{
	m_gemeente = value;
}

void Entiteit::setTelefoon(const QString &value)
{
	m_telefoon = value;
}

void Entiteit::setOpmerkingen(const QString &value)
{
	m_opmerkingen = value;
}
