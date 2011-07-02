#ifndef PRESENTER_SETTINGS_H
#define PRESENTER_SETTINGS_H

#include <QObject>

namespace View
{
    class Settings;
}

namespace Model
{
    class Settings;
}

namespace Presenter
{
    class Settings : public QObject
    {
    Q_OBJECT
    public:
        Settings(View::Settings &view, Model::Settings &model);
        virtual ~Settings();

        // --- IPresenter ---
        virtual void setup();
        virtual void teardown();

    private:
        // --- Data members ---
        View::Settings &m_view;
        Model::Settings &m_model;
    };
}

#endif // PRESENTER_SETTINGS_H
