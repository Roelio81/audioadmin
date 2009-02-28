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
        Dossier(View::Dossier &view, Model::Dossier &model);
        virtual ~Dossier();

        void attachToUniversum(Model::Universum *universum);
        void detachFromUniversum();

        void setup();

    private slots:
        void briefArtsTonen();
        void briefArtsSluiten();
        void briefKlantTonen();
        void briefKlantSluiten();
        void briefMutualiteitTonen();
        void briefMutualiteitSluiten();
        void factuurTonen();
        void factuurSluiten();
        void meetgegevensTonen();
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
        View::BriefKlant *m_briefKlant;
        View::BriefMutualiteit *m_briefMutualiteit;
        View::Factuur *m_factuur;
        View::Meetgegevens *m_meetgegevens;
    };
}

#endif // _PRESENTER_DOSSIER_H
