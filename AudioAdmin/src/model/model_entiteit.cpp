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
                    m_postcode = subelement.attribute("postcode").toInt();
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
    QDomElement result;
    QDomElement naam;
    naam.setTagName("naam");
    naam.setNodeValue(m_naam);
    result.appendChild(naam);
    QDomElement adres;
    adres.setTagName("adres");
    QDomElement straat;
    straat.setTagName("straat");
    straat.setNodeValue(m_straat);
    adres.appendChild(straat);
    QDomElement gemeente;
    gemeente.setTagName("gemeente");
    gemeente.setNodeValue(m_gemeente);
    gemeente.setAttribute("postcode", QString::number(m_postcode));
    adres.appendChild(gemeente);
    result.appendChild(adres);
    QDomElement telefoon;
    telefoon.setTagName("telefoon");
    telefoon.setNodeValue(m_telefoon);
    result.appendChild(telefoon);
    QDomElement opmerkingen;
    opmerkingen.setTagName("opmerkingen");
    opmerkingen.setNodeValue(m_opmerkingen);
    result.appendChild(opmerkingen);
    result.setTagName("entiteit");
    return result;
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
