#ifndef _MODEL_BRIEFARTS_H
#define _MODEL_BRIEFARTS_H

class QDomElement;

namespace Model
{
	class BriefArts
	{
		public:
			BriefArts();
			virtual ~BriefArts();

			void fromDomElement(const QDomElement &e);
			QDomElement toDomElement() const;
	};
}

#endif // _MODEL_BRIEFARTS_H
