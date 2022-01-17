#include "widget.h"

#include <QApplication>
//引入头文件包含
#include "log4qt/logger.h"
#include "log4qt/basicconfigurator.h"
#include "log4qt/propertyconfigurator.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);





    Widget w;
    w.show();
    return a.exec();
}
