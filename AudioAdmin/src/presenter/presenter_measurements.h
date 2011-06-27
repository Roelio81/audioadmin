#ifndef PRESENTER_MEETGEGEVENS_H
#define PRESENTER_MEETGEGEVENS_H

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

        void setup();
        void teardown();

    private:
        View::Measurements &m_view;
        Model::Measurements &m_model;
    };
}

#endif // PRESENTER_MEETGEGEVENS_H
