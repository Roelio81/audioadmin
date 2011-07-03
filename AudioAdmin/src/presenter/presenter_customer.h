#ifndef _PRESENTER_CUSTOMER_H
#define _PRESENTER_CUSTOMER_H

#include <QObject>

namespace View
{
    class Customer;
}

namespace Model
{
    class Customer;
}

namespace Presenter
{
    class Customer : public QObject
    {
    Q_OBJECT
    public:
        explicit Customer(View::Customer &view, Model::Customer &model);
        virtual ~Customer();

        // --- IPresenter ---
        virtual void setup();
        virtual void teardown();

    signals:
        void edited();

    private:
        // --- Data members ---
        View::Customer &m_view;
        Model::Customer &m_model;
    };

}

#endif // _PRESENTER_CUSTOMER_H
