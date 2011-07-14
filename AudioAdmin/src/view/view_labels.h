#ifndef _VIEW_LABELS_H
#define _VIEW_LABELS_H

#include "ui_labels.h"
#include <QDate>
#include <QDialog>
#include <QStringList>

namespace View
{
    class Labels : public QDialog
    {
    Q_OBJECT
    public:
        explicit Labels(QWidget *parent = 0);
        virtual ~Labels();

        // --- Getters ---
        QString getPlaceAdjustment() const;
        QDate getTestDate() const;
        bool isAdjustmentPlaceChecked() const;
        bool isTestDateChecked() const;

        // --- Setters ---
        void clearPlacesAdjustment();
        void addPlaceAdjustment(const QString &value);
        void setTestDate(const QDate &value);

    private:
        // --- Data members ---
        QStringList m_placesAdjustment;
        Ui::Labels m_ui;
    };
}

#endif // _VIEW_LABELS_H
