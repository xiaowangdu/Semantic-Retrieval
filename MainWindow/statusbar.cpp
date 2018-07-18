#include "statusbar.h"
#include "../utility/Logging.hpp"
#include <QPainter>

StatusBar::StatusBar(QWidget *parent):
    QStatusBar(parent)
{

}

void StatusBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); 
    painter.setBrush(QBrush(Qt::gray));
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRect(rect);
    QStatusBar::paintEvent(event);
}
