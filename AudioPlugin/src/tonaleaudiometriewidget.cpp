#include "tonaleaudiometriewidget.h"

#include <QPainter>
#include <QtGui>

TonaleAudiometrieWidget::TonaleAudiometrieWidget(QWidget *parent)
: QWidget(parent)
, m_lgData(11, -30)
, m_bgData(11, -30)
, m_uclData(11, -30)
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
	tekenData();
	painter.drawPicture(0, 0, m_rooster);
	painter.drawPicture(0, 0, m_data);
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

void TonaleAudiometrieWidget::tekenData()
{
	
}
