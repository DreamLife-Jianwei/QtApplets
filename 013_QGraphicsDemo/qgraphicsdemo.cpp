#include "qgraphicsdemo.h"
#include "ui_qgraphicsdemo.h"

QGraphicsDemo::QGraphicsDemo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QGraphicsDemo)
{
    ui->setupUi(this);
    this->setWindowTitle("QGraphicsDemo");
}

QGraphicsDemo::~QGraphicsDemo()
{
    delete ui;
}

