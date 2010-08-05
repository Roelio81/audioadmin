#ifndef _PRESENTER_MUTUALITEIT_H
#define _PRESENTER_MUTUALITEIT_H

#include <QObject>

namespace View
{
    class Mutualiteit;
}

namespace Model
{
    class Mutualiteit;
}

namespace Presenter
{
    class Mutualiteit : public ::QObject
    {
    Q_OBJECT
    public:
        Mutualiteit(View::Mutualiteit &view, Model::Mutualiteit &model);
        virtual ~Mutualiteit();

        void setup();
        void teardown();

    signals:
        void mutualiteitGewijzigd(int id);

    private:
        View::Mutualiteit &m_view;
        Model::Mutualiteit &m_model;
    };
}

#endif // _PRESENTER_MUTUALITEIT_H
