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
        void addPhysician(int id, const QString &name, const QString &straat, int postcode, const QString &city);
        void changePhysician(int id, const QString &name, const QString &straat, int postcode, const QString &city);
        void clearHearingAidList();
        void addHearingAid(const QString &brand, const QString &type, double price, const QDate &datePrice);
        void clearCustomerList();
        void addCustomer(int id, const QString &name, const QString &straat, int postcode, const QString &city);
        void changeCustomer(int id, const QString &name, const QString &straat, int postcode, const QString &city);
        void clearInsuranceCompanyList();
        void addInsuranceCompany(int id, const QString &name, const QString &straat, int postcode, const QString &city);
        void changeInsuranceCompany(int id, const QString &name, const QString &straat, int postcode, const QString &city);

        void setPhysicianListChanged(bool changed);
        void setFileListChanged(bool changed);
        void setInsuranceCompanyListChanged(bool changed);

        int physicianIndexToId(int index) const;
        int physicianIdToIndex(int id) const;
        int customerIndexToId(int index) const;
        int customerIdToIndex(int id) const;
        int insuranceCompanyIndexToId(int index) const;
        int insuranceCompanyIdToIndex(int id) const;

        QSet<QString> getHearingAidBrands() const;
        QSet<QString> getHearingAidTypes(const QString &brand) const;

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
        BrandToTypesAndPricesMap m_hearingAidBrandToTypes;
        Physician m_physician;
        File m_file;
        InsuranceCompany m_insuranceCompany;
        Labels m_labels;
        Settings m_settings;
        int m_currentTab;
    };
}

#endif // _VIEW_UNIVERSE_H
