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
        QPixmap getPureToneAudiometryRight() const;
        QPixmap getPureToneAudiometryLeft() const;
        QPixmap getSpeechAudiometryWithoutAid() const;
        QPixmap getSpeechAudiometryWithAid() const;
        QString getAverageLossRight() const;
        QString getAverageLossLeft() const;
        QString getREWithout() const;
        QString getLEWithout() const;
        QString getRELEWithout() const;
        QString getREWith() const;
        QString getLEWith() const;
        QString getRELEWith() const;
        QString getREGain() const;
        QString getLEGain() const;
        QString getRELEGain() const;


        // --- Setters ---
        void setACRightData(int Hz, int dB);
        void setBCRightData(int Hz, int dB);
        void setUCLRightData(int Hz, int dB);
        void setACLeftData(int Hz, int dB);
        void setBCLeftData(int Hz, int dB);
        void setUCLLeftData(int Hz, int dB);
        void setREWithoutData(int dB, int percentage);
        void setLEWithoutData(int dB, int percentage);
        void setRELEWithoutData(int dB, int percentage);
        void setROWithData(int dB, int percentage);
        void setLOWithData(int dB, int percentage);
        void setROLOWithData(int dB, int percentage);
        void setLocalizationWithout(int dB);
        void setLocalizationWithRight(int dB);
        void setLocalizationWithLeft(int dB);
        void setLocalizationWithBoth(int dB);

    private slots:
        void recalculateAverageLossRight();
        void recalculateAverageLossLeft();
        void recalculateREWithoutAid();
        void recalculateLEWithoutAid();
        void recalculateRELEWithoutAid();
        void recalculateREWithAid();
        void recalculateLEWithAid();
        void recalculateRELEWithAid();

    private:
        void recalculateREGain();
        void recalculateLEGain();
        void recalculateRELEGain();

        // --- Data members ---
        Ui::Measurements m_ui;
    };
}

#endif // _VIEW_MEASUREMENTS_H
