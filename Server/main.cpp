#include "server.h"
#include "connection.h"
#include <QApplication>
#include <QProcess>
#include "chatdetail.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QProcess process;
    process.start("C:/Program Files/MySQL/MySQL Server 8.0/bin/mysqld.exe");
    if(!createConnection())return 1;
    Server w;
//    ChatDetail w;
    w.show();
    return a.exec();
}
