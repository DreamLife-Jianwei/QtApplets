#include "widget.h"

#include <QApplication>
//引入头文件包含
#include "log4qt/logger.h"
#include "log4qt/basicconfigurator.h"
#include "log4qt/propertyconfigurator.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Log4Qt::PropertyConfigurator::configure(a.applicationDirPath()
        + "/log4qt.conf");

    Log4Qt::Logger *a1 = Log4Qt::Logger::logger("A1");
        a1->debug("the message of log");

    Widget w;
    w.show();
    return a.exec();
}
