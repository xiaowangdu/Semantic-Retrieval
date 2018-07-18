#include "Canvas.hpp"
#include "Lib.h"
#include "../utility/UMath.h"
#include "../Common/Exception.hpp"
#include <QApplication>
#include <QWheelEvent>
#include <math.h>
#include <QLabel>
#include "LabelImage.h"
#include "UiManager.hpp"

#define DEBUG 1
#define DEBUG_RETURN if(DEBUG) {return;}

Canvas::Canvas(QWidget * parent) 
	: QWidget(parent)
	, m_currentBoxShape(NULL), m_selectedBoxShape(NULL), m_selectedBoxShapeCopy(NULL)
	, m_hoveredShape(NULL)
	, m_offsets(QPointF(), QPointF())
	, m_menus()
{
	m_loader = parent;

	m_pixmap = new QPixmap();

	m_drawingLineColor = QColor(0, 0, 255);
	m_drawingRectColor = QColor(0, 0, 255);

	m_lineShape = new Shape(LINE); // new a line shape
	m_lineShape->setFillColor(m_drawingLineColor);

	m_painter = new QPainter();

	m_menus.first = new QMenu();
	m_menus.second = new QMenu();

	setMouseTracking(true);
	setFocusPolicy(Qt::WheelFocus);

	m_cursor = QCursor(CURSOR_DEFAULT);
	//QApplication::setOverrideCursor(m_cursor);

	//for test
	//QPoint a(0, 0), b(0, 100), c(100, 100), d(80, 110), e(50, 90), f(100, 0);
	//QVector<QPoint> p;
	//p.append(a);
	//p.append(b);
	//p.append(c);
	//p.append(d);
	//p.append(e);
	//p.append(f);
	//ShapeData s(p);
	//m_currentBoxShape = new Shape(BOX, s);


}

Canvas::~Canvas() {

}

void Canvas::loadPixmap(QPixmap &pixmap)
{
	//clear last pixmap.
	if (m_pixmap != NULL) {
		delete m_pixmap;
		m_pixmap = NULL;
	}
	m_pixmap = new QPixmap(pixmap);
	clearAllShapes();
	this->repaint();
}

void Canvas::loadPixmap(const QString &fileName)
{
	Q_ASSERT(m_pixmap != NULL);
	m_pixmap->load(fileName);
	clearAllShapes();
	this->repaint();
}

void Canvas::loadShapes(const QVector<Shape *> shapes)
{
	m_boxShapes = shapes;
	m_currentBoxShape = NULL;
	this->repaint();
}

QPixmap *Canvas::getPixmap()const
{
	return m_pixmap;
}

QSize Canvas::sizeHint()const
{
	return minimumSizeHint();
}

QSize Canvas::minimumSizeHint() const
{
	if (!m_pixmap->isNull()) {
		return m_scale * m_pixmap->size();
	}
	return QWidget::minimumSizeHint();
}

void Canvas::setDrawingColor(const QColor &color)
{
	m_drawingLineColor = color;
	m_drawingRectColor = color;
}

bool Canvas::isVisible(Shape *const shape)
{
	if (m_visible.count(shape) <= 0) {
		return true;
	}

	return m_visible[shape];
}

bool Canvas::drawing()const
{
	return m_mode == CREATE;
}

bool Canvas::editing()const
{
	return m_mode == EDIT;
}

void Canvas::setEditing(const bool value)
{
	m_mode = value ? EDIT : CREATE;
	if (!value) {
		unHighlight();
		deSelectShape();
	}

	m_prevPoint = QPointF();
	repaint();
}

void Canvas::unHighlight()
{
	if (m_hoveredShape) {
		m_hoveredShape->highlightClear();
	}
	m_hVertexIndex = -1;

	//delete m_hShape;
	m_hoveredShape = NULL;
}

void Canvas::deSelectShape()
{
	if (m_selectedBoxShape) {
		m_selectedBoxShape->setSelected(false);
		m_selectedBoxShape = NULL;

		setHiding(false);
		emit selectionChanged(false);
		update();
	}
}

void Canvas::setHiding(const bool value)
{
	m_hideBackround = value;
}

