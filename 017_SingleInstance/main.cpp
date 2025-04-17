#include "widget.h"

#include <QApplication>
#include <QMessageBox>
#include "singleinstance.h"
int main(int argc, char *argv[])
{
    // 使用应用名称作为唯一标识（建议改为你的应用名）
    SingleInstance guard("YourAppName_Company");

    if (guard.isRunning()) {
        QMessageBox::warning(nullptr, "警告", "程序已在运行中");
        guard.killExisting(); // 可选：强制终止已有实例
    }

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
