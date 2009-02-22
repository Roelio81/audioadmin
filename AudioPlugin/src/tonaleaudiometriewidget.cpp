#include "tonaleaudiometriewidget.h"

#include <QPainter>
#include <QtGui>

TonaleAudiometrieWidget::TonaleAudiometrieWidget(QWidget *parent)
: QWidget(parent)
, m_lgData(11, -30)
, m_bgData(11, -30)
, m_uclData(11, -30)
, m_kant(RECHTS)
, m_tekenMode(LG)
{
    m_hzValuesToIndex[125] = 0;
    m_hzValuesToIndex[250] = 1;
    m_hzValuesToIndex[500] = 2;
    m_hzValuesToIndex[750] = 3;
    m_hzValuesToIndex[1000] = 4;
    m_hzValuesToIndex[1500] = 5;
    m_hzValuesToIndex[2000] = 6;
    m_hzValuesToIndex[3000] = 7;
    m_hzValuesToIndex[4000] = 8;
    m_hzValuesToIndex[6000] = 9;
    m_hzValuesToIndex[8000] = 10;
}

TonaleAudiometrieWidget::~TonaleAudiometrieWidget()
{
}

void TonaleAudiometrieWidget::setKant(Kant kant)
{
    m_kant = kant;
}

void TonaleAudiometrieWidget::setLGdata(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_lgData[m_hzValuesToIndex[Hz]] = dB;
}

void TonaleAudiometrieWidget::setBGdata(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_bgData[m_hzValuesToIndex[Hz]] = dB;
}

void TonaleAudiometrieWidget::setUCLdata(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_uclData[m_hzValuesToIndex[Hz]] = dB;
}

int TonaleAudiometrieWidget::getLGdata(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_lgData[m_hzValuesToIndex[Hz]];
}

int TonaleAudiometrieWidget::getBGdata(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_bgData[m_hzValuesToIndex[Hz]];
}

int TonaleAudiometrieWidget::getUCLdata(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_uclData[m_hzValuesToIndex[Hz]];
}

void TonaleAudiometrieWidget::checkLG()
{
    m_tekenMode = LG;
}

void TonaleAudiometrieWidget::checkBG()
{
    m_tekenMode = BG;
}

void TonaleAudiometrieWidget::checkUCL()
{
    m_tekenMode = UCL;
}

void TonaleAudiometrieWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // We passen een vector aan op positie i zetten we waarde j: bepaal i en j
        int i1 = (event->x() - 40 + rasterBreedte()/24) / (rasterBreedte()/12);
        int i2 = (event->x() - 40 + rasterBreedte()/12) / (rasterBreedte()/6);
        int i = (i2 < 2) ? i2 : i1 - 2;
        int j = static_cast<int> ((((event->y() - 20.0)/rasterHoogte() * 145.0) - 10.0) / 5.0 + 0.5) * 5;
        if (j >= 0)
        {
            switch (m_tekenMode)
            {
            case LG: m_lgData[i] = j; break;
            case BG: m_bgData[i] = j; break;
            case UCL: m_uclData[i] = j; break;
            default: Q_ASSERT(false);
            }

        update();
        }
    }
}

void TonaleAudiometrieWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    tekenLeegRaster();
    tekenData();
    painter.drawPicture(0, 0, m_rooster);
    painter.drawPicture(0, 0, m_data);
}

void TonaleAudiometrieWidget::tekenLeegRaster()
{
    QPainter paint;
    paint.begin(&m_rooster);

    // Teken de verticale assen
    int dB[] = {125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000};
    for (int i = 0; i < 11; ++i)
    {
        int x = 40 + ((i < 2) ? i*(rasterBreedte()/6) : (i+2)*(rasterBreedte()/12));
        paint.setPen(Qt::black);
        paint.drawText((i<4)?x-6:x-9, (i>2 && i%2==1) ? (34+rasterHoogte()) : 12, QString::number(dB[i]));
        paint.setPen((i == 4) ? Qt::black : Qt::lightGray);
        paint.drawLine(x, 20, x, 20 + rasterHoogte());
    }

    // Teken de horizonale assen
    for (int i = 0; i < 30; ++i)
    {
        int y = 20 + (static_cast<int> (i * rasterHoogte()/29.0));
        if ((i != 0) && (i % 2 == 0))
        {
            paint.setPen(Qt::black);
            paint.drawText(15 + 6*(((22-i)/20) + (22-i <= 0 ? 0 : 1)), y + 5, QString::number((i - 2) * 5));
        }
        paint.setPen((i == 2) ? Qt::black : Qt::lightGray);
        paint.drawLine(40, y, 40 + rasterBreedte(), y);
    }
    paint.end();
}

