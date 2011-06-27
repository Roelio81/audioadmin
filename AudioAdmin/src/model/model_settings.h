#ifndef _MODEL_INSTELLINGEN_H
#define _MODEL_INSTELLINGEN_H

#include <QString>

class QDomDocument;
class QDomElement;

namespace Model
{
    class Universe;

    class Settings
    {
    public:
        explicit Settings(const Universe &universum);
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
        QString getOnderschrift() const { return m_onderschrift; }
        QString getRiziv() const { return m_riziv; }
        int getVATPercentage() const { return m_btwPercentage; }
        QString getBtwNummer() const { return m_btwNummer; }
        QString getRekeningNummer() const { return m_rekeningNummer; }

        // --- Setters ---
        void setName(const QString &value) { m_name = value; }
        void setStreet(const QString &value) { m_street = value; }
        void setPostalCode(int value) { m_postalCode = value; }
        void setCity(const QString &value) { m_city = value; }
        void setTelephone(const QString &value) { m_telephone = value; }
        void setMobilePhone(const QString &value) { m_mobilePhone = value; }
        void setEmail(const QString &value) { m_email = value; }
        void setOnderschrift(const QString &value) { m_onderschrift = value; }
        void setRiziv(const QString &value) { m_riziv = value; }
        void setBtwPercentage(int value) { m_btwPercentage = value; }
        void setBtwNummer(const QString &value) { m_btwNummer = value; }
        void setRekeningNummer(const QString &value) { m_rekeningNummer = value; }

    private:
        // --- Data members ---
        const Universe &m_universum;
        QString m_name;
        QString m_street;
        int m_postalCode;
        QString m_city;
        QString m_telephone;
        QString m_mobilePhone;
        QString m_email;
        QString m_onderschrift;
        QString m_riziv;
        int m_btwPercentage;
        QString m_btwNummer;
        QString m_rekeningNummer;
    };
}

#endif // _MODEL_INSTELLINGEN_H
