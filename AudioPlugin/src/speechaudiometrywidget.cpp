#include "speechaudiometrywidget.h"

#include <QPainter>
#include <QtGui>

namespace
    {
    const int BORDER_TOP = 13;
    const int BORDER_LEFT = 40;
    const int INVALID_VALUE = -30;
    }

SpeechAudiometryWidget::SpeechAudiometryWidget(QWidget *parent)
: QWidget(parent)
, m_reData(23, INVALID_VALUE)
, m_leData(23, INVALID_VALUE)
, m_releData(23, INVALID_VALUE)
, m_kind(WITHOUT)
, m_drawMode(RE)
{
}

SpeechAudiometryWidget::~SpeechAudiometryWidget()
{
}

void SpeechAudiometryWidget::setKind(Kind kind)
{
    m_kind = kind;
}

void SpeechAudiometryWidget::setROdata(int dB, int percentage)
{
    m_reData[dB/5] = percentage;
    emit changedREvalue();
}

void SpeechAudiometryWidget::setLOdata(int dB, int percentage)
{
    m_leData[dB/5] = percentage;
    emit changedLEvalue();
}

void SpeechAudiometryWidget::setROLOdata(int dB, int percentage)
{
    m_releData[dB/5] = percentage;
    emit changedRELEvalue();
}

int SpeechAudiometryWidget::getREdata(int dB)
{
    return m_reData[dB/5];
}

int SpeechAudiometryWidget::getLEdata(int dB)
{
    return m_leData[dB/5];
}

int SpeechAudiometryWidget::getRELEdata(int dB)
{
    return m_releData[dB/5];
}

void SpeechAudiometryWidget::checkRE()
{
    m_drawMode = RE;
}

void SpeechAudiometryWidget::checkLE()
{
    m_drawMode = LE;
}

void SpeechAudiometryWidget::checkRELE()
{
    m_drawMode = RELE;
}

void SpeechAudiometryWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // We passen een vector aan op positie i zetten we waarde j: bepaal i en j
        int i = (event->x() - BORDER_LEFT + gridWidth()/44) / (gridWidth()/22);
        int j = 100 - static_cast<int> (floor(((event->y() - BORDER_TOP * 1.0)/gridHeight() * 100.0) / 5.0 + 0.5)) * 5;
        if (j < 0 || j > 100)
            j = INVALID_VALUE;
        switch (m_drawMode)
        {
            case RE:
                m_reData[i] = j;
                emit changedREvalue();
                break;
            case LE:
                m_leData[i] = j;
                emit changedLEvalue();
                break;
            case RELE:
                m_releData[i] = j;
                emit changedRELEvalue();
                break;
            default:
                Q_ASSERT(false);
        }

        update();
    }
}

void SpeechAudiometryWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawGrid();
    drawData();
    painter.drawPicture(0, 0, m_rooster);
    painter.drawPicture(0, 0, m_data);
}

void SpeechAudiometryWidget::drawGrid()
{
    QPainter paint;
    paint.begin(&m_rooster);

    QFont boldFont;
    boldFont.setBold(true);

    // Paint the vertical axes
    for (int i = 0; i < 23; ++i)
    {
        int x = BORDER_LEFT + i*gridWidth()/22;
        paint.setPen(Qt::black);
        if ((i % 2 == 0) && (i != 0) && (i < 20))
            paint.drawText(x-6, gridHeight()+25, QString::number(i*5));
        else if (i == 20)
            paint.drawText(x-9, gridHeight()+25, QString::number(i*5));

        paint.setPen(QPen((i == 0 || i == 8 || i == 11 || i == 14) ? Qt::black : Qt::lightGray, (i == 0) ? 2 : 1));
        paint.drawLine(x, BORDER_TOP, x, gridHeight()+BORDER_TOP);
    }
    paint.setPen(Qt::black);
    paint.setFont(boldFont);
    paint.drawText(BORDER_LEFT+gridWidth(), 25+gridHeight(), "dB");
    paint.setFont(QFont());

    // Paint the horizontal axes
    for (int i = 0; i < 21; ++i)
    {
        int y = BORDER_TOP + i*gridHeight()/20;
        if (i % 2 == 0)
        {
            paint.setPen(Qt::black);
            paint.drawText(15 + 6*((i/20) + (i == 0 ? 0 : 1)), y+6, QString::number((20-i)*5));
        }

        paint.setPen(QPen((i == 10 || i == 20) ? Qt::black : Qt::lightGray, (i == 20) ? 2 : 1));
        paint.drawLine(BORDER_LEFT+1, y, BORDER_LEFT+gridWidth(), y);
    }
    paint.setPen(Qt::black);
    paint.setFont(boldFont);
    paint.drawText(34, 8, "%");
    paint.setFont(QFont());

    // Tekenen van de curve
    int minY = BORDER_TOP;
    int maxY = BORDER_TOP + gridHeight();
    paint.setPen(Qt::black);
    for (int x = BORDER_LEFT; x < BORDER_LEFT + 2*(gridWidth()/22); ++x)
    {
        double xx1 = (x - BORDER_LEFT*1.0) / (4.0*(gridWidth()/22.0) / 20.0);
        double yy1 = (3.0/5.0)*xx1*xx1 - xx1;
        double xx2 = (x - BORDER_LEFT*1.0 + 1.0) / (4.0*(gridWidth()/22.0) / 20.0);
        double yy2 = (3.0/5.0)*xx2*xx2 - xx2;
        int y1 = std::min(static_cast<int> (BORDER_TOP + ((100.0 - yy1) * gridHeight())/100.0), maxY);
        int y2 = std::min(static_cast<int> (BORDER_TOP + ((100.0 - yy2) * gridHeight())/100.0), maxY);
        paint.drawLine(x, y1, x+1, y2);
    }
    for (int x = BORDER_LEFT + 2*(gridWidth()/22); x < BORDER_LEFT + 4*(gridWidth()/22); ++x)
    {
        double xx1 = (x - BORDER_LEFT*1.0) / (4.0*(gridWidth()/22.0) / 20.0);
        double yy1 = (-3.0/5.0)*xx1*xx1 + 23.0*xx1 - 120.0;
        double xx2 = (x - BORDER_LEFT*1.0 + 1.0) / (4.0*(gridWidth()/22.0) / 20.0);
        double yy2 = (-3.0/5.0)*xx2*xx2 + 23.0*xx2 - 120.0;
        int y1 = std::max(static_cast<int> (BORDER_TOP + ((100.0 - yy1) * gridHeight())/100.0), minY);
        int y2 = std::max(static_cast<int> (BORDER_TOP + ((100.0 - yy2) * gridHeight())/100.0), minY);
        paint.drawLine(x, y1, x+1, y2);
    }
}

