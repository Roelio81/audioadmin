#include "model_klant.h"

#include <QDomElement>

using namespace Model;

Klant::Klant()
{
}

Klant::~Klant()
{
}

void Klant::fromDomElement(const QDomElement &e)
{
	Entiteit::fromDomElement(e);
}

QDomElement Klant::toDomElement() const
{
	return Entiteit::toDomElement();
}
