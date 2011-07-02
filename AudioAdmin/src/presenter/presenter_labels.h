#ifndef PRESENTER_LABELS_H
#define PRESENTER_LABELS_H

#include <QObject>

namespace View
{
    class Labels;
}

namespace Model
{
    class Universe;
}

namespace Presenter
{
    class Labels : public QObject
    {
    Q_OBJECT
    public:
        explicit Labels(View::Labels &view, Model::Universe &model);
        virtual ~Labels();

        // --- IPresenter ---
        virtual void setup();
        virtual void teardown();

    private slots:
        void print();

    private:
        // --- Data members ---
        View::Labels &m_view;
        Model::Universe &m_model;
    };

}

#endif // PRESENTER_LABELS_H
