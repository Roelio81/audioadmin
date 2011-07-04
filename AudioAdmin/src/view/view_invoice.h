#ifndef _VIEW_INVOICE_H
#define _VIEW_INVOICE_H

#include <QDialog>
#include "ui_invoice.h"

namespace View
{
    class Invoice : public QDialog
    {
    Q_OBJECT
    public:
        explicit Invoice(QWidget *parent = 0);
        virtual ~Invoice();

        // --- Getters ---
        QString getNumber() const;
        QDate getDate() const;
        QDate getExpirationDate() const;
        double getReductionPercentage() const;
        double getVATPercentage() const;
        QString getConditions() const;
        QString getText() const;

        // --- Setters ---
        void setName(const QString &value);
        void setStreet(const QString &value);
        void setCity(const QString &value);
        void setTelephone(const QString &value);
        void setMobilePhone(const QString &value);
        void setCustomerName(const QString &value);
        void setCustomerStreet(const QString &value);
        void setCustomerCity(const QString &value);
        void setNumber(const QString &value);
        void setDate(const QDate &value);
        void setExpirationDate(const QDate &value);
        void setReductionPercentage(double value);
        void setVATPercentage(double value);
        void setConditions(const QString &value);
        void setText(const QString &value);

    private:
        // --- Data members ---
        Ui::Invoice m_ui;
    };
}

#endif // _VIEW_INVOICE_H
