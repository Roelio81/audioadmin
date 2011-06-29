#ifndef _MODEL_CUSTOMER_H
#define _MODEL_CUSTOMER_H

#include "model_entity.h"
#include <QDate>
#include <QString>

class QDomDocument;
class QDomElement;

namespace Model
{
    class Universe;

    class Customer : public Entity
    {
    public:
        explicit Customer(const Universe &universe);
        virtual ~Customer();

        // --- ISerializable ---
        virtual void fromDomElement(const QDomElement &e);
        virtual QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        QString getTitle() const { return m_title; }
        QString getFirstName() const { return m_firstName; }
        QDate getDateOfBirth() const { return m_dateOfBirth; }

        // --- Setters ---
        void setTitle(const QString &value) { m_title = value; }
        void setVoornaam(const QString &value) { m_firstName = value; }
        void setGeboorteDatum(const QDate &value) { m_dateOfBirth = value; }

    private:
        // --- Data members ---
        const Universe &m_universe;
        QString m_title;
        QString m_firstName;
        QDate m_dateOfBirth;
    };
}

#endif // _MODEL_CUSTOMER_H
