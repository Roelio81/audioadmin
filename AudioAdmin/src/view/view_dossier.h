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
        void wijzigenArts(int id, const QString &naam, const QString &straat, const QString &gemeente);
        void toevoegenMutualiteit(int id, const QString &naam);
        void wijzigenMutualiteit(int id, const QString &naam);

        QString getAanspreektitel() const;
        QString getNaam() const;
        QString getVoornaam() const;
        QString getStraat() const;
        int getPostcode() const;
        QString getGemeente() const;
        QString getTelefoon() const;
        QDate *getGeboorteDatum() const;
        int getMutualiteit() const;
        QString getAansluitingsnummer() const;
        QString getPlaatsAanpassing() const;
        QString getOpmerkingen() const;
        int getArts() const;
        QString getRechterHoorapparaatMerk() const;
        QString getRechterHoorapparaatType() const;
        QString getRechterHoorapparaatSerienummer() const;
        double getRechterHoorapparaatPrijs() const;
        QString getLinkerHoorapparaatMerk() const;
        QString getLinkerHoorapparaatType() const;
        QString getLinkerHoorapparaatSerienummer() const;
        double getLinkerHoorapparaatPrijs() const;
        QDate *getOnderzoekDatum() const;
        QDate *getProefDatum() const;
        QDate *getNKORapportDatum() const;
        QDate *getDokterAdviesDatum() const;
        QDate *getAkkoordMutualiteitDatum() const;
        QDate *getBetalingDatum() const;
        QDate *getAfleveringDatum() const;
        QDate *getWisselDatum() const;
        QDate *getOHKDatum() const;

        void setAanspreektitel(const QString &value);
        void setNaam(const QString &value);
        void setVoornaam(const QString &value);
        void setStraat(const QString &value);
        void setPostcode(int value);
        void setGemeente(const QString &value);
        void setTelefoon(const QString &value);
        void setGeboorteDatum(QDate *value);
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
        void setOnderzoekDatum(QDate *value);
        void setProefDatum(QDate *value);
        void setNKORapportDatum(QDate *value);
        void setDokterAdviesDatum(QDate *value);
        void setAkkoordMutualiteitDatum(QDate *value);
        void setBetalingDatum(QDate *value);
        void setAfleveringDatum(QDate *value);
        void setWisselDatum(QDate *value);
        void setOHKDatum(QDate *value);

    public slots:
        void toonArts(int value);
        void toonBriefArts();
        void toonBriefKlant();
        void toonBriefMutualiteit();
        void toonFactuur();
        void toonMeetgegevens();
        void toonMutualiteit(int value);
        void refreshRechterHoorapparaatLijst(int indexMerk);
        void refreshLinkerHoorapparaatLijst(int indexMerk);

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
