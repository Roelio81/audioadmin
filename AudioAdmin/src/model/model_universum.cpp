#include "model_universum.h"

#include "model_arts.h"
#include "model_dossier.h"
#include "model_mutualiteit.h"

#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QFile>
#include <QIODevice>

using namespace Model;

Universum::Universum(const ::QString &bestandsNaam)
: QObject()
, m_bestandsNaam(bestandsNaam)
{
	openen();
}

Universum::~Universum()
{
}

bool Universum::openen()
{
	// Eerst het bestand proberen te openen alvorens het model leeg te maken
	::QFile file(m_bestandsNaam);
	if (!file.open(::QIODevice::ReadOnly)) 
	{
		return false;
	}
	
	m_artsenLijst.clear();
	m_mutualiteitenLijst.clear();
	m_dossierLijst.clear();

	::QDomDocument doc;
	if (!doc.setContent(&file)) 
	{
		return false;
	}
	::QDomElement root = doc.documentElement();
	::Q_ASSERT( root.tagName() == "administratie");
	
	for (QDomElement e = root.firstChildElement(); !e.isNull(); e = e.nextSiblingElement())
	{
		if (e.tagName() == "instellingen")
		{
			openInstellingen(e);
		}
		else if (e.tagName() == "nkoArtsen")
		{
			for (::QDomElement artsElement = e.firstChildElement(); !artsElement.isNull(); artsElement = artsElement.nextSiblingElement())
			{
				Q_ASSERT(artsElement.tagName() == "dokter");
				m_artsenLijst.push_back(new Arts(artsElement));
			}
		}
		else if (e.tagName() == "mutualiteiten")
		{
			for (::QDomElement mutElement = e.firstChildElement(); !mutElement.isNull(); mutElement = mutElement.nextSiblingElement())
			{
				Q_ASSERT(mutElement.tagName() == "mutualiteit");
				m_mutualiteitenLijst.push_back(new Mutualiteit(mutElement));
			}
		}
		else if (e.tagName() == "dossiers")
		{
			for (::QDomElement dossierElement = e.firstChildElement(); !dossierElement.isNull(); dossierElement = dossierElement.nextSiblingElement())
			{
				Q_ASSERT(dossierElement.tagName() == "dossier");
				m_dossierLijst.push_back(new Dossier(dossierElement));
			}
		}
		else
		{
			Q_ASSERT(false);
		}
	}
	return true;
}

void Universum::openen(::QString bestandsNaam)
{
	const ::QString &origNaam = m_bestandsNaam;
	m_bestandsNaam = bestandsNaam;
	bool succes = load();
	Q_ASSERT(succes);
	m_bestandsNaam = origNaam;
}

bool Universum::bewaren()
{
	return true;
}

void Universum::bewaren(QString bestandsNaam)
{
	const ::QString &origNaam = m_bestandsNaam;
	m_bestandsNaam = bestandsNaam;
	bool succes = save();
	Q_ASSERT(succes);
	m_bestandsNaam = origNaam;
}

void Universum::openInstellingen(QDomElement &e)
{
	
}