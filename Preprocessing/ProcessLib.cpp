#include "ProcessLib.h"
#include <QString>
#include <QPixmap>
#include <QImage>
#include <QDebug>

Mat read2Gray(const QString &filename)
{
	Mat img = imread(filename.toStdString().c_str());
	Mat gray_image;
	cvtColor(img, gray_image, COLOR_BGR2GRAY);

	return gray_image;
}

void convertToGray(Mat &data)
{
	cvtColor(data, data, COLOR_BGR2GRAY);
}

QImage cvMatToQImage(const Mat &data)
{
	switch (data.type()){
	// 8-bit, 4 channel
	case CV_8UC4:
	{
		QImage image(data.data,
			data.cols, data.rows,
			static_cast<int>(data.step),
			QImage::Format_ARGB32);

		return image;
	}
	// 8-bit, 3 channel
	case CV_8UC3:
	{
		QImage image(data.data,
			data.cols, data.rows,
			static_cast<int>(data.step),
			QImage::Format_RGB888);

		return image.rgbSwapped();
	}
	// 8-bit, 1 channel
	case CV_8UC1:
	{
		QImage image(data.data,
			data.cols, data.rows,
			static_cast<int>(data.step),
			QImage::Format_Grayscale8);//Format_Alpha8 and Format_Grayscale8 were added in Qt 5.5

		return image;
	}

	default:
		qWarning() << "CVS::cvMatToQImage() - cv::Mat image type not handled in switch:" << data.type();
		break;
	}

	return QImage();
}

QPixmap cvMatToQPixmap(const Mat &data)
{
	return QPixmap::fromImage(cvMatToQImage(data));
}

Mat QImageToCvMat(const QImage &image, bool inCloneImageData)
{
	switch (image.format()){
	// 8-bit, 4 channel
	case QImage::Format_ARGB32:
	case QImage::Format_ARGB32_Premultiplied:
	{
		Mat mat(image.height(), image.width(),
			CV_8UC4,
			const_cast<uchar*>(image.bits()),
			static_cast<size_t>(image.bytesPerLine())
			);

		return (inCloneImageData ? mat.clone() : mat);
	}

	// 8-bit, 3 channel
	case QImage::Format_RGB32:
	case QImage::Format_RGB888:
	{
		if (!inCloneImageData){
			qWarning() << "CVS::QImageToCvMat() - Conversion requires cloning because we use a temporary QImage";
		}

		QImage swapped = image;

		if (image.format() == QImage::Format_RGB32){
			swapped = swapped.convertToFormat(QImage::Format_RGB888);
		}

		swapped = swapped.rgbSwapped();

		return Mat(swapped.height(), swapped.width(),
			CV_8UC3,
			const_cast<uchar*>(swapped.bits()),
			static_cast<size_t>(swapped.bytesPerLine())
			).clone();
	}

	// 8-bit, 1 channel
	case QImage::Format_Indexed8:
	{
		Mat mat(image.height(), image.width(),
			CV_8UC1,
			const_cast<uchar*>(image.bits()),
			static_cast<size_t>(image.bytesPerLine())
			);

		return (inCloneImageData ? mat.clone() : mat);
	}

	default:
		qWarning() << "CVS::QImageToCvMat() - QImage format not handled in switch:" << image.format();
		break;
	}

	return Mat();
}

Mat QPixmapToCvMat(const QPixmap &pixmap, bool inCloneImageData)
{
	return QImageToCvMat(pixmap.toImage(), inCloneImageData);
}

MatND _calhistogram(Mat &image)
{
	MatND hist;
	int channels[] = { 0 };
	int dims = 1;
	int histSize[] = { 256 };
	float granges[] = { 0, 255 };
	const float *ranges[] = { granges };
	calcHist(&image, 1, channels, Mat(), hist, dims, histSize, ranges);
	return hist;
}

Mat histogramImage(Mat &image)
{
	MatND hist = _calhistogram(image);
	Mat showImage(256, 256, CV_8U, Scalar(0));
	int i;
	double maxValue = 0;
	minMaxLoc(hist, 0, &maxValue, 0, 0);
	for (i = 0; i < 256; i++)
	{
		float value = hist.at<float>(i);
		int intensity = saturate_cast<int>(256 - 256 * (value / maxValue));
		rectangle(showImage, Point(i, 256 - 1), Point((i + 1) - 1, intensity), Scalar(255));
	}
	return showImage;
}