#ifndef CHATDETAIL_H
#define CHATDETAIL_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>

class QSqlTableModel;

namespace Ui {
class ChatDetail;
}

class ChatDetail : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDetail(QWidget *parent = 0);
    ~ChatDetail();

private slots:
    void on_pushButtonBack_clicked();

    void on_pushButtonSelect_clicked();

    void on_pushButtonUp_clicked();

    void on_pushButtonDown_clicked();

    void on_pushButton_clicked();

private:
    Ui::ChatDetail *ui;

    QSqlTableModel *model;

};

#endif // CHATDETAIL_H
