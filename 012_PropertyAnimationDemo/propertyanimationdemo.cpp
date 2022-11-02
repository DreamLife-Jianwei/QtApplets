#include "propertyanimationdemo.h"
#include "ui_propertyanimationdemo.h"

PropertyAnimationDemo::PropertyAnimationDemo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PropertyAnimationDemo)
{
    ui->setupUi(this);
    this->setWindowTitle("属性动画");
}

PropertyAnimationDemo::~PropertyAnimationDemo()
{
    delete ui;
}

