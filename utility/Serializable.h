#pragma once
#include <QByteArray>
#include <QBuffer>
#include <QString>
#include <QDataStream>
#include <QFile>

template<typename T>
bool deserializable(T &tp, const QByteArray *bytedata)
{
	if (bytedata->isNull()) {
		qDebug() << "the content is null.";
		return false;
	}

	QDataStream in(*bytedata);

	in >> tp;
	return true;
}

template<typename T>
bool deserializable(T &tp, const QString &deserialfrom)
{
	if (deserialfrom == "") {
		qDebug() << "file path is null.";
		return false;
	}

	QFile file(deserialfrom);
	if (!file.open(QIODevice::ReadWrite)) {
		return false;
	}

	QDataStream in(&file);    // read the data serialized from file  
	in >> tp;

	return true;
}


template<typename T>
QByteArray* serializable(const T &tp)
{
	QByteArray *tmparray = new QByteArray();
	QDataStream out(tmparray, QIODevice::WriteOnly);

	out << tp;

	return tmparray;
}

template<typename T>
bool serializable(const T &tp, const QString &targetFile)
{
	QFile file(targetFile);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
		return false; 

	QDataStream out(&file);   // we will serialize the data into the file  
	out << tp;

	return true;
}