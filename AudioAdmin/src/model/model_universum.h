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
    class Arts;
    class Dossier;
    class Instellingen;
    class Mutualiteit;

    class Universum
    {
    public:
        explicit Universum(const QString &bestandsNaam);
        virtual ~Universum();

        void fromDomElement(const QDomElement &root);
        QDomElement toDomElement(QDomDocument &d) const;

        QDate getInvalidDate() const { return QDate(1900, 1, 1); }

        bool openen();
        bool bewaren();

        Arts *toevoegenArts(const QString &voornaam, const QString &naam);
        void verwijderenArts(int id);
        QVector<Arts *> &getArtsen();
        Arts *getArts(int id) const;

        Dossier *toevoegenDossier(const QString &voornaam, const QString &naam);
        void verwijderenDossier(int id);
        QVector<Dossier *> &getDossiers();
        Dossier *getDossier(int klantId) const;

        Mutualiteit *toevoegenMutualiteit(const QString &naam);
        void verwijderenMutualiteit(int id);
        QVector<Mutualiteit *> &getMutualiteiten();
        Mutualiteit *getMutualiteit(int id) const;

        Instellingen &getInstellingen() { return *m_instellingen; }
        const Instellingen &getInstellingen() const { return *m_instellingen; }

    private:
        void openInstellingen(QDomElement &element);

        QString m_bestandsNaam;
        QVector<Arts *> m_artsenLijst;
        QVector<Dossier *> m_dossierLijst;
        QVector<Mutualiteit *> m_mutualiteitenLijst;
        Instellingen *m_instellingen;
    };
}

#endif // _MODEL_UNIVERSUM_H
