#ifndef _VIEW_INSTELLINGEN_H
#define _VIEW_INSTELLINGEN_H

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
        QString getNaam() const;
        QString getStraat() const;
        int getPostcode() const;
        QString getGemeente() const;
        QString getTelefoon() const;
        QString getGsm() const;
        QString getEmail() const;
        QString getOnderschrift() const;
        QString getRiziv() const;
        int getBtwPercentage() const;
        QString getVATNumber() const;
        QString getRekeningNummer() const;

        // --- Setters ---
        void setName(const QString &value);
        void setStreet(const QString &value);
        void setPostalCode(const int &value);
        void setCity(const QString &value);
        void setTelephone(const QString &value);
        void setMobilePhone(const QString &value);
        void setEmail(const QString &value);
        void setOnderschrift(const QString &value);
        void setRiziv(const QString &value);
        void setVATPercentage(const int &value);
        void setVATNumber(const QString &value);
        void setRekeningNummer(const QString &value);

    private:
        // --- Data members ---
        Ui::Settings m_ui;
    };
}

#endif // _VIEW_INSTELLINGEN_H
