#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextToSpeech>
#include <QTextEdit>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clear_clicked();

    void on_pushButton_read_clicked();

    void on_doubleSpinBoxPitch_valueChanged(double arg1);

    void on_doubleSpinBox_Rate_valueChanged(double arg1);

    void on_doubleSpinBox_Volume_valueChanged(double arg1);

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Widget *ui;

    QTextToSpeech* mQTextToSpeech = nullptr;

};
#endif // WIDGET_H
