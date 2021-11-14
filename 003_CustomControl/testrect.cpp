#include "testrect.h"

class TestRectData : public QSharedData
{
public:

};

TestRect::TestRect(QWidget *parent) : QWidget(parent), data(new TestRectData)
{

}

TestRect::TestRect(const TestRect &rhs) : data(rhs.data)
{

}

TestRect &TestRect::operator=(const TestRect &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

TestRect::~TestRect()
{

}

int TestRect::getTestX()
{
    return mTestX;
}

void TestRect::setTestX(int temp)
{
    mTestX = temp;
}

bool TestRect::operator !=(TestRect &t)
{
    if(this->mTestX != t.mTestX)
        return true;
    return  false;

}
