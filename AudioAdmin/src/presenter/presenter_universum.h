#ifndef _PRESENTER_UNIVERSUM_H
#define _PRESENTER_UNIVERSUM_H

#include <QObject>

namespace View
{
    class Universum;
}

namespace Model
{
    class Universum;
}

namespace Presenter
{
    class Arts;
    class Dossier;
    class Mutualiteit;
	
    class Universum : public ::QObject
    {
    Q_OBJECT
    public:
        Universum(View::Universum &view, Model::Universum &model);
        virtual ~Universum();

    private slots:
        void openen(QString bestandsNaam);
        void bewaren(QString bestandsNaam);
        void etiketten();
        void instellingen();
        void toonArts(int id);
        void toonDossier(int id);
        void toonMutualiteit(int id);
        void verwijderArts(int id);
        void verwijderDossier(int id);
        void verwijderMutualiteit(int id);
        void toevoegenArts(QString voornaam, QString naam);
        void toevoegenDossier(QString voornaam, QString naam);
        void toevoegenMutualiteit(QString naam);
        void artsGewijzigd(int id);
        void dossierGewijzigd(int id);
        void mutualiteitGewijzigd(int id);
        void teardownArts();
        void teardownDossier();
        void teardownMutualiteit();
        void setupArts();
        void setupDossier();
        void setupMutualiteit();

    private:
        void setupEtiketten();
        void setupInstellingen();
        void teardownEtiketten();
        void teardownInstellingen();

        void refreshArtsenLijst();
        void refreshHoorapparatenLijst();
        void refreshKlantenLijst();
        void refreshMutualiteitenLijst();

        View::Universum &m_view;
        Model::Universum &m_model;

        Presenter::Arts *m_artsPresenter;
        Presenter::Dossier *m_dossierPresenter;
        Presenter::Mutualiteit *m_mutualiteitPresenter;

        int m_arts;
        int m_dossier;
        int m_mutualiteit;
    };
}

#endif // _PRESENTER_UNIVERSUM_H
