#include "vocaleaudiometriewidget.h"

#include <QPainter>
#include <QtGui>

namespace
{
const int BORDER_TOP = 13;
const int BORDER_LEFT = 40;
const int INVALID_VALUE = -30;
}

VocaleAudiometrieWidget::VocaleAudiometrieWidget(QWidget *parent)
: QWidget(parent)
, m_roData(23, INVALID_VALUE)
, m_loData(23, INVALID_VALUE)
, m_roloData(23, INVALID_VALUE)
, m_soort(ZONDER)
, m_tekenMode(RO)
{
}

VocaleAudiometrieWidget::~VocaleAudiometrieWidget()
{
}

void VocaleAudiometrieWidget::setSoort(Soort soort)
{
    m_soort = soort;
}

void VocaleAudiometrieWidget::setROdata(int dB, int percentage)
{
    m_roData[dB/5] = percentage;
    emit wijzigingROwaarde();
}

void VocaleAudiometrieWidget::setLOdata(int dB, int percentage)
{
    m_loData[dB/5] = percentage;
    emit wijzigingLOwaarde();
}

void VocaleAudiometrieWidget::setROLOdata(int dB, int percentage)
{
    m_roloData[dB/5] = percentage;
    emit wijzigingROLOwaarde();
}

int VocaleAudiometrieWidget::getROdata(int dB)
{
    return m_roData[dB/5];
}

int VocaleAudiometrieWidget::getLOdata(int dB)
{
    return m_loData[dB/5];
}

int VocaleAudiometrieWidget::getROLOdata(int dB)
{
    return m_roloData[dB/5];
}

void VocaleAudiometrieWidget::checkRO()
{
    m_tekenMode = RO;
}

void VocaleAudiometrieWidget::checkLO()
{
    m_tekenMode = LO;
}

void VocaleAudiometrieWidget::checkROLO()
{
    m_tekenMode = ROLO;
}

void VocaleAudiometrieWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // We passen een vector aan op positie i zetten we waarde j: bepaal i en j
        int i = (event->x() - BORDER_LEFT + rasterBreedte()/44) / (rasterBreedte()/22);
        int j = 100 - static_cast<int> (floor(((event->y() - BORDER_TOP * 1.0)/rasterHoogte() * 100.0) / 5.0 + 0.5)) * 5;
        if (j < 0 || j > 100)
            j = INVALID_VALUE;
        switch (m_tekenMode)
        {
            case RO:
                m_roData[i] = j;
                emit wijzigingROwaarde();
                break;
            case LO:
                m_loData[i] = j;
                emit wijzigingLOwaarde();
                break;
            case ROLO:
                m_roloData[i] = j;
                emit wijzigingROLOwaarde();
                break;
            default:
                Q_ASSERT(false);
        }

        update();
    }
}

void VocaleAudiometrieWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    tekenLeegRaster();
    tekenData();
    painter.drawPicture(0, 0, m_rooster);
    painter.drawPicture(0, 0, m_data);
}

