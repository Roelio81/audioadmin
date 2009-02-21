#ifndef __TONALEAUDIOMETRIEWIDGET_H__
#define __TONALEAUDIOMETRIEWIDGET_H__

#include <QPicture>
#include <QWidget>

class TonaleAudiometrieWidget : public QWidget
{
	Q_OBJECT
	public:
		TonaleAudiometrieWidget(QWidget *parent = 0);
		virtual ~TonaleAudiometrieWidget();

	public slots:
		void checkLG();
		void checkBG();
		void checkUCL();

	protected:
		virtual void mouseClickEvent(QMouseEvent *event);
		virtual void paintEvent(QPaintEvent *event);

	private:
		void tekenLeegRaster();

		QPicture m_rooster;
};


#endif // __TONALEAUDIOMETRIEWIDGET_H__
