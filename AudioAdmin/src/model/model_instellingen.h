#ifndef _MODEL_INSTELLINGEN_H
#define _MODEL_INSTELLINGEN_H

#include <QString>

class QDomElement;

namespace Model
{
	class Instellingen
	{
		public:
			Instellingen();
			virtual ~Instellingen();

			void fromDomElement(const QDomElement &e);
			QDomElement toDomElement() const;

			QString getNaam() const;
			QString getStraat() const;
			int getPostcode() const;
			QString getGemeente() const;
			QString getTelefoon() const;
			QString getGsm() const;
			QString getEmail() const;
			QString getOnderschrift() const;
			QString getRiziv() const;
			int getBtwPercentage() const;
			QString getBtwNummer() const;
			QString getRekeningNummer() const;

			void setNaam(const QString &value);
			void setStraat(const QString &value);
			void setPostcode(int value);
			void setGemeente(const QString &value);
			void setTelefoon(const QString &value);
			void setGsm(const QString &value);
			void setEmail(const QString &value);
			void setOnderschrift(const QString &value);
			void setRiziv(const QString &value);
			void setBtwPercentage(int value);
			void setBtwNummer(const QString &value);
			void setRekeningNummer(const QString &value);

		private:
			QString m_naam;
			QString m_straat;
			int m_postcode;
			QString m_gemeente;
			QString m_telefoon;
			QString m_gsm;
			QString m_email;
			QString m_onderschrift;
			QString m_riziv;
			int m_btwPercentage;
			QString m_btwNummer;
			QString m_rekeningNummer;
	};
}

#endif // _MODEL_INSTELLINGEN_H
