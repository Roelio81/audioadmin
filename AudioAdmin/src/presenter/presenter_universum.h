#ifndef _PRESENTER_UNIVERSUM_H
#define _PRESENTER_UNIVERSUM_H

#include <QObject>

namespace View
{
    class Universum;
}

namespace Model
{
    class Universum;
}

namespace Presenter
{
    class Arts;
    class Dossier;
    class Mutualiteit;
	
    class Universum : public ::QObject
    {
    Q_OBJECT
    public:
        Universum(View::Universum &view, Model::Universum &model);
        virtual ~Universum();

    private slots:
        void openen(QString bestandsNaam);
        void bewaren(QString bestandsNaam);
        void etiketten();
        void instellingen();
        void toonArts(int id);
        void toonDossier(int id);
        void toonMutualiteit(int id);
        void verwijderArts(int it);
        void verwijderDossier(int it);
        void verwijderMutualiteit(int it);

    private:
        void setupEtiketten();
        void setupInstellingen();
        void teardownEtiketten();
        void teardownInstellingen();

        void refreshArtsenLijst();
        void refreshHoorapparatenLijst();
        void refreshKlantenLijst();
        void refreshMutualiteitenLijst();

        View::Universum &m_view;
        Model::Universum &m_model;

        Presenter::Arts *m_artsPresenter;
        Presenter::Dossier *m_dossierPresenter;
        Presenter::Mutualiteit *m_mutualiteitPresenter;
    };
}

#endif // _PRESENTER_UNIVERSUM_H
