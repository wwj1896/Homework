#include "interface.h"
#include "ui_interface.h"
#include "connection.h"
#include <QMessageBox>
#include <QList>
#include <QBuffer>
#include <QSqlQuery>

InterFace::InterFace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterFace)
{
    ui->setupUi(this);
    this->setWindowTitle("客户端");
    this->move(100,200);
    this->setMaximumSize(1020,700);
    this->setMinimumSize(1020,700);
    mSocket = new QTcpSocket();
    init();

    ui->pushButtonSend->setEnabled(false);
    ui->pushButtonDisconnect->setEnabled(false);
    ui->calendarWidget->hide();
    //初始化套接字对象

    //检测链接成功信号关联槽函数
    connect(mSocket,SIGNAL(connected()),this,SLOT(connect_suc()));
    //检测掉线信号
    connect(mSocket,SIGNAL(disconnected()),this,SLOT(client_dis()));
    //关联数据信号
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(read_data()));
}

InterFace::~InterFace()
{
    delete ui;
}

void InterFace::connect_suc()
{
    ui->pushButtonConnect->setEnabled(false);//如果连接成功则连接按钮不能按下
    QMessageBox::information(this, "Title", "连接成功！");
    ui->pushButtonSend->setEnabled(true);
    ui->pushButtonDisconnect->setEnabled(true);
    ui->pushButtonConnect->setEnabled(false);
    showConnect = mSocket->peerAddress().toString();
    ui->labelShowConnect->setText("服务器IP:"+showConnect+"    连接成功！");
    ui->calendarWidget->show();
}

void InterFace::client_dis()
{
    QMessageBox::warning(this,"提示","断开连接");
    ui->pushButtonSend->setEnabled(false);
    ui->pushButtonConnect->setEnabled(true);//如果连接没有成功则连接按钮还可以按下
    ui->textEditWriter->clear();
    ui->pushButtonDisconnect->setEnabled(false);
    ui->pushButtonConnect->setEnabled(true);
    ui->labelShowConnect->setText("未连接服务器...");
}

void InterFace::read_data()
{
    ui->listWidgetShow->setCurrentItem(NULL);
    QTcpSocket *obj = (QTcpSocket*)sender();
    QByteArray buf = obj->readAll();
    if (true == isStart)
    {
        //接收头
        isStart = false;
        //            分段   0   0  1  1  2    2
        //解析头部信息 buf = "hello##1024##333333"
//            QString str = "hello##1024";
//            str.section("##",0,0);//这个拆出来hello，其中##是分段标识符，格式为：段1+标识符+段2+标识符+段3+标识符+……
        //初始化
        fileName = QString(buf).section("##",0,0);
        fileSize = QString(buf).section("##",1,1).toInt();
        if(fileSize == 0){
            sendName = "Mr.wang";
            sendTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm");

            sendSave = sendName+"   "+sendTime+'\n'+buf;

            QListWidgetItem *actionItem = new QListWidgetItem();
            actionItem->setText(sendSave);
            ui->listWidgetShow->addItem(actionItem);
            ui->listWidgetShow->setCurrentItem(actionItem, QItemSelectionModel::Select);
            QString ActionList;
            ActionList = actionItem->text();
            init();
            return;
        }
        QString str =QString("[%1 : %2kb]").arg(fileName).arg(fileSize/1024);
        ui->listWidgetShow->setCurrentItem(NULL);
        sendName = "Mr.wang";
        sendTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm");
        sendSave = sendName+"   "+sendTime+'\n'+str;

        QListWidgetItem *actionItem = new QListWidgetItem();
        actionItem->setText(sendSave);
        ui->listWidgetShow->addItem(actionItem);
        ui->listWidgetShow->setCurrentItem(actionItem, QItemSelectionModel::Select);
        //QString ActionList;
        //ActionList = actionItem->text();

        //打开文件
        file.setFileName(fileName);
        bool isOk = file.open(QIODevice::WriteOnly);
        if (false == isOk)
        {
            file.close();//关闭文件
            //ui->listWidgetShow->deleteLater();
        }
        //弹出对话框，显示接收文件信息
//        QString str =QString("接收文件： [%1 : %2kb]").arg(fileName).arg(fileSize/1024);
//        QMessageBox::information(this,"文件信息",str);

        //设置进度条
        ui->progressBar->setMinimum(0);//最小值
        ui->progressBar->setMaximum(fileSize/1024);//最大值
        //ui->progressBar->setValue(0);//当前值
    }else{
            qint64 len =  file.write(buf);
            if(len > 0)
            {
                recvSize += len;//累积接收大小
            }
            //更新进度条
            ui->progressBar->setValue(recvSize/1024);
            qDebug()<<"1";
            if (ui->progressBar->text() == "100%")
            {
            //先给服务发送（接收文件完成的消息）
            //mSocket->write("file done ");
            QMessageBox::information(this,"完成","文件接收完毕");
            file.close();//关闭文件
            init();
            }
        }
}

void InterFace::on_pushButtonSend_clicked()
{
    ui->listWidgetShow->setCurrentItem(NULL);
    sendName = ui->labelName->text();
    sendTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm");

    //取发送信息编辑框内容
    //QString msg = ui->textEditWriter->toPlainText();
    msg = ui->textEditWriter->toPlainText();
    sendSave = sendName+"   "+sendTime+'\n'+msg;
    mSocket->write(msg.toUtf8());//转编码

    if(msg != NULL){
    ui->listWidgetShow->colorCount();
    QListWidgetItem *actionItem = new QListWidgetItem();
    actionItem->setText(sendSave);
    ui->listWidgetShow->addItem(actionItem);
    ui->listWidgetShow->setCurrentItem(actionItem, QItemSelectionModel::Select);
    QString ActionList;
    ActionList = actionItem->text();
    ui->textEditWriter->clear();
    }else{
        QMessageBox::information(this,"提示","请输入内容");
    }
}

void InterFace::on_pushButtonConnect_clicked()
{
    ui->textEditWriter->setFocus();
    //连接服务器，设置ip和端口号
    mSocket->connectToHost(ui->lineEditIP->text(),ui->lineEditPort->text().toInt());
}

void InterFace::on_pushButtonPicture_clicked()
{

}

void InterFace::on_pushButtonDisconnect_clicked()
{
    mSocket->disconnectFromHost();
}

void InterFace::on_pushButtonClose_clicked()
{
    this->close();
}

void InterFace::init(){
    isStart = true;
    ui->progressBar->setValue(0);//当前值
    fileSize = 0;
    recvSize = 0; 
}

void InterFace::sendUser(QString name)
{
    ui->labelName->setText(name);
}
