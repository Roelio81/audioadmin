#ifndef __MAINDOCUMENT_H__
#define __MAINDOCUMENT_H__

#include <QMap>
#include <QObject>
#include <QString>
#include <QVector>

class ArtsModel;
class DossierModel;
class MutualiteitModel;
class QDomElement;

class WorldModel : public QObject
{
Q_OBJECT
public:
	WorldModel(const QString &bestandsNaam);
	virtual ~WorldModel();

	bool save();
	bool load();

	void addDossier(DossierModel *dossier);
	void deleteDossier();
	QVector<DossierModel *> &getDossiers();

public slots:
	void load(QString bestandsNaam);
	void save(QString bestandsNaam);
	
private:
	void loadInstellingen(QDomElement &e);

	QString m_bestandsNaam;
	QVector<DossierModel *> m_dossierLijst;
	QVector<ArtsModel *> m_artsenLijst;
	QVector<MutualiteitModel *> m_mutualiteitenLijst;
};

#endif // __MAINDOCUMENT_H__
