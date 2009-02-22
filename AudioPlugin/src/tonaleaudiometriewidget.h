#ifndef __TONALEAUDIOMETRIEWIDGET_H__
#define __TONALEAUDIOMETRIEWIDGET_H__

#include <QMap>
#include <QPicture>
#include <QVector>
#include <QWidget>

class TonaleAudiometrieWidget : public QWidget
{
    Q_OBJECT
    public:
        TonaleAudiometrieWidget(QWidget *parent = 0);
        virtual ~TonaleAudiometrieWidget();

        typedef enum { LINKS, RECHTS } Kant;
        void setKant(Kant kant);
        void setLGdata(int Hz, int dB);
        void setBGdata(int Hz, int dB);
        void setUCLdata(int Hz, int dB);

        int getLGdata(int Hz);
        int getBGdata(int Hz);
        int getUCLdata(int Hz);

    public slots:
        void checkLG();
        void checkBG();
        void checkUCL();

    protected:
        virtual void mouseReleaseEvent(QMouseEvent *event);
        virtual void paintEvent(QPaintEvent *event);

    private:
        void tekenLeegRaster();
        void tekenData();

        int rasterHoogte() const;
        int rasterBreedte() const;

        typedef enum { LG, BG, UCL } TekenMode;

        QVector<int> m_lgData;
        QVector<int> m_bgData;
        QVector<int> m_uclData;
        QMap<int, int> m_hzValuesToIndex;
        QPicture m_rooster;
        QPicture m_data;
        Kant m_kant;
        TekenMode m_tekenMode;
};

#endif // __TONALEAUDIOMETRIEWIDGET_H__
