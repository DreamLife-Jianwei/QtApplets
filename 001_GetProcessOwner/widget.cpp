#include "widget.h"
#include "ui_widget.h"
#include <windows.h>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("Listene Process And Get UserName"));

        //参考 https://bbs.csdn.net/topics/360187493
        //https://blog.csdn.net/zzz3265/article/details/1883208
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::listenProcess(QString processName)
{
    bool isRuning = false;

    HANDLE processHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);          //拍摄系统当前所有进程快照

    if((HANDLE)-1 == processHandle)
    {
        return  false;
    }

    PROCESSENTRY32 pInfo;                                                           //进程信息
    pInfo.dwSize = sizeof (PROCESSENTRY32);
    bool bResult = Process32First(processHandle,&pInfo);                            //获得第一个进程，进程快照迭代器
    if(!bResult)
    {
        return  false;
    }

    QString currentProcessName = "";
    while (bResult) {
        currentProcessName = QString("%1").arg(QString::fromUtf16(reinterpret_cast<const unsigned short *>(pInfo.szExeFile)));
        if(currentProcessName == processName)
        {


            qDebug()  << "用户名："<< getProcessOwner(pInfo.th32ProcessID);
            ui->textEdit_show->append("用户名：" + QString::fromLatin1(getProcessOwner(pInfo.th32ProcessID)));

            isRuning = true;
            break;
        }
        bResult = Process32Next(processHandle,&pInfo);

    }

    return  isRuning;
}

char * Widget::getProcessOwner(DWORD pid)
{
    char* owner = new char[513];
    *owner = '\0';
    qDebug() << "PID:" << pid;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION,FALSE,pid);
    if(hProcess == NULL)
    {
        return owner;
    }

    HANDLE hToken = NULL;
    DWORD dwSize = 0;
    TCHAR szUserName[256] = {0};
    TCHAR szDomain[256] = {0};
    DWORD dwDomainSize = 256;
    DWORD dwNameSize = 256;

    SID_NAME_USE SNU;
    PTOKEN_USER pTokenUser = NULL;


    if(!OpenProcessToken(hProcess,TOKEN_QUERY,&hToken))
        qDebug() << "123";
    qDebug() << hToken;
    if(!GetTokenInformation(hToken,TokenUser,pTokenUser,dwSize,&dwSize))
    {
        if(GetLastError() != ERROR_HV_INSUFFICIENT_BUFFER)
            qDebug() << GetLastError();
    }
    pTokenUser = NULL;
    pTokenUser = (PTOKEN_USER)malloc(dwSize);
    if(pTokenUser == NULL)
        qDebug() << "345";
    if(!GetTokenInformation(hToken,TokenUser,pTokenUser,dwSize,&dwSize))
        qDebug() << "456";
    if(LookupAccountSidW(NULL,pTokenUser->User.Sid,szUserName,&dwNameSize,szDomain,&dwDomainSize,&SNU) != 0)
        sprintf(owner,"%s\0",toChar(szUserName));
    if(pTokenUser != NULL)
        free(pTokenUser);
    return owner;
}

char *Widget::toChar(const wchar_t *_wchar)
{
    int len = WideCharToMultiByte(CP_ACP,0,_wchar,-1,NULL,0,NULL,NULL);
    char* _char = new char[len];
    WideCharToMultiByte(CP_ACP,0,_wchar,-1,_char,len,NULL,NULL);
    return _char;
}


void Widget::on_pushButton_get_clicked()
{

    ui->textEdit_show->append("----------------------------------------------------------------------------");

    qDebug() <<"<---------------------------------------------------------------------------------->";


    if(ui->lineEdit_processName->text().isEmpty())
    {
        if(listenProcess())
        {
            qDebug()<<"好了";
            ui->textEdit_show->append("好了");
        }
        else
        {
            qDebug() <<"失败";
            ui->textEdit_show->append("失败");
        }
    }
    else
    {
        if(listenProcess(ui->lineEdit_processName->text()))
        {
            qDebug() << ui->lineEdit_processName->text() << "linten";
            ui->textEdit_show->append(ui->lineEdit_processName->text() + "linten");
        }
        else
        {
            qDebug() <<"失败";
            ui->textEdit_show->append("失败");
        }

    }

}
