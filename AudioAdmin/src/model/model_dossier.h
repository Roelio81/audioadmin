#ifndef _MODEL_DOSSIER_H
#define _MODEL_DOSSIER_H

#include <QObject>

class QDomElement;

namespace Model
{
	class Dossier : public QObject
	{
		Q_OBJECT
		public:
			Dossier();
			explicit Dossier(QDomElement &e);
			virtual ~Dossier();
	};
}

#endif // _MODEL_DOSSIER_H
