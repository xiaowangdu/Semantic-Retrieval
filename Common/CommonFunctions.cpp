#include <QStringList>
#include <QImageReader>
#include <QFileDialog>
#include <QMessageBox>
#include "../utility/Constants.hpp"
#include "CommonFunctions.h"

QStringList getSupportedImgExtensions()
{
	QByteArrayList tl = QImageReader::supportedImageFormats();
	QStringList supported;
	for (int i = 0; i < tl.size(); ++i) {
		supported << tl.at(i).data();
	}

	return supported;
}

QString getSupportedImgFilters()
{
	QString filters;
	QStringList tlist = getSupportedImgExtensions();
	for (int i = 0; i < tlist.size(); ++i) {
		filters += "*." + tlist[i];
		if (i != tlist.size() - 1) {
			filters += " ";
		}
	}

	return filters;
}

QString openFileDialog(
	const QString &where,
	const QString &filters, const QString &type, const QString &title, QWidget *parent)
{
	QString defaultPath = where.isEmpty() ? "." : where;

	QString title_ = title.isEmpty() ? QString("%1 - Choose %2 file").arg(__APPNAME__).arg(type) : title;

	return QFileDialog::getOpenFileName(parent, title_, defaultPath, filters);
}

QString openImageDialog(QWidget *parent, const QString &title, const QString &defaultpath, const QString &filters)
{
	QString defaultPath = defaultpath.isEmpty() ? "." : defaultpath;

	QString filters_ = filters;
	if (filters.isEmpty()) {
		filters_ = QString("Image files (%1)").arg(getSupportedImgFilters());
	}

	QString filename = QFileDialog::getOpenFileName(parent, QString("%1 - Choose Image file").arg(title.isEmpty()? __APPNAME__:title), defaultPath, filters_);
	return filename;
}

QString configPath()
{
	QString path = QCoreApplication::applicationDirPath();
	path = QDir::toNativeSeparators(path + QDir::separator() + "config");
	return path;
}

bool askingDialog(QWidget *parent, const QString &msg)
{
	return QMessageBox::Yes == QMessageBox::warning(parent, "Attention", msg, QMessageBox::Yes | QMessageBox::No);
}