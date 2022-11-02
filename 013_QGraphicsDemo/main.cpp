#include "qgraphicsdemo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsDemo w;
    w.show();
    return a.exec();
}
