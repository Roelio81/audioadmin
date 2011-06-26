#ifndef _VIEW_ADDDIALOG_H
#define _VIEW_ADDDIALOG_H

#include <QDialog>
#include "ui_adddialog.h"

namespace View
{
    class AddDialog : public QDialog
    {
    Q_OBJECT
    public:
        explicit AddDialog(bool showFirstName, QWidget *parent = 0);
        virtual ~AddDialog();

        // --- Getters ---
        QString getFirstName() const;
        QString getName() const;

    private:
        // --- Data members ---
        Ui::AddDialog m_ui;
    };
}

#endif // _VIEW_ADDDIALOG_H
