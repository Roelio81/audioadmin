#ifndef _PRESENTER_UNIVERSUM_H
#define _PRESENTER_UNIVERSUM_H

#include <QObject>

namespace View
{
    class Universe;
}

namespace Model
{
    class Universe;
}

namespace Presenter
{
    class Physician;
    class Dossier;
    class InsuranceCompany;
	
    class Universum : public ::QObject
    {
    Q_OBJECT
    public:
        explicit Universum(View::Universe &view, Model::Universe &model);
        virtual ~Universum();

    private slots:
        void afsluiten();
        void bewaren();
        void etiketten();
        void afdrukkenEtiketten();
        void annuleerEtiketten();
        void instellingen();
        void okInstellingen();
        void annuleerInstellingen();
        void toonArts(int id);
        void toonDossier(int id);
        void toonMutualiteit(int id);
        void verwijderArts(int id);
        void verwijderDossier(int id);
        void verwijderMutualiteit(int id);
        void toevoegenArts(QString voornaam, QString naam);
        void toevoegenDossier(QString voornaam, QString naam);
        void toevoegenMutualiteit(QString naam);
        void editedPhysician(int id);
        void editedFile(int id);
        void editedInsuranceCompany(int id);
        void hoorapparaatGewijzigd();
        void teardownArts();
        void teardownDossier();
        void teardownMutualiteit();
        void setupPhysician();
        void setupFile();
        void setupInsuranceCompany();

    private:
        void setupEtiketten();
        void setupInstellingen();
        void teardownEtiketten();
        void teardownInstellingen();

        void refreshArtsenLijst();
        void refreshHoorapparatenLijst();
        void refreshKlantenLijst();
        void refreshMutualiteitenLijst();

        View::Universe &m_view;
        Model::Universe &m_model;

        Presenter::Physician *m_artsPresenter;
        Presenter::Dossier *m_dossierPresenter;
        Presenter::InsuranceCompany *m_mutualiteitPresenter;

        int m_arts;
        int m_dossier;
        int m_mutualiteit;
        bool m_gewijzigd;
    };
}

#endif // _PRESENTER_UNIVERSUM_H
