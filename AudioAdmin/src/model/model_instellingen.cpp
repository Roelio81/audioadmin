#include "model_instellingen.h"

#include <QDomElement>

using namespace Model;

Instellingen::Instellingen()
: QObject()
{
	
}

Instellingen::Instellingen(QDomElement &e)
: QObject()
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
	}
}

Instellingen::~Instellingen()
{
	
}

QString Instellingen::getNaam() const
{
	return m_naam;
}

QString Instellingen::getStraat() const
{
	return m_straat;
}

int Instellingen::getPostcode() const
{
	return m_postcode;
}

QString Instellingen::getGemeente() const
{
	return m_gemeente;
}
