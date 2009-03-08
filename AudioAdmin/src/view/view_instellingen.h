#ifndef _VIEW_INSTELLINGEN_H
#define _VIEW_INSTELLINGEN_H

#include <QDialog>
#include <QString>
#include "ui_instellingen.h"

namespace View
{
    class Instellingen : public QDialog, public Ui::Instellingen
    {
    Q_OBJECT
    public:
        Instellingen(QWidget *parent = 0);
        virtual ~Instellingen();

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
        QString getBtwNummer() const;
        QString getRekeningNummer() const;

        void setNaam(const QString &value);
        void setStraat(const QString &value);
        void setPostcode(const int &value);
        void setGemeente(const QString &value);
        void setTelefoon(const QString &value);
        void setGsm(const QString &value);
        void setEmail(const QString &value);
        void setOnderschrift(const QString &value);
        void setRiziv(const QString &value);
        void setBtwPercentage(const int &value);
        void setBtwNummer(const QString &value);
        void setRekeningNummer(const QString &value);
    };
}

#endif // _VIEW_INSTELLINGEN_H
