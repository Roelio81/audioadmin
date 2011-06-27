#ifndef _MODEL_DOSSIER_H
#define _MODEL_DOSSIER_H

#include "model_letter.h"
#include "model_invoice.h"
#include "model_customer.h"
#include "model_measurements.h"

class QDomDocument;
class QDomElement;

namespace Model
{
    class Universe;

    class File
    {
    public:
        explicit File(int id, const Universe &universum);
        virtual ~File();

        // --- ISerializable ---
        virtual void fromDomElement(const QDomElement &e);
        virtual QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        int getId() const { return m_id; }
        const Universe &getUniversum() const { return m_universum; }
        int getArts() const { return m_arts; }
        int getMutualiteit() const { return m_mutualiteit; }
        QString getAansluitingsnummer() const { return m_aansluitingsnummer; }
        QString getPlaatsAanpassing() const { return m_plaatsAanpassing; }
        QString getRechterHoorapparaatMerk() const { return m_rechterHoorapparaatMerk; }
        QString getRechterHoorapparaatType() const { return m_rechterHoorapparaatType; }
        QString getRechterHoorapparaatSerienummer() const { return m_rechterHoorapparaatSerienummer; }
        double getRechterHoorapparaatPrijs() const { return m_rechterHoorapparaatPrijs; }
        QString getLinkerHoorapparaatMerk() const { return m_linkerHoorapparaatMerk; }
        QString getLinkerHoorapparaatType() const { return m_linkerHoorapparaatType; }
        QString getLinkerHoorapparaatSerienummer() const { return m_linkerHoorapparaatSerienummer; }
        double getLinkerHoorapparaatPrijs() const { return m_linkerHoorapparaatPrijs; }
        int getAantalHoorapparaten() const;
        QDate getOnderzoekDatum() const { return m_onderzoekDatum; }
        QDate getProefDatum() const { return m_proefDatum; }
        QDate getNKORapportDatum() const { return m_nkoRapportDatum; }
        QDate getDokterAdviesDatum() const { return m_dokterAdviesDatum; }
        QDate getAkkoordMutualiteitDatum() const { return m_akkoordMutualiteitDatum; }
        QDate getBetalingDatum() const { return m_betalingDatum; }
        QDate getAfleveringDatum() const { return m_afleveringDatum; }
        QDate getWisselDatum() const { return m_wisselDatum; }
        QDate getOnderhoudsContractDatum() const { return m_onderhoudsContractDatum; }
        Letter &getBriefArts() { return m_letterPhysician; }
        const Letter &getBriefArts() const { return m_letterPhysician; }
        Letter &getBriefKlant() { return m_letterCustomer; }
        const Letter &getBriefKlant() const { return m_letterCustomer; }
        Letter &getBriefMutualiteit() { return m_briefMutualiteit; }
        const Letter &getBriefMutualiteit() const { return m_briefMutualiteit; }
        Invoice &getFactuur() { return m_invoice; }
        const Invoice &getFactuur() const { return m_invoice; }
        Klant &getKlant() { return m_customer; }
        const Klant &getKlant() const { return m_customer; }
        Measurements &getMeetgegevens() { return m_meetgegevens; }
        const Measurements &getMeetgegevens() const { return m_meetgegevens; }

        // --- Setters ---
        void setArts(int value) { m_arts = value; }
        void setMutualiteit(int value) { m_mutualiteit = value; }
        void setAansluitingsnummer(const QString &value) { m_aansluitingsnummer = value; }
        void setPlaatsAanpassing(const QString &value) { m_plaatsAanpassing = value; }
        void setRechterHoorapparaatMerk(const QString &value) { m_rechterHoorapparaatMerk = value; }
        void setRechterHoorapparaatType(const QString &value) { m_rechterHoorapparaatType = value; }
        void setRechterHoorapparaatSerienummer(const QString &value) { m_rechterHoorapparaatSerienummer = value; }
        void setRechterHoorapparaatPrijs(double value) {m_rechterHoorapparaatPrijs = value; }
        void setLinkerHoorapparaatMerk(const QString &value) { m_linkerHoorapparaatMerk = value; }
        void setLinkerHoorapparaatType(const QString &value) { m_linkerHoorapparaatType = value; }
        void setLinkerHoorapparaatSerienummer(const QString &value) { m_linkerHoorapparaatSerienummer = value; }
        void setLinkerHoorapparaatPrijs(double value) { m_linkerHoorapparaatPrijs = value; }
        void setOnderzoekDatum(const QDate &value) { m_onderzoekDatum = value; }
        void setProefDatum(const QDate &value) { m_proefDatum = value; }
        void setNKORapportDatum(const QDate &value) { m_nkoRapportDatum = value; }
        void setDokterAdviesDatum(const QDate &value) { m_dokterAdviesDatum = value; }
        void setAkkoordMutualiteitDatum(const QDate &value) { m_akkoordMutualiteitDatum = value; }
        void setBetalingDatum(const QDate &value) { m_betalingDatum = value; }
        void setAfleveringDatum(const QDate &value) { m_afleveringDatum = value; }
        void setWisselDatum(const QDate &value) { m_wisselDatum = value; }
        void setOnderhoudsContractDatum(const QDate &value) { m_onderhoudsContractDatum = value; }

    private:
        // --- Data members ---
        const int m_id;
        const Universe &m_universum;
        int m_arts;
        int m_mutualiteit;
        QString m_aansluitingsnummer;
        QString m_plaatsAanpassing;
        QString m_rechterHoorapparaatMerk;
        QString m_rechterHoorapparaatType;
        QString m_rechterHoorapparaatSerienummer;
        double m_rechterHoorapparaatPrijs;
        QString m_linkerHoorapparaatMerk;
        QString m_linkerHoorapparaatType;
        QString m_linkerHoorapparaatSerienummer;
        double m_linkerHoorapparaatPrijs;
        QDate m_onderzoekDatum;
        QDate m_proefDatum;
        QDate m_nkoRapportDatum;
        QDate m_dokterAdviesDatum;
        QDate m_akkoordMutualiteitDatum;
        QDate m_betalingDatum;
        QDate m_afleveringDatum;
        QDate m_wisselDatum;
        QDate m_onderhoudsContractDatum;
        Letter m_letterPhysician;
        Letter m_letterCustomer;
        Letter m_briefMutualiteit;
        Invoice m_invoice;
        Klant m_customer;
        Measurements m_meetgegevens;
    };
}

#endif // _MODEL_DOSSIER_H
