#include "widget.h"

#include <QtDebug>

#include <QApplication>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDir>
#include <QDateTime>
#include <QString>
#include <QThread>

static QSqlDatabase g_DataBase;                 //数据库
const bool deleteOld = false;                   //是否删除去年日志


void openDB()
{

    /**********************************创建日志文件夹**********************************/
    QDir* temp = new QDir;
    if(!temp->exists("./log"))
        if(!temp->mkdir("./log"))
            QMessageBox::warning(nullptr,"警告","创建日志目录失败",QMessageBox::Ok);

    QString mpath = "./log/" + QDateTime::currentDateTime().toString("yyyy");
    if(!temp->exists(mpath))
        if(!temp->mkdir(mpath))
            QMessageBox::warning(nullptr,"警告","创建日志目录失败",QMessageBox::Ok);


    /**********************************只保存本年度日志**********************************/
    if(deleteOld)
    {
        temp->setPath("./log");
        temp->setFilter(QDir::Dirs);
        QFileInfoList list = temp->entryInfoList();
        int i = 0;
        do{
            QFileInfo fileInfo = list.at(i);
            if((fileInfo.fileName() != ".") &&
                    (fileInfo.fileName() != "..") &&
                    (fileInfo.fileName() != QDateTime::currentDateTime().toString("yyyy")))
            {
                temp->setPath("./log/" + fileInfo.fileName());
                temp->removeRecursively();
            }
            ++i;
        }while (i<list.size());
    }

    /**********************************打开/建立数据库操作**********************************/

    if(QSqlDatabase::contains("qt_sql_default_connection"))
        g_DataBase = QSqlDatabase::database("qt_sql_default_connection");
    else
    {
        mpath += ("/" + QDateTime::currentDateTime().toString("MM") + ".db");
        g_DataBase = QSqlDatabase::addDatabase("QSQLITE");
        g_DataBase.setDatabaseName(mpath);
        g_DataBase.setUserName("Root");
        g_DataBase.setPassword("Root");
        if(!g_DataBase.open())
            QMessageBox::warning(nullptr,"警告","数据库打开失败",QMessageBox::Ok);
        else
        {
            QSqlQuery sql_query;
            QString sqlString = QString("select count(*) from sqlite_master where type='table' and name='day%1'").arg(QDateTime::currentDateTime().toString("dd"));
            sql_query.exec(sqlString);
            if(sql_query.next())
            {
                if(sql_query.value(0).toUInt() == 0)
                {
                    sqlString = QString("create table day%1 (id INTEGER PRIMARY KEY AUTOINCREMENT, threadID varchar(30),  date varchar(30),level varchar(30), file varchar(300),line int, info varchar(300))").arg(QDateTime::currentDateTime().toString("dd"));
                    if(!sql_query.exec(sqlString))
                        QMessageBox::warning(nullptr,"警告","数据库建表失败",QMessageBox::Ok);
                }
            }
        }



    }
}

void myLog(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QSqlQuery sql_query;
    QString insert_sql = "insert into student values (?, ?, ?)";
    QString temp,ThreadID,FileName,CurrentLine,Message;
    temp = msg;
    ThreadID = temp.mid(0,temp.indexOf("\r\n"));
    temp = temp.mid(temp.indexOf("\r\n")+2);
    FileName = temp.mid(0,temp.indexOf("\r\n"));
    temp = temp.mid(temp.indexOf("\r\n")+2);
    CurrentLine = temp.mid(0,temp.indexOf("\r\n"));
    temp = temp.mid(temp.indexOf("\r\n")+2);
    Message = temp.mid(0,temp.indexOf("\r\n"));

    switch(type)
    {
    default:
        break;
    case QtDebugMsg:
    {
        insert_sql = QString("insert into day%1(threadID,date,level,file,line,info) values ('%2', '%3', '%4','%5','%6','%7')")
                .arg(QDateTime::currentDateTime().toString("dd"))
                .arg(ThreadID)
                .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                .arg("Debug")
                .arg(FileName)
                .arg(CurrentLine)
                .arg(Message);
        sql_query.exec(insert_sql);
        break;
    }
    case QtInfoMsg:
    {
        insert_sql = QString("insert into day%1(threadID,date,level,file,line,info) values ('%2', '%3', '%4','%5','%6','%7')")
                .arg(QDateTime::currentDateTime().toString("dd"))
                .arg(ThreadID)
                .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                .arg("Info")
                .arg(FileName)
                .arg(CurrentLine)
                .arg(Message);
        sql_query.exec(insert_sql);
        break;
    }

    case QtWarningMsg:
    {
        insert_sql = QString("insert into day%1(threadID,date,level,file,line,info) values ('%2', '%3', '%4','%5','%6','%7')")
                .arg(QDateTime::currentDateTime().toString("dd"))
                .arg(ThreadID)
                .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                .arg("Warning")
                .arg(FileName)
                .arg(CurrentLine)
                .arg(Message);
        sql_query.exec(insert_sql);
        break;
    }
    case QtCriticalMsg:
    {
        insert_sql = QString("insert into day%1(threadID,date,level,file,line,info) values ('%2', '%3', '%4','%5','%6','%7')")
                .arg(QDateTime::currentDateTime().toString("dd"))
                .arg(ThreadID)
                .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                .arg("Critical")
                .arg(FileName)
                .arg(CurrentLine)
                .arg(Message);
        sql_query.exec(insert_sql);
        break;
    }
    case QtFatalMsg:
    {
        insert_sql = QString("insert into day%1(threadID,date,level,file,line,info) values ('%2', '%3', '%4','%5','%6','%7')")
                .arg(QDateTime::currentDateTime().toString("dd"))
                .arg(ThreadID)
                .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                .arg("Fatal")
                .arg(FileName)
                .arg(CurrentLine)
                .arg(Message);
        sql_query.exec(insert_sql);
        break;
    }
    }

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    openDB();
    qInstallMessageHandler(myLog);
    qInfo()<< QThread::currentThreadId()<<"\r\n"<<__FILE__<<"\r\n"<<__LINE__<<"\r\n"<<"系统启动";
    Widget w;
    w.show();
    return a.exec();
    g_DataBase.close();
}
