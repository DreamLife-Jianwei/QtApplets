#include "widget.h"

#include <QApplication>
#include <QMessageBox>
//引入头文件包含
#include "log4qt/logmanager.h"
#include "log4qt/propertyconfigurator.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!Log4Qt::PropertyConfigurator::configure("./QtLog4Qt.conf"))             //设置Log4Qt配置文件
    {
        QMessageBox::warning(nullptr,"警告","加载日志配置文件失败",QMessageBox::Ok);
    }
    Log4Qt::LogManager::setHandleQtMessages(true);


    Widget w;
    w.show();
    return a.exec();
}
