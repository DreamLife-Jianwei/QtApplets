#ifndef PROPERTYANIMATIONDEMO_H
#define PROPERTYANIMATIONDEMO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class PropertyAnimationDemo; }
QT_END_NAMESPACE

class PropertyAnimationDemo : public QWidget
{
    Q_OBJECT

public:
    PropertyAnimationDemo(QWidget *parent = nullptr);
    ~PropertyAnimationDemo();

private:
    Ui::PropertyAnimationDemo *ui;
};
#endif // PROPERTYANIMATIONDEMO_H
