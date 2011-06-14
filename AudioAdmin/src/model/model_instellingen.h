#ifndef _MODEL_INSTELLINGEN_H
#define _MODEL_INSTELLINGEN_H

#include <QString>

class QDomDocument;
class QDomElement;

namespace Model
{
    class Universum;

    class Instellingen
    {
    public:
        explicit Instellingen(const Universum &universum);
        virtual ~Instellingen();

        void fromDomElement(const QDomElement &e);
        QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        QString getNaam() const { return m_naam; }
        QString getStraat() const { return m_straat; }
        int getPostcode() const { return m_postcode; }
        QString getGemeente() const { return m_gemeente; }
        QString getTelefoon() const { return m_telefoon; }
        QString getGsm() const { return m_gsm; }
        QString getEmail() const { return m_email; }
        QString getOnderschrift() const { return m_onderschrift; }
        QString getRiziv() const { return m_riziv; }
        int getBtwPercentage() const { return m_btwPercentage; }
        QString getBtwNummer() const { return m_btwNummer; }
        QString getRekeningNummer() const { return m_rekeningNummer; }

        // --- Setters ---
        void setNaam(const QString &value) { m_naam = value; }
        void setStraat(const QString &value) { m_straat = value; }
        void setPostcode(int value) { m_postcode = value; }
        void setGemeente(const QString &value) { m_gemeente = value; }
        void setTelefoon(const QString &value) { m_telefoon = value; }
        void setGsm(const QString &value) { m_gsm = value; }
        void setEmail(const QString &value) { m_email = value; }
        void setOnderschrift(const QString &value) { m_onderschrift = value; }
        void setRiziv(const QString &value) { m_riziv = value; }
        void setBtwPercentage(int value) { m_btwPercentage = value; }
        void setBtwNummer(const QString &value) { m_btwNummer = value; }
        void setRekeningNummer(const QString &value) { m_rekeningNummer = value; }

    private:
        // --- Data members ---
        const Universum &m_universum;
        QString m_naam;
        QString m_straat;
        int m_postcode;
        QString m_gemeente;
        QString m_telefoon;
        QString m_gsm;
        QString m_email;
        QString m_onderschrift;
        QString m_riziv;
        int m_btwPercentage;
        QString m_btwNummer;
        QString m_rekeningNummer;
    };
}

#endif // _MODEL_INSTELLINGEN_H
