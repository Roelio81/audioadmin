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
}

namespace Model
{
	class Dossier;
}

namespace Presenter
{
	class Dossier : public QObject
	{
	Q_OBJECT
	public:
		Dossier(View::Dossier &view, Model::Dossier &model);
		virtual ~Dossier();

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

	private:
		void setupBriefArts();
		void setupBriefKlant();
		void setupBriefMutualiteit();
		void setupFactuur();

		View::Dossier &m_view;
		Model::Dossier &m_model;

		View::BriefArts *m_briefArts;
		View::BriefKlant *m_briefKlant;
		View::BriefMutualiteit *m_briefMutualiteit;
		View::Factuur *m_factuur;
	};
}

#endif // _PRESENTER_DOSSIER_H
