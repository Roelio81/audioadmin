#ifndef __MUTUALITEITMODEL_H__
#define __MUTUALITEITMODEL_H__

#include <QObject>

class QDomElement;

class MutualiteitModel : public QObject
{
	Q_OBJECT
	public:
		MutualiteitModel(QDomElement &e);
		virtual ~MutualiteitModel();
};

#endif // __MUTUALITEITMODEL_H__
