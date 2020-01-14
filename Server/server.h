#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QBuffer>
#include <QFileDialog>
#include <QFile>
#include <QTimer>
#include <QSqlQuery>
#include "chatdetail.h"
namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();   
private slots:
    void new_client();
    void read_client_data();
    void client_dis();

    void on_pushButton_clicked();

    void on_pushButtonSendPic_clicked();

    void on_pushButtonOpenPic_clicked();
    void sendData();
    void chatDetail(QString name,QString time,QString content);

    void on_pushButtonConmentShow_clicked();

private:
    Ui::Server *ui;
    QList<QTcpSocket *> tcpSocketConnetList;

    QString SendIP;
    QTcpServer *mServer;
    QTcpSocket *mSocket;

    ChatDetail *chatdetail;
    QTimer timer;
    QString fileName;//文件名字
    qint64 fileSize;//文件大小
    qint64 sendSize;//已经发送文件的大小
    QFile file;
};

#endif // SERVER_H
