#ifndef _VIEW_FILE_H
#define _VIEW_FILE_H

#include <QStandardItemModel>
#include <QMap>
#include <QObject>
#include <QDate>

namespace Ui
{
    class Universe;
}

namespace View
{
    class Universe;

    class File : public QObject
    {
    Q_OBJECT
    public:
        explicit File(Universe &universe);
        virtual ~File();

        QWidget *getParentWindow();

        void leegAanspreektitels();
        void toevoegenAanspreektitel(const QString &value);
        void clearPhysicianList();
        void addPhysician(int id, const QString &naam, const QString &straat, const QString &gemeente);
        void changePhysician(int id, const QString &naam, const QString &straat, const QString &gemeente);
        void clearInsuranceCompanyList();
        void addInsuranceCompany(int id, const QString &naam);
        void changeInsruanceCompany(int id, const QString &naam);

        // --- Getters ---
        QString getAanspreektitel() const;
        QString getNaam() const;
        QString getVoornaam() const;
        QString getStraat() const;
        int getPostcode() const;
        QString getGemeente() const;
        QString getTelefoon() const;
        QDate getGeboorteDatum() const;
        int getInsuranceCompany() const;
        QString getAansluitingsnummer() const;
        QString getPlaatsAanpassing() const;
        QString getComments() const;
        int getPhysician() const;
        QString getRechterHoorapparaatMerk() const;
        QString getRechterHoorapparaatType() const;
        QString getRechterHoorapparaatSerienummer() const;
        double getRechterHoorapparaatPrijs() const;
        QString getLinkerHoorapparaatMerk() const;
        QString getLinkerHoorapparaatType() const;
        QString getLinkerHoorapparaatSerienummer() const;
        double getLinkerHoorapparaatPrijs() const;
        QDate getOnderzoekDatum() const;
        QDate getProefDatum() const;
        QDate getNKORapportDatum() const;
        QDate getDokterAdviesDatum() const;
        QDate getAkkoordMutualiteitDatum() const;
        QDate getBetalingDatum() const;
        QDate getAfleveringDatum() const;
        QDate getWisselDatum() const;
        QDate getOnderhoudsContractDatum() const;

        // --- Setters ---
        void setAanspreektitel(const QString &value);
        void setNaam(const QString &value);
        void setVoornaam(const QString &value);
        void setStraat(const QString &value);
        void setPostcode(int value);
        void setGemeente(const QString &value);
        void setTelefoon(const QString &value);
        void setGeboorteDatum(const QDate &value);
        void setInsuranceCompany(int value);
        void setAansluitingsnummer(const QString &value);
        void setPlaatsAanpassing(const QString &value);
        void setOpmerkingen(const QString &value);
        void setPhysician(int value);
        void setRechterHoorapparaatMerk(const QString &value);
        void setRechterHoorapparaatType(const QString &value);
        void setRechterHoorapparaatSerienummer(const QString &value);
        void setRechterHoorapparaatPrijs(double value);
        void setLinkerHoorapparaatMerk(const QString &value);
        void setLinkerHoorapparaatType(const QString &value);
        void setLinkerHoorapparaatSerienummer(const QString &value);
        void setLinkerHoorapparaatPrijs(double value);
        void setOnderzoekDatum(const QDate &value);
        void setProefDatum(const QDate &value);
        void setNKORapportDatum(const QDate &value);
        void setDokterAdviesDatum(const QDate &value);
        void setAkkoordMutualiteitDatum(const QDate &value);
        void setBetalingDatum(const QDate &value);
        void setAfleveringDatum(const QDate &value);
        void setWisselDatum(const QDate &value);
        void setOnderhoudsContractDatum(const QDate &value);

    public slots:
        void showPhysician(int value);
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
        void showInvoice();
        void showMeasurements();

    private:
        // --- Data members ---
        Universe &m_universe;
        Ui::Universe &m_ui;
        QStandardItemModel m_physicianList;
        QStandardItemModel m_insuranceCompanyList;
    };
}

#endif // _VIEW_FILE_H
