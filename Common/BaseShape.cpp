#include "BaseShape.hpp"
#include "../utility/Constants.hpp"
#include <QDebug>

//config
const VertexStruct __vertex_settings[] = {
	VertexStruct(MOVE_VERTEX, 1.5, P_SQUARE), //vertex type: NEAR_VERTEX  --- 0
	VertexStruct(NEAR_VERTEX, 4.0, P_ROUND)   //vertex type: MOVE_VERTEX  --- 1
};

BaseShape::BaseShape(QObject * parent) : QObject(parent) {

	m_lineColor = DEFAULT_LINE_COLOR;
	m_fillColor = DEFAULT_FILL_COLOR;
	m_selectLineColor = DEFAULT_SELECT_LINE_COLOR;
	m_selectFillColor = DEFAULT_SELECT_FILL_COLOR;
	m_vertexFillColor = DEFAULT_VERTEX_FILL_COLOR;
	m_hvertexFillColor = DEFAULT_HVERTEX_FILL_COLOR;

	for (int i = 0; i < sizeof(__vertex_settings) / sizeof(VertexStruct); i++) {
		m_highlightSettings[__vertex_settings[i].mode] = __vertex_settings[i];
	}
}

BaseShape::~BaseShape() {
	
}


void BaseShape::paint(QPainter *painter)
{

}

void BaseShape::drawVertex(QPainterPath &path, const QPointF &point, bool ishighlight, VertexShape shape)
{
	float d = m_pointSize / m_scale;
	VertexShape pointshape = shape;
	//QPointF point = m_points[pointindex];

	if (ishighlight) {
		float size = m_highlightSettings[m_highlightMode].size;
		d *= size;

		pointshape = m_highlightSettings[m_highlightMode].shape;
	}

	if (m_highlightPointIndex >= 0) {
		m_vertexFillColor = m_hvertexFillColor;
	}
	else {
		m_vertexFillColor = DEFAULT_VERTEX_FILL_COLOR;
	}

	if (pointshape == P_SQUARE) {
		path.addRect(point.x() - d / 2, point.y() - d / 2, d, d);
	}
	else if (pointshape == P_ROUND) {
		path.addEllipse(point, d / 2.0, d / 2.0);
	}
	else {
		qDebug() << "unsupported vertex shape";
		Q_ASSERT(0);
	}
}