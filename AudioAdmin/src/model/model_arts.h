#ifndef _MODEL_ARTS_H
#define _MODEL_ARTS_H

#include "model_entiteit.h"

class QDomElement;

namespace Model
{
	class Arts : public Entiteit
	{
	public:
		Arts(int id);
		virtual ~Arts();

		void fromDomElement(const QDomElement &e);
		QDomElement toDomElement() const;

		int getId() const;

		QString getVoornaam() const;

		void setVoornaam(const QString &value);

	private:
		const int m_id;
		QString m_voornaam;
	};
}

#endif // _MODEL_ARTS_H
