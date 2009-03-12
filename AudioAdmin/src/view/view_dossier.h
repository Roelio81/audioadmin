#ifndef _VIEW_DOSSIER_H
#define _VIEW_DOSSIER_H

#include <QMap>
#include <QObject>
#include <QDate>

namespace View
{
    class Universum;

    class Dossier : public QObject
    {
    Q_OBJECT
    public:
        Dossier(Universum &universum);
        virtual ~Dossier();

        QWidget *getParentWindow();

        void leegAanspreektitels();
        void toevoegenAanspreektitel(const QString &value);
        void leegArtsenLijst();
        void toevoegenArts(int id, const QString &naam, const QString &straat, const QString &gemeente);

        QString getAanspreektitel() const;
        QString getNaam() const;
        QString getVoornaam() const;
        QString getStraat() const;
        int getPostcode() const;
        QString getGemeente() const;
        QString getTelefoon() const;
        QDate getGeboorteDatum() const;
        int getMutualiteit() const;
        QString getAansluitingsnummer() const;
        QString getPlaatsAanpassing() const;
        QString getOpmerkingen() const;
        int getArts() const;
        QString getRechterHoorapparaatMerk() const;
        QString getRechterHoorapparaatType() const;
        QString geRechterHoorapparaatSerienummer() const;
        double getRechterHoorapparaatPrijs() const;
        QString getLinkerHoorapparaatMerk() const;
        QString getLinkerHoorapparaatType() const;
        QString getLinkerHoorapparaatSerienummer() const;
        double getLinkerHoorapparaatPrijs() const;

        void setAanspreektitel(const QString &value);
        void setNaam(const QString &value);
        void setVoornaam(const QString &value);
        void setStraat(const QString &value);
        void setPostcode(int value);
        void setGemeente(const QString &value);
        void setTelefoon(const QString &value);
        void setGeboorteDatum(const QDate &value);
        void setMutualiteit(int value);
        void setAansluitingsnummer(const QString &value);
        void setPlaatsAanpassing(const QString &value);
        void setOpmerkingen(const QString &value);
        void setArts(int value);
        void setRechterHoorapparaatMerk(const QString &value);
        void setRechterHoorapparaatType(const QString &value);
        void setRechterHoorapparaatSerienummer(const QString &value);
        void setRechterHoorapparaatPrijs(double value);
        void setLinkerHoorapparaatMerk(const QString &value);
        void setLinkerHoorapparaatType(const QString &value);
        void setLinkerHoorapparaatSerienummer(const QString &value);
        void setLinkerHoorapparaatPrijs(double value);

    public slots:
        void toonArts(int value);
        void toonBriefArts();
        void toonBriefKlant();
        void toonBriefMutualiteit();
        void toonFactuur();
        void toonMeetgegevens();
        void toonMutualiteit(int value);

    signals:
        void briefArtsTonen();
        void briefKlantTonen();
        void briefMutualiteitTonen();
        void factuurTonen();
        void meetgegevensTonen();

    private:
        Universum &m_universum;
        QMap<int, QString> m_artsIdToStraat;
        QMap<int, QString> m_artsIdToGemeente;
    };
}

#endif // _VIEW_DOSSIER_H
