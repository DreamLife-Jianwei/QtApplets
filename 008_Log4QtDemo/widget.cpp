#include "widget.h"
#include "ui_widget.h"





Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("日志");

//    log = Log4Qt::Logger::rootLogger();

}

Widget::~Widget()
{
    delete ui;
}

