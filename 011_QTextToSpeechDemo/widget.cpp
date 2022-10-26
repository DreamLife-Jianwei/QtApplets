#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(QSize(1366,768));
    this->setWindowTitle("Qt文字转语音Demo");
    mQTextToSpeech = new QTextToSpeech;
    mQTextToSpeech->say("Hello World");
    mQTextToSpeech->setPitch(0.0);

}

Widget::~Widget()
{
    delete ui;
}

/**
 * @brief Widget::on_pushButton_clear_clicked
 * 清除输入框
 */
void Widget::on_pushButton_clear_clicked()
{
    ui->textEdit->clear();
}

/**
 * @brief Widget::on_pushButton_read_clicked
 * 朗读输入文字
 */
void Widget::on_pushButton_read_clicked()
{

    if(ui->textEdit->document()->isEmpty())
        QMessageBox::warning(this,"警告","文本内容为空",QMessageBox::Ok);
    else
        if(mQTextToSpeech)
            mQTextToSpeech->say(ui->textEdit->document()->toRawText());
}

/**
 * @brief Widget::on_doubleSpinBoxPitch_valueChanged
 * @param arg1
 * 设置音高
 */
void Widget::on_doubleSpinBoxPitch_valueChanged(double arg1)
{
    mQTextToSpeech->setPitch(arg1);
}

/**
 * @brief Widget::on_doubleSpinBox_Rate_valueChanged
 * @param arg1
 * 设置速率
 *
 */
void Widget::on_doubleSpinBox_Rate_valueChanged(double arg1)
{
    mQTextToSpeech->setRate(arg1);
}

/**
 * @brief Widget::on_doubleSpinBox_Volume_valueChanged
 * @param arg1
 * 设置音量
 */
void Widget::on_doubleSpinBox_Volume_valueChanged(double arg1)
{
    mQTextToSpeech->setVolume(arg1);
}

/**
 * @brief Widget::on_comboBox_currentIndexChanged
 * @param index
 * 设置音色
 */
void Widget::on_comboBox_currentIndexChanged(int index)
{
    //mQTextToSpeech->setVoice();
}

