#ifndef _MODEL_KLANT_H
#define _MODEL_KLANT_H

#include <QObject>

class QDomElement;

namespace Model
{
	class Klant : public QObject
	{
		Q_OBJECT
		public:
			Klant();
			explicit Klant(QDomElement &e);
			virtual ~Klant();
	};
}

#endif // _MODEL_KLANT_H
