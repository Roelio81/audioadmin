#ifndef _MODEL_KLANT_H
#define _MODEL_KLANT_H

#include "model_entiteit.h"
#include <QDate>
#include <QString>

class QDomElement;

namespace Model
{
    class Klant : public Entiteit
    {
    public:
        Klant();
        virtual ~Klant();

        void fromDomElement(const QDomElement &e);
        QDomElement toDomElement() const;

        QString getAanspreektitel() const;
        QString getVoornaam() const;
        QDate getGeboorteDatum() const;

        void setAanspreektitel(const QString &value);
        void setVoornaam(const QString &value);
        void setGeboorteDatum(const QDate &value);

    private:
        QString m_aanspreektitel;
        QString m_voornaam;
        QDate m_geboorteDatum;
    };
}

#endif // _MODEL_KLANT_H
