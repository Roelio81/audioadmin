#include "model_entiteit.h"

#include <QDomElement>

using namespace Model;

Entiteit::Entiteit()
: m_postcode(1000)
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
            m_opmerkingen = element.text().replace("\r\n", "\n");
        }
    }
}

QDomElement Entiteit::toDomElement(QDomDocument &d) const
{
    QDomElement result = d.createElement("entiteit");
    QDomElement naam = d.createElement("naam");
    naam.appendChild(d.createTextNode(m_naam));
    result.appendChild(naam);
    QDomElement adres = d.createElement("adres");
    QDomElement straat = d.createElement("straat");
    straat.appendChild(d.createTextNode(m_straat));
    adres.appendChild(straat);
    QDomElement gemeente = d.createElement("gemeente");
    gemeente.appendChild(d.createTextNode(m_gemeente));
    gemeente.setAttribute("postcode", QString::number(m_postcode));
    adres.appendChild(gemeente);
    result.appendChild(adres);
    QDomElement telefoon = d.createElement("telefoon");
    telefoon.appendChild(d.createTextNode(m_telefoon));
    result.appendChild(telefoon);
    QDomElement opmerkingen = d.createElement("opmerkingen");
    opmerkingen.appendChild(d.createTextNode(QString(m_opmerkingen).replace("\n", "\r\n")));
    result.appendChild(opmerkingen);
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
