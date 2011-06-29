#include "model_physician.h"

#include <QDomElement>

using namespace Model;

Physician::Physician(int id)
: Entity()
, m_id(id)
{
}

Physician::~Physician()
{
}

void Physician::fromDomElement(const QDomElement &e)
{
    for (QDomElement element = e.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "firstName")
        {
            m_firstName = element.text();
        }
    }

    Entity::fromDomElement(e);
}

QDomElement Physician::toDomElement(QDomDocument &d) const
{
    QDomElement result = Entity::toDomElement(d);
    QDomElement firstName = d.createElement("firstName");
    firstName.appendChild(d.createTextNode(m_firstName));
    result.insertAfter(firstName, result.firstChildElement("name"));
    result.setTagName("physician");
    result.setAttribute("id", m_id);
    return result;
}
