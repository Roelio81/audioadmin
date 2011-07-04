#ifndef _PURETONEAUDIOMETRYWIDGET_H
#define _PURETONEAUDIOMETRYWIDGET_H

#include <QMap>
#include <QPicture>
#include <QVector>
#include <QWidget>

class PureToneAudiometryWidget : public QWidget
    {
    Q_OBJECT
    public:
        explicit PureToneAudiometryWidget(QWidget *parent = 0);
        virtual ~PureToneAudiometryWidget();

        typedef enum { LEFT, RIGHT } Side;
        void setSide(Side side);
        void setACdata(int Hz, int dB);
        void setBCdata(int Hz, int dB);
        void setUCLdata(int Hz, int dB);

        int getACdata(int Hz);
        int getBCdata(int Hz);
        int getUCLdata(int Hz);

    public slots:
        void checkAC();
        void checkBC();
        void checkUCL();

    signals:
        void changedACvalue();

    protected:
        // --- QWidget ---
        virtual void mouseReleaseEvent(QMouseEvent *event);
        virtual void paintEvent(QPaintEvent *event);

    private:
        void drawGrid();
        void drawData();

        int gridHeight() const;
        int gridWidth() const;

        typedef enum { AC, BC, UCL } DrawMode;

        QVector<int> m_acData;
        QVector<int> m_bcData;
        QVector<int> m_uclData;
        QMap<int, int> m_hzValuesToIndex;
        QPicture m_grid;
        QPicture m_data;
        Side m_side;
        DrawMode m_drawMode;
    };

#endif // _PURETONEAUDIOMETRYWIDGET_H
