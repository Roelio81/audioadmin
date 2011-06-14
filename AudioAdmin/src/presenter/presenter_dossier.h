#ifndef _PRESENTER_DOSSIER_H
#define _PRESENTER_DOSSIER_H

#include <QObject>

namespace View
{
    class Dossier;
    class BriefArts;
    class BriefKlant;
    class BriefMutualiteit;
    class Factuur;
    class Meetgegevens;
}

namespace Model
{
    class Dossier;
    class Universum;
}

namespace Presenter
{
    class Dossier : public QObject
    {
    Q_OBJECT
    public:
        explicit Dossier(View::Dossier &view, Model::Dossier &model);
        virtual ~Dossier();

        void attachToUniversum(Model::Universum *universum);
        void detachFromUniversum();

        void setup();
        void teardown();

    signals:
        void dossierGewijzigd(int id);
        void hoorapparaatGewijzigd();

    private slots:
        void briefArtsTonen();
        void briefArtsSluiten();
        void briefArtsBewaren();
        void briefKlantTonen();
        void briefMutualiteitTonen();
        void briefMutualiteitSluiten();
        void briefMutualiteitBewaren();
        void factuurTonen();
        void factuurSluiten();
        void factuurBewaren();
        void meetgegevensTonen();
        void meetgegevensBewaren();
        void meetgegevensSluiten();

    private:
        void setupBriefArts();
        void setupBriefKlant();
        void setupBriefMutualiteit();
        void setupFactuur();
        void setupMeetgegevens();

        View::Dossier &m_view;
        Model::Dossier &m_model;

        Model::Universum *m_universum;
        View::BriefArts *m_briefArts;
        View::BriefMutualiteit *m_briefMutualiteit;
        View::Factuur *m_factuur;
        View::Meetgegevens *m_meetgegevens;
    };
}

#endif // _PRESENTER_DOSSIER_H
