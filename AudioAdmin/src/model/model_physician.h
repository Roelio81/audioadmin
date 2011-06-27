#ifndef _MODEL_PHYSICIAN_H
#define _MODEL_PHYSICIAN_H

#include "model_entity.h"

class QDomDocument;
class QDomElement;

namespace Model
{
    class Physician : public Entity
    {
    public:
        explicit Physician(int id);
        virtual ~Physician();

        // --- ISerializable ---
        virtual void fromDomElement(const QDomElement &e);
        virtual QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        int getId() const { return m_id; }
        QString getFirstName() const { return m_firstName; }

        // --- Setters ---
        void setFirstName(const QString &value) { m_firstName = value; }

    private:
        // --- Data members ---
        const int m_id;
        QString m_firstName;
    };
}

#endif // _MODEL_PHYSICIAN_H
