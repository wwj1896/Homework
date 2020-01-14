#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mydata");       //这里输入你的数据库名
    db.setUserName("root");
    db.setPassword("1111");   //这里输入你的密码
        if (!db.open())
        {
            QMessageBox::critical(0, QObject::tr("无法打开数据库"),
            "无法创建数据库连接！ ", QMessageBox::Cancel);
            return false;
        }else{
            QMessageBox::information(0,"提示","连接成功！");
            return true;
        }
}

#endif // CONNECTION_H
