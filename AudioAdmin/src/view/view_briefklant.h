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

    signals:
        void briefKlantSluiten();

    private slots:
        void sluitBriefKlant();
    };
}

#endif // _VIEW_BRIEFKLANT_H
