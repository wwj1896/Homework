#ifndef ZHUCE_H
#define ZHUCE_H

#include <QDialog>

namespace Ui {
class Zhuce;
}

class Zhuce : public QDialog
{
    Q_OBJECT

public:
    explicit Zhuce(QWidget *parent = 0);
    ~Zhuce();

    void back();

private slots:
    void on_pushButtonback_clicked();

    void on_pushButtonzhuce_clicked();

private:
    Ui::Zhuce *ui;
};

#endif // ZHUCE_H
