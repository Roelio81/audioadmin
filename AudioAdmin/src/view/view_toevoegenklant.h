#ifndef _VIEW_TOEVOEGENKLANT_H
#define _VIEW_TOEVOEGENKLANT_H

#include <QDialog>
#include "ui_toevoegenklant.h"

namespace View
{
    class ToevoegenKlant : public QDialog, public Ui::ToevoegenKlant
    {
    Q_OBJECT
    public:
        ToevoegenKlant(QWidget *parent = 0);
        virtual ~ToevoegenKlant();

        QString getVoornaam() const;
        QString getNaam() const;
    };
}

#endif // _VIEW_TOEVOEGENKLANT_H
