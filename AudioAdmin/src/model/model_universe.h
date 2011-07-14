#ifndef _MODEL_UNIVERSE_H
#define _MODEL_UNIVERSE_H

#include <QDate>
#include <QMap>
#include <QString>
#include <QVector>

class QDomDocument;
class QDomElement;

namespace Model
{
    class File;
    class InsuranceCompany;
    class Labels;
    class Physician;
    class Settings;

    class Universe
    {
    public:
        explicit Universe(const QString &fileName);
        virtual ~Universe();

        // Load the data from file
        bool open();
        // Save the data to file
        bool save();

        // --- ISerializable ---
        virtual void fromDomElement(const QDomElement &root);
        virtual QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        QDate getInvalidDate() const { return QDate(1900, 1, 1); }
        const QVector<Physician *> &getPhysicians() { return m_physicians; }
        const QVector<File *> &getFiles() { return m_files; }
        const QVector<InsuranceCompany *> &getInsuranceCompanies() { return m_insuranceCompanies; }
        Settings &getSettings() { return *m_settings; }
        Labels &getLabels() { return *m_labels; }
        const Settings &getSettings() const { return *m_settings; }
        Physician *getPhysician(int id) const;
        File *getFile(int id) const;
        InsuranceCompany *getInsuranceCompany(int id) const;

        // --- Methods to add and remove entities ---
        Physician *addPhysician(const QString &firstName, const QString &name);
        File *addFile(const QString &firstName, const QString &name);
        InsuranceCompany *addInsuranceCompany(const QString &name);
        void removePhysician(int id);
        void removeFile(int id);
        void removeInsuranceCompany(int id);

    private:
        // --- Data members ---
        QString m_fileName;
        QVector<Physician *> m_physicians;
        QVector<File *> m_files;
        QVector<InsuranceCompany *> m_insuranceCompanies;
        Settings *m_settings;
        Labels *m_labels;
    };
}

#endif // _MODEL_UNIVERSE_H
