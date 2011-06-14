#ifndef _MODEL_BRIEFKLANT_H
#define _MODEL_BRIEFKLANT_H

#include <QString>

class QDomDocument;
class QDomElement;

namespace Model
{
    class Dossier;

    class BriefKlant
    {
    public:
        explicit BriefKlant(const Dossier &dossier);
        virtual ~BriefKlant();

        void fromDomElement(const QDomElement &e);
        QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        const Dossier &getDossier() { return m_dossier; }
        QString getPostdatum() const { return m_postdatum; }
        QString getTekstblok() const { return m_tekstblok; }

        // --- Setters ---
        void setPostdatum(const QString &value) { m_postdatum = value; }
        void setTekstblok(const QString &value) { m_tekstblok = value; }

    private:
        // --- Data members ---
        const Dossier &m_dossier;
        QString m_postdatum;
        QString m_tekstblok;
    };
}

#endif // _MODEL_KLANT_H
