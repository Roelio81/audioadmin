#ifndef _MODEL_FACTUUR_H
#define _MODEL_FACTUUR_H

#include <QDate>
#include <QString>

class QDomDocument;
class QDomElement;

namespace Model
{
    class Universum;

    class Factuur
    {
    public:
        explicit Factuur(const Universum &universum);
        virtual ~Factuur();

        void fromDomElement(const QDomElement &e);
        QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        QString getNummer() const { return m_nummer; }
        QDate getDatum() const { return m_datum; }
        QDate getVervalDatum() const { return m_vervaldatum; }
        double getKortingPercentage() const { return m_kortingPercentage; }
        double getBtwPercentage() const { return m_btwPercentage; }
        QString getCondities() const { return m_condities; }
        QString getTekst() const { return m_tekst; }

        // --- Setters ---
        void setNummer(const QString &value) { m_nummer = value; }
        void setDatum(const QDate &value) { m_datum = value; }
        void setVervalDatum(const QDate &value) { m_vervaldatum = value; }
        void setKortingPercentage(double value) { m_kortingPercentage = value; }
        void setBtwPercentage(double value) { m_btwPercentage = value; }
        void setCondities(const QString &value) { m_condities = value; }
        void setTekst(const QString &value) { m_tekst = value; }

    private:
        // --- Data members ---
        const Universum &m_universum;
        QString m_nummer;
        QDate m_datum;
        QDate m_vervaldatum;
        double m_kortingPercentage;
        double m_btwPercentage;
        QString m_condities;
        QString m_tekst;
    };
}

#endif // _MODEL_KLANT_H
