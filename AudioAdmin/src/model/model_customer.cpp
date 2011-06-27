#include "model_customer.h"
#include "model_universe.h"

#include <QDomElement>

using namespace Model;


Customer::Customer(const Universe &universum)
    : m_universum(universum)
    , m_geboorteDatum(universum.getInvalidDate())
{
}

Customer::~Customer()
{
}

void Customer::fromDomElement(const QDomElement &e)
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

    Entity::fromDomElement(e);
}

QDomElement Customer::toDomElement(QDomDocument &d) const
{
    QDomElement result = Entity::toDomElement(d);
    QDomElement voornaam = d.createElement("voornaam");
    voornaam.appendChild(d.createTextNode(m_voornaam));
    result.insertAfter(voornaam, result.firstChildElement("naam"));
    QDomElement aanspreektitel = d.createElement("aanspreektitel");
    aanspreektitel.appendChild(d.createTextNode(m_aanspreektitel));
    result.insertAfter(aanspreektitel, result.firstChildElement("voornaam"));
    if (m_geboorteDatum != m_universum.getInvalidDate())
    {
        QDomElement geboorteDatum = d.createElement("geboortedatum");
        geboorteDatum.appendChild(d.createTextNode(m_geboorteDatum.toString("yyyy-MM-dd")));
        result.insertAfter(geboorteDatum, result.firstChildElement("telefoon"));
    }

    result.setTagName("klant");
    return result;
}
