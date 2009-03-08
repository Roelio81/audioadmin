#include "model_instellingen.h"

#include <QDomElement>

using namespace Model;

Instellingen::Instellingen()
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
                    m_postcode = subelement.attributeNode("postcode").value().toInt();
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

QDomElement Instellingen::toDomElement() const
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
    QDomElement gsm;
    gsm.setTagName("gsm");
    gsm.setNodeValue(m_gsm);
    result.appendChild(gsm);
    QDomElement email;
    email.setTagName("email");
    email.setNodeValue(m_email);
    result.appendChild(email);
    QDomElement onderschrift;
    onderschrift.setTagName("onderschrift");
    onderschrift.setNodeValue(m_gsm);
    result.appendChild(onderschrift);
    QDomElement riziv;
    riziv.setTagName("riziv");
    riziv.setNodeValue(m_riziv);
    result.appendChild(riziv);
    QDomElement btwnr;
    btwnr.setTagName("btwnr");
    btwnr.setNodeValue(m_btwNummer);
    result.appendChild(btwnr);
    QDomElement btwpct;
    btwpct.setTagName("btwpct");
    btwpct.setNodeValue(QString::number(m_btwPercentage));
    result.appendChild(btwpct);
    QDomElement rekeningnr;
    rekeningnr.setTagName("rekeningnr");
    rekeningnr.setNodeValue(m_rekeningNummer);
    result.appendChild(rekeningnr);
    result.setTagName("instellingen");
    return result;
}

QString Instellingen::getNaam() const
{
    return m_naam;
}

QString Instellingen::getStraat() const
{
    return m_straat;
}

int Instellingen::getPostcode() const
{
    return m_postcode;
}

QString Instellingen::getGemeente() const
{
    return m_gemeente;
}

QString Instellingen::getTelefoon() const
{
    return m_telefoon;
}

QString Instellingen::getGsm() const
{
    return m_gsm;
}

QString Instellingen::getEmail() const
{
    return m_email;
}

QString Instellingen::getOnderschrift() const
{
    return m_onderschrift;
}
QString Instellingen::getRiziv() const
{
    return m_riziv;
}

int Instellingen::getBtwPercentage() const
{
    return m_btwPercentage;
}

QString Instellingen::getBtwNummer() const
{
    return m_btwNummer;
}

QString Instellingen::getRekeningNummer() const
{
    return m_rekeningNummer;
}

void Instellingen::setNaam(const QString &value)
{
    m_naam = value;
}

void Instellingen::setStraat(const QString &value)
{
    m_straat = value;
}

void Instellingen::setPostcode(int value)
{
    m_postcode = value;
}

void Instellingen::setGemeente(const QString &value)
{
    m_gemeente = value;
}

void Instellingen::setTelefoon(const QString &value)
{
    m_telefoon = value;
}

void Instellingen::setGsm(const QString &value)
{
    m_gsm = value;
}

void Instellingen::setEmail(const QString &value)
{
    m_email = value;
}

void Instellingen::setOnderschrift(const QString &value)
{
    m_onderschrift = value;
}

void Instellingen::setRiziv(const QString &value)
{
    m_riziv = value;
}

void Instellingen::setBtwPercentage(int value)
{
    m_btwPercentage = value;
}

void Instellingen::setBtwNummer(const QString &value)
{
    m_btwNummer = value;
}

void Instellingen::setRekeningNummer(const QString &value)
{
    m_rekeningNummer = value;
}
