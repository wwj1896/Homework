#include "zhuce.h"
#include "ui_zhuce.h"
#include "login.h"

#include <QSqlQuery>
#include <QMessageBox>

Zhuce::Zhuce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Zhuce)
{
    ui->setupUi(this);

    ui->lineEditadmin->setPlaceholderText("請输入用户名");

    ui->lineEditpassword->setPlaceholderText("请输入密码");
}

Zhuce::~Zhuce()
{
    delete ui;
}

void Zhuce::on_pushButtonback_clicked()
{
    back();
}

void Zhuce::back()
{
    Login *login = new Login();
    login->show();
    this->hide();
}

void Zhuce::on_pushButtonzhuce_clicked()
{
    QString user;
    QString pwd;
    user = ui->lineEditadmin->text();
    pwd = ui->lineEditpassword->text();
    if(user == "")
        QMessageBox::warning(this,"","用户名不能为空！");
    else if(pwd == "")
        QMessageBox::warning(this,"","密码不能为空！");
    else
    {
        QString i=QString("insert into admin values ('%1','%2'); ").arg(user).arg(pwd);
        QString S =QString("select * from admin where user='%1' ").arg(user);
        QSqlQuery query;
         if(query.exec(i))
            {
             QMessageBox::information(NULL, "注册成功", "注册成功！！！", QMessageBox::Yes);
             back();
         }
         else if(query.exec(S)&&query.first())
            QMessageBox::warning(NULL,"Error","用户名重复！！！");
         else
            QMessageBox::warning(NULL,"Error","注册失败，请重试！！！");
    }
}
