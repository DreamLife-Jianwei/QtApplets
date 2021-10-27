#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("GetUserName");
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    DWORD dwSize = MAX_PATH;                    //获取当前用户名
    TCHAR *pszName = new TCHAR[dwSize];
    if (!GetUserName(pszName, &dwSize))
    {
        delete[] pszName;
        pszName = new TCHAR[dwSize];
        if(GetUserName(pszName, &dwSize))
        {

        }
    }
    qDebug()<<"当前程序用户名："<< toChar(pszName);

    ui->label->setText(QString::fromUtf8("当前进程用户名：")+QString::fromUtf8(toChar(pszName)));
}

char * Widget::toChar(const wchar_t *_wchar)
{
    int len = WideCharToMultiByte(CP_ACP,0,_wchar,-1,NULL,0,NULL,NULL);
    char* _char = new char[len];
    WideCharToMultiByte(CP_ACP,0,_wchar,-1,_char,len,NULL,NULL);
    return _char;
}
