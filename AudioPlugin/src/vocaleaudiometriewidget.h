#ifndef __VOCALEAUDIOMETRIEWIDGET_H__
#define __VOCALEAUDIOMETRIEWIDGET_H__

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class VocaleAudiometrieWidget : public QWidget
{
	Q_OBJECT

public:
	VocaleAudiometrieWidget(QWidget *parent = 0);

	void setPenColor(const QColor &newColor);
	void setPenWidth(int newWidth);

	bool isModified() const { return modified; }
	QColor penColor() const { return myPenColor; }
	int penWidth() const { return myPenWidth; }

public slots:
	void clearImage();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);

private:
	void drawLineTo(const QPoint &endPoint);
	void resizeImage(QImage *image, const QSize &newSize);

	bool modified;
	bool scribbling;
	int myPenWidth;
	QColor myPenColor;
	QImage image;
	QPoint lastPoint;
};


#endif // __VOCALEAUDIOMETRIEWIDGET_H__
