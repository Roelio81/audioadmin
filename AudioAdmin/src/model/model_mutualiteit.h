#ifndef _MODEL_MUTUALITEIT_H
#define _MODEL_MUTUALITEIT_H

#include "model_entiteit.h"

class QDomElement;

namespace Model
{
	class Mutualiteit : public Entiteit
	{
		public:
			Mutualiteit();
			virtual ~Mutualiteit();

			void fromDomElement(const QDomElement &e);
			QDomElement toDomElement() const;
	};
}

#endif // _MODEL_MUTUALITEIT_H
