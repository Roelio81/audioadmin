#ifndef _MODEL_DOSSIER_H
#define _MODEL_DOSSIER_H

#include "model_klant.h"
#include "model_meetgegevens.h"

class QDomElement;

namespace Model
{
    class Dossier
    {
    public:
        Dossier(int id);
        virtual ~Dossier();

        void fromDomElement(const QDomElement &e);
        QDomElement toDomElement() const;

        Klant &getKlant();
        Meetgegevens &getMeetgegevens();

        int getId() const;

        int getArts() const;
        int getMutualiteit() const;
        QString getAansluitingsnummer() const;
        QString getPlaatsAanpassing() const;
        QString getBriefArtsPostdatum() const;
        QString getBriefArtsTekstblok() const;
        QString getBriefArtsConclusie() const;
        QString getBriefKlantPostdatum() const;
        QString getBriefKlantTekstblok() const;
        QString getBriefMutualiteitPostdatum() const;
        QString getBriefMutualiteitTekstblok() const;
        QString getBriefMutualiteitConclusie() const;
        QString getRechterHoorapparaatMerk() const;
        QString getRechterHoorapparaatType() const;
        QString getRechterHoorapparaatSerienummer() const;
        double getRechterHoorapparaatPrijs() const;
        QString getLinkerHoorapparaatMerk() const;
        QString getLinkerHoorapparaatType() const;
        QString getLinkerHoorapparaatSerienummer() const;
        double getLinkerHoorapparaatPrijs() const;
        int getAantalHoorapparaten() const;
        QDate *getOnderzoekDatum() const;
        QDate *getProefDatum() const;
        QDate *getNKORapportDatum() const;
        QDate *getDokterAdviesDatum() const;
        QDate *getAkkoordMutualiteitDatum() const;
        QDate *getBetalingDatum() const;
        QDate *getAfleveringDatum() const;
        QDate *getWisselDatum() const;
        QDate *getOHKDatum() const;

        void setArts(int value);
        void setMutualiteit(int value);
        void setAansluitingsnummer(const QString &value);
        void setPlaatsAanpassing(const QString &value);
        void setBriefArtsPostdatum(const QString &value);
        void setBriefArtsTekstblok(const QString &value);
        void setBriefArtsConclusie(const QString &value);
        void setBriefKlantPostdatum(const QString &value);
        void setBriefKlantTekstblok(const QString &value);
        void setBriefMutualiteitPostdatum(const QString &value);
        void setBriefMutualiteitTekstblok(const QString &value);
        void setBriefMutualiteitConclusie(const QString &value);
        void setRechterHoorapparaatMerk(const QString &value);
        void setRechterHoorapparaatType(const QString &value);
        void setRechterHoorapparaatSerienummer(const QString &value);
        void setRechterHoorapparaatPrijs(double value);
        void setLinkerHoorapparaatMerk(const QString &value);
        void setLinkerHoorapparaatType(const QString &value);
        void setLinkerHoorapparaatSerienummer(const QString &value);
        void setLinkerHoorapparaatPrijs(double value);
        void setOnderzoekDatum(QDate *value);
        void setProefDatum(QDate *value);
        void setNKORapportDatum(QDate *value);
        void setDokterAdviesDatum(QDate *value);
        void setAkkoordMutualiteitDatum(QDate *value);
        void setBetalingDatum(QDate *value);
        void setAfleveringDatum(QDate *value);
        void setWisselDatum(QDate *value);
        void setOHKDatum(QDate *value);

    private:
        const int m_id;
        Klant m_klant;
        int m_arts;
        int m_mutualiteit;
        QString m_aansluitingsnummer;
        QString m_plaatsAanpassing;
        QString m_briefArtsPostdatum;
        QString m_briefArtsTekstblok;
        QString m_briefArtsConclusie;
        QString m_briefKlantPostdatum;
        QString m_briefKlantTekstblok;
        QString m_briefMutualiteitPostdatum;
        QString m_briefMutualiteitTekstblok;
        QString m_briefMutualiteitConclusie;
        QString m_rechterHoorapparaatMerk;
        QString m_rechterHoorapparaatType;
        QString m_rechterHoorapparaatSerienummer;
        double m_rechterHoorapparaatPrijs;
        QString m_linkerHoorapparaatMerk;
        QString m_linkerHoorapparaatType;
        QString m_linkerHoorapparaatSerienummer;
        double m_linkerHoorapparaatPrijs;
        QDate *m_onderzoekDatum;
        QDate *m_proefDatum;
        QDate *m_nkoRapportDatum;
        QDate *m_dokterAdviesDatum;
        QDate *m_akkoordMutualiteitDatum;
        QDate *m_betalingDatum;
        QDate *m_afleveringDatum;
        QDate *m_wisselDatum;
        QDate *m_ohkDatum;
        Meetgegevens m_meetgegevens;
    };
}

#endif // _MODEL_DOSSIER_H
