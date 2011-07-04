#include "puretoneaudiometrywidget.h"

#include <QPainter>
#include <QtGui>

namespace
{
const int BORDER_TOP = 20;
const int BORDER_LEFT = 40;
const int INVALID_VALUE = -30;
}

PureToneAudiometryWidget::PureToneAudiometryWidget(QWidget *parent)
: QWidget(parent)
, m_acData(11, INVALID_VALUE)
, m_bcData(11, INVALID_VALUE)
, m_uclData(11, INVALID_VALUE)
, m_side(RIGHT)
, m_drawMode(AC)
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

PureToneAudiometryWidget::~PureToneAudiometryWidget()
{
}

void PureToneAudiometryWidget::setSide(Side side)
{
    m_side = side;
}

void PureToneAudiometryWidget::setACdata(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_acData[m_hzValuesToIndex[Hz]] = dB;
    emit changedACvalue();
}

void PureToneAudiometryWidget::setBCdata(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_bcData[m_hzValuesToIndex[Hz]] = dB;
}

void PureToneAudiometryWidget::setUCLdata(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_uclData[m_hzValuesToIndex[Hz]] = dB;
}

int PureToneAudiometryWidget::getACdata(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_acData[m_hzValuesToIndex[Hz]];
}

int PureToneAudiometryWidget::getBCdata(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_bcData[m_hzValuesToIndex[Hz]];
}

int PureToneAudiometryWidget::getUCLdata(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_uclData[m_hzValuesToIndex[Hz]];
}

void PureToneAudiometryWidget::checkAC()
{
    m_drawMode = AC;
}

void PureToneAudiometryWidget::checkBC()
{
    m_drawMode = BC;
}

void PureToneAudiometryWidget::checkUCL()
{
    m_drawMode = UCL;
}

void PureToneAudiometryWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // We are changing a vector: on position i we set value j: determine i and j
        int i1 = (event->x() - BORDER_LEFT + gridWidth()/24) / (gridWidth()/12);
        int i2 = (event->x() - BORDER_LEFT + gridWidth()/12) / (gridWidth()/6);
        int i = (i2 < 2) ? i2 : i1 - 2;
        int j = static_cast<int> ((((event->y() - BORDER_TOP * 1.0)/gridHeight() * 145.0)) / 5.0 + 0.5) * 5 - 10;
        if (j > 135 || j < 0)
            j = INVALID_VALUE;
        switch (m_drawMode)
        {
            case AC:
                m_acData[i] = j;
                emit changedACvalue();
                break;
            case BC:
                m_bcData[i] = j;
                break;
            case UCL:
                m_uclData[i] = j;
                break;
            default:
                Q_ASSERT(false);
        }

        update();
    }
}

void PureToneAudiometryWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    drawGrid();
    drawData();
    painter.drawPicture(0, 0, m_grid);
    painter.drawPicture(0, 0, m_data);
}

void PureToneAudiometryWidget::drawGrid()
{
    QPainter paint;
    paint.begin(&m_grid);

    QFont boldFont;
    boldFont.setBold(true);

    // Paint the vertical axes
    int dB[] = {125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000};
    for (int i = 0; i < 11; ++i)
    {
        int x = BORDER_LEFT + ((i < 2) ? i*(gridWidth()/6) : (i+2)*(gridWidth()/12));
        paint.setPen(Qt::black);
        paint.drawText((i<4)?x-6:x-9, (i>2 && i%2==1) ? (34+gridHeight()) : 12, QString::number(dB[i]));
        paint.setPen(QPen((i == 0 || i == 4) ? Qt::black : Qt::lightGray, (i == 0) ? 2 : 1));
        paint.drawLine(x, BORDER_TOP, x, BORDER_TOP + gridHeight());
    }
    paint.setPen(Qt::black);
    paint.setFont(boldFont);
    paint.drawText(BORDER_LEFT + gridWidth(), 34 + gridHeight(), "Hz");
    paint.setFont(QFont());

    // Paint the horizontal axes
    for (int i = 0; i < 30; ++i)
    {
        int y = BORDER_TOP + (static_cast<int> (i * gridHeight()/29.0));
        if ((i != 0) && (i % 2 == 0))
        {
            paint.setPen(Qt::black);
            paint.drawText(15 + 6*(((22-i)/20) + (22-i <= 0 ? 0 : 1)), y + 5, QString::number((i - 2) * 5));
        }
        paint.setPen(QPen((i == 2 || i == 29) ? Qt::black : Qt::lightGray, (i == 29) ? 2 : 1));
        paint.drawLine(BORDER_LEFT+1, y, BORDER_LEFT+gridWidth(), y);
    }
    paint.setPen(Qt::black);
    paint.setFont(boldFont);
    paint.drawText(19, 25, "dB");
    paint.setFont(QFont());

    paint.end();
}

void PureToneAudiometryWidget::drawData()
{
    int xx = -1;
    int yy = -1;

    QPainter paint;
    QPen pen;
    paint.begin(&m_data);
    pen.setColor(m_side == RIGHT ? Qt::red : Qt::blue);
    pen.setStyle(Qt::SolidLine);
    paint.setPen(pen);

    // Draw AC data
    xx = -1;
    yy = -1;
    for (int i = 0; i < 11; ++i)
    {
        int x = BORDER_LEFT + ((i < 2) ? i*(gridWidth()/6) : (i+2)*(gridWidth()/12));
        if (m_acData[i] >= 0)
        {
            int y = BORDER_TOP + static_cast<int> (((m_acData[i]+10.0)/145.0)*gridHeight() + 0.5);
            switch (m_side)
            {
                case RIGHT:
                    paint.drawEllipse(x-4, y-4, 8, 8);
                    break;
                case LEFT:
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

    // Draw BC data
    xx = -1;
    yy = -1;
    for (int i = 0; i < 11; ++i)
    {
        int x = BORDER_LEFT + ((i < 2) ? i*(gridWidth()/6) : (i+2)*(gridWidth()/12));
        if (m_bcData[i] >= 0)
        {
            int y = BORDER_TOP + static_cast<int> (((m_bcData[i]+10.0)/145.0)*gridHeight() + 0.5);
            switch (m_side)
            {
                case RIGHT:
                    paint.drawLine(x, y, x+4, y+4);
                    paint.drawLine(x, y, x+4, y-4);
                    break;
                case LEFT:
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


    // Draw UCL data
    xx = -1;
    yy = -1;
    for (int i = 0; i < 11; ++i)
    {
        int x = BORDER_LEFT + ((i < 2) ? i*(gridWidth()/6) : (i+2)*(gridWidth()/12));
        if (m_uclData[i] >= 0)
        {
            int y = BORDER_TOP + static_cast<int> (((m_uclData[i]+10.0)/145.0)*gridHeight() + 0.5);
            paint.drawLine(x-4, y-4, x+4, y-4);
            paint.drawLine(x-4, y-4, x, y+4);
            paint.drawLine(x, y+4, x+4, y-4);
            if (xx > 0 && yy > 0) paint.drawLine(xx, yy, x, y);
            xx = x;
            yy = y;
        }
    }

}

int PureToneAudiometryWidget::gridWidth() const
{
    return static_cast<int>((width()-51)/12.0 + 0.5) * 12;
}

int PureToneAudiometryWidget::gridHeight() const
{
    return static_cast<int>((height()-51)/29.0 + 0.5) * 29;
}
