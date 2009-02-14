#ifndef _VIEW_MUTUALITEIT_H
#define _VIEW_MUTUALITEIT_H

#include <QObject>
#include <QDate>

namespace View
{
	class Universum;
	
	class Mutualiteit : QObject
	{
	Q_OBJECT
	public:
		Mutualiteit(Universum &universum);
		virtual ~Mutualiteit();

		QString getNaam() const;
		QString getStraat() const;
		int getPostcode() const;
		QString getGemeente() const;
		QString getTelefoon() const;
		QString getOpmerkingen() const;

		void setNaam(const QString &value);
		void setStraat(const QString &value);
		void setPostcode(int value);
		void setGemeente(const QString &value);
		void setTelefoon(const QString &value);
		void setOpmerkingen(const QString &value);

	private:
		Universum &m_universum;
	};
}

#endif // _VIEW_MUTUALITEIT_H
