#ifndef _MODEL_ENTITEIT_H
#define _MODEL_ENTITEIT_H

#include <QString>

class QDomElement;

namespace Model
{
    class Entiteit
    {
    public:
        Entiteit();
        virtual ~Entiteit();

        void fromDomElement(const QDomElement &e);
        QDomElement toDomElement() const;

        QString getNaam() const;
        QString getStraat() const;
        int getPostcode() const;
        QString getGemeente() const;
        QString getTelefoon() const;
        QString getOpmerkingen() const;

        void setNaam(const QString &value);
        void setStraat(const QString &value);
        void setPostcode(int value);
        void setGemeente(const QString &value);
        void setTelefoon(const QString &value);
        void setOpmerkingen(const QString &value);

    private:
        QString m_naam;
        QString m_straat;
        int m_postcode;
        QString m_gemeente;
        QString m_telefoon;
        QString m_opmerkingen;
    };
}

#endif // _MODEL_ENTITEIT_H
