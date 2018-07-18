#pragma once

#include "XmlBase.h"
#include <QObject>
#include <QVector>


class VocXmlReader : private XmlBase {
	

public:
	VocXmlReader(const QString filePath);
	~VocXmlReader();

	QVector<ShapeData> getShapesData() const;
	bool isVerified()const { return m_bIsVerified; }
	void setVerified(const bool v) { m_bIsVerified = v; }

	bool parseXML();
#ifdef DEBUG
	void print();
#endif


private:
	void addLabeledShape(const QVector<QPointF> bnd, const QString name, const QString difficult);
	DISABLE_COPY(VocXmlReader);

private:
	QString	m_sFileName;
};
