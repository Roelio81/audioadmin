#include "vocaleaudiometriewidget.h"

#include <QPainter>
#include <QtGui>

VocaleAudiometrieWidget::VocaleAudiometrieWidget(QWidget *parent)
: QWidget(parent)
, m_roData(23, -30)
, m_loData(23, -30)
, m_roloData(23, -30)
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
        int i = (event->x() - 40 + rasterBreedte()/44) / (rasterBreedte()/22);
        int j = 100 - static_cast<int> (((event->y() - 10.0)/rasterHoogte() * 100.0) / 5.0 + 0.5) * 5;
        if (j >= 0)
        {
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

    for (int i = 0; i < 23; ++i)
    {
        int x = 40 + i*rasterBreedte()/22;
        paint.setPen(Qt::black);
        if ((i % 2 == 0) && (i != 0) && (i < 20))
            paint.drawText(x-6, rasterHoogte()+25, QString::number(i*5));
        else if (i == 20)
            paint.drawText(x-9, rasterHoogte()+25, QString::number(i*5));

        paint.setPen((i == 8 || i == 11 || i == 14) ? Qt::black : Qt::lightGray);
        paint.drawLine(x, 10, x, rasterHoogte()+10);
    }

    for (int i = 0; i < 21; ++i)
    {
        int y = 10 + i*rasterHoogte()/20;
        if (i % 2 == 0)
        {
            paint.setPen(Qt::black);
            paint.drawText(15 + 6*((i/20) + (i == 0 ? 0 : 1)), y+6, QString::number((20-i)*5));
        }

        paint.setPen((i == 10) ? Qt::black : Qt::lightGray);
        paint.drawLine(40, y, 40 + rasterBreedte(), y);
    }

/* MOGELIJK QWT gebruiken voor bezier? of op andere manier functie zien te evalueren!
   bitmap.Canvas.MoveTo(41, 10+realheight);
   bitmap.Canvas.Brush.Color := clBlack;
   bitmap.Canvas.Pen.Color := clBlack;
   punten[0].Y := 10+realheight;                   punten[0].X := 41;
   punten[1].Y := 10+(18 * (realheight div 20));   punten[1].X := 41+(1 * (realwidth div 22));
   punten[2].Y := 10+(16 * (realheight div 20));   punten[2].X := 41+(Round(1.5 * (realwidth div 22)));
   punten[3].Y := 10+(10 * (realheight div 20));   punten[3].X := 41+(2 * (realwidth div 22));
   punten[4].Y := 10+(4  * (realheight div 20));   punten[4].X := 41+(Round(2.5 * (realwidth div 22)));
   punten[5].Y := 10+(2  * (realheight div 20));   punten[5].X := 41+(3 * (realwidth div 22));
   punten[6].Y := 10+(0  * (realheight div 20));   punten[6].X := 41+(4 * (realwidth div 22));
   bitmap.Canvas.PolyBezier(punten);
   EmptyRaster2 := bitmap;
*/
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
        int x = 40 + i*rasterBreedte()/22;
        if (m_roData[i] >= 0)
        {
            int y = 10 + static_cast<int> (((100 - m_roData[i])/100.0)*rasterHoogte() + 0.5);
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
        int x = 40 + i*rasterBreedte()/22;
        if (m_loData[i] >= 0)
        {
            int y = 10 + static_cast<int> (((100 - m_loData[i])/100.0)*rasterHoogte() + 0.5);
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
        int x = 40 + i*rasterBreedte()/22;
        if (m_roloData[i] >= 0)
        {
            int y = 10 + static_cast<int> (((100 - m_roloData[i])/100.0)*rasterHoogte() + 0.5);
            switch (m_soort)
            {
                case ZONDER:
                    paint.drawLine(x-4, y-4, x+4, y-4);
                    paint.drawLine(x-4, y-4, x, y+4);
                    paint.drawLine(x, y+4, x+4, y-4);
                    break;
                case MET:
                    {
                        paint.setBrush(QBrush(paint.pen().color(), Qt::SolidPattern));
                        QPoint points[] = { QPoint(x-4, y-4), QPoint(x+4, y-4), QPoint(x, y+4) };
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
