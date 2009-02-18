#include "tonaleaudiometriewidget.h"

#include <QPainter>
#include <QtGui>

TonaleAudiometrieWidget::TonaleAudiometrieWidget(QWidget *parent)
: QWidget(parent)
{
	tekenLeegRaster();
}

TonaleAudiometrieWidget::~TonaleAudiometrieWidget()
{
}

void TonaleAudiometrieWidget::mouseClickEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
	}
}

void TonaleAudiometrieWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawPicture(QPoint(0, 0), m_rooster);
}

void TonaleAudiometrieWidget::tekenLeegRaster()
{
	int width  = m_rooster.width();
	int height = m_rooster.height();
	width = 250;
	height = 250;
	int realWidth = static_cast<int>((width-51)/12 + 0.5) * 12;
	int realHeight = static_cast<int>((height-41)/29 + 0.5) * 29;

	QPainter paint;
	paint.begin(&m_rooster);

	// Teken de verticale assen
	int j = 40;
	int dB[] = {125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000};
	for (int i = 0; i < 11; ++i)
	{
		paint.drawText((i < 4) ? j-10 : j-15, (i > 2  && i % 2 == 0) ? 5 : 25 + realHeight, QString::number(dB[i]));
		paint.setPen((i == 4) ? Qt::black : Qt::lightGray);
		paint.drawLine(j, 20, j, 20 + realHeight);
		j += (i < 2) ? (realWidth / 6) : (realWidth / 12);
	}

	// Teken de horizonale assen
	j = 20;
	for (int i = 0; i < 30; ++i)
	{
		if ((i != 0) && (i % 2 == 0))
		{
			paint.setPen(Qt::black);
			paint.drawText(15 + (((std::max(0, 22-i) / 2) + 9) / 10) * 5, j - 6, QString::number((i - 2) * 5));
		}
		paint.setPen((i == 0) ? Qt::black : Qt::lightGray);
		paint.drawLine(40, j, 40 + realWidth, j);
		j += realHeight / 29;
	}
	paint.end();
}
