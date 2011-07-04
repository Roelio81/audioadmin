#ifndef _SPEECHAUDIOMETRYWIDGET_H
#define _SPEECHAUDIOMETRYWIDGET_H

#include <QMap>
#include <QPicture>
#include <QVector>
#include <QWidget>

class SpeechAudiometryWidget : public QWidget
    {
    Q_OBJECT
    public:
        explicit SpeechAudiometryWidget(QWidget *parent = 0);
        virtual ~SpeechAudiometryWidget();

        typedef enum { WITHOUT, WITH } Kind;
        void setKind(Kind kind);
        void setROdata(int dB, int percentage);
        void setLOdata(int dB, int percentage);
        void setROLOdata(int dB, int percentage);

        int getREdata(int dB);
        int getLEdata(int dB);
        int getRELEdata(int dB);

    public slots:
        void checkRE();
        void checkLE();
        void checkRELE();

    signals:
        void changedREvalue();
        void changedLEvalue();
        void changedRELEvalue();

    protected:
        // --- QWidget ---
        virtual void mouseReleaseEvent(QMouseEvent *event);
        virtual void paintEvent(QPaintEvent *event);

    private:
        void drawGrid();
        void drawData();

        int gridHeight() const;
        int gridWidth() const;

        typedef enum { RE, LE, RELE } DrawMode;

        QVector<int> m_reData;
        QVector<int> m_leData;
        QVector<int> m_releData;
        QPicture m_rooster;
        QPicture m_data;
        Kind m_kind;
        DrawMode m_drawMode;
    };

#endif // _SPEECHAUDIOMETRYWIDGET_H
