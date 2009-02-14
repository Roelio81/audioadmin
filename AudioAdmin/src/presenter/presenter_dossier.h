#ifndef _PRESENTER_DOSSIER_H
#define _PRESENTER_DOSSIER_H

#include <QObject>

namespace View
{
	class Dossier;
}

namespace Model
{
	class Dossier;
}

namespace Presenter
{
	class Dossier : public ::QObject
	{
		public:
			Dossier(View::Dossier &view, Model::Dossier &model);
			virtual ~Dossier();

			void setup();

		private:
			View::Dossier &m_view;
			Model::Dossier &m_model;
	};
}

#endif // _PRESENTER_DOSSIER_H
