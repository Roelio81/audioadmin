#ifndef _MODEL_SETTINGS_H
#define _MODEL_SETTINGS_H

#include <QString>

class QDomDocument;
class QDomElement;

namespace Model
{
    class Settings
    {
    public:
        explicit Settings();
        virtual ~Settings();

        // --- ISerializable ---
        virtual void fromDomElement(const QDomElement &e);
        virtual QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        QString getName() const { return m_name; }
        QString getStreet() const { return m_street; }
        int getPostalCode() const { return m_postalCode; }
        QString getCity() const { return m_city; }
        QString getTelephone() const { return m_telephone; }
        QString getMobilePhone() const { return m_mobilePhone; }
        QString getEmail() const { return m_email; }
        QString getCaption() const { return m_caption; }
        QString getNationalId() const { return m_nationalId; }
        int getVATPercentage() const { return m_vatPercentage; }
        QString getVATNumber() const { return m_vatNumber; }
        QString getBankAccount() const { return m_bankAccount; }

        // --- Setters ---
        void setName(const QString &value) { m_name = value; }
        void setStreet(const QString &value) { m_street = value; }
        void setPostalCode(int value) { m_postalCode = value; }
        void setCity(const QString &value) { m_city = value; }
        void setTelephone(const QString &value) { m_telephone = value; }
        void setMobilePhone(const QString &value) { m_mobilePhone = value; }
        void setEmail(const QString &value) { m_email = value; }
        void setCaption(const QString &value) { m_caption = value; }
        void setNationalId(const QString &value) { m_nationalId = value; }
        void setVATPercentage(int value) { m_vatPercentage = value; }
        void setVATNumber(const QString &value) { m_vatNumber = value; }
        void setBankAccount(const QString &value) { m_bankAccount = value; }

    private:
        // --- Data members ---
        QString m_name;
        QString m_street;
        int m_postalCode;
        QString m_city;
        QString m_telephone;
        QString m_mobilePhone;
        QString m_email;
        QString m_caption;
        QString m_nationalId;
        int m_vatPercentage;
        QString m_vatNumber;
        QString m_bankAccount;
    };
}

#endif // _MODEL_SETTINGS_H
