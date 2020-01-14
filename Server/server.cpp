#include "server.h"
#include "ui_server.h"
#include <QMessageBox>
#include <QImageReader>
#include <QImage>
#include <QDateTime>

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

    this->setWindowTitle("服务器");
    this->move(1000,200);
    this->setMaximumSize(900,650);
    this->setMinimumSize(900,650);
    ui->pushButton->setEnabled(false);
    ui->pushButtonSendPic->setEnabled(false);
    ui->pushButtonOpenPic->setEnabled(false);
    //初始化服务器server对象
    mServer = new QTcpServer();
    //关联客户端连接信号newConnection
    connect(mServer,SIGNAL(newConnection()),this,SLOT(new_client())); //连接客户端
    //启动服务器监听
    mServer->listen(QHostAddress::Any,8888);

    connect(&timer,SIGNAL(timeout()),this,SLOT(sendData()));
//    connect(&timer,&QTimer::timeout,[=](){
//        //关闭定时器
//        timer.stop();

//        //发送文件
//        sendData();
//    });
}

Server::~Server()
{
    delete ui;
}

void Server::new_client()
{
    mSocket = new QTcpSocket(this);
    mSocket = mServer->nextPendingConnection();//与客户端通信的套接字
    //mSocket->setSocketDescriptor(socketDescriptor);
    tcpSocketConnetList.append(mSocket);

    //关联接收客户端数据信号readyRead信号（客户端有数据就会发readyRead信号）
    SendIP = mSocket->peerAddress().toString();
    SendIP = SendIP.remove(0,6);
    QMessageBox::information(this,"提示","新客户IP"+SendIP+"连接成功！");
    ui->labelshowConnect->setText("新客户IP"+SendIP+"连接成功！");
    ui->pushButton->setEnabled(true);
    ui->pushButtonOpenPic->setEnabled(true);
    ui->pushButtonSendPic->setEnabled(false);
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(read_client_data()));
    //检测掉线信号
    connect(mSocket,SIGNAL(disconnected()),this,SLOT(client_dis()));
}

void Server::read_client_data()
{
    ui->listWidgetShow->setCurrentItem(NULL);
    QString sendTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm");
    //可以实现同时读取多个客户端发送过来的消息
    QTcpSocket *obj = (QTcpSocket*)sender();
    QString msg = obj->readAll();
    SendIP = obj->peerAddress().toString();
    SendIP = SendIP.remove(0,7);

    ui->listWidgetShow->colorCount();
    QListWidgetItem *actionItem = new QListWidgetItem();
    actionItem->setText("用户:"+SendIP+sendTime+'\n'+msg);
    ui->listWidgetShow->addItem(actionItem);
    ui->listWidgetShow->setCurrentItem(actionItem, QItemSelectionModel::Select);
    QString ActionList;
    ActionList = actionItem->text();
    chatDetail(SendIP,sendTime,msg);
}

void Server::client_dis()
{
     QTcpSocket *obj = (QTcpSocket*)sender();//掉线对象
     SendIP = obj->peerAddress().toString();
     ui->labelshowConnect->setText("未连接。。。");
     ui->pushButton->setEnabled(false);
     ui->pushButtonSendPic->setEnabled(false);
     ui->pushButtonOpenPic->setEnabled(false);
     SendIP = SendIP.remove(0,7);
     QMessageBox::information(this,"提示","客户"+SendIP+"断开连接！");
}

void Server::on_pushButton_clicked()
{
    ui->listWidgetShow->setCurrentItem(NULL);

    QString sendTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm");
    QString msg = ui->textEditWriter->toPlainText();
    //取发送信息编辑框内容
    //mSocket->write(msg.toUtf8());//转编码
    for(int i = 0;i<tcpSocketConnetList.count();i++)//实现广播,即将新发送到服务器中的数据进行广播,发送到每一个连接的对象,进行同步更新对话框
    {
        QTcpSocket *item = tcpSocketConnetList.at(i);//
        item->write(msg.toUtf8());//转编码     
    }
    if(msg != NULL){
        QString w = "服务器";
        ui->listWidgetShow->colorCount();
        QListWidgetItem *actionItem = new QListWidgetItem();
        actionItem->setText(w+" "+sendTime+'\n'+msg);
        ui->listWidgetShow->addItem(actionItem);
        ui->listWidgetShow->setCurrentItem(actionItem, QItemSelectionModel::Select);
        QString ActionList;
        ActionList = actionItem->text();
        ui->textEditWriter->clear();
        chatDetail(w,sendTime,msg);
    }else{
        QMessageBox::information(this,"提示","请输入内容");
    }
}

