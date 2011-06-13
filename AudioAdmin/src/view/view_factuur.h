#ifndef _VIEW_FACTUUR_H
#define _VIEW_FACTUUR_H

#include <QDialog>
#include "ui_factuur.h"

namespace View
{
    class Factuur : public QDialog, public Ui::Factuur
    {
    Q_OBJECT
    public:
        explicit Factuur(QWidget *parent = 0);
        virtual ~Factuur();

        void setAudioloogNaam(const QString &value);
        void setAudioloogStraat(const QString &value);
        void setAudioloogGemeente(const QString &value);
        void setAudioloogTelefoon(const QString &value);
        void setAudioloogGSM(const QString &value);
        void setKlantNaam(const QString &value);
        void setKlantStraat(const QString &value);
        void setKlantGemeente(const QString &value);
        void setNummer(const QString &value);
        void setDatum(const QDate &value);
        void setVervalDatum(const QDate &value);
        void setKortingPercentage(double value);
        void setBtwPercentage(double value);
        void setCondities(const QString &value);
        void setTekst(const QString &value);

        QString getNummer() const;
        QDate getDatum() const;
        QDate getVervalDatum() const;
        double getKortingPercentage() const;
        double getBtwPercentage() const;
        QString getCondities() const;
        QString getTekst() const;

    signals:
        void factuurSluiten();
        void factuurBewaren();

    private slots:
        void okFactuur();
        void annuleerFactuur();
    };
}

#endif // _VIEW_FACTUUR_H
