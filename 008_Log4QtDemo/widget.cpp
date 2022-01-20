#include "widget.h"
#include "ui_widget.h"
#include <QtDebug>




Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("日志");

}

Widget::~Widget()
{
    delete ui;
}

/**
 * @brief Widget::on_pushButton_Qdebug_clicked
 * 调试信息测试
 */
void Widget::on_pushButton_Qdebug_clicked()
{
    qDebug() << "qDebug Testing";
}

/**
 * @brief Widget::on_pushButton_Qwarning_clicked
 * 一般警告测试
 */
void Widget::on_pushButton_Qwarning_clicked()
{
    qWarning() << "qWarning Testing";
}

/**
 * @brief Widget::on_pushButton_QCritical_clicked
 * 严重错误测试
 */
void Widget::on_pushButton_QCritical_clicked()
{
    qCritical() << "qCritical Testing";
}

/**
 * @brief Widget::on_pushButton_QFatal_clicked
 * 致命错误测试
 */
void Widget::on_pushButton_QFatal_clicked()
{
    qFatal("qFatall Testing");
}

/**
 * @brief Widget::on_pushButton_INfor_clicked
 * infor 消息测试
 */
void Widget::on_pushButton_INfor_clicked()
{
    qInfo() <<"qInfo Testing";
}

