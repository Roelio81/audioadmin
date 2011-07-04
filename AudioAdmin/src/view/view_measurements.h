#ifndef _VIEW_MEASUREMENTS_H
#define _VIEW_MEASUREMENTS_H

#include <QDialog>
#include "ui_measurements.h"

namespace View
{
    class Measurements : public QDialog
    {
    Q_OBJECT
    public:
        explicit Measurements(QWidget *parent = 0);
        virtual ~Measurements();

        // --- Getters ---
        int getACRightData(int Hz) const;
        int getBCRightData(int Hz) const;
        int getUCLRightData(int Hz) const;
        int getACLeftData(int Hz) const;
        int getBCLeftData(int Hz) const;
        int getUCLLeftData(int Hz) const;
        int getREWithoutData(int dB) const;
        int getLEWithoutData(int dB) const;
        int getRELEWithoutData(int dB) const;
        int getREWithData(int dB) const;
        int getLEWithData(int dB) const;
        int getRELEWithData(int dB) const;
        int getLocalizationWithout() const;
        int getLocalizationRight() const;
        int getLocalizationLeft() const;
        int getLocalizationBoth() const;
        QPixmap getTonaleLinks() const;
        QPixmap getTonaleRechts() const;
        QPixmap getVocaleZonderApparaat() const;
        QPixmap getVocaleMetApparaat() const;
        QString getROZonder() const;
        QString getLOZonder() const;
        QString getROLOZonder() const;
        QString getROMet() const;
        QString getLOMet() const;
        QString getROLOMet() const;
        QString getROWinst() const;
        QString getLOWinst() const;
        QString getROLOWinst() const;


        // --- Setters ---
        void setLGRechtsData(int Hz, int dB);
        void setBGRechtsData(int Hz, int dB);
        void setUCLRechtsData(int Hz, int dB);
        void setLGLinksData(int Hz, int dB);
        void setBGLinksData(int Hz, int dB);
        void setUCLLinksData(int Hz, int dB);
        void setROZonderData(int dB, int percentage);
        void setLOZonderData(int dB, int percentage);
        void setROLOZonderData(int dB, int percentage);
        void setROMetData(int dB, int percentage);
        void setLOMetData(int dB, int percentage);
        void setROLOMetData(int dB, int percentage);
        void setLocalisatieZonder(int dB);
        void setLocalisatieRechts(int dB);
        void setLocalisatieLinks(int dB);
        void setLocalisatieBeide(int dB);

    private slots:
        void herberekenGemiddeldVerliesLinks();
        void herberekenGemiddeldVerliesRechts();
        void herberekenROZonder();
        void herberekenLOZonder();
        void herberekenROLOZonder();
        void herberekenROMet();
        void herberekenLOMet();
        void herberekenROLOMet();

    private:
        void herberekenROWinst();
        void herberekenLOWinst();
        void herberekenROLOWinst();

        // --- Data members ---
        Ui::Measurements m_ui;
    };
}

#endif // _VIEW_MEASUREMENTS_H
