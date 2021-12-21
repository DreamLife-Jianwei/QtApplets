#include "qsignalmapperdemo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSignalMapperDemo w;
    w.show();
    return a.exec();
}
