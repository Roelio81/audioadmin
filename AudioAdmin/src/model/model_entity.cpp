#include "model_entity.h"

#include <QDomElement>

using namespace Model;

Entity::Entity()
: m_postalCode(1000)
{
}

Entity::~Entity()
{
}

void Entity::fromDomElement(const QDomElement &e)
{
    for (QDomElement element = e.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "naam")
        {
            m_name = element.text();
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
                    m_city = subelement.text();
                    m_postalCode = subelement.attribute("postcode").toInt();
                }
            }
        }
        else if (element.tagName() == "telefoon")
        {
            m_telephone = element.text();
        }
        else if (element.tagName() == "opmerkingen")
        {
            m_comments = element.text().replace("\r\n", "\n");
        }
    }
}

QDomElement Entity::toDomElement(QDomDocument &d) const
{
    QDomElement result = d.createElement("entiteit");
    QDomElement naam = d.createElement("naam");
    naam.appendChild(d.createTextNode(m_name));
    result.appendChild(naam);
    QDomElement adres = d.createElement("adres");
    QDomElement straat = d.createElement("straat");
    straat.appendChild(d.createTextNode(m_straat));
    adres.appendChild(straat);
    QDomElement gemeente = d.createElement("gemeente");
    gemeente.appendChild(d.createTextNode(m_city));
    gemeente.setAttribute("postcode", QString::number(m_postalCode));
    adres.appendChild(gemeente);
    result.appendChild(adres);
    QDomElement telefoon = d.createElement("telefoon");
    telefoon.appendChild(d.createTextNode(m_telephone));
    result.appendChild(telefoon);
    QDomElement opmerkingen = d.createElement("opmerkingen");
    opmerkingen.appendChild(d.createTextNode(QString(m_comments).replace("\n", "\r\n")));
    result.appendChild(opmerkingen);
    return result;
}
