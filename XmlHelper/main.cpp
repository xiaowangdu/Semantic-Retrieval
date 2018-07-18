#include <QtCore/QCoreApplication>
#include "VocXmlWriter.hpp"
#include "VocXmlReader.hpp"


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	
	VocXmlWriter writer;
	//writer.addBndBox(QRect(2,3, 2, 2), "lyn", "1");
	//writer.addBndBox(QRect(2, 3, 2, 2), "lyn", "1");
	writer.save("F:/workspace/spyder_prj_test/data/hello.xml");
	
	VocXmlReader reader("F:/workspace/spyder_prj_test/data/hello.xml");
	reader.parseXML();
	//reader.print();

	return a.exec();
}
