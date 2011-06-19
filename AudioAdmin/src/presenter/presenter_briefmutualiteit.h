#ifndef PRESENTER_BRIEFMUTUALITEIT_H
#define PRESENTER_BRIEFMUTUALITEIT_H

#include <QObject>

namespace View
{
    class BriefMutualiteit;
}

namespace Model
{
    class BriefMutualiteit;
}

namespace Presenter
{
    class BriefMutualiteit : public QObject
    {
    Q_OBJECT
    public:
        explicit BriefMutualiteit(View::BriefMutualiteit &view, Model::BriefMutualiteit &model);
        virtual ~BriefMutualiteit();

        void setup();
        void teardown();

    private slots:
        void print();

    private:
        View::BriefMutualiteit &m_view;
        Model::BriefMutualiteit &m_model;
    };
}

#endif // PRESENTER_BRIEFMUTUALITEIT_H
