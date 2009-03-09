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
        QString getBriefArtsPostdatum() const;
        QString getBriefArtsTekstblok() const;
        QString getBriefArtsConclusie() const;
        QString getBriefKlantPostdatum() const;
        QString getBriefKlantTekstblok() const;
        QString getBriefMutualiteitPostdatum() const;
        QString getBriefMutualiteitTekstblok() const;
        QString getBriefMutualiteitConclusie() const;

        void setArts(int value);
        void setBriefArtsPostdatum(const QString &value);
        void setBriefArtsTekstblok(const QString &value);
        void setBriefArtsConclusie(const QString &value);
        void setBriefKlantPostdatum(const QString &value);
        void setBriefKlantTekstblok(const QString &value);
        void setBriefMutualiteitPostdatum(const QString &value);
        void setBriefMutualiteitTekstblok(const QString &value);
        void setBriefMutualiteitConclusie(const QString &value);

    private:
        const int m_id;
        Klant m_klant;
        int m_arts;
        QString m_briefArtsPostdatum;
        QString m_briefArtsTekstblok;
        QString m_briefArtsConclusie;
        QString m_briefKlantPostdatum;
        QString m_briefKlantTekstblok;
        QString m_briefMutualiteitPostdatum;
        QString m_briefMutualiteitTekstblok;
        QString m_briefMutualiteitConclusie;
        Meetgegevens m_meetgegevens;
    };
}

#endif // _MODEL_DOSSIER_H
