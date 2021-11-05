#include "customcontrol.h"

CustomControl::CustomControl(QWidget *parent) :
    QWidget(parent)
{
    m_label = new QLabel(this);
    m_label->setGeometry(0,0,100,20);
}

int CustomControl::getTestID()
{
    return testID;
}

void CustomControl::setTestID(int temp)
{
    testID = temp;
    m_label->setGeometry(0,0,100,20);
    m_label->setStyleSheet("color: rgb(255, 255, 0);font: 11pt '黑体';");
    m_label->setText(QString::number(testID,10));
    update();
}
