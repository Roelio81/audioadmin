#include "model_universe.h"

#include "model_physician.h"
#include "model_file.h"
#include "model_settings.h"
#include "model_insurancecompany.h"

#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

using namespace Model;

Universe::Universe(const QString &fileName)
: m_fileName(fileName)
, m_settings(new Settings(*this))
{
    open();
}

Universe::~Universe()
{
}

void Universe::fromDomElement(const QDomElement &root)
{
    // First load settings: we need this for the default VAT percentage...
    Q_ASSERT(m_settings);
    QDomElement instellingen = root.firstChildElement("instellingen");
    if (!instellingen.isNull())
        m_settings->fromDomElement(instellingen);

    // Now load the entities, i.e., physicians, insurance companies and file (the order doesn't really matter)
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
                m_physicians.push_back(arts);
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
                m_insuranceCompanies.push_back(mutualiteit);
            }
        }
        else if (e.tagName() == "dossiers")
        {
            for (QDomElement fileElement = e.firstChildElement(); !fileElement.isNull(); fileElement = fileElement.nextSiblingElement())
            {
                Q_ASSERT(fileElement.tagName() == "dossier");
                Q_ASSERT(fileElement.hasAttribute("id"));
                int dossierId = fileElement.attribute("id").toInt();
                File *file = new File(dossierId, *this);
                file->fromDomElement(fileElement);
                m_files.push_back(file);
            }
        }
    }
}

QDomElement Universe::toDomElement(QDomDocument &domDoc) const
{
    QDomElement result = domDoc.createElement("administratie");

    Q_ASSERT(m_settings);
    QDomElement instellingen = m_settings->toDomElement(domDoc);
    result.appendChild(instellingen);

    QDomElement nkoArtsen = domDoc.createElement("nkoArtsen");
    for (QVector<Physician *>::const_iterator itArts = m_physicians.begin(); itArts != m_physicians.end(); ++itArts)
    {
        Physician *arts = *itArts;
        Q_ASSERT(arts);
        nkoArtsen.appendChild(arts->toDomElement(domDoc));
    }
    result.appendChild(nkoArtsen);

    QDomElement mutualiteiten = domDoc.createElement("mutualiteiten");
    for (QVector<InsuranceCompany *>::const_iterator itMutualiteit = m_insuranceCompanies.begin(); itMutualiteit != m_insuranceCompanies.end(); ++itMutualiteit)
    {
        InsuranceCompany *mutualiteit = *itMutualiteit;
        Q_ASSERT(mutualiteit);
        mutualiteiten.appendChild(mutualiteit->toDomElement(domDoc));
    }
    result.appendChild(mutualiteiten);

    QDomElement dossiers = domDoc.createElement("dossiers");
    for (QVector<File *>::const_iterator itDossier = m_files.begin(); itDossier != m_files.end(); ++itDossier)
    {
        File *dossier = *itDossier;
        Q_ASSERT(dossier);
        dossiers.appendChild(dossier->toDomElement(domDoc));
    }
    result.appendChild(dossiers);

    return result;
}

bool Universe::open()
{
    // First try to open the file before clearing the model
    QFile file(m_fileName);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    m_physicians.clear();
    m_insuranceCompanies.clear();
    m_files.clear();

    QDomDocument doc;
    if (!doc.setContent(&file))
        return false;
    QDomElement root = doc.documentElement();
    Q_ASSERT(root.tagName() == "administratie");

    fromDomElement(root);
    return true;
}

bool Universe::save()
{
    QFile file(m_fileName);
    if (!file.open(QIODevice::ReadWrite|QIODevice::Truncate))
        return false;

    QDomDocument doc;
    QDomElement element = toDomElement(doc);
    QTextStream ts(&file);
    doc.appendChild(element);
    doc.save(ts, 0);
    file.close();
    return true;
}

Physician *Universe::addPhysician(const QString &firstName, const QString &name)
{
    int maxId = 0;
    for (QVector<Physician *>::iterator itArts = m_physicians.begin(); itArts != m_physicians.end(); ++itArts)
    {
        Physician *physician = *itArts;
        maxId = std::max(maxId, physician->getId());
    }
    Physician *physician = new Physician(maxId+1);
    physician->setFirstName(firstName);
    physician->setName(name);
    m_physicians.push_back(physician);
    return physician;
}

void Universe::removePhysician(int id)
{
    Physician *arts = getPhysician(id);
    if (!arts)
        return;
    int posInVector = m_physicians.indexOf(arts, 0);
    Q_ASSERT(posInVector >= 0 && posInVector < m_physicians.size());
    m_physicians.erase(m_physicians.begin() + posInVector);
}

Physician *Universe::getPhysician(int id) const
{
    for (QVector<Physician *>::const_iterator itArts = m_physicians.begin(); itArts != m_physicians.end(); ++itArts)
    {
        Physician *arts = *itArts;
        if (arts->getId() == id)
            return arts;
    }
    return 0;
}


File *Universe::addFile(const QString &voornaam, const QString &naam)
{
    int maxId = 0;
    for (QVector<File *>::iterator itDossier = m_files.begin(); itDossier != m_files.end(); ++itDossier)
    {
        File *dossier = *itDossier;
        maxId = std::max(maxId, dossier->getId());
    }
    File *dossier = new File(maxId+1, *this);
    dossier->getCustomer().setVoornaam(voornaam);
    dossier->getCustomer().setName(naam);
    m_files.push_back(dossier);
    return dossier;
}

void Universe::removeFile(int id)
{
    File *dossier = getFile(id);
    if (dossier)
    {
        int posInVector = m_files.indexOf(dossier, 0);
        Q_ASSERT(posInVector >= 0 && posInVector < m_files.size());
        m_files.erase(m_files.begin() + posInVector);
    }
}

File *Universe::getFile(int id) const
{
    for (QVector<File *>::const_iterator itDossier = m_files.begin(); itDossier != m_files.end(); ++itDossier)
    {
        File *file = *itDossier;
        if (file->getId() == id)
            return file;
    }
    return 0;
}

InsuranceCompany *Universe::addInsuranceCompany(const QString &naam)
{
    int maxId = 0;
    for (QVector<InsuranceCompany *>::iterator itMutualiteit = m_insuranceCompanies.begin(); itMutualiteit != m_insuranceCompanies.end(); ++itMutualiteit)
    {
        InsuranceCompany *mutualiteit = *itMutualiteit;
        maxId = std::max(maxId, mutualiteit->getId());
    }
    InsuranceCompany *mutualiteit = new InsuranceCompany(maxId+1);
    mutualiteit->setName(naam);
    m_insuranceCompanies.push_back(mutualiteit);
    return mutualiteit;
}

void Universe::removeInsuranceCompany(int id)
{
    InsuranceCompany *mutualiteit = getInsuranceCompany(id);
    if (mutualiteit)
    {
        int posInVector = m_insuranceCompanies.indexOf(mutualiteit, 0);
        Q_ASSERT(posInVector >= 0 && posInVector < m_insuranceCompanies.size());
        m_insuranceCompanies.erase(m_insuranceCompanies.begin() + posInVector);
    }
}

InsuranceCompany *Universe::getInsuranceCompany(int id) const
{
    for (QVector<InsuranceCompany *>::const_iterator itMutualiteit = m_insuranceCompanies.begin(); itMutualiteit != m_insuranceCompanies.end(); ++itMutualiteit)
    {
        InsuranceCompany *mutualiteit = *itMutualiteit;
        if (mutualiteit->getId() == id)
            return mutualiteit;
    }
    return 0;
}
