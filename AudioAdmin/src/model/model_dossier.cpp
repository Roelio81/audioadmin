#include "model_dossier.h"

#include <QDomElement>

using namespace Model;

Dossier::Dossier(int id)
: m_id(id)
, m_klant()
{
}

Dossier::~Dossier()
{
}

void Dossier::fromDomElement(const QDomElement &e)
{
	m_klant.fromDomElement(e);
}

QDomElement Dossier::toDomElement() const
{
	return m_klant.toDomElement();
}

Klant &Dossier::getKlant()
{
	return m_klant;
}

int Dossier::getId() const
{
	return m_id;
}
