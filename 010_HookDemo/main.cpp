#include "hookdemo.h"

#include <QApplication>

int main(int argc, char *argv[])
{

#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);        //开启高分屏支持
#endif
    QApplication a(argc, argv);
    HookDemo w;

    w.show();
//#ifdef QT_NO_DEBUG                                                      //条件编译，非Debug版本运行
//    w.showFullScreen();                                                 //Release 编译全屏显示
//    mHook.setAllEnable(true);                                           //Release 打开键盘快捷键屏蔽
//#else                                                                   //条件编译，Debug版本运行
//    w.show();                                                           //Debug 不全屏显示
//    mHook.setAllEnable(false);                                          //Debug 不开启键盘快捷键屏蔽
//#endif
    return a.exec();
}
