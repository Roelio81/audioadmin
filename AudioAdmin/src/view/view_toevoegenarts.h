#ifndef _VIEW_TOEVOEGENARTS_H
#define _VIEW_TOEVOEGENARTS_H

#include <QDialog>
#include "ui_toevoegenarts.h"

namespace View
{
    class ToevoegenArts : public QDialog, public Ui::ToevoegenArts
    {
    Q_OBJECT
    public:
        ToevoegenArts(QWidget *parent = 0);
        virtual ~ToevoegenArts();

        QString getVoornaam() const;
        QString getNaam() const;
    };
}

#endif // _VIEW_TOEVOEGENARTS_H
