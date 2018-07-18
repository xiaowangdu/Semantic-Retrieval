#include "FileHelper.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileHelper w;
    w.show();

    return a.exec();
}