Shape * Canvas::deleteSelected()
{
	Shape * p = NULL;
	if (m_selectedBoxShape) {
		p = m_selectedBoxShape;
		//self.shapes.remove(self.selectedShape)
		m_selectedBoxShape = NULL;

		update();
	}
	return p;
}

Shape * Canvas::copySelectedShape()
{
	Shape * p = NULL;
	if (m_selectedBoxShape) {
		p = (Shape *)(m_selectedBoxShape->copy());
		deSelectShape();
		m_boxShapes.append(p);

		p->setSelected(true);
		m_selectedBoxShape = p;

		boundedShiftShape(p);
	}
	return p;
}

void Canvas::boundedShiftShape(Shape * shape)
{
	Q_ASSERT(shape != NULL);
	QPointF point = (*shape)[0];

	calculateOffsets(*shape, point);
	m_prevPoint = point;

	QPointF ofs(2.0, 2.0);
	if (!boundedMoveShape(*shape, point - ofs)) {
		boundedMoveShape(*shape, point + ofs);
	}
}

void Canvas::selectShape(Shape * const shape)
{
	deSelectShape();
	shape->setSelected(true);

	m_selectedBoxShape = shape;
	setHiding(false);

	emit selectionChanged(true);
	update();
}

Shape *Canvas::getSelectedShape()const
{
	return m_selectedBoxShape;
}

void Canvas::selectShapePoint(const QPointF &point)
{
	deSelectShape();
	if (selectedVertex()) {
		Q_ASSERT(m_hoveredShape != NULL);
		m_hoveredShape->highlightVertex(m_hVertexIndex, MOVE_VERTEX);
		selectShape(m_hoveredShape);
		return;
	}

	for (int i = m_boxShapes.size() - 1; i >= 0; i--) {
		if (isVisible(m_boxShapes[i]) && m_boxShapes[i]->containsPoint(point)) {
			selectShape(m_boxShapes[i]);
			calculateOffsets(*(m_boxShapes[i]), point);
			return;
		}
	}
}

void Canvas::calculateOffsets(Shape & s, const QPointF & point)
{
	QRectF rect = s.boundingRect();
	qreal x1 = rect.x() - point.x();
	qreal y1 = rect.y() - point.y();

	qreal x2 = (rect.x() + rect.width()) - point.x();
	qreal y2 = (rect.y() + rect.height()) - point.y();

	m_offsets.first = QPointF(x1, y1);
	m_offsets.second = QPointF(x2, y2);
}

bool Canvas::outOfPixmap(const QPointF &p)
{
	qreal w = m_pixmap->width();
	qreal h = m_pixmap->height();
	return !((0 <= p.x() && p.x() <= w) && (0 <= p.y() && p.y() <= h));
}

bool Canvas::boundedMoveShape(Shape & shape, const QPointF & pos)
{
	if (outOfPixmap(pos)) {
		return false;
	}

	QPointF p = pos;
	QPointF o1 = p + m_offsets.first;
	if (outOfPixmap(o1)) {
		p -= QPointF(qMin(0.0, o1.x()), qMin(0.0, o1.y()));
	}

	QPointF o2 = p + m_offsets.second;
	if (outOfPixmap(o2)) {
		p += QPointF(qMin(0.0, m_pixmap->width() - o2.x()), qMin(0.0, m_pixmap->height() - o2.y()));
	}

	QPointF dp = p - m_prevPoint;
	if (!dp.isNull()) {
		shape.moveBy(dp);
		m_prevPoint = p;
		return true;
	}

	return false;
}

void Canvas::boundedMoveVertex(const QPointF & pos)
{
	int index = m_hVertexIndex;
	QPointF point = (*m_hoveredShape).getPoints()[index];
	QPointF p = pos;
	if (outOfPixmap(pos)) {
		p = intersectionPoint(point, pos);
	}

	QPointF shiftPos = p - point;
	(*m_hoveredShape).moveVertexBy(index, shiftPos);

	int lindex = (index + 1) % 4;
	int rindex = (index + 3) % 4;

	QPointF lshift;
	QPointF rshift;

	if (index % 2 == 0) {
		rshift = QPointF(shiftPos.x(), 0);
		lshift = QPointF(0, shiftPos.y());
	}
	else {
		lshift = QPointF(shiftPos.x(), 0);
		rshift = QPointF(0, shiftPos.y());
	}
	(*m_hoveredShape).moveVertexBy(rindex, rshift);
	(*m_hoveredShape).moveVertexBy(lindex, lshift);

}

