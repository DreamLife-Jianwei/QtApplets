#ifndef HOOKDEMO_H
#define HOOKDEMO_H

#include <QWidget>
#include <MyHook/myhook.h>
QT_BEGIN_NAMESPACE
namespace Ui { class HookDemo; }
QT_END_NAMESPACE

class HookDemo : public QWidget
{
    Q_OBJECT

public:
    HookDemo(QWidget *parent = nullptr);
    ~HookDemo();

signals:

    void siganlOpen();

    void signalClose();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::HookDemo *ui;
    MyHook mHook;
};
#endif // HOOKDEMO_H
