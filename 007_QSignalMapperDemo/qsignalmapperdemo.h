#ifndef QSIGNALMAPPERDEMO_H
#define QSIGNALMAPPERDEMO_H

#include <QWidget>
#include <QSignalMapper>
#include <QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui { class QSignalMapperDemo; }
QT_END_NAMESPACE

class QSignalMapperDemo : public QWidget
{
    Q_OBJECT

public:
    QSignalMapperDemo(QWidget *parent = nullptr);
    ~QSignalMapperDemo();

private:
    Ui::QSignalMapperDemo *ui;
};
#endif // QSIGNALMAPPERDEMO_H
