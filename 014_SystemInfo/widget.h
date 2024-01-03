#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <pdh.h>
#include <psapi.h>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    void initCpuUsage();
    void getCurrentCpuUsage();
    void getMemory();
protected slots:
    void slot_getSystemInfor();

private:
    Ui::Widget *ui;
    QTimer*             m_getSystemInfo             = nullptr;
};
#endif // WIDGET_H