Shape * Canvas::setLastLabel(const QString &text, const QColor &linecolor, const QColor & fillcolor)
{
	Q_ASSERT(!text.isEmpty());

	m_boxShapes.last()->setLabel(text);
	if (linecolor.isValid()) {
		m_boxShapes.last()->setLineColor(linecolor);
	}
	if (fillcolor.isValid()) {
		m_boxShapes.last()->setFillColor(fillcolor);
	}

	return m_boxShapes.last();
}

bool Canvas::closeEnough(const QPointF &p1, const QPointF &p2)
{
	return distance(p1 - p2) < m_epsilon;
}

QPointF & Canvas::intersectionPoint(const QPointF & p1, const QPointF & p2)
{
	QSize size = m_pixmap->size();
	QVector<QPointF> points;
	points.append(QPointF(0, 0));
	points.append(QPointF(size.width(), 0));
	points.append(QPointF(size.width(), size.height()));
	points.append(QPointF(0, size.height()));

	qreal x1 = p1.x(), y1 = p1.y();
	qreal x2 = p2.x(), y2 = p2.y();

	QVector<qreal> mx = intersectingEdges(p1, p2, points);

	int maxindex = int(mx[1]);
	qreal x = mx[2], y = mx[3];

	qreal x3 = points[maxindex].x(), y3 = points[maxindex].y();
	qreal x4 = points[(maxindex + 1) % 4].x();
	qreal y4 = points[(maxindex + 1) % 4].y();
	if (x == x1 && y == y1) {
		if (x3 == x4) {
			return QPointF(x3, qMin(qMax(0.0, y2), qMax(y3, y4)));
		}
		else {
			return QPointF(qMin(qMax(0.0, x2), qMax(x3, x4)), y3);
		}
	}

	return QPointF(x, y);
}

