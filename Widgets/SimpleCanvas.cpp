#include "SimpleCanvas.hpp"
#include <QPainter>
#include <QWheelEvent>
#include <QDebug>

SimpleCanvas::SimpleCanvas(QWidget * parent) 
	: QWidget(parent) 
{
	m_pixmap = new QPixmap();
	m_painter = new QPainter();
}

SimpleCanvas::~SimpleCanvas() 
{
	//delete m_pixmap;
}

void SimpleCanvas::loadPixmap(const QString &fileName)
{
	if (!m_pixmap->load(fileName)) {
		qDebug() << QString("Load image {%1} failed.").arg(fileName);
	}
	m_currentImagePath = fileName;
	this->repaint();
}

QPixmap *SimpleCanvas::getPixmap() const 
{
	return m_pixmap;
}

QSize SimpleCanvas::sizeHint()const
{
	return minimumSizeHint();
}

QSize SimpleCanvas::minimumSizeHint() const
{
	if (!m_pixmap->isNull()) {
		return m_scale * m_pixmap->size();
	}
	return QWidget::minimumSizeHint();
}

void SimpleCanvas::setScale(qreal scale)
{
	m_scale = scale;
}

qreal SimpleCanvas::getScale()const
{
	return m_scale;
}

void SimpleCanvas::paintEvent(QPaintEvent *event)
{
	if (m_pixmap->isNull()) {
		return QWidget::paintEvent(event);
	}

	QPainter * p = m_painter;
	p->begin(this);
	p->setRenderHint(QPainter::Antialiasing);
	p->setRenderHint(QPainter::HighQualityAntialiasing);
	p->setRenderHint(QPainter::SmoothPixmapTransform);

	p->scale(m_scale, m_scale);
	p->translate(offsetToCenter());

	p->drawPixmap(0, 0, *m_pixmap);

	p->end();
}

void SimpleCanvas::mouseDoubleClickEvent(QMouseEvent *event)
{
	emit mouseDoubleClicked(m_currentImagePath);
}

QPointF SimpleCanvas::offsetToCenter()
{
	qreal s = m_scale;
	QSize area = size();

	qreal w = m_pixmap->width() * s, h = m_pixmap->height() * s;
	qreal aw = area.width(), ah = area.height();

	qreal x = aw > w ? (aw - w) / (2 * s) : 0.0;
	qreal y = ah > h ? (ah - h) / (2 * s) : 0.0;

	return QPoint(x, y);
}

void SimpleCanvas::wheelEvent(QWheelEvent *event)
{
	QPoint delta = event->angleDelta();
	int h_delta = delta.x();
	int v_delta = delta.y();

	Qt::KeyboardModifiers mods = event->modifiers();
	if (Qt::ControlModifier == int(mods) && v_delta) {
		emit zoomRequest(v_delta);
	}

	event->accept();
}