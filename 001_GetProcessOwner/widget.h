#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <windows.h>
#include <WinBase.h>
#include <CommCtrl.h>
#include <tlhelp32.h>
#include <stdio.h>
#include "Psapi.h"
#include <tchar.h>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void on_pushButton_get_clicked();

private:
    /**
     * @brief listenProcess
     * @param processName
     * @return
     * 监听指定程序
     */
    bool listenProcess(QString processName = "Snipaste.exe");
    /**
     * @brief getProcessOwner
     * @param pid
     * 获取进程名称
     */
    char *getProcessOwner(DWORD pid);

    char* toChar(const wchar_t* _wchar);
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
