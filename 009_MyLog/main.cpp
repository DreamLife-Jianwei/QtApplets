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


static QSqlDatabase g_DataBase;                 //数据库




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
    temp->setPath("./log");
    temp->setFilter(QDir::Dirs);
    QFileInfoList list = temp->entryInfoList();
    int i = 0;
    do{
        QFileInfo fileInfo = list.at(i);
       if((fileInfo.fileName() != QDateTime::currentDateTime().toString("yyyy")) &&
               (fileInfo.fileName() != ".") &&
               (fileInfo.fileName() != ".."))
       {
           temp->setPath("./log/" + fileInfo.fileName());
           temp->removeRecursively();
       }
       ++i;
    }while (i<list.size());

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
    }
}






int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    openDB();

    Widget w;
    w.show();
    return a.exec();
    g_DataBase.close();
}
