#pragma once

#include <QString>
#include <QRect>
#include <QColor>
#include <QVector>
#include "../LabelImage/Shape.hpp"

//// BoxShape type:
//// [label, points[2], color, color, difficult]


class XmlBase {

public:
	XmlBase(){}
	~XmlBase(){}

public:
	QVector<ShapeData> m_vBoxShapeVec;
	QString m_sXmlFilePath;
	bool m_bIsVerified = false;

};

