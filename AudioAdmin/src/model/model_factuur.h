#ifndef _MODEL_FACTUUR_H
#define _MODEL_FACTUUR_H

#include <QObject>

class QDomElement;

namespace Model
{
	class Factuur : public QObject
	{
		Q_OBJECT
		public:
			Factuur();
			explicit Factuur(QDomElement &e);
			virtual ~Factuur();
	};
}

#endif // _MODEL_KLANT_H
