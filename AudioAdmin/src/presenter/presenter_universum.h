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
	class Universum : public ::QObject
	{
	Q_OBJECT
		public:
			Universum(View::Universum &view, Model::Universum &model);
			virtual ~Universum();

		public slots:
			void openen(const QString &bestandsNaam);
			void bewaren(const QString &bestandsNaam);
			void instellingen();

		private:
			void setupInstellingen();
			void teardownInstellingen();

			void refreshArtsenLijst();
			void refreshKlantenLijst();
			void refreshMutualiteitenLijst();

			View::Universum &m_view;
			Model::Universum &m_model;
	};
}

#endif // _PRESENTER_UNIVERSUM_H
