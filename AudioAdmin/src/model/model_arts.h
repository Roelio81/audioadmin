#ifndef _MODEL_ARTS_H
#define _MODEL_ARTS_H

#include "model_entiteit.h"

class QDomElement;

namespace Model
{
	class Arts : public Entiteit
	{
		public:
			Arts();
			virtual ~Arts();
			
			void fromDomElement(const QDomElement &e);
			QDomElement toDomElement() const;
	};
}

#endif // _MODEL_ARTS_H
