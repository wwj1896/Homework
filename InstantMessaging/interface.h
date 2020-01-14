#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>

class IPConnect;
namespace Ui {
class InterFace;
}

class InterFace : public QWidget
{
    Q_OBJECT

public:
    explicit InterFace(QWidget *parent = 0);
    ~InterFace();
    void init();
    void sendUser(QString name);

signals:

private slots:
    void read_data();
    void connect_suc();
    void client_dis();

    void on_pushButtonSend_clicked();

    void on_pushButtonConnect_clicked();

    void on_pushButtonPicture_clicked();

    void on_pushButtonDisconnect_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::InterFace *ui;

    QTcpSocket *mSocket;
    IPConnect *ipconnect;

    QString sendName;
    QString sendTime;
    QString msg;
    QString sendSave;

    QString showConnect;

    QFile file;//文件对象

    QString fileName;//文件名字
    qint64 fileSize;//文件大小
    qint64 recvSize;//已经接收文件的大小

    bool isStart;//接收头文件标志

};

#endif // INTERFACE_H
