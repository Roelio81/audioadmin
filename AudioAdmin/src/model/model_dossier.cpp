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
        else if (element.tagName() == "audiometrie")
        {
            m_meetgegevens.fromDomElement(element);
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

Meetgegevens &Dossier::getMeetgegevens()
{
    return m_meetgegevens;
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
