#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    // 获取全局线程池的实例
    QThreadPool *pool = QThreadPool::globalInstance();
    // 设置线程池中最大线程数
    pool->setMaxThreadCount(5);

    // 创建并启动任务
    for (int i = 0; i < 10; ++i) {
        Task *task = new Task();
        // 如果不设置，则任务执行完毕后会自动删除
        task->setAutoDelete(true);
        pool->start(task);
    }

    // 等待所有任务完成，你可以设置一个超时或者无限等待
    pool->waitForDone();

}

Widget::~Widget()
{
    delete ui;
}

