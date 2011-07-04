#ifndef _PRESENTER_UNIVERSE_H
#define _PRESENTER_UNIVERSE_H

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
    class File;
    class InsuranceCompany;
	
    class Universe : public ::QObject
    {
    Q_OBJECT
    public:
        explicit Universe(View::Universe &view, Model::Universe &model);
        virtual ~Universe();

    private slots:
        void exit();
        void save();
        void openLabels();
        void openSettings();
        void showPhysician(int id);
        void showFile(int id);
        void showInsuranceCompany(int id);
        void removePhysician(int id);
        void removeFile(int id);
        void removeInsuranceCompany(int id);
        void addPhysician(QString firstName, QString name);
        void addFile(QString firstName, QString name);
        void addInsuranceCompany(QString name);
        void editedPhysician(int id);
        void editedFile(int id);
        void editedInsuranceCompany(int id);
        void editedHearingAids();
        void teardownPhysician();
        void teardownFile();
        void teardownInsuranceCompany();
        void setupPhysician();
        void setupFile();
        void setupInsuranceCompany();

    private:
        void refreshPhysicianList();
        void refreshHearingAidsList();
        void refreshCustomerList();
        void refreshInsuranceCompanyList();

        View::Universe &m_view;
        Model::Universe &m_model;

        Presenter::Physician *m_physicianPresenter;
        Presenter::File *m_filePresenter;
        Presenter::InsuranceCompany *m_insuranceCompanyPresenter;

        int m_physician;
        int m_file;
        int m_insuranceCompany;
        bool m_changed;
    };
}

#endif // _PRESENTER_UNIVERSE_H
