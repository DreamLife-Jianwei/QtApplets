#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QSettings>
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
    void on_pushButton_clicked();

    void readConfig();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::Widget *ui;

    QTimer *mTimer = nullptr;
};
#endif // WIDGET_H
