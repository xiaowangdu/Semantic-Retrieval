#include "LabelFile.hpp"
#include "../XmlHelper/VocXmlWriter.hpp"
#include <QFileInfo>
#include <QDir>
#include <QImage>
#include <QRect>

QString LabelFile::m_suffix = XML_EXT;

LabelFile::LabelFile(QObject * parent) : QObject(parent) 
{

}

LabelFile::~LabelFile() 
{
	
}

void LabelFile::savePascalVocFormat(const QString &targetFileName, const QVector<ShapeData> &shapes, const QString &imagepath)
{
	QFileInfo fileinfo(imagepath);
	const QString imgfilename = fileinfo.fileName();
	const QString imgfolderpath = fileinfo.absoluteDir().absolutePath();
	const QString imgfoldername = fileinfo.absoluteDir().dirName();

	QImage image = QImage();
	image.load(imagepath);

	QSize imagesize = QSize(image.height(), image.width());
	VocXmlWriter xwriter(imagepath);
	xwriter.setFileName(imgfilename);
	xwriter.setFolderName(imgfoldername);
	xwriter.setImageSize(imagesize);
	xwriter.setImageChannel(3);
	if (image.isGrayscale()) {
		xwriter.setImageChannel(1);
	}

	for (int i = 0; i < shapes.size(); i++) {
		QVector<QPoint> rect;
		LabelFile::convertPoints2BndBox(shapes[i].points, rect);
		xwriter.addShape(rect, shapes[i].label, shapes[i].difficult);

	}
	xwriter.save(targetFileName);
}

bool LabelFile::isLabelFile(const QString &filename)
{
	QFileInfo fileinfo(filename);
	const QString filesuffix = fileinfo.suffix();

	return filesuffix == LabelFile::getSuffix();
}

void LabelFile::convertPoints2BndBox(const QVector<QPointF> &points, QVector<QPoint> &box)
{
	qreal xmin = FLOATMAX;
	qreal ymin = FLOATMAX;
	qreal xmax = FLOATMIN;
	qreal ymax = FLOATMIN;

	for (int i = 0; i < points.size(); i++) {
		xmin = qMin(points[i].x(), xmin);
		ymin = qMin(points[i].y(), ymin);
		xmax = qMax(points[i].x(), xmax);
		ymax = qMax(points[i].y(), ymax);
	}

	if (xmin < 1) {
		xmin = 1;
	}
	
	if (ymin < 1) {
		ymin = 1;
	}

	box.append(QPoint(int(xmin), int(ymin)));
	box.append(QPoint(int(xmax), int(ymax)));
}