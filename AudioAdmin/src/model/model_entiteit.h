#ifndef _MODEL_ENTITEIT_H
#define _MODEL_ENTITEIT_H

#include <QString>

class QDomDocument;
class QDomElement;

namespace Model
{
    class Entiteit
    {
    public:
        explicit Entiteit();
        virtual ~Entiteit();

        void fromDomElement(const QDomElement &e);
        QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        QString getNaam() const { return m_naam; }
        QString getStraat() const { return m_straat; }
        int getPostcode() const { return m_postcode; }
        QString getGemeente() const { return m_gemeente; }
        QString getTelefoon() const { return m_telefoon; }
        QString getOpmerkingen() const { return m_opmerkingen; }

        // --- Setters ---
        void setNaam(const QString &value) { m_naam = value; }
        void setStraat(const QString &value) { m_straat = value; }
        void setPostcode(int value) { m_postcode = value; }
        void setGemeente(const QString &value) { m_gemeente = value; }
        void setTelefoon(const QString &value) { m_telefoon = value; }
        void setOpmerkingen(const QString &value) { m_opmerkingen = value; }

    private:
        // --- Data members ---
        QString m_naam;
        QString m_straat;
        int m_postcode;
        QString m_gemeente;
        QString m_telefoon;
        QString m_opmerkingen;
    };
}

#endif // _MODEL_ENTITEIT_H
