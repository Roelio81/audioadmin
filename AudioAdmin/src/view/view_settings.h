#ifndef _VIEW_SETTINGS_H
#define _VIEW_SETTINGS_H

#include <QDialog>
#include <QString>
#include "ui_settings.h"

namespace View
{
    class Settings : public QDialog
    {
    Q_OBJECT
    public:
        explicit Settings(QWidget *parent = 0);
        virtual ~Settings();

        // --- Getters ---
        QString getName() const;
        QString getStreet() const;
        int getPostalCode() const;
        QString getCity() const;
        QString getTelephone() const;
        QString getMobilePhone() const;
        QString getEmail() const;
        QString getCaption() const;
        QString getNationalId() const;
        int getVATPercentage() const;
        QString getVATNumber() const;
        QString getBankAccount() const;

        // --- Setters ---
        void setName(const QString &value);
        void setStreet(const QString &value);
        void setPostalCode(const int &value);
        void setCity(const QString &value);
        void setTelephone(const QString &value);
        void setMobilePhone(const QString &value);
        void setEmail(const QString &value);
        void setCaption(const QString &value);
        void setNationalId(const QString &value);
        void setVATPercentage(const int &value);
        void setVATNumber(const QString &value);
        void setBankAccount(const QString &value);

    private:
        // --- Data members ---
        Ui::Settings m_ui;
    };
}

#endif // _VIEW_SETTINGS_H
