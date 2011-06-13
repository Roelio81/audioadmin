#include "model_factuur.h"

#include <QDate>
#include <QDomDocument>
#include <QDomElement>

using namespace Model;

Factuur::Factuur(double standaardBtwPercentage)
    : m_datum(QDate::currentDate())
    , m_vervaldatum(QDate::currentDate().addMonths(1))
    , m_kortingPercentage(0.0)
    , m_btwPercentage(standaardBtwPercentage)
{
}

Factuur::~Factuur()
{
}

QString Factuur::getNummer() const
{
    return m_nummer;
}

QDate Factuur::getDatum() const
{
    return m_datum;
}

QDate Factuur::getVervalDatum() const
{
    return m_vervaldatum;
}

double Factuur::getKortingPercentage() const
{
    return m_kortingPercentage;
}

double Factuur::getBtwPercentage() const
{
    return m_btwPercentage;
}

QString Factuur::getCondities() const
{
    return m_condities;
}

QString Factuur::getTekst() const
{
    return m_tekst;
}

void Factuur::setNummer(const QString &value)
{
    m_nummer = value;
}

void Factuur::setDatum(const QDate &value)
{
    m_datum = value;
}

void Factuur::setVervalDatum(const QDate &value)
{
    m_vervaldatum = value;
}

void Factuur::setKortingPercentage(double value)
{
    m_kortingPercentage = value;
}

void Factuur::setBtwPercentage(double value)
{
    m_btwPercentage = value;
}

void Factuur::setCondities(const QString &value)
{
    m_condities = value;
}

void Factuur::setTekst(const QString &value)
{
    m_tekst = value;
}

void Factuur::fromDomElement(const QDomElement &e)
{
    m_nummer = e.attribute("nummer");
    m_datum = QDate::fromString(e.attribute("datum"), "yyyy-MM-dd");
    m_vervaldatum = QDate::fromString(e.attribute("vervaldatum"), "yyyy-MM-dd");
    for (QDomElement element = e.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "condities")
        {
            m_kortingPercentage = element.attribute("kortingpercentage").toDouble();
            m_btwPercentage = element.attribute("btwpercentage").toDouble();
            m_condities = element.text().replace("\r\n", "\n");
        }
        else if (element.tagName() == "extra")
        {
            m_tekst = element.text().replace("\r\n", "\n");
        }
    }

}

QDomElement Factuur::toDomElement(QDomDocument &d) const
{
    QDomElement result = d.createElement("factuur");
    result.setAttribute("nummer", m_nummer);
    result.setAttribute("datum", m_datum.toString("yyyy-MM-dd"));
    result.setAttribute("vervaldatum", m_vervaldatum.toString("yyyy-MM-dd"));
    QDomElement condities = d.createElement("condities");
    condities.setAttribute("kortingpercentage", m_kortingPercentage);
    condities.setAttribute("btwpercentage", m_btwPercentage);
    condities.appendChild(d.createTextNode(m_condities));
    result.appendChild(condities);
    QDomElement tekst = d.createElement("extra");
    tekst.appendChild(d.createTextNode(m_tekst));
    result.appendChild(tekst);
    return result;
}
