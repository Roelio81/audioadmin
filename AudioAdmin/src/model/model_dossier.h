#ifndef _MODEL_DOSSIER_H
#define _MODEL_DOSSIER_H

#include "model_klant.h"

class QDomElement;

namespace Model
{
	class Dossier
	{
		public:
			Dossier();
			virtual ~Dossier();

			void fromDomElement(const QDomElement &e);
			QDomElement toDomElement() const;

			Klant &getKlant();

		private:
			Klant m_klant;
	};
}

#endif // _MODEL_DOSSIER_H
