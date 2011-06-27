#ifndef _PRESENTER_MUTUALITEIT_H
#define _PRESENTER_MUTUALITEIT_H

#include <QObject>

namespace View
{
    class InsuranceCompany;
}

namespace Model
{
    class InsuranceCompany;
}

namespace Presenter
{
    class InsuranceCompany : public QObject
    {
    Q_OBJECT
    public:
        explicit InsuranceCompany(View::InsuranceCompany &view, Model::InsuranceCompany &model);
        virtual ~InsuranceCompany();

        // --- IPresenter ---
        virtual void setup();
        virtual void teardown();

    signals:
        void edited(int id);

    private:
        View::InsuranceCompany &m_view;
        Model::InsuranceCompany &m_model;
    };
}

#endif // _PRESENTER_MUTUALITEIT_H
