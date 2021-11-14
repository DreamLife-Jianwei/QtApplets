#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int a = 1;
    int b = 2;
    int c = a + b;

    Q_ASSERT(c == 5);

    qDebug() << "Test 1";
}


void MainWindow::on_pushButton_2_clicked()
{
    int a = 1;
    int b = 2;
    int c = a + b;

    Q_ASSERT_X(c == 5,"Error","Error Test 1");

    qDebug() << "Test 1";
}

