#include "model_customer.h"
#include "model_universe.h"

#include <QDomElement>

using namespace Model;


Customer::Customer(const Universe &universe)
    : m_universe(universe)
    , m_title(MR)
    , m_dateOfBirth(universe.getInvalidDate())
{
}

Customer::~Customer()
{
}

void Customer::fromDomElement(const QDomElement &e)
{
    for (QDomElement element = e.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "title")
        {
            if (element.text() == "mr.")
                m_title = MR;
            else if (element.text() == "mrs.")
                m_title = MRS;
            else
                Q_ASSERT(false);    // Incorrect title!
        }
        else if (element.tagName() == "firstName")
        {
            m_firstName = element.text();
        }
        else if (element.tagName() == "dateOfBirth")
        {
            m_dateOfBirth = QDate::fromString(element.text(), "yyyy-MM-dd");
        }
    }

    Entity::fromDomElement(e);
}

QDomElement Customer::toDomElement(QDomDocument &d) const
{
    QDomElement result = Entity::toDomElement(d);
    QDomElement voornaam = d.createElement("firstName");
    voornaam.appendChild(d.createTextNode(m_firstName));
    result.insertAfter(voornaam, result.firstChildElement("name"));
    QString titleString;
    switch (m_title)
    {
    case MR:
        titleString = "mr.";
        break;
    case MRS:
        titleString = "mrs.";
        break;
    }
    QDomElement title = d.createElement("title");
    title.appendChild(d.createTextNode(titleString));
    result.insertAfter(title, result.firstChildElement("firstName"));
    if (m_dateOfBirth != m_universe.getInvalidDate())
    {
        QDomElement geboorteDatum = d.createElement("dateOfBirth");
        geboorteDatum.appendChild(d.createTextNode(m_dateOfBirth.toString("yyyy-MM-dd")));
        result.insertAfter(geboorteDatum, result.firstChildElement("telephone"));
    }

    result.setTagName("customer");
    return result;
}
