#ifndef _VIEW_TOEVOEGENMUTUALITEIT_H
#define _VIEW_TOEVOEGENMUTUALITEIT_H

#include <QDialog>
#include "ui_toevoegenmutualiteit.h"

namespace View
{
    class ToevoegenMutualiteit : public QDialog, public Ui::ToevoegenMutualiteit
    {
    Q_OBJECT
    public:
        explicit ToevoegenMutualiteit(QWidget *parent = 0);
        virtual ~ToevoegenMutualiteit();

        // --- Getters ---
        QString getNaam() const;
    };
}

#endif // _VIEW_TOEVOEGENMUTUALITEIT_H
