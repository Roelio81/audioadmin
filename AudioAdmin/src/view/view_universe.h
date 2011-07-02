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

        Physician &getPhysician();
        File &getFile();
        InsuranceCompany &getInsuranceCompany();
        Labels &getLabels();
        Settings &getSettings();

        void saveAtExit();
        void clearPhysicianList();
        void addPhysician(int id, const QString &name, const QString &straat, int postcode, const QString &gemeente);
        void changePhysician(int id, const QString &name, const QString &straat, int postcode, const QString &gemeente);
        void leegHoorapparatenLijst();
        void toevoegenHoorapparaat(const QString &merk, const QString &type, double prijs, const QDate &datumPrijs);
        void leegKlantenLijst();
        void addCustomer(int id, const QString &name, const QString &straat, int postcode, const QString &gemeente);
        void changeCustomer(int id, const QString &name, const QString &straat, int postcode, const QString &gemeente);
        void clearInsuranceCompanyList();
        void addInsuranceCompany(int id, const QString &name, const QString &straat, int postcode, const QString &gemeente);
        void changeInsuranceCompany(int id, const QString &name, const QString &straat, int postcode, const QString &gemeente);

        void setPhysicianListChanged(bool changed);
        void setFileListChanged(bool changed);
        void setInsuranceCompanyListChanged(bool changed);

        int artsIndexToId(int index) const;
        int artsIdToIndex(int id) const;
        int klantIndexToId(int index) const;
        int klantIdToIndex(int id) const;
        int mutualiteitIndexToId(int index) const;
        int mutualiteitIdToIndex(int id) const;

        QSet<QString> getMerkHoorapparaten() const;
        QSet<QString> getTypeHoorapparaten(const QString &merk) const;

        void selectPhysician(int id);
        void selectCustomer(int id);
        void selectInsuranceCompany(int id);
        void enableWidgetsForPhysician();
        void enableWidgetsForCustomer();
        void enableWidgetsForInsuranceCompany();

        // This method should disappear and be replaced with subpanels
        Ui::Universe &getUi() { return m_ui; }

    public slots:
        void cleanupTabFile(const QDate &invalidDate);
        void cleanupTabPhysician();
        void cleanupTabInsuranceCompany();

    private slots:
        void tabChanged(int newTab);
        void about();
        void selectPhysician(int currentRow, int currentColumn, int previousRow, int previousColumn);
        void selectCustomer(int currentRow, int currentColumn, int previousRow, int previousColumn);
        void selectInsuranceCompany(int currentRow, int currentColumn, int previousRow, int previousColumn);
        void addPhysician();
        void removePhysician();
        void findPhysician();
        void addFile();
        void removeFile();
        void findFile();
        void addInsuranceCompany();
        void removeInsuranceCompany();
        void findInsuranceCompany();
        void markTabChanged(int tabIndex, bool changed);

    signals:
        void exitSignal();
        void saveSignal();
        void openSettings();
        void artsSelectieSignal(int id);
        void artsVerwijderenSignal(int id);
        void artsToevoegenSignal(QString firstName, QString name);
        void klantSelectieSignal(int id);
        void klantVerwijderenSignal(int id);
        void klantToevoegenSignal(QString firstName, QString name);
        void mutualiteitSelectieSignal(int id);
        void mutualiteitVerwijderenSignal(int id);
        void mutualiteitToevoegenSignal(QString name);
        void openLabels();
        void closeFileTab();
        void closePhysicianTab();
        void closeInsuranceCompanyTab();
        void openDossierTab();
        void openArtsTab();
        void openMutualiteitTab();

    private:
        void closeEvent(QCloseEvent *event);

        // --- Type definitions ---
        typedef QPair<double, QDate> PriceDatePair;
        typedef QMap<QString, PriceDatePair> TypeToPriceMap;
        typedef QMap<QString, TypeToPriceMap> BrandToTypesAndPricesMap;

        // --- Data members ---
        Ui::Universe m_ui;
        BrandToTypesAndPricesMap m_hoorapparaatMerkToTypes;
        Physician m_physician;
        File m_file;
        InsuranceCompany m_insuranceCompany;
        Labels m_labels;
        Settings m_settings;
        int m_currentTab;
    };
}

#endif // _VIEW_UNIVERSE_H
