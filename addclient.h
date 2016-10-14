#ifndef ADDCLIENT_H
#define ADDCLIENT_H

#include <QDialog>

namespace Ui {
class Addclient;
}

class Addclient : public QDialog
{
    Q_OBJECT

public:
    explicit Addclient(QWidget *parent = 0);
    ~Addclient();


signals:
  void getClientData(QString name,QString surname,QString direction,QString tel,QString mail,QString ipc,QString ips,QString mac,int plan,float price);



private slots:
  void on_ok_clicked();

  void on_cancel_clicked();

private:
    Ui::Addclient *ui;
};

#endif // ADDCLIENT_H
