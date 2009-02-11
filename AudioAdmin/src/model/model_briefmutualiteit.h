#ifndef _MODEL_BRIEFMUTUALITEIT_H
#define _MODEL_BRIEFMUTUALITEIT_H

class QDomElement;

namespace Model
{
	class BriefMutualiteit
	{
		public:
			BriefMutualiteit();
			virtual ~BriefMutualiteit();

			void fromDomElement(const QDomElement &e);
			QDomElement toDomElement() const;
	};
}

#endif // _MODEL_BRIEFMUTUALITEIT_H
