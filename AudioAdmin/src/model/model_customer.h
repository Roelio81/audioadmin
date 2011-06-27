#ifndef _MODEL_KLANT_H
#define _MODEL_KLANT_H

#include "model_entity.h"
#include <QDate>
#include <QString>

class QDomDocument;
class QDomElement;

namespace Model
{
    class Universe;

    class Klant : public Entity
    {
    public:
        explicit Klant(const Universe &universum);
        virtual ~Klant();

        void fromDomElement(const QDomElement &e);
        QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        QString getAanspreektitel() const { return m_aanspreektitel; }
        QString getVoornaam() const { return m_voornaam; }
        QDate getGeboorteDatum() const { return m_geboorteDatum; }

        // --- Setters ---
        void setAanspreektitel(const QString &value) { m_aanspreektitel = value; }
        void setVoornaam(const QString &value) { m_voornaam = value; }
        void setGeboorteDatum(const QDate &value) { m_geboorteDatum = value; }

    private:
        // --- Data members ---
        const Universe &m_universum;
        QString m_aanspreektitel;
        QString m_voornaam;
        QDate m_geboorteDatum;
    };
}

#endif // _MODEL_KLANT_H
