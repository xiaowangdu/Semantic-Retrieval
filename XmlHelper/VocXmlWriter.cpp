#include "VocXmlWriter.hpp"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QFileInfo>
#include <QDebug>

#undef DEBUG

VocXmlWriter::VocXmlWriter(const QString labeledFilePath, const QString targetFilePath){
	m_document = new QDomDocument();
	m_sFilePath = labeledFilePath;

	QFileInfo fileinfo(targetFilePath);
	if (fileinfo.suffix() == "xml") {
		m_sXmlFilePath = targetFilePath;
	}
}

VocXmlWriter::~VocXmlWriter() {
	delete m_document;
}

QDomElement VocXmlWriter::generateVocXML()
{
	//QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml", "version = \'1.0\' encoding=\'UTF-8\'");
	//doc.appendChild(instruction);

	QDomElement root = m_document->createElement("annotation");
	if (this->m_bIsVerified) {
		QDomAttr attr = m_document->createAttribute("verified");
		attr.setValue("yes");
		root.setAttributeNode(attr);
	}
	m_document->appendChild(root);
	//node: <folder>
	QDomElement element = m_document->createElement("folder");
	QDomText text = m_document->createTextNode(getFolderName());
	element.appendChild(text);
	root.appendChild(element);

	//node: <filename>
	element = m_document->createElement("filename");
	text = m_document->createTextNode(getFileName());
	element.appendChild(text);
	root.appendChild(element);

	//node: <path>
	if (m_sFilePath != NULL){
		element = m_document->createElement("path");
		text = m_document->createTextNode(m_sFilePath);
		element.appendChild(text);
		root.appendChild(element);
	}
	//node: <source>
	element = m_document->createElement("source");
	root.appendChild(element);

	QDomElement sourceElement = m_document->createElement("database");
	text = m_document->createTextNode(getDatabaseSrc());
	sourceElement.appendChild(text);
	element.appendChild(sourceElement);

	//node: <size>
	element = m_document->createElement("size");
	root.appendChild(element);

	QDomElement sizeElement = m_document->createElement("width");
	text = m_document->createTextNode(QString("%1").arg(getImageSize().width()));
	sizeElement.appendChild(text);
	element.appendChild(sizeElement);

	sizeElement = m_document->createElement("height");
	text = m_document->createTextNode(QString("%1").arg(getImageSize().height()));
	sizeElement.appendChild(text);
	element.appendChild(sizeElement);

	sizeElement = m_document->createElement("depth");
	text = m_document->createTextNode(QString("%1").arg(getImageChannel()));
	sizeElement.appendChild(text);
	element.appendChild(sizeElement);
	//end node: </size>

	//node: <segmented>
	element = m_document->createElement("segmented");
	text = m_document->createTextNode("0");
	element.appendChild(text);
	root.appendChild(element);

	return root;
}

void VocXmlWriter::addShape(const QVector<QPoint> &bnd, const QString label, const QString difficult)
{
	ShapeData shape(bnd);
	shape.label = label;
	shape.difficult = difficult;
	this->m_vBoxShapeVec.append(shape);
}

void VocXmlWriter::vocXmlAppendObjs(QDomElement root)
{
	QDomElement element;
	QDomText text;
	
	for (int i = 0; i < this->m_vBoxShapeVec.size(); ++i) {
		element = m_document->createElement("object");
		root.appendChild(element);

		QDomElement objectElement = m_document->createElement("name");
		text = m_document->createTextNode(m_vBoxShapeVec[i].label);
		objectElement.appendChild(text);
		element.appendChild(objectElement);

		objectElement = m_document->createElement("pose");
		text = m_document->createTextNode("Unspecified");
		objectElement.appendChild(text);
		element.appendChild(objectElement);

		objectElement = m_document->createElement("truncated");
		if ((m_vBoxShapeVec[i].points[1].y() == getImageSize().height()) || (m_vBoxShapeVec[i].points[0].y() == 1)) {
			text = m_document->createTextNode("1"); // max == height or min
		}
		else if ((m_vBoxShapeVec[i].points[1].x() == getImageSize().width()) || (m_vBoxShapeVec[i].points[0].x() == 1)) {
			text = m_document->createTextNode("1"); // max == width or min
		}
		else {
			text = m_document->createTextNode("0");
		}
		objectElement.appendChild(text);
		element.appendChild(objectElement);

		objectElement = m_document->createElement("difficult");
		bool dif = m_vBoxShapeVec[i].difficult.isEmpty() ? 0 : m_vBoxShapeVec[i].difficult.toInt();
		text = m_document->createTextNode(QString("%1").arg(dif));
		objectElement.appendChild(text);
		element.appendChild(objectElement);

		//node: <bndbox>
		QDomElement bndboxElement = m_document->createElement("bndbox");
		element.appendChild(bndboxElement);

		QDomElement bndboxSubElement = m_document->createElement("xmin");
		text = m_document->createTextNode(QString("%1").arg(m_vBoxShapeVec[i].points[0].x()));
		bndboxSubElement.appendChild(text);
		bndboxElement.appendChild(bndboxSubElement);

		bndboxSubElement = m_document->createElement("ymin");
		text = m_document->createTextNode(QString("%1").arg(m_vBoxShapeVec[i].points[0].y()));
		bndboxSubElement.appendChild(text);
		bndboxElement.appendChild(bndboxSubElement);

		bndboxSubElement = m_document->createElement("xmax");
		text = m_document->createTextNode(QString("%1").arg(m_vBoxShapeVec[i].points[1].x()));
		bndboxSubElement.appendChild(text);
		bndboxElement.appendChild(bndboxSubElement);

		bndboxSubElement = m_document->createElement("ymax");
		text = m_document->createTextNode(QString("%1").arg(m_vBoxShapeVec[i].points[1].y()));
		bndboxSubElement.appendChild(text);
		bndboxElement.appendChild(bndboxSubElement);
		//end node: </bndbox>
	}
}

void VocXmlWriter::save(const QString targetFile) 
{
	QString savedFile = targetFile;
	if (targetFile == "") {
		savedFile = m_sXmlFilePath;
	}

	QFile file(savedFile);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
	return;

	QTextStream out(&file);
	QTextCodec *codec = QTextCodec::codecForName("utf-8");
	out.setCodec(codec);
	QDomElement root = generateVocXML();
	vocXmlAppendObjs(root);
#ifdef DEBUG
	QString s = m_document->toString();
	qDebug() << s;
#endif
	m_document->save(out, 4);       //each line space of file is 4  
}