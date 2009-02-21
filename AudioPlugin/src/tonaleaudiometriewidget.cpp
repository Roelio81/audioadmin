#include "tonaleaudiometriewidget.h"

#include <QPainter>
#include <QtGui>

TonaleAudiometrieWidget::TonaleAudiometrieWidget(QWidget *parent)
: QWidget(parent)
{
}

TonaleAudiometrieWidget::~TonaleAudiometrieWidget()
{
}

void TonaleAudiometrieWidget::checkLG()
{
}

void TonaleAudiometrieWidget::checkBG()
{
}

void TonaleAudiometrieWidget::checkUCL()
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
	tekenLeegRaster();
	painter.drawPicture(QPoint(0, 0), m_rooster);
}

void TonaleAudiometrieWidget::tekenLeegRaster()
{
	int realWidth = static_cast<int>((width()-51)/12 + 0.5) * 12;
	int realHeight = static_cast<int>((height()-41)/29 + 0.5) * 29;

	QPainter paint;
	paint.begin(&m_rooster);

	// Teken de verticale assen
	int j = 40;
	int dB[] = {125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000};
	for (int i = 0; i < 11; ++i)
	{
		paint.setPen(Qt::black);
		paint.drawText((i < 4) ? j-6 : j-9, (i > 2  && i % 2 == 1) ? (34 + realHeight) : 12, QString::number(dB[i]));
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
			paint.drawText(15 + 6*(((22-i)/20) + (22-i <= 0 ? 0 : 1)), j + 5, QString::number((i - 2) * 5));
		}
		paint.setPen((i == 2) ? Qt::black : Qt::lightGray);
		paint.drawLine(40, j, 40 + realWidth, j);
		j += realHeight / 29;
	}
	paint.end();
}
