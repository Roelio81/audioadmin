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
        QString getLinkerHoorapparaatMerk() const;
        QString getLinkerHoorapparaatType() const;
        QString getRechterHoorapparaatMerk() const;
        QString getRechterHoorapparaatType() const;
        int getAantalHoorapparaten() const;

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
        void setLinkerHoorapparaatMerk(const QString &value);
        void setLinkerHoorapparaatType(const QString &value);
        void setRechterHoorapparaatMerk(const QString &value);
        void setRechterHoorapparaatType(const QString &value);

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
        QString m_linkerHoorapparaatMerk;
        QString m_linkerHoorapparaatType;
        QString m_rechterHoorapparaatMerk;
        QString m_rechterHoorapparaatType;
        Meetgegevens m_meetgegevens;
    };
}

#endif // _MODEL_DOSSIER_H
