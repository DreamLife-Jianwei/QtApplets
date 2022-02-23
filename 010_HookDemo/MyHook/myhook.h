#ifndef MYHOOK_H
#define MYHOOK_H

#include <QObject>
#include <windows.h>
class MyHook : public QObject
{
    Q_OBJECT
public:
    explicit MyHook(QObject *parent = nullptr);
    ~MyHook();
    void setAllEnable(bool flag);
private:
    void hook(bool flag);                       //功能键
    void closeTaskWindow(bool flag);            //显示任务栏
    void closeTaskManager(bool flag);           //任务管理器
private:
    HWND mTask;                                  //任务栏
    HWND mDesktop;                               //桌面

};

#endif // MYHOOK_H
