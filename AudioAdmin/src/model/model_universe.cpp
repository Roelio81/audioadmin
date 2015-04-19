#include "model_universe.h"

#include "model_file.h"
#include "model_insurancecompany.h"
#include "model_labels.h"
#include "model_physician.h"
#include "model_settings.h"

#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

using namespace Model;

Universe::Universe(const QString &fileName)
: m_fileName(fileName)
, m_settings(new Settings())
, m_labels(new Labels(*this))
{
    open();
}

Universe::~Universe()
{
    delete m_settings;
    delete m_labels;
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
            for (QDomElement ePhysician = e.firstChildElement(); !ePhysician.isNull(); ePhysician = ePhysician.nextSiblingElement())
            {
                Q_ASSERT(ePhysician.tagName() == "physician");
                Q_ASSERT(ePhysician.hasAttribute("id"));
                int id = ePhysician.attribute("id").toInt();
                Physician *physician = new Physician(id);
                physician->fromDomElement(ePhysician);
                m_physicians.push_back(physician);
            }
        }
        else if (e.tagName() == "insuranceCompanies")
        {
            for (QDomElement eInsuranceCompany = e.firstChildElement(); !eInsuranceCompany.isNull(); eInsuranceCompany = eInsuranceCompany.nextSiblingElement())
            {
                Q_ASSERT(eInsuranceCompany.tagName() == "insuranceCompany");
                Q_ASSERT(eInsuranceCompany.hasAttribute("id"));
                int id = eInsuranceCompany.attribute("id").toInt();
                InsuranceCompany *insuranceCompany = new InsuranceCompany(id);
                insuranceCompany->fromDomElement(eInsuranceCompany);
                m_insuranceCompanies.push_back(insuranceCompany);
            }
        }
        else if (e.tagName() == "files")
        {
            for (QDomElement eFile = e.firstChildElement(); !eFile.isNull(); eFile = eFile.nextSiblingElement())
            {
                Q_ASSERT(eFile.tagName() == "file");
                Q_ASSERT(eFile.hasAttribute("id"));
                int id = eFile.attribute("id").toInt();
                File *file = new File(id, *this);
                file->fromDomElement(eFile);
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
    if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
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
    for (QVector<Physician *>::iterator it = m_physicians.begin(); it != m_physicians.end(); ++it)
    {
        Physician *physician = *it;
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
    Physician *physician = getPhysician(id);
    if (!physician)
        return;
    int posInVector = m_physicians.indexOf(physician, 0);
    Q_ASSERT(posInVector >= 0 && posInVector < m_physicians.size());
    m_physicians.erase(m_physicians.begin() + posInVector);
    for (QVector<File *>::const_iterator it = m_files.begin(); it != m_files.end(); ++it)
    {
        File *file = *it;
        Q_ASSERT(file);
        if (file->getPhysician() == id)
            file->setPhysician(-1);
    }
}

Physician *Universe::getPhysician(int id) const
{
    for (QVector<Physician *>::const_iterator it = m_physicians.begin(); it != m_physicians.end(); ++it)
    {
        Physician *physician = *it;
        if (physician->getId() == id)
            return physician;
    }
    return 0;
}


File *Universe::addFile(const QString &firstName, const QString &name)
{
    int maxId = 0;
    for (QVector<File *>::iterator it = m_files.begin(); it != m_files.end(); ++it)
    {
        File *file = *it;
        maxId = std::max(maxId, file->getId());
    }
    File *file = new File(maxId+1, *this);
    file->getCustomer().setFirstName(firstName);
    file->getCustomer().setName(name);
    m_files.push_back(file);
    return file;
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
    for (QVector<File *>::const_iterator it = m_files.begin(); it != m_files.end(); ++it)
    {
        File *file = *it;
        if (file->getId() == id)
            return file;
    }
    return 0;
}

InsuranceCompany *Universe::addInsuranceCompany(const QString &name)
{
    int maxId = 0;
    for (QVector<InsuranceCompany *>::iterator it = m_insuranceCompanies.begin(); it != m_insuranceCompanies.end(); ++it)
    {
        InsuranceCompany *insuranceCompany = *it;
        maxId = std::max(maxId, insuranceCompany->getId());
    }
    InsuranceCompany *insuranceCompany = new InsuranceCompany(maxId+1);
    insuranceCompany->setName(name);
    m_insuranceCompanies.push_back(insuranceCompany);
    return insuranceCompany;
}

void Universe::removeInsuranceCompany(int id)
{
    InsuranceCompany *insuranceCompany = getInsuranceCompany(id);
    if (!insuranceCompany)
        return;
    int posInVector = m_insuranceCompanies.indexOf(insuranceCompany, 0);
    Q_ASSERT(posInVector >= 0 && posInVector < m_insuranceCompanies.size());
    m_insuranceCompanies.erase(m_insuranceCompanies.begin() + posInVector);
    for (QVector<File *>::const_iterator it = m_files.begin(); it != m_files.end(); ++it)
    {
        File *file = *it;
        Q_ASSERT(file);
        if (file->getInsuranceCompany() == id)
            file->setInsuranceCompany(-1);
    }
}

InsuranceCompany *Universe::getInsuranceCompany(int id) const
{
    for (QVector<InsuranceCompany *>::const_iterator it = m_insuranceCompanies.begin(); it != m_insuranceCompanies.end(); ++it)
    {
        InsuranceCompany *insuranceCompany = *it;
        if (insuranceCompany->getId() == id)
            return insuranceCompany;
    }
    return 0;
}
