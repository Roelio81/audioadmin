#include "vocaleaudiometriewidget.h"

#include <QPainter>
#include <QtGui>

VocaleAudiometrieWidget::VocaleAudiometrieWidget(QWidget *parent)
: QWidget(parent)
{
}

VocaleAudiometrieWidget::~VocaleAudiometrieWidget()
{
}

void VocaleAudiometrieWidget::checkRO()
{
}

void VocaleAudiometrieWidget::checkLO()
{
}

void VocaleAudiometrieWidget::checkROLO()
{
}

void VocaleAudiometrieWidget::mouseClickEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
	}
}

void VocaleAudiometrieWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	tekenLeegRaster();
	painter.drawPicture(QPoint(0, 0), m_rooster);
}

void VocaleAudiometrieWidget::tekenLeegRaster()
{
	int realWidth = static_cast<int>((width()-51)/22 + 0.5) * 22;
	int realHeight = static_cast<int>((height()-31)/20 + 0.5) * 20;

	QPainter paint;
	paint.begin(&m_rooster);

	int j = 40;
	for (int i = 0; i < 23; ++i)
	{
		paint.setPen(Qt::black);
		if ((i % 2 == 0) && (i != 0) && (i < 20))
			paint.drawText(j-6, realHeight+25, QString::number(i*5));
		else if (i == 20)
			paint.drawText(j-9, realHeight+25, QString::number(i*5));

		paint.setPen((i == 8 || i == 11 || i == 14) ? Qt::black : Qt::lightGray); 
		paint.drawLine(j, 10, j, realHeight+10);
		j += realWidth / 22;
	}

	j = 10;
	for (int i = 0; i < 21; ++i)
	{
		if (i % 2 == 0)
		{
			paint.setPen(Qt::black);
			paint.drawText(15 + 6*((i/20) + (i == 0 ? 0 : 1)), j+6, QString::number((20-i)*5));
		}

		paint.setPen((i == 10) ? Qt::black : Qt::lightGray);
		paint.drawLine(40, j, 40 + realWidth, j);
		j += realHeight / 20;
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
