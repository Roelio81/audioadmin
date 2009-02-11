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

		private:
			QString m_naam;
			QString m_straat;
			int m_postcode;
			QString m_gemeente;
			QString m_telefoon;
	};
}

#endif // _MODEL_INSTELLINGEN_H
