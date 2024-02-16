#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QRunnable>
#include <QThreadPool>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE



class Task : public QRunnable
{
protected:
    void run() override
    {
        // 这里放置任务代码
        qDebug() << "Task executed in thread" << QThread::currentThread();
        // 模拟一些工作
        QThread::sleep(1);
    }
};


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
