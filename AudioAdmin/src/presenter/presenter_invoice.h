#ifndef PRESENTER_INVOICE_H
#define PRESENTER_INVOICE_H

#include <QObject>

namespace View
{
    class Invoice;
}

namespace Model
{
    class Invoice;
}

namespace Presenter
{
    class Invoice : public QObject
    {
    Q_OBJECT
    public:
        explicit Invoice(View::Invoice &view, Model::Invoice &model);
        virtual ~Invoice();

        // --- IPresenter ---
        void setup();
        void teardown();

    private:
        View::Invoice &m_view;
        Model::Invoice &m_model;
    };
}

#endif // PRESENTER_INVOICE_H
