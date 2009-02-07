#ifndef __DOSSIERMODEL_H__
#define __DOSSIERMODEL_H__

#include <QObject>

class QDomElement;

class DossierModel : public QObject
{
	Q_OBJECT
	public:
		DossierModel(QDomElement &e);
		virtual ~DossierModel();
};

#endif // __DOSSIERMODEL_H__
