#ifndef _VIEW_MEETGEGEVENS_H
#define _VIEW_MEETGEGEVENS_H

#include <QDialog>
#include "ui_meetgegevens.h"

namespace View
{
    class Meetgegevens : public QDialog, public Ui::Meetgegevens
    {
    Q_OBJECT
    public:
        explicit Meetgegevens(QWidget *parent = 0);
        virtual ~Meetgegevens();

        // --- Getters ---
        int getLGRechtsData(int Hz) const;
        int getBGRechtsData(int Hz) const;
        int getUCLRechtsData(int Hz) const;
        int getLGLinksData(int Hz) const;
        int getBGLinksData(int Hz) const;
        int getUCLLinksData(int Hz) const;
        int getROZonderData(int dB) const;
        int getLOZonderData(int dB) const;
        int getROLOZonderData(int dB) const;
        int getROMetData(int dB) const;
        int getLOMetData(int dB) const;
        int getROLOMetData(int dB) const;
        int getLocalisatieZonder() const;
        int getLocalisatieRechts() const;
        int getLocalisatieLinks() const;
        int getLocalisatieBeide() const;
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
    };
}

#endif // _VIEW_MEETGEGEVENS_H
