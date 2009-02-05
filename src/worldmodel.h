#ifndef __MAINDOCUMENT_H__
#define __MAINDOCUMENT_H__

#include <QMap>
#include <QObject>
#include <QString>
#include <QVector>

class DossierModel;
class MutualiteitModel;
class ArtsModel;

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
	QString m_bestandsNaam;
	QVector<DossierModel *> m_dossierLijst;
	QVector<ArtsModel *> m_artsenLijst;
	QVector<MutualiteitModel *> m_mutualiteitenLijst;
	QMap<QString, QVector<QString> > m_apparatenLijst;
};

#endif // __MAINDOCUMENT_H__
