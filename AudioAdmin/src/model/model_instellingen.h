#ifndef _MODEL_INSTELLINGEN_H
#define _MODEL_INSTELLINGEN_H

#include <QObject>
#include <QString>

class QDomElement;

namespace Model
{
	class Instellingen : public QObject
	{
		Q_OBJECT
		public:
			Instellingen();
			explicit Instellingen(QDomElement &e);
			virtual ~Instellingen();

			QString getNaam() const;
			QString getStraat() const;
			int getPostcode() const;
			QString getGemeente() const;

		private:
			QString m_naam;
			QString m_straat;
			int m_postcode;
			QString m_gemeente;
	};
}

#endif // _MODEL_INSTELLINGEN_H
