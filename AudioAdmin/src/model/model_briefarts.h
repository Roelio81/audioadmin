#ifndef _MODEL_BRIEFARTS_H
#define _MODEL_BRIEFARTS_H

#include <QObject>

class QDomElement;

namespace Model
{
	class BriefArts : public ::QObject
	{
		Q_OBJECT
		public:
			BriefArts(::QDomElement &e);
			virtual ~BriefArts();
	};
}

#endif // _MODEL_BRIEFARTS_H
