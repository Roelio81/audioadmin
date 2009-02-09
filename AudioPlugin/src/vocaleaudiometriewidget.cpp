#include "vocaleaudiometriewidget.h"

 #include <QtGui>

 VocaleAudiometrieWidget::VocaleAudiometrieWidget(QWidget *parent)
     : QWidget(parent)
 {
     setAttribute(Qt::WA_StaticContents);
     modified = false;
     scribbling = false;
     myPenWidth = 1;
     myPenColor = Qt::blue;
 }

 void VocaleAudiometrieWidget::setPenColor(const QColor &newColor)
 {
     myPenColor = newColor;
 }

 void VocaleAudiometrieWidget::setPenWidth(int newWidth)
 {
     myPenWidth = newWidth;
 }

 void VocaleAudiometrieWidget::clearImage()
 {
     image.fill(qRgb(255, 255, 255));
     modified = true;
     update();
 }

 void VocaleAudiometrieWidget::mousePressEvent(QMouseEvent *event)
 {
     if (event->button() == Qt::LeftButton) {
         lastPoint = event->pos();
         scribbling = true;
     }
 }

 void VocaleAudiometrieWidget::mouseMoveEvent(QMouseEvent *event)
 {
     if ((event->buttons() & Qt::LeftButton) && scribbling)
         drawLineTo(event->pos());
 }

 void VocaleAudiometrieWidget::mouseReleaseEvent(QMouseEvent *event)
 {
     if (event->button() == Qt::LeftButton && scribbling) {
         drawLineTo(event->pos());
         scribbling = false;
     }
 }

 void VocaleAudiometrieWidget::paintEvent(QPaintEvent * /* event */)
 {
     QPainter painter(this);
     painter.drawImage(QPoint(0, 0), image);
 }

 void VocaleAudiometrieWidget::resizeEvent(QResizeEvent *event)
 {
     if (width() > image.width() || height() > image.height()) {
         int newWidth = qMax(width() + 128, image.width());
         int newHeight = qMax(height() + 128, image.height());
         resizeImage(&image, QSize(newWidth, newHeight));
         update();
     }
     QWidget::resizeEvent(event);
 }

 void VocaleAudiometrieWidget::drawLineTo(const QPoint &endPoint)
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

 void VocaleAudiometrieWidget::resizeImage(QImage *image, const QSize &newSize)
 {
     if (image->size() == newSize)
         return;

     QImage newImage(newSize, QImage::Format_RGB32);
     newImage.fill(qRgb(255, 255, 255));
     QPainter painter(&newImage);
     painter.drawImage(QPoint(0, 0), *image);
     *image = newImage;
 }