QVector<qreal> Canvas::intersectingEdges(const QPointF &x1y1, const QPointF &x2y2, QVector<QPointF> &points)
{
	//QVector<QVector<qreal>> res;
	QVector<qreal> res;
	qreal tmp_d = INT64MAX;

	const int RANGE = 4;
	qreal x1 = x1y1.x(), y1 = x1y1.y();
	qreal x2 = x2y2.x(), y2 = x2y2.y();
	qreal x3, y3, x4, y4;

	for (int i = 0; i < RANGE; i++) {
		x3 = points[i].x(), y3 = points[i].y();
		x4 = points[(i + 1) % 4].x();
		y4 = points[(i + 1) % 4].y();

		qreal denom = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
		qreal nua = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
		qreal nub = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
		
		if (denom == 0.0) {
			continue;
		}

		qreal ua = nua / denom, ub = nub / denom;
		if ((0.0 <= ua && ua <= 1.0) && (0.0 <= ub && ub <= 1.0)) {
			
			qreal x = x1 + ua * (x2 - x1);
			qreal y = y1 + ua * (y2 - y1);
			
			QPointF m = QPointF((x3 + x4) / 2, (y3 + y4) / 2);
			qreal d = distance(m - QPointF(x2, y2));

			if (tmp_d > d) {
				res.append(d); res.append(i);
				res.append(x); res.append(y);
			}
		}
	}

	if (res.size() <= 0) {
		return QVector<qreal>(4, 0.0);
	}
	
	return res;
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
	QPointF pos = transformPos(event->pos());
	emit mousePositionChanged(int(pos.x()), int(pos.y()));

	if (drawing()) {
		overrideCursor(CURSOR_DRAW);
		if (m_currentBoxShape) {
			QColor color = m_drawingLineColor;
			if (outOfPixmap(pos)) {
				QVector<QPointF> p = m_currentBoxShape->getPoints();
				pos = intersectionPoint(p.last(), pos);

			}
			else if (m_currentBoxShape->getPoints().size() > 1 && closeEnough(pos, (*m_currentBoxShape)[0])) {
				pos = (*m_currentBoxShape)[0];
				color = (*m_currentBoxShape).getLineColor();
				overrideCursor(CURSOR_POINT);
				m_currentBoxShape->highlightVertex(0, NEAR_VERTEX);
			}

			(*m_lineShape)[1] = pos;
			(*m_lineShape).setLineColor(color);
			m_prevPoint = QPointF();
			(*m_currentBoxShape).highlightClear();
		}
		else {
			m_prevPoint = pos;
		}

		repaint();
		return;
	}

	// Polygon copy moving.
	if (Qt::RightButton & event->buttons()) {
		if (m_selectedBoxShapeCopy && m_prevPoint.isNull()) {
			overrideCursor(CURSOR_MOVE);
			boundedMoveShape(*m_selectedBoxShapeCopy, pos);
			repaint();
		}
		else if (m_selectedBoxShape) {
			m_selectedBoxShapeCopy = (Shape *)(m_selectedBoxShape->copy());
			repaint();
		}
		return;
	}

	//Polygon/Vertex moving.
	if (Qt::LeftButton & event->buttons()) {
		if (selectedVertex()) {
			boundedMoveVertex(pos);
			emit shapeMoved();
			repaint();
		}
		else if (m_selectedBoxShape && !m_prevPoint.isNull()) {
			overrideCursor(CURSOR_MOVE);
			boundedMoveShape(*m_selectedBoxShape, pos);
			emit shapeMoved();
			repaint();
		}
		return;
	}

	//
	setToolTip("Image");
	for (int i = m_boxShapes.size() - 1; i >= 0; i--) {
		if (!isVisible(m_boxShapes[i])) {
			continue;
		}

		int index = (*m_boxShapes[i]).nearestVertex(pos, m_epsilon);
		if (index != -1) {
			if (selectedVertex()) {
				m_hoveredShape->highlightClear();
			}
			m_hVertexIndex = index;
			m_hoveredShape = m_boxShapes[i];
			m_boxShapes[i]->highlightVertex(index, MOVE_VERTEX);
			overrideCursor(CURSOR_POINT);
			setToolTip("Click & drag to move point");
			setStatusTip(toolTip());
			update();
			break;

		}
		else if ((*m_boxShapes[i]).containsPoint(pos)) {
			if (selectedVertex()) {
				m_hoveredShape->highlightClear();
			}
			m_hVertexIndex = index;
			m_hoveredShape = m_boxShapes[i];

			setToolTip(QString("Click & drag to move shape '%1'").arg(m_boxShapes[i]->getLabel()));
			setStatusTip(toolTip());
			overrideCursor(CURSOR_GRAB);
			update();
			break;
		}
		else if (i == 0) {
			if (m_hoveredShape) {
				m_hoveredShape->highlightClear();
				update();
				//delete m_hShape;
				m_hoveredShape = NULL;
			}
			m_hVertexIndex = -1;
			overrideCursor(CURSOR_DEFAULT);
		}
	}

}

void Canvas::mousePressEvent(QMouseEvent *event)
{
	QPointF pos = transformPos(event->pos());
	if (event->button() == Qt::LeftButton) {
		if (drawing()) {
			handleDrawing(pos);
		}
		else {
			selectShapePoint(pos);
			m_prevPoint = pos;
			repaint();
		}
	}
	else if (event->button() == Qt::RightButton && editing()) {
		selectShapePoint(pos);
		m_prevPoint = pos;
		repaint();
	}
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton) {
		QMenu * menu = bool(m_selectedBoxShapeCopy)? m_menus.second : m_menus.first;
		restoreCursor();
		if (!menu->exec(mapToGlobal(event->pos())) && m_selectedBoxShapeCopy) {
			m_selectedBoxShapeCopy = NULL;
			repaint();
		}
	}
	else if (event->button() == Qt::LeftButton && m_selectedBoxShape) {
		if (selectedVertex()) {
			overrideCursor(CURSOR_POINT);
		}
		else {
			overrideCursor(CURSOR_GRAB);
		}
	}
	else if (event->button() == Qt::LeftButton) {
		QPointF pos = transformPos(event->pos());
		if (drawing()) {
			handleDrawing(pos);
		}
	}
	
}

