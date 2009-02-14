#ifndef _MODEL_MUTUALITEIT_H
#define _MODEL_MUTUALITEIT_H

#include "model_entiteit.h"

class QDomElement;

namespace Model
{
	class Mutualiteit : public Entiteit
	{
		public:
			Mutualiteit(int id);
			virtual ~Mutualiteit();

			void fromDomElement(const QDomElement &e);
			QDomElement toDomElement() const;

			int getId() const;

		private:
			const int m_id;
	};
}

#endif // _MODEL_MUTUALITEIT_H
