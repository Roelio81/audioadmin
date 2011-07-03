#ifndef PRESENTER_LETTER_H
#define PRESENTER_LETTER_H

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
    class Letter : public QObject
    {
    Q_OBJECT
    public:
        explicit Letter(View::Letter &view, Model::Letter &model);
        virtual ~Letter();

        // --- IPresenter ---
        virtual void setup();
        virtual void teardown();

    protected:
        Model::Letter &getModel() { return m_model; }
        const Model::Letter &getModel() const { return m_model; }

        // --- To be implemented by subclasses ---
        virtual QString getGreeting() const = 0;
        virtual QString getAddresseeName() const = 0;
        virtual QString getAddresseeStreet() const = 0;
        virtual QString getAddresseeCity() const = 0;
        virtual QString getDefaultText() const = 0;

    private slots:
        void print();

    private:
        View::Letter &m_view;
        Model::Letter &m_model;
    };
}

#endif // PRESENTER_LETTER_H