void Canvas::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (canCloseShape() && m_currentBoxShape->getPoints().size() > 3) {
		(*m_currentBoxShape).popPoint();
		finalise();
	}
}

void Canvas::paintEvent(QPaintEvent *event)
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
	//Shape.scale = self.scale

	
	for (int i = 0; i < m_boxShapes.size(); i++) {
		//qDebug() << "------>>>>>>>" << !m_hideBackround << isVisible(m_boxShapes[i]);
		if ((m_boxShapes[i]->getSelected() || !m_hideBackround) && isVisible(m_boxShapes[i])) {
			//qDebug() << "-------------------------->>>>>>>>>>>>";
			m_boxShapes[i]->setFilled(m_boxShapes[i]->getSelected()|| m_boxShapes[i] == m_hoveredShape);
			m_boxShapes[i]->paint(p);
		}
	}

	if (m_currentBoxShape && m_lineShape) {
		m_currentBoxShape->paint(p);
		m_lineShape->paint(p);
	}
	if (m_selectedBoxShapeCopy) {
		m_selectedBoxShapeCopy->paint(p);
	}

	//Paint rect
	if (m_currentBoxShape && m_lineShape->getPoints().size() == 2) {
		QPointF leftTop = m_lineShape->getPoints()[0];
		QPointF rightBottom = m_lineShape->getPoints()[1];
		qreal rectWidth = rightBottom.x() - leftTop.x();
		qreal rectHeight = rightBottom.y() - leftTop.y();
		p->setPen(m_drawingRectColor);

		QBrush brush = QBrush(Qt::BDiagPattern);
		p->setBrush(brush);
		p->drawRect(leftTop.x(), leftTop.y(), rectWidth, rectHeight);
	}

	//draw '+' 
	if (drawing() && !m_prevPoint.isNull() && !outOfPixmap(m_prevPoint)) {
		p->setPen(QColor(0, 0, 255));
		p->drawLine(m_prevPoint.x(), 0, m_prevPoint.x(), m_pixmap->height());
		p->drawLine(0, m_prevPoint.y(), m_pixmap->width(), m_prevPoint.y());
	}

	setAutoFillBackground(true);
	QPalette pal = palette();
	if (getVerified()) {
		pal.setColor(backgroundRole(), QColor(184, 239, 38, 128));
	}
	else {
		pal.setColor(backgroundRole(), QColor(232, 232, 232, 255));	
	}
	setPalette(pal);

	p->end();
}

void Canvas::enterEvent(QEvent *event)
{
	overrideCursor(m_cursor);
}

void Canvas::leaveEvent(QEvent *event)
{
	restoreCursor();
}

void Canvas::focusOutEvent(QFocusEvent *event)
{
	restoreCursor();
}

void Canvas::wheelEvent(QWheelEvent *event)
{
	QPoint delta = event->angleDelta();
	int h_delta = delta.x();
	int v_delta = delta.y();

	Qt::KeyboardModifiers mods = event->modifiers();
	if (Qt::ControlModifier == int(mods) && v_delta) {
		emit zoomRequest(v_delta);
	}
	else {
		if(v_delta) emit scrollRequest(v_delta, Qt::Vertical);
		if(h_delta) emit scrollRequest(h_delta, Qt::Horizontal);
	}

	event->accept();
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
	int key = event->key();
	if (key == Qt::Key_Escape && m_currentBoxShape) {
		m_currentBoxShape = NULL;
		emit drawingPolygon(false);
		update();
	}
	else if (key == Qt::Key_Return && canCloseShape()) {
		finalise();
	}
	else if (key == Qt::Key_Left && m_selectedBoxShape) {
		moveOnePixel("Left");
	}
	else if (key == Qt::Key_Right && m_selectedBoxShape) {
		moveOnePixel("Right");
	}
	else if (key == Qt::Key_Up && m_selectedBoxShape) {
		moveOnePixel("Up");
	}
	else if (key == Qt::Key_Down && m_selectedBoxShape) {
		moveOnePixel("Down");
	}
}

