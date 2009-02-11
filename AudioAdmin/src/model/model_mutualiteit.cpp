#include "model_mutualiteit.h"

#include <QDomElement>

using namespace Model;

Mutualiteit::Mutualiteit()
{
}

Mutualiteit::~Mutualiteit()
{
}

void Mutualiteit::fromDomElement(const QDomElement &e)
{
	Entiteit::fromDomElement(e);
}

QDomElement Mutualiteit::toDomElement() const
{
	return Mutualiteit::toDomElement();
}
