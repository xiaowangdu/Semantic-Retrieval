#include "Serializable.h"
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include "Settings.hpp"
#include <QDebug>
#include <QDir>
#include <QCoreApplication>


const QByteArray _Settings<>::operator[](const QString &key) const
{
	return m_dict[key];
}

_Settings<> & _Settings<>::operator=(const _Settings<> &other)
{
	m_dict = other.m_dict;
	return *this;
}

void _Settings<>::deleteElement(const QString &key)
{
	QMap<QString, QByteArray>::iterator i = m_dict.find(key);
	while (i != m_dict.end() && i.key() == key) {
		m_dict.erase(i);
		++i;
	}
}

QByteArray & _Settings<>::operator[](const QString &key)
{
	return m_dict[key];
}


QByteArray & _Settings<>::value(const QString &key)
{
	return m_dict[key];
}

bool _Settings<>::saveAsText(const QString &filepath)
{
	if (filepath == "") {
		return false;
	}

	QFile file(filepath);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
		return false;
	}

	QMapIterator<QString, QByteArray> iter(m_dict);
	QTextStream ts(&file);

	QString tmp;
	while (iter.hasNext()) {
		iter.next();
		deserializable(tmp, &(iter.value()));
		//why 'endl' does not working.
		ts << iter.key() << ": " << tmp << "\r\n";
	}

	return true;
}

bool _Settings<>::load(const QString &filepath)
{
	QString path = filepath;
	if (path.isEmpty()) {
		//Try load config data last time save.
		path = QCoreApplication::applicationDirPath();
		path = QDir::toNativeSeparators(path + QDir::separator() + "config");

		QDir dir(path);
		if (!dir.exists()){
			return false;
		}
		else{
			path = QDir::toNativeSeparators(path + QDir::separator() + ".labeliamgesettings.dat");
			if (!QFileInfo::exists(path)) {
				return false;
			}
		}
	}

	QFileInfo fileinfo(path);
	if (fileinfo.suffix() != "dat") {
		qDebug() << "Unsupport file format";
		Q_ASSERT(0);
		return false;
	}

	m_dict.clear();
	return deserializable(m_dict, path);
}

bool _Settings<>::save(const QString &filepath)
{
	QString path = filepath;
	if (path.isEmpty()) {
		path = QCoreApplication::applicationDirPath();
		path = QDir::toNativeSeparators(path + QDir::separator() + "config");

		QDir dir(path);
		if (!dir.exists()) {
			dir.mkpath(path);
		}

		path = QDir::toNativeSeparators(path + QDir::separator() + ".labeliamgesettings.dat");
	}

	QFileInfo fileinfo(path);
	if (fileinfo.suffix() != "dat") {
		qDebug() << "Unsupport file format";
		Q_ASSERT(0);
	}

	return serializable(m_dict, path);
}

//#ifdef DEBUG
//void _Settings<QString, QString>::dprint()
//{
//	QMapIterator<QString, QString> i(m_dict);
//	while (i.hasNext()) {
//		i.next();
//		qDebug() << i.key() << ": " << i.value();
//	}
//}
//#endif

