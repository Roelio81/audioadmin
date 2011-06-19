#ifndef _VIEW_ETIKETTEN_H
#define _VIEW_ETIKETTEN_H

#include "ui_etiketten.h"
#include <QDate>
#include <QDialog>
#include <QStringList>

namespace View
{
    class Etiketten : public QDialog, public Ui::Etiketten
    {
    Q_OBJECT
    public:
        explicit Etiketten(QWidget *parent = 0);
        virtual ~Etiketten();

        void leegPlaatsenAanpassing();
        void toevoegenPlaatsAanpassing(const QString &value);
        void setDatumOnderzoek(const QDate &value);
        void afdrukken();

    private:
        // --- Data members ---
        QStringList m_plaatsenAanpassing;
    };
}

#endif // _VIEW_ETIKETTEN_H
