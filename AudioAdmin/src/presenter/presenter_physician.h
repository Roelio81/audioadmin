#ifndef _PRESENTER_PHYSICIAN_H
#define _PRESENTER_PHYSICIAN_H

#include <QObject>

namespace View
{
    class Physician;
}

namespace Model
{
    class Physician;
}

namespace Presenter
{
    class Physician : public QObject
    {
    Q_OBJECT
    public:
        Physician(View::Physician &view, Model::Physician &model);
        virtual ~Physician();

        // --- IPresenter ---
        virtual void setup();
        virtual void teardown();

    signals:
        void edited(int id);

    private:
        View::Physician &m_view;
        Model::Physician &m_model;
    };
}

#endif // _PRESENTER_PHYSICIAN_H
