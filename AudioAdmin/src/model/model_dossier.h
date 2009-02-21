#ifndef _MODEL_DOSSIER_H
#define _MODEL_DOSSIER_H

#include "model_klant.h"
#include "model_meetgegevens.h"

class QDomElement;

namespace Model
{
	class Dossier
	{
	public:
		Dossier(int id);
		virtual ~Dossier();

		void fromDomElement(const QDomElement &e);
		QDomElement toDomElement() const;

		Klant &getKlant();
		Meetgegevens &getMeetgegevens();

		int getId() const;

		int getArts() const;

		void setArts(int value);

	private:
		const int m_id;
		Klant m_klant;
		int m_arts;
		Meetgegevens m_meetgegevens;
	};
}

#endif // _MODEL_DOSSIER_H
