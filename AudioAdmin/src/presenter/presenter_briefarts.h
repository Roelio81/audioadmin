#ifndef PRESENTER_BRIEFARTS_H
#define PRESENTER_BRIEFARTS_H

#include <QObject>

namespace View
{
    class Letter;
}

namespace Model
{
    class BriefArts;
}

namespace Presenter
{
    class BriefArts : public QObject
    {
    Q_OBJECT
    public:
        explicit BriefArts(View::Letter &view, Model::BriefArts &model);
        virtual ~BriefArts();

        void setup();
        void teardown();

    private slots:
        void print();

    private:
        View::Letter &m_view;
        Model::BriefArts &m_model;
    };
}

#endif // PRESENTER_BRIEFARTS_H
