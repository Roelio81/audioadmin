#ifndef __VOCALEAUDIOMETRIEWIDGET_H__
#define __VOCALEAUDIOMETRIEWIDGET_H__

#include <QPicture>
#include <QWidget>

class VocaleAudiometrieWidget : public QWidget
{
	Q_OBJECT
	public:
		VocaleAudiometrieWidget(QWidget *parent = 0);
		virtual ~VocaleAudiometrieWidget();

	public slots:
		void checkRO();
		void checkLO();
		void checkROLO();

	protected:
		virtual void mouseClickEvent(QMouseEvent *event);
		virtual void paintEvent(QPaintEvent *event);

	private:
		void tekenLeegRaster();

		QPicture m_rooster;
};


#endif // __VOCALEAUDIOMETRIEWIDGET_H__
