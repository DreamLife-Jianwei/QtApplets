#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QThread>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer;
    connect(timer,&QTimer::timeout,this,[=](){
        qDebug()<< QThread::currentThreadId()<<"\r\n"<<__FILE__<<"\r\n"<<__LINE__<<"\r\n"<<"我的大傻子";
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_logTest_clicked()
{
    if(ui->pushButton_logTest->text() == "开始")
    {
        timer->start(10);
        ui->pushButton_logTest->setText("停止");
    }
    else
    {
        timer->stop();
        ui->pushButton_logTest->setText("开始");
    }

}

