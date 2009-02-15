#include "model_dossier.h"

#include <QDomElement>

using namespace Model;

Dossier::Dossier(int id)
: m_id(id)
, m_klant()
, m_arts(-1)
{
}

Dossier::~Dossier()
{
}

void Dossier::fromDomElement(const QDomElement &e)
{
	for (QDomElement element = e.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
	{
		if (element.tagName() == "nkoArts")
		{
			m_arts = element.attributeNode("id").value().toInt();
		}
	}

	m_klant.fromDomElement(e);
}

QDomElement Dossier::toDomElement() const
{
	return m_klant.toDomElement();
}

Klant &Dossier::getKlant()
{
	return m_klant;
}

int Dossier::getId() const
{
	return m_id;
}

int Dossier::getArts() const
{
	return m_arts;
}

void Dossier::setArts(int value)
{
	m_arts = value;
}
