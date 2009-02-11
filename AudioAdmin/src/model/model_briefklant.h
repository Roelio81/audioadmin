#ifndef _MODEL_BRIEFKLANT_H
#define _MODEL_BRIEFKLANT_H

class QDomElement;

namespace Model
{
	class BriefKlant
	{
		public:
			BriefKlant();
			virtual ~BriefKlant();

			void fromDomElement(const QDomElement &e);
			QDomElement toDomElement() const;
	};
}

#endif // _MODEL_BRIEFKLANT_H
