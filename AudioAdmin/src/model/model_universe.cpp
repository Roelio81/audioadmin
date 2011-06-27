#include "model_universe.h"

#include "model_physician.h"
#include "model_file.h"
#include "model_settings.h"
#include "model_insurance.h"

#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

using namespace Model;

Universe::Universe(const QString &bestandsNaam)
: m_bestandsNaam(bestandsNaam)
, m_instellingen(new Settings(*this))
{
    openen();
}

Universe::~Universe()
{
}

void Universe::fromDomElement(const QDomElement &root)
{
    // Eerst instellingen laden: dit is nodig voor de default BTW percentages...
    Q_ASSERT(m_instellingen);
    QDomElement instellingen = root.firstChildElement("instellingen");
    if (!instellingen.isNull())
        m_instellingen->fromDomElement(instellingen);

    // Nu artsen, mutualiteiten en dossiers openen (kan in gelijk welke volgorde)
    for (QDomElement e = root.firstChildElement(); !e.isNull(); e = e.nextSiblingElement())
    {
        if (e.tagName() == "nkoArtsen")
        {
            for (QDomElement artsElement = e.firstChildElement(); !artsElement.isNull(); artsElement = artsElement.nextSiblingElement())
            {
                Q_ASSERT(artsElement.tagName() == "dokter");
                Q_ASSERT(artsElement.hasAttribute("id"));
                int artsId = artsElement.attribute("id").toInt();
                Physician *arts = new Physician(artsId);
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
                InsuranceCompany *mutualiteit = new InsuranceCompany(mutId);
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
                File *dossier = new File(dossierId, *this);
                dossier->fromDomElement(dossierElement);
                m_dossierLijst.push_back(dossier);
            }
        }
    }
}

QDomElement Universe::toDomElement(QDomDocument &domDoc) const
{
    QDomElement result = domDoc.createElement("administratie");

    Q_ASSERT(m_instellingen);
    QDomElement instellingen = m_instellingen->toDomElement(domDoc);
    result.appendChild(instellingen);

    QDomElement nkoArtsen = domDoc.createElement("nkoArtsen");
    for (QVector<Physician *>::const_iterator itArts = m_artsenLijst.begin(); itArts != m_artsenLijst.end(); ++itArts)
    {
        Physician *arts = *itArts;
        Q_ASSERT(arts);
        nkoArtsen.appendChild(arts->toDomElement(domDoc));
    }
    result.appendChild(nkoArtsen);

    QDomElement mutualiteiten = domDoc.createElement("mutualiteiten");
    for (QVector<InsuranceCompany *>::const_iterator itMutualiteit = m_mutualiteitenLijst.begin(); itMutualiteit != m_mutualiteitenLijst.end(); ++itMutualiteit)
    {
        InsuranceCompany *mutualiteit = *itMutualiteit;
        Q_ASSERT(mutualiteit);
        mutualiteiten.appendChild(mutualiteit->toDomElement(domDoc));
    }
    result.appendChild(mutualiteiten);

    QDomElement dossiers = domDoc.createElement("dossiers");
    for (QVector<File *>::const_iterator itDossier = m_dossierLijst.begin(); itDossier != m_dossierLijst.end(); ++itDossier)
    {
        File *dossier = *itDossier;
        Q_ASSERT(dossier);
        dossiers.appendChild(dossier->toDomElement(domDoc));
    }
    result.appendChild(dossiers);

    return result;
}

bool Universe::openen()
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

    fromDomElement(root);
    return true;
}

bool Universe::bewaren()
{
    QFile file(m_bestandsNaam);
    if (!file.open(QIODevice::ReadWrite|QIODevice::Truncate))
    {
        return false;
    }

    QDomDocument doc;
    QDomElement element = toDomElement(doc);
    QTextStream ts(&file);
    doc.appendChild(element);
    doc.save(ts, 0);
    file.close();
    return true;
}

