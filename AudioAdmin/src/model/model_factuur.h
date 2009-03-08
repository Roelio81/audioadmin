#ifndef _MODEL_FACTUUR_H
#define _MODEL_FACTUUR_H

class QDomElement;

namespace Model
{
    class Factuur
    {
    public:
        Factuur();
        virtual ~Factuur();

        void fromDomElement(const QDomElement &e);
        QDomElement toDomElement() const;
    };
}

#endif // _MODEL_KLANT_H
