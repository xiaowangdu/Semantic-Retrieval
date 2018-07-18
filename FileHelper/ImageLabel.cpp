#include "ImageLabel.h"
#include <QIcon>
#include <QDebug>
#include <QPainter>
#include <qmath.h>
#include <QPaintEvent>

ImageLabel::ImageLabel(QWidget *parent) : QWidget(parent)
{

}

void ImageLabel::drawImage(const QPixmap& pixmap)
{
    m_pixmap = pixmap;
    repaint();
}

QSize ImageLabel::minDistance(const QSize &centre, const QList<QSize> &sizeList)
{
    QSize size;
    qreal mdis = std::numeric_limits<long long>::max();
    foreach (const QSize &s, sizeList) {
        qreal d = qPow(centre.width() - s.width(), 2) + qPow(centre.height() - s.height(), 2);
        if(d < mdis){
            size = s;
            mdis = d;
        }
    }
    return size;
}

void ImageLabel::drawIcon(const QIcon& icon)
{
    QList<QSize> sizeList = icon.availableSizes(QIcon::Normal, QIcon::On);
    QSize size = this->size();
    size = minDistance(size, sizeList);
    if(size.isValid()){
        m_pixmap = icon.pixmap(size, QIcon::Normal, QIcon::On);
    }
    else{
        m_pixmap = QPixmap();
    }
    repaint();
}

void ImageLabel::paintEvent(QPaintEvent *event)
{

    if (!m_pixmap.isNull()) {
        QPainter * p = new QPainter();
        p->begin(this);
        QRect rc = event->rect();
        p->drawPixmap(rc.x(), rc.y(), rc.width()-1, rc.height()-1, m_pixmap);
        p->end();
    }
    else{
        QWidget::paintEvent(event);
    }
}
