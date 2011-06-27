#ifndef _PRESENTER_DOSSIER_H
#define _PRESENTER_DOSSIER_H

#include <QObject>

namespace View
{
    class File;
    class BriefArts;
    class BriefKlant;
    class Letter;
    class Factuur;
    class Measurements;
}

namespace Model
{
    class File;
    class Universe;
}

namespace Presenter
{
    class Dossier : public QObject
    {
    Q_OBJECT
    public:
        explicit Dossier(View::File &view, Model::File &model);
        virtual ~Dossier();

        // --- IPresenter ---
        void setup();
        void teardown();

    signals:
        void edited(int id);
        void hoorapparaatGewijzigd();

    private slots:
        void briefArtsTonen();
        void briefKlantTonen();
        void briefMutualiteitTonen();
        void showInvoice();
        void factuurSluiten();
        void factuurBewaren();
        void showMeasurements();

    private:
        void setupInvoice();

        View::File &m_view;
        Model::File &m_model;

        Model::Universe *m_universum;
        View::Factuur *m_factuur;
    };
}

#endif // _PRESENTER_DOSSIER_H
