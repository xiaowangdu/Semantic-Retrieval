#pragma once
#include <QObject>
#include "../utility/Constants.hpp"
#include "../utility/MacroDef.h"
#include "Shape.hpp"
#include <QVector>


class LabelFile : public QObject {
	DEFINE_CLASS_PROPERTY(bool, Verified);

public:
	LabelFile(QObject * parent = Q_NULLPTR);
	~LabelFile();

	void savePascalVocFormat(const QString &filename, const QVector<ShapeData> &shapes, const QString &imagepath);

	static bool isLabelFile(const QString &filename);
	static void convertPoints2BndBox(const QVector<QPointF> &points, QVector<QPoint> &box);

	static const QString &getSuffix() { return m_suffix; }

private:
	static QString m_suffix;
	QString m_imagePath;

};
