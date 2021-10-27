#ifndef WIDGET_H
#define WIDGET_H


#include <QWidget>
#include <QtDebug>
#include <Windows.h>
#include <tchar.h>

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

private:

    char * toChar(const wchar_t *_wchar);
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
