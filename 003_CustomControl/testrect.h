#ifndef TESTRECT_H
#define TESTRECT_H

#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>

class TestRectData;

class TestRect : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int testX READ getTestX WRITE setTestX)

public:
    explicit TestRect(QWidget *parent = nullptr);
    TestRect(const TestRect &);
    TestRect &operator=(const TestRect &);
    ~TestRect();

    int getTestX();

    void setTestX(int temp);




signals:


private:
    QSharedDataPointer<TestRectData> data;

private:
    int mTestX = 0;
};

#endif // TESTRECT_H
