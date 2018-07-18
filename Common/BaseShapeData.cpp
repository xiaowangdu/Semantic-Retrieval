#include "BaseShapeData.hpp"

BaseShapeData::BaseShapeData(const QVector<QPointF> &points_)
{
	points = points_;
}

BaseShapeData::BaseShapeData(const QVector<QPoint> &points_)
{
	QPointF pointf;
	for (int i = 0; i < points_.size(); ++i) {
		pointf.setX(points_[i].x());
		pointf.setY(points_[i].y());

		points.append(pointf);
	}
}

//ShapeData::ShapeData(BaseShape *s)
//{
//	Shape *p = dynamic_cast<Shape *>(s);
//	Q_ASSERT(p != NULL);
//
//	label = p->getLabel();
//	lineColor = p->getLineColor();
//	fillColor = p->getFillColor();
//	difficult = p->getDifficult();
//
//	//copy points
//	points = p->getPoints();
//
//}

BaseShapeData & BaseShapeData::operator=(const BaseShapeData &other)
{
	this->label = other.label;
	this->lineColor = other.lineColor;
	this->fillColor = other.fillColor;
	this->difficult = other.difficult;

	//QVector already do 'operator='
	this->points = other.points;
	Q_ASSERT(points.size() == 2);

	return *this;
}
