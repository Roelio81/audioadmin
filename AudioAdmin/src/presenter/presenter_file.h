#ifndef _PRESENTER_DOSSIER_H
#define _PRESENTER_DOSSIER_H

#include <QObject>

namespace View
{
    class File;
}

namespace Model
{
    class File;
}

namespace Presenter
{
    class File : public QObject
    {
    Q_OBJECT
    public:
        explicit File(View::File &view, Model::File &model);
        virtual ~File();

        // --- IPresenter ---
        void setup();
        void teardown();

    signals:
        void edited(int id);

    private slots:
        void showLetterPhysician();
        void showLetterCustomer();
        void showLetterInsuranceCompany();
        void showInvoice();
        void showMeasurements();

    private:
        // --- Data members ---
        View::File &m_view;
        Model::File &m_model;
    };
}

#endif // _PRESENTER_DOSSIER_H
