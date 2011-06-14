#ifndef _MODEL_MUTUALITEIT_H
#define _MODEL_MUTUALITEIT_H

#include "model_entiteit.h"

class QDomDocument;
class QDomElement;

namespace Model
{
    class Mutualiteit : public Entiteit
    {
    public:
        explicit Mutualiteit(int id);
        virtual ~Mutualiteit();

        void fromDomElement(const QDomElement &e);
        QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        int getId() const { return m_id; }

    private:
        const int m_id;
    };
}

#endif // _MODEL_MUTUALITEIT_H
