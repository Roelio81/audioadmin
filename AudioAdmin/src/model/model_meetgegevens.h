#ifndef _MODEL_MEETGEGEVENS_H
#define _MODEL_MEETGEGEVENS_H

#include <QObject>

class QDomElement;

namespace Model
{
	class Meetgegevens : public ::QObject
	{
		Q_OBJECT
		public:
			Meetgegevens(::QDomElement &e);
			virtual ~Meetgegevens();
	};
}

#endif // _MODEL_MEETGEGEVENS_H
