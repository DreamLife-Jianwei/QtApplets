#include "customcontrol.h"

CustomControl::CustomControl(QWidget *parent) :
    QWidget(parent)
{
    m_label = new QLabel(this);
    m_label->setGeometry(0,0,100,20);


}

CustomControl::BrowserType CustomControl::browserType() const
{
    return mBrowserType;
}

void CustomControl::setBrowserType(const CustomControl::BrowserType type)
{

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

QRect CustomControl::testGeometry()
{
    return  testQRect;
}

void CustomControl::setTestGeometry(const QRect r)
{
    m_label->setText(QString::number(r.width(),10));
    testQRect = r;
}

TestRect CustomControl::getTestRect()
{
    return mT;
}

void CustomControl::setTestRect(const TestRect t)
{
//    mT = t;
}



