#include "worldmodel.h"

WorldModel::WorldModel(const QString &bestandsNaam)
: QObject()
, m_bestandsNaam(bestandsNaam)
{
}

WorldModel::~WorldModel()
{
}

bool WorldModel::load()
{
	return true;
}

void WorldModel::load(QString bestandsNaam)
{
	const QString &origNaam = m_bestandsNaam;
	m_bestandsNaam = bestandsNaam;
	bool succes = load();
	m_bestandsNaam = origNaam;
}

bool WorldModel::save()
{
	return true;
}

void WorldModel::save(QString bestandsNaam)
{
	const QString &origNaam = m_bestandsNaam;
	m_bestandsNaam = bestandsNaam;
	bool succes = save();
	m_bestandsNaam = origNaam;
}
