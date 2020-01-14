#include "login.h"
#include "connection.h"
#include <QApplication>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QProcess process;
    process.start("C:/Program Files/MySQL/MySQL Server 8.0/bin/mysqld.exe");
    if(!createConnection())
        return 1;
    Login w;
    w.show();
    return a.exec();
}
