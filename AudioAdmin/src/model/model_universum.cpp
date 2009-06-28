#include "model_universum.h"

#include "model_arts.h"
#include "model_dossier.h"
#include "model_instellingen.h"
#include "model_mutualiteit.h"

#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QFile>
#include <QIODevice>

using namespace Model;

Universum::Universum(const QString &bestandsNaam)
: m_bestandsNaam(bestandsNaam)
, m_instellingen(0)
{
    openen();
}

Universum::~Universum()
{
}

bool Universum::openen()
{
    // Eerst het bestand proberen te openen alvorens het model leeg te maken
    QFile file(m_bestandsNaam);
    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    m_artsenLijst.clear();
    m_mutualiteitenLijst.clear();
    m_dossierLijst.clear();

    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        return false;
    }
    QDomElement root = doc.documentElement();
    Q_ASSERT( root.tagName() == "administratie");
	
    for (QDomElement e = root.firstChildElement(); !e.isNull(); e = e.nextSiblingElement())
    {
        if (e.tagName() == "instellingen")
        {
            m_instellingen = new Instellingen();
            m_instellingen->fromDomElement(e);
        }
        else if (e.tagName() == "nkoArtsen")
        {
            for (QDomElement artsElement = e.firstChildElement(); !artsElement.isNull(); artsElement = artsElement.nextSiblingElement())
            {
                Q_ASSERT(artsElement.tagName() == "dokter");
                Q_ASSERT(artsElement.hasAttribute("id"));
                int artsId = artsElement.attribute("id").toInt();
                Arts *arts = new Arts(artsId);
                arts->fromDomElement(artsElement);
                m_artsenLijst.push_back(arts);
            }
        }
        else if (e.tagName() == "mutualiteiten")
        {
            for (QDomElement mutElement = e.firstChildElement(); !mutElement.isNull(); mutElement = mutElement.nextSiblingElement())
            {
                Q_ASSERT(mutElement.tagName() == "mutualiteit");
                Q_ASSERT(mutElement.hasAttribute("id"));
                int mutId = mutElement.attribute("id").toInt();
                Mutualiteit *mutualiteit = new Mutualiteit(mutId);
                mutualiteit->fromDomElement(mutElement);
                m_mutualiteitenLijst.push_back(mutualiteit);
            }
        }
        else if (e.tagName() == "dossiers")
        {
            for (QDomElement dossierElement = e.firstChildElement(); !dossierElement.isNull(); dossierElement = dossierElement.nextSiblingElement())
            {
                Q_ASSERT(dossierElement.tagName() == "dossier");
                Q_ASSERT(dossierElement.hasAttribute("id"));
                int dossierId = dossierElement.attribute("id").toInt();
                Dossier *dossier = new Dossier(dossierId);
                dossier->fromDomElement(dossierElement);
                m_dossierLijst.push_back(dossier);
            }
        }
    }
    return true;
}

bool Universum::openen(const QString &bestandsNaam)
{
    const ::QString &origNaam = m_bestandsNaam;
    m_bestandsNaam = bestandsNaam;
    bool succes = openen();
    m_bestandsNaam = origNaam;
    return succes;
}

bool Universum::bewaren()
{
    return true;
}

bool Universum::bewaren(const QString &bestandsNaam)
{
    const ::QString &origNaam = m_bestandsNaam;
    m_bestandsNaam = bestandsNaam;
    bool succes = bewaren();
    m_bestandsNaam = origNaam;
    return succes;
}

Instellingen *Universum::getInstellingen()
{
    if (! m_instellingen)
        m_instellingen = new Instellingen();
    return m_instellingen;
}

void Universum::verwijderenArts(int id)
{
    Arts *arts = getArts(id);
    if (arts)
    {
        int posInVector = m_artsenLijst.indexOf(arts, 0);
        Q_ASSERT(posInVector >= 0 && posInVector < m_artsenLijst.size());
        m_artsenLijst.erase(m_artsenLijst.begin() + posInVector);
    }
}

QVector<Arts *> &Universum::getArtsen()
{
    return m_artsenLijst;
}

Arts *Universum::getArts(int id)
{
    for (QVector<Arts *>::iterator itArts = m_artsenLijst.begin(); itArts != m_artsenLijst.end(); ++itArts)
    {
        Arts *arts = *itArts;
        if (arts->getId() == id) return arts;
    }
    return 0;
}

void Universum::verwijderenDossier(int id)
{
    Dossier *dossier = getDossier(id);
    if (dossier)
    {
        int posInVector = m_dossierLijst.indexOf(dossier, 0);
        Q_ASSERT(posInVector >= 0 && posInVector < m_dossierLijst.size());
        m_dossierLijst.erase(m_dossierLijst.begin() + posInVector);
    }
}

QVector<Dossier *> &Universum::getDossiers()
{
    return m_dossierLijst;
}

Dossier *Universum::getDossier(int id)
{
    for (QVector<Dossier *>::iterator itDossier = m_dossierLijst.begin(); itDossier != m_dossierLijst.end(); ++itDossier)
    {
        Dossier *dossier = *itDossier;
        if (dossier->getId() == id) return dossier;
    }
    return 0;
}

void Universum::verwijderenMutualiteit(int id)
{
    Mutualiteit *mutualiteit = getMutualiteit(id);
    if (mutualiteit)
    {
        int posInVector = m_mutualiteitenLijst.indexOf(mutualiteit, 0);
        Q_ASSERT(posInVector >= 0 && posInVector < m_mutualiteitenLijst.size());
        m_mutualiteitenLijst.erase(m_mutualiteitenLijst.begin() + posInVector);
    }
}

QVector<Mutualiteit *> &Universum::getMutualiteiten()
{
    return m_mutualiteitenLijst;
}

Mutualiteit *Universum::getMutualiteit(int id)
{
    for (QVector<Mutualiteit *>::iterator itMutualiteit = m_mutualiteitenLijst.begin(); itMutualiteit != m_mutualiteitenLijst.end(); ++itMutualiteit)
    {
        Mutualiteit *mutualiteit = *itMutualiteit;
        if (mutualiteit->getId() == id) return mutualiteit;
    }
    return 0;
}
