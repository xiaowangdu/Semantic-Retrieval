#include "VocXmlReader.hpp"
#include <QFileInfo>
#include <QDomDocument>
#include <QDebug>

VocXmlReader::VocXmlReader(const QString filePath)
{
	m_sXmlFilePath = filePath;
	if (!filePath.isEmpty()) {
		parseXML();
	}
	
}

VocXmlReader::~VocXmlReader() 
{
	
}

QVector<ShapeData> VocXmlReader::getShapesData() const
{
	return m_vBoxShapeVec;
}

void VocXmlReader::addLabeledShape(const QVector<QPointF> bnd, const QString name, const QString difficult)
{
	ShapeData shape(bnd);
	shape.label = name;
	shape.difficult = difficult;
	this->m_vBoxShapeVec.append(shape);
}

bool VocXmlReader::parseXML()
{
	QFileInfo fileinfo(m_sXmlFilePath);

	if (fileinfo.suffix() != "xml") {
		qDebug() << "Unsupport file format";
		Q_ASSERT(0);
	}

	QFile file(m_sXmlFilePath);
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << QString("Open %1 failed!").arg(m_sXmlFilePath);
		return false;
	}

	QString errorStr;
	int errorLine;
	int errorColumn;
	QDomDocument doc;
	if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)){
		qDebug() << "Parse file failed:" << errorLine << "---" << errorColumn << ":" << errorStr;
		file.close();
		return false;
	}

	file.close();

	QDomElement pAnnotation = doc.documentElement();
	for (int i = 0; i<pAnnotation.childNodes().count(); i++){
		QDomNode node = pAnnotation.childNodes().item(i);
		if (node.nodeName() == "filename"){
			m_sFileName = node.toElement().attributeNode("filename").value();
		}
		else if (node.nodeName() == "verified") {
			m_bIsVerified = node.toElement().attributeNode("verified").value().toInt();
		}
		//node <object>
		else if (node.nodeName() == "object"){
			ShapeData shape;
			for (int j = 0; j<node.childNodes().count(); j++){
				
				QDomNode objItem = node.childNodes().item(j);
				if (objItem.nodeName() == "name") {
					shape.label = objItem.firstChild().toText().data();
	
				}
				else if (objItem.nodeName() == "difficult") {
					shape.difficult = objItem.firstChild().toText().data();
				}
				//node <bndbox>
				else if (objItem.nodeName() == "bndbox") {
					for (int k = 0; k < objItem.childNodes().count(); k++)
					{
						QDomNode bndboxItem = objItem.childNodes().item(k);
						qreal xmin, ymin, xmax, ymax;
						if (bndboxItem.nodeName() == "xmin") {
							xmin = bndboxItem.firstChild().toText().data().toInt();
						}
						else if (bndboxItem.nodeName() == "ymin") {
							ymin = bndboxItem.firstChild().toText().data().toInt();
						}
						else if (bndboxItem.nodeName() == "xmax") {
							xmax = bndboxItem.firstChild().toText().data().toInt();
						}
						else if (bndboxItem.nodeName() == "ymax") {
							ymax = bndboxItem.firstChild().toText().data().toInt();
						}
						shape.points.append(QPointF(xmin, ymin));
						shape.points.append(QPointF(xmax, ymax));
					}
				}//node </bndbox>
			}

			m_vBoxShapeVec.append(shape);
		}//node </object>
	}

	return true;
}

#ifdef DEBUG
void VocXmlReader::print()
{
	QString str(" filename: %1 label: %2 difficult: %3 \r\nxmin: %4 ymin: %5 xmax: %6 ymax: %7");
/*
	for (int i = 0; i < m_vBoxShapeVec.size(); i++) {
		qDebug() << str.arg(m_sFileName).arg(m_vBoxShapeVec[i].label) \
			.arg(m_vBoxShapeVec[i].difficult).arg(m_vBoxShapeVec[i].rect.x()).arg(m_vBoxShapeVec[i].rect.y()) \
			.arg(m_vBoxShapeVec[i].rect.width()).arg(m_vBoxShapeVec[i].rect.height());
	}
*/
}
#endif