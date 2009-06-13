#ifndef _MODEL_UNIVERSUM_H
#define _MODEL_UNIVERSUM_H

#include <QMap>
#include <QString>
#include <QVector>

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
        Universum(const QString &bestandsNaam);
        virtual ~Universum();

        bool openen();
        bool openen(const QString &bestandsNaam);
        bool bewaren();
        bool bewaren(const QString &bestandsNaam);

        void toevoegenArts(Arts *arts);
        void verwijderenArts(int id);
        QVector<Arts *> &getArtsen();
        Arts *getArts(int id);

        void toevoegenDossier(Dossier *dossier);
        void verwijderenDossier(int id);
        QVector<Dossier *> &getDossiers();
        Dossier *getDossier(int klantId);

        void toevoegenMutualiteit(Mutualiteit *mutualiteit);
        void verwijderenMutualiteit(int id);
        QVector<Mutualiteit *> &getMutualiteiten();
        Mutualiteit *getMutualiteit(int id);

        Instellingen *getInstellingen();

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
