#pragma once

class QStringList;

extern QStringList getSupportedImgExtensions();

extern QString getSupportedImgFilters();

extern QString openFileDialog(const QString &where,
	const QString &filters, 
	const QString &type = "Image", const QString &title = "", QWidget *parent = nullptr);

extern QString openImageDialog(QWidget *parent = nullptr, 
	const QString &title = "", 
	const QString &defaultpath="", 
	const QString &filters="");

extern QString configPath();

extern bool askingDialog(QWidget *parent, const QString &msg);