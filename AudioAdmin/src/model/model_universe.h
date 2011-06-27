#ifndef _MODEL_UNIVERSUM_H
#define _MODEL_UNIVERSUM_H

#include <QDate>
#include <QMap>
#include <QString>
#include <QVector>

class QDomDocument;
class QDomElement;

namespace Model
{
    class Physician;
    class File;
    class Settings;
    class InsuranceCompany;

    class Universe
    {
    public:
        explicit Universe(const QString &bestandsNaam);
        virtual ~Universe();

        void fromDomElement(const QDomElement &root);
        QDomElement toDomElement(QDomDocument &d) const;

        QDate getInvalidDate() const { return QDate(1900, 1, 1); }

        bool openen();
        bool bewaren();

        Physician *toevoegenArts(const QString &voornaam, const QString &naam);
        void verwijderenArts(int id);
        QVector<Physician *> &getArtsen();
        Physician *getArts(int id) const;

        File *toevoegenDossier(const QString &voornaam, const QString &naam);
        void verwijderenDossier(int id);
        QVector<File *> &getDossiers();
        File *getDossier(int klantId) const;

        InsuranceCompany *toevoegenMutualiteit(const QString &naam);
        void verwijderenMutualiteit(int id);
        QVector<InsuranceCompany *> &getMutualiteiten();
        InsuranceCompany *getMutualiteit(int id) const;

        Settings &getSettings() { return *m_instellingen; }
        const Settings &getSettings() const { return *m_instellingen; }

    private:
        void openInstellingen(QDomElement &element);

        QString m_bestandsNaam;
        QVector<Physician *> m_artsenLijst;
        QVector<File *> m_dossierLijst;
        QVector<InsuranceCompany *> m_mutualiteitenLijst;
        Settings *m_instellingen;
    };
}

#endif // _MODEL_UNIVERSUM_H
