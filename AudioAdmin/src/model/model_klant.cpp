#include "model_klant.h"

#include <QDomElement>

using namespace Model;

namespace
{
    QDate ongeldigeDatum(1900, 1, 1);
}

Klant::Klant()
: m_geboorteDatum(ongeldigeDatum)
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
        else if (element.tagName() == "geboortedatum")
        {
            m_geboorteDatum = QDate::fromString(element.text(), "yyyy-MM-dd");
        }
    }

    Entiteit::fromDomElement(e);
}

QDomElement Klant::toDomElement(QDomDocument &d) const
{
    QDomElement result = Entiteit::toDomElement(d);
    QDomElement voornaam = d.createElement("voornaam");
    voornaam.appendChild(d.createTextNode(m_voornaam));
    result.insertAfter(voornaam, result.firstChildElement("naam"));
    QDomElement aanspreektitel = d.createElement("aanspreektitel");
    aanspreektitel.appendChild(d.createTextNode(m_aanspreektitel));
    result.insertAfter(aanspreektitel, result.firstChildElement("voornaam"));
    if (m_geboorteDatum != ongeldigeDatum)
    {
        QDomElement geboorteDatum = d.createElement("geboortedatum");
        geboorteDatum.appendChild(d.createTextNode(m_geboorteDatum.toString("yyyy-MM-dd")));
        result.appendChild(geboorteDatum);
    }

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
