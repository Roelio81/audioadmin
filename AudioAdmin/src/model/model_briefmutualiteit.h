#ifndef MODEL_BRIEFMUTUALITEIT_H
#define MODEL_BRIEFMUTUALITEIT_H

#include <QString>

class QDomDocument;
class QDomElement;

namespace Model
{
    class Dossier;

    class BriefMutualiteit
    {
    public:
        explicit BriefMutualiteit(const Dossier &dossier);
        virtual ~BriefMutualiteit();

        void fromDomElement(const QDomElement &e);
        QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        const Dossier &getDossier() { return m_dossier; }
        QString getPostdatum() const { return m_postdatum; }
        QString getTekstblok() const { return m_tekstblok; }
        QString getConclusie() const { return m_conclusie; }

        // --- Setters ---
        void setPostdatum(const QString &value) { m_postdatum = value; }
        void setTekstblok(const QString &value) { m_tekstblok = value; }
        void setConclusie(const QString &value) { m_conclusie = value; }

    private:
        // --- Data members ---
        const Dossier &m_dossier;
        QString m_postdatum;
        QString m_tekstblok;
        QString m_conclusie;
    };
}

#endif // MODEL_BRIEFMUTUALITEIT_H
