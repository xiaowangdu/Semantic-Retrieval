#include "MainWindow.h"
#include "../Common/iconloader.h"
#include <QtWidgets/QApplication>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	IconLoader::init();
	MainWindow w;
	w.show();

	return a.exec();
}
