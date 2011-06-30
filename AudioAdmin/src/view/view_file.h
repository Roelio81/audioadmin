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

        void clearTitles();
        void addTitle(const QString &value);
        void clearPhysicianList();
        void addPhysician(int id, const QString &naam, const QString &straat, const QString &gemeente);
        void changePhysician(int id, const QString &naam, const QString &straat, const QString &gemeente);
        void clearInsuranceCompanyList();
        void addInsuranceCompany(int id, const QString &naam);
        void changeInsruanceCompany(int id, const QString &naam);

        // --- Getters ---
        QString getTitle() const;
        QString getName() const;
        QString getFirstName() const;
        QString getStreet() const;
        int getPostalCode() const;
        QString getCity() const;
        QString getTelephone() const;
        QDate getDateOfBirth() const;
        int getInsuranceCompany() const;
        QString getMemberNumber() const;
        QString getPlaceAdjustment() const;
        QString getComments() const;
        int getPhysician() const;
        QString getRightHearingAidBrand() const;
        QString getRightHearingAidType() const;
        QString getRightHearingAidSerialNumber() const;
        double getRightHearingAidPrice() const;
        QString getLeftHearingAidBrand() const;
        QString getLeftHearingAidType() const;
        QString getLeftHearingAidSerialNumber() const;
        double getLeftHearingAidPrice() const;
        QDate getTestDate() const;
        QDate getTrialDate() const;
        QDate getPhysicianReportDate() const;
        QDate getPhysicianAdviceDate() const;
        QDate getInsuranceAgreementDate() const;
        QDate getPaymentDate() const;
        QDate getDeliveryDate() const;
        QDate getExchangeDate() const;
        QDate getMaintenanceContractDate() const;

        // --- Setters ---
        void setTitle(const QString &value);
        void setName(const QString &value);
        void setFirstName(const QString &value);
        void setStreet(const QString &value);
        void setPostalCode(int value);
        void setCity(const QString &value);
        void setTelephone(const QString &value);
        void setDateOfBirth(const QDate &value);
        void setInsuranceCompany(int value);
        void setMemberNumber(const QString &value);
        void setPlaceAdjustment(const QString &value);
        void setComments(const QString &value);
        void setPhysician(int value);
        void setRightHearingAidBrand(const QString &value);
        void setRightHearingAidType(const QString &value);
        void setRightHearingAidSerialNumber(const QString &value);
        void setRightHearingAidPrice(double value);
        void setLeftHearingAidBrand(const QString &value);
        void setLeftHearingAidType(const QString &value);
        void setLeftHearingAidSerialNumber(const QString &value);
        void setLeftHearingAidPrice(double value);
        void setTestDate(const QDate &value);
        void setTrialDate(const QDate &value);
        void setPhysicianReportDate(const QDate &value);
        void setPhysicianAdviceDate(const QDate &value);
        void setInsuranceAgreementDate(const QDate &value);
        void setPaymentDate(const QDate &value);
        void setDeliveryDate(const QDate &value);
        void setExchangeDate(const QDate &value);
        void setMaintenanceContractDate(const QDate &value);

    public slots:
        void showPhysician(int value);
        void showInsuranceCompany(int value);
        void refreshRechterHoorapparaatLijst(int indexMerk);
        void refreshLinkerHoorapparaatLijst(int indexMerk);

    signals:
        void showLetterCustomer();
        void showLetterPhysician();
        void showLetterInsuranceCompany();
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