//clear memory
void Canvas::clearAllShapes()
{
	//QVector<BoxShape *> m_boxShapes;

	for (int i = 0; i < m_boxShapes.size(); i++) {
		if (m_boxShapes[i] != NULL) {
			delete m_boxShapes[i];
			m_boxShapes[i] = NULL;
		}
	}

	m_boxShapes.clear();
}

void Canvas::clearShape(Shape *const shape)
{
	Q_ASSERT(shape != NULL);
	QVector<Shape *>::iterator iter;

	for (iter = m_boxShapes.begin(); iter != m_boxShapes.end(); ++iter) {
		if (shape == *iter) {
			delete *iter;
			m_boxShapes.erase(iter);
			break;
		}
	}

	try {
		assertNoRepeatShapeWith(shape);
	}
	catch (MemoryException &e) {
		e.raise();
	}
}

void Canvas::setScale(qreal sclae)
{
	m_scale = sclae;
}

qreal Canvas::getScale()const
{
	return m_scale;
}

void Canvas::restoreCursor()
{
	QApplication::restoreOverrideCursor();
}

void Canvas::resetAllLines()
{
	if (m_boxShapes.size() <= 0) {
		return;
	}
	m_currentBoxShape = m_boxShapes.last();
	m_boxShapes.removeLast();
	m_currentBoxShape->setOpen();
	//self.line.points = [self.current[-1], self.current[0]];
	emit drawingPolygon(true);
	delete m_currentBoxShape;
	m_currentBoxShape = NULL;
	emit drawingPolygon(false);
	update();
}

QCursor *Canvas::currentCursor()
{
	return QApplication::overrideCursor();
}

void Canvas::overrideCursor(const QCursor &cursor)
{
	m_cursor = cursor;
	if (currentCursor()) {
		QApplication::setOverrideCursor(cursor);
	}
	else {
		QApplication::changeOverrideCursor(cursor);
	}
}

void Canvas::moveOnePixel(const QString &direction)
{
	if (direction == "Left" && !moveOutOfBound(QPointF(-1.0, 0))) {
		m_selectedBoxShape->getPoints()[0] += QPointF(-1.0, 0);
		m_selectedBoxShape->getPoints()[1] += QPointF(-1.0, 0);
		m_selectedBoxShape->getPoints()[2] += QPointF(-1.0, 0);
		m_selectedBoxShape->getPoints()[3] += QPointF(-1.0, 0);
	}
	else if (direction == "Right" && !moveOutOfBound(QPointF(1.0, 0))) {
		m_selectedBoxShape->getPoints()[0] += QPointF(1.0, 0);
		m_selectedBoxShape->getPoints()[1] += QPointF(1.0, 0);
		m_selectedBoxShape->getPoints()[2] += QPointF(1.0, 0);
		m_selectedBoxShape->getPoints()[3] += QPointF(1.0, 0);
	}
	else if (direction == "Up" && !moveOutOfBound(QPointF(0, -1.0))) {
		m_selectedBoxShape->getPoints()[0] += QPointF(0, -1.0);
		m_selectedBoxShape->getPoints()[1] += QPointF(0, -1.0);
		m_selectedBoxShape->getPoints()[2] += QPointF(0, -1.0);
		m_selectedBoxShape->getPoints()[3] += QPointF(0, -1.0);
	}
	else if (direction == "Down" && !moveOutOfBound(QPointF(0, 1.0))) {
		m_selectedBoxShape->getPoints()[0] += QPointF(0, 1.0);
		m_selectedBoxShape->getPoints()[1] += QPointF(0, 1.0);
		m_selectedBoxShape->getPoints()[2] += QPointF(0, 1.0);
		m_selectedBoxShape->getPoints()[3] += QPointF(0, 1.0);
	}

	emit shapeMoved();
	repaint();
}

bool Canvas::moveOutOfBound(const QPointF &step)
{
	QVector<QPointF> points = m_selectedBoxShape->getPoints();
	for (int i = 0; i < points.size(); i++) {
		QPointF p = points[i] + step;
		if (outOfPixmap(p)) {
			return true;
		}
	}
	return false;
}

