#pragma once

#include "opencv.hpp"

class QString;
class QPixmap;
class QImage;
using namespace cv;

extern Mat read2Gray(const QString &filename);
extern Mat read2Gray(Mat &data);

extern void convertToGray(Mat &data);
extern QPixmap cvMatToQPixmap(const Mat &data);
extern QImage cvMatToQImage(const Mat &data);
extern QPixmap cvMatToQPixmap(const Mat &data);
extern Mat QImageToCvMat(const QImage &image, bool inCloneImageData = true);
extern Mat QPixmapToCvMat(const QPixmap &pixmap, bool inCloneImageData = true);

extern Mat histogramImage(Mat &image);