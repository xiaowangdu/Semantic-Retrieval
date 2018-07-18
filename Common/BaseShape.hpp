#pragma once
#include <QObject>
#include <QVector>
#include <QMap>
#include <QColor>
#include <QPainter>


enum VertexMode {
	MOVE_VERTEX, NEAR_VERTEX
};

enum VertexShape {
	P_SQUARE, P_ROUND
};

struct VertexStruct {
public:
	qreal size;
	VertexMode mode;
	VertexShape shape;

public:
	VertexStruct() {}
	VertexStruct(VertexMode mode_, qreal size_, VertexShape shape_) :mode(mode_), size(size_), shape(shape_) {}

	VertexStruct & operator=(const VertexStruct &other) {
		this->size = other.size;
		this->mode = other.mode;
		this->shape = other.shape;
		return *this;
	}
};


class BaseShape : public QObject {

public:

	BaseShape(QObject * parent = Q_NULLPTR);
	~BaseShape();

	virtual void paint(QPainter *painter);
	virtual void drawVertex(QPainterPath &path, const QPointF &point, bool ishighlight = false, VertexShape shape = P_ROUND);

	virtual BaseShape *copy() = 0;

public:
	//color config
	QColor m_lineColor;
	QColor m_fillColor;
	QColor m_selectLineColor;
	QColor m_selectFillColor;
	QColor m_vertexFillColor;
	QColor m_hvertexFillColor;

	QMap<VertexMode, VertexStruct> m_highlightSettings;

	QVector<QPointF> m_points;
	VertexMode m_highlightMode = NEAR_VERTEX;
	int m_highlightPointIndex = -1;

	int m_pointSize = 8;
	float m_scale = 1.0;
};