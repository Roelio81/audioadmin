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
        Meetgegevens(QWidget *parent = 0);
        virtual ~Meetgegevens();

        int getLGRechtsData(int Hz);
        int getBGRechtsData(int Hz);
        int getUCLRechtsData(int Hz);
        int getLGLinksData(int Hz);
        int getBGLinksData(int Hz);
        int getUCLLinksData(int Hz);
        int getROZonderData(int dB);
        int getLOZonderData(int dB);
        int getROLOZonderData(int dB);
        int getROMetData(int dB);
        int getLOMetData(int dB);
        int getROLOMetData(int dB);
        int getLocalisatieZonder();
        int getLocalisatieRechts();
        int getLocalisatieLinks();
        int getLocalisatieBeide();

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

    signals:
        void meetgegevensSluiten();
        void meetgegevensBewaren();

    private slots:
        void herberekenGemiddeldVerliesLinks();
        void herberekenGemiddeldVerliesRechts();
        void herberekenROZonder();
        void herberekenLOZonder();
        void herberekenROLOZonder();
        void herberekenROMet();
        void herberekenLOMet();
        void herberekenROLOMet();
        void sluitMeetgegevens();
        void bewaarMeetgegevens();

    private:
        void herberekenROWinst();
        void herberekenLOWinst();
        void herberekenROLOWinst();
    };
}

#endif // _VIEW_MEETGEGEVENS_H
