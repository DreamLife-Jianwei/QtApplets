#ifndef CUSTOMCONTROL_H
#define CUSTOMCONTROL_H

#include <QWidget>
#include <QLabel>
#include <QRect>
#include <QMetaType>
#include "testrect.h"

Q_DECLARE_METATYPE(TestRect);

class CustomControl : public QWidget
{
    Q_OBJECT


    Q_PROPERTY(int testID READ getTestID WRITE setTestID)

    Q_PROPERTY(QRect testGeometry READ testGeometry WRITE setTestGeometry)

    Q_PROPERTY(TestRect testRect READ getTestRect WRITE setTestRect)

    Q_PROPERTY(BrowserType browserType READ browserType WRITE setBrowserType)

public:
    CustomControl(QWidget *parent = 0);


    enum BrowserType { File, Folder };
    Q_ENUMS(BrowserType)

    BrowserType browserType() const;
    void setBrowserType(const BrowserType type);


    int testID = 1;
    int getTestID();
    void setTestID(int temp);

    QRect testGeometry();
    void setTestGeometry(const QRect r);

    TestRect getTestRect();
    void setTestRect(const TestRect t);

private:
    QLabel *m_label = nullptr;

    QRect testQRect;

    TestRect mT;

    BrowserType mBrowserType;


};

#endif // CUSTOMCONTROL_H
