#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>



//引入头文件包含
#include "log4qt/logger.h"
#include "log4qt/basicconfigurator.h"


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
    void on_pushButton_Qdebug_clicked();

    void on_pushButton_Qwarning_clicked();

    void on_pushButton_QCritical_clicked();

    void on_pushButton_QFatal_clicked();

    void on_pushButton_INfor_clicked();

private:
    Ui::Widget *ui;

//    Log4Qt::Logger* log = nullptr;

};
#endif // WIDGET_H
