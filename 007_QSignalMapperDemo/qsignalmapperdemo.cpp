#include "qsignalmapperdemo.h"
#include "ui_qsignalmapperdemo.h"
#include <QVBoxLayout>
#include <QLineEdit>
QSignalMapperDemo::QSignalMapperDemo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QSignalMapperDemo)
{
    ui->setupUi(this);

    QVBoxLayout *pLayout = new QVBoxLayout(this);

    QString str = "Button1 Button2 Button3 Button4 Button5";
    QStringList strList = str.split(" ");
    QSignalMapper *pMapper = new QSignalMapper(this);

    int nRowCnt = 0;
    foreach(QString itor, strList)
    {
        QPushButton *pBtn = new QPushButton(this);
        pBtn->setFixedHeight(20);
        pBtn->setText(itor);

        connect(pBtn, SIGNAL(clicked()), pMapper, SLOT(map()));
        pMapper->setMapping(pBtn, pBtn->text());

        pLayout->addWidget(pBtn, nRowCnt++, 0);
    }

    QLineEdit *pEdit = new QLineEdit(this);
    pEdit->setFixedHeight(30);
    connect(pMapper, SIGNAL(mapped(QString)), pEdit, SLOT(setText(QString)));
    pLayout->addWidget(pEdit, nRowCnt, 0);
    pLayout->addStretch();

}

QSignalMapperDemo::~QSignalMapperDemo()
{
    delete ui;
}

