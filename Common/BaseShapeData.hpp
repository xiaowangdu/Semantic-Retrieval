#pragma once
#include <QObject>
#include <QWidget>
#include "BaseShape.hpp"
//#include <QColor>

class BaseShapeData {
public:
	QString label;
	QColor lineColor;
	QColor fillColor;
	QVector<QPointF> points;
	QString difficult;

	BaseShapeData(const QVector<QPointF> &points_);
	BaseShapeData(const QVector<QPoint> &points_);

	BaseShapeData() {}
	virtual BaseShapeData & operator=(const BaseShapeData &other);
};

