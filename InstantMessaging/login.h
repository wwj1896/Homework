#ifndef LOGIN_H
#define LOGIN_H

#include "interface.h"
#include "zhuce.h"

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButtonLogin_clicked();

    void on_lineEditPassword_textEdited();

    void on_pushButtonLoginRegister_clicked();

private:
    Ui::Login *ui;

    InterFace *interface;
    Zhuce *zhuce;
};

#endif // LOGIN_H
