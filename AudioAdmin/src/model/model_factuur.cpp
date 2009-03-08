#include "model_factuur.h"

#include <QDomElement>

using namespace Model;

Factuur::Factuur()
{
}

Factuur::~Factuur()
{
}

void Factuur::fromDomElement(const QDomElement &e)
{
}

QDomElement Factuur::toDomElement() const
{
    QDomElement result;
    result.setTagName("factuur");
    return result;
}
