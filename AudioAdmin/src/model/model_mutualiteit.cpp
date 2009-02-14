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

QDomElement Mutualiteit::toDomElement() const
{
	return Mutualiteit::toDomElement();
}

int Mutualiteit::getId() const
{
	return m_id;
}
