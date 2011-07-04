#include "model_settings.h"

#include <QDomElement>

using namespace Model;

Settings::Settings(const Universe &universe)
    : m_universe(universe)
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
        else if (element.tagName() == "mobile")
        {
            m_mobilePhone = element.text();
        }
        else if (element.tagName() == "email")
        {
            m_email = element.text();
        }
        else if (element.tagName() == "caption")
        {
            m_caption = element.text();
        }
        else if (element.tagName() == "natId")
        {
            m_nationalId = element.text();
        }
        else if (element.tagName() == "vatNr")
        {
            m_vatNumber = element.text();
        }
        else if (element.tagName() == "vatPct")
        {
            m_vatPercentage = element.text().toInt();
        }
        else if (element.tagName() == "bankAccount")
        {
            m_bankAccount = element.text();
        }
    }
}

QDomElement Settings::toDomElement(QDomDocument &d) const
{
    QDomElement result = d.createElement("settings");
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
    QDomElement telephone = d.createElement("telephone");
    telephone.appendChild(d.createTextNode(m_telephone));
    result.appendChild(telephone);
    QDomElement mobilePhone = d.createElement("mobile");
    mobilePhone.appendChild(d.createTextNode(m_mobilePhone));
    result.appendChild(mobilePhone);
    QDomElement caption = d.createElement("caption");
    caption.appendChild(d.createTextNode(m_caption));
    result.appendChild(caption);
    QDomElement email = d.createElement("email");
    email.appendChild(d.createTextNode(m_email));
    result.appendChild(email);
    QDomElement vatNumber = d.createElement("vatNr");
    vatNumber.appendChild(d.createTextNode(m_vatNumber));
    result.appendChild(vatNumber);
    QDomElement bankAccount = d.createElement("bankAccount");
    bankAccount.appendChild(d.createTextNode(m_bankAccount));
    result.appendChild(bankAccount);
    QDomElement nationalId = d.createElement("natId");
    nationalId.appendChild(d.createTextNode(m_nationalId));
    result.appendChild(nationalId);
    QDomElement vatPercentage = d.createElement("vatPct");
    vatPercentage.appendChild(d.createTextNode(QString::number(m_vatPercentage)));
    result.appendChild(vatPercentage);
    return result;
}
