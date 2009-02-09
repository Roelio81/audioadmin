#ifndef _MODEL_BRIEFMUTUALITEIT_H
#define _MODEL_BRIEFMUTUALITEIT_H

#include <QObject>

class QDomElement;

namespace Model
{
	class BriefMutualiteit : public ::QObject
	{
		Q_OBJECT
		public:
			BriefMutualiteit(::QDomElement &e);
			virtual ~BriefMutualiteit();
	};
}

#endif // _MODEL_BRIEFMUTUALITEIT_H
