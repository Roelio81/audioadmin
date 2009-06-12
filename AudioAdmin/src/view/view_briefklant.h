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
        void setAanspreking(const QString &value);
        void setPostdatum(const QString &value);
        void setTekst(const QString &value);

        QString getPostdatum() const;
        QString getTekst() const;

    signals:
        void briefKlantSluiten();
        void briefKlantBewaren();

    private slots:
        void sluitBriefKlant();
        void bewaarBriefKlant();
    };
}

#endif // _VIEW_BRIEFKLANT_H