void VocaleAudiometrieWidget::tekenLeegRaster()
{
    QPainter paint;
    paint.begin(&m_rooster);

    QFont boldFont;
    boldFont.setBold(true);

    // Paint the vertical axes
    for (int i = 0; i < 23; ++i)
    {
        int x = BORDER_LEFT + i*rasterBreedte()/22;
        paint.setPen(Qt::black);
        if ((i % 2 == 0) && (i != 0) && (i < 20))
            paint.drawText(x-6, rasterHoogte()+25, QString::number(i*5));
        else if (i == 20)
            paint.drawText(x-9, rasterHoogte()+25, QString::number(i*5));

        paint.setPen(QPen((i == 0 || i == 8 || i == 11 || i == 14) ? Qt::black : Qt::lightGray, (i == 0) ? 2 : 1));
        paint.drawLine(x, BORDER_TOP, x, rasterHoogte()+BORDER_TOP);
    }
    paint.setPen(Qt::black);
    paint.setFont(boldFont);
    paint.drawText(BORDER_LEFT+rasterBreedte(), 25+rasterHoogte(), "dB");
    paint.setFont(QFont());

    // Paint the horizontal axes
    for (int i = 0; i < 21; ++i)
    {
        int y = BORDER_TOP + i*rasterHoogte()/20;
        if (i % 2 == 0)
        {
            paint.setPen(Qt::black);
            paint.drawText(15 + 6*((i/20) + (i == 0 ? 0 : 1)), y+6, QString::number((20-i)*5));
        }

        paint.setPen(QPen((i == 10 || i == 20) ? Qt::black : Qt::lightGray, (i == 20) ? 2 : 1));
        paint.drawLine(BORDER_LEFT+1, y, BORDER_LEFT+rasterBreedte(), y);
    }
    paint.setPen(Qt::black);
    paint.setFont(boldFont);
    paint.drawText(34, 8, "%");
    paint.setFont(QFont());

    // Tekenen van de curve
    int minY = BORDER_TOP;
    int maxY = BORDER_TOP + rasterHoogte();
    paint.setPen(Qt::black);
    for (int x = BORDER_LEFT; x < BORDER_LEFT + 2*(rasterBreedte()/22); ++x)
    {
        double xx1 = (x - BORDER_LEFT*1.0) / (4.0*(rasterBreedte()/22.0) / 20.0);
        double yy1 = (3.0/5.0)*xx1*xx1 - xx1;
        double xx2 = (x - BORDER_LEFT*1.0 + 1.0) / (4.0*(rasterBreedte()/22.0) / 20.0);
        double yy2 = (3.0/5.0)*xx2*xx2 - xx2;
        int y1 = std::min(static_cast<int> (BORDER_TOP + ((100.0 - yy1) * rasterHoogte())/100.0), maxY);
        int y2 = std::min(static_cast<int> (BORDER_TOP + ((100.0 - yy2) * rasterHoogte())/100.0), maxY);
        paint.drawLine(x, y1, x+1, y2);
    }
    for (int x = BORDER_LEFT + 2*(rasterBreedte()/22); x < BORDER_LEFT + 4*(rasterBreedte()/22); ++x)
    {
        double xx1 = (x - BORDER_LEFT*1.0) / (4.0*(rasterBreedte()/22.0) / 20.0);
        double yy1 = (-3.0/5.0)*xx1*xx1 + 23.0*xx1 - 120.0;
        double xx2 = (x - BORDER_LEFT*1.0 + 1.0) / (4.0*(rasterBreedte()/22.0) / 20.0);
        double yy2 = (-3.0/5.0)*xx2*xx2 + 23.0*xx2 - 120.0;
        int y1 = std::max(static_cast<int> (BORDER_TOP + ((100.0 - yy1) * rasterHoogte())/100.0), minY);
        int y2 = std::max(static_cast<int> (BORDER_TOP + ((100.0 - yy2) * rasterHoogte())/100.0), minY);
        paint.drawLine(x, y1, x+1, y2);
    }
}

void VocaleAudiometrieWidget::tekenData()
{
    int xx = -1;
    int yy = -1;

    QPainter paint;
    paint.begin(&m_data);

    // Teken RO data
    paint.setPen(Qt::red);
    xx = -1;
    yy = -1;
    for (int i = 0; i < 23; ++i)
    {
        int x = BORDER_LEFT + i*rasterBreedte()/22;
        if (m_roData[i] >= 0)
        {
            int y = BORDER_TOP + static_cast<int> (((100 - m_roData[i])/100.0)*rasterHoogte() + 0.5);
            switch (m_soort)
            {
                case ZONDER:
                    paint.drawEllipse(x-4, y-4, 8, 8);
                    break;
                case MET:
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

    // Teken LO data
    paint.setPen(Qt::blue);
    xx = -1;
    yy = -1;
    for (int i = 0; i < 23; ++i)
    {
        int x = BORDER_LEFT + i*rasterBreedte()/22;
        if (m_loData[i] >= 0)
        {
            int y = BORDER_TOP + static_cast<int> (((100 - m_loData[i])/100.0)*rasterHoogte() + 0.5);
            switch (m_soort)
            {
                case ZONDER:
                    paint.drawLine(x-4, y-4, x+4, y+4);
                    paint.drawLine(x-4, y+4, x+4, y-4);
                    break;
                case MET:
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

    // Teken ROLO data
    paint.setPen(Qt::darkGreen);
    xx = -1;
    yy = -1;
    for (int i = 0; i < 23; ++i)
    {
        int x = BORDER_LEFT + i*rasterBreedte()/22;
        if (m_roloData[i] >= 0)
        {
            int y = BORDER_TOP + static_cast<int> (((100 - m_roloData[i])/100.0)*rasterHoogte() + 0.5);
            switch (m_soort)
            {
                case ZONDER:
                    paint.drawLine(x-4, y+4, x+4, y+4);
                    paint.drawLine(x-4, y+4, x, y-4);
                    paint.drawLine(x, y-4, x+4, y+4);
                    break;
                case MET:
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

int VocaleAudiometrieWidget::rasterBreedte() const
{
    return static_cast<int>((width()-51)/22 + 0.5) * 22;
}

int VocaleAudiometrieWidget::rasterHoogte() const
{
    return static_cast<int>((height()-31)/20 + 0.5) * 20;
}
