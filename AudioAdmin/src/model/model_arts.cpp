#include "model_arts.h"

#include <QDomElement>

using namespace Model;

Arts::Arts()
: Entiteit()
{
}

Arts::~Arts()
{
}

void Arts::fromDomElement(const QDomElement &e)
{
	Entiteit::fromDomElement(e);
}

QDomElement Arts::toDomElement() const
{
	return Entiteit::toDomElement();
}
