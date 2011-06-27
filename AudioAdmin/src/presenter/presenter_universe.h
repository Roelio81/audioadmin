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
        void openSettings();
        void showPhysician(int id);
        void showFile(int id);
        void showInsuranceCompany(int id);
        void removePhysician(int id);
        void removeFile(int id);
        void removeInsuranceCompany(int id);
        void addPhysician(QString voornaam, QString naam);
        void addFile(QString voornaam, QString naam);
        void toevoegenMutualiteit(QString naam);
        void editedPhysician(int id);
        void editedFile(int id);
        void editedInsuranceCompany(int id);
        void hoorapparaatGewijzigd();
        void teardownPhysician();
        void teardownFile();
        void teardownInsuranceCompany();
        void setupPhysician();
        void setupFile();
        void setupInsuranceCompany();

    private:
        void setupEtiketten();
        void setupSettings();
        void teardownEtiketten();
        void teardownSettings();

        void refreshArtsenLijst();
        void refreshHoorapparatenLijst();
        void refreshKlantenLijst();
        void refreshMutualiteitenLijst();

        View::Universe &m_view;
        Model::Universe &m_model;

        Presenter::Physician *m_physicianPresenter;
        Presenter::Dossier *m_filePresenter;
        Presenter::InsuranceCompany *m_insuranceCompanyPresenter;

        int m_arts;
        int m_file;
        int m_insuranceCompany;
        bool m_changed;
    };
}

#endif // _PRESENTER_UNIVERSUM_H
