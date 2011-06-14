#include "model_instellingen.h"

#include <QDomElement>

using namespace Model;

Instellingen::Instellingen(const Universum &universum)
    : m_universum(universum)
{
}

Instellingen::~Instellingen()
{
}

void Instellingen::fromDomElement(const QDomElement &e)
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
        else if (element.tagName() == "gsm")
        {
            m_gsm = element.text();
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

QDomElement Instellingen::toDomElement(QDomDocument &d) const
{
    QDomElement result = d.createElement("instellingen");
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
    QDomElement gsm = d.createElement("gsm");
    gsm.appendChild(d.createTextNode(m_gsm));
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
