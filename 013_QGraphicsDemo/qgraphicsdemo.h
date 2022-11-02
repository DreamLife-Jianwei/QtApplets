#ifndef QGRAPHICSDEMO_H
#define QGRAPHICSDEMO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class QGraphicsDemo; }
QT_END_NAMESPACE

class QGraphicsDemo : public QWidget
{
    Q_OBJECT

public:
    QGraphicsDemo(QWidget *parent = nullptr);
    ~QGraphicsDemo();

private:
    Ui::QGraphicsDemo *ui;
};
#endif // QGRAPHICSDEMO_H