void TonaleAudiometrieWidget::tekenData()
{
    int xx = -1;
    int yy = -1;

    QPainter paint;
    QPen pen;
    paint.begin(&m_data);
    pen.setColor(m_kant == RECHTS ? Qt::red : Qt::blue);
    pen.setStyle(Qt::SolidLine);
    paint.setPen(pen);

    // Teken LG data
    xx = -1;
    yy = -1;
    for (int i = 0; i < 11; ++i)
    {
        int x = 40 + ((i < 2) ? i*(rasterBreedte()/6) : (i+2)*(rasterBreedte()/12));
        if (m_lgData[i] >= 0)
        {
            int y = 20 + static_cast<int> (((m_lgData[i]+10.0)/145.0)*rasterHoogte() + 0.5);
            switch (m_kant)
            {
                case RECHTS:
                    paint.drawEllipse(x-4, y-4, 8, 8);
                    break;
                case LINKS:
                    paint.drawLine(x-4, y-4, x+4, y+4);
                    paint.drawLine(x-4, y+4, x+4, y-4);
                    break;
                default:
                   Q_ASSERT(false);
            }
            if (xx > 0 && yy > 0) paint.drawLine(xx, yy, x, y);
            xx = x;
            yy = y;
        }
    }

    // Teken BG data
    xx = -1;
    yy = -1;
    for (int i = 0; i < 11; ++i)
    {
        int x = 40 + ((i < 2) ? i*(rasterBreedte()/6) : (i+2)*(rasterBreedte()/12));
        if (m_bgData[i] >= 0)
        {
            int y = 20 + static_cast<int> (((m_bgData[i]+10.0)/145.0)*rasterHoogte() + 0.5);
            switch (m_kant)
            {
                case RECHTS:
                    paint.drawLine(x, y, x+4, y+4);
                    paint.drawLine(x, y, x+4, y-4);
                    break;
                case LINKS:
                    paint.drawLine(x-4, y-4, x, y);
                    paint.drawLine(x-4, y+4, x, y);
                    break;
                default:
                   Q_ASSERT(false);
            }
            if (xx > 0 && yy > 0)
            {
                pen.setStyle(Qt::DashLine);
                paint.setPen(pen);
                paint.drawLine(xx, yy, x, y);
                pen.setStyle(Qt::SolidLine);
                paint.setPen(pen);
            }
            xx = x;
            yy = y;
        }
    }


    // Teken UCL data
    xx = -1;
    yy = -1;
    for (int i = 0; i < 11; ++i)
    {
        int x = 40 + ((i < 2) ? i*(rasterBreedte()/6) : (i+2)*(rasterBreedte()/12));
        if (m_uclData[i] >= 0)
        {
            int y = 20 + static_cast<int> (((m_uclData[i]+10.0)/145.0)*rasterHoogte() + 0.5);
            paint.drawLine(x-4, y-4, x+4, y-4);
            paint.drawLine(x-4, y-4, x, y+4);
            paint.drawLine(x, y+4, x+4, y-4);
            if (xx > 0 && yy > 0) paint.drawLine(xx, yy, x, y);
            xx = x;
            yy = y;
        }
    }

}

int TonaleAudiometrieWidget::rasterBreedte() const
{
    return static_cast<int>((width()-51)/12.0 + 0.5) * 12;
}

int TonaleAudiometrieWidget::rasterHoogte() const
{
    return static_cast<int>((height()-51)/29.0 + 0.5) * 29;
}
