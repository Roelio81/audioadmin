#ifndef MODEL_BRIEFARTS_H
#define MODEL_BRIEFARTS_H

#include <QString>

class QDomDocument;
class QDomElement;

namespace Model
{
    class Dossier;

    class BriefArts
    {
    public:
        explicit BriefArts(const Dossier &dossier);
        virtual ~BriefArts();

        void fromDomElement(const QDomElement &e);
        QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        const Dossier &getDossier() { return m_dossier; }
        QString getPostalDate() const { return m_postdatum; }
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

#endif // MODEL_BRIEFARTS_H
