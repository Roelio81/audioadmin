#ifndef _MODEL_MUTUALITEIT_H
#define _MODEL_MUTUALITEIT_H

#include <QObject>

class QDomElement;

namespace Model
{
	class Mutualiteit : public ::QObject
	{
		Q_OBJECT
		public:
			Mutualiteit(::QDomElement &e);
			virtual ~Mutualiteit();
	};
}

#endif // _MODEL_MUTUALITEIT_H
