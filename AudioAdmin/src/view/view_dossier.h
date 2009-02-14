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

		void leegAanspreektitels();
		void toevoegenAanspreektitel(const QString &value);

		QString getAanspreektitel() const;
		QString getNaam() const;
		QString getVoornaam() const;
		QString getStraat() const;
		int getPostcode() const;
		QString getGemeente() const;
		QString getTelefoon() const;
		QDate getGeboorteDatum() const;
		int getMutualiteit() const;
		QString getAansluitingsnummer() const;
		QString getPlaatsAanpassing() const;
		QString getOpmerkingen() const;

		void setAanspreektitel(const QString &value);
		void setNaam(const QString &value);
		void setVoornaam(const QString &value);
		void setStraat(const QString &value);
		void setPostcode(int value);
		void setGemeente(const QString &value);
		void setTelefoon(const QString &value);
		void setGeboorteDatum(const QDate &value);
		void setMutualiteit(int value);
		void setAansluitingsnummer(const QString &value);
		void setPlaatsAanpassing(const QString &value);
		void setOpmerkingen(const QString &value);

	private:
		Universum &m_universum;
	};
}

#endif // _VIEW_DOSSIER_H
