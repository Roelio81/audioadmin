#ifndef PRESENTER_BRIEFKLANT_H
#define PRESENTER_BRIEFKLANT_H

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
    class BriefKlant : public QObject
    {
    Q_OBJECT
    public:
        explicit BriefKlant(View::Letter &view, Model::Letter &model);
        virtual ~BriefKlant();

        void setup();
        void teardown();

    private slots:
        void print();

    private:
        View::Letter &m_view;
        Model::Letter &m_model;
    };
}

#endif // PRESENTER_BRIEFKLANT_H
