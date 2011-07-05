#ifndef PRESENTER_MEASUREMENTS_H
#define PRESENTER_MEASUREMENTS_H

#include <QObject>

namespace View
{
    class Measurements;
}

namespace Model
{
    class Measurements;
}

namespace Presenter
{
    class Measurements : public QObject
    {
    Q_OBJECT
    public:
        explicit Measurements(View::Measurements &view, Model::Measurements &model);
        virtual ~Measurements();

        // --- IPresenter ---
        virtual void setup();
        virtual void teardown();

    private:
        View::Measurements &m_view;
        Model::Measurements &m_model;
    };
}

#endif // PRESENTER_MEASUREMENTS_H
