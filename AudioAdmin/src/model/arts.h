#ifndef _MODEL_ARTS_H
#define _MODEL_ARTS_H

#include <QObject>

class QDomElement;

namespace Model
{
	class Arts : public ::QObject
	{
		Q_OBJECT
		public:
			Arts(::QDomElement &e);
			virtual ~Arts();
	};
}

#endif // _MODEL_ARTS_H
