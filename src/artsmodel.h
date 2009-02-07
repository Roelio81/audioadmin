#ifndef __ARTSMODEL_H__
#define __ARTSMODEL_H__

#include <QObject>

class QDomElement;

class ArtsModel : public QObject
{
	Q_OBJECT
	public:
		ArtsModel(QDomElement &e);
		virtual ~ArtsModel();
};

#endif // __ARTSMODEL_H__
