#include "tonaleaudiometriewidget.h"

 #include <QtGui>

TonaleAudiometrieWidget::TonaleAudiometrieWidget(QWidget *parent)
    : QWidget(parent)
{
     setAttribute(Qt::WA_StaticContents);
     modified = false;
     scribbling = false;
     myPenWidth = 1;
     myPenColor = Qt::blue;
 }

 void TonaleAudiometrieWidget::setPenColor(const QColor &newColor)
 {
     myPenColor = newColor;
 }

 void TonaleAudiometrieWidget::setPenWidth(int newWidth)
 {
     myPenWidth = newWidth;
 }

 void TonaleAudiometrieWidget::clearImage()
 {
     image.fill(qRgb(255, 255, 255));
     modified = true;
     update();
 }

 void TonaleAudiometrieWidget::mousePressEvent(QMouseEvent *event)
 {
     if (event->button() == Qt::LeftButton) {
         lastPoint = event->pos();
         scribbling = true;
     }
 }

 void TonaleAudiometrieWidget::mouseMoveEvent(QMouseEvent *event)
 {
     if ((event->buttons() & Qt::LeftButton) && scribbling)
         drawLineTo(event->pos());
 }

 void TonaleAudiometrieWidget::mouseReleaseEvent(QMouseEvent *event)
 {
     if (event->button() == Qt::LeftButton && scribbling) {
         drawLineTo(event->pos());
         scribbling = false;
     }
 }

 void TonaleAudiometrieWidget::paintEvent(QPaintEvent * /* event */)
 {
     QPainter painter(this);
     painter.drawImage(QPoint(0, 0), image);
 }

 void TonaleAudiometrieWidget::resizeEvent(QResizeEvent *event)
 {
     if (width() > image.width() || height() > image.height()) {
         int newWidth = qMax(width() + 128, image.width());
         int newHeight = qMax(height() + 128, image.height());
         resizeImage(&image, QSize(newWidth, newHeight));
         update();
     }
     QWidget::resizeEvent(event);
 }

 void TonaleAudiometrieWidget::drawLineTo(const QPoint &endPoint)
 {
     QPainter painter(&image);
     painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                         Qt::RoundJoin));
     painter.drawLine(lastPoint, endPoint);
     modified = true;

     int rad = (myPenWidth / 2) + 2;
     update(QRect(lastPoint, endPoint).normalized()
                                      .adjusted(-rad, -rad, +rad, +rad));
     lastPoint = endPoint;
 }

 void TonaleAudiometrieWidget::resizeImage(QImage *image, const QSize &newSize)
 {
     if (image->size() == newSize)
         return;

     QImage newImage(newSize, QImage::Format_RGB32);
     newImage.fill(qRgb(255, 255, 255));
     QPainter painter(&newImage);
     painter.drawImage(QPoint(0, 0), *image);
     *image = newImage;
 }
