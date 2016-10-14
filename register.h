#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include<QtSql/QSqlQuery>
namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:


    explicit Register(QWidget *parent = 0);
    ~Register();

private slots:



    void on_cancel_clicked();

    void on_ok_clicked();

signals:
    void getAdminData(QString usr,QString psw,int lvl);




private:
    Ui::Register *ui;


};

#endif // REGISTER_H
