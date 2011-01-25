#include "model_mutualiteit.h"

#include <QDomElement>

using namespace Model;

Mutualiteit::Mutualiteit(int id)
: m_id(id)
{
}

Mutualiteit::~Mutualiteit()
{
}

void Mutualiteit::fromDomElement(const QDomElement &e)
{
    Entiteit::fromDomElement(e);
}

QDomElement Mutualiteit::toDomElement(QDomDocument &d) const
{
    QDomElement result = Entiteit::toDomElement(d);
    result.setTagName("mutualiteit");
    result.setAttribute("id", m_id);
    return result;
}

int Mutualiteit::getId() const
{
    return m_id;
}
