#ifndef _MODEL_FACTUUR_H
#define _MODEL_FACTUUR_H

#include <QObject>

class QDomElement;

namespace Model
{
	class Factuur : public ::QObject
	{
		Q_OBJECT
		public:
			Klant(::QDomElement &e);
			virtual ~Klant();
	};
}

#endif // _MODEL_KLANT_H