void Server::on_pushButtonSendPic_clicked()
{  
    ui->listWidgetShow->setCurrentItem(NULL);

    QString msg = ui->textEditWriter->toPlainText();
    QString w = "Server";
    ui->listWidgetShow->colorCount();
    QListWidgetItem *actionItem = new QListWidgetItem();
    actionItem->setText(w+'\n'+msg);
    ui->listWidgetShow->addItem(actionItem);
    ui->listWidgetShow->setCurrentItem(actionItem, QItemSelectionModel::Select);
    QString ActionList;
    ActionList = actionItem->text();

    //先发送文件头信息  格式如：文件名##文件大小
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);

    //发送头部的信息
    qint64 len = mSocket->write(head.toUtf8());
    qDebug()<<"头部信息发送成功！";

    if (len > 0)//头部信息发送成功
    {
        qDebug()<<"定时器启动";
        //发送真正的文件信息
        //防止TCP黏包文件
        //需要通过定时器延时 20ms
        timer.start(200);
    }
    else
    {
        QMessageBox::information(this,"提示","头文件发送失败！");
        file.close();
    }
}

void Server::on_pushButtonOpenPic_clicked()
{
    QString filePath = QFileDialog ::getOpenFileName(this,"open","../");
    if (false == filePath.isEmpty())
    {
        fileName.clear();
        fileSize = 0;

        //获取文件信息
        QFileInfo info(filePath);
        fileName = info.fileName();//获取文件名字
        fileSize = info.size();//获取文件大小

        sendSize = 0;//发送文件的大小

        //只读方式打开文件
        //指定文件的名字
        file.setFileName(filePath);

        //打开文件
        bool isOk = file.open(QIODevice::ReadOnly);
        if (false == isOk)
        {
            qDebug()<<"只读方式打开文件失败 78";
        }
        //提示打开文件路径
        ui->textEditWriter->setText(filePath);
        ui->pushButton->setEnabled(false);
        ui->pushButtonSendPic->setEnabled(true);
        ui->pushButtonOpenPic->setEnabled(true);
    }
    else
    {
        qDebug()<<"选择文件路径出错 62 ";
        ui->pushButton->setEnabled(true);
    }
}

void Server::sendData()
{
    timer.stop();
    qint64 len = 0;
    do
    {
        //每次发送数据的大小 4K
        char buf[32*1024] = {0};
        len = 0;

        //往文件中读数据
        len  = file.read(buf,sizeof(buf));
        //发送数据，读多少 ，发多少
        len = mSocket->write(buf,len);

        //发送的数据需要积累
        sendSize += len;
        qDebug()<<"发送";
    }
    while(len > 0);
    //是否发送文件完毕
    if(sendSize == fileSize)
    {
        QMessageBox::information(this,"提示","文件发送完毕！");
        file.close();

        ui->textEditWriter->clear();
        ui->pushButton->setEnabled(true);
        ui->pushButtonOpenPic->setEnabled(true);
        ui->pushButtonSendPic->setEnabled(false);
    }
}

void Server::chatDetail(QString name,QString time,QString content)
{   
    QString sql = QString("INSERT INTO chatcontent (name,time,content) VALUES ('%1','%2','%3')").arg(name).arg(time).arg(content);
    QSqlQuery query;
    if(sql != NULL)
    {
        query.exec(sql);
    }
}

void Server::on_pushButtonConmentShow_clicked()
{
    chatdetail = new ChatDetail(this);
    chatdetail->show();
}
