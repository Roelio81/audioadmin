#include "worldmodel.h"

#include "artsmodel.h"
#include "dossiermodel.h"
#include "mutualiteitmodel.h"

#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QFile>
#include <QIODevice>

WorldModel::WorldModel(const QString &bestandsNaam)
: QObject()
, m_bestandsNaam(bestandsNaam)
{
	load();
}

WorldModel::~WorldModel()
{
}

bool WorldModel::load()
{
	// First try to open the file before clearing all data in the model
	QFile file(m_bestandsNaam);
	if (!file.open( QIODevice::ReadOnly )) return false;
	
	m_artsenLijst.clear();
	m_mutualiteitenLijst.clear();
	m_dossierLijst.clear();

	QDomDocument doc;
	if (!doc.setContent(&file)) return false;
	QDomElement root = doc.documentElement();
	Q_ASSERT( root.tagName() == "administratie");
	
	for (QDomElement e = root.firstChildElement(); !e.isNull(); e = e.nextSiblingElement())
	{
		if (e.tagName() == "instellingen")
		{
			loadInstellingen(e);
		}
		else if (e.tagName() == "nkoArtsen")
		{
			for (QDomElement artsElement = e.firstChildElement(); !artsElement.isNull(); artsElement = artsElement.nextSiblingElement())
			{
				Q_ASSERT(artsElement.tagName() == "dokter");
				m_artsenLijst.push_back(new ArtsModel(artsElement));
			}
		}
		else if (e.tagName() == "mutualiteiten")
		{
			for (QDomElement mutElement = e.firstChildElement(); !mutElement.isNull(); mutElement = mutElement.nextSiblingElement())
			{
				Q_ASSERT(mutElement.tagName() == "mutualiteit");
				m_mutualiteitenLijst.push_back(new MutualiteitModel(mutElement));
			}
		}
		else if (e.tagName() == "dossiers")
		{
			for (QDomElement dossierElement = e.firstChildElement(); !dossierElement.isNull(); dossierElement = dossierElement.nextSiblingElement())
			{
				Q_ASSERT(dossierElement.tagName() == "dossier");
				m_dossierLijst.push_back(new DossierModel(dossierElement));
			}
		}
		else
		{
			Q_ASSERT(false);
		}
	}
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

void WorldModel::loadInstellingen(QDomElement &e)
{
	
}