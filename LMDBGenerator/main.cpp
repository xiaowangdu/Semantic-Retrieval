#include "LMDBGenerator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LMDBGenerator w;
	w.show();
	return a.exec();
}
