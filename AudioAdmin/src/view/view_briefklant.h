#ifndef _VIEW_BRIEFKLANT_H
#define _VIEW_BRIEFKLANT_H

#include <QDialog>
#include "ui_briefklant.h"

namespace View
{
    class BriefKlant : public QDialog, public Ui::BriefKlant
    {
    Q_OBJECT
    public:
        BriefKlant(QWidget *parent = 0);
        virtual ~BriefKlant();

        void setAudioloogNaam(const QString &value);
        void setAudioloogStraat(const QString &value);
        void setAudioloogGemeente(const QString &value);
        void setAudioloogTelefoon(const QString &value);
        void setAudioloogGSM(const QString &value);
        void setKlantNaam(const QString &value);
        void setKlantStraat(const QString &value);
        void setKlantGemeente(const QString &value);

    signals:
        void briefKlantSluiten();

    private slots:
        void sluitBriefKlant();
    };
}

#endif // _VIEW_BRIEFKLANT_H
