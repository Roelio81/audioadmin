#ifndef __VOCALEAUDIOMETRIEWIDGET_H__
#define __VOCALEAUDIOMETRIEWIDGET_H__

#include <QMap>
#include <QPicture>
#include <QVector>
#include <QWidget>

class VocaleAudiometrieWidget : public QWidget
{
	Q_OBJECT
	public:
		VocaleAudiometrieWidget(QWidget *parent = 0);
		virtual ~VocaleAudiometrieWidget();

		void setROdata(int dB, int percentage);
		void setLOdata(int dB, int percentage);
		void setROLOdata(int dB, int percentage);

		int getROdata(int dB);
		int getLOdata(int dB);
		int getROLOdata(int dB);

	public slots:
		void checkRO();
		void checkLO();
		void checkROLO();

	protected:
                virtual void mouseReleaseEvent(QMouseEvent *event);
		virtual void paintEvent(QPaintEvent *event);

	private:
		void tekenLeegRaster();
		void tekenData();

		typedef enum { RO, LO, ROLO } TekenMode;

		QVector<int> m_roData;
		QVector<int> m_loData;
		QVector<int> m_roloData;
		QPicture m_rooster;
		QPicture m_data;
		TekenMode m_tekenMode;
};

#endif // __VOCALEAUDIOMETRIEWIDGET_H__
