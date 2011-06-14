#ifndef _MODEL_ARTS_H
#define _MODEL_ARTS_H

#include "model_entiteit.h"

class QDomDocument;
class QDomElement;

namespace Model
{
    class Arts : public Entiteit
    {
    public:
        explicit Arts(int id);
        virtual ~Arts();

        void fromDomElement(const QDomElement &e);
        QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        int getId() const { return m_id; }
        QString getVoornaam() const { return m_voornaam; }

        // --- Setters ---
        void setVoornaam(const QString &value) { m_voornaam = value; }

    private:
        // --- Data members ---
        const int m_id;
        QString m_voornaam;
    };
}

#endif // _MODEL_ARTS_H