bool Canvas::selectedVertex()
{
	return m_hVertexIndex != -1 ? true : false;
}

QPointF Canvas::transformPos(const QPointF &point)
{
	return point / m_scale - offsetToCenter();
}

QPointF Canvas::offsetToCenter()
{
	qreal s = m_scale;
	QSize area = QWidget::size();
	
	qreal w = m_pixmap->width() * s, h = m_pixmap->height() * s;
	qreal aw = area.width(), ah = area.height();

	//map to draw coordinate system
	qreal x = aw > w ? ((aw - w) / 2) / s : 0.0;
	qreal y = ah > h ? ((ah - h) / 2) / s : 0.0;

	return QPointF(x, y);
}

void Canvas::finalise()
{
	Q_ASSERT(m_currentBoxShape != NULL);
	QVector<QPointF> p = m_currentBoxShape->getPoints();
	int size = p.size();
	if (p[0] == p[size-1]) {
		m_currentBoxShape = NULL;
		emit drawingPolygon(false);
		update();
		return;
	}

	m_currentBoxShape->setClose();
	m_boxShapes.append(m_currentBoxShape);
	m_currentBoxShape = NULL;
	setHiding(false);
	emit newShape();
	update();
}

bool Canvas::canCloseShape()
{
	return drawing() && (m_currentBoxShape != NULL) && m_currentBoxShape->size() > 2;
}

void Canvas::endMove(const bool copy)
{
	Q_ASSERT(m_selectedBoxShape != NULL && m_selectedBoxShapeCopy != NULL);
	Shape * shape = m_selectedBoxShapeCopy;
	if (copy) {
		m_boxShapes.append(shape);
		m_selectedBoxShape->setSelected(false);
		m_selectedBoxShape = shape;
		repaint();
	}
	else {
		for (int i = 0; i < shape->getPoints().size(); i++) {
			m_selectedBoxShape->addPoint(shape->getPoints().at(i));
		}
	}

	m_selectedBoxShapeCopy = NULL;
}

void Canvas::hideBackroundShapes(const bool value)
{
	m_hideBackround = value;
	if (m_selectedBoxShape != NULL) {
		setHiding(true);
		repaint();
	}
}

void Canvas::handleDrawing(const QPointF &pos)
{
	if (m_currentBoxShape != NULL && !m_currentBoxShape->reachMaxPoints()) {
		QPointF initPos = (*m_currentBoxShape)[0];
		qreal minX = initPos.x();
		qreal minY = initPos.y();

		QPointF targetPos = (*m_lineShape)[1];
		qreal maxX = targetPos.x();
		qreal maxY = targetPos.y();

		m_currentBoxShape->addPoint(QPointF(maxX, minY));
		m_currentBoxShape->addPoint(targetPos);
		m_currentBoxShape->addPoint(QPointF(minX, maxY));
		finalise();

		qDebug() << "handleDrawing>>>>>>>>>>>>>>>>>>>>>>";
	}
	else if (!outOfPixmap(pos)) {
		qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
		m_lineShape->clearPoints();
		m_currentBoxShape = new Shape(BOX);
		m_currentBoxShape->addPoint(pos);

		m_lineShape->addPoint(pos);
		m_lineShape->addPoint(pos);

		setHiding(false);
		emit drawingPolygon(true);
		update();
	}
}

void Canvas::assertNoRepeatShapeWith(Shape *shape)
{
	for (int i = 0; i < m_boxShapes.size(); i++) {
		if (m_boxShapes[i] == shape) {
			throw new MemoryException("The shape may be have more than one reference.", this);
		}
	}
}

void Canvas::resetState()
{
	restoreCursor();
	
	if (!m_pixmap->isNull()) {
		delete m_pixmap;
		m_pixmap = new QPixmap();
	}
	update();
}

void Canvas::setShapeVisible(Shape *shape, bool value)
{
	m_visible.insert(shape, value);
	repaint();
}

QVector<Shape *> Canvas::getShapes() const
{
	return m_boxShapes;
}