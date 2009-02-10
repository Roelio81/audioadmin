#ifndef _MODEL_BRIEFKLANT_H
#define _MODEL_BRIEFKLANT_H

#include <QObject>

class QDomElement;

namespace Model
{
	class BriefKlant : public QObject
	{
		Q_OBJECT
		public:
			BriefKlant();
			explicit BriefKlant(QDomElement &e);
			virtual ~BriefKlant();
	};
}

#endif // _MODEL_BRIEFKLANT_H
