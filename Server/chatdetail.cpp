#include "chatdetail.h"
#include "ui_chatdetail.h"

#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

ChatDetail::ChatDetail(QWidget *parent) :
    QDialog (parent),
    ui(new Ui::ChatDetail)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this);
    model->setTable("chatcontent");
    model->select();
    // 设置编辑策略
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);

}

ChatDetail::~ChatDetail()
{
    delete ui;
}

void ChatDetail::on_pushButtonBack_clicked()
{
    this->close();
}


void ChatDetail::on_pushButtonSelect_clicked()
{
    QString name = ui->lineEditName->text();
        if(name.length()){
        //根据姓名进行筛选， 一定要使用单引号
        model->setFilter(QString("name = '%1'").arg(name));
        model->select();
        }
        else
        {
            QMessageBox::warning(this, tr("Warning"),tr("姓名不能为空") );
        }
}

void ChatDetail::on_pushButton_clicked()
{
    model->setTable("chatcontent");
    model->select();
}

void ChatDetail::on_pushButtonUp_clicked()
{
    model->setSort(0, Qt::AscendingOrder);
    model->select();
}

void ChatDetail::on_pushButtonDown_clicked()
{
    model->setSort(0, Qt::DescendingOrder);
    model->select();
}
