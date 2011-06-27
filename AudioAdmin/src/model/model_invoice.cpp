#include "model_invoice.h"
#include "model_settings.h"
#include "model_universe.h"

#include <QDate>
#include <QDomDocument>
#include <QDomElement>

using namespace Model;

Invoice::Invoice(const Universe &universe)
    : m_universe(universe)
    , m_date(QDate::currentDate())
    , m_expirationDate(QDate::currentDate().addMonths(1))
    , m_reductionPercentage(0.0)
    , m_vatPercentage(universe.getSettings().getVATPercentage())
{
}

Invoice::~Invoice()
{
}

void Invoice::fromDomElement(const QDomElement &e)
{
    m_number = e.attribute("nummer");
    m_date = QDate::fromString(e.attribute("datum"), "yyyy-MM-dd");
    m_expirationDate = QDate::fromString(e.attribute("vervaldatum"), "yyyy-MM-dd");
    for (QDomElement element = e.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "condities")
        {
            m_reductionPercentage = element.attribute("kortingpercentage").toDouble();
            m_vatPercentage = element.attribute("btwpercentage").toDouble();
            m_conditions = element.text().replace("\r\n", "\n");
        }
        else if (element.tagName() == "extra")
        {
            m_text = element.text().replace("\r\n", "\n");
        }
    }

}

QDomElement Invoice::toDomElement(QDomDocument &d) const
{
    QDomElement result = d.createElement("factuur");
    result.setAttribute("nummer", m_number);
    result.setAttribute("datum", m_date.toString("yyyy-MM-dd"));
    result.setAttribute("vervaldatum", m_expirationDate.toString("yyyy-MM-dd"));
    QDomElement conditions = d.createElement("condities");
    conditions.setAttribute("kortingpercentage", m_reductionPercentage);
    conditions.setAttribute("btwpercentage", m_vatPercentage);
    conditions.appendChild(d.createTextNode(m_conditions));
    result.appendChild(conditions);
    QDomElement text = d.createElement("extra");
    text.appendChild(d.createTextNode(m_text));
    result.appendChild(text);
    return result;
}
