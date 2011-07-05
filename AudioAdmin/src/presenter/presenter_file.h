#ifndef _PRESENTER_FILE_H
#define _PRESENTER_FILE_H

#include "presenter_customer.h"

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
        virtual void setup();
        virtual void teardown();

    signals:
        void edited(int id);

    private slots:
        void customerEdited();
        void showLetterPhysician();
        void showLetterCustomer();
        void showLetterInsuranceCompany();
        void showInvoice();
        void showMeasurements();

    private:
        // --- Data members ---
        View::File &m_view;
        Model::File &m_model;
        Customer m_customer;
    };
}

#endif // _PRESENTER_FILE_H
