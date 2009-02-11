#ifndef _MODEL_KLANT_H
#define _MODEL_KLANT_H

#include "model_entiteit.h"

class QDomElement;

namespace Model
{
	class Klant : public Entiteit
	{
		public:
			Klant();
			virtual ~Klant();

			void fromDomElement(const QDomElement &e);
			QDomElement toDomElement() const;
	};
}

#endif // _MODEL_KLANT_H
