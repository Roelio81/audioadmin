#include "model_factuur.h"
#include "model_instellingen.h"
#include "model_universum.h"

#include <QDate>
#include <QDomDocument>
#include <QDomElement>

using namespace Model;

Factuur::Factuur(const Universum &universum)
    : m_universum(universum)
    , m_datum(QDate::currentDate())
    , m_vervaldatum(QDate::currentDate().addMonths(1))
    , m_kortingPercentage(0.0)
    , m_btwPercentage(universum.getInstellingen().getBtwPercentage())
{
}

Factuur::~Factuur()
{
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
