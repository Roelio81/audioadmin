#ifndef _MODEL_UNIVERSUM_H
#define _MODEL_UNIVERSUM_H

#include <QMap>
#include <QObject>
#include <QString>
#include <QVector>

class QDomElement;

namespace Model
{
	class Arts;
	class Dossier;
	class Mutualiteit;

	class Universum : public QObject
	{
		Q_OBJECT
		public:
			Universum(const ::QString &bestandsNaam);
			virtual ~Universum();

			bool bewaren();
			bool openen();

			void toevoegenDossier(Dossier *dossier);
			void verwijderenDossier();
			QVector<Dossier *> &getDossiers();
			
			QString getNaam() const;

		public slots:
			void openen(const QString &bestandsNaam);
			void bewaren(const QString &bestandsNaam);
			
		private:
			void openInstellingen(::QDomElement &element);

			QString m_bestandsNaam;
			QVector<Dossier *> m_dossierLijst;
			QVector<Arts *> m_artsenLijst;
			QVector<Mutualiteit *> m_mutualiteitenLijst;
			
			QString m_naam;
	};
}

#endif // _MODEL_UNIVERSUM_H
