#include "RetrievalShowItem.hpp"
#include <QPainter>
#include <QResizeEvent>
#include <QDebug>

using namespace RetrievalCanvas;

RetrievalShowItem::RetrievalShowItem(QWidget * parent)
	: SimpleCanvas(parent)
{
	m_painter = new QPainter();

}

RetrievalShowItem::~RetrievalShowItem()
{
	delete m_painter;
}

bool RetrievalShowItem::selected() const
{
	return m_selected;
}

void RetrievalShowItem::setSelected(bool state)
{
	m_selected = state;
}

void RetrievalShowItem::paintEvent(QPaintEvent *event)
{
	QSize size = event->rect().size();
	setScale(caculateScale(size));

	SimpleCanvas::paintEvent(event);

	QPainter * p = m_painter;
	p->begin(this);
	if (selected()) {
		QBrush brush = QBrush(QColor(125, 225, 0, 50));
		p->setBrush(brush);
		QRect r = event->rect();
		r.setWidth(r.width() - 1);
		r.setHeight(r.height() - 1);
		p->drawRect(r);
	}

	if (hovered) {
		QBrush brush = QBrush(QColor(125, 125, 0, 50));
		p->setBrush(brush);
		QRect r = event->rect();
		r.setWidth(r.width() - 1);
		r.setHeight(r.height() - 1);
		p->drawRect(r);
	}
	p->end();

}

qreal RetrievalShowItem::caculateScale(const QSize cansize)
{
	QSize sizeimg = sizeHint() / getScale();
	QSize sizeican = cansize;

	QSize offset = (sizeican - sizeimg) / 2;

	qreal scale = 1.0;
	qreal w = offset.width();
	qreal h = offset.height();

	if (w < 0 && h < 0) {
		scale = abs(w) > abs(h) ? (qreal)sizeican.width() / (qreal)sizeimg.width() : (qreal)sizeican.height() / (qreal)sizeimg.height();
	}
	else if (w < 0 && h >= 0) {
		scale = (qreal)sizeican.width() / (qreal)sizeimg.width();
	}
	else if (w >= 0 && h < 0) {
		scale = (qreal)sizeican.height() / (qreal)sizeimg.height();
	}

	return scale;
}

void RetrievalShowItem::enterEvent(QEvent *event)
{
	hovered = true;
	repaint();
}

void RetrievalShowItem::leaveEvent(QEvent *event)
{
	hovered = false;
	repaint();
}