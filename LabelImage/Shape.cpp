#include "Shape.hpp"
#include "../utility/Constants.hpp"
#include "Lib.h"
#include <limits>
#include <QDebug>


Shape::Shape(unsigned int vertexnum, const QString label, const bool difficult, QObject * parent) : BaseShape(parent)
{
	m_maxVertexNum = vertexnum;
	m_label = label;
	setDifficult(difficult);
}

Shape::Shape(unsigned int vertexnum, const ShapeData &data)
{
	m_maxVertexNum = vertexnum;
	
	//copy points
	int len = data.points.size() >= m_maxVertexNum ? m_maxVertexNum : data.points.size();
	QPointF point;
	for (int i = 0; i < len; ++i) {
		m_points.append(data.points[i]);
	}

	m_label = data.label;
	m_lineColor = data.lineColor;
	m_fillColor = data.fillColor;
	setDifficult(data.difficult.toInt());
}

Shape::~Shape()
{
}


bool Shape::reachMaxPoints()
{
	if (m_points.size() >= 4) {
		return true;
	}

	return false;
}

void Shape::addPoint(const QPointF &point)
{
	if (!reachMaxPoints()) {
		m_points.append(point);
	}
	else {
		qDebug() << "The size of points >= 4";
	}
}

QPointF &Shape::popPoint()
{
	QPointF pf = m_points.back();
	m_points.pop_back();
	return pf;
}

BaseShape *Shape::copy()
{
	Shape *shape = new Shape(m_maxVertexNum, m_label);
	//copy m_highlightSettings
	QMap<VertexMode, VertexStruct>::const_iterator iter = m_highlightSettings.constBegin();
	while (iter != m_highlightSettings.constEnd()) {
		shape->m_highlightSettings.insert(iter.key(), iter.value());
		++iter;
	}

	//copy m_points
	for (int i = 0; i < m_points.size(); i++) {
		shape->m_points.append(m_points[i]);
	}

	shape->setFilled(getFilled());
	shape->setSelected(getSelected());
	shape->setClosed(isClosed());
	shape->setDifficult(getDifficult());

	if (m_lineColor != DEFAULT_LINE_COLOR) {
		shape->setLineColor(m_lineColor);
	}

	if (m_fillColor != DEFAULT_FILL_COLOR) {
		shape->setFillColor(m_fillColor);
	}

	return shape;
}

void Shape::highlightClear()
{
	m_highlightPointIndex = -1;
}

void Shape::highlightVertex(const int index, const VertexMode &action)
{
	m_highlightPointIndex = index;
	m_highlightMode = action;
}

bool Shape::containsPoint(const QPointF & point)
{
	return makePath().contains(point);
}

QPainterPath Shape::makePath()
{
	QPainterPath path = QPainterPath(m_points[0]);
	for (int i = 1; i < m_points.size(); i++) {
		path.lineTo(m_points[i]);
	}

	return path;
}

QRectF Shape::boundingRect()
{
	return makePath().boundingRect();
}

void Shape::moveBy(const QPointF offset)
{
	for (int i = 0; i < m_points.size(); i++) {
		m_points[i] += offset;
	}
}

void Shape::moveVertexBy(const int index, const QPointF offset)
{
	m_points[index] = m_points[index] + offset;
}

int Shape::nearestVertex(const QPointF &point, const double epsilon)
{
	for (int i = 0; i < m_points.size(); i++) {
		if (distance(m_points[i] - point) <= epsilon) {
			return i;
		}
	}
	return -1;
}

void Shape::clearPoints()
{
	m_points.clear();
}

void Shape::paint(QPainter *painter)
{
	if (m_points.size() == 0) {
		return;
	}

	QColor color = getSelected() ? m_selectLineColor : m_lineColor;
	QPen pen = QPen(color);

	pen.setWidth(qMax(1, int(qRound(2.0 / m_scale))));
	painter->setPen(pen);

	QPainterPath linepath;
	QPainterPath vrtxpath;

	linepath.moveTo(m_points[0]);

	for (int i = 0; i < m_points.size(); i++) {
		linepath.lineTo(m_points[i]);
		if (m_highlightPointIndex == i) {
			drawVertex(vrtxpath, m_points[i], true);
		}
		else{
			drawVertex(vrtxpath, m_points[i]);
		}
		
	}
	if (isClosed()) {
		linepath.lineTo(m_points[0]);
	}

	painter->drawPath(linepath);
	painter->drawPath(vrtxpath);
	painter->fillPath(vrtxpath, m_vertexFillColor);

	//draw text at the top left
	qreal min_x = INT32MAX;
	qreal min_y = INT32MAX;

	for (int i = 0; i < m_points.size(); i++) {
		min_x = qMin(min_x, m_points[i].x());
		min_y = qMin(min_y, m_points[i].y());
	}

	if (min_x != INT32MAX && min_y != INT32MAX) {
		QFont font = QFont();
		font.setPointSize(8);
		font.setBold(true);
		painter->setFont(font);
		painter->drawText(min_x, min_y, m_label);
	}

	if (getFilled()) {
		color = getSelected() ? m_selectFillColor : m_fillColor;
		painter->fillPath(linepath, color);
	}
		
}
QPointF & Shape::operator[](const unsigned int index)
{
	Q_ASSERT(m_points.size() > 0);
	return m_points[index];
}


ShapeData *Shape::extractShapeData()
{
	ShapeData * res = new ShapeData(m_points);
	res->difficult = this->getDifficult();
	res->fillColor = this->getFillColor();
	res->lineColor = this->getLineColor();
	res->label = this->getLabel();
	return res;
}

ShapeData * Shape::extractShapeData(const Shape &shape)
{
	ShapeData * res = new ShapeData(shape.getPoints());
	res->difficult = shape.getDifficult();
	res->fillColor = shape.getFillColor();
	res->lineColor = shape.getLineColor();
	res->label = shape.getLabel();
	return res;
}
