#include "view_dossier.h"
#include "view_universum.h"

using namespace View;

Dossier::Dossier(Universum &universum)
: m_universum(universum)
{
}

Dossier::~Dossier()
{
}

void Dossier::setKlantNaam(const QString &value)
{
	m_universum.m_klantNaam->setText(value);
}
