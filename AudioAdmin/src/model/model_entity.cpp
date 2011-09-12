#include "model_entity.h"

#include <QDomElement>

using namespace Model;

Entity::Entity()
: m_postalCode(1000)
{
}

Entity::~Entity()
{
}

void Entity::fromDomElement(const QDomElement &e)
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
                    m_postalCode = subelement.attribute("postalCode").toInt();
                }
            }
        }
        else if (element.tagName() == "telephone")
        {
            m_telephone = element.text();
        }
        else if (element.tagName() == "comments")
        {
            m_comments = element.text().replace("\r\n", "\n");
        }
    }
}

QDomElement Entity::toDomElement(QDomDocument &d) const
{
    QDomElement result = d.createElement("entity");
    QDomElement name = d.createElement("name");
    name.appendChild(d.createTextNode(m_name));
    result.appendChild(name);
    QDomElement address = d.createElement("address");
    QDomElement street = d.createElement("street");
    street.appendChild(d.createTextNode(m_street));
    address.appendChild(street);
    QDomElement city = d.createElement("city");
    city.appendChild(d.createTextNode(m_city));
    city.setAttribute("postalCode", QString::number(m_postalCode));
    address.appendChild(city);
    result.appendChild(address);
    if (!m_telephone.isEmpty())
    {
        QDomElement telephone = d.createElement("telephone");
        telephone.appendChild(d.createTextNode(m_telephone));
        result.appendChild(telephone);
    }
    QDomElement comments = d.createElement("comments");
    comments.appendChild(d.createTextNode(QString(m_comments).replace("\n", "\r\n")));
    result.appendChild(comments);
    return result;
}
