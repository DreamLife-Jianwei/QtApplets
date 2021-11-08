#include "international.h"
#include "ui_international.h"
#include <QTranslator>
International::International(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::International)
{
    ui->setupUi(this);
}

International::~International()
{
    delete ui;
}

/**
 * @brief International::on_pushButton_2_clicked
 * 切换中文
 */
void International::on_pushButton_2_clicked()
{
    QTranslator trans;
    trans.load(":/Chines.qm");
    qApp->installTranslator(&trans);
    this->ui->retranslateUi(this);
}
/**
 * @brief International::on_pushButton_3_clicked
 * 切换英文
 */
void International::on_pushButton_3_clicked()
{
    QTranslator trans;
    trans.load(":/English.qm");
    qApp->installTranslator(&trans);
    this->ui->retranslateUi(this);
}
