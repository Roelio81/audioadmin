#ifndef _VIEW_LETTER_H
#define _VIEW_LETTER_H

#include <QDialog>
#include "ui_letter.h"

namespace View
{
    class Letter : public QDialog
    {
    Q_OBJECT
    public:
        explicit Letter(bool showConclusion, QWidget *parent = 0);
        virtual ~Letter();

        // --- Getters ---
        QString getPostalDate() const;
        QString getText() const;
        QString getConclusion() const;

        // --- Setters ---
        void setSenderName(const QString &value);
        void setSenderStreet(const QString &value);
        void setSenderCity(const QString &value);
        void setSenderTelephone(const QString &value);
        void setSenderMobilePhone(const QString &value);
        void setAddresseeName(const QString &value);
        void setAddresseeStreet(const QString &value);
        void setAddresseeCity(const QString &value);
        void setPostalDate(const QString &value);
        void setGreeting(const QString &value);
        void setText(const QString &value);
        void setConclusion(const QString &value);

    signals:
        void print();

    private:
        // --- Data members ---
        Ui::Letter m_ui;
    };
}

#endif // _VIEW_LETTER_H
