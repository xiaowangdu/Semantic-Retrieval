#include "Preprocessing.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Preprocessing w;
	w.show();
	return a.exec();
}
