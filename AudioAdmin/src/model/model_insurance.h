#ifndef _MODEL_INSURANCE_H
#define _MODEL_INSURANCE_H

#include "model_entity.h"

class QDomDocument;
class QDomElement;

namespace Model
{
    class InsuranceCompany : public Entity
    {
    public:
        explicit InsuranceCompany(int id);
        virtual ~InsuranceCompany();

        // --- ISerializable ---
        virtual void fromDomElement(const QDomElement &e);
        virtual QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        int getId() const { return m_id; }

    private:
        const int m_id;
    };
}

#endif // _MODEL_INSURANCE_H
