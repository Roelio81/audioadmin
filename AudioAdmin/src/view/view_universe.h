#ifndef _VIEW_UNIVERSE_H
#define _VIEW_UNIVERSE_H

#include "ui_universe.h"
#include "view_physician.h"
#include "view_file.h"
#include "view_insurancecompany.h"
#include "view_labels.h"
#include "view_settings.h"

#include <QMainWindow>
#include <QMap>
#include <QSet>

namespace View
{
    class Universe : public QMainWindow
    {
    Q_OBJECT
    public:
        explicit Universe(QWidget *parent = 0, Qt::WFlags f = 0);
        virtual ~Universe();

        Physician &getArts();
        File &getDossier();
        InsuranceCompany &getMutualiteit();
        Etiketten &getEtiketten();
        Instellingen &getInstellingen();

        void bewarenBijAfsluiten();
        void markeerArtsenLijstStatus(bool wijzigingen);
        void leegArtsenLijst();
        void toevoegenArts(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente);
        void wijzigenArts(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente);
        void leegHoorapparatenLijst();
        void toevoegenHoorapparaat(const QString &merk, const QString &type, double prijs, const QDate &datumPrijs);
        void markeerKlantenLijstStatus(bool wijzigingen);
        void leegKlantenLijst();
        void toevoegenKlant(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente);
        void wijzigenKlant(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente);
        void markeerMutualiteitenLijstStatus(bool wijzigingen);
        void leegMutualiteitenLijst();
        void toevoegenMutualiteit(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente);
        void wijzigenMutualiteit(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente);

        int artsIndexToId(int index) const;
        int artsIdToIndex(int id) const;
        int klantIndexToId(int index) const;
        int klantIdToIndex(int id) const;
        int mutualiteitIndexToId(int index) const;
        int mutualiteitIdToIndex(int id) const;

        QSet<QString> getMerkHoorapparaten() const;
        QSet<QString> getTypeHoorapparaten(const QString &merk) const;

        void selecteerArts(int id);
        void selecteerKlant(int id);
        void selecteerMutualiteit(int id);

        // This method should disappear and be replaced with subpanels
        Ui::Universe &getUi() { return m_ui; }

    public slots:
        void cleanupTabFile(const QDate &invalidDate);
        void cleanupTabPhysician();
        void cleanupTabInsuranceCompany();

    private slots:
        void tabVeranderd(int nieuweTab);
        void instellingen();
        void bewaren();
        void etikettenAfdrukken();
        void omtrent();
        void selecteerArts(int currentRow, int currentColumn, int previousRow, int previousColumn);
        void selecteerKlant(int currentRow, int currentColumn, int previousRow, int previousColumn);
        void selecteerMutualiteit(int currentRow, int currentColumn, int previousRow, int previousColumn);
        void toevoegenArts();
        void verwijderenArts();
        void zoekenArts();
        void toevoegenDossier();
        void verwijderenDossier();
        void zoekenDossier();
        void toevoegenMutualiteit();
        void verwijderenMutualiteit();
        void zoekenMutualiteit();

    signals:
        void afsluitenSignal();
        void bewarenSignal();
        void instellingenSignal();
        void artsSelectieSignal(int id);
        void artsVerwijderenSignal(int id);
        void artsToevoegenSignal(QString voornaam, QString naam);
        void klantSelectieSignal(int id);
        void klantVerwijderenSignal(int id);
        void klantToevoegenSignal(QString voornaam, QString naam);
        void mutualiteitSelectieSignal(int id);
        void mutualiteitVerwijderenSignal(int id);
        void mutualiteitToevoegenSignal(QString naam);
        void etikettenSignal();
        void sluitDossierTab();
        void sluitArtsTab();
        void sluitMutualiteitTab();
        void openDossierTab();
        void openArtsTab();
        void openMutualiteitTab();

    private:
        void closeEvent(QCloseEvent *event);

        // --- Type definitions ---
        typedef QPair<double, QDate> PrijsDatumInfo;
        typedef QMap<QString, PrijsDatumInfo> HaarApparaatTypeMap;
        typedef QMap<QString, HaarApparaatTypeMap> HoorApparaatMap;

        // --- Data members ---
        Ui::Universe m_ui;
        HoorApparaatMap m_hoorapparaatMerkToTypes;
        Physician m_arts;
        File m_dossier;
        InsuranceCompany m_mutualiteit;
        Etiketten m_etiketten;
        Instellingen m_instellingen;
        int m_huidigeTab;
    };
}

#endif // _VIEW_UNIVERSUM_H
