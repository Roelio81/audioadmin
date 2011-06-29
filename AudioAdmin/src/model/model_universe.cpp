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
    QDomElement settings = root.firstChildElement("settings");
    if (!settings.isNull())
        m_settings->fromDomElement(settings);

    // Now load the entities, i.e., physicians, insurance companies and file (the order doesn't really matter)
    for (QDomElement e = root.firstChildElement(); !e.isNull(); e = e.nextSiblingElement())
    {
        if (e.tagName() == "physicians")
        {
            for (QDomElement artsElement = e.firstChildElement(); !artsElement.isNull(); artsElement = artsElement.nextSiblingElement())
            {
                Q_ASSERT(artsElement.tagName() == "physician");
                Q_ASSERT(artsElement.hasAttribute("id"));
                int id = artsElement.attribute("id").toInt();
                Physician *physician = new Physician(id);
                physician->fromDomElement(artsElement);
                m_physicians.push_back(physician);
            }
        }
        else if (e.tagName() == "insuranceCompanies")
        {
            for (QDomElement mutElement = e.firstChildElement(); !mutElement.isNull(); mutElement = mutElement.nextSiblingElement())
            {
                Q_ASSERT(mutElement.tagName() == "insuranceCompany");
                Q_ASSERT(mutElement.hasAttribute("id"));
                int id = mutElement.attribute("id").toInt();
                InsuranceCompany *mutualiteit = new InsuranceCompany(id);
                mutualiteit->fromDomElement(mutElement);
                m_insuranceCompanies.push_back(mutualiteit);
            }
        }
        else if (e.tagName() == "files")
        {
            for (QDomElement fileElement = e.firstChildElement(); !fileElement.isNull(); fileElement = fileElement.nextSiblingElement())
            {
                Q_ASSERT(fileElement.tagName() == "file");
                Q_ASSERT(fileElement.hasAttribute("id"));
                int id = fileElement.attribute("id").toInt();
                File *file = new File(id, *this);
                file->fromDomElement(fileElement);
                m_files.push_back(file);
            }
        }
    }
}

QDomElement Universe::toDomElement(QDomDocument &domDoc) const
{
    QDomElement result = domDoc.createElement("admin");

    Q_ASSERT(m_settings);
    QDomElement instellingen = m_settings->toDomElement(domDoc);
    result.appendChild(instellingen);

    QDomElement physicians = domDoc.createElement("physicians");
    for (QVector<Physician *>::const_iterator it = m_physicians.begin(); it != m_physicians.end(); ++it)
    {
        Physician *physician = *it;
        Q_ASSERT(physician);
        physicians.appendChild(physician->toDomElement(domDoc));
    }
    result.appendChild(physicians);

    QDomElement insuranceCompanies = domDoc.createElement("insuranceCompanies");
    for (QVector<InsuranceCompany *>::const_iterator it = m_insuranceCompanies.begin(); it != m_insuranceCompanies.end(); ++it)
    {
        InsuranceCompany *insuranceCompany = *it;
        Q_ASSERT(insuranceCompany);
        insuranceCompanies.appendChild(insuranceCompany->toDomElement(domDoc));
    }
    result.appendChild(insuranceCompanies);

    QDomElement files = domDoc.createElement("files");
    for (QVector<File *>::const_iterator it = m_files.begin(); it != m_files.end(); ++it)
    {
        File *file = *it;
        Q_ASSERT(file);
        files.appendChild(file->toDomElement(domDoc));
    }
    result.appendChild(files);

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
    if (root.tagName() != "admin")
        return false;

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
    File *file = getFile(id);
    if (file)
    {
        int posInVector = m_files.indexOf(file, 0);
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
    InsuranceCompany *insuranceCompany = new InsuranceCompany(maxId+1);
    insuranceCompany->setName(naam);
    m_insuranceCompanies.push_back(insuranceCompany);
    return insuranceCompany;
}

void Universe::removeInsuranceCompany(int id)
{
    InsuranceCompany *insuranceCompany = getInsuranceCompany(id);
    if (insuranceCompany)
    {
        int posInVector = m_insuranceCompanies.indexOf(insuranceCompany, 0);
        Q_ASSERT(posInVector >= 0 && posInVector < m_insuranceCompanies.size());
        m_insuranceCompanies.erase(m_insuranceCompanies.begin() + posInVector);
    }
}

InsuranceCompany *Universe::getInsuranceCompany(int id) const
{
    for (QVector<InsuranceCompany *>::const_iterator itMutualiteit = m_insuranceCompanies.begin(); itMutualiteit != m_insuranceCompanies.end(); ++itMutualiteit)
    {
        InsuranceCompany *insuranceCompany = *itMutualiteit;
        if (insuranceCompany->getId() == id)
            return insuranceCompany;
    }
    return 0;
}
