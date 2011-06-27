#ifndef _MODEL_ENTITY_H
#define _MODEL_ENTITY_H

#include <QString>

class QDomDocument;
class QDomElement;

namespace Model
{
    class Entity
    {
    public:
        explicit Entity();
        virtual ~Entity();

        // --- ISerializable ---
        virtual void fromDomElement(const QDomElement &e);
        virtual QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        QString getName() const { return m_name; }
        QString getStreet() const { return m_straat; }
        int getPostalCode() const { return m_postalCode; }
        QString getCity() const { return m_city; }
        QString getTelephone() const { return m_telephone; }
        QString getComments() const { return m_comments; }

        // --- Setters ---
        void setName(const QString &value) { m_name = value; }
        void setStreet(const QString &value) { m_straat = value; }
        void setPostalCode(int value) { m_postalCode = value; }
        void setCity(const QString &value) { m_city = value; }
        void setTelephone(const QString &value) { m_telephone = value; }
        void setComments(const QString &value) { m_comments = value; }

    private:
        // --- Data members ---
        QString m_name;
        QString m_straat;
        int m_postalCode;
        QString m_city;
        QString m_telephone;
        QString m_comments;
    };
}

#endif // _MODEL_ENTITY_H
