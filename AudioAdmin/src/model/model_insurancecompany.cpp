#include "model_insurancecompany.h"

#include <QDomElement>

using namespace Model;

InsuranceCompany::InsuranceCompany(int id)
: m_id(id)
{
}

InsuranceCompany::~InsuranceCompany()
{
}

void InsuranceCompany::fromDomElement(const QDomElement &e)
{
    Entity::fromDomElement(e);
}

QDomElement InsuranceCompany::toDomElement(QDomDocument &d) const
{
    QDomElement result = Entity::toDomElement(d);
    result.setTagName("mutualiteit");
    result.setAttribute("id", m_id);
    return result;
}
