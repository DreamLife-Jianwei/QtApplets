#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QVariant>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("QSettingTimer");
    mTimer = new QTimer;
    connect(mTimer,&QTimer::timeout,this,&Widget::readConfig);
}

Widget::~Widget()
{
    mTimer->stop();
    delete mTimer;
    mTimer = nullptr;
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    readConfig();
}

void Widget::readConfig()
{
    QSettings *config = new QSettings("./config.ini",QSettings::IniFormat);
    config->beginGroup("TestNode");
    ui->textBrowser->append(config->value("TEST").toString());
    config->endGroup();

}

void Widget::on_checkBox_stateChanged(int arg1)
{
    if(arg1 != 0)
    {
        mTimer->start(1000);
    }
    else
    {
        if(mTimer->isActive())
            mTimer->stop();
    }
}
