#include "model_arts.h"

#include <QDomElement>

using namespace Model;

Arts::Arts(int id)
: Entiteit()
, m_id(id)
{
}

Arts::~Arts()
{
}

void Arts::fromDomElement(const QDomElement &e)
{
    for (QDomElement element = e.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "voornaam")
        {
            m_voornaam = element.text();
        }
    }

    Entiteit::fromDomElement(e);
}

QDomElement Arts::toDomElement() const
{
    return Entiteit::toDomElement();
}

int Arts::getId() const
{
    return m_id;
}

QString Arts::getVoornaam() const
{
    return m_voornaam;
}

void Arts::setVoornaam(const QString &value)
{
    m_voornaam = value;
}
