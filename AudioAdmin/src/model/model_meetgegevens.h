#ifndef _MODEL_MEETGEGEVENS_H
#define _MODEL_MEETGEGEVENS_H

class QDomElement;

namespace Model
{
	class Meetgegevens
	{
		public:
			Meetgegevens();
			virtual ~Meetgegevens();

			void fromDomElement(const QDomElement &e);
			QDomElement toDomElement() const;
	};
}

#endif // _MODEL_MEETGEGEVENS_H
