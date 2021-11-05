#ifndef CUSTOMCONTROL_H
#define CUSTOMCONTROL_H

#include <QWidget>
#include <QLabel>
class CustomControl : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int testID READ getTestID WRITE setTestID)


public:
    CustomControl(QWidget *parent = 0);

    int testID = 1;
    int getTestID();
    void setTestID(int temp);

private:
    QLabel *m_label = nullptr;


};

#endif // CUSTOMCONTROL_H
