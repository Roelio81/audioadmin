#ifndef _MODEL_FACTUUR_H
#define _MODEL_FACTUUR_H

#include <QDate>
#include <QString>

class QDomDocument;
class QDomElement;

namespace Model
{
    class Factuur
    {
    public:
        explicit Factuur(double standaardBtwPercentage);
        virtual ~Factuur();

        QString getNummer() const;
        QDate getDatum() const;
        QDate getVervalDatum() const;
        double getKortingPercentage() const;
        double getBtwPercentage() const;
        QString getCondities() const;
        QString getTekst() const;

        void setNummer(const QString &value);
        void setDatum(const QDate &value);
        void setVervalDatum(const QDate &value);
        void setKortingPercentage(double value);
        void setBtwPercentage(double value);
        void setCondities(const QString &value);
        void setTekst(const QString &value);

        void fromDomElement(const QDomElement &e);
        QDomElement toDomElement(QDomDocument &d) const;

    private:
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
