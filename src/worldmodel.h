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
	public:
		WorldModel(const QString &bestandsNaam);
		virtual ~WorldModel();

		bool save();
		bool save(const QString &bestandsNaam);
		bool load();
		bool load(const QString &bestandsNaam);

		void addDossier(DossierModel *dossier);
		void deleteDossier();
		QVector<DossierModel *> &getDossiers();

	private:
		QString bestandsNaam;
		QVector<DossierModel *> dossierLijst;
		QVector<ArtsModel *> artsenLijst;
		QVector<MutualiteitModel *> mutualiteitenLijst;
		QMap<QString, QVector<QString> > apparatenLijst;
};

#endif // __MAINDOCUMENT_H__