Physician *Universe::toevoegenArts(const QString &voornaam, const QString &naam)
{
    int maxId = 0;
    for (QVector<Physician *>::iterator itArts = m_artsenLijst.begin(); itArts != m_artsenLijst.end(); ++itArts)
    {
        Physician *arts = *itArts;
        maxId = std::max(maxId, arts->getId());
    }
    Physician *arts = new Physician(maxId+1);
    arts->setFirstName(voornaam);
    arts->setName(naam);
    m_artsenLijst.push_back(arts);
    return arts;
}

void Universe::verwijderenArts(int id)
{
    Physician *arts = getArts(id);
    if (!arts)
        return;
    int posInVector = m_artsenLijst.indexOf(arts, 0);
    Q_ASSERT(posInVector >= 0 && posInVector < m_artsenLijst.size());
    m_artsenLijst.erase(m_artsenLijst.begin() + posInVector);
}

QVector<Physician *> &Universe::getArtsen()
{
    return m_artsenLijst;
}

Physician *Universe::getArts(int id) const
{
    for (QVector<Physician *>::const_iterator itArts = m_artsenLijst.begin(); itArts != m_artsenLijst.end(); ++itArts)
    {
        Physician *arts = *itArts;
        if (arts->getId() == id)
            return arts;
    }
    return 0;
}


File *Universe::toevoegenDossier(const QString &voornaam, const QString &naam)
{
    int maxId = 0;
    for (QVector<File *>::iterator itDossier = m_dossierLijst.begin(); itDossier != m_dossierLijst.end(); ++itDossier)
    {
        File *dossier = *itDossier;
        maxId = std::max(maxId, dossier->getId());
    }
    File *dossier = new File(maxId+1, *this);
    dossier->getKlant().setVoornaam(voornaam);
    dossier->getKlant().setName(naam);
    m_dossierLijst.push_back(dossier);
    return dossier;
}

void Universe::verwijderenDossier(int id)
{
    File *dossier = getDossier(id);
    if (dossier)
    {
        int posInVector = m_dossierLijst.indexOf(dossier, 0);
        Q_ASSERT(posInVector >= 0 && posInVector < m_dossierLijst.size());
        m_dossierLijst.erase(m_dossierLijst.begin() + posInVector);
    }
}

QVector<File *> &Universe::getDossiers()
{
    return m_dossierLijst;
}

File *Universe::getDossier(int id) const
{
    for (QVector<File *>::const_iterator itDossier = m_dossierLijst.begin(); itDossier != m_dossierLijst.end(); ++itDossier)
    {
        File *dossier = *itDossier;
        if (dossier->getId() == id)
            return dossier;
    }
    return 0;
}

InsuranceCompany *Universe::toevoegenMutualiteit(const QString &naam)
{
    int maxId = 0;
    for (QVector<InsuranceCompany *>::iterator itMutualiteit = m_mutualiteitenLijst.begin(); itMutualiteit != m_mutualiteitenLijst.end(); ++itMutualiteit)
    {
        InsuranceCompany *mutualiteit = *itMutualiteit;
        maxId = std::max(maxId, mutualiteit->getId());
    }
    InsuranceCompany *mutualiteit = new InsuranceCompany(maxId+1);
    mutualiteit->setName(naam);
    m_mutualiteitenLijst.push_back(mutualiteit);
    return mutualiteit;
}

void Universe::verwijderenMutualiteit(int id)
{
    InsuranceCompany *mutualiteit = getMutualiteit(id);
    if (mutualiteit)
    {
        int posInVector = m_mutualiteitenLijst.indexOf(mutualiteit, 0);
        Q_ASSERT(posInVector >= 0 && posInVector < m_mutualiteitenLijst.size());
        m_mutualiteitenLijst.erase(m_mutualiteitenLijst.begin() + posInVector);
    }
}

QVector<InsuranceCompany *> &Universe::getMutualiteiten()
{
    return m_mutualiteitenLijst;
}

InsuranceCompany *Universe::getMutualiteit(int id) const
{
    for (QVector<InsuranceCompany *>::const_iterator itMutualiteit = m_mutualiteitenLijst.begin(); itMutualiteit != m_mutualiteitenLijst.end(); ++itMutualiteit)
    {
        InsuranceCompany *mutualiteit = *itMutualiteit;
        if (mutualiteit->getId() == id)
            return mutualiteit;
    }
    return 0;
}
