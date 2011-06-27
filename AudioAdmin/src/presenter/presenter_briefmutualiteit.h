#ifndef PRESENTER_BRIEFMUTUALITEIT_H
#define PRESENTER_BRIEFMUTUALITEIT_H

#include <QObject>

namespace View
{
    class Letter;
}

namespace Model
{
    class Letter;
}

namespace Presenter
{
    class BriefMutualiteit : public QObject
    {
    Q_OBJECT
    public:
        explicit BriefMutualiteit(View::Letter &view, Model::Letter &model);
        virtual ~BriefMutualiteit();

        void setup();
        void teardown();

    private slots:
        void print();

    private:
        View::Letter &m_view;
        Model::Letter &m_model;
    };
}

#endif // PRESENTER_BRIEFMUTUALITEIT_H
