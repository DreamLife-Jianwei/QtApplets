#include "hookdemo.h"
#include "ui_hookdemo.h"

HookDemo::HookDemo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HookDemo)
{
    ui->setupUi(this);
}

HookDemo::~HookDemo()
{
    delete ui;
}


void HookDemo::on_pushButton_clicked()
{
    mHook.setAllEnable(true);
}


void HookDemo::on_pushButton_2_clicked()
{
    mHook.setAllEnable(false);
}

