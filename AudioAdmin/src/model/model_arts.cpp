#include "model_arts.h"

#include <QDomElement>

using namespace Model;

Arts::Arts(int id)
: Entiteit()
, m_id(id)
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

int Arts::getId() const
{
	return m_id;
}