void SpeechAudiometryWidget::drawData()
{
    int xx = -1;
    int yy = -1;

    QPainter paint;
    paint.begin(&m_data);

    // Draw RE data
    paint.setPen(Qt::red);
    xx = -1;
    yy = -1;
    for (int i = 0; i < 23; ++i)
    {
        int x = BORDER_LEFT + i*gridWidth()/22;
        if (m_reData[i] >= 0)
        {
            int y = BORDER_TOP + static_cast<int> (((100 - m_reData[i])/100.0)*gridHeight() + 0.5);
            switch (m_kind)
            {
                case WITHOUT:
                    paint.drawEllipse(x-4, y-4, 8, 8);
                    break;
                case WITH:
                    paint.setBrush(QBrush(paint.pen().color(), Qt::SolidPattern));
                    paint.drawEllipse(x-4, y-4, 8, 8);
                    paint.setBrush(Qt::NoBrush);
                    break;
                default:
                   Q_ASSERT(false);
            }
            if (xx > 0 && yy > 0) paint.drawLine(xx, yy, x, y);
            xx = x;
            yy = y;
        }
    }

    // Draw LE data
    paint.setPen(Qt::blue);
    xx = -1;
    yy = -1;
    for (int i = 0; i < 23; ++i)
    {
        int x = BORDER_LEFT + i*gridWidth()/22;
        if (m_leData[i] >= 0)
        {
            int y = BORDER_TOP + static_cast<int> (((100 - m_leData[i])/100.0)*gridHeight() + 0.5);
            switch (m_kind)
            {
                case WITHOUT:
                    paint.drawLine(x-4, y-4, x+4, y+4);
                    paint.drawLine(x-4, y+4, x+4, y-4);
                    break;
                case WITH:
                    paint.fillRect(x-4, y-4, 8, 8, paint.pen().color());
                    break;
                default:
                   Q_ASSERT(false);
            }
            if (xx > 0 && yy > 0) paint.drawLine(xx, yy, x, y);
            xx = x;
            yy = y;
        }
    }

    // Draw RELE data
    paint.setPen(Qt::darkGreen);
    xx = -1;
    yy = -1;
    for (int i = 0; i < 23; ++i)
    {
        int x = BORDER_LEFT + i*gridWidth()/22;
        if (m_releData[i] >= 0)
        {
            int y = BORDER_TOP + static_cast<int> (((100 - m_releData[i])/100.0)*gridHeight() + 0.5);
            switch (m_kind)
            {
                case WITHOUT:
                    paint.drawLine(x-4, y+4, x+4, y+4);
                    paint.drawLine(x-4, y+4, x, y-4);
                    paint.drawLine(x, y-4, x+4, y+4);
                    break;
                case WITH:
                    {
                        paint.setBrush(QBrush(paint.pen().color(), Qt::SolidPattern));
                        QPoint points[] = { QPoint(x-4, y+4), QPoint(x+4, y+4), QPoint(x, y-4) };
                        paint.drawConvexPolygon(points, 3);
                        paint.setBrush(Qt::NoBrush);
                    }
                    break;
                default:
                   Q_ASSERT(false);
            }
            if (xx > 0 && yy > 0) paint.drawLine(xx, yy, x, y);
            xx = x;
            yy = y;
        }
    }
}

int SpeechAudiometryWidget::gridWidth() const
{
    return static_cast<int>((width()-51)/22 + 0.5) * 22;
}

int SpeechAudiometryWidget::gridHeight() const
{
    return static_cast<int>((height()-31)/20 + 0.5) * 20;
}
