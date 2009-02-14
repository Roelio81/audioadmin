#ifndef _VIEW_DOSSIER_H
#define _VIEW_DOSSIER_H

#include <QObject>
#include <QDate>

namespace View
{
	class Universum;
	
	class Dossier : QObject
	{
		Q_OBJECT
		public:
			Dossier(Universum &universum);
			virtual ~Dossier();

			void setAanspreektitel(const QString &value);
			void setKlantNaam(const QString &value);
			void setKlantVoornaam(const QString &value);
			void setKlantStraat(const QString &value);
			void setKlantPostcode(const QString &value);
			void setKlantGemeente(const QString &value);
			void setKlantTelefoon(const QString &value);
			void setKlantGeboorteDatum(const QDate &value);
			void setKlantMutualiteit(int value);
			void setAansluitingsnummer(const QString &value);
			void setPlaatsAanpassing(const QString &value);
			void setKlantOpmerkingen(const QString &value);

			QString getAanspreektitel() const;
			QString getKlantNaam() const;
			QString getKlantVoornaam() const;
			QString getKlantStraat() const;
			int getKlantPostcode() const;
			QString getKlantGemeente() const;
			QString getKlantTelefoon() const;
			QDate getKlantGeboorteDatum() const;
			int getKlantMutualiteit() const;
			QString getAansluitingsnummer() const;
			QString getPlaatsAanpassing() const;
			QString getKlantOpmerkingen() const;

		private:
			Universum &m_universum;
	};
}

#endif // _VIEW_DOSSIER_H
