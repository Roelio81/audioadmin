#include "model_settings.h"

#include <QDomElement>

using namespace Model;

Settings::Settings(const Universe &universum)
    : m_universum(universum)
{
}

Settings::~Settings()
{
}

void Settings::fromDomElement(const QDomElement &e)
{
    for (QDomElement element = e.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "name")
        {
            m_name = element.text();
        }
        else if (element.tagName() == "address")
        {
            for (QDomElement subelement = element.firstChildElement(); !subelement.isNull(); subelement = subelement.nextSiblingElement())
            {
                if (subelement.tagName() == "street")
                {
                    m_street = subelement.text();
                }
                else if (subelement.tagName() == "city")
                {
                    m_city = subelement.text();
                    m_postalCode = subelement.attribute("postalCcode").toInt();
                }
            }
        }
        else if (element.tagName() == "telephone")
        {
            m_telephone = element.text();
        }
        else if (element.tagName() == "gsm")
        {
            m_mobilePhone = element.text();
        }
        else if (element.tagName() == "email")
        {
            m_email = element.text();
        }
        else if (element.tagName() == "onderschrift")
        {
            m_onderschrift = element.text();
        }
        else if (element.tagName() == "riziv")
        {
            m_riziv = element.text();
        }
        else if (element.tagName() == "btwnr")
        {
            m_btwNummer = element.text();
        }
        else if (element.tagName() == "btwpct")
        {
            m_btwPercentage = element.text().toInt();
        }
        else if (element.tagName() == "rekeningnr")
        {
            m_rekeningNummer = element.text();
        }
    }
}

QDomElement Settings::toDomElement(QDomDocument &d) const
{
    QDomElement result = d.createElement("settings");
    QDomElement naam = d.createElement("name");
    naam.appendChild(d.createTextNode(m_name));
    result.appendChild(naam);
    QDomElement adres = d.createElement("address");
    QDomElement straat = d.createElement("straat");
    straat.appendChild(d.createTextNode(m_street));
    adres.appendChild(straat);
    QDomElement gemeente = d.createElement("gemeente");
    gemeente.appendChild(d.createTextNode(m_city));
    gemeente.setAttribute("postcode", QString::number(m_postalCode));
    adres.appendChild(gemeente);
    result.appendChild(adres);
    QDomElement telefoon = d.createElement("telefoon");
    telefoon.appendChild(d.createTextNode(m_telephone));
    result.appendChild(telefoon);
    QDomElement gsm = d.createElement("gsm");
    gsm.appendChild(d.createTextNode(m_mobilePhone));
    result.appendChild(gsm);
    QDomElement onderschrift = d.createElement("onderschrift");
    onderschrift.appendChild(d.createTextNode(m_onderschrift));
    result.appendChild(onderschrift);
    QDomElement email = d.createElement("email");
    email.appendChild(d.createTextNode(m_email));
    result.appendChild(email);
    QDomElement btwnr = d.createElement("btwnr");
    btwnr.appendChild(d.createTextNode(m_btwNummer));
    result.appendChild(btwnr);
    QDomElement rekeningnr = d.createElement("rekeningnr");
    rekeningnr.appendChild(d.createTextNode(m_rekeningNummer));
    result.appendChild(rekeningnr);
    QDomElement riziv = d.createElement("riziv");
    riziv.appendChild(d.createTextNode(m_riziv));
    result.appendChild(riziv);
    QDomElement btwpct = d.createElement("btwpct");
    btwpct.appendChild(d.createTextNode(QString::number(m_btwPercentage)));
    result.appendChild(btwpct);
    return result;
}
