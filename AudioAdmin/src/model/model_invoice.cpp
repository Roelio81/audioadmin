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
    m_number = e.attribute("nr");
    m_date = QDate::fromString(e.attribute("date"), "yyyy-MM-dd");
    m_expirationDate = QDate::fromString(e.attribute("expDate"), "yyyy-MM-dd");
    for (QDomElement element = e.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "conditions")
        {
            m_reductionPercentage = element.attribute("reduction").toDouble();
            m_vatPercentage = element.attribute("vat").toDouble();
            m_conditions = element.text().replace("\r\n", "\n");
        }
        else if (element.tagName() == "text")
        {
            m_text = element.text().replace("\r\n", "\n");
        }
    }

}

QDomElement Invoice::toDomElement(QDomDocument &d) const
{
    QDomElement result = d.createElement("invoice");
    result.setAttribute("nr", m_number);
    result.setAttribute("date", m_date.toString("yyyy-MM-dd"));
    result.setAttribute("expDate", m_expirationDate.toString("yyyy-MM-dd"));
    QDomElement conditions = d.createElement("conditions");
    conditions.setAttribute("reduction", m_reductionPercentage);
    conditions.setAttribute("vat", m_vatPercentage);
    conditions.appendChild(d.createTextNode(m_conditions));
    result.appendChild(conditions);
    QDomElement text = d.createElement("text");
    text.appendChild(d.createTextNode(m_text));
    result.appendChild(text);
    return result;
}
