#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlTableModel>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->move(200,200);
    this->setMaximumSize(963,600);
    this->setMinimumSize(963,600);

    interface = new InterFace();

    QPalette Loginimage = this->palette();
    QImage ImgAllbackground(":/Image/Image/login.jpg");
    QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    Loginimage.setBrush(QPalette::Window, QBrush(fitimgpic));this->setPalette(Loginimage);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButtonLogin_clicked()
{
    QString user;
    QString pwd;
    user = ui->lineEditAccount->text();//获取用户名
    pwd = ui->lineEditPassword->text();//获取密码
    if(user == "")
         QMessageBox::warning(this,"","用户名不能为空！");
    else if(pwd == "")
         QMessageBox::warning(this,"","密码不能为空！");
         else
         {
            QSqlTableModel model;
            model.setTable("admin");
            model.setFilter(tr("user = '%1' and pwd = '%2'").arg(user).arg(pwd));
            model.select();
            if(model.rowCount()==1)//查询到有一个结果
            {
               interface->show();
               interface->sendUser(user);
               this->close();
            }
            else
               QMessageBox::warning(NULL,"Error","用户名或密码错误！！！");
               ui->lineEditPassword->clear();
        }
}

void Login::on_lineEditPassword_textEdited()
{
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
}

void Login::on_pushButtonLoginRegister_clicked()
{
    zhuce = new Zhuce();
    zhuce->show();
    this->hide();
}
