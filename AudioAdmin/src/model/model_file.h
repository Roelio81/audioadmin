#ifndef _MODEL_FILE_H
#define _MODEL_FILE_H

#include "model_letter.h"
#include "model_invoice.h"
#include "model_customer.h"
#include "model_measurements.h"

class QDomDocument;
class QDomElement;

namespace Model
{
    class Universe;

    class File
    {
    public:
        explicit File(int id, const Universe &Universe);
        virtual ~File();

        // --- ISerializable ---
        virtual void fromDomElement(const QDomElement &e);
        virtual QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        int getId() const { return m_id; }
        const Universe &getUniverse() const { return m_universe; }
        int getPhysician() const { return m_physician; }
        int getInsuranceCompany() const { return m_insuranceCompany; }
        QString getMemberNumber() const { return m_memberNumber; }
        QString getPlaceAdjustment() const { return m_placeAdjustment; }
        QString getRightHearingAidBrand() const { return m_rightHearingAidBrand; }
        QString getRightHearingAidType() const { return m_rightHearingAidType; }
        QString getRightHearingAidSerialNumber() const { return m_rightHearingAidSerialNumber; }
        double getRightHearingAidPrice() const { return m_rightHearingAidPrice; }
        QString getLeftHearingAidBrand() const { return m_leftHearingAidBrand; }
        QString getLeftHearingAidType() const { return m_leftHearingAidType; }
        QString getLeftHearingAidSerialNumber() const { return m_leftHearingAidSerialNumber; }
        double getLeftHearingAidPrice() const { return m_leftHearingAidPrice; }
        int getNofHearingAids() const;
        QDate getTestDate() const { return m_testDate; }
        QDate getTrialDate() const { return m_trialDate; }
        QDate getPhysicianReportDate() const { return m_physicianReportDate; }
        QDate getPhysicianAdviceDate() const { return m_physicianAdviceDate; }
        QDate getInsuranceAgreementDate() const { return m_insuranceAgreementDate; }
        QDate getPaymentDate() const { return m_paymentDate; }
        QDate getDeliveryDate() const { return m_deliveryDate; }
        QDate getExchangeDate() const { return m_exchangeDate; }
        QDate getMaintenanceContractDate() const { return m_maintenanceContractDate; }
        Letter &getLetterPhysician() { return m_letterPhysician; }
        const Letter &getLetterPhysician() const { return m_letterPhysician; }
        Letter &getLetterCustomer() { return m_letterCustomer; }
        const Letter &getLetterCustomer() const { return m_letterCustomer; }
        Letter &getLetterInsuranceCompany() { return m_letterInsuranceCompany; }
        const Letter &getLetterInsuranceCompany() const { return m_letterInsuranceCompany; }
        Invoice &getInvoice() { return m_invoice; }
        const Invoice &getInvoice() const { return m_invoice; }
        Customer &getCustomer() { return m_customer; }
        const Customer &getCustomer() const { return m_customer; }
        Measurements &getMeasurements() { return m_meetgegevens; }
        const Measurements &getMeasurements() const { return m_meetgegevens; }

        // --- Setters ---
        void setPhysician(int value) { m_physician = value; }
        void setInsuranceCompany(int value) { m_insuranceCompany = value; }
        void setMemberNumber(const QString &value) { m_memberNumber = value; }
        void setPlaceAdjustment(const QString &value) { m_placeAdjustment = value; }
        void setRightHearingAidBrand(const QString &value) { m_rightHearingAidBrand = value; }
        void setRightHearingAidType(const QString &value) { m_rightHearingAidType = value; }
        void setRightHearingAidSerialNumber(const QString &value) { m_rightHearingAidSerialNumber = value; }
        void setRightHearingAidPrice(double value) {m_rightHearingAidPrice = value; }
        void setLeftHearingAidBrand(const QString &value) { m_leftHearingAidBrand = value; }
        void setLeftHearingAidType(const QString &value) { m_leftHearingAidType = value; }
        void setLeftHearingAidSerialNumber(const QString &value) { m_leftHearingAidSerialNumber = value; }
        void setLeftHearingAidPrice(double value) { m_leftHearingAidPrice = value; }
        void setTestDate(const QDate &value) { m_testDate = value; }
        void setTrialDate(const QDate &value) { m_trialDate = value; }
        void setPhysicianReportDate(const QDate &value) { m_physicianReportDate = value; }
        void setPhysicianAdviceDate(const QDate &value) { m_physicianAdviceDate = value; }
        void setInsuranceAgreementDate(const QDate &value) { m_insuranceAgreementDate = value; }
        void setPaymentDate(const QDate &value) { m_paymentDate = value; }
        void setDeliveryDate(const QDate &value) { m_deliveryDate = value; }
        void setExchangeDate(const QDate &value) { m_exchangeDate = value; }
        void setMaintenanceContractDate(const QDate &value) { m_maintenanceContractDate = value; }

    private:
        // --- Data members ---
        const int m_id;
        const Universe &m_universe;
        int m_physician;
        int m_insuranceCompany;
        QString m_memberNumber;
        QString m_placeAdjustment;
        QString m_rightHearingAidBrand;
        QString m_rightHearingAidType;
        QString m_rightHearingAidSerialNumber;
        double m_rightHearingAidPrice;
        QString m_leftHearingAidBrand;
        QString m_leftHearingAidType;
        QString m_leftHearingAidSerialNumber;
        double m_leftHearingAidPrice;
        QDate m_testDate;
        QDate m_trialDate;
        QDate m_physicianReportDate;
        QDate m_physicianAdviceDate;
        QDate m_insuranceAgreementDate;
        QDate m_paymentDate;
        QDate m_deliveryDate;
        QDate m_exchangeDate;
        QDate m_maintenanceContractDate;
        Letter m_letterPhysician;
        Letter m_letterCustomer;
        Letter m_letterInsuranceCompany;
        Invoice m_invoice;
        Customer m_customer;
        Measurements m_meetgegevens;
    };
}

#endif // _MODEL_FILE_H
