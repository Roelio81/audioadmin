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
    }

    Entiteit::fromDomElement(e);
}

QDomElement Klant::toDomElement() const
{
    QDomElement result = Entiteit::toDomElement();
    QDomElement aanspreektitel;
    aanspreektitel.setTagName("aanspreektitel");
    aanspreektitel.setNodeValue(m_voornaam);
    result.appendChild(aanspreektitel);
    QDomElement voornaam;
    voornaam.setTagName("voornaam");
    voornaam.setNodeValue(m_voornaam);
    result.appendChild(voornaam);
    result.setTagName("klant");
    return result;
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
