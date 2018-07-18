#pragma once
#include <QObject>
#include <QVector>
#include <QSize>
#include <QDomDocument>

#include "XmlBase.h"
#include "../utility/MacroDef.h"
//#include "../LabelImage/BoxShape.hpp"

class VocXmlWriter : private XmlBase {
	DEFINE_CLASS_PROPERTY(QString, FolderName);
	DEFINE_CLASS_PROPERTY(QString, FileName);
	DEFINE_CLASS_PROPERTY(QSize, ImageSize);
	DEFINE_CLASS_PROPERTY_DEFAULT(int, ImageChannel, 3);
	DEFINE_CLASS_PROPERTY(QString, DatabaseSrc);

public:
	VocXmlWriter(const QString labeledFilePath = "", const QString targetFilePath = "");
	~VocXmlWriter();

	QDomElement generateVocXML();
	void addShape(const QVector<QPoint> &bnd, const QString name, const QString difficult);
	void save(const QString targetFile = "");
	bool isVerified()const { return m_bIsVerified; }
	void setVerified(const bool v) { m_bIsVerified = v; }

private:
	void vocXmlAppendObjs(QDomElement root);
	DISABLE_COPY(VocXmlWriter);

private:
	QDomDocument *m_document;
	QString m_sFilePath;
	QString m_sLocalImgPath;

};
