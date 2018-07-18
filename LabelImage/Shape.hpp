#pragma once
#include "../Common/BaseShapeData.hpp"
#include "../Common/BaseShape.hpp"
#include "../utility/MacroDef.h"

//define shape data struct.
class ShapeData : public BaseShapeData {
public:
	ShapeData() {}
	ShapeData(const QVector<QPointF> &points_) : BaseShapeData(points_) {}
	ShapeData(const QVector<QPoint> &points_) : BaseShapeData(points_) {}

	~ShapeData() {}

private:

};

class Shape : private BaseShape {

	DEFINE_CLASS_PROPERTY_DEFAULT(bool, Filled, false);
	DEFINE_CLASS_PROPERTY_DEFAULT(bool, Selected, false);
	DEFINE_CLASS_PROPERTY_DEFAULT(bool, Difficult, false);

public:
	Shape(unsigned int vertexnum, const QString label = "", const bool difficult = false, QObject * parent = Q_NULLPTR);
	Shape(unsigned int vertexnum, const ShapeData &data);
	~Shape();

	void setLineColor(const QColor &color) { m_lineColor = color; }
	QColor getLineColor() const { return m_lineColor; }
	void setFillColor(const QColor &color) { m_fillColor = color; }
	QColor getFillColor() const { return m_fillColor; }
	void setSelectLineColor(const QColor &color) { m_selectLineColor = color; }
	QColor getSelectLineColor() const { return m_selectLineColor; }
	void setSelectFillColor(const QColor &color) { m_selectFillColor = color; }
	QColor getSelectFillColor() const { return m_selectFillColor; }
	void setLabel(const QString &label) { m_label = label; }
	QString getLabel() const { return m_label; }
	QVector<QPointF> getPoints() const{ return m_points; }
	ShapeData *extractShapeData();
	static ShapeData * extractShapeData(const Shape &shape);

	void setClose() { m_isClosed = true; }
	void setOpen() { m_isClosed = false; }
	bool isClosed() const { return m_isClosed; }
	void setClosed(const bool &c) { m_isClosed = c; }
	bool reachMaxPoints();
	void addPoint(const QPointF &point);
	QPointF &popPoint();
	int size()const { return m_points.size(); }
	void highlightClear();
	void highlightVertex(const int index, const VertexMode &action);
	bool containsPoint(const QPointF & point);
	QPainterPath makePath();
	QRectF boundingRect();
	void moveBy(const QPointF offset);
	void moveVertexBy(const int index, const QPointF offset);
	int nearestVertex(const QPointF &point, const double epsilon);
	void clearPoints();

	virtual BaseShape *copy();

	void paint(QPainter *painter);

	QPointF & operator[](const unsigned int index);

private:
	QString m_label;
	bool m_isClosed = false;
	unsigned int m_maxVertexNum = 1;
	//VertexShape m_pointType = P_ROUND;

private:
	DISABLE_COPY(Shape);

};

