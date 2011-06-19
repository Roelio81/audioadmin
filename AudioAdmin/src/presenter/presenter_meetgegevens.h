#ifndef PRESENTER_MEETGEGEVENS_H
#define PRESENTER_MEETGEGEVENS_H

#include <QObject>

namespace View
{
    class Meetgegevens;
}

namespace Model
{
    class Meetgegevens;
}

namespace Presenter
{
    class Meetgegevens : public QObject
    {
    Q_OBJECT
    public:
        explicit Meetgegevens(View::Meetgegevens &view, Model::Meetgegevens &model);
        virtual ~Meetgegevens();

        void setup();
        void teardown();

    private:
        View::Meetgegevens &m_view;
        Model::Meetgegevens &m_model;
    };
}

#endif // PRESENTER_MEETGEGEVENS_H
